#include "include/common.h"
#include "include/timer.h"
#include "include/idt.h"
#include "include/video_textmode.h"

timer * timer_i;

timer::timer()
{
	vid->write("Setting up PIT");
	
	register_irq(timer_interrupt, &timer_irq_callback);
	
	set_interval(50);
	
	vid->write("\t\t\t\t[OK]\n", 2);
}

timer::~timer()
{

}

void timer::set_interval(u32int hz)
{
	u32int divisor = 1193180 / hz;	// Calculate our divisor
	outb(0x43, 0x36);				// Set our command byte 0x36
	outb(0x40, divisor & 0xFF);		// Set low byte of divisor
	outb(0x40, divisor >> 8);		// Set high byte of divisor
	frequency = hz;
}

void timer::delay(u32int seconds)
{
	u32int finishedTicks = ticks + (seconds * frequency);
	
	while(finishedTicks != ticks)
	{
	}
}

void timer_irq_callback(registers_t r)
{	
	// First, make the compiler happy by using r
	if(r.int_no != timer_interrupt)
		return
		
	timer_i->set_ticks(timer_i->get_ticks() + 1);
	
}
