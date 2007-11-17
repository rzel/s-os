// vbe.cpp - Change graphics mode

#include "common.h"
#include "vbe.h"

void vbe_write(u16int index, u16int value)
{
   outw(VBE_DISPI_IOPORT_INDEX, index);
   outw(VBE_DISPI_IOPORT_DATA, value);
}

void vbe_set(u16int xres, u16int yres, u16int bpp)
{
   vbe_write(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
   vbe_write(VBE_DISPI_INDEX_XRES, xres);
   vbe_write(VBE_DISPI_INDEX_YRES, yres);
   vbe_write(VBE_DISPI_INDEX_BPP, bpp);
   vbe_write(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED);   
}

