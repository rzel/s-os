#include "include/common.h"
#include "include/idt.h"
#include "include/video_textmode.h"

idt::idt()
{
	vid->write("Setting up IDT");
	vid->write("\t\t\t\t[Incomplete]\n", 4);
}

idt::~idt()
{

}
