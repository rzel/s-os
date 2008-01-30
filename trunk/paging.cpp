#include "include/paging.h"
#include "include/video_textmode.h"

extern video * vid;

// This doesn't do anything yet, just a skeleton as of now...

paging::paging()
{
	vid->write("Setting up Paging");
	
	// Init Paging here
	
	vid->setcolour(0,2);
	vid->write("\t\t\t[OK]\n");
	vid->setcolour(0,7);
}

paging::~paging()
{
	
}

void paging::switch_page_directory(page_directory_t *new_directory)
{

}
	

page_t *get_page(u32int address, bool make, page_directory_t *dir)
{
	page_t * tmp;
	return tmp;
}
	
void page_fault(registers_t regs)
{

}

