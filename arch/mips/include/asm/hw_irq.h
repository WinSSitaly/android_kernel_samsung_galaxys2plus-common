/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2000, 2001, 2002 by Ralf Baechle
 */
#ifndef __ASM_HW_IRQ_H
#define __ASM_HW_IRQ_H

<<<<<<< HEAD
#include <linux/atomic.h>
=======
#include <asm/atomic.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

extern atomic_t irq_err_count;

/*
 * interrupt-retrigger: NOP for now. This may not be appropriate for all
 * machines, we'll see ...
 */

#endif /* __ASM_HW_IRQ_H */
