// common.h -- Defines typedefs and some global functions.
// Based on JamesM's kernel development tutorials.

#ifndef COMMON_H
#define COMMON_H

// The platfrom is that SoS will be built for is defined here. 
// Options are PLATFORM_x86_64 or PLATFORM_x86
#define PLATFORM_x86

#define NULL 0

// Some nice typedefs, to standardise sizes across platforms.
// These typedefs work both on X86 and X86_64.
typedef unsigned	int   u32int;
typedef 			int   s32int;
typedef unsigned	short u16int;
typedef			short s16int;
typedef unsigned	char  u8int;
typedef 			char  s8int;

void outb(u16int port, u8int value);
void outw(u16int port, u16int value);
u8int inb(u16int port);
u16int inw(u16int port);
void memcpy(u32int *dest, const u32int *src, u32int len);
void memset(u32int *dest, u32int val, u32int len);

bool strcmp(const char * str1, const char * str2);

// Some handy assembly functions
extern "C" 
{ 
	void halt();
	void disable();
	void enable();
};

void fixme(const char * message);
void panic(const char * message);

#endif
