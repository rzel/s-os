#include "include/paging.h"
#include "include/kheap.h"
#include "include/video_textmode.h"

extern u32int placement_address;

// Macros used in the bitset algorithms.
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

paging::paging()
{
	vid->write("Setting up Paging");
	
	// The size of the physical memory
	// This is 16MB for now
	u32int mem_end_page = 0x1000000;
	
	// Work out the number of frames available in that space
	nframes = mem_end_page / 0x1000;
	
	// Allocate a block of memory for those frames
	frames = (u32int*)kmalloc(INDEX_FROM_BIT(nframes));
	
	// Clear the memory
	//memset(frames, NULL, INDEX_FROM_BIT(nframes));
	
	vid->setcolour(0,2);
	vid->write("\t\t\t[OK]\n");
	vid->setcolour(0,7);
}

paging::~paging()
{
	
}

// Private Functions
void paging::set_frame(u32int frame_address)
{
	u32int frame = frame_address / 0x1000;
	u32int index = INDEX_FROM_BIT(frame);
	u32int offset = OFFSET_FROM_BIT(frame);
	frames[index] |= (0x1 << offset);
}

void paging::clear_frame(u32int frame_address)
{
	u32int frame = frame_address / 0x1000;
	u32int index = INDEX_FROM_BIT(frame);
	u32int offset = OFFSET_FROM_BIT(frame);
	frames[index] &= ~(0x1 << offset);
}

// Check if bit is set
u32int paging::test_frame(u32int frame_address)
{
   	u32int frame = frame_address / 0x1000;
	u32int index = INDEX_FROM_BIT(frame);
	u32int offset = OFFSET_FROM_BIT(frame);
	
	return (frames[index] & (0x1 << offset));
}

u32int paging::first_frame()
{
	fixme("stub: first_frame not implemented");
	
	return 1;
}

void paging::alloc_frame(page_t * page, bool is_kernel, bool is_writeable)
{
	fixme("stub: alloc_frame not implemented");
}

void paging::free_frame(page_t * page)
{
	fixme("stub: free_frame not implemented");
}

// Public Functions

void paging::switch_page_directory(page_directory_t *new_directory)
{
	fixme("stub: switch_page_directory not implemented");
}
	

page_t *get_page(u32int address, bool make, page_directory_t *dir)
{
	fixme("stub: get_page not implemented");
	
	page_t * tmp;  // FIXME: This is just so it will compile
	return tmp;
}
	
void page_fault(registers_t regs)
{
	fixme("stub: page fault handler not implemented");
}

