/* Link.ld -- Linker script for the kernel - ensure everything goes in the */
/*            Correct place.  */
/*            Original file taken from Bran's Kernel Development */
/*            tutorials: http://www.osdever.net/bkerndev/index.php. */

ENTRY(start)
SECTIONS
{
  .text 0x100000 :
  {
	code = .; _code = .; __code = .;
	*(.text)
	. = ALIGN(4096);
  }

  .data :
  {
	__CTOR_LIST__ = .; LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2) *(.ctors)   LONG(0) __CTOR_END__ = .;
	__DTOR_LIST__ = .; LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2) *(.dtors) LONG(0) __DTOR_END__ = .;
	data = .; _data = .; __data = .;
	*(.data)
	*(.rodata)
	. = ALIGN(4096);
  }

  .bss :
  {
    bss = .; _bss = .; __bss = .;
    *(.bss)
    . = ALIGN(4096);
  }

  end = .; _end = .; __end = .;
}
INPUT(kernel_asm.o kernel.o main.o runtime.o common.o video_textmode.o descriptor_tables.o gdt.o idt.o isr.o kheap.o vbe.o paging.o cpuid.o cpuid_asm.o vfs.o keyboard.o timer.o seashell.o)
OUTPUT(image/system/kernel)
