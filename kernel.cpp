// This is the main C++ kernel file. main is called from the Assembly boilerplate

#include "kernel.h"
#include "video_textmode.h"
#include "common.h"
#include "vbe.h"

video* vid;

void test();

int main(struct multiboot *mboot_ptr)
{
	construct();
	
	vid = new video();
	
	vid->setcolour(0, 2);
	vid->write("Welcome to SoS version 0.1 Alpha 1");
	
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
}

