#include "include/common.h"
#include "include/seashell.h"
#include "include/keyboard.h"
#include "include/video_textmode.h"
#include "include/kernel.h"

seashell * seashell_i;

seashell::seashell()
{
	vid->write("Starting Seashell");
	
	vid->write("\t\t\t[OK]\n", 2);
}

seashell::~seashell()
{

}
	
void seashell::main()
{
	for(; ;)
	{
		vid->write("SoS", 2);
		vid->write(":~$");
		
		char * input = keyboard_i->get_string();
		
		if(strcmp(input, "help"))
		{
			seashell_help();
		}
		else if(strcmp(input, "about"))
		{
			seashell_about();
		}
		else if(strcmp(input, "clear"))
		{
			vid->clear();
		}
		else if(strcmp(input, "reboot"))
		{
			delete kernel_i;
		}
		else if(strcmp(input, "uname"))
		{
			seashell_uname();
		}
	}
}

void seashell::seashell_help()
{
	vid->write("\nHelp\n\n", 14);
	vid->write(" about\t- Information about SoS\n");
	vid->write(" clear\t- Clear the screen\n");
	vid->write(" help\t- Show commands available\n");
	vid->write(" reboot\t- Restart computer\n\n");
	
}

void seashell::seashell_about()
{
	vid->write("\nSeashell", 14);
	vid->write("Version 0.1 - Running on SoS Version ");
	vid->write(SYSTEM_VERSION);
	vid->write("\n\n");
}

void seashell::seashell_uname()
{
	vid->write("\nSoS\n");
}

