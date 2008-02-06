#ifndef KERNEL_H
#define KERNEL_H

#define SYSTEM_VERSION "0.1 - SVN Revision 35"

#include "video_textmode.h"
#include "common.h"
#include "vbe.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "paging.h"
#include "multiboot.h"
#include "cpuid.h"
#include "keyboard.h"
#include "seashell.h"

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
	
	#ifdef PLATFORM_x86_64
	void enable_long_mode();
	#endif
	
	// Instances of our GDT, IDT and paging objects
	gdt * gdt_i;
	idt * idt_i;
	paging * paging_i;
	
	// Variables
	u32int total_memory;

public:
	kernel();		// The constructor calls the init function
	~kernel();
	
	void calculate_memory(struct multiboot * mboot_ptr);
	
	void restart();
};

extern kernel * kernel_i;

#endif
