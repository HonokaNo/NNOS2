#ifndef __UEFI_H__
#define __UEFI_H__

/* 2.3.1 Data Types */
typedef unsigned char BOOLEAN;
#define FALSE 0
#define TRUE 1

/* signed integer */
typedef signed char INT8;
typedef signed short INT16;
typedef signed int INT32;
typedef signed long INT64;
typedef signed __int128 INT128;

/* unsigned integer */
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long long UINT64;
typedef unsigned __int128 UINT128;

#if ARCH_BIT == 32
	typedef INT32 INTN;
	typedef UINT32 UINTN;
#elif ARCH_BIT == 64
	typedef INT64 INTN;
	typedef UINT64 UINTN;
#elif ARCH_BIT == 128
	typedef INT128 INTN;
	typedef UINT128 UINTN;
#else
	#error You must define ARCH_BIT
#endif

typedef unsigned char CHAR8;
typedef unsigned short CHAR16;

typedef void VOID;

typedef struct
{
	UINT32 Data1;
	UINT16 Data2;
	UINT16 Data3;
	UINT8 Data4[8];
}EFI_GUID;

typedef UINTN EFI_STATUS;
typedef VOID* EFI_HANDLE;
typedef VOID* EFI_EVENT;
typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;

typedef struct
{
	UINT8 Addr[32];
}EFI_MAC_ADDRESS;

typedef struct
{
	UINT8 Addr[4];
}EFI_IPv4_ADDRESS;

typedef struct
{
	UINT8 Addr[16];
}EFI_IPv6_ADDRESS;

typedef union
{
	UINT32 Addr[4];
	EFI_IPv4_ADDRESS v4;
	EFI_IPv6_ADDRESS v6;
}EFI_IP_ADDRESS;

#define IN
#define OUT
#define OPTIONAL
#define CONST const
#define EFIAPI

typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;

/* Status Codes */

#if ARCH_BIT == 32
	#define EFI_SUCCESS		0x00000000
	#define EFI_NOT_READY	0x80000006
	#define EFI_NOT_STARTED	0x80000013
#elif ARCH_BIT == 64
	#define EFI_SUCCESS		0x0000000000000000ULL
	#define EFI_NOT_READY	0x8000000000000006ULL
	#define EFI_NOT_STARTED	0x8000000000000013ULL
#else
	#error not support
#endif

/* Open Modes */
#define EFI_FILE_MODE_READ		0x0000000000000001ULL
#define EFI_FILE_MODE_WRITE		0x0000000000000002ULL
#define EFI_FILE_MODE_CREATE	0x8000000000000000ULL

/* File Attributes */
#define EFI_FILE_READ_ONLY		0x0000000000000001ULL
#define EFI_FILE_HIDDEN			0x0000000000000002ULL
#define EFI_FILE_SYSTEM			0x0000000000000004ULL
#define EFI_FILE_RESERVED		0x0000000000000008ULL
#define EFI_FILE_DIRECTORY		0x0000000000000010ULL
#define EFI_FILE_ARCHIVE		0x0000000000000020ULL
#define EFI_FILE_VALID_ATTR		0x0000000000000037ULL

