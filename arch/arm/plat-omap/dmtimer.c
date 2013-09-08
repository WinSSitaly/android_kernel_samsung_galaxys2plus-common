/*
 * linux/arch/arm/plat-omap/dmtimer.c
 *
 * OMAP Dual-Mode Timers
 *
<<<<<<< HEAD
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * Tarun Kanti DebBarma <tarun.kanti@ti.com>
 * Thara Gopinath <thara@ti.com>
 *
 * dmtimer adaptation to platform_driver.
 *
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
 * Copyright (C) 2005 Nokia Corporation
 * OMAP2 support by Juha Yrjola
 * API improvements and OMAP2 clock framework support by Timo Teras
 *
 * Copyright (C) 2009 Texas Instruments
 * Added OMAP4 support - Santosh Shilimkar <santosh.shilimkar@ti.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You should have received a copy of the  GNU General Public License along
 * with this program; if not, write  to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */

<<<<<<< HEAD
#include <linux/module.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/pm_runtime.h>

#include <plat/dmtimer.h>

#include <mach/hardware.h>

static LIST_HEAD(omap_timer_list);
static DEFINE_SPINLOCK(dm_timer_lock);

/**
 * omap_dm_timer_read_reg - read timer registers in posted and non-posted mode
 * @timer:      timer pointer over which read operation to perform
 * @reg:        lowest byte holds the register offset
 *
 * The posted mode bit is encoded in reg. Note that in posted mode write
 * pending bit must be checked. Otherwise a read of a non completed write
 * will produce an error.
 */
static inline u32 omap_dm_timer_read_reg(struct omap_dm_timer *timer, u32 reg)
{
	WARN_ON((reg & 0xff) < _OMAP_TIMER_WAKEUP_EN_OFFSET);
	return __omap_dm_timer_read(timer, reg, timer->posted);
}

/**
 * omap_dm_timer_write_reg - write timer registers in posted and non-posted mode
 * @timer:      timer pointer over which write operation is to perform
 * @reg:        lowest byte holds the register offset
 * @value:      data to write into the register
 *
 * The posted mode bit is encoded in reg. Note that in posted mode the write
 * pending bit must be checked. Otherwise a write on a register which has a
 * pending write will be lost.
=======
#include <linux/init.h>
#include <linux/spinlock.h>
#include <linux/errno.h>
#include <linux/list.h>
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/module.h>
#include <mach/hardware.h>
#include <plat/dmtimer.h>
#include <mach/irqs.h>

/* register offsets */
#define _OMAP_TIMER_ID_OFFSET		0x00
#define _OMAP_TIMER_OCP_CFG_OFFSET	0x10
#define _OMAP_TIMER_SYS_STAT_OFFSET	0x14
#define _OMAP_TIMER_STAT_OFFSET		0x18
#define _OMAP_TIMER_INT_EN_OFFSET	0x1c
#define _OMAP_TIMER_WAKEUP_EN_OFFSET	0x20
#define _OMAP_TIMER_CTRL_OFFSET		0x24
#define		OMAP_TIMER_CTRL_GPOCFG		(1 << 14)
#define		OMAP_TIMER_CTRL_CAPTMODE	(1 << 13)
#define		OMAP_TIMER_CTRL_PT		(1 << 12)
#define		OMAP_TIMER_CTRL_TCM_LOWTOHIGH	(0x1 << 8)
#define		OMAP_TIMER_CTRL_TCM_HIGHTOLOW	(0x2 << 8)
#define		OMAP_TIMER_CTRL_TCM_BOTHEDGES	(0x3 << 8)
#define		OMAP_TIMER_CTRL_SCPWM		(1 << 7)
#define		OMAP_TIMER_CTRL_CE		(1 << 6) /* compare enable */
#define		OMAP_TIMER_CTRL_PRE		(1 << 5) /* prescaler enable */
#define		OMAP_TIMER_CTRL_PTV_SHIFT	2 /* prescaler value shift */
#define		OMAP_TIMER_CTRL_POSTED		(1 << 2)
#define		OMAP_TIMER_CTRL_AR		(1 << 1) /* auto-reload enable */
#define		OMAP_TIMER_CTRL_ST		(1 << 0) /* start timer */
#define _OMAP_TIMER_COUNTER_OFFSET	0x28
#define _OMAP_TIMER_LOAD_OFFSET		0x2c
#define _OMAP_TIMER_TRIGGER_OFFSET	0x30
#define _OMAP_TIMER_WRITE_PEND_OFFSET	0x34
#define		WP_NONE			0	/* no write pending bit */
#define		WP_TCLR			(1 << 0)
#define		WP_TCRR			(1 << 1)
#define		WP_TLDR			(1 << 2)
#define		WP_TTGR			(1 << 3)
#define		WP_TMAR			(1 << 4)
#define		WP_TPIR			(1 << 5)
#define		WP_TNIR			(1 << 6)
#define		WP_TCVR			(1 << 7)
#define		WP_TOCR			(1 << 8)
#define		WP_TOWR			(1 << 9)
#define _OMAP_TIMER_MATCH_OFFSET	0x38
#define _OMAP_TIMER_CAPTURE_OFFSET	0x3c
#define _OMAP_TIMER_IF_CTRL_OFFSET	0x40
#define _OMAP_TIMER_CAPTURE2_OFFSET		0x44	/* TCAR2, 34xx only */
#define _OMAP_TIMER_TICK_POS_OFFSET		0x48	/* TPIR, 34xx only */
#define _OMAP_TIMER_TICK_NEG_OFFSET		0x4c	/* TNIR, 34xx only */
#define _OMAP_TIMER_TICK_COUNT_OFFSET		0x50	/* TCVR, 34xx only */
#define _OMAP_TIMER_TICK_INT_MASK_SET_OFFSET	0x54	/* TOCR, 34xx only */
#define _OMAP_TIMER_TICK_INT_MASK_COUNT_OFFSET	0x58	/* TOWR, 34xx only */

/* register offsets with the write pending bit encoded */
#define	WPSHIFT					16

#define OMAP_TIMER_ID_REG			(_OMAP_TIMER_ID_OFFSET \
							| (WP_NONE << WPSHIFT))

#define OMAP_TIMER_OCP_CFG_REG			(_OMAP_TIMER_OCP_CFG_OFFSET \
							| (WP_NONE << WPSHIFT))

#define OMAP_TIMER_SYS_STAT_REG			(_OMAP_TIMER_SYS_STAT_OFFSET \
							| (WP_NONE << WPSHIFT))

