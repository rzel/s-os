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
		vid->write(":/$ ");
		
		u32int arg_num = 0;
		char ** args;
		
		char * input = NULL;
		
		input = keyboard_i->get_string();
		
		if(*input != 0)
		{
		
			arg_num = process_arguments(input, args);
			//arg_num = 1;
		
			//vid->putint(arg_num);
			//vid->write("\n");
		
			if(strcmp(input, "help"))
			{
				seashell_help(arg_num, args);
			}
			else if(strcmp(input, "about"))
			{
				seashell_about(arg_num, args);
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
				seashell_uname(arg_num, args);
			}
			else
			{
				vid->write("Seashell: ");
				vid->write(args[0]);
				vid->write(": command not found\n");
			}
		}
		
	}
}

u32int seashell::process_arguments(char * str, char * argv[])
{
	u32int arg_num = 0;
	char * args[32];
	char *in = str, *ch;
	
	//char * args[32];
	
	/*while(*str != 0)
	{		
		while(*str != ' ')
		{
			//*args[arg_num] = *str;
			
			//*argv[arg_num]++;
			*str++;
		}
		
		*str++;
		
		if(*str != ' ' && str != 0)
		{
			vid->putch('1');
			vid->putch(*str);
			arg_num++;
		}
	}*/
	
	for(ch = in; *ch; *ch++)
	{
		if(*ch == ' ')
		{
			arg_num++;
		}
		else
		{
			//*args[arg_num] = *ch;
			//*args[arg_num]++;
			//*args[arg_num] = 0;
		}
	}
	
	//argv = args;
	
	return arg_num + 1;
}

void seashell::seashell_help(int argc, char * argv[])
{
	if(argc == 1)
	{
		vid->write("\nHelp\n\n", 14);
		vid->write(" about\t- Information about SoS\n");
		vid->write(" clear\t- Clear the screen\n");
		vid->write(" help\t- Show commands available\n");
		vid->write(" reboot\t- Restart computer\n");
		vid->write(" uname\t- Display system information\n\n");
	}
	
}

void seashell::seashell_about(int argc, char * argv[])
{
	if(argc == 1)
	{
		vid->write("\nSeashell\n\n", 14);
		vid->write("Version 0.1 - Running on SoS Version ");
		vid->write(SYSTEM_VERSION);
		vid->write("\n\n");
	}
}

void seashell::seashell_uname(int argc, char * argv[])
{
	if(argc == 1)
	{
		vid->write("SoS\n");
	}	
}
