#include "lib.h"

EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;

// s:buffer
// i:integer
// aindex:buffer length 文字数 + 1
void setdec(CHAR16 *s, UINT64 i, int aindex)
{
	int j;
	for(j = aindex - 2; j >= 0; j--){
		s[j] = L'0' + i % 10;
		i /= 10;
	}
	s[aindex - 1] = 0;
	return;
}

void sethex(CHAR16 *s, UINT64 i, int aindex)
{
	int j;
	CHAR16 *l = L"0123456789abcdef";

	for(j = aindex - 2; j >= 0; j--){
		s[j] = l[i % 16];
		i /= 16;
	}
	s[aindex - 1] = 0;
	return;
}

EFI_STATUS print(CHAR16 *s)
{
	EFI_STATUS Status;

	Status = ConOut->OutputString(ConOut, s);
	return Status;
}

void putpixel(EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP, UINT32 x, UINT32 y, UINT8 r, UINT8 g, UINT8 b)
{
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)GOP->Mode->FrameBufferBase;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *p = base + (GOP->Mode->Info->HorizontalResolution * y) + x;

	p->Blue = b;
	p->Green = g;
	p->Red = r;
	p->Reserved = 0x00;
}

void fillrect(EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP, UINT32 x, UINT32 y, UINT32 w, UINT32 h, UINT8 r, UINT8 g, UINT8 b)
{
	UINTN i, j;

	for(i = y; i < h; i++){
		for(j = x; j < w; j++){
			putpixel(GOP, j, i, r, g, b);
		}
	}
}

