#ifndef KERNEL_H
#define KERNEL_H

#define SYSTEM_VERSION "0.1 - SVN Revision 29"

#include "video_textmode.h"
#include "common.h"
#include "vbe.h"
#include "gdt.h"
#include "paging.h"
#include "multiboot.h"
#include "cpuid.h"

extern "C"
{
	int __cxa_atexit(void (*f)(void *), void *p, void *d);
	void __cxa_finalize(void *d);
};

void construct();
void destruct();

class kernel {
protected:
	void init();
	void terminate();
	void enable_long_mode();
	
	// Instances of our GDT and paging objects
	paging * paging_i;
	gdt * gdi_i;
	
	// Variables
	u32int total_memory;

public:
	kernel();		// The constructor calls the init function
	~kernel();
	
	void calculate_memory(struct multiboot * mboot_ptr);
};

extern kernel * kernel_i;

#endif
