#include "./lib/header/stdint.h"

struct pixel
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char reserved;
};

void kernel_main(uint64_t vadr)
{
	struct pixel *pixels = (struct pixel *)vadr;

//	while(1);

	pixels[0].red = 0xff;

	while(1) __asm__("hlt");
}

