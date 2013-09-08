/*
 *  linux/drivers/mfd/mcp-sa11x0.c
 *
 *  Copyright (C) 2001-2005 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 *  SA11x0 MCP (Multimedia Communications Port) driver.
 *
 *  MCP read/write timeouts from Jordi Colomer, rehacked by rmk.
 */
#include <linux/module.h>
#include <linux/init.h>
<<<<<<< HEAD
#include <linux/io.h>
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#include <linux/platform_device.h>
<<<<<<< HEAD
#include <linux/pm.h>
#include <linux/mfd/mcp.h>

#include <mach/hardware.h>
#include <asm/mach-types.h>
#include <mach/mcp.h>

#define DRIVER_NAME "sa11x0-mcp"

struct mcp_sa11x0 {
	void __iomem	*base0;
	void __iomem	*base1;
	u32		mccr0;
	u32		mccr1;
};

/* Register offsets */
#define MCCR0(m)	((m)->base0 + 0x00)
#define MCDR0(m)	((m)->base0 + 0x08)
#define MCDR1(m)	((m)->base0 + 0x0c)
#define MCDR2(m)	((m)->base0 + 0x10)
#define MCSR(m)		((m)->base0 + 0x18)
#define MCCR1(m)	((m)->base1 + 0x00)

=======
#include <linux/mfd/mcp.h>

#include <mach/dma.h>
#include <mach/hardware.h>
#include <asm/mach-types.h>
#include <asm/system.h>
#include <mach/mcp.h>

#include <mach/assabet.h>


struct mcp_sa11x0 {
	u32	mccr0;
	u32	mccr1;
};

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#define priv(mcp)	((struct mcp_sa11x0 *)mcp_priv(mcp))

