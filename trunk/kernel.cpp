#include "kernel.h"

int main(void)
{
	video vid;

	vid.clear();
	vid.write("Welcome to SoS");
	
	return 0;
}
