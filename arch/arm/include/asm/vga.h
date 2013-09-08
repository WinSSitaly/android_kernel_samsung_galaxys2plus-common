#ifndef ASMARM_VGA_H
#define ASMARM_VGA_H

#include <linux/io.h>
<<<<<<< HEAD

extern unsigned long vga_base;

#define VGA_MAP_MEM(x,s)	(vga_base + (x))
=======
#include <mach/hardware.h>

#define VGA_MAP_MEM(x,s)	(PCIMEM_BASE + (x))
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#define vga_readb(x)	(*((volatile unsigned char *)x))
#define vga_writeb(x,y)	(*((volatile unsigned char *)y) = (x))

#endif
