#ifndef VIDEO_H
#define VIDEO_H

#include "common.h"

class video
{
private:
	int width;			// width of the screen
	int height;			// height of the screen
	u8int cursor_x;			// The X and Y cooddinates of the cursor
	u8int cursor_y;			
	
	u16int colour;			// A byte holding the colour information
	
	unsigned int offset;		// Offset 
	unsigned int position; 		// X coordinate
	unsigned short *videomem;	// A pointer to the video RAM
	
public:
	// Constructor and Deconstructor
	video();
	~video();
	
	// Other methods
	void clear();
	void write(char * cp);
	
	void putch(char c);
	void putint(u32int n);
	void puthex(u32int n);
	
	void scroll();
	void move_cursor(u8int x, u8int);
	void newline();
	void setcolour(u8int back, u8int fore);
};

#endif
