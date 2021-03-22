#include "arch.h"

#include "lib.h"

#include "lib/header/elf.h"

static CHAR16 s[17];

EFI_FILE_PROTOCOL *getVolume(EFI_SYSTEM_TABLE *SystemTable, EFI_HANDLE image)
{
	EFI_LOADED_IMAGE *loaded_image = NULL;
	EFI_GUID lipGUID = EFI_LOADED_IMAGE_PROTOCOL_GUID;
	EFI_FILE_IO_INTERFACE *IOVolume;
	EFI_GUID fsGUID = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
	EFI_FILE_PROTOCOL Volume;
	EFI_FILE_PROTOCOL *Vol = &Volume;

	/* ファイルを開くのに必要な構造体を用意する */
	SystemTable->BootServices->HandleProtocol((VOID *)image, &lipGUID, (VOID **)&loaded_image);
	SystemTable->BootServices->HandleProtocol(loaded_image->DeviceHandle, &fsGUID, (VOID *)&IOVolume);
	IOVolume->OpenVolume(IOVolume, &Vol);

	return Vol;
}

UINT64 FileSize(EFI_FILE_PROTOCOL *FileHandle)
{
	UINT64 ret;
	EFI_FILE_INFO FileInfo;
	EFI_FILE_INFO *pFileInfo = &FileInfo;
	UINTN BufferSize = sizeof(EFI_FILE_INFO);
	EFI_GUID FInfoID = EFI_FILE_INFO_ID;

	FileHandle->GetInfo(FileHandle, &FInfoID, &BufferSize, pFileInfo);

	ret = pFileInfo->FileSize;

	return ret;
}

void CalcLoadAddressRange(Elf64_Ehdr *ehdr, UINT64 *first, UINT64 *last)
{
	Elf64_Phdr *phdr = (Elf64_Phdr *)((UINT64)ehdr + ehdr->e_phoff);
	*first = 18446744073709551615ULL;
	*last = 0ULL;

	for(Elf64_Half i = 0; i < ehdr->e_phnum; ++i){
		if(phdr[i].p_type != PT_LOAD) continue;

		*first = MIN(*first, phdr[i].p_vaddr);
		*last = MAX(*last, phdr[i].p_vaddr + phdr[i].p_memsz);
	}

	return;
}

void CopyLoadSegments(EFI_SYSTEM_TABLE *ST, Elf64_Ehdr *ehdr)
{
	Elf64_Phdr *phdr = (Elf64_Phdr *)((UINT64)ehdr + ehdr->e_phoff);

	for(Elf64_Half i = 0; i < ehdr->e_phnum; ++i){
		if(phdr[i].p_type != PT_LOAD) continue;

		UINT64 segm_in_file = (UINT64)ehdr + phdr[i].p_offset;
		ST->BootServices->CopyMem((VOID *)phdr[i].p_vaddr, (VOID *)segm_in_file, phdr[i].p_filesz);

		UINTN remain_bytes = phdr[i].p_memsz - phdr[i].p_filesz;
		ST->BootServices->SetMem((VOID *)(phdr[i].p_vaddr + phdr[i].p_filesz), remain_bytes, 0);
	}
}

void PrintMemoryType(UINT32 Type)
{
	switch(Type){
		case EfiReservedMemoryType:
			print(L"EfiReservedMemoryType");
			break;
		case EfiLoaderCode:
			print(L"EfiLoaderCode");
			break;
		case EfiLoaderData:
			print(L"EfiLoaderData");
			break;
		case EfiBootServicesCode:
			print(L"EfiBootServicesCode");
			break;
		case EfiBootServicesData:
			print(L"EfiBootServicesData");
			break;
		case EfiRuntimeServicesCode:
			print(L"EfiRuntimeServicesCode");
			break;
		case EfiRuntimeServicesData:
			print(L"EfiRuntimeServicesData");
			break;
		case EfiConvertionalMemory:
			print(L"EfiConvertionalMemory");
			break;
		case EfiUnusableMemory:
			print(L"EfiUnusableMemory");
			break;
		case EfiACPIReclaimMemory:
			print(L"EfiACPIReclaimMemory");
			break;
		case EfiACPIMemoryNVS:
			print(L"EfiACPIMemoryNVS");
			break;
		case EfiMemoryMappedIO:
			print(L"EfiMemoryMappedIO");
			break;
		case EfiMemoryMappedIOPortSpace:
			print(L"EfiMemoryMappedIOPortSpace");
			break;
		case EfiPalCode:
			print(L"EfiPalCode");
			break;
		case EfiPersistentMemory:
			print(L"EfiPersistentMemory");
			break;
		case EfiMaxMemoryType:
			print(L"EfiMaxMemoryType");
			break;
	}

	return;
}

