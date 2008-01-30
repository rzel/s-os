#ifndef HEAP_H
#define HEAP_H

#include "common.h"

u32int kmalloc(u32int sz, u32int * phys, bool align = false);
u32int kmalloc(u32int sz, bool align = false);

#endif