typedef struct _EFI_MEMORY_DESCRIPTOR EFI_MEMORY_DESCRIPTOR;
typedef struct _EFI_TABLE_HEADER EFI_TABLE_HEADER;
typedef struct _EFI_SYSTEM_TABLE EFI_SYSTEM_TABLE;
typedef struct _EFI_BOOT_SERVICES EFI_BOOT_SERVICES;
typedef enum _EFI_ALLOCATE_TYPE EFI_ALLOCATE_TYPE;
typedef enum _EFI_MEMORY_TYPE EFI_MEMORY_TYPE;
typedef enum _EFI_TIMER_DELAY EFI_TIMER_DELAY;
typedef enum _EFI_INTERFACE_TYPE EFI_INTERFACE_TYPE;
typedef enum _EFI_LOCATE_SEARCH_TYPE EFI_LOCATE_SEARCH_TYPE;
typedef struct _EFI_OPEN_PROTOCOL_INFORMATION_ENTRY EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;
typedef struct _EFI_RUNTIME_SERVICES EFI_RUNTIME_SERVICES;
typedef struct _EFI_TIME EFI_TIME;
typedef struct _EFI_TIME_CAPABILITIES EFI_TIME_CAPABILITIES;
typedef enum _EFI_RESET_TYPE EFI_RESET_TYPE;
typedef struct _EFI_CAPSULE_HEADER EFI_CAPSULE_HEADER;
typedef struct _EFI_CONFIGURATION_TABLE EFI_CONFIGURATION_TABLE;
typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL EFI_GRAPHICS_OUTPUT_PROTOCOL;
typedef struct _EFI_PIXEL_BITMASK EFI_PIXEL_BITMASK;
typedef enum _EFI_GRAPHICS_PIXEL_FORMAT EFI_GRAPHICS_PIXEL_FORMAT;
typedef struct _EFI_GRAPHICS_OUTPUT_MODE_INFORMATION EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;
typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;
typedef struct _EFI_GRAPHICS_OUTPUT_BLT_PIXEL EFI_GRAPHICS_OUTPUT_BLT_PIXEL;
typedef enum _EFI_GRAPHICS_OUTPUT_BLT_OPERATION EFI_GRAPHICS_OUTPUT_BLT_OPERATION;
typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
typedef struct _EFI_INPUT_KEY EFI_INPUT_KEY;
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
typedef struct _SIMPLE_TEXT_OUTPUT_MODE SIMPLE_TEXT_OUTPUT_MODE;
typedef struct _EFI_DEVICE_PATH_PROTOCOL EFI_DEVICE_PATH_PROTOCOL;
typedef struct _EFI_LOADED_IMAGE_PROTOCOL EFI_LOADED_IMAGE_PROTOCOL;
typedef EFI_LOADED_IMAGE_PROTOCOL EFI_LOADED_IMAGE;
typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;
typedef EFI_SIMPLE_FILE_SYSTEM_PROTOCOL EFI_FILE_IO_INTERFACE;
typedef struct _EFI_FILE_PROTOCOL EFI_FILE_PROTOCOL;
typedef struct _EFI_FILE_IO_TOKEN EFI_FILE_IO_TOKEN;
typedef struct _EFI_FILE_INFO EFI_FILE_INFO;

struct _EFI_MEMORY_DESCRIPTOR
{
	UINT32 Type;
	EFI_PHYSICAL_ADDRESS PhysicalStart;
	EFI_VIRTUAL_ADDRESS VirtualStart;
	UINT64 NumberOfPages;
	UINT64 Attribute;
};

struct _EFI_TABLE_HEADER
{
	UINT64 Signature;
	UINT32 Revision;
	UINT32 HeaderSize;
	UINT32 CRC32;
	UINT32 Reserved;
};

struct _EFI_SYSTEM_TABLE
{
	EFI_TABLE_HEADER Hdr;
	CHAR16 *FirmwareVendor;
	UINT32 FirmwareRevision;
	EFI_HANDLE ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
	EFI_HANDLE ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
	EFI_HANDLE StandardErrorHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
	EFI_RUNTIME_SERVICES *RuntimeServices;
	EFI_BOOT_SERVICES *BootServices;
	UINTN NumberOfTableEntries;
	EFI_CONFIGURATION_TABLE *ConfigurationTable;
};

/* 関数ポインタのtypedefはこんな文法になる */
/* qiita.com/aminevsky/items/82ecce1d6d8b42d65533を参考にしました */
typedef VOID (*EFI_EVENT_NOTIFY)(IN EFI_EVENT Event, IN VOID *Context);

struct _EFI_BOOT_SERVICES
{
	EFI_TABLE_HEADER Hdr;