#define OMAP_TIMER_STAT_REG			(_OMAP_TIMER_STAT_OFFSET \
							| (WP_NONE << WPSHIFT))

#define OMAP_TIMER_INT_EN_REG			(_OMAP_TIMER_INT_EN_OFFSET \
							| (WP_NONE << WPSHIFT))

#define OMAP_TIMER_WAKEUP_EN_REG		(_OMAP_TIMER_WAKEUP_EN_OFFSET \
							| (WP_NONE << WPSHIFT))

#define OMAP_TIMER_CTRL_REG			(_OMAP_TIMER_CTRL_OFFSET \
							| (WP_TCLR << WPSHIFT))

#define OMAP_TIMER_COUNTER_REG			(_OMAP_TIMER_COUNTER_OFFSET \
							| (WP_TCRR << WPSHIFT))

#define OMAP_TIMER_LOAD_REG			(_OMAP_TIMER_LOAD_OFFSET \
							| (WP_TLDR << WPSHIFT))

#define OMAP_TIMER_TRIGGER_REG			(_OMAP_TIMER_TRIGGER_OFFSET \
							| (WP_TTGR << WPSHIFT))

#define OMAP_TIMER_WRITE_PEND_REG		(_OMAP_TIMER_WRITE_PEND_OFFSET \
							| (WP_NONE << WPSHIFT))

#define OMAP_TIMER_MATCH_REG			(_OMAP_TIMER_MATCH_OFFSET \
							| (WP_TMAR << WPSHIFT))

#define OMAP_TIMER_CAPTURE_REG			(_OMAP_TIMER_CAPTURE_OFFSET \
							| (WP_NONE << WPSHIFT))

#define OMAP_TIMER_IF_CTRL_REG			(_OMAP_TIMER_IF_CTRL_OFFSET \
							| (WP_NONE << WPSHIFT))

#define OMAP_TIMER_CAPTURE2_REG			(_OMAP_TIMER_CAPTURE2_OFFSET \
							| (WP_NONE << WPSHIFT))

#define OMAP_TIMER_TICK_POS_REG			(_OMAP_TIMER_TICK_POS_OFFSET \
							| (WP_TPIR << WPSHIFT))

#define OMAP_TIMER_TICK_NEG_REG			(_OMAP_TIMER_TICK_NEG_OFFSET \
							| (WP_TNIR << WPSHIFT))

#define OMAP_TIMER_TICK_COUNT_REG		(_OMAP_TIMER_TICK_COUNT_OFFSET \
							| (WP_TCVR << WPSHIFT))

#define OMAP_TIMER_TICK_INT_MASK_SET_REG				\
		(_OMAP_TIMER_TICK_INT_MASK_SET_OFFSET | (WP_TOCR << WPSHIFT))

#define OMAP_TIMER_TICK_INT_MASK_COUNT_REG				\
		(_OMAP_TIMER_TICK_INT_MASK_COUNT_OFFSET | (WP_TOWR << WPSHIFT))

struct omap_dm_timer {
	unsigned long phys_base;
	int irq;
#ifdef CONFIG_ARCH_OMAP2PLUS
	struct clk *iclk, *fclk;
#endif
	void __iomem *io_base;
	unsigned reserved:1;
	unsigned enabled:1;
	unsigned posted:1;
};

static int dm_timer_count;

#ifdef CONFIG_ARCH_OMAP1
static struct omap_dm_timer omap1_dm_timers[] = {
	{ .phys_base = 0xfffb1400, .irq = INT_1610_GPTIMER1 },
	{ .phys_base = 0xfffb1c00, .irq = INT_1610_GPTIMER2 },
	{ .phys_base = 0xfffb2400, .irq = INT_1610_GPTIMER3 },
	{ .phys_base = 0xfffb2c00, .irq = INT_1610_GPTIMER4 },
	{ .phys_base = 0xfffb3400, .irq = INT_1610_GPTIMER5 },
	{ .phys_base = 0xfffb3c00, .irq = INT_1610_GPTIMER6 },
	{ .phys_base = 0xfffb7400, .irq = INT_1610_GPTIMER7 },
	{ .phys_base = 0xfffbd400, .irq = INT_1610_GPTIMER8 },
};

static const int omap1_dm_timer_count = ARRAY_SIZE(omap1_dm_timers);

#else
#define omap1_dm_timers			NULL
#define omap1_dm_timer_count		0
#endif	/* CONFIG_ARCH_OMAP1 */

#ifdef CONFIG_ARCH_OMAP2
static struct omap_dm_timer omap2_dm_timers[] = {
	{ .phys_base = 0x48028000, .irq = INT_24XX_GPTIMER1 },
	{ .phys_base = 0x4802a000, .irq = INT_24XX_GPTIMER2 },
	{ .phys_base = 0x48078000, .irq = INT_24XX_GPTIMER3 },
	{ .phys_base = 0x4807a000, .irq = INT_24XX_GPTIMER4 },
	{ .phys_base = 0x4807c000, .irq = INT_24XX_GPTIMER5 },
	{ .phys_base = 0x4807e000, .irq = INT_24XX_GPTIMER6 },
	{ .phys_base = 0x48080000, .irq = INT_24XX_GPTIMER7 },
	{ .phys_base = 0x48082000, .irq = INT_24XX_GPTIMER8 },
	{ .phys_base = 0x48084000, .irq = INT_24XX_GPTIMER9 },
	{ .phys_base = 0x48086000, .irq = INT_24XX_GPTIMER10 },
	{ .phys_base = 0x48088000, .irq = INT_24XX_GPTIMER11 },
	{ .phys_base = 0x4808a000, .irq = INT_24XX_GPTIMER12 },
};

static const char *omap2_dm_source_names[] __initdata = {
	"sys_ck",
	"func_32k_ck",
	"alt_ck",
	NULL
};

static struct clk *omap2_dm_source_clocks[3];
static const int omap2_dm_timer_count = ARRAY_SIZE(omap2_dm_timers);

#else
#define omap2_dm_timers			NULL
#define omap2_dm_timer_count		0
#define omap2_dm_source_names		NULL
#define omap2_dm_source_clocks		NULL
#endif	/* CONFIG_ARCH_OMAP2 */

