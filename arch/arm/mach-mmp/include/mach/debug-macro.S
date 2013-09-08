/* arch/arm/mach-mmp/include/mach/debug-macro.S
 *
 * Debugging macro include header
 *
 *  Copied from arch/arm/mach-pxa/include/mach/debug.S
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <mach/addr-map.h>

<<<<<<< HEAD
		.macro	addruart, rp, rv, tmp
=======
		.macro	addruart, rp, rv
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		ldr	\rp, =APB_PHYS_BASE		@ physical
		ldr	\rv, =APB_VIRT_BASE		@ virtual
		orr	\rp, \rp, #0x00017000
		orr	\rv, \rv, #0x00017000
		.endm

#define UART_SHIFT	2
#include <asm/hardware/debug-8250.S>
