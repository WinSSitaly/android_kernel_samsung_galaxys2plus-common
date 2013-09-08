/*
 * Copyright (C) 2004-2006 Atmel Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __ASM_AVR32_TYPES_H
#define __ASM_AVR32_TYPES_H

#include <asm-generic/int-ll64.h>

<<<<<<< HEAD
=======
#ifndef __ASSEMBLY__

typedef unsigned short umode_t;

#endif /* __ASSEMBLY__ */

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
/*
 * These aren't exported outside the kernel to avoid name space clashes
 */
#ifdef __KERNEL__

#define BITS_PER_LONG 32

#endif /* __KERNEL__ */


#endif /* __ASM_AVR32_TYPES_H */
