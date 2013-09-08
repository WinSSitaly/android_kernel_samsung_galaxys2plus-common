/*
 * linux/arch/arm/mach-w90p910/include/mach/gpio.h
 *
 * Generic w90p910 GPIO handling
 *
 *  Wan ZongShun <mcuos.com@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ASM_ARCH_W90P910_GPIO_H
#define __ASM_ARCH_W90P910_GPIO_H

#include <mach/hardware.h>
#include <asm/irq.h>
<<<<<<< HEAD
=======
#include <asm-generic/gpio.h>

#define gpio_get_value	__gpio_get_value
#define gpio_set_value	__gpio_set_value
#define gpio_cansleep	__gpio_cansleep
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

static inline int gpio_to_irq(unsigned gpio)
{
	return gpio;
}
<<<<<<< HEAD
#define gpio_to_irq gpio_to_irq
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

static inline int irq_to_gpio(unsigned irq)
{
	return irq;
}

#endif
