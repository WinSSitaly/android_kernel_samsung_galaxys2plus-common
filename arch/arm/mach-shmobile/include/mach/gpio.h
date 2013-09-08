/*
 * Generic GPIO API and pinmux table support
 *
 * Copyright (c) 2008  Magnus Damm
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */
#ifndef __ASM_ARCH_GPIO_H
#define __ASM_ARCH_GPIO_H

#include <linux/kernel.h>
#include <linux/errno.h>
<<<<<<< HEAD
=======

#define ARCH_NR_GPIOS 1024
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <linux/sh_pfc.h>

#ifdef CONFIG_GPIOLIB

<<<<<<< HEAD
static inline int irq_to_gpio(unsigned int irq)
{
	return -ENOSYS;
}

#else

#define __ARM_GPIOLIB_COMPLEX
=======
static inline int gpio_get_value(unsigned gpio)
{
	return __gpio_get_value(gpio);
}

static inline void gpio_set_value(unsigned gpio, int value)
{
	__gpio_set_value(gpio, value);
}

static inline int gpio_cansleep(unsigned gpio)
{
	return __gpio_cansleep(gpio);
}

static inline int gpio_to_irq(unsigned gpio)
{
	return __gpio_to_irq(gpio);
}

static inline int irq_to_gpio(unsigned int irq)
{
	return -ENOSYS;
}
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#endif /* CONFIG_GPIOLIB */

#endif /* __ASM_ARCH_GPIO_H */
