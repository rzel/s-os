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
	vid->write("\nSoS Version ");
	vid->write(SYSTEM_VERSION);
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
	vid->write("\n");
	
	vid->write("\nProcessor vendor string: ");
	vid->write(get_cpu_vendor());
	
	vid->write("\n");
}

kernel::kernel()
{
	vid = new video();
	
	vid->setcolour(0, 14);
	vid->write("Starting SoS...\n\n");
	vid->setcolour(0, 7);
	
	init();
}

kernel::~kernel()
{
	vid->write("\nShutting Down...\n");
	
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
	
	// First we check the CPUID information to see if the processor can
	// support 64 bit code
	if(!cpuid_check_flag(CPUID_FLAG_IA64))
	{
		vid->setcolour(0, 4);
		vid->write("\t\t\t[FAIL]\n");
		
		vid->write("\nFatal Error:\n");
		
		vid->setcolour(0, 7);
		
		vid->write("This processor does not support 64 bit long mode,\nand is unable to run SoS.\n\n");
		
		vid->write("Sorry for any inconvienence");
		
		halt();
	}
	
	vid->setcolour(0, 2);
	vid->write("\t\t\t[OK]\n");
	
	fixme("Jump to Long mode here");
	
	vid->setcolour(0, 7);
	
}

void kernel::terminate()
{	
	delete paging_i;
	//delete gdt_i;
	delete vid;
	
	destruct();
	__cxa_finalize(0);
}

void kernel::calculate_memory(struct multiboot * mboot_ptr)
{
	u32int upper = mboot_ptr->mem_upper;
	u32int lower = mboot_ptr->mem_lower;
	
	vid->write("Calculating Memory\t\t\t");
	
	total_memory = upper + lower;
	
	vid->setcolour(0, 2);
	
	vid->putint((u32int) total_memory / 1024);
	
	vid->write("MB detected\n");
	vid->setcolour(0, 7);
}


