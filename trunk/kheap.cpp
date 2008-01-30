#include "include/kheap.h"

u32int kmalloc_internal(u32int sz, bool align, u32int * phys);

extern u32int end;
u32int placement_address = (u32int)&end;

// This is just a dead-simple memory allocator so I can make global objects.
// As of now, the memory can't be freed. It can do page allignment, and 
// optionally output a physical address

// I plan to implement better heap management once I have enabled paging.

u32int kmalloc_internal(u32int sz, bool align, u32int * phys)
{	
	// We check if we want to page-allign the memory, and whether it
	// is already page aligned
	
	if(align && (placement_address & 0xFFFFF000) )
	{
		// If it's not aligned...
		placement_address &= 0xFFFFF000;
		placement_address += 0x1000;
	}
	
	if(phys != NULL)
	{
		*phys = placement_address;
	}
	
	u32int tmp = placement_address;
	
	placement_address += sz;
	
	return tmp;
}

u32int kmalloc(u32int sz, u32int * phys, bool align)
{
	return kmalloc_internal(sz, align, phys);
}

u32int kmalloc(u32int sz, bool align)
{
	/*u32int tmp = placement_address;
	placement_address += sz;
	return tmp;*/
	
	return kmalloc_internal(sz, align, NULL);
}