	EFI_TPL (*RaiseTPL)(
		IN EFI_TPL NewTpl
	);
	VOID (*RestoreTPL)(
		IN EFI_TPL OldTpl
	);
	EFI_STATUS (*AllocatePages)(
		IN EFI_ALLOCATE_TYPE Type,
		IN EFI_MEMORY_TYPE MemoryType,
		IN UINTN Pages,
		IN OUT EFI_PHYSICAL_ADDRESS *Memory
	);
	EFI_STATUS (*FreePages)(
		IN EFI_PHYSICAL_ADDRESS Memory,
		IN UINTN Pages
	);
	EFI_STATUS (*GetMemoryMap)(
		IN OUT UINTN *MemoryMapSize,
		OUT EFI_MEMORY_DESCRIPTOR *MemoryMap,
		OUT UINTN *MapKey,
		OUT UINTN *DescriptorSize,
		OUT UINT32 *DescriptorVersion
	);
	EFI_STATUS (*AllocatePool)(
		IN EFI_MEMORY_TYPE PoolType,
		IN UINTN Size,
		OUT VOID **Buffer
	);
	EFI_STATUS (*FreePool)(
		IN VOID *Buffer
	);
	EFI_STATUS (*CreateEvent)(
		IN UINT32 Type,
		IN EFI_TPL NotifyTpl,
		IN EFI_EVENT_NOTIFY NotifyFunction OPTIONAL,
		IN VOID *NotifyContext OPTIONAL,
		OUT EFI_EVENT *Event
	);
	EFI_STATUS (*SetTimer)(
		IN EFI_EVENT Event,
		IN EFI_TIMER_DELAY Type,
		IN UINT64 TriggerTime
	);
	EFI_STATUS (*WaitForEvent)(
		IN UINTN NumberOfEvents,
		IN EFI_EVENT *Event,
		OUT UINTN *Index
	);
	EFI_STATUS (*SignalEvent)(
		IN EFI_EVENT Event
	);
	EFI_STATUS (*CloseEvent)(
		IN EFI_EVENT Event
	);
	EFI_STATUS (*CheckEvent)(
		IN EFI_EVENT Event
	);
	EFI_STATUS (*InstallProtocolInterface)(
		IN OUT EFI_HANDLE *Handle,
		IN EFI_GUID *Protocol,
		IN EFI_INTERFACE_TYPE InterfaceType,
		IN VOID *Interface
	);
	EFI_STATUS (*ReinstallProtocolInterface)(
		IN EFI_HANDLE Handle,
		IN EFI_GUID *Protocol,
		IN VOID *OldInterface,
		IN VOID *NewInterface
	);
	EFI_STATUS (*UninstallProtocolInterface)(
		IN EFI_HANDLE Handle,
		IN EFI_GUID *Protocol,
		IN VOID *Interface
	);
	EFI_STATUS (*HandleProtocol)(
		IN EFI_HANDLE Handle,
		IN EFI_GUID *Protocol,
		OUT VOID **Interface
	);
	VOID *Reserved;
	EFI_STATUS (*RegisterProtocolNotify)(
		IN EFI_GUID *Protocol,
		IN EFI_EVENT Event,
		OUT VOID **Registration
	);
	EFI_STATUS (*LocateHandle)(
		IN EFI_LOCATE_SEARCH_TYPE SearchType,
		IN EFI_GUID *Protocol OPTIONAL,
		IN VOID *SearchKey OPTIONAL,
		IN OUT UINTN *BufferSize,
		OUT EFI_HANDLE *Buffer
	);
	EFI_STATUS (*LocateDevicePath)(
		IN EFI_GUID *Protocol,
		IN OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath,
		OUT EFI_HANDLE *Device
	);
	EFI_STATUS (*InstallConfigurationTable)(
		IN EFI_GUID *Guid,
		IN VOID *Table
	);
	EFI_STATUS (*LoadImage)(
		IN BOOLEAN BootPolicy,
		IN EFI_HANDLE ParentImageHandle,
		IN EFI_DEVICE_PATH_PROTOCOL *DevicePath,
		IN VOID *SourceBuffer OPTIONAL,
		IN UINTN SourceSize,
		OUT EFI_HANDLE *ImageHandle
	);
	EFI_STATUS (*StartImage)(
		IN EFI_HANDLE ImageHandle,
		OUT UINTN *ExitDataSize,
		OUT CHAR16 **ExitData OPTIONAL
	);
	EFI_STATUS (*Exit)(
		IN EFI_HANDLE ImageHandle,
		IN EFI_STATUS ExitStatus,
		IN UINTN ExitDataSize,
		IN CHAR16 *ExitData OPTIONAL
	);
	EFI_STATUS (*UnloadImage)(
		IN EFI_HANDLE ImageHandle
	);
	EFI_STATUS (*ExitBootService)(
		IN EFI_HANDLE ImageHandle,
		IN UINTN MapKey
	);
	EFI_STATUS (*GetNextMonotonicCount)(
		OUT UINT64 *Count
	);
	EFI_STATUS (*Stall)(
		IN UINTN Microseconds
	);
	EFI_STATUS (*SetWatchdogTimer)(
		IN UINTN Timeout,
		IN UINT64 WatchdogCode,
		IN UINTN DataSize,
		IN CHAR16 *WatchdogData OPTIONAL
	);
	EFI_STATUS (*ConnectController)(
		IN EFI_HANDLE ControllerHandle,
		IN EFI_HANDLE *DriverImageHandle OPTIONAL,
		IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL,
		IN BOOLEAN Recursive
	);
	EFI_STATUS (*DisconnectController)(
		IN EFI_HANDLE ControllerHandle,
		IN EFI_HANDLE DriverImageHandle OPTIONAL,
		IN EFI_HANDLE ChildHandle OPTIONAL
	);
	EFI_STATUS (*OpenProtocol)(
		IN EFI_HANDLE Handle,
		IN EFI_GUID *Protocol,
		OUT VOID **Interface OPTIONAL,
		IN EFI_HANDLE AgentHandle,
		IN EFI_HANDLE ControllerHandle,
		IN UINT32 Attributes
	);
	EFI_STATUS (*CloseProtocol)(
		IN EFI_HANDLE Handle,
		IN EFI_GUID *Protocol,
		IN EFI_HANDLE AgentHandle,
		IN EFI_HANDLE ControllerHandle
	);
	EFI_STATUS (*OpenProtocolInformation)(
		IN EFI_HANDLE Handle,
		IN EFI_GUID *Protocol,
		OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer,
		OUT UINTN *EntryCount
	);
	EFI_STATUS (*ProtocolsPerHandle)(
		IN EFI_HANDLE Handle,
		OUT EFI_GUID ***ProtocolBuffer,
		OUT UINTN *ProtocolBufferCount
	);
	EFI_STATUS (*LocateHandleBuffer)(
		IN EFI_LOCATE_SEARCH_TYPE SearchType,
		IN EFI_GUID *Protocol OPTIONAL,
		IN VOID *SearchKey OPTIONAL,
		OUT UINTN *NoHandles,
		OUT EFI_HANDLE **Buffer
	);
	EFI_STATUS (*LocateProtocol)(
		IN EFI_GUID *Protocol,
		IN VOID *Registration OPTIONAL,
		OUT VOID **Interface
	);
	EFI_STATUS (*InstallMultipleProtocolInterfaces)(
		IN OUT EFI_HANDLE *Handle,
		...
	);
	EFI_STATUS (*UninstallMultipleProtocolInterfaces)(
		IN EFI_HANDLE Handle,
		...
	);
	EFI_STATUS (*CalculateCrc32)(
		IN VOID *Data,
		IN UINTN DataSize,
		OUT UINT32 *Crc32
	);
	VOID (*CopyMem)(
		IN VOID *Destination,
		IN VOID *Source,
		IN UINTN Length
	);
	VOID (*SetMem)(
		IN VOID *Buffer,
		IN UINTN Size,
		IN UINT8 Value
	);
	EFI_STATUS (*CreateEventEx)(
		IN UINT32 Type,
		IN EFI_TPL NotifyTpl,
		IN EFI_EVENT_NOTIFY NotifyFunction OPTIONAL,
		IN CONST VOID *NotifyContext OPTIONAL,
		IN CONST EFI_GUID *EventGroup OPTIONAL,
		OUT EFI_EVENT *Event
	);
};

