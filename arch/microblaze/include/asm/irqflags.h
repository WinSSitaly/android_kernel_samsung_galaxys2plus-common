/*
 * Copyright (C) 2006 Atmark Techno, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the main directory of this archive
 * for more details.
 */

#ifndef _ASM_MICROBLAZE_IRQFLAGS_H
#define _ASM_MICROBLAZE_IRQFLAGS_H

#include <linux/types.h>
#include <asm/registers.h>

#if CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR

<<<<<<< HEAD
static inline notrace unsigned long arch_local_irq_save(void)
=======
static inline unsigned long arch_local_irq_save(void)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	unsigned long flags;
	asm volatile("	msrclr %0, %1	\n"
		     "	nop		\n"
		     : "=r"(flags)
		     : "i"(MSR_IE)
		     : "memory");
	return flags;
}

<<<<<<< HEAD
static inline notrace void arch_local_irq_disable(void)
=======
static inline void arch_local_irq_disable(void)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	/* this uses r0 without declaring it - is that correct? */
	asm volatile("	msrclr r0, %0	\n"
		     "	nop		\n"
		     :
		     : "i"(MSR_IE)
		     : "memory");
}

<<<<<<< HEAD
static inline notrace void arch_local_irq_enable(void)
=======
static inline void arch_local_irq_enable(void)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	/* this uses r0 without declaring it - is that correct? */
	asm volatile("	msrset	r0, %0	\n"
		     "	nop		\n"
		     :
		     : "i"(MSR_IE)
		     : "memory");
}

#else /* !CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR */

<<<<<<< HEAD
static inline notrace unsigned long arch_local_irq_save(void)
=======
static inline unsigned long arch_local_irq_save(void)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	unsigned long flags, tmp;
	asm volatile ("	mfs	%0, rmsr	\n"
		      "	nop			\n"
		      "	andi	%1, %0, %2	\n"
		      "	mts	rmsr, %1	\n"
		      "	nop			\n"
		      : "=r"(flags), "=r"(tmp)
		      : "i"(~MSR_IE)
		      : "memory");
	return flags;
}

<<<<<<< HEAD
static inline notrace void arch_local_irq_disable(void)
=======
static inline void arch_local_irq_disable(void)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	unsigned long tmp;
	asm volatile("	mfs	%0, rmsr	\n"
		     "	nop			\n"
		     "	andi	%0, %0, %1	\n"
		     "	mts	rmsr, %0	\n"
		     "	nop			\n"
		     : "=r"(tmp)
		     : "i"(~MSR_IE)
		     : "memory");
}

<<<<<<< HEAD
static inline notrace void arch_local_irq_enable(void)
=======
static inline void arch_local_irq_enable(void)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	unsigned long tmp;
	asm volatile("	mfs	%0, rmsr	\n"
		     "	nop			\n"
		     "	ori	%0, %0, %1	\n"
		     "	mts	rmsr, %0	\n"
		     "	nop			\n"
		     : "=r"(tmp)
		     : "i"(MSR_IE)
		     : "memory");
}

#endif /* CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR */

<<<<<<< HEAD
static inline notrace unsigned long arch_local_save_flags(void)
=======
static inline unsigned long arch_local_save_flags(void)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	unsigned long flags;
	asm volatile("	mfs	%0, rmsr	\n"
		     "	nop			\n"
		     : "=r"(flags)
		     :
		     : "memory");
	return flags;
}

<<<<<<< HEAD
static inline notrace void arch_local_irq_restore(unsigned long flags)
=======
static inline void arch_local_irq_restore(unsigned long flags)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	asm volatile("	mts	rmsr, %0	\n"
		     "	nop			\n"
		     :
		     : "r"(flags)
		     : "memory");
}

<<<<<<< HEAD
static inline notrace bool arch_irqs_disabled_flags(unsigned long flags)
=======
static inline bool arch_irqs_disabled_flags(unsigned long flags)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	return (flags & MSR_IE) == 0;
}

<<<<<<< HEAD
static inline notrace bool arch_irqs_disabled(void)
=======
static inline bool arch_irqs_disabled(void)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	return arch_irqs_disabled_flags(arch_local_save_flags());
}

#endif /* _ASM_MICROBLAZE_IRQFLAGS_H */
