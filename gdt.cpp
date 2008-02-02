#include "include/gdt.h"
#include "include/video_textmode.h"

gdt::gdt()
{
	vid->write("Setting up GDT");
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_ptr.base  = (u32int)&gdt_entries;
	
	set_gate(0, 0, 0, 0, 0);				// Null segment
	set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);	// Code segment
	set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);	// Data segment
	set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);	// User mode code segment
	set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);	// User mode data segment
	
	gdt_flush((u32int)&gdt_ptr);
	
	vid->write("\t\t\t\t[OK]\n", 2);
}

void gdt::set_gate(s32int num, u32int base, u32int limit, u8int access, u8int gran)
{	
	gdt_entries[num].base_low    = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high   = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low   = (limit & 0xFFFF);
	
	#ifdef PLATFORM_x86_64
	// This following describes the segment as 64-bit
	gdt_entries[num].granularity = (limit >> 16) & 0x2F;
	#endif
	
	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access      = access;
}

gdt::~gdt()
{

}
