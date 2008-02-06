#include "include/paging.h"
#include "include/kheap.h"
#include "include/video_textmode.h"

extern u32int placement_address;
extern "C" { u32int get_cr2(); };

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
	/*for(int i = 0; i < INDEX_FROM_BIT(nframes); i++)
	{
		frames[i] = NULL;
	}*/
	
	//register_irq(14, page_fault);
	
	vid->write("\t\t\t[Incomplete]\n", 4);
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
	for (u32int i = 0; i < INDEX_FROM_BIT(nframes); i++)
	{
		if (frames[i] != 0xFFFFFFFF) // nothing free, exit early.
		{
			// at least one bit is free here.
			for (int j = 0; j < 32; j++)
			{
				u32int toTest = 0x1 << j;
				
				if ( !(frames[i]&toTest) )
				{
					return i*4*8+j;
				}
			}
		}
	}
	
	return NULL;
}

void paging::alloc_frame(page_t * page, bool is_kernel, bool is_writeable)
{
	if(page->frame != 0)
	{
		return; // This frame has already been allocated!
	}
	
	u32int index = first_frame();
	
	if(index == (u32int)-1)	// Is that possible?
	{
		panic("Your computer is completly out of memory and cannot continue.");
	}
	
	set_frame(index * 0x1000);	// Set the frame's address
	
	page->present = 1;
	
	page->rw = (int)is_writeable;	// Is the page read only?
	page->user = (int)!is_kernel;	// Does this belong to the kernel or a user?
	
	page->frame = index;		// Set the index and we're done!
	
}

void paging::free_frame(page_t * page)
{
	if(page->frame == 0x0)
	{
		// If that frame is not allocated, we won't try to clear it
		return;
	}
	else
	{
		clear_frame(page->frame);
		page->frame = 0x0;
	}
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
	u32int fault_address = get_cr2();
	
	// Print some info to say what happenned
	vid->write("\nPage Fault (", 4);
	
	if((regs.err_code & 0x1) == 0)	vid->write("Page not Present", 4);
	if(regs.err_code & 0x2 == 1)		vid->write("Write Operation", 4);
	if(regs.err_code & 0x4 == 1)		vid->write("Processor was in User Mode", 4);
	if(regs.err_code & 0x8 == 1)		vid->write("Overwritten Reserved Page Bits", 4);
	
	vid->write(") at ", 4);
	vid->puthex(fault_address, 4);
	
	panic("System Halted");
	
}

