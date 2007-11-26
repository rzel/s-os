#ifndef IDT_H
#define IDT_H

#include "common.h"
#include "isr.h"

extern "C" { void idt_flush(u32int); };

// A struct describing an interrupt gate.
struct idt_entry_struct
{
	u16int base_lo;		// The lower 16 bits of the address to jump to when this interrupt fires.
	u16int sel;			// Kernel segment selector.
	u8int  always0;		// This must always be zero.
	u8int  flags;			// More flags. See documentation.
	u16int base_hi;		// The upper 16 bits of the address to jump to.
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct
{
	u16int limit;
	u32int base;			// The address of the first element in our idt_entry_t array.
} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

typedef void (*isr_t)(registers_t);

class idt
{
protected:
	void remap_pic();
	void set_gate(u8int num, u32int base, u16int sel, u8int flags);
	idt_entry_t idt_entries[256];
	idt_ptr_t   idt_ptr;
	
public:
	idt();
	~idt();
	void register_irq_handler(u8int n, isr_t handler);
};

extern "C"
{
	void isr0 ();
	void isr1 ();
	void isr2 ();
	void isr3 ();
	void isr4 ();
	void isr5 ();
	void isr6 ();
	void isr7 ();
	void isr8 ();
	void isr9 ();
	void isr10();
	void isr11();
	void isr12();
	void isr13();
	void isr14();
	void isr15();
	void isr16();
	void isr17();
	void isr18();
	void isr19();
	void isr20();
	void isr21();
	void isr22();
	void isr23();
	void isr24();
	void isr25();
	void isr26();
	void isr27();
	void isr28();
	void isr29();
	void isr30();
	void isr31();
	
	void irq0 ();
	void irq1 ();
	void irq2 ();
	void irq3 ();
	void irq4 ();
	void irq5 ();
	void irq6 ();
	void irq7 ();
	void irq8 ();
	void irq9 ();
	void irq10();
	void irq11();
	void irq12();
	void irq13();
	void irq14();
	void irq15();
};

#endif