enum _EFI_ALLOCATE_TYPE
{
	AllocateAnyPages,
	AllocateMaxAddress,
	AllocateAddress,
	MaxAllocateType
};

enum _EFI_MEMORY_TYPE
{
	EfiReservedMemoryType,
	EfiLoaderCode,
	EfiLoaderData,
	EfiBootServicesCode,
	EfiBootServicesData,
	EfiRuntimeServicesCode,
	EfiRuntimeServicesData,
	EfiConvertionalMemory,
	EfiUnusableMemory,
	EfiACPIReclaimMemory,
	EfiACPIMemoryNVS,
	EfiMemoryMappedIO,
	EfiMemoryMappedIOPortSpace,
	EfiPalCode,
	EfiPersistentMemory,
	EfiMaxMemoryType
};

enum _EFI_TIMER_DELAY
{
	TimerCancel,
	TimerPeriodic,
	TimerRelative
};

enum _EFI_INTERFACE_TYPE
{
	EFI_NATIVE_INTERFACE
};

enum _EFI_LOCATE_SEARCH_TYPE
{
	AllHandles,
	ByRegisterNotify,
	ByProtocol
};

struct _EFI_OPEN_PROTOCOL_INFORMATION_ENTRY
{
	EFI_HANDLE AgentHandle;
	EFI_HANDLE ControllerHandle;
	UINT32 Attributes;
	UINT32 OpenCount;
};

