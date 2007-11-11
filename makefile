# A Quick and dirty makefile. This builds the OS and then makes a bootable CD image

all:
	g++ -c *.cpp -nostdlib -fno-builtin -fno-rtti -fno-exceptions
	g++ -c video/*.cpp  -nostdlib -fno-builtin -fno-rtti -fno-exceptions
	nasm -f elf kernel.asm -o kernel_asm.o
	ld -T link.ld
	rm *.o
	cp /usr/lib/grub/i386-pc/stage2_eltorito iso/boot/grub
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o sos.iso iso
	
