#ifndef _H8300_TYPES_H
#define _H8300_TYPES_H

#include <asm-generic/int-ll64.h>

<<<<<<< HEAD
=======
#if !defined(__ASSEMBLY__)

/*
 * This file is never included by application software unless
 * explicitly requested (e.g., via linux/types.h) in which case the
 * application is Linux specific so (user-) name space pollution is
 * not a major issue.  However, for interoperability, libraries still
 * need to be careful to avoid a name clashes.
 */

typedef unsigned short umode_t;

/*
 * These aren't exported outside the kernel to avoid name space clashes
 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#ifdef __KERNEL__

#define BITS_PER_LONG 32

#endif /* __KERNEL__ */

<<<<<<< HEAD
=======
#endif /* __ASSEMBLY__ */

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#endif /* _H8300_TYPES_H */
