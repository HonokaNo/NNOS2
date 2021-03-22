void kernel_main(unsigned int width, unsigned int height, char *buffer)
{
	unsigned int i, j;

	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
			buffer[0] = 0xff;
			buffer[1] = 0xff;
			buffer[2] = 0xff;
			buffer[3] = 0xff;

			buffer += 4;
		}
	}

	while(1) __asm__("hlt");
}

