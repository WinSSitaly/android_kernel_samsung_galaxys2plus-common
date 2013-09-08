#ifndef _LINUX_SECCOMP_H
#define _LINUX_SECCOMP_H


#ifdef CONFIG_SECCOMP

#include <linux/thread_info.h>
#include <asm/seccomp.h>

typedef struct { int mode; } seccomp_t;

extern void __secure_computing(int);
static inline void secure_computing(int this_syscall)
{
	if (unlikely(test_thread_flag(TIF_SECCOMP)))
		__secure_computing(this_syscall);
}

extern long prctl_get_seccomp(void);
extern long prctl_set_seccomp(unsigned long);

<<<<<<< HEAD
static inline int seccomp_mode(seccomp_t *s)
{
	return s->mode;
}

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#else /* CONFIG_SECCOMP */

#include <linux/errno.h>

typedef struct { } seccomp_t;

#define secure_computing(x) do { } while (0)

static inline long prctl_get_seccomp(void)
{
	return -EINVAL;
}

static inline long prctl_set_seccomp(unsigned long arg2)
{
	return -EINVAL;
}

<<<<<<< HEAD
static inline int seccomp_mode(seccomp_t *s)
{
	return 0;
}

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#endif /* CONFIG_SECCOMP */

#endif /* _LINUX_SECCOMP_H */
