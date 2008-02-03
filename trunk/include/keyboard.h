#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "isr.h"
#include "common.h"

class keyboard
{
public:
	keyboard();
	~keyboard();	
};

void keyboard_irq_callback(registers_t r);

extern keyboard * keyboard_i;

#endif
