#ifndef _ASM_GENERIC_CPUTIME_H
#define _ASM_GENERIC_CPUTIME_H

#include <linux/time.h>
#include <linux/jiffies.h>

<<<<<<< HEAD
typedef unsigned long __nocast cputime_t;

#define cputime_one_jiffy		jiffies_to_cputime(1)
#define cputime_to_jiffies(__ct)	(__force unsigned long)(__ct)
#define cputime_to_scaled(__ct)		(__ct)
#define jiffies_to_cputime(__hz)	(__force cputime_t)(__hz)

typedef u64 __nocast cputime64_t;

#define cputime64_to_jiffies64(__ct)	(__force u64)(__ct)
#define jiffies64_to_cputime64(__jif)	(__force cputime64_t)(__jif)

#define nsecs_to_cputime64(__ct)	\
	jiffies64_to_cputime64(nsecs_to_jiffies64(__ct))
=======
typedef unsigned long cputime_t;

#define cputime_zero			(0UL)
#define cputime_one_jiffy		jiffies_to_cputime(1)
#define cputime_max			((~0UL >> 1) - 1)
#define cputime_add(__a, __b)		((__a) +  (__b))
#define cputime_sub(__a, __b)		((__a) -  (__b))
#define cputime_div(__a, __n)		((__a) /  (__n))
#define cputime_halve(__a)		((__a) >> 1)
#define cputime_eq(__a, __b)		((__a) == (__b))
#define cputime_gt(__a, __b)		((__a) >  (__b))
#define cputime_ge(__a, __b)		((__a) >= (__b))
#define cputime_lt(__a, __b)		((__a) <  (__b))
#define cputime_le(__a, __b)		((__a) <= (__b))
#define cputime_to_jiffies(__ct)	(__ct)
#define cputime_to_scaled(__ct)		(__ct)
#define jiffies_to_cputime(__hz)	(__hz)

typedef u64 cputime64_t;

#define cputime64_zero (0ULL)
#define cputime64_add(__a, __b)		((__a) + (__b))
#define cputime64_sub(__a, __b)		((__a) - (__b))
#define cputime64_to_jiffies64(__ct)	(__ct)
#define jiffies64_to_cputime64(__jif)	(__jif)
#define cputime_to_cputime64(__ct)	((u64) __ct)
#define cputime64_gt(__a, __b)		((__a) >  (__b))

#define nsecs_to_cputime64(__ct)	nsecs_to_jiffies64(__ct)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip


/*
 * Convert cputime to microseconds and back.
 */
<<<<<<< HEAD
#define cputime_to_usecs(__ct)		\
	jiffies_to_usecs(cputime_to_jiffies(__ct))
#define usecs_to_cputime(__usec)	\
	jiffies_to_cputime(usecs_to_jiffies(__usec))
#define usecs_to_cputime64(__usec)	\
	jiffies64_to_cputime64(nsecs_to_jiffies64((__usec) * 1000))
=======
#define cputime_to_usecs(__ct)		jiffies_to_usecs(__ct);
#define usecs_to_cputime(__msecs)	usecs_to_jiffies(__msecs);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

/*
 * Convert cputime to seconds and back.
 */
<<<<<<< HEAD
#define cputime_to_secs(jif)		(cputime_to_jiffies(jif) / HZ)
#define secs_to_cputime(sec)		jiffies_to_cputime((sec) * HZ)
=======
#define cputime_to_secs(jif)		((jif) / HZ)
#define secs_to_cputime(sec)		((sec) * HZ)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

/*
 * Convert cputime to timespec and back.
 */
<<<<<<< HEAD
#define timespec_to_cputime(__val)	\
	jiffies_to_cputime(timespec_to_jiffies(__val))
#define cputime_to_timespec(__ct,__val)	\
	jiffies_to_timespec(cputime_to_jiffies(__ct),__val)
=======
#define timespec_to_cputime(__val)	timespec_to_jiffies(__val)
#define cputime_to_timespec(__ct,__val)	jiffies_to_timespec(__ct,__val)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

/*
 * Convert cputime to timeval and back.
 */
<<<<<<< HEAD
#define timeval_to_cputime(__val)	\
	jiffies_to_cputime(timeval_to_jiffies(__val))
#define cputime_to_timeval(__ct,__val)	\
	jiffies_to_timeval(cputime_to_jiffies(__ct),__val)
=======
#define timeval_to_cputime(__val)	timeval_to_jiffies(__val)
#define cputime_to_timeval(__ct,__val)	jiffies_to_timeval(__ct,__val)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

/*
 * Convert cputime to clock and back.
 */
<<<<<<< HEAD
#define cputime_to_clock_t(__ct)	\
	jiffies_to_clock_t(cputime_to_jiffies(__ct))
#define clock_t_to_cputime(__x)		\
	jiffies_to_cputime(clock_t_to_jiffies(__x))
=======
#define cputime_to_clock_t(__ct)	jiffies_to_clock_t(__ct)
#define clock_t_to_cputime(__x)		clock_t_to_jiffies(__x)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

/*
 * Convert cputime64 to clock.
 */
<<<<<<< HEAD
#define cputime64_to_clock_t(__ct)	\
	jiffies_64_to_clock_t(cputime64_to_jiffies64(__ct))
=======
#define cputime64_to_clock_t(__ct)	jiffies_64_to_clock_t(__ct)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#endif