struct _EFI_RUNTIME_SERVICES
{
	EFI_STATUS (*GetTime)(
		OUT EFI_TIME *Time,
		OUT EFI_TIME_CAPABILITIES *Capabilities OPTIONAL
	);
	EFI_STATUS (*SetTime)(
		IN EFI_TIME *Time
	);
	EFI_STATUS (*GetWakeupTime)(
		OUT BOOLEAN *Enabled,
		OUT BOOLEAN *Pending,
		OUT EFI_TIME *Time
	);
	EFI_STATUS (*SetWakeupTime)(
		IN BOOLEAN Enable,
		IN EFI_TIME *Time OPTIONAL
	);
	EFI_STATUS (*SetVirtualAddressMap)(
		IN UINTN MemoryMapSize,
		IN UINTN DescriptorSize,
		IN UINT32 DescriptorVersion,
		IN EFI_MEMORY_DESCRIPTOR *VirtualMap
	);
	EFI_STATUS (*ConvertPointer)(
		IN UINTN DebugDisposition,
		IN VOID **Address
	);
	EFI_STATUS (*GetVariable)(
		IN CHAR16 *VariableName,
		IN EFI_GUID *VendorGuid,
		OUT UINT32 *Attributes OPTIONAL,
		IN OUT UINTN *DataSize,
		OUT VOID *Data OPTIONAL
	);
	EFI_STATUS (*GetNextVariableName)(
		IN OUT UINTN *VariableNameSize,
		IN OUT CHAR16 *VariableName,
		IN OUT EFI_GUID *VendorGuid
	);
	EFI_STATUS (*SetVariable)(
		IN CHAR16 *VariableName,
		IN EFI_GUID *VendorGuid,
		IN UINT32 Attributes,
		IN UINT32 DataSize,
		IN VOID *Data
	);
	EFI_STATUS (*GetNextHighMonotonicCount)(
		OUT UINT32 *HighCount
	);
	VOID (*ResetSystem)(
		IN EFI_RESET_TYPE ResetType,
		IN UINTN DataSize,
		IN VOID *ResetData OPTIONAL
	);
	EFI_STATUS (*UpdateCapsule)(
		IN EFI_CAPSULE_HEADER **CapsuleHeaderArray,
		IN UINTN CapsuleCount,
		IN EFI_PHYSICAL_ADDRESS ScatterGatherList OPTIONAL
	);
	EFI_STATUS (*QueryCapsuleCapabilities)(
		IN EFI_CAPSULE_HEADER **CapsuleHeaderArray,
		IN UINTN CapsuleCount,
		OUT UINT64 *MaximumCapsuleSize,
		OUT EFI_RESET_TYPE *ResetType
	);
	EFI_STATUS (*QueryVariableInfo)(
		IN UINT32 Attributes,
		OUT UINT64 *MaximumVariableStorageSize,
		OUT UINT64 *RemainingVariableStorageSize,
		OUT UINT64 *MaximumVariableSize
	);
};

struct _EFI_TIME
{
	UINT16 Year;			// 1990 - 9999
	UINT8 Month;			// 1 - 12
	UINT8 Day;				// 1 - 31
	UINT8 Hour;				// 0 - 23
	UINT8 Minute;			// 0 - 59
	UINT8 Second;			// 0 - 59
	UINT8 Pad1;
	UINT32 Nanosecond;		// 0 - 999,999,999
	INT16 TimeZone;			// -1440 to 1440 or 2047
	UINT8 Daylight;
	UINT8 Pad2;
};

struct _EFI_TIME_CAPABILITIES
{
	UINT32 Resolution;
	UINT32 Accuracy;
	BOOLEAN SetsToZero;
};

enum _EFI_RESET_TYPE
{
	EfiResetCold,
	EfiResetWarm,
	EfiResetShutdown,
	EfiResetPlatformSpecific
};

struct _EFI_CAPSULE_HEADER
{
	EFI_GUID CapsuleGuid;
	UINT32 HeaderSize;
	UINT32 Flags;
	UINT32 CapsuleImageSize;
};

