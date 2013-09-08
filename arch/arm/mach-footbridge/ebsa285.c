/*
 * linux/arch/arm/mach-footbridge/ebsa285.c
 *
 * EBSA285 machine fixup
 */
#include <linux/init.h>
#include <linux/spinlock.h>

#include <asm/hardware/dec21285.h>
#include <asm/mach-types.h>

#include <asm/mach/arch.h>

#include "common.h"

MACHINE_START(EBSA285, "EBSA285")
	/* Maintainer: Russell King */
<<<<<<< HEAD
	.atag_offset	= 0x100,
=======
	.boot_params	= 0x00000100,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	.video_start	= 0x000a0000,
	.video_end	= 0x000bffff,
	.map_io		= footbridge_map_io,
	.init_irq	= footbridge_init_irq,
	.timer		= &footbridge_timer,
<<<<<<< HEAD
	.restart	= footbridge_restart,
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
MACHINE_END

