#include "video.h"

video::video()
{
	position = 0;	// Reset the X position
	offset = 0;	// Reset the Y position
	
	width = 80;	// Set the width and height to the default 80*25
	height = 25;
	
	videomem = (unsigned short*) 0xb8000;	// Set the address of the video ram
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
}

void video::write(char *cp)
{
	char *str = cp, *ch;
	
	for(ch = str; *ch; ch++)
	{
		put(*ch);	// Write the character to the display
	}
}

void video::put(char c)
{

	if(position >= width)
	{
		position = 0;
		offset += width;	
	}
	
	if(offset >= (width*height))
	{
		clear(); 	// Later on, this will scroll the display
	}
	
	videomem[offset + position] = (unsigned char) c | 0x0700;
	position++;
}
