#include<iostream>
#include<fstream>
#include "../common.h"
#include "../ramdisk.h"

using namespace std;

int main(int argc, char * argv[])
{
	fstream ramdisk;
	char * buffer;
	ramdisk_header_t * initrd_header;
	
	if(argv[1] == "")
	{
		cout << "Usage: test_ramdisk [initrd]\n";
		return 1;
	}
	
	ramdisk.open(argv[1], fstream::in | fstream::binary);
	
	ramdisk.read(buffer, sizeof(initrd_header));
	
	initrd_header = (ramdisk_header_t *)buffer;
	
	cout << "Number of files in ramdisk: " << initrd_header->num_files << endl;
	
	ramdisk.close();

	return 0;
}
