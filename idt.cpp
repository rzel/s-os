#include "include/common.h"
#include "include/idt.h"
#include "include/isr.h"
#include "include/video_textmode.h"

extern "C" { 
	void idt_flush(u32int pointer); 
	void isr_handler(registers_t r);
	void irq_handler(registers_t r);
};

const s8int *exceptionMessages[] =
{
  "Division By Zero Exception",
  "Debug Exception",
  "Non Maskable Interrupt Exception",
  "Breakpoint Exception",
  "Into Detected Overflow Exception",
  "Out of Bounds Exception",
  "Invalid Opcode Exception",
  "No Coprocessor Exception",
  "Double Fault Exception",
  "Coprocessor Segment Overrun Exception",
  "Bad TSS Exception",
  "Segment Not Present Exception",
  "Stack Fault Exception",
  "General Protection Fault Exception",
  "Page Fault Exception",
  "Unknown Interrupt Exception",
  "Coprocessor Fault Exception",
  "Alignment Check Exception (486+)",
  "Machine Check Exception (Pentium/586+)",
  "Reserved"
};

isr_t interrupt_handlers[256];

idt::idt()
{
	vid->write("Setting up IDT");
	
	idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
	idt_ptr.base  = (u32int)&idt_entries;

	//memset((u32int *)&idt_entries, NULL, sizeof(idt_entry_t)*256);
	for (int i = 0; i < 256; i++)
	{
		idt_entries[i].base_lo = idt_entries[i].base_hi = idt_entries[i].sel = 0;
		idt_entries[i].always0 = idt_entries[i].flags = 0;
	}
	
	remap_pic();
	
	// Set gates for service routines
	set_gate( 0, (u32int)isr0 , 0x08, 0x8E);
	set_gate( 1, (u32int)isr1 , 0x08, 0x8E);
	set_gate( 2, (u32int)isr2 , 0x08, 0x8E);
	set_gate( 3, (u32int)isr3 , 0x08, 0x8E);
	set_gate( 4, (u32int)isr4 , 0x08, 0x8E);
	set_gate( 5, (u32int)isr5 , 0x08, 0x8E);
	set_gate( 6, (u32int)isr6 , 0x08, 0x8E);
	set_gate( 7, (u32int)isr7 , 0x08, 0x8E);
	set_gate( 8, (u32int)isr8 , 0x08, 0x8E);
	set_gate( 9, (u32int)isr9 , 0x08, 0x8E);
	set_gate(10, (u32int)isr10, 0x08, 0x8E);
	set_gate(11, (u32int)isr11, 0x08, 0x8E);
	set_gate(12, (u32int)isr12, 0x08, 0x8E);
	set_gate(13, (u32int)isr13, 0x08, 0x8E);
	set_gate(14, (u32int)isr14, 0x08, 0x8E);
	set_gate(15, (u32int)isr15, 0x08, 0x8E);
	set_gate(16, (u32int)isr16, 0x08, 0x8E);
	set_gate(17, (u32int)isr17, 0x08, 0x8E);
	set_gate(18, (u32int)isr18, 0x08, 0x8E);
	set_gate(19, (u32int)isr19, 0x08, 0x8E);
	set_gate(20, (u32int)isr20, 0x08, 0x8E);
	set_gate(21, (u32int)isr21, 0x08, 0x8E);
	set_gate(22, (u32int)isr22, 0x08, 0x8E);
	set_gate(23, (u32int)isr23, 0x08, 0x8E);
	set_gate(24, (u32int)isr24, 0x08, 0x8E);
	set_gate(25, (u32int)isr25, 0x08, 0x8E);
	set_gate(26, (u32int)isr26, 0x08, 0x8E);
	set_gate(27, (u32int)isr27, 0x08, 0x8E);
	set_gate(28, (u32int)isr28, 0x08, 0x8E);
	set_gate(29, (u32int)isr29, 0x08, 0x8E);
	set_gate(30, (u32int)isr30, 0x08, 0x8E);
	set_gate(31, (u32int)isr31, 0x08, 0x8E);
	
	idt_flush((u32int)&idt_ptr);
	
	// IRQs
	set_gate(32, (u32int)irq0 , 0x08, 0x8E);
	set_gate(33, (u32int)irq1 , 0x08, 0x8E);
	set_gate(34, (u32int)irq2 , 0x08, 0x8E);
	set_gate(35, (u32int)irq3 , 0x08, 0x8E);
	set_gate(36, (u32int)irq4 , 0x08, 0x8E);
	set_gate(37, (u32int)irq5 , 0x08, 0x8E);
	set_gate(38, (u32int)irq6 , 0x08, 0x8E);
	set_gate(39, (u32int)irq7 , 0x08, 0x8E);
	set_gate(40, (u32int)irq8 , 0x08, 0x8E);
	set_gate(41, (u32int)irq9 , 0x08, 0x8E);
	set_gate(42, (u32int)irq10, 0x08, 0x8E);
	set_gate(43, (u32int)irq11, 0x08, 0x8E);
	set_gate(44, (u32int)irq12, 0x08, 0x8E);
	set_gate(45, (u32int)irq13, 0x08, 0x8E);
	set_gate(46, (u32int)irq14, 0x08, 0x8E);
	set_gate(47, (u32int)irq15, 0x08, 0x8E);
	
	enable();
	
	vid->write("\t\t\t\t[OK]\n", 2);
}

idt::~idt()
{

}

void  idt::set_gate(u8int num, u32int base, u16int sel, u8int flags)
{
	idt_entries[num].base_lo = base & 0xFFFF;
	idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

 	idt_entries[num].sel	= sel;
	idt_entries[num].always0 = 0;
	// We must uncomment the OR below when we get to using user-mode.
	// It sets the interrupt gate's privilege level to 3.
	idt_entries[num].flags	= flags /* | 0x60 */;
}

void idt::remap_pic()
{
	// This will remap the interrupt controler to send us IRQs.
	
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
}

void register_irq(u32int irq, isr_t handler)
{
	interrupt_handlers[irq + 32] = handler;
}

void register_isr(u32int irq, isr_t handler)
{
	interrupt_handlers[irq] = handler;
}

void isr_handler(registers_t r)
{
	vid->write("\nERROR: ", 4);
	vid->write("Recieved Interrupt ");
	vid->putint(r.int_no);
	vid->write(" - ");
	vid->write((char *)exceptionMessages[r.int_no]);
	vid->write("!\n\n");
	
	panic("System Halted");
}

void irq_handler(registers_t r)
{
	if (r.int_no >= 40)
	{
		// Send reset signal to slave PIC
		outb(0xA0, 0x20);
	}
	
	// Send reset signal to master PIC
	outb(0x20, 0x20);

	if(interrupt_handlers[r.int_no] != 0)
	{
		(interrupt_handlers[r.int_no])(r);
	}	

}

