ENTRY_POINT = loader_main

img: BOOTX64.EFI kernel.bin Makefile
	cp $< fs/EFI/BOOT/$<
	dd if=/dev/zero of=fat.img bs=1k count=1440
	mformat -i fat.img -f 1440 ::
	mcopy -i fat.img kernel.bin ::/
	mmd -i fat.img ::/EFI
	mmd -i fat.img ::/EFI/BOOT
	mcopy -i fat.img $< ::/EFI/BOOT

BOOTX64.EFI: loader.c lib.c
	x86_64-w64-mingw32-gcc -Wall -Wextra -nostdlib -nostdinc -ffreestanding -mno-red-zone -Wl,--subsystem,10 -m64 -shared -Wl,-Bsymbolic -mabi=ms -mgeneral-regs-only -fpic -fno-stack-protector -e $(ENTRY_POINT) -o $@ $+

kernel.bin: kernel.o Makefile
	ld.lld -e kernel_main -z norelro --image-base 0x100000 --static -o $@ $<

%.o: %.c Makefile
	gcc -Wall -Wextra -nostdlib -nostdinc -ffreestanding -mno-red-zone -Wl,--subsystem,10 -m64 -shared -Wl,-Bsymbolic -mabi=ms -mgeneral-regs-only -fpic -fno-stack-protector -c -o $*.o $*.c

run: img
	qemu-system-x86_64 -m 4G -bios OVMF.fd -hda fat.img -monitor stdio

clean:
	rm -f BOOTX64.EFI
	rm -f fs/EFI/BOOT/BOOTX64.EFI
	rm -f fat.img
	rm -f kernel.bin
	rm -f *.o

kernellist: kernel.c
	gcc -Wall -Wextra -nostdinc -nostdlib -fno-builtin -S -o kernel.s kernel.c
	as -al kernel.s

