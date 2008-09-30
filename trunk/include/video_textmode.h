#ifndef VIDEO_H
#define VIDEO_H

#include "common.h"

class video
{
private:
	u32int width;				// width of the screen
	u32int height;				// height of the screen
	u8int cursor_x;			// The X and Y cooddinates of the cursor
	u8int cursor_y;			
	
	u16int colour;				// A byte holding the colour information
	
	u32int offset;				// Offset 
	u32int position; 			// X coordinate
	unsigned short *videomem;	// A pointer to the video RAM
	
public:
	// Constructor and Deconstructor
	video();
	~video();
	
	// Other methods
	void clear();
	void write(const char * cp, u32int fore = 7, u32int back = 0);
	
	void putch(char c);
	void putint(u32int n, u32int fore = 7, u32int back = 0);
	void puthex(u32int n, u32int fore = 7, u32int back = 0);
	
	void scroll();
	void move_cursor(u8int x, u8int);
	void newline();
	void setcolour(u8int back, u8int fore);
};

extern video * vid;

#endif
