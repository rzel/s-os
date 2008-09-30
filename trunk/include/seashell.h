#ifndef SEASHELL_H
#define SEASHELL_H

#include "common.h"

class seashell
{
private:
	u32int process_arguments(char * str, char * argv[]);

	void seashell_help(int argc, char **);
	void seashell_about(int argc, char **);	
	void seashell_uname(int argc, char **);

public:
	seashell();
	~seashell();
	
	void main();
};

extern seashell * seashell_i;

#endif
