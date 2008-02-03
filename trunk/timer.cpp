#include "include/common.h"
#include "include/timer.h"
#include "include/idt.h"
#include "include/video_textmode.h"

timer * timer_i;

timer::timer()
{
	vid->write("Setting up PIT");
	
	//register_irq(1, &timer_irq_callback);
	
	vid->write("\t\t\t\t[Incomplete]\n", 4);
}

timer::~timer()
{

}
