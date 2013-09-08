/*
 * arch/sh/drivers/dma/dma-sysfs.c
 *
 * sysfs interface for SH DMA API
 *
 * Copyright (C) 2004 - 2006  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */
#include <linux/kernel.h>
#include <linux/init.h>
<<<<<<< HEAD
#include <linux/stat.h>
#include <linux/device.h>
=======
#include <linux/sysdev.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/string.h>
#include <asm/dma.h>

<<<<<<< HEAD
static struct bus_type dma_subsys = {
	.name = "dma",
	.dev_name = "dma",
};

static ssize_t dma_show_devices(struct device *dev,
				struct device_attribute *attr, char *buf)
=======
static struct sysdev_class dma_sysclass = {
	.name = "dma",
};

static ssize_t dma_show_devices(struct sys_device *dev,
				struct sysdev_attribute *attr, char *buf)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	ssize_t len = 0;
	int i;

	for (i = 0; i < MAX_DMA_CHANNELS; i++) {
		struct dma_info *info = get_dma_info(i);
		struct dma_channel *channel = get_dma_channel(i);

		if (unlikely(!info) || !channel)
			continue;

		len += sprintf(buf + len, "%2d: %14s    %s\n",
			       channel->chan, info->name,
			       channel->dev_id);
	}

	return len;
}

<<<<<<< HEAD
static DEVICE_ATTR(devices, S_IRUGO, dma_show_devices, NULL);

static int __init dma_subsys_init(void)
{
	int ret;

	ret = subsys_system_register(&dma_subsys, NULL);
	if (unlikely(ret))
		return ret;

	return device_create_file(dma_subsys.dev_root, &dev_attr_devices);
}
postcore_initcall(dma_subsys_init);

static ssize_t dma_show_dev_id(struct device *dev,
				struct device_attribute *attr, char *buf)
=======
static SYSDEV_ATTR(devices, S_IRUGO, dma_show_devices, NULL);

static int __init dma_sysclass_init(void)
{
	int ret;

	ret = sysdev_class_register(&dma_sysclass);
	if (unlikely(ret))
		return ret;

	return sysfs_create_file(&dma_sysclass.kset.kobj, &attr_devices.attr);
}
postcore_initcall(dma_sysclass_init);

static ssize_t dma_show_dev_id(struct sys_device *dev,
				struct sysdev_attribute *attr, char *buf)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	struct dma_channel *channel = to_dma_channel(dev);
	return sprintf(buf, "%s\n", channel->dev_id);
}

