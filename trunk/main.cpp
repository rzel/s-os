#include "include/kernel.h"

int main(struct multiboot *mboot_ptr);
void test();

int main(struct multiboot *mboot_ptr)
{
	construct();
	
	kernel_i = new kernel();		// Start up the kernel
	kernel_i->calculate_memory(mboot_ptr);
	
	vid->write("\nSoS Version ", 2);
	vid->write(SYSTEM_VERSION, 2);
	
	test();
	
	for(; ;);

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
	vid->write(get_cpu_vendor(), 2);
	
	vid->write("\n\nTesting the timer: ");
	
	for(int i = 0; i < 3; i++)
	{
		timer_i->delay(1);
		vid->write("* ", 14);
	}
	
	vid->write("\n\nYou can test the (very basic) keyboard driver by typing something here.\n\n");
	vid->write("You can restart by pressing ");
	//vid->write("Ctrl+Alt+Delete", 14);
	vid->write("Escape", 14);
	vid->write(".\n");
	
	vid->write("SoS", 2);
	vid->write(">");
}

