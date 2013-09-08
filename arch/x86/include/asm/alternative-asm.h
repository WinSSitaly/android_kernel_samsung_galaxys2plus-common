#ifdef __ASSEMBLY__

#include <asm/asm.h>

#ifdef CONFIG_SMP
	.macro LOCK_PREFIX
<<<<<<< HEAD
672:	lock
	.section .smp_locks,"a"
	.balign 4
	.long 672b - .
=======
1:	lock
	.section .smp_locks,"a"
	.balign 4
	.long 1b - .
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	.previous
	.endm
#else
	.macro LOCK_PREFIX
	.endm
#endif

.macro altinstruction_entry orig alt feature orig_len alt_len
<<<<<<< HEAD
	.long \orig - .
	.long \alt - .
=======
	.align 8
	.quad \orig
	.quad \alt
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	.word \feature
	.byte \orig_len
	.byte \alt_len
.endm

#endif  /*  __ASSEMBLY__  */
