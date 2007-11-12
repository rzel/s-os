#include "kernel.h"

int main(struct multiboot *mboot_ptr)
{
	video vid;
	
	vid.write("Welcome to SoS version 0.0.1");
	
	// Just to test if this works
	return 0xDEADBEEF;
}
