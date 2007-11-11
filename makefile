all:
	g++ -c *.cpp -nostdlib -fno-builtin -fno-rtti -fno-exceptions
	g++ -c video/*.cpp  -nostdlib -fno-builtin -fno-rtti -fno-exceptions
	nasm -f elf kernel.asm -o kernel_asm.o
	ld -T link.ld
	rm *.o
