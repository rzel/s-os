#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "isr.h"
#include "common.h"

class keyboard
{
private:
	char buffer[512];
	u32int position;
	
	bool print_chars;

public:
	keyboard();
	~keyboard();
	
	char * get_string();
	
	void add_char(char c);
};

void keyboard_irq_callback(registers_t r);

extern keyboard * keyboard_i;

#endif
