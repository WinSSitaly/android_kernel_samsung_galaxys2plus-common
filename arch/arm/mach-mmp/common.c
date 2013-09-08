/*
 *  linux/arch/arm/mach-mmp/common.c
 *
 *  Code common to PXA168 processor lines
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include <asm/page.h>
#include <asm/mach/map.h>
<<<<<<< HEAD
#include <asm/system_misc.h>
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <mach/addr-map.h>
#include <mach/cputype.h>

#include "common.h"

#define MMP_CHIPID	(AXI_VIRT_BASE + 0x82c00)

unsigned int mmp_chip_id;
EXPORT_SYMBOL(mmp_chip_id);

static struct map_desc standard_io_desc[] __initdata = {
	{
		.pfn		= __phys_to_pfn(APB_PHYS_BASE),
<<<<<<< HEAD
		.virtual	= (unsigned long)APB_VIRT_BASE,
=======
		.virtual	= APB_VIRT_BASE,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		.length		= APB_PHYS_SIZE,
		.type		= MT_DEVICE,
	}, {
		.pfn		= __phys_to_pfn(AXI_PHYS_BASE),
<<<<<<< HEAD
		.virtual	= (unsigned long)AXI_VIRT_BASE,
=======
		.virtual	= AXI_VIRT_BASE,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		.length		= AXI_PHYS_SIZE,
		.type		= MT_DEVICE,
	},
};

void __init mmp_map_io(void)
{
	iotable_init(standard_io_desc, ARRAY_SIZE(standard_io_desc));

	/* this is early, initialize mmp_chip_id here */
	mmp_chip_id = __raw_readl(MMP_CHIPID);
}
<<<<<<< HEAD

void mmp_restart(char mode, const char *cmd)
{
	soft_restart(0);
}
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
