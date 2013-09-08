#ifndef _H8300_BUG_H
#define _H8300_BUG_H

/* always true */
#define is_valid_bugaddr(addr) (1)

#include <asm-generic/bug.h>
<<<<<<< HEAD

struct pt_regs;
extern void die(const char *str, struct pt_regs *fp, unsigned long err);

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#endif
