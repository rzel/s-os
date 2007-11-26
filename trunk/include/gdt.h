#ifndef GDT_H
#define GDT_H

#include "common.h"

extern "C" { void gdt_flush(u32int pointer); };

// Our GDT Entry Structure
struct gdt_entry_struct
{
	u16int limit_low;           // The lower 16 bits of the limit.
	u16int base_low;            // The lower 16 bits of the base.
	u8int  base_middle;         // The next 8 bits of the base.
	u8int  access;              // Access flags, determine what ring this segment can be used in.
	u8int  granularity;
	u8int  base_high;           // The last 8 bits of the base.
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;


// The pointer to the GDT structure
struct gdt_ptr_struct
{
	u16int limit;               // The upper 16 bits of all selector limits.
	u32int base;                // The address of the first gdt_entry_t struct.
}
 __attribute__((packed));
 
typedef struct gdt_ptr_struct gdt_ptr_t;


class gdt {

private:
	void 		set_gate(s32int num, u32int base, u32int limit, u8int access, u8int gran);
	gdt_entry_t	gdt_entries[5];
	gdt_ptr_t		gdt_ptr;

public:
	gdt();	// The Constructor loads the GDT
	~gdt();
};

#endif
