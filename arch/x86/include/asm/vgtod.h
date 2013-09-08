#ifndef _ASM_X86_VGTOD_H
#define _ASM_X86_VGTOD_H

#include <asm/vsyscall.h>
#include <linux/clocksource.h>

struct vsyscall_gtod_data {
<<<<<<< HEAD
	seqcount_t	seq;

	struct { /* extract of a clocksource struct */
		int vclock_mode;
=======
	seqlock_t	lock;

	/* open coded 'struct timespec' */
	time_t		wall_time_sec;
	u32		wall_time_nsec;

	int		sysctl_enabled;
	struct timezone sys_tz;
	struct { /* extract of a clocksource struct */
		cycle_t (*vread)(void);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		cycle_t	cycle_last;
		cycle_t	mask;
		u32	mult;
		u32	shift;
	} clock;
<<<<<<< HEAD

	/* open coded 'struct timespec' */
	time_t		wall_time_sec;
	u32		wall_time_nsec;
	u32		monotonic_time_nsec;
	time_t		monotonic_time_sec;

	struct timezone sys_tz;
	struct timespec wall_time_coarse;
	struct timespec monotonic_time_coarse;
=======
	struct timespec wall_to_monotonic;
	struct timespec wall_time_coarse;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
};
extern struct vsyscall_gtod_data vsyscall_gtod_data;

#endif /* _ASM_X86_VGTOD_H */
