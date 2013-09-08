/*
 * Copyright (C) 2011 Jean-Christophe PLAGNIOL-VILLARD <plagnioj@jcrosoft.com>
 *
 * Under GPLv2 only
 */

#ifndef __ARCH_SYSTEM_REV_H__
#define __ARCH_SYSTEM_REV_H__

<<<<<<< HEAD
#include <asm/system_info.h>

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
/*
 * board revision encoding
 * mach specific
 * the 16-31 bit are reserved for at91 generic information
 *
 * bit 31:
 *	0 => nand 8 bit
 *	1 => nand 16 bit
 */
#define BOARD_HAVE_NAND_16BIT	(1 << 31)
static inline int board_have_nand_16bit(void)
{
<<<<<<< HEAD
	return (system_rev & BOARD_HAVE_NAND_16BIT) ? 1 : 0;
=======
	return system_rev & BOARD_HAVE_NAND_16BIT;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

#endif /* __ARCH_SYSTEM_REV_H__ */
