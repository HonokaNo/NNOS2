#include "arch.h"
#include "uefi.h"

#define NULL (VOID *)0

#define MIN(a, b) (a > b ? b : a)
#define MAX(a, b) (a < b ? b : a)

extern EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;

void setdec(CHAR16 *s, UINT64 i, int aindex);
void sethex(CHAR16 *s, UINT64 i, int aindex);
EFI_STATUS print(CHAR16 *s);
void putpixel(EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP, UINT32 x, UINT32 y, UINT8 r, UINT8 g, UINT8 b);
void fillrect(EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP, UINT32 x, UINT32 y, UINT32 w, UINT32 h, UINT8 r, UINT8 g, UINT8 b);