#ifdef CONFIG_ARCH_OMAP3
static struct omap_dm_timer omap3_dm_timers[] = {
	{ .phys_base = 0x48318000, .irq = INT_24XX_GPTIMER1 },
	{ .phys_base = 0x49032000, .irq = INT_24XX_GPTIMER2 },
	{ .phys_base = 0x49034000, .irq = INT_24XX_GPTIMER3 },
	{ .phys_base = 0x49036000, .irq = INT_24XX_GPTIMER4 },
	{ .phys_base = 0x49038000, .irq = INT_24XX_GPTIMER5 },
	{ .phys_base = 0x4903A000, .irq = INT_24XX_GPTIMER6 },
	{ .phys_base = 0x4903C000, .irq = INT_24XX_GPTIMER7 },
	{ .phys_base = 0x4903E000, .irq = INT_24XX_GPTIMER8 },
	{ .phys_base = 0x49040000, .irq = INT_24XX_GPTIMER9 },
	{ .phys_base = 0x48086000, .irq = INT_24XX_GPTIMER10 },
	{ .phys_base = 0x48088000, .irq = INT_24XX_GPTIMER11 },
	{ .phys_base = 0x48304000, .irq = INT_34XX_GPT12_IRQ },
};

static const char *omap3_dm_source_names[] __initdata = {
	"sys_ck",
	"omap_32k_fck",
	NULL
};

static struct clk *omap3_dm_source_clocks[2];
static const int omap3_dm_timer_count = ARRAY_SIZE(omap3_dm_timers);

#else
#define omap3_dm_timers			NULL
#define omap3_dm_timer_count		0
#define omap3_dm_source_names		NULL
#define omap3_dm_source_clocks		NULL
#endif	/* CONFIG_ARCH_OMAP3 */

#ifdef CONFIG_ARCH_OMAP4
static struct omap_dm_timer omap4_dm_timers[] = {
	{ .phys_base = 0x4a318000, .irq = OMAP44XX_IRQ_GPT1 },
	{ .phys_base = 0x48032000, .irq = OMAP44XX_IRQ_GPT2 },
	{ .phys_base = 0x48034000, .irq = OMAP44XX_IRQ_GPT3 },
	{ .phys_base = 0x48036000, .irq = OMAP44XX_IRQ_GPT4 },
	{ .phys_base = 0x40138000, .irq = OMAP44XX_IRQ_GPT5 },
	{ .phys_base = 0x4013a000, .irq = OMAP44XX_IRQ_GPT6 },
	{ .phys_base = 0x4013a000, .irq = OMAP44XX_IRQ_GPT7 },
	{ .phys_base = 0x4013e000, .irq = OMAP44XX_IRQ_GPT8 },
	{ .phys_base = 0x4803e000, .irq = OMAP44XX_IRQ_GPT9 },
	{ .phys_base = 0x48086000, .irq = OMAP44XX_IRQ_GPT10 },
	{ .phys_base = 0x48088000, .irq = OMAP44XX_IRQ_GPT11 },
	{ .phys_base = 0x4a320000, .irq = OMAP44XX_IRQ_GPT12 },
};
static const char *omap4_dm_source_names[] __initdata = {
	"sys_clkin_ck",
	"sys_32k_ck",
	NULL
};
static struct clk *omap4_dm_source_clocks[2];
static const int omap4_dm_timer_count = ARRAY_SIZE(omap4_dm_timers);

#else
#define omap4_dm_timers			NULL
#define omap4_dm_timer_count		0
#define omap4_dm_source_names		NULL
#define omap4_dm_source_clocks		NULL
#endif	/* CONFIG_ARCH_OMAP4 */

static struct omap_dm_timer *dm_timers;
static const char **dm_source_names;
static struct clk **dm_source_clocks;

static spinlock_t dm_timer_lock;

/*
 * Reads timer registers in posted and non-posted mode. The posted mode bit
 * is encoded in reg. Note that in posted mode write pending bit must be
 * checked. Otherwise a read of a non completed write will produce an error.
 */
static inline u32 omap_dm_timer_read_reg(struct omap_dm_timer *timer, u32 reg)
{
	if (timer->posted)
		while (readl(timer->io_base + (OMAP_TIMER_WRITE_PEND_REG & 0xff))
				& (reg >> WPSHIFT))
			cpu_relax();
	return readl(timer->io_base + (reg & 0xff));
}

/*
 * Writes timer registers in posted and non-posted mode. The posted mode bit
 * is encoded in reg. Note that in posted mode the write pending bit must be
 * checked. Otherwise a write on a register which has a pending write will be
 * lost.
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
 */
static void omap_dm_timer_write_reg(struct omap_dm_timer *timer, u32 reg,
						u32 value)
{
<<<<<<< HEAD
	WARN_ON((reg & 0xff) < _OMAP_TIMER_WAKEUP_EN_OFFSET);
	__omap_dm_timer_write(timer, reg, value, timer->posted);
}

