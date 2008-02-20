#ifndef SEASHELL_H
#define SEASHELL_H

#include "common.h"

class seashell
{
private:
	u32int process_arguments(char * str, char * argv[]);

	void seashell_help(int argc, char * argv[]);
	void seashell_about(int argc, char * argv[]);	
	void seashell_uname(int argc, char * argv[]);

public:
	seashell();
	~seashell();
	
	void main();
};

extern seashell * seashell_i;

#endif
