#ifndef __ARM_MMU_H
#define __ARM_MMU_H

#ifdef CONFIG_MMU

typedef struct {
#ifdef CONFIG_CPU_HAS_ASID
	unsigned int id;
<<<<<<< HEAD
	raw_spinlock_t id_lock;
=======
	spinlock_t id_lock;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#endif
	unsigned int kvm_seq;
} mm_context_t;

#ifdef CONFIG_CPU_HAS_ASID
#define ASID(mm)	((mm)->context.id & 255)

/* init_mm.context.id_lock should be initialized. */
#define INIT_MM_CONTEXT(name)                                                 \
<<<<<<< HEAD
	.context.id_lock    = __RAW_SPIN_LOCK_UNLOCKED(name.context.id_lock),
=======
	.context.id_lock    = __SPIN_LOCK_UNLOCKED(name.context.id_lock),
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#else
#define ASID(mm)	(0)
#endif

#else

/*
 * From nommu.h:
 *  Copyright (C) 2002, David McCullough <davidm@snapgear.com>
 *  modified for 2.6 by Hyok S. Choi <hyok.choi@samsung.com>
 */
typedef struct {
	unsigned long		end_brk;
} mm_context_t;

#endif

<<<<<<< HEAD
/*
 * switch_mm() may do a full cache flush over the context switch,
 * so enable interrupts over the context switch to avoid high
 * latency.
 */
#define __ARCH_WANT_INTERRUPTS_ON_CTXSW

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#endif
