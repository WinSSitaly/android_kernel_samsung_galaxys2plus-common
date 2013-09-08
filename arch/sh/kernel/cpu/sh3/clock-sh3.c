/*
 * arch/sh/kernel/cpu/sh3/clock-sh3.c
 *
 * Generic SH-3 support for the clock framework
 *
 *  Copyright (C) 2005  Paul Mundt
 *
 * FRQCR parsing hacked out of arch/sh/kernel/time.c
 *
 *  Copyright (C) 1999  Tetsuya Okada & Niibe Yutaka
 *  Copyright (C) 2000  Philipp Rumpf <prumpf@tux.org>
 *  Copyright (C) 2002, 2003, 2004  Paul Mundt
 *  Copyright (C) 2002  M. R. Brown  <mrbrown@linux-sh.org>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */
#include <linux/init.h>
#include <linux/kernel.h>
#include <asm/clock.h>
#include <asm/freq.h>
#include <asm/io.h>

static int stc_multipliers[] = { 1, 2, 3, 4, 6, 1, 1, 1 };
static int ifc_divisors[]    = { 1, 2, 3, 4, 1, 1, 1, 1 };
static int pfc_divisors[]    = { 1, 2, 3, 4, 6, 1, 1, 1 };

static void master_clk_init(struct clk *clk)
{
	int frqcr = __raw_readw(FRQCR);
	int idx = ((frqcr & 0x2000) >> 11) | (frqcr & 0x0003);

	clk->rate *= pfc_divisors[idx];
}

<<<<<<< HEAD
static struct sh_clk_ops sh3_master_clk_ops = {
=======
static struct clk_ops sh3_master_clk_ops = {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	.init		= master_clk_init,
};

static unsigned long module_clk_recalc(struct clk *clk)
{
	int frqcr = __raw_readw(FRQCR);
	int idx = ((frqcr & 0x2000) >> 11) | (frqcr & 0x0003);

	return clk->parent->rate / pfc_divisors[idx];
}

<<<<<<< HEAD
static struct sh_clk_ops sh3_module_clk_ops = {
=======
static struct clk_ops sh3_module_clk_ops = {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	.recalc		= module_clk_recalc,
};

static unsigned long bus_clk_recalc(struct clk *clk)
{
	int frqcr = __raw_readw(FRQCR);
	int idx = ((frqcr & 0x8000) >> 13) | ((frqcr & 0x0030) >> 4);

	return clk->parent->rate / stc_multipliers[idx];
}

<<<<<<< HEAD
static struct sh_clk_ops sh3_bus_clk_ops = {
=======
static struct clk_ops sh3_bus_clk_ops = {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	.recalc		= bus_clk_recalc,
};

static unsigned long cpu_clk_recalc(struct clk *clk)
{
	int frqcr = __raw_readw(FRQCR);
	int idx = ((frqcr & 0x4000) >> 12) | ((frqcr & 0x000c) >> 2);

	return clk->parent->rate / ifc_divisors[idx];
}

<<<<<<< HEAD
static struct sh_clk_ops sh3_cpu_clk_ops = {
	.recalc		= cpu_clk_recalc,
};

static struct sh_clk_ops *sh3_clk_ops[] = {
=======
static struct clk_ops sh3_cpu_clk_ops = {
	.recalc		= cpu_clk_recalc,
};

static struct clk_ops *sh3_clk_ops[] = {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	&sh3_master_clk_ops,
	&sh3_module_clk_ops,
	&sh3_bus_clk_ops,
	&sh3_cpu_clk_ops,
};

<<<<<<< HEAD
void __init arch_init_clk_ops(struct sh_clk_ops **ops, int idx)
=======
void __init arch_init_clk_ops(struct clk_ops **ops, int idx)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	if (idx < ARRAY_SIZE(sh3_clk_ops))
		*ops = sh3_clk_ops[idx];
}

