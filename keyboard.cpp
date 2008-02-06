#include "include/common.h"
#include "include/keyboard.h"
#include "include/idt.h"
#include "include/video_textmode.h"
#include "include/kernel.h"

keyboard * keyboard_i;

bool shift = false;

unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,					/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

unsigned char kbdshift[128] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
  '(', ')', '_', '+', '\b',	/* Backspace */
  '\t',			/* Tab */
  'Q', 'W', 'E', 'R',	/* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',		/* Enter key */
    0,			/* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
 '"', '~',   0,		/* Left shift */
 '|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
  'M', '<', '>', '?',   0,					/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

keyboard::keyboard()
{
	vid->write("Setting up Keyboard");
	
	register_irq(1, &keyboard_irq_callback);
	
	print_chars = false;
	
	vid->write("\t\t\t[OK]\n", 2);
}

keyboard::~keyboard()
{

}

void keyboard::add_char(char c)
{	
	if(c == '\b')
	{
		// We don't want to backspace over the prompt
		if(position == 0)
		{
			return;		
		}
		
		position--;
		buffer[position] = '\0';
	}
	else if(c == '\n')
	{
		buffer[position] = '\1';
	}
	else
	{
		buffer[position] = c;
		position++;
		buffer[position] = '\0';
	}	
	
	
	// Kind of hackish, I know
	if(print_chars)
	{
		vid->putch(c);
	}
}

char * keyboard::get_string()
{
	print_chars = true;
	
	// Clear that keyboard buffer
	position = 0;
	buffer[0] = '\0';
	
	while(buffer[position] != '\1')
	{
		
	}
	
	buffer[position] = '\0';
	
	print_chars = false;
	
	return (char *)buffer;
}

void keyboard_irq_callback(registers_t r)
{	
	u32int scancode = inb(0x60);
	
	// Check if the key is being released
	if(scancode & 0x80)
	{
		scancode -= 0x80;
				if(scancode == 0x2a || scancode == 0x36)
		{
			shift = false;
		}
	}
	else
	{	
		if(scancode == 0x01)
		{
			delete kernel_i;
		}
		else if(scancode == 0x2a || scancode == 0x36)
		{
			shift = true;
		}
		else if(kbdus[scancode] != 0)
		{
			if(shift)
			{
				keyboard_i->add_char(kbdshift[scancode]);
				
			}
			else
			{
				keyboard_i->add_char(kbdus[scancode]);
			}
		}
	}
}


