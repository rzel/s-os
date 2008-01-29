// This is the main C++ kernel file. main is called from the Assembly boilerplate

#include "include/kernel.h"

using namespace std;

video * vid;
kernel * kernel_i;

void test();

int main(struct multiboot *mboot_ptr)
{
	construct();
	
	kernel_i = new kernel();		// Start up the kernel
	kernel_i->calculate_memory(mboot_ptr);
	
	vid->setcolour(0, 2);
	vid->write("\nSoS version 0.1 Alpha 1 - Revision 24");
	vid->setcolour(0, 7);
	
	test();

	delete kernel_i;	// Delete the instance of the kernel
	
	// Just to test if we exit properley
	return 0xDEADBEEF;
}

void test()
{
	vid->write("\n\nKernel object located at: ");
	vid->puthex((u32int)&kernel_i);
	
	vid->write("\nVideo object located at: ");
	vid->puthex((u32int)&vid);
}

kernel::kernel()
{
	vid = new video();
	
	vid->setcolour(0, 14);
	vid->write("Starting SoS...\n");
	vid->setcolour(0, 7);
	
	init();
}

kernel::~kernel()
{
	vid->write("\n\nShutting Down...\n");
	
	terminate();
}

void kernel::init()
{	
	long_mode();
	
	//gdi_i = new gdt();	// The GDT describes 64 bit segments, so the computer will crash if we
					// try to call it before jumping to long mode.
					
	paging_i = new paging();
}

void kernel::long_mode()
{
	vid->write("Jumping to Long Mode");
	
	vid->setcolour(0, 4);
	vid->write("\t\t[FAIL]\n");
	
	vid->write("FIXME: Jump to long mode here\n");
	
	vid->setcolour(0, 7);
	
}

void kernel::terminate()
{	
	delete paging_i;
	
	destruct();
	__cxa_finalize(0);
}

void kernel::calculate_memory(struct multiboot * mboot_ptr)
{
	u32int upper = mboot_ptr->mem_upper;
	u32int lower = mboot_ptr->mem_lower;
	
	vid->write("Calculating Memory\t\t");
	
	total_memory = upper + lower;
	
	vid->setcolour(0, 2);
	
	vid->putint((u32int) total_memory / 1024);
	
	vid->write("MB Detected\n");
	vid->setcolour(0, 7);
}


