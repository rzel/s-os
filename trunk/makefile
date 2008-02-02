# A Quick and dirty makefile. This builds the OS and then makes a bootable CD image

all:
	g++ -c *.cpp -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-stack-protector -W -Wall
	nasm -f elf kernel.asm -o kernel_asm.o
	nasm -f elf cpuid.asm -o cpuid_asm.o
	nasm -f elf isr.asm -o isr.o
	nasm -f elf descriptor_tables.asm -o descriptor_tables.o
	ld -T link.ld
	rm *.o

clean:
	rm *.o
	
install:
	#cp /usr/lib/grub/i386-pc/stage2_eltorito image/boot/grub
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o sos.iso image