static void
mcp_sa11x0_set_telecom_divisor(struct mcp *mcp, unsigned int divisor)
{
<<<<<<< HEAD
	struct mcp_sa11x0 *m = priv(mcp);

	divisor /= 32;

	m->mccr0 &= ~0x00007f00;
	m->mccr0 |= divisor << 8;
	writel_relaxed(m->mccr0, MCCR0(m));
=======
	unsigned int mccr0;

	divisor /= 32;

	mccr0 = Ser4MCCR0 & ~0x00007f00;
	mccr0 |= divisor << 8;
	Ser4MCCR0 = mccr0;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

static void
mcp_sa11x0_set_audio_divisor(struct mcp *mcp, unsigned int divisor)
{
<<<<<<< HEAD
	struct mcp_sa11x0 *m = priv(mcp);

	divisor /= 32;

	m->mccr0 &= ~0x0000007f;
	m->mccr0 |= divisor;
	writel_relaxed(m->mccr0, MCCR0(m));
=======
	unsigned int mccr0;

	divisor /= 32;

	mccr0 = Ser4MCCR0 & ~0x0000007f;
	mccr0 |= divisor;
	Ser4MCCR0 = mccr0;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

/*
 * Write data to the device.  The bit should be set after 3 subframe
 * times (each frame is 64 clocks).  We wait a maximum of 6 subframes.
 * We really should try doing something more productive while we
 * wait.
 */
static void
mcp_sa11x0_write(struct mcp *mcp, unsigned int reg, unsigned int val)
{
<<<<<<< HEAD
	struct mcp_sa11x0 *m = priv(mcp);
	int ret = -ETIME;
	int i;

	writel_relaxed(reg << 17 | MCDR2_Wr | (val & 0xffff), MCDR2(m));

	for (i = 0; i < 2; i++) {
		udelay(mcp->rw_timeout);
		if (readl_relaxed(MCSR(m)) & MCSR_CWC) {
=======
	int ret = -ETIME;
	int i;

	Ser4MCDR2 = reg << 17 | MCDR2_Wr | (val & 0xffff);

	for (i = 0; i < 2; i++) {
		udelay(mcp->rw_timeout);
		if (Ser4MCSR & MCSR_CWC) {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			ret = 0;
			break;
		}
	}

	if (ret < 0)
		printk(KERN_WARNING "mcp: write timed out\n");
}

/*
 * Read data from the device.  The bit should be set after 3 subframe
 * times (each frame is 64 clocks).  We wait a maximum of 6 subframes.
 * We really should try doing something more productive while we
 * wait.
 */
static unsigned int
mcp_sa11x0_read(struct mcp *mcp, unsigned int reg)
{
<<<<<<< HEAD
	struct mcp_sa11x0 *m = priv(mcp);
	int ret = -ETIME;
	int i;

	writel_relaxed(reg << 17 | MCDR2_Rd, MCDR2(m));

	for (i = 0; i < 2; i++) {
		udelay(mcp->rw_timeout);
		if (readl_relaxed(MCSR(m)) & MCSR_CRC) {
			ret = readl_relaxed(MCDR2(m)) & 0xffff;
=======
	int ret = -ETIME;
	int i;

	Ser4MCDR2 = reg << 17 | MCDR2_Rd;

	for (i = 0; i < 2; i++) {
		udelay(mcp->rw_timeout);
		if (Ser4MCSR & MCSR_CRC) {
			ret = Ser4MCDR2 & 0xffff;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			break;
		}
	}

	if (ret < 0)
		printk(KERN_WARNING "mcp: read timed out\n");

	return ret;
}

static void mcp_sa11x0_enable(struct mcp *mcp)
{
<<<<<<< HEAD
	struct mcp_sa11x0 *m = priv(mcp);

	writel(-1, MCSR(m));
	m->mccr0 |= MCCR0_MCE;
	writel_relaxed(m->mccr0, MCCR0(m));
=======
	Ser4MCSR = -1;
	Ser4MCCR0 |= MCCR0_MCE;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

static void mcp_sa11x0_disable(struct mcp *mcp)
{
<<<<<<< HEAD
	struct mcp_sa11x0 *m = priv(mcp);

	m->mccr0 &= ~MCCR0_MCE;
	writel_relaxed(m->mccr0, MCCR0(m));
=======
	Ser4MCCR0 &= ~MCCR0_MCE;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

/*
 * Our methods.
 */
static struct mcp_ops mcp_sa11x0 = {
	.set_telecom_divisor	= mcp_sa11x0_set_telecom_divisor,
	.set_audio_divisor	= mcp_sa11x0_set_audio_divisor,
	.reg_write		= mcp_sa11x0_write,
	.reg_read		= mcp_sa11x0_read,
	.enable			= mcp_sa11x0_enable,
	.disable		= mcp_sa11x0_disable,
};

<<<<<<< HEAD
static int mcp_sa11x0_probe(struct platform_device *dev)
{
	struct mcp_plat_data *data = dev->dev.platform_data;
	struct resource *mem0, *mem1;
	struct mcp_sa11x0 *m;
=======
static int mcp_sa11x0_probe(struct platform_device *pdev)
{
	struct mcp_plat_data *data = pdev->dev.platform_data;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	struct mcp *mcp;
	int ret;

	if (!data)
		return -ENODEV;

<<<<<<< HEAD
	mem0 = platform_get_resource(dev, IORESOURCE_MEM, 0);
	mem1 = platform_get_resource(dev, IORESOURCE_MEM, 1);
	if (!mem0 || !mem1)
		return -ENXIO;

	if (!request_mem_region(mem0->start, resource_size(mem0),
				DRIVER_NAME)) {
		ret = -EBUSY;
		goto err_mem0;
	}

	if (!request_mem_region(mem1->start, resource_size(mem1),
				DRIVER_NAME)) {
		ret = -EBUSY;
		goto err_mem1;
	}

	mcp = mcp_host_alloc(&dev->dev, sizeof(struct mcp_sa11x0));
	if (!mcp) {
		ret = -ENOMEM;
		goto err_alloc;
=======
	if (!request_mem_region(0x80060000, 0x60, "sa11x0-mcp"))
		return -EBUSY;

	mcp = mcp_host_alloc(&pdev->dev, sizeof(struct mcp_sa11x0));
	if (!mcp) {
		ret = -ENOMEM;
		goto release;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}

	mcp->owner		= THIS_MODULE;
	mcp->ops		= &mcp_sa11x0;
	mcp->sclk_rate		= data->sclk_rate;
<<<<<<< HEAD

	m = priv(mcp);
	m->mccr0 = data->mccr0 | 0x7f7f;
	m->mccr1 = data->mccr1;

	m->base0 = ioremap(mem0->start, resource_size(mem0));
	m->base1 = ioremap(mem1->start, resource_size(mem1));
	if (!m->base0 || !m->base1) {
		ret = -ENOMEM;
		goto err_ioremap;
	}

	platform_set_drvdata(dev, mcp);
=======
	mcp->dma_audio_rd	= DMA_Ser4MCP0Rd;
	mcp->dma_audio_wr	= DMA_Ser4MCP0Wr;
	mcp->dma_telco_rd	= DMA_Ser4MCP1Rd;
	mcp->dma_telco_wr	= DMA_Ser4MCP1Wr;
	mcp->gpio_base		= data->gpio_base;

	platform_set_drvdata(pdev, mcp);

	if (machine_is_assabet()) {
		ASSABET_BCR_set(ASSABET_BCR_CODEC_RST);
	}

	/*
	 * Setup the PPC unit correctly.
	 */
	PPDR &= ~PPC_RXD4;
	PPDR |= PPC_TXD4 | PPC_SCLK | PPC_SFRM;
	PSDR |= PPC_RXD4;
	PSDR &= ~(PPC_TXD4 | PPC_SCLK | PPC_SFRM);
	PPSR &= ~(PPC_TXD4 | PPC_SCLK | PPC_SFRM);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	/*
	 * Initialise device.  Note that we initially
	 * set the sampling rate to minimum.
	 */
<<<<<<< HEAD
	writel_relaxed(-1, MCSR(m));
	writel_relaxed(m->mccr1, MCCR1(m));
	writel_relaxed(m->mccr0, MCCR0(m));
=======
	Ser4MCSR = -1;
	Ser4MCCR1 = data->mccr1;
	Ser4MCCR0 = data->mccr0 | 0x7f7f;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	/*
	 * Calculate the read/write timeout (us) from the bit clock
	 * rate.  This is the period for 3 64-bit frames.  Always
	 * round this time up.
	 */
	mcp->rw_timeout = (64 * 3 * 1000000 + mcp->sclk_rate - 1) /
			  mcp->sclk_rate;

<<<<<<< HEAD
	ret = mcp_host_add(mcp, data->codec_pdata);
	if (ret == 0)
		return 0;

	platform_set_drvdata(dev, NULL);

 err_ioremap:
	iounmap(m->base1);
	iounmap(m->base0);
	mcp_host_free(mcp);
 err_alloc:
	release_mem_region(mem1->start, resource_size(mem1));
 err_mem1:
	release_mem_region(mem0->start, resource_size(mem0));
 err_mem0:
=======
	ret = mcp_host_register(mcp);
	if (ret == 0)
		goto out;

 release:
	release_mem_region(0x80060000, 0x60);
	platform_set_drvdata(pdev, NULL);

 out:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	return ret;
}

static int mcp_sa11x0_remove(struct platform_device *dev)
{
	struct mcp *mcp = platform_get_drvdata(dev);
<<<<<<< HEAD
	struct mcp_sa11x0 *m = priv(mcp);
	struct resource *mem0, *mem1;

	if (m->mccr0 & MCCR0_MCE)
		dev_warn(&dev->dev,
			 "device left active (missing disable call?)\n");

	mem0 = platform_get_resource(dev, IORESOURCE_MEM, 0);
	mem1 = platform_get_resource(dev, IORESOURCE_MEM, 1);

	platform_set_drvdata(dev, NULL);
	mcp_host_del(mcp);
	iounmap(m->base1);
	iounmap(m->base0);
	mcp_host_free(mcp);
	release_mem_region(mem1->start, resource_size(mem1));
	release_mem_region(mem0->start, resource_size(mem0));
=======

	platform_set_drvdata(dev, NULL);
	mcp_host_unregister(mcp);
	release_mem_region(0x80060000, 0x60);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	return 0;
}

<<<<<<< HEAD
#ifdef CONFIG_PM_SLEEP
static int mcp_sa11x0_suspend(struct device *dev)
{
	struct mcp_sa11x0 *m = priv(dev_get_drvdata(dev));

	if (m->mccr0 & MCCR0_MCE)
		dev_warn(dev, "device left active (missing disable call?)\n");

	writel(m->mccr0 & ~MCCR0_MCE, MCCR0(m));
=======
static int mcp_sa11x0_suspend(struct platform_device *dev, pm_message_t state)
{
	struct mcp *mcp = platform_get_drvdata(dev);

	priv(mcp)->mccr0 = Ser4MCCR0;
	priv(mcp)->mccr1 = Ser4MCCR1;
	Ser4MCCR0 &= ~MCCR0_MCE;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	return 0;
}

<<<<<<< HEAD
static int mcp_sa11x0_resume(struct device *dev)
{
	struct mcp_sa11x0 *m = priv(dev_get_drvdata(dev));

	writel_relaxed(m->mccr1, MCCR1(m));
	writel_relaxed(m->mccr0, MCCR0(m));

	return 0;
}
#endif

static const struct dev_pm_ops mcp_sa11x0_pm_ops = {
#ifdef CONFIG_PM_SLEEP
	.suspend = mcp_sa11x0_suspend,
	.freeze = mcp_sa11x0_suspend,
	.poweroff = mcp_sa11x0_suspend,
	.resume_noirq = mcp_sa11x0_resume,
	.thaw_noirq = mcp_sa11x0_resume,
	.restore_noirq = mcp_sa11x0_resume,
#endif
};
=======
static int mcp_sa11x0_resume(struct platform_device *dev)
{
	struct mcp *mcp = platform_get_drvdata(dev);

	Ser4MCCR1 = priv(mcp)->mccr1;
	Ser4MCCR0 = priv(mcp)->mccr0;

	return 0;
}

/*
 * The driver for the SA11x0 MCP port.
 */
MODULE_ALIAS("platform:sa11x0-mcp");
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

static struct platform_driver mcp_sa11x0_driver = {
	.probe		= mcp_sa11x0_probe,
	.remove		= mcp_sa11x0_remove,
<<<<<<< HEAD
	.driver		= {
		.name	= DRIVER_NAME,
		.owner	= THIS_MODULE,
		.pm	= &mcp_sa11x0_pm_ops,
=======
	.suspend	= mcp_sa11x0_suspend,
	.resume		= mcp_sa11x0_resume,
	.driver		= {
		.name	= "sa11x0-mcp",
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	},
};

/*
 * This needs re-working
 */
<<<<<<< HEAD
module_platform_driver(mcp_sa11x0_driver);

MODULE_ALIAS("platform:" DRIVER_NAME);
=======
static int __init mcp_sa11x0_init(void)
{
	return platform_driver_register(&mcp_sa11x0_driver);
}

static void __exit mcp_sa11x0_exit(void)
{
	platform_driver_unregister(&mcp_sa11x0_driver);
}

module_init(mcp_sa11x0_init);
module_exit(mcp_sa11x0_exit);

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
MODULE_AUTHOR("Russell King <rmk@arm.linux.org.uk>");
MODULE_DESCRIPTION("SA11x0 multimedia communications port driver");
MODULE_LICENSE("GPL");
