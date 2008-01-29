#include "include/paging.h"
#include "include/video_textmode.h"

extern video * vid;

// This is just a skeleton class for paging

paging::paging()
{
	vid->write("Setting up Paging");
	
	// Init Paging here
	
	vid->setcolour(0,2);
	vid->write("\t\t[OK]\n");
	vid->setcolour(0,7);
}

paging::~paging()
{
	
}