EFI_STATUS loader_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_STATUS Status;
	EFI_GUID GOP_GUID = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info;
	EFI_FILE_PROTOCOL *Volume;
	UINTN SizeOfInfo, numModes, nativeMode, mode;
	UINTN i;
	CHAR16 *FileName = L"kernel.bin";
	EFI_FILE_PROTOCOL FileHandle;
	EFI_FILE_PROTOCOL *FHandle = &FileHandle;
	UINT64 ReadSize;
	CHAR8 *Buffer;
	Elf64_Ehdr *kernel_elfhdr;
	UINT64 kernel_start, kernel_end;
	UINTN MemoryMapSize = sizeof(EFI_MEMORY_DESCRIPTOR);
	EFI_MEMORY_DESCRIPTOR *pMemoryMap = NULL;
	UINTN MapKey = 0;
	UINTN DescriptorSize = MemoryMapSize;
	UINT32 DescriptorVersion;

	ConOut = SystemTable->ConOut;

	ConOut->ClearScreen(ConOut);

	/* 描画準備 */
	Status = SystemTable->BootServices->LocateProtocol(&GOP_GUID, NULL, (VOID **)&GOP);
	Status = GOP->QueryMode(GOP, GOP->Mode == NULL ? 0 : GOP->Mode->Mode, &SizeOfInfo, &info);

	if(Status == EFI_NOT_STARTED) Status = GOP->SetMode(GOP, 0);

	if(Status == EFI_SUCCESS){
		nativeMode = GOP->Mode->Mode;
		numModes = GOP->Mode->MaxMode;
	}else{
		print(L"unable to get native mode");
	}

	mode = nativeMode;

	/* 使用可能なモードをすべて表示 */
	for(i = 0; i < numModes; i++){
		Status = GOP->QueryMode(GOP, i, &SizeOfInfo, &info);

		print(L"mode:");
		setdec(s, i, 4);
		print(s);
		print(L" width:");
		setdec(s, info->HorizontalResolution, 5);
		print(s);
		print(L" height:");
		setdec(s, info->VerticalResolution, 5);
		print(s);
		print(L" format:");
		setdec(s, info->PixelFormat, 2);
		print(s);
		print(i == nativeMode ? L"(current)" : L"");
		print(L"\r\n");

		/* 1920x1080な画面モードがあればデフォルトにしたいので設定 */
		if(info->HorizontalResolution == 1920 && info->VerticalResolution == 1080){
			mode = i;
		}
	}

	print(L"\r\n");
	print(L"select mode:");
	setdec(s, mode, 4);
	print(s);

	/* 画面を設定 */
	GOP->SetMode(GOP, mode);

	if(Status == EFI_SUCCESS){
		print(L"framebuffer address:");
		sethex(s, GOP->Mode->FrameBufferBase, 17);
		print(s);
		print(L" size:");
		setdec(s, GOP->Mode->FrameBufferSize, 8);
		print(s);
		print(L" width:");
		setdec(s, GOP->Mode->Info->HorizontalResolution, 5);
		print(s);
		print(L" height:");
		setdec(s, GOP->Mode->Info->VerticalResolution, 5);
		print(s);
		print(L" pixelsperline:");
		setdec(s, GOP->Mode->Info->PixelsPerScanLine, 5);
		print(s);
		print(L"\r\n");
	}else{
		print(L"unable to set mode:");
		setdec(s, mode, 4);
		print(s);
	}

	/* カーネルファイルを開く準備 */
	Volume = getVolume(SystemTable, ImageHandle);

	Volume->Open(Volume, &FHandle, FileName, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM);

	ReadSize = FileSize(FHandle);
	SystemTable->BootServices->AllocatePool(EfiLoaderData, ReadSize, (VOID **)&Buffer);

	FHandle->Read(FHandle, &ReadSize, Buffer);

	FHandle->Close(FHandle);

	kernel_elfhdr = (Elf64_Ehdr *)Buffer;

	print(L"Magic[0]:");
	sethex(s, kernel_elfhdr->e_ident[0], 3);
	print(s);
	print(L" Magic[1]:");
	sethex(s, kernel_elfhdr->e_ident[1], 3);
	print(s);
	print(L" Magic[2]:");
	sethex(s, kernel_elfhdr->e_ident[2], 3);
	print(s);
	print(L" Magic[3]:");
	sethex(s, kernel_elfhdr->e_ident[3], 3);
	print(s);	

	CalcLoadAddressRange(kernel_elfhdr, &kernel_start, &kernel_end);

	UINTN pages = (kernel_end - kernel_start + 0xfff) / 0x1000;

	Status = SystemTable->BootServices->AllocatePages(AllocateAddress, EfiLoaderData, pages, &kernel_start);

	if(Status != EFI_SUCCESS){
		print(L" ");
		sethex(s, Status, 17);
		print(s);
		print(L"\r\npages allocate error.");
	}

	CopyLoadSegments(SystemTable, kernel_elfhdr);

	SystemTable->BootServices->FreePool(Buffer);

	Status = SystemTable->BootServices->GetMemoryMap(&MemoryMapSize, pMemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);

