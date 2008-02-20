#ifndef RAMDISK_H
#define RAMDISK_H

struct ramdisk_header
{
	u32int num_files;
} __attribute__((__packed__));

typedef struct ramdisk_header ramdisk_header_t;

struct ramdisk_file_header
{
	s8int magic;
	s8int name[64];
	u32int offset;
	u32int length;
	
} __attribute__((__packed__));

typedef struct ramdisk_file_header ramdisk_file_header_t;

#endif
