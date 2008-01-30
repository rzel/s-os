#ifndef PAGING_H
#define PAGING_H

#include "common.h"
#include "isr.h"

typedef struct page
{
	u32int present		: 1;   // Page present in memory
	u32int rw			: 1;   // Read-only if clear, readwrite if set
	u32int user		: 1;   // Supervisor level only if clear
	u32int accessed	: 1;   // Has the page been accessed since last refresh?
	u32int dirty		: 1;   // Has the page been written to since last refresh?
	u32int unused		: 7;   // Amalgamation of unused and reserved bits
	u32int frame		: 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
	page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
	// An array of pointers to our page tables
	page_table_t *tables[1024];
	
	/**
		Array of pointers to the page tables above, but gives their *physical*
		location, for loading into the CR3 register.
	**/
	u32int tablesPhysical[1024];
	
	/**
		The physical address of tablesPhysical. This comes into play
		when we get our kernel heap allocated and the directory
		may be in a different location in virtual memory.
	**/
	u32int physicalAddr;
} page_directory_t;

class paging 
{

public:
	paging();
	~paging();
	
	// Load the specified page directory into the CR3 register
	void switch_page_directory(page_directory_t *new_directory);
	
	// Find a page in a page directory
	page_t *get_page(u32int address, bool make, page_directory_t *dir);
	
	// Fault handler for the page fault exception
	void page_fault(registers_t regs);
};

#endif
