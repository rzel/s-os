#ifndef SEASHELL_H
#define SEASHELL_H

#include "common.h"

class seashell
{
private:
	void seashell_help();
	void seashell_about();	
	void seashell_uname();

public:
	seashell();
	~seashell();
	
	void main();
};

extern seashell * seashell_i;

#endif
