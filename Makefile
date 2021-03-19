ENTRY_POINT = loader_main

kernel.bin: kernel.o
#	ld.lld -e kernel_main -z norelro --image-base 0x100000 --static -o $@ $<
	ld -e kernel_main -z norelro -T linker.ld -o $@ $<

BOOTX64.EFI: loader.c lib.c
	x86_64-w64-mingw32-gcc -Wall -Wextra -nostdinc -nostdlib -fno-builtin -Wl,--subsystem,10 -e $(ENTRY_POINT) -o $@ $+

%.o: %.c
	gcc -Wall -Wextra -nostdinc -nostdlib -fno-builtin -c -o $*.o $*.c

img: BOOTX64.EFI kernel.bin
	cp $< fs/EFI/BOOT/$<
	dd if=/dev/zero of=fat.img bs=1k count=1440
	mformat -i fat.img -f 1440 ::
	mcopy -i fat.img kernel.bin ::/
	mmd -i fat.img ::/EFI
	mmd -i fat.img ::/EFI/BOOT
	mcopy -i fat.img $< ::/EFI/BOOT

run: img
	qemu-system-x86_64 -m 4G -bios OVMF.fd -hda fat.img

clean:
	rm -f BOOTX64.EFI
	rm -f fs/EFI/BOOT/BOOTX64.EFI
	rm -f fat.img
	rm -f kernel.bin
	rm -f *.o