struct _EFI_CONFIGURATION_TABLE
{
	EFI_GUID VendorGuid;
	VOID *VendorTable;
};

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}}

struct _EFI_GRAPHICS_OUTPUT_PROTOCOL
{
	EFI_STATUS (*QueryMode)(
		IN EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
		IN UINT32 ModeNumber,
		OUT UINTN *SizeOfInfo,
		OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info;
	);
	EFI_STATUS (*SetMode)(
		IN EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
		IN UINT32 ModeNumber
	);
	EFI_STATUS (*Blt)(
		IN EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
		IN OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer OPTIONAL,
		IN EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation,
		IN UINTN SourceX,
		IN UINTN SourceY,
		IN UINTN DestinationX,
		IN UINTN DestinationY,
		IN UINTN Width,
		IN UINTN Height,
		IN UINTN Delta OPTIONAL
	);
	EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
};

struct _EFI_PIXEL_BITMASK
{
	UINT32 RedMask;
	UINT32 GreenMask;
	UINT32 BlueMask;
	UINT32 Reserved;
};

enum _EFI_GRAPHICS_PIXEL_FORMAT
{
	PixelRedGreenBlueReserved8BitPerColor,
	PixelBlueGreenRedReserved8BitPerColor,
	PixelBitMask,
	PixelBitOnly,
	PixelFormatMax
};

struct _EFI_GRAPHICS_OUTPUT_MODE_INFORMATION
{
	UINT32 Version;
	UINT32 HorizontalResolution;
	UINT32 VerticalResolution;
	EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
	EFI_PIXEL_BITMASK PixelInformation;
	UINT32 PixelsPerScanLine;
};

struct _EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE
{
	UINT32 MaxMode;
	UINT32 Mode;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
	UINTN SizeOfInfo;
	EFI_PHYSICAL_ADDRESS FrameBufferBase;
	UINTN FrameBufferSize;
};

struct _EFI_GRAPHICS_OUTPUT_BLT_PIXEL
{
	UINT8 Blue;
	UINT8 Green;
	UINT8 Red;
	UINT8 Reserved;
};

enum _EFI_GRAPHICS_OUTPUT_BLT_OPERATION
{
	EfiBltVideoFill,
	EfiBltVideoToBltBuffer,
	EfiBltBufferToVideo,
	EfiBltVideoToVideo,
	EfiGraphicsOutputBltOperationMax
};

struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL
{
	EFI_STATUS (*Reset)(
		IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
		IN BOOLEAN ExtendedVerification;
	);
	EFI_STATUS (*ReadKeyStroke)(
		IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
		OUT EFI_INPUT_KEY *Key
	);
	EFI_EVENT WaitForKey;
};

struct _EFI_INPUT_KEY
{
	UINT16 ScanCode;
	CHAR16 UnicodeChar;
};

struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
{
	EFI_STATUS (*Reset)(
		IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
		IN BOOLEAN ExtendedVerification
	);
	EFI_STATUS (*OutputString)(
		IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
		IN CHAR16 *String
	);
	EFI_STATUS (*TestString)(
		IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
		IN CHAR16 *String
	);
	EFI_STATUS (*QueryMode)(
		IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
		IN UINTN ModeNumber,
		OUT UINTN *Columns,
		OUT UINTN *Rows
	);
	EFI_STATUS (*SetMode)(
		IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
		IN UINTN ModeNumber
	);
	EFI_STATUS (*SetAttribute)(
		IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
		IN UINTN Attribute
	);
	EFI_STATUS (*ClearScreen)(
		IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This
	);
	EFI_STATUS (*SetCursorPosition)(
		IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
		IN UINTN Column,
		IN UINTN Row
	);
	EFI_STATUS (*EnableCursor)(
		IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
		IN BOOLEAN Visible
	);
	SIMPLE_TEXT_OUTPUT_MODE *Mode;
};

struct _SIMPLE_TEXT_OUTPUT_MODE
{
	INT32 MaxMode;
	/* current mode */
	INT32 Mode;
	INT32 Attribute;
	INT32 CursorColumn;
	INT32 CursorRow;
	BOOLEAN CursorVisible;
};

struct _EFI_DEVICE_PATH_PROTOCOL
{
	UINT8 Type;
	UINT8 SubType;
	UINT8 Length[2];
};

