/* linux/arch/arm/mach-s5p64x0/include/mach/regs-clock.h
 *
 * Copyright (c) 2009-2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * S5P64X0 - Clock register definitions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM_ARCH_REGS_CLOCK_H
#define __ASM_ARCH_REGS_CLOCK_H __FILE__

#include <mach/map.h>

#define S5P_CLKREG(x)			(S3C_VA_SYS + (x))

#define S5P64X0_APLL_CON		S5P_CLKREG(0x0C)
#define S5P64X0_MPLL_CON		S5P_CLKREG(0x10)
#define S5P64X0_EPLL_CON		S5P_CLKREG(0x14)
#define S5P64X0_EPLL_CON_K		S5P_CLKREG(0x18)

#define S5P64X0_CLK_SRC0		S5P_CLKREG(0x1C)

#define S5P64X0_CLK_DIV0		S5P_CLKREG(0x20)
#define S5P64X0_CLK_DIV1		S5P_CLKREG(0x24)
#define S5P64X0_CLK_DIV2		S5P_CLKREG(0x28)

#define S5P64X0_CLK_GATE_HCLK0		S5P_CLKREG(0x30)
#define S5P64X0_CLK_GATE_PCLK		S5P_CLKREG(0x34)
#define S5P64X0_CLK_GATE_SCLK0		S5P_CLKREG(0x38)
#define S5P64X0_CLK_GATE_MEM0		S5P_CLKREG(0x3C)

#define S5P64X0_CLK_DIV3		S5P_CLKREG(0x40)

#define S5P64X0_CLK_GATE_HCLK1		S5P_CLKREG(0x44)
#define S5P64X0_CLK_GATE_SCLK1		S5P_CLKREG(0x48)

#define S5P6450_DPLL_CON		S5P_CLKREG(0x50)
#define S5P6450_DPLL_CON_K		S5P_CLKREG(0x54)

<<<<<<< HEAD
#define S5P64X0_AHB_CON0		S5P_CLKREG(0x100)
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#define S5P64X0_CLK_SRC1		S5P_CLKREG(0x10C)

#define S5P64X0_SYS_ID			S5P_CLKREG(0x118)
#define S5P64X0_SYS_OTHERS		S5P_CLKREG(0x11C)

#define S5P64X0_PWR_CFG			S5P_CLKREG(0x804)
<<<<<<< HEAD
#define S5P64X0_EINT_WAKEUP_MASK	S5P_CLKREG(0x808)
#define S5P64X0_SLEEP_CFG		S5P_CLKREG(0x818)
#define S5P64X0_PWR_STABLE		S5P_CLKREG(0x828)

#define S5P64X0_OTHERS			S5P_CLKREG(0x900)
#define S5P64X0_WAKEUP_STAT		S5P_CLKREG(0x908)

#define S5P64X0_INFORM0			S5P_CLKREG(0xA00)
=======
#define S5P64X0_OTHERS			S5P_CLKREG(0x900)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#define S5P64X0_CLKDIV0_HCLK_SHIFT	(8)
#define S5P64X0_CLKDIV0_HCLK_MASK	(0xF << S5P64X0_CLKDIV0_HCLK_SHIFT)

<<<<<<< HEAD
/* HCLK GATE Registers */
#define S5P64X0_CLK_GATE_HCLK1_FIMGVG	(1 << 2)
#define S5P64X0_CLK_GATE_SCLK1_FIMGVG	(1 << 2)

/* PCLK GATE Registers */
#define S5P64X0_CLK_GATE_PCLK_UART3	(1 << 4)
#define S5P64X0_CLK_GATE_PCLK_UART2	(1 << 3)
#define S5P64X0_CLK_GATE_PCLK_UART1	(1 << 2)
#define S5P64X0_CLK_GATE_PCLK_UART0	(1 << 1)

#define S5P64X0_PWR_CFG_MMC1_DISABLE		(1 << 15)
#define S5P64X0_PWR_CFG_MMC0_DISABLE		(1 << 14)
#define S5P64X0_PWR_CFG_RTC_TICK_DISABLE	(1 << 11)
#define S5P64X0_PWR_CFG_RTC_ALRM_DISABLE	(1 << 10)
#define S5P64X0_PWR_CFG_WFI_MASK		(3 << 5)
#define S5P64X0_PWR_CFG_WFI_SLEEP		(3 << 5)

#define S5P64X0_SLEEP_CFG_OSC_EN	(1 << 0)

#define S5P64X0_PWR_STABLE_PWR_CNT_VAL4	(4 << 0)

#define S5P6450_OTHERS_DISABLE_INT	(1 << 31)
#define S5P64X0_OTHERS_RET_UART		(1 << 26)
#define S5P64X0_OTHERS_RET_MMC1		(1 << 25)
#define S5P64X0_OTHERS_RET_MMC0		(1 << 24)
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#define S5P64X0_OTHERS_USB_SIG_MASK	(1 << 16)

/* Compatibility defines */

#define ARM_CLK_DIV			S5P64X0_CLK_DIV0
#define ARM_DIV_RATIO_SHIFT		0
#define ARM_DIV_MASK			(0xF << ARM_DIV_RATIO_SHIFT)

#define S5P_EPLL_CON			S5P64X0_EPLL_CON

#endif /* __ASM_ARCH_REGS_CLOCK_H */
