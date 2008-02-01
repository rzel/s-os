#include "include/kernel.h"

int main(struct multiboot *mboot_ptr);
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
