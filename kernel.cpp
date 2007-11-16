#include "kernel.h"

int main(struct multiboot *mboot_ptr)
{
	video vid;
	vid.write("Welcome to SoS version 0.0.1");
	
	
	//__cxa_finalize(0); - This will be required once globals are supported
	
	// Just to test if this works
	return 0xDEADBEEF;
}
