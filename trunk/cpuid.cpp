#include "include/common.h"
#include "include/cpuid.h"
//#include "include/video_textmode.h"

char * get_cpu_vendor()
{	
	// Still trying to work out how to decode the names without magic numbers...
	
	switch(get_cpuid_ebx(0x0)) {
		case 0x756e6547: //Intel Magic Code
			return "GenuineIntel";
			break;
		case 0x68747541: //AMD Magic Code
			return "AuthenticAMD";
			break;
		default:
			return "Unknown";
			break;
	}
}

bool cpuid_check_flag(u32int flag)
{
	// I'm not sure if this is correct...
	
	if((get_cpuid_ebx(0x1) || flag) == 0x1)
		return true;
	else
		return false;
}