#define EFI_LOADED_IMAGE_PROTOCOL_GUID {0x5b1b31a1, 0x9562, 0x11d2, {0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

struct _EFI_LOADED_IMAGE_PROTOCOL
{
	UINT32 Revision;
	EFI_HANDLE ParentHandle;
	EFI_SYSTEM_TABLE *SystemTable;

	EFI_HANDLE DeviceHandle;
	EFI_DEVICE_PATH_PROTOCOL *FilePath;
	VOID *Reserved;

	UINT32 LoadOptionsSize;
	VOID *LoadOptions;

	VOID *ImageBase;
	UINT64 ImageSize;
	EFI_MEMORY_TYPE ImageCodeType;
	EFI_MEMORY_TYPE ImageDataType;
	EFI_STATUS (*Unload)(
		IN EFI_HANDLE ImageHandle
	);
};

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID {0x964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL
{
	UINT64 Revision;
	EFI_STATUS (*OpenVolume)(
		IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This,
		OUT EFI_FILE_PROTOCOL **Root
	);
};

struct _EFI_FILE_PROTOCOL
{
	UINT64 Revision;
	EFI_STATUS (*Open)(
		IN EFI_FILE_PROTOCOL *This,
		OUT EFI_FILE_PROTOCOL **NewHandle,
		IN CHAR16 *FileName,
		IN UINT64 OpenMode,
		IN UINT64 Attributes
	);
	EFI_STATUS (*Close)(
		IN EFI_FILE_PROTOCOL *This
	);
	EFI_STATUS (*Delete)(
		IN EFI_FILE_PROTOCOL *This
	);
	EFI_STATUS (*Read)(
		IN EFI_FILE_PROTOCOL *This,
		IN OUT UINTN *BufferSize,
		OUT VOID *Buffer
	);
	EFI_STATUS (*Write)(
		IN EFI_FILE_PROTOCOL *This,
		IN OUT UINTN *BufferSize,
		IN VOID *Buffer
	);
	EFI_STATUS (*GetPosition)(
		IN EFI_FILE_PROTOCOL *This,
		OUT UINT64 *Position
	);
	EFI_STATUS (*SetPosition)(
		IN EFI_FILE_PROTOCOL *This,
		IN UINT64 Position
	);
	EFI_STATUS (*GetInfo)(
		IN EFI_FILE_PROTOCOL *This,
		IN EFI_GUID *InformationType,
		IN OUT UINTN *BufferSize,
		OUT VOID *Buffer
	);
	EFI_STATUS (*SetInfo)(
		IN EFI_FILE_PROTOCOL *This,
		IN EFI_GUID *InformationType,
		IN UINTN BufferSize,
		IN VOID *Buffer
	);
	EFI_STATUS (*Flush)(
		IN EFI_FILE_PROTOCOL *This
	);
	EFI_STATUS (*OpenEx)(
		IN EFI_FILE_PROTOCOL *This,
		OUT EFI_FILE_PROTOCOL **NewHandle,
		IN CHAR16 *FileName,
		IN UINT64 OpenMode,
		IN UINT64 Attributes,
		IN OUT EFI_FILE_IO_TOKEN *Token
	);
	EFI_STATUS (*ReadEx)(
		IN EFI_FILE_PROTOCOL *This,
		IN OUT EFI_FILE_IO_TOKEN *Token
	);
	EFI_STATUS (*WriteEx)(
		IN EFI_FILE_PROTOCOL *This,
		IN OUT EFI_FILE_IO_TOKEN *Token
	);
	EFI_STATUS (*FlushEx)(
		IN EFI_FILE_PROTOCOL *This,
		IN OUT EFI_FILE_IO_TOKEN *Token
	);
};

struct _EFI_FILE_IO_TOKEN
{
	EFI_EVENT Event;
	EFI_STATUS Status;
	UINTN BufferSize;
	VOID *Buffer;
};

#define EFI_FILE_INFO_ID {0x09576e92, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

struct _EFI_FILE_INFO
{
	UINT64 Size;
	UINT64 FileSize;
	UINT64 PhysicalSize;
	EFI_TIME CreateTime;
	EFI_TIME LastAccessTime;
	EFI_TIME ModificationTime;
	UINT64 Attribute;
	CHAR16 FileName[12+1];
};

#endif

