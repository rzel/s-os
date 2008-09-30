#ifndef VFS_H
#define VFS_H

#include "common.h"

class vfs
{
private:

public:
	vfs();
	~vfs();
	
	void mount();

};

extern vfs * vfs_i;

#endif
