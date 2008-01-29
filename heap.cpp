#include "include/heap.h"

extern u32int end;
u32int placement_address = (u32int)&end;

// This is just a dead-simple memory allocator so I can make global objects.
// As of now, the memory can't be freed

// I plan to implement real heap management once I have enabled paging.

u32int kmalloc(u32int sz)
{
	u32int tmp = placement_address;
	placement_address += sz;
	return tmp;
}
