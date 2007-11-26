#include "include/isr.h"
#include "include/idt.h"
#include "include/video_textmode.h"

extern video * vid;
extern idt * idt_i;

isr_t interrupt_handlers[256];

extern "C" 
{ 
	void isr_handler(registers_t regs); 
	void irq_handler(registers_t regs);
};

void isr_handler(registers_t regs)
{
   vid->write("recieved interrupt: ");
   vid->putint(regs.int_no);
   vid->write("\n");
}

void irq_handler(registers_t regs)
{
   // Send an EOI (end of interrupt) signal to the PICs.
   // If this interrupt involved the slave.
   if (regs.int_no >= 40)
   {
       // Send reset signal to slave.
       outb(0xA0, 0x20);
   }
   // Send reset signal to master. (As well as slave, if necessary).
   outb(0x20, 0x20);

   if (interrupt_handlers[regs.int_no] != 0)
   {
       isr_t handler = interrupt_handlers[regs.int_no];
       handler(regs);
   }
}
