// common.h -- Defines typedefs and some global functions.
// Based on JamesM's kernel development tutorials.

#ifndef COMMON_H
#define COMMON_H

#define PLATFORM_X86
// #define PLATFORM_x86_64

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
void memcpy(u8int *dest, const u8int *src, u32int len);
void memset(u8int *dest, u8int val, u32int len);

// Some handy assembly functions
extern "C" 
{ 
	void halt();
	void disable();
	void enable();
};

void fixme(char * message);
void panic(char * message);

#endif