chkerr:
	if(Status != EFI_SUCCESS){
		if(Status != EFI_BUFFER_TOO_SMALL){
			print(L"\r\nmemory map get error.");
			print(L" ");
			while(1);
		}else{
			SystemTable->BootServices->AllocatePool(EfiLoaderData, MemoryMapSize, (VOID **)&pMemoryMap);
			Status = SystemTable->BootServices->GetMemoryMap(&MemoryMapSize, pMemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
			goto chkerr;
		}
	}

	print(L"\r\n");

	EFI_PHYSICAL_ADDRESS iter;

	for(iter = (EFI_PHYSICAL_ADDRESS)pMemoryMap, i = 0; iter < (EFI_PHYSICAL_ADDRESS)pMemoryMap + MemoryMapSize && i < 10; iter += DescriptorSize, i++){
		EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)iter;

		PrintMemoryType(desc->Type);
		print(L" ");
		sethex(s, desc->PhysicalStart, 17);
		print(s);
		print(L" ");
		sethex(s, desc->VirtualStart, 17);
		print(s);
		print(L" ");
		sethex(s, desc->NumberOfPages, 17);
		print(s);
		print(L" ");
		print(L"\r\n");
	}

	/* GOP描画テスト 矩形描画 */
	fillrect(GOP, 50, 50, 100, 100, 0x00, 0xff, 0x00);

	sethex(s, kernel_start, 17);
	print(s);

	print(L"\r\n");

	UINT64 kernel_addr = *(UINT64 *)(kernel_start + 24);

	sethex(s, kernel_addr, 17);
	print(s);

	Status = SystemTable->BootServices->ExitBootServices(ImageHandle, MapKey);
	if(Status != EFI_SUCCESS){
		SystemTable->BootServices->GetMemoryMap(&MemoryMapSize, pMemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
		Status = SystemTable->BootServices->ExitBootServices(ImageHandle, MapKey);

		if(Status != EFI_SUCCESS){
			print(L"ExitBootServices Error");
			while(1);
		}
	}

	typedef void kernel_main(UINT32 width, UINT32 height, char *vram);
	kernel_main *kernel = (kernel_main *)kernel_addr;
	kernel(GOP->Mode->Info->HorizontalResolution, GOP->Mode->Info->VerticalResolution, (char *)GOP->Mode->FrameBufferBase);

	while(1);

	return Status;
}

