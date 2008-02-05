#ifndef TIMER_H
#define TIMER_H

#include "isr.h"

const u8int timer_interrupt = 0;

class timer
{
private:
	u32int ticks;
	u32int frequency;

public:
	timer();
	~timer();
	
	u32int get_ticks()		{ return ticks; };
	void set_ticks(int t)	{ ticks = t; };
	
	void set_interval(u32int hz);
	void delay(u32int seconds);
};

void timer_irq_callback(registers_t r);

extern timer * timer_i;

#endif
