// This is the main C++ kernel file. main is called from the Assembly boilerplate

#include "include/kernel.h"
#include "include/video_textmode.h"
#include "include/common.h"
#include "include/vbe.h"
#include "include/gdt.h"
#include "include/idt.h"

video * vid;
gdt * gdt_i;
idt * idt_i;

void test();
void init();
void kb_test(registers_t regs);

int main(struct multiboot *mboot_ptr)
{
	construct();
	
	init(); // Initiate SoS
	
	
	vid->setcolour(0, 2);
	vid->write("\nSoS version 0.1 Alpha 1 - Revision 20");
	
	vid->setcolour(0, 7);
	
	test();

	idt_i->register_irq_handler(1, kb_test);
	
	while(1)
	{
		// wait
	}
	
	vid->write("\n\nShutting Down...");

	destruct();
	__cxa_finalize(0);
	
	// Just to test if we exit properley
	return 0xDEADBEEF;
}

void test()
{
	vid->write("\n\nVideo object located at: ");
	vid->puthex((u32int)&vid);
	
	//vid->write("\nGDT object located at: ");
	//vid->puthex((u32int)&gdt_i);
	
	vid->write("\nIDT object located at: ");
	vid->puthex((u32int)&idt_i);
	
}

void init()
{
	vid = new video();
	
	vid->setcolour(0, 14);
	vid->write("Starting SoS...\n");
	vid->setcolour(0, 7);
	
	gdt_i = new gdt();
	
	idt_i = new idt();
}

void kb_test(registers_t regs)
{
	vid->write("*");
}


