/*
 *  linux/arch/arm/lib/changebit.S
 *
 *  Copyright (C) 1995-1996 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/linkage.h>
#include <asm/assembler.h>
#include "bitops.h"
                .text

<<<<<<< HEAD
bitop	_change_bit, eor
=======
ENTRY(_change_bit)
	bitop	eor
ENDPROC(_change_bit)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
