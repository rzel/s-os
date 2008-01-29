#ifndef KERNEL_H
#define KERNEL_H

#include "video_textmode.h"
#include "common.h"
#include "vbe.h"
#include "paging.h"
#include "gdt.h"

int main(struct multiboot *mboot_ptr);

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
	void long_mode();
	
	// Instances of our IDT and GDT objects
	gdt * gdi_i;

public:
	kernel();		// The constructor calls the init function
	~kernel();
};

#endif
