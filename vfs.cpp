#include "include/common.h"
#include "include/vfs.h"
#include "include/video_textmode.h"

vfs::vfs()
{
	vid->write("Starting Virtual File System");
	
	vid->write("\t\t[Incomplete]\n", 4);
}

vfs::~vfs()
{

}

vfs * vfs_i;

