/*
** asm/blinken.h -- m68k blinkenlights support (currently hp300 only)
**
** (c) 1998 Phil Blundell <philb@gnu.org>
**
** This file is subject to the terms and conditions of the GNU General Public
** License.  See the file COPYING in the main directory of this archive
** for more details.
**
*/

#ifndef _M68K_BLINKEN_H
#define _M68K_BLINKEN_H

#include <asm/setup.h>
#include <asm/io.h>

#define HP300_LEDS		0xf001ffff

<<<<<<< HEAD
extern unsigned char hp300_ledstate;
=======
extern unsigned char ledstate;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

static __inline__ void blinken_leds(int on, int off)
{
	if (MACH_IS_HP300)
	{
<<<<<<< HEAD
		hp300_ledstate |= on;
		hp300_ledstate &= ~off;
		out_8(HP300_LEDS, ~hp300_ledstate);
=======
		ledstate |= on;
		ledstate &= ~off;
		out_8(HP300_LEDS, ~ledstate);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}
}

#endif
