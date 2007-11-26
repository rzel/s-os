#include "include/heap.h"

extern u32int end;
u32int placement_address = (u32int)&end;

u32int kmalloc(u32int sz)
{
	u32int tmp = placement_address;
	placement_address += sz;
	return tmp;
}
