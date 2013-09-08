<<<<<<< HEAD
/*
 * Copyright (C) 2007 Google, Inc.
 * Copyright (c) 2011, Code Aurora Forum. All rights reserved.
=======
/* arch/arm/mach-msm/include/mach/uncompress.h
 *
 * Copyright (C) 2007 Google, Inc.
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __ASM_ARCH_MSM_UNCOMPRESS_H
<<<<<<< HEAD
#define __ASM_ARCH_MSM_UNCOMPRESS_H

#include <asm/barrier.h>
#include <asm/processor.h>
#include <mach/msm_iomap.h>

#define UART_CSR      (*(volatile uint32_t *)(MSM_DEBUG_UART_PHYS + 0x08))
#define UART_TF       (*(volatile uint32_t *)(MSM_DEBUG_UART_PHYS + 0x0c))

#define UART_DM_SR    (*((volatile uint32_t *)(MSM_DEBUG_UART_PHYS + 0x08)))
#define UART_DM_CR    (*((volatile uint32_t *)(MSM_DEBUG_UART_PHYS + 0x10)))
#define UART_DM_ISR   (*((volatile uint32_t *)(MSM_DEBUG_UART_PHYS + 0x14)))
#define UART_DM_NCHAR (*((volatile uint32_t *)(MSM_DEBUG_UART_PHYS + 0x40)))
#define UART_DM_TF    (*((volatile uint32_t *)(MSM_DEBUG_UART_PHYS + 0x70)))
=======

#include "hardware.h"
#include "linux/io.h"
#include "mach/msm_iomap.h"
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

static void putc(int c)
{
#if defined(MSM_DEBUG_UART_PHYS)
<<<<<<< HEAD
#ifdef CONFIG_MSM_HAS_DEBUG_UART_HS
	/*
	 * Wait for TX_READY to be set; but skip it if we have a
	 * TX underrun.
	 */
	if (UART_DM_SR & 0x08)
		while (!(UART_DM_ISR & 0x80))
			cpu_relax();

	UART_DM_CR = 0x300;
	UART_DM_NCHAR = 0x1;
	UART_DM_TF = c;
#else
	while (!(UART_CSR & 0x04))
		cpu_relax();
	UART_TF = c;
#endif
=======
	unsigned base = MSM_DEBUG_UART_PHYS;
	while (!(readl(base + 0x08) & 0x04)) ;
	writel(c, base + 0x0c);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#endif
}

static inline void flush(void)
{
}

static inline void arch_decomp_setup(void)
{
}

static inline void arch_decomp_wdog(void)
{
}

#endif
