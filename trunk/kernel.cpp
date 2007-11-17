// This is the main C++ kernel file. main is called from the Assembly boilerplate

#include "kernel.h"
#include "video_textmode.h"
#include "common.h"
#include "vbe.h"

int main(struct multiboot *mboot_ptr)
{
	video vid;
	
	vid.write("Welcome to SoS version 0.0.1\n\nThis is a test of newlines");
	
	//__cxa_finalize(0); - This will be required once globals are supported
	
	// Just to test if this works
	return 0xDEADBEEF;
}