<<<<<<< HEAD
static ssize_t dma_store_dev_id(struct device *dev,
				struct device_attribute *attr,
=======
static ssize_t dma_store_dev_id(struct sys_device *dev,
				struct sysdev_attribute *attr,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
				const char *buf, size_t count)
{
	struct dma_channel *channel = to_dma_channel(dev);
	strcpy(channel->dev_id, buf);
	return count;
}

<<<<<<< HEAD
static DEVICE_ATTR(dev_id, S_IRUGO | S_IWUSR, dma_show_dev_id, dma_store_dev_id);

static ssize_t dma_store_config(struct device *dev,
				struct device_attribute *attr,
=======
static SYSDEV_ATTR(dev_id, S_IRUGO | S_IWUSR, dma_show_dev_id, dma_store_dev_id);

static ssize_t dma_store_config(struct sys_device *dev,
				struct sysdev_attribute *attr,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
				const char *buf, size_t count)
{
	struct dma_channel *channel = to_dma_channel(dev);
	unsigned long config;

	config = simple_strtoul(buf, NULL, 0);
	dma_configure_channel(channel->vchan, config);

	return count;
}

<<<<<<< HEAD
static DEVICE_ATTR(config, S_IWUSR, NULL, dma_store_config);

static ssize_t dma_show_mode(struct device *dev,
				struct device_attribute *attr, char *buf)
=======
static SYSDEV_ATTR(config, S_IWUSR, NULL, dma_store_config);

static ssize_t dma_show_mode(struct sys_device *dev,
				struct sysdev_attribute *attr, char *buf)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	struct dma_channel *channel = to_dma_channel(dev);
	return sprintf(buf, "0x%08x\n", channel->mode);
}

<<<<<<< HEAD
static ssize_t dma_store_mode(struct device *dev,
			      struct device_attribute *attr,
=======
static ssize_t dma_store_mode(struct sys_device *dev,
			      struct sysdev_attribute *attr,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			      const char *buf, size_t count)
{
	struct dma_channel *channel = to_dma_channel(dev);
	channel->mode = simple_strtoul(buf, NULL, 0);
	return count;
}

<<<<<<< HEAD
static DEVICE_ATTR(mode, S_IRUGO | S_IWUSR, dma_show_mode, dma_store_mode);

#define dma_ro_attr(field, fmt)						\
static ssize_t dma_show_##field(struct device *dev,		\
				struct device_attribute *attr, char *buf)\
=======
static SYSDEV_ATTR(mode, S_IRUGO | S_IWUSR, dma_show_mode, dma_store_mode);

#define dma_ro_attr(field, fmt)						\
static ssize_t dma_show_##field(struct sys_device *dev, 		\
				struct sysdev_attribute *attr, char *buf)\
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{									\
	struct dma_channel *channel = to_dma_channel(dev);		\
	return sprintf(buf, fmt, channel->field);			\
}									\
<<<<<<< HEAD
static DEVICE_ATTR(field, S_IRUGO, dma_show_##field, NULL);
=======
static SYSDEV_ATTR(field, S_IRUGO, dma_show_##field, NULL);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

dma_ro_attr(count, "0x%08x\n");
dma_ro_attr(flags, "0x%08lx\n");

int dma_create_sysfs_files(struct dma_channel *chan, struct dma_info *info)
{
<<<<<<< HEAD
	struct device *dev = &chan->dev;
=======
	struct sys_device *dev = &chan->dev;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	char name[16];
	int ret;

	dev->id  = chan->vchan;
<<<<<<< HEAD
	dev->bus = &dma_subsys;

	ret = device_register(dev);
	if (ret)
		return ret;

	ret |= device_create_file(dev, &dev_attr_dev_id);
	ret |= device_create_file(dev, &dev_attr_count);
	ret |= device_create_file(dev, &dev_attr_mode);
	ret |= device_create_file(dev, &dev_attr_flags);
	ret |= device_create_file(dev, &dev_attr_config);
=======
	dev->cls = &dma_sysclass;

	ret = sysdev_register(dev);
	if (ret)
		return ret;

	ret |= sysdev_create_file(dev, &attr_dev_id);
	ret |= sysdev_create_file(dev, &attr_count);
	ret |= sysdev_create_file(dev, &attr_mode);
	ret |= sysdev_create_file(dev, &attr_flags);
	ret |= sysdev_create_file(dev, &attr_config);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	if (unlikely(ret)) {
		dev_err(&info->pdev->dev, "Failed creating attrs\n");
		return ret;
	}

	snprintf(name, sizeof(name), "dma%d", chan->chan);
	return sysfs_create_link(&info->pdev->dev.kobj, &dev->kobj, name);
}

void dma_remove_sysfs_files(struct dma_channel *chan, struct dma_info *info)
{
<<<<<<< HEAD
	struct device *dev = &chan->dev;
	char name[16];

	device_remove_file(dev, &dev_attr_dev_id);
	device_remove_file(dev, &dev_attr_count);
	device_remove_file(dev, &dev_attr_mode);
	device_remove_file(dev, &dev_attr_flags);
	device_remove_file(dev, &dev_attr_config);
=======
	struct sys_device *dev = &chan->dev;
	char name[16];

	sysdev_remove_file(dev, &attr_dev_id);
	sysdev_remove_file(dev, &attr_count);
	sysdev_remove_file(dev, &attr_mode);
	sysdev_remove_file(dev, &attr_flags);
	sysdev_remove_file(dev, &attr_config);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	snprintf(name, sizeof(name), "dma%d", chan->chan);
	sysfs_remove_link(&info->pdev->dev.kobj, name);

<<<<<<< HEAD
	device_unregister(dev);
=======
	sysdev_unregister(dev);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}
