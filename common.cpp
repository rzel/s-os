// common.cpp -- Defines some global functions.
// From JamesM's kernel development tutorials.

#include "include/common.h"
#include "include/video_textmode.h"

extern video * vid;

// Write a byte out to the specified port.
void outb(u16int port, u8int value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

void outw(u16int port, u16int value)
{
    asm volatile ("outw %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port)
{
   u8int ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

u16int inw(u16int port)
{
   u16int ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

// Copy len bytes from src to dest.
void memcpy(u32int *dest, const u32int *src, u32int len)
{
    const u32int *sp = (const u32int *)src;
    u32int *dp = (u32int *)dest;
    for(; len != 0; len--) *dp++ = *sp++;
}

// Write len copies of val into dest.
void memset(u32int *dest, u32int val, u32int len)
{
    u32int *temp = (u32int *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

// This function prints a FIXME: message
void fixme(char * message)
{
	vid->write("FIXME: ", 4);
	vid->write(message);
	vid->write("\n");
}

// This is a kernel panic - after showing a message, the CPU will halt
void panic(char * message)
{
	disable();			// Let's disable any interrupts
	
	vid->write("Fatal Error:\n\n", 4);
	
	vid->write(message);
	
	halt();
}


