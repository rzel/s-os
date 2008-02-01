// This is the kernel object

#include "include/kernel.h"

using namespace std;

kernel * kernel_i;

kernel::kernel()
{
	vid = new video();
	
	vid->write("Starting SoS...\n\n", 14);
	
	init();
}

kernel::~kernel()
{
	vid->write("\nShutting Down...\n", 14);
	
	terminate();
}

void kernel::init()
{	
	#ifdef PLATFORM_x86_64
		enable_long_mode();
	#endif
	
	gdt_i = new gdt();
	idt_i = new idt();
					
	paging_i = new paging();
}

#ifdef PLATFORM_x86_64
void kernel::enable_long_mode()
{
	// This function will only be called if the platform is defined as
	// X86_64 in common.h.
	vid->write("Jumping to Long Mode");
	
	// First we check the CPUID information to see if the processor can
	// support 64 bit code
	if(!cpuid_check_flag(CPUID_FLAG_IA64))
	{
		vid->write("\t\t\t[FAIL]\n\n", 4);
		
		panic("This processor does not support 64 bit long mode,\nand is unable to run this version of SoS.\n\nFor more information, please cousult the user manual", 4);
		
		halt();
	}
	
	vid->write("\t\t\t[OK]\n", 2);
	
	fixme("Jump to Long mode here");	
}
#endif

void kernel::terminate()
{	
	delete paging_i;
	delete gdt_i;
	delete idt_i;
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
	
	vid->putint((u32int) total_memory / 1024, 2);
	
	vid->write("MB detected\n", 2);
}


