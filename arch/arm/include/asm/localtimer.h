/*
 *  arch/arm/include/asm/localtimer.h
 *
 *  Copyright (C) 2004-2005 ARM Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __ASM_ARM_LOCALTIMER_H
#define __ASM_ARM_LOCALTIMER_H

<<<<<<< HEAD
#include <linux/errno.h>

struct clock_event_device;

struct local_timer_ops {
	int  (*setup)(struct clock_event_device *);
	void (*stop)(struct clock_event_device *);
};

#ifdef CONFIG_LOCAL_TIMERS
/*
 * Register a local timer driver
 */
int local_timer_register(struct local_timer_ops *);
#else
static inline int local_timer_register(struct local_timer_ops *ops)
{
	return -ENXIO;
}
#endif

#endif
=======
struct clock_event_device;
/*
 * Setup a per-cpu timer, whether it be a local timer or dummy broadcast
 */
void percpu_timer_setup(void);

/*
 * Called from assembly, this is the local timer IRQ handler
 */
asmlinkage void do_local_timer(struct pt_regs *);

#ifdef CONFIG_LOCAL_TIMERS

#ifdef CONFIG_HAVE_ARM_TWD
#include "smp_twd.h"
#define local_timer_ack()	twd_timer_ack()

#else
/*
 * Platform provides this to acknowledge a local timer IRQ.
 * Returns true if the local timer IRQ is to be processed.
 */
int local_timer_ack(void);
#endif

/*
 * Setup a local timer interrupt for a CPU.
 */
int local_timer_setup(struct clock_event_device *);

#else	/* !CONFIG_LOCAL_TIMERS */
static inline int local_timer_setup(struct clock_event_device *evt)
{
	return -ENXIO;
}

#endif	/* CONFIG_LOCAL_TIMERS */

#endif	/* __ASM_ARM_LOCALTIMER_H */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
