<<<<<<< HEAD
/* Copyright (c) 2010, 2011, Code Aurora Forum. All rights reserved.
=======
/* Copyright (c) 2010, Code Aurora Forum. All rights reserved.
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
<<<<<<< HEAD
=======
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
 */

#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/irq.h>
<<<<<<< HEAD
#include <linux/irqdomain.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/memblock.h>
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/hardware/gic.h>
<<<<<<< HEAD
#include <asm/setup.h>
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#include <mach/board.h>
#include <mach/msm_iomap.h>

<<<<<<< HEAD
static void __init msm8x60_fixup(struct tag *tag, char **cmdline,
		struct meminfo *mi)
{
	for (; tag->hdr.size; tag = tag_next(tag))
		if (tag->hdr.tag == ATAG_MEM &&
				tag->u.mem.start == 0x40200000) {
			tag->u.mem.start = 0x40000000;
			tag->u.mem.size += SZ_2M;
		}
}

static void __init msm8x60_reserve(void)
{
	memblock_remove(0x40000000, SZ_2M);
}
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

static void __init msm8x60_map_io(void)
{
	msm_map_msm8x60_io();
}

<<<<<<< HEAD
#ifdef CONFIG_OF
static struct of_device_id msm_dt_gic_match[] __initdata = {
	{ .compatible = "qcom,msm-8660-qgic", .data = gic_of_init },
	{}
};
#endif

static void __init msm8x60_init_irq(void)
{
	if (!of_have_populated_dt())
		gic_init(0, GIC_PPI_START, MSM_QGIC_DIST_BASE,
			 (void *)MSM_QGIC_CPU_BASE);
#ifdef CONFIG_OF
	else
		of_irq_init(msm_dt_gic_match);
#endif
=======
static void __init msm8x60_init_irq(void)
{
	unsigned int i;

	gic_init(0, GIC_PPI_START, MSM_QGIC_DIST_BASE,
		 (void *)MSM_QGIC_CPU_BASE);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	/* Edge trigger PPIs except AVS_SVICINT and AVS_SVICINTSWDONE */
	writel(0xFFFFD7FF, MSM_QGIC_DIST_BASE + GIC_DIST_CONFIG + 4);

	/* RUMI does not adhere to GIC spec by enabling STIs by default.
	 * Enable/clear is supposed to be RO for STIs, but is RW on RUMI.
	 */
	if (!machine_is_msm8x60_sim())
		writel(0x0000FFFF, MSM_QGIC_DIST_BASE + GIC_DIST_ENABLE_SET);
<<<<<<< HEAD
}

static void __init msm8x60_init(void)
{
}

#ifdef CONFIG_OF
static struct of_dev_auxdata msm_auxdata_lookup[] __initdata = {
	{}
};

static void __init msm8x60_dt_init(void)
{
	if (of_machine_is_compatible("qcom,msm8660-surf")) {
		printk(KERN_INFO "Init surf UART registers\n");
		msm8x60_init_uart12dm();
	}

	of_platform_populate(NULL, of_default_bus_match_table,
			msm_auxdata_lookup, NULL);
}

static const char *msm8x60_fluid_match[] __initdata = {
	"qcom,msm8660-fluid",
	"qcom,msm8660-surf",
	NULL
};
#endif /* CONFIG_OF */

MACHINE_START(MSM8X60_RUMI3, "QCT MSM8X60 RUMI3")
	.fixup = msm8x60_fixup,
	.reserve = msm8x60_reserve,
	.map_io = msm8x60_map_io,
	.init_irq = msm8x60_init_irq,
	.handle_irq = gic_handle_irq,
=======

	/* FIXME: Not installing AVS_SVICINT and AVS_SVICINTSWDONE yet
	 * as they are configured as level, which does not play nice with
	 * handle_percpu_irq.
	 */
	for (i = GIC_PPI_START; i < GIC_SPI_START; i++) {
		if (i != AVS_SVICINT && i != AVS_SVICINTSWDONE)
			irq_set_handler(i, handle_percpu_irq);
	}
}

static void __init msm8x60_init(void)
{
}

MACHINE_START(MSM8X60_RUMI3, "QCT MSM8X60 RUMI3")
	.map_io = msm8x60_map_io,
	.init_irq = msm8x60_init_irq,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	.init_machine = msm8x60_init,
	.timer = &msm_timer,
MACHINE_END

MACHINE_START(MSM8X60_SURF, "QCT MSM8X60 SURF")
<<<<<<< HEAD
	.fixup = msm8x60_fixup,
	.reserve = msm8x60_reserve,
	.map_io = msm8x60_map_io,
	.init_irq = msm8x60_init_irq,
	.handle_irq = gic_handle_irq,
=======
	.map_io = msm8x60_map_io,
	.init_irq = msm8x60_init_irq,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	.init_machine = msm8x60_init,
	.timer = &msm_timer,
MACHINE_END

MACHINE_START(MSM8X60_SIM, "QCT MSM8X60 SIMULATOR")
<<<<<<< HEAD
	.fixup = msm8x60_fixup,
	.reserve = msm8x60_reserve,
	.map_io = msm8x60_map_io,
	.init_irq = msm8x60_init_irq,
	.handle_irq = gic_handle_irq,
=======
	.map_io = msm8x60_map_io,
	.init_irq = msm8x60_init_irq,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	.init_machine = msm8x60_init,
	.timer = &msm_timer,
MACHINE_END

MACHINE_START(MSM8X60_FFA, "QCT MSM8X60 FFA")
<<<<<<< HEAD
	.fixup = msm8x60_fixup,
	.reserve = msm8x60_reserve,
	.map_io = msm8x60_map_io,
	.init_irq = msm8x60_init_irq,
	.handle_irq = gic_handle_irq,
	.init_machine = msm8x60_init,
	.timer = &msm_timer,
MACHINE_END

#ifdef CONFIG_OF
/* TODO: General device tree support for all MSM. */
DT_MACHINE_START(MSM_DT, "Qualcomm MSM (Flattened Device Tree)")
	.map_io = msm8x60_map_io,
	.init_irq = msm8x60_init_irq,
	.init_machine = msm8x60_dt_init,
	.timer = &msm_timer,
	.dt_compat = msm8x60_fluid_match,
MACHINE_END
#endif /* CONFIG_OF */
=======
	.map_io = msm8x60_map_io,
	.init_irq = msm8x60_init_irq,
	.init_machine = msm8x60_init,
	.timer = &msm_timer,
MACHINE_END
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
