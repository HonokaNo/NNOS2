struct pixel
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char reserved;
};

void kernel_main(unsigned long long buffer, unsigned long long size)
{
	unsigned char *vram = (unsigned char *)buffer;
//	unsigned int i;

	vram[0] = 0xff;

//	for(i = 0; i < size; i++){
//		vram[i] = 0xff;
//	}

	while(1) __asm__("hlt");
}

