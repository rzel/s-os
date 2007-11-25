// This is the main C++ kernel file. main is called from the Assembly boilerplate

#include "kernel.h"
#include "video_textmode.h"
#include "common.h"
#include "vbe.h"
#include "gdt.h"

video* vid;
gdt* gdt_i;

void test();
void init();

int main(struct multiboot *mboot_ptr)
{
	construct();
	
	init(); // Initiate SoS
	
	
	vid->setcolour(0, 2);
	vid->write("\nSoS version 0.1 Alpha 1 - Revision 20");
	
	vid->setcolour(0, 7);
	
	test();
	
	vid->write("\n\nShutting Down...");

	destruct();
	__cxa_finalize(0);
	
	// Just to test if we exit properley
	return 0xDEADBEEF;
}

void test()
{
	vid->write("\n\nTesting global objects!");
	
	vid->write("\nVideo object located at: ");
	vid->puthex((u32int)&vid);
	
	vid->write("\nGDT object located at: ");
	vid->puthex((u32int)&gdt_i);
	
}

void init()
{
	vid = new video();
	
	vid->setcolour(0, 14);
	vid->write("Starting SoS...\n");
	vid->setcolour(0, 7);
	
	gdt_i = new gdt();
}