static void omap_timer_restore_context(struct omap_dm_timer *timer)
{
	__raw_writel(timer->context.tiocp_cfg,
			timer->io_base + OMAP_TIMER_OCP_CFG_OFFSET);
	if (timer->revision == 1)
		__raw_writel(timer->context.tistat, timer->sys_stat);

	__raw_writel(timer->context.tisr, timer->irq_stat);
	omap_dm_timer_write_reg(timer, OMAP_TIMER_WAKEUP_EN_REG,
				timer->context.twer);
	omap_dm_timer_write_reg(timer, OMAP_TIMER_COUNTER_REG,
				timer->context.tcrr);
	omap_dm_timer_write_reg(timer, OMAP_TIMER_LOAD_REG,
				timer->context.tldr);
	omap_dm_timer_write_reg(timer, OMAP_TIMER_MATCH_REG,
				timer->context.tmar);
	omap_dm_timer_write_reg(timer, OMAP_TIMER_IF_CTRL_REG,
				timer->context.tsicr);
	__raw_writel(timer->context.tier, timer->irq_ena);
	omap_dm_timer_write_reg(timer, OMAP_TIMER_CTRL_REG,
				timer->context.tclr);
=======
	if (timer->posted)
		while (readl(timer->io_base + (OMAP_TIMER_WRITE_PEND_REG & 0xff))
				& (reg >> WPSHIFT))
			cpu_relax();
	writel(value, timer->io_base + (reg & 0xff));
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

static void omap_dm_timer_wait_for_reset(struct omap_dm_timer *timer)
{
	int c;

<<<<<<< HEAD
	if (!timer->sys_stat)
		return;

	c = 0;
	while (!(__raw_readl(timer->sys_stat) & 1)) {
=======
	c = 0;
	while (!(omap_dm_timer_read_reg(timer, OMAP_TIMER_SYS_STAT_REG) & 1)) {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		c++;
		if (c > 100000) {
			printk(KERN_ERR "Timer failed to reset\n");
			return;
		}
	}
}

static void omap_dm_timer_reset(struct omap_dm_timer *timer)
{
<<<<<<< HEAD
	omap_dm_timer_enable(timer);
	if (timer->pdev->id != 1) {
		omap_dm_timer_write_reg(timer, OMAP_TIMER_IF_CTRL_REG, 0x06);
		omap_dm_timer_wait_for_reset(timer);
	}

	__omap_dm_timer_reset(timer, 0, 0);
	omap_dm_timer_disable(timer);
	timer->posted = 1;
}

int omap_dm_timer_prepare(struct omap_dm_timer *timer)
{
	struct dmtimer_platform_data *pdata = timer->pdev->dev.platform_data;
	int ret;

	timer->fclk = clk_get(&timer->pdev->dev, "fck");
	if (WARN_ON_ONCE(IS_ERR_OR_NULL(timer->fclk))) {
		timer->fclk = NULL;
		dev_err(&timer->pdev->dev, ": No fclk handle.\n");
		return -EINVAL;
	}

	if (pdata->needs_manual_reset)
		omap_dm_timer_reset(timer);

	ret = omap_dm_timer_set_source(timer, OMAP_TIMER_SRC_32_KHZ);

	timer->posted = 1;
	return ret;
=======
	u32 l;

	if (!cpu_class_is_omap2() || timer != &dm_timers[0]) {
		omap_dm_timer_write_reg(timer, OMAP_TIMER_IF_CTRL_REG, 0x06);
		omap_dm_timer_wait_for_reset(timer);
	}
	omap_dm_timer_set_source(timer, OMAP_TIMER_SRC_32_KHZ);

	l = omap_dm_timer_read_reg(timer, OMAP_TIMER_OCP_CFG_REG);
	l |= 0x02 << 3;  /* Set to smart-idle mode */
	l |= 0x2 << 8;   /* Set clock activity to perserve f-clock on idle */

	/* Enable autoidle on OMAP2 / OMAP3 */
	if (cpu_is_omap24xx() || cpu_is_omap34xx())
		l |= 0x1 << 0;

	/*
	 * Enable wake-up on OMAP2 CPUs.
	 */
	if (cpu_class_is_omap2())
		l |= 1 << 2;
	omap_dm_timer_write_reg(timer, OMAP_TIMER_OCP_CFG_REG, l);

	/* Match hardware reset default of posted mode */
	omap_dm_timer_write_reg(timer, OMAP_TIMER_IF_CTRL_REG,
			OMAP_TIMER_CTRL_POSTED);
	timer->posted = 1;
}

static void omap_dm_timer_prepare(struct omap_dm_timer *timer)
{
	omap_dm_timer_enable(timer);
	omap_dm_timer_reset(timer);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

struct omap_dm_timer *omap_dm_timer_request(void)
{
<<<<<<< HEAD
	struct omap_dm_timer *timer = NULL, *t;
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&dm_timer_lock, flags);
	list_for_each_entry(t, &omap_timer_list, node) {
		if (t->reserved)
			continue;

		timer = t;
		timer->reserved = 1;
		break;
	}

	if (timer) {
		ret = omap_dm_timer_prepare(timer);
		if (ret) {
			timer->reserved = 0;
			timer = NULL;
		}
	}
	spin_unlock_irqrestore(&dm_timer_lock, flags);

	if (!timer)
		pr_debug("%s: timer request failed!\n", __func__);
=======
	struct omap_dm_timer *timer = NULL;
	unsigned long flags;
	int i;

	spin_lock_irqsave(&dm_timer_lock, flags);
	for (i = 0; i < dm_timer_count; i++) {
		if (dm_timers[i].reserved)
			continue;

		timer = &dm_timers[i];
		timer->reserved = 1;
		break;
	}
	spin_unlock_irqrestore(&dm_timer_lock, flags);

	if (timer != NULL)
		omap_dm_timer_prepare(timer);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	return timer;
}
EXPORT_SYMBOL_GPL(omap_dm_timer_request);

struct omap_dm_timer *omap_dm_timer_request_specific(int id)
{
<<<<<<< HEAD
	struct omap_dm_timer *timer = NULL, *t;
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&dm_timer_lock, flags);
	list_for_each_entry(t, &omap_timer_list, node) {
		if (t->pdev->id == id && !t->reserved) {
			timer = t;
			timer->reserved = 1;
			break;
		}
	}

	if (timer) {
		ret = omap_dm_timer_prepare(timer);
		if (ret) {
			timer->reserved = 0;
			timer = NULL;
		}
	}
	spin_unlock_irqrestore(&dm_timer_lock, flags);

	if (!timer)
		pr_debug("%s: timer%d request failed!\n", __func__, id);
=======
	struct omap_dm_timer *timer;
	unsigned long flags;

	spin_lock_irqsave(&dm_timer_lock, flags);
	if (id <= 0 || id > dm_timer_count || dm_timers[id-1].reserved) {
		spin_unlock_irqrestore(&dm_timer_lock, flags);
		printk("BUG: warning at %s:%d/%s(): unable to get timer %d\n",
		       __FILE__, __LINE__, __func__, id);
		dump_stack();
		return NULL;
	}

	timer = &dm_timers[id-1];
	timer->reserved = 1;
	spin_unlock_irqrestore(&dm_timer_lock, flags);

	omap_dm_timer_prepare(timer);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	return timer;
}
EXPORT_SYMBOL_GPL(omap_dm_timer_request_specific);

<<<<<<< HEAD
int omap_dm_timer_free(struct omap_dm_timer *timer)
{
	if (unlikely(!timer))
		return -EINVAL;

	clk_put(timer->fclk);

	WARN_ON(!timer->reserved);
	timer->reserved = 0;
	return 0;
=======
void omap_dm_timer_free(struct omap_dm_timer *timer)
{
	omap_dm_timer_enable(timer);
	omap_dm_timer_reset(timer);
	omap_dm_timer_disable(timer);

	WARN_ON(!timer->reserved);
	timer->reserved = 0;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}
EXPORT_SYMBOL_GPL(omap_dm_timer_free);

void omap_dm_timer_enable(struct omap_dm_timer *timer)
{
<<<<<<< HEAD
	pm_runtime_get_sync(&timer->pdev->dev);
=======
	if (timer->enabled)
		return;

#ifdef CONFIG_ARCH_OMAP2PLUS
	if (cpu_class_is_omap2()) {
		clk_enable(timer->fclk);
		clk_enable(timer->iclk);
	}
#endif

	timer->enabled = 1;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}
EXPORT_SYMBOL_GPL(omap_dm_timer_enable);

void omap_dm_timer_disable(struct omap_dm_timer *timer)
{
<<<<<<< HEAD
	pm_runtime_put_sync(&timer->pdev->dev);
=======
	if (!timer->enabled)
		return;

#ifdef CONFIG_ARCH_OMAP2PLUS
	if (cpu_class_is_omap2()) {
		clk_disable(timer->iclk);
		clk_disable(timer->fclk);
	}
#endif

	timer->enabled = 0;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}
EXPORT_SYMBOL_GPL(omap_dm_timer_disable);

int omap_dm_timer_get_irq(struct omap_dm_timer *timer)
{
<<<<<<< HEAD
	if (timer)
		return timer->irq;
	return -EINVAL;
=======
	return timer->irq;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}
EXPORT_SYMBOL_GPL(omap_dm_timer_get_irq);

#if defined(CONFIG_ARCH_OMAP1)

/**
 * omap_dm_timer_modify_idlect_mask - Check if any running timers use ARMXOR
 * @inputmask: current value of idlect mask
 */
__u32 omap_dm_timer_modify_idlect_mask(__u32 inputmask)
{
<<<<<<< HEAD
	int i = 0;
	struct omap_dm_timer *timer = NULL;
	unsigned long flags;
=======
	int i;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	/* If ARMXOR cannot be idled this function call is unnecessary */
	if (!(inputmask & (1 << 1)))
		return inputmask;

	/* If any active timer is using ARMXOR return modified mask */
<<<<<<< HEAD
	spin_lock_irqsave(&dm_timer_lock, flags);
	list_for_each_entry(timer, &omap_timer_list, node) {
		u32 l;

		l = omap_dm_timer_read_reg(timer, OMAP_TIMER_CTRL_REG);
=======
	for (i = 0; i < dm_timer_count; i++) {
		u32 l;

		l = omap_dm_timer_read_reg(&dm_timers[i], OMAP_TIMER_CTRL_REG);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		if (l & OMAP_TIMER_CTRL_ST) {
			if (((omap_readl(MOD_CONF_CTRL_1) >> (i * 2)) & 0x03) == 0)
				inputmask &= ~(1 << 1);
			else
				inputmask &= ~(1 << 2);
		}
<<<<<<< HEAD
		i++;
	}
	spin_unlock_irqrestore(&dm_timer_lock, flags);
=======
	}
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	return inputmask;
}
EXPORT_SYMBOL_GPL(omap_dm_timer_modify_idlect_mask);

#else

struct clk *omap_dm_timer_get_fclk(struct omap_dm_timer *timer)
{
<<<<<<< HEAD
	if (timer)
		return timer->fclk;
	return NULL;
=======
	return timer->fclk;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}
EXPORT_SYMBOL_GPL(omap_dm_timer_get_fclk);

__u32 omap_dm_timer_modify_idlect_mask(__u32 inputmask)
{
	BUG();

	return 0;
}
EXPORT_SYMBOL_GPL(omap_dm_timer_modify_idlect_mask);

#endif

<<<<<<< HEAD
int omap_dm_timer_trigger(struct omap_dm_timer *timer)
{
	if (unlikely(!timer || pm_runtime_suspended(&timer->pdev->dev))) {
		pr_err("%s: timer not available or enabled.\n", __func__);
		return -EINVAL;
	}

	omap_dm_timer_write_reg(timer, OMAP_TIMER_TRIGGER_REG, 0);
	return 0;
}
EXPORT_SYMBOL_GPL(omap_dm_timer_trigger);

int omap_dm_timer_start(struct omap_dm_timer *timer)
{
	u32 l;

	if (unlikely(!timer))
		return -EINVAL;

	omap_dm_timer_enable(timer);

	if (timer->loses_context) {
		u32 ctx_loss_cnt_after =
			timer->get_context_loss_count(&timer->pdev->dev);
		if (ctx_loss_cnt_after != timer->ctx_loss_count)
			omap_timer_restore_context(timer);
	}

=======
void omap_dm_timer_trigger(struct omap_dm_timer *timer)
{
	omap_dm_timer_write_reg(timer, OMAP_TIMER_TRIGGER_REG, 0);
}
EXPORT_SYMBOL_GPL(omap_dm_timer_trigger);

void omap_dm_timer_start(struct omap_dm_timer *timer)
{
	u32 l;

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	l = omap_dm_timer_read_reg(timer, OMAP_TIMER_CTRL_REG);
	if (!(l & OMAP_TIMER_CTRL_ST)) {
		l |= OMAP_TIMER_CTRL_ST;
		omap_dm_timer_write_reg(timer, OMAP_TIMER_CTRL_REG, l);
	}
<<<<<<< HEAD

	/* Save the context */
	timer->context.tclr = l;
	return 0;
}
EXPORT_SYMBOL_GPL(omap_dm_timer_start);

int omap_dm_timer_stop(struct omap_dm_timer *timer)
{
	unsigned long rate = 0;
	struct dmtimer_platform_data *pdata = timer->pdev->dev.platform_data;

	if (unlikely(!timer))
		return -EINVAL;

	if (!pdata->needs_manual_reset)
		rate = clk_get_rate(timer->fclk);

	__omap_dm_timer_stop(timer, timer->posted, rate);

	if (timer->loses_context && timer->get_context_loss_count)
		timer->ctx_loss_count =
			timer->get_context_loss_count(&timer->pdev->dev);

	/*
	 * Since the register values are computed and written within
	 * __omap_dm_timer_stop, we need to use read to retrieve the
	 * context.
	 */
	timer->context.tclr =
			omap_dm_timer_read_reg(timer, OMAP_TIMER_CTRL_REG);
	timer->context.tisr = __raw_readl(timer->irq_stat);
	omap_dm_timer_disable(timer);
	return 0;
}
EXPORT_SYMBOL_GPL(omap_dm_timer_stop);

int omap_dm_timer_set_source(struct omap_dm_timer *timer, int source)
{
	int ret;
	struct dmtimer_platform_data *pdata;

	if (unlikely(!timer))
		return -EINVAL;

	pdata = timer->pdev->dev.platform_data;
=======
}
EXPORT_SYMBOL_GPL(omap_dm_timer_start);

void omap_dm_timer_stop(struct omap_dm_timer *timer)
{
	u32 l;

	l = omap_dm_timer_read_reg(timer, OMAP_TIMER_CTRL_REG);
	if (l & OMAP_TIMER_CTRL_ST) {
		l &= ~0x1;
		omap_dm_timer_write_reg(timer, OMAP_TIMER_CTRL_REG, l);
#ifdef CONFIG_ARCH_OMAP2PLUS
		/* Readback to make sure write has completed */
		omap_dm_timer_read_reg(timer, OMAP_TIMER_CTRL_REG);
		 /*
		  * Wait for functional clock period x 3.5 to make sure that
		  * timer is stopped
		  */
		udelay(3500000 / clk_get_rate(timer->fclk) + 1);
#endif
	}
	/* Ack possibly pending interrupt */
	omap_dm_timer_write_reg(timer, OMAP_TIMER_STAT_REG,
			OMAP_TIMER_INT_OVERFLOW);
}
EXPORT_SYMBOL_GPL(omap_dm_timer_stop);

#ifdef CONFIG_ARCH_OMAP1

int omap_dm_timer_set_source(struct omap_dm_timer *timer, int source)
{
	int n = (timer - dm_timers) << 1;
	u32 l;

	l = omap_readl(MOD_CONF_CTRL_1) & ~(0x03 << n);
	l |= source << n;
	omap_writel(l, MOD_CONF_CTRL_1);

	return 0;
}
EXPORT_SYMBOL_GPL(omap_dm_timer_set_source);

#else

int omap_dm_timer_set_source(struct omap_dm_timer *timer, int source)
{
	int ret = -EINVAL;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	if (source < 0 || source >= 3)
		return -EINVAL;

<<<<<<< HEAD
	ret = pdata->set_timer_src(timer->pdev, source);
=======
	clk_disable(timer->fclk);
	ret = clk_set_parent(timer->fclk, dm_source_clocks[source]);
	clk_enable(timer->fclk);

	/*
	 * When the functional clock disappears, too quick writes seem
	 * to cause an abort. XXX Is this still necessary?
	 */
	__delay(300000);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	return ret;
}
EXPORT_SYMBOL_GPL(omap_dm_timer_set_source);

<<<<<<< HEAD
int omap_dm_timer_set_load(struct omap_dm_timer *timer, int autoreload,
=======
#endif

void omap_dm_timer_set_load(struct omap_dm_timer *timer, int autoreload,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			    unsigned int load)
{
	u32 l;

<<<<<<< HEAD
	if (unlikely(!timer))
		return -EINVAL;

	omap_dm_timer_enable(timer);
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	l = omap_dm_timer_read_reg(timer, OMAP_TIMER_CTRL_REG);
	if (autoreload)
		l |= OMAP_TIMER_CTRL_AR;
	else
		l &= ~OMAP_TIMER_CTRL_AR;
	omap_dm_timer_write_reg(timer, OMAP_TIMER_CTRL_REG, l);
	omap_dm_timer_write_reg(timer, OMAP_TIMER_LOAD_REG, load);

	omap_dm_timer_write_reg(timer, OMAP_TIMER_TRIGGER_REG, 0);
<<<<<<< HEAD
	/* Save the context */
	timer->context.tclr = l;
	timer->context.tldr = load;
	omap_dm_timer_disable(timer);
	return 0;
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}
EXPORT_SYMBOL_GPL(omap_dm_timer_set_load);

/* Optimized set_load which removes costly spin wait in timer_start */
<<<<<<< HEAD
int omap_dm_timer_set_load_start(struct omap_dm_timer *timer, int autoreload,
=======
void omap_dm_timer_set_load_start(struct omap_dm_timer *timer, int autoreload,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
                            unsigned int load)
{
	u32 l;

<<<<<<< HEAD
	if (unlikely(!timer))
		return -EINVAL;

	omap_dm_timer_enable(timer);

	if (timer->loses_context) {
		u32 ctx_loss_cnt_after =
			timer->get_context_loss_count(&timer->pdev->dev);
		if (ctx_loss_cnt_after != timer->ctx_loss_count)
			omap_timer_restore_context(timer);
	}

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	l = omap_dm_timer_read_reg(timer, OMAP_TIMER_CTRL_REG);
	if (autoreload) {
		l |= OMAP_TIMER_CTRL_AR;
		omap_dm_timer_write_reg(timer, OMAP_TIMER_LOAD_REG, load);
	} else {
		l &= ~OMAP_TIMER_CTRL_AR;
	}
	l |= OMAP_TIMER_CTRL_ST;

<<<<<<< HEAD
	__omap_dm_timer_load_start(timer, l, load, timer->posted);

	/* Save the context */
	timer->context.tclr = l;
	timer->context.tldr = load;
	timer->context.tcrr = load;
	return 0;
}
EXPORT_SYMBOL_GPL(omap_dm_timer_set_load_start);

int omap_dm_timer_set_match(struct omap_dm_timer *timer, int enable,
=======
	omap_dm_timer_write_reg(timer, OMAP_TIMER_COUNTER_REG, load);
	omap_dm_timer_write_reg(timer, OMAP_TIMER_CTRL_REG, l);
}
EXPORT_SYMBOL_GPL(omap_dm_timer_set_load_start);

void omap_dm_timer_set_match(struct omap_dm_timer *timer, int enable,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			     unsigned int match)
{
	u32 l;

<<<<<<< HEAD
	if (unlikely(!timer))
		return -EINVAL;

	omap_dm_timer_enable(timer);
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	l = omap_dm_timer_read_reg(timer, OMAP_TIMER_CTRL_REG);
	if (enable)
		l |= OMAP_TIMER_CTRL_CE;
	else
		l &= ~OMAP_TIMER_CTRL_CE;
	omap_dm_timer_write_reg(timer, OMAP_TIMER_CTRL_REG, l);
	omap_dm_timer_write_reg(timer, OMAP_TIMER_MATCH_REG, match);
<<<<<<< HEAD

	/* Save the context */
	timer->context.tclr = l;
	timer->context.tmar = match;
	omap_dm_timer_disable(timer);
	return 0;
}
EXPORT_SYMBOL_GPL(omap_dm_timer_set_match);

int omap_dm_timer_set_pwm(struct omap_dm_timer *timer, int def_on,
=======
}
EXPORT_SYMBOL_GPL(omap_dm_timer_set_match);

void omap_dm_timer_set_pwm(struct omap_dm_timer *timer, int def_on,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			   int toggle, int trigger)
{
	u32 l;

<<<<<<< HEAD
	if (unlikely(!timer))
		return -EINVAL;

	omap_dm_timer_enable(timer);
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	l = omap_dm_timer_read_reg(timer, OMAP_TIMER_CTRL_REG);
	l &= ~(OMAP_TIMER_CTRL_GPOCFG | OMAP_TIMER_CTRL_SCPWM |
	       OMAP_TIMER_CTRL_PT | (0x03 << 10));
	if (def_on)
		l |= OMAP_TIMER_CTRL_SCPWM;
	if (toggle)
		l |= OMAP_TIMER_CTRL_PT;
	l |= trigger << 10;
	omap_dm_timer_write_reg(timer, OMAP_TIMER_CTRL_REG, l);
<<<<<<< HEAD

	/* Save the context */
	timer->context.tclr = l;
	omap_dm_timer_disable(timer);
	return 0;
}
EXPORT_SYMBOL_GPL(omap_dm_timer_set_pwm);

int omap_dm_timer_set_prescaler(struct omap_dm_timer *timer, int prescaler)
{
	u32 l;

	if (unlikely(!timer))
		return -EINVAL;

	omap_dm_timer_enable(timer);
=======
}
EXPORT_SYMBOL_GPL(omap_dm_timer_set_pwm);

void omap_dm_timer_set_prescaler(struct omap_dm_timer *timer, int prescaler)
{
	u32 l;

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	l = omap_dm_timer_read_reg(timer, OMAP_TIMER_CTRL_REG);
	l &= ~(OMAP_TIMER_CTRL_PRE | (0x07 << 2));
	if (prescaler >= 0x00 && prescaler <= 0x07) {
		l |= OMAP_TIMER_CTRL_PRE;
		l |= prescaler << 2;
	}
	omap_dm_timer_write_reg(timer, OMAP_TIMER_CTRL_REG, l);
<<<<<<< HEAD

	/* Save the context */
	timer->context.tclr = l;
	omap_dm_timer_disable(timer);
	return 0;
}
EXPORT_SYMBOL_GPL(omap_dm_timer_set_prescaler);

int omap_dm_timer_set_int_enable(struct omap_dm_timer *timer,
				  unsigned int value)
{
	if (unlikely(!timer))
		return -EINVAL;

	omap_dm_timer_enable(timer);
	__omap_dm_timer_int_enable(timer, value);

	/* Save the context */
	timer->context.tier = value;
	timer->context.twer = value;
	omap_dm_timer_disable(timer);
	return 0;
=======
}
EXPORT_SYMBOL_GPL(omap_dm_timer_set_prescaler);

void omap_dm_timer_set_int_enable(struct omap_dm_timer *timer,
				  unsigned int value)
{
	omap_dm_timer_write_reg(timer, OMAP_TIMER_INT_EN_REG, value);
	omap_dm_timer_write_reg(timer, OMAP_TIMER_WAKEUP_EN_REG, value);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}
EXPORT_SYMBOL_GPL(omap_dm_timer_set_int_enable);

unsigned int omap_dm_timer_read_status(struct omap_dm_timer *timer)
{
	unsigned int l;

<<<<<<< HEAD
	if (unlikely(!timer || pm_runtime_suspended(&timer->pdev->dev))) {
		pr_err("%s: timer not available or enabled.\n", __func__);
		return 0;
	}

	l = __raw_readl(timer->irq_stat);
=======
	l = omap_dm_timer_read_reg(timer, OMAP_TIMER_STAT_REG);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	return l;
}
EXPORT_SYMBOL_GPL(omap_dm_timer_read_status);

<<<<<<< HEAD
int omap_dm_timer_write_status(struct omap_dm_timer *timer, unsigned int value)
{
	if (unlikely(!timer || pm_runtime_suspended(&timer->pdev->dev)))
		return -EINVAL;

	__omap_dm_timer_write_status(timer, value);
	/* Save the context */
	timer->context.tisr = value;
	return 0;
=======
void omap_dm_timer_write_status(struct omap_dm_timer *timer, unsigned int value)
{
	omap_dm_timer_write_reg(timer, OMAP_TIMER_STAT_REG, value);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}
EXPORT_SYMBOL_GPL(omap_dm_timer_write_status);

unsigned int omap_dm_timer_read_counter(struct omap_dm_timer *timer)
{
<<<<<<< HEAD
	if (unlikely(!timer || pm_runtime_suspended(&timer->pdev->dev))) {
		pr_err("%s: timer not iavailable or enabled.\n", __func__);
		return 0;
	}

	return __omap_dm_timer_read_counter(timer, timer->posted);
}
EXPORT_SYMBOL_GPL(omap_dm_timer_read_counter);

int omap_dm_timer_write_counter(struct omap_dm_timer *timer, unsigned int value)
{
	if (unlikely(!timer || pm_runtime_suspended(&timer->pdev->dev))) {
		pr_err("%s: timer not available or enabled.\n", __func__);
		return -EINVAL;
	}

	omap_dm_timer_write_reg(timer, OMAP_TIMER_COUNTER_REG, value);

	/* Save the context */
	timer->context.tcrr = value;
	return 0;
=======
	unsigned int l;

	l = omap_dm_timer_read_reg(timer, OMAP_TIMER_COUNTER_REG);

	return l;
}
EXPORT_SYMBOL_GPL(omap_dm_timer_read_counter);

void omap_dm_timer_write_counter(struct omap_dm_timer *timer, unsigned int value)
{
	omap_dm_timer_write_reg(timer, OMAP_TIMER_COUNTER_REG, value);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}
EXPORT_SYMBOL_GPL(omap_dm_timer_write_counter);

int omap_dm_timers_active(void)
{
<<<<<<< HEAD
	struct omap_dm_timer *timer;

	list_for_each_entry(timer, &omap_timer_list, node) {
		if (!timer->reserved)
=======
	int i;

	for (i = 0; i < dm_timer_count; i++) {
		struct omap_dm_timer *timer;

		timer = &dm_timers[i];

		if (!timer->enabled)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			continue;

		if (omap_dm_timer_read_reg(timer, OMAP_TIMER_CTRL_REG) &
		    OMAP_TIMER_CTRL_ST) {
			return 1;
		}
	}
	return 0;
}
EXPORT_SYMBOL_GPL(omap_dm_timers_active);

<<<<<<< HEAD
/**
 * omap_dm_timer_probe - probe function called for every registered device
 * @pdev:	pointer to current timer platform device
 *
 * Called by driver framework at the end of device registration for all
 * timer devices.
 */
static int __devinit omap_dm_timer_probe(struct platform_device *pdev)
{
	int ret;
	unsigned long flags;
	struct omap_dm_timer *timer;
	struct resource *mem, *irq, *ioarea;
	struct dmtimer_platform_data *pdata = pdev->dev.platform_data;

	if (!pdata) {
		dev_err(&pdev->dev, "%s: no platform data.\n", __func__);
		return -ENODEV;
	}

	irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (unlikely(!irq)) {
		dev_err(&pdev->dev, "%s: no IRQ resource.\n", __func__);
		return -ENODEV;
	}

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (unlikely(!mem)) {
		dev_err(&pdev->dev, "%s: no memory resource.\n", __func__);
		return -ENODEV;
	}

	ioarea = request_mem_region(mem->start, resource_size(mem),
			pdev->name);
	if (!ioarea) {
		dev_err(&pdev->dev, "%s: region already claimed.\n", __func__);
		return -EBUSY;
	}

	timer = kzalloc(sizeof(struct omap_dm_timer), GFP_KERNEL);
	if (!timer) {
		dev_err(&pdev->dev, "%s: no memory for omap_dm_timer.\n",
			__func__);
		ret = -ENOMEM;
		goto err_free_ioregion;
	}

	timer->io_base = ioremap(mem->start, resource_size(mem));
	if (!timer->io_base) {
		dev_err(&pdev->dev, "%s: ioremap failed.\n", __func__);
		ret = -ENOMEM;
		goto err_free_mem;
	}

	timer->id = pdev->id;
	timer->irq = irq->start;
	timer->reserved = pdata->reserved;
	timer->pdev = pdev;
	timer->loses_context = pdata->loses_context;
	timer->get_context_loss_count = pdata->get_context_loss_count;

	/* Skip pm_runtime_enable for OMAP1 */
	if (!pdata->needs_manual_reset) {
		pm_runtime_enable(&pdev->dev);
		pm_runtime_irq_safe(&pdev->dev);
	}

	if (!timer->reserved) {
		pm_runtime_get_sync(&pdev->dev);
		__omap_dm_timer_init_regs(timer);
		pm_runtime_put(&pdev->dev);
	}

	/* add the timer element to the list */
	spin_lock_irqsave(&dm_timer_lock, flags);
	list_add_tail(&timer->node, &omap_timer_list);
	spin_unlock_irqrestore(&dm_timer_lock, flags);

	dev_dbg(&pdev->dev, "Device Probed.\n");

	return 0;

err_free_mem:
	kfree(timer);

err_free_ioregion:
	release_mem_region(mem->start, resource_size(mem));

	return ret;
}

/**
 * omap_dm_timer_remove - cleanup a registered timer device
 * @pdev:	pointer to current timer platform device
 *
 * Called by driver framework whenever a timer device is unregistered.
 * In addition to freeing platform resources it also deletes the timer
 * entry from the local list.
 */
static int __devexit omap_dm_timer_remove(struct platform_device *pdev)
{
	struct omap_dm_timer *timer;
	unsigned long flags;
	int ret = -EINVAL;

	spin_lock_irqsave(&dm_timer_lock, flags);
	list_for_each_entry(timer, &omap_timer_list, node)
		if (timer->pdev->id == pdev->id) {
			list_del(&timer->node);
			kfree(timer);
			ret = 0;
			break;
		}
	spin_unlock_irqrestore(&dm_timer_lock, flags);

	return ret;
}

static struct platform_driver omap_dm_timer_driver = {
	.probe  = omap_dm_timer_probe,
	.remove = __devexit_p(omap_dm_timer_remove),
	.driver = {
		.name   = "omap_timer",
	},
};

static int __init omap_dm_timer_driver_init(void)
{
	return platform_driver_register(&omap_dm_timer_driver);
}

static void __exit omap_dm_timer_driver_exit(void)
{
	platform_driver_unregister(&omap_dm_timer_driver);
}

early_platform_init("earlytimer", &omap_dm_timer_driver);
module_init(omap_dm_timer_driver_init);
module_exit(omap_dm_timer_driver_exit);

MODULE_DESCRIPTION("OMAP Dual-Mode Timer Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_AUTHOR("Texas Instruments Inc");
=======
int __init omap_dm_timer_init(void)
{
	struct omap_dm_timer *timer;
	int i, map_size = SZ_8K;	/* Module 4KB + L4 4KB except on omap1 */

	if (!(cpu_is_omap16xx() || cpu_class_is_omap2()))
		return -ENODEV;

	spin_lock_init(&dm_timer_lock);

	if (cpu_class_is_omap1()) {
		dm_timers = omap1_dm_timers;
		dm_timer_count = omap1_dm_timer_count;
		map_size = SZ_2K;
	} else if (cpu_is_omap24xx()) {
		dm_timers = omap2_dm_timers;
		dm_timer_count = omap2_dm_timer_count;
		dm_source_names = omap2_dm_source_names;
		dm_source_clocks = omap2_dm_source_clocks;
	} else if (cpu_is_omap34xx()) {
		dm_timers = omap3_dm_timers;
		dm_timer_count = omap3_dm_timer_count;
		dm_source_names = omap3_dm_source_names;
		dm_source_clocks = omap3_dm_source_clocks;
	} else if (cpu_is_omap44xx()) {
		dm_timers = omap4_dm_timers;
		dm_timer_count = omap4_dm_timer_count;
		dm_source_names = omap4_dm_source_names;
		dm_source_clocks = omap4_dm_source_clocks;
	}

	if (cpu_class_is_omap2())
		for (i = 0; dm_source_names[i] != NULL; i++)
			dm_source_clocks[i] = clk_get(NULL, dm_source_names[i]);

	if (cpu_is_omap243x())
		dm_timers[0].phys_base = 0x49018000;

	for (i = 0; i < dm_timer_count; i++) {
		timer = &dm_timers[i];

		/* Static mapping, never released */
		timer->io_base = ioremap(timer->phys_base, map_size);
		BUG_ON(!timer->io_base);

#ifdef CONFIG_ARCH_OMAP2PLUS
		if (cpu_class_is_omap2()) {
			char clk_name[16];
			sprintf(clk_name, "gpt%d_ick", i + 1);
			timer->iclk = clk_get(NULL, clk_name);
			sprintf(clk_name, "gpt%d_fck", i + 1);
			timer->fclk = clk_get(NULL, clk_name);
		}
#endif
	}

	return 0;
}
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
