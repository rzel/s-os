#ifndef VIDEO_H
#define VIDEO_H

class video
{
private:
	int width;			// width of the screen
	int height;			// height of the screen
	
	unsigned int offset;		// Y coordinate
	unsigned int position; 		// X coordinate
	unsigned short *videomem;	// A pointer to the video RAM
	
public:
	// Constructor and Deconstructor
	video();
	~video();
	
	// Other methods
	void clear();
	void write(char * cp);
	void put(char c);
};

#endif
