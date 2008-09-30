#include "include/video_textmode.h"

video * vid;

video::video()
{
	position = 0;	// Reset the X position
	offset = 0;	// Reset the offset
	
	cursor_x = 0;	// Reset the position of the cursor 
	cursor_y = 0;
	
	width = 80;	// Set the width and height to the default 80*25
	height = 25;
	
	videomem = (unsigned short*) 0xb8000;	// Set the address of the video ram
	
	setcolour(0, 7);// Set the colour to white on black
	
	clear();	// Clear the screen
}

video::~video() {}

void video::clear()
{
	// Replace the video buffer with spaces
	
	for(unsigned int i = 0; i < (width*height); i++)
	{
		videomem[i] = (unsigned char) ' ' | 0x0700;
	}
	
	position = 0;	// Reset the position and offset
	offset = 0;
	cursor_y = 0;
	cursor_x = 0;
}

void video::write(const char *cp, u32int fore, u32int back)
{
	const char *str = cp, *ch;
	
	setcolour(back, fore);
	
	for(ch = str; *ch; ch++)
	{
		putch(*ch);	// Write the character to the display
	}
}

void video::putch(char c)
{

	if(position >= width)
	{
		newline();	
	}
	
	
	if(c == '\n') // Newline
	{
		newline();
	}
	else if(c == '\r') // Carrage Return
	{
		cursor_x = 0;
		position = 0;
	}
	else if(c == '\t')
	{
		 cursor_x = (cursor_x + 8) & ~(8 - 1);
		 position = cursor_x;
	}
	else if(c == '\b')
	{
		if(cursor_x > 0)
		{
			cursor_x--;
			position--;
		}
		else
		{
			offset -= width;
			cursor_y--;
			
			position = width - 1;
			cursor_x = position;
		}
		
		videomem[offset + position] = ' ' | colour;
	}
	else
	{
		videomem[offset + position] = (unsigned char) c | colour;
	
		cursor_x++;		// Move the cursor forward one character
		position++;
	}
	
	move_cursor(cursor_x, cursor_y);
		
}

void video::putint(u32int n, u32int fore, u32int back)
{	
	if(n == 0)
	{
		putch('0');
		return;
	}
	
	s32int acc = n;
	char c[32];
	int i = 0;
	while (acc > 0)
	{
		c[i] = '0' + acc%10;
 		acc /= 10;
		i++;
	}
	c[i] = 0;

	char c2[32];
	c2[i--] = 0;
	int j = 0;
	while(i >= 0)
	{
		c2[i--] = c[j++];
	}
	
	write(c2, fore, back);
	
}

void video::puthex(u32int n, u32int fore, u32int back)
{
	setcolour(back, fore);	
	
	s32int tmp;

	write("0x");

	char noZeroes = 1;

	int i;
	for (i = 28; i > 0; i -= 4)
	{
		tmp = (n >> i) & 0xF;
		
		if (tmp == 0 && noZeroes != 0)
		{
			continue;
		}
    
	 	if (tmp >= 0xA)
		{
			noZeroes = 0;
	 		putch(tmp-0xA+'a' );
		}
		else
		{
			noZeroes = 0;
			putch( tmp+'0' );
		}
	}
  
	tmp = n & 0xF;
	
	if (tmp >= 0xA)
	{
       	 	putch(tmp-0xA+'a');
	}
	else
	{
		putch(tmp+'0');
	}
}

void video::move_cursor(u8int x, u8int y)
{
	// Updates the hardware cursor.

	u16int cursorLocation = y * width + x;
	outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
	outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
	outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
	outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}

void video::scroll()
{
	u8int  attributeByte = (0 << 4) | (7 & 0x0F);
	u16int blank = 0x20 | (attributeByte << 8);
	
	// Move every character up one line
	for(unsigned int i = 0; i < width * (height - 1); i++)
	{
		videomem[i] = videomem[i + 80];
	}
	
	// Clear the last line
	for(unsigned int i = width * (height - 1); i < width * height; i++)
	{
		videomem[i] = blank;
	}
	
	// Reset the coordinates and offset
	position = 0;
	cursor_x = 0;
	cursor_y = height - 1;
	offset = width * (height - 1);
	
}

void video::newline()
{
	position = 0;
	cursor_x = 0;
	
	offset += width;
	cursor_y++;
	
	if(offset >= (width*height))
	{
		scroll(); 	// Scroll the contents of the display up
	}
}

void video::setcolour(u8int back, u8int fore)
{
	u8int  attributeByte = (back << 4) | (fore & 0x0F);
	colour = attributeByte << 8;
}

