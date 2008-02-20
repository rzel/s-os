#include<iostream>
#include<fstream>
#include "common.h"
#include "ramdisk.h"

using namespace std;


int main(int argc, char * argv[])
{
	if(argc < 2)
	{
		cout << "Usage: ramdisk [ramdisk_file]...\n";
		return 1;
	}
	
	fstream ramdisk;
	
	// Open the ramdisk file
	ramdisk.open("initrd", fstream::out | fstream::binary);
	
	ramdisk_header_t initrd_header;
	ramdisk_file_header_t initrd_file_headers[64];
	
	initrd_header.num_files = argc - 1;
	u32int file_header_size = (sizeof(ramdisk_file_header_t) * 64);
	u32int file_offest = sizeof(ramdisk_header_t) + file_header_size;
	
	
	
	cout << "Writing Header... " << endl;
	
	// Write the header and file headers
	ramdisk.write((const char *)&initrd_header, sizeof(initrd_header));
	ramdisk.write((const char *)&initrd_file_headers, sizeof(file_header_size));
	
	// Write files to disk
	for(u32int i = 0; i < initrd_header.num_files; i++)
	{
		cout << "Writing File " << argv[i + 1] << endl;
		
	}
	
	ramdisk.close();
	
	cout << endl << initrd_header.num_files << " written to ramdisk\n";

	return 0;
}
