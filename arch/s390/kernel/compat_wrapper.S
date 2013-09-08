/*
*  arch/s390/kernel/compat_wrapper.S
*    wrapper for 31 bit compatible system calls.
*
*    Copyright (C) IBM Corp. 2000,2006
*    Author(s): Gerhard Tonn (ton@de.ibm.com),
*		Thomas Spatzier (tspat@de.ibm.com)
*/

<<<<<<< HEAD
#include <linux/linkage.h>

ENTRY(sys32_exit_wrapper)
	lgfr	%r2,%r2			# int
	jg	sys_exit		# branch to sys_exit

ENTRY(sys32_read_wrapper)
=======
	.globl	sys32_exit_wrapper
sys32_exit_wrapper:
	lgfr	%r2,%r2			# int
	jg	sys_exit		# branch to sys_exit

	.globl	sys32_read_wrapper
sys32_read_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# char *
	llgfr	%r4,%r4			# size_t
	jg	sys32_read		# branch to sys_read

<<<<<<< HEAD
ENTRY(sys32_write_wrapper)
=======
	.globl	sys32_write_wrapper
sys32_write_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# const char *
	llgfr	%r4,%r4			# size_t
	jg	sys32_write		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_open_wrapper)
=======
	.globl	sys32_open_wrapper
sys32_open_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	lgfr	%r3,%r3			# int
	lgfr	%r4,%r4			# int
	jg	sys_open		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_close_wrapper)
	llgfr	%r2,%r2			# unsigned int
	jg	sys_close		# branch to system call

ENTRY(sys32_creat_wrapper)
=======
	.globl	sys32_close_wrapper
sys32_close_wrapper:
	llgfr	%r2,%r2			# unsigned int
	jg	sys_close		# branch to system call

	.globl	sys32_creat_wrapper
sys32_creat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	lgfr	%r3,%r3			# int
	jg	sys_creat		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_link_wrapper)
=======
	.globl	sys32_link_wrapper
sys32_link_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	llgtr	%r3,%r3			# const char *
	jg	sys_link		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_unlink_wrapper)
	llgtr	%r2,%r2			# const char *
	jg	sys_unlink		# branch to system call

ENTRY(sys32_chdir_wrapper)
	llgtr	%r2,%r2			# const char *
	jg	sys_chdir		# branch to system call

ENTRY(sys32_time_wrapper)
	llgtr	%r2,%r2			# int *
	jg	compat_sys_time		# branch to system call

ENTRY(sys32_mknod_wrapper)
=======
	.globl	sys32_unlink_wrapper
sys32_unlink_wrapper:
	llgtr	%r2,%r2			# const char *
	jg	sys_unlink		# branch to system call

	.globl	sys32_chdir_wrapper
sys32_chdir_wrapper:
	llgtr	%r2,%r2			# const char *
	jg	sys_chdir		# branch to system call

	.globl	sys32_time_wrapper
sys32_time_wrapper:
	llgtr	%r2,%r2			# int *
	jg	compat_sys_time		# branch to system call

	.globl	sys32_mknod_wrapper
sys32_mknod_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	lgfr	%r3,%r3			# int
	llgfr	%r4,%r4			# dev
	jg	sys_mknod		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_chmod_wrapper)
=======
	.globl	sys32_chmod_wrapper
sys32_chmod_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	llgfr	%r3,%r3			# mode_t
	jg	sys_chmod		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_lchown16_wrapper)
=======
	.globl	sys32_lchown16_wrapper
sys32_lchown16_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	llgfr	%r3,%r3			# __kernel_old_uid_emu31_t
	llgfr	%r4,%r4			# __kernel_old_uid_emu31_t
	jg	sys32_lchown16		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_lseek_wrapper)
=======
	.globl	sys32_lseek_wrapper
sys32_lseek_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	lgfr	%r3,%r3			# off_t
	llgfr	%r4,%r4			# unsigned int
	jg	sys_lseek		# branch to system call

#sys32_getpid_wrapper				# void

<<<<<<< HEAD
ENTRY(sys32_mount_wrapper)
=======
	.globl	sys32_mount_wrapper
sys32_mount_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# char *
	llgtr	%r4,%r4			# char *
	llgfr	%r5,%r5			# unsigned long
	llgtr	%r6,%r6			# void *
	jg	compat_sys_mount	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_oldumount_wrapper)
	llgtr	%r2,%r2			# char *
	jg	sys_oldumount		# branch to system call

ENTRY(sys32_setuid16_wrapper)
=======
	.globl	sys32_oldumount_wrapper
sys32_oldumount_wrapper:
	llgtr	%r2,%r2			# char *
	jg	sys_oldumount		# branch to system call

	.globl	sys32_setuid16_wrapper
sys32_setuid16_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# __kernel_old_uid_emu31_t
	jg	sys32_setuid16		# branch to system call

#sys32_getuid16_wrapper			# void

<<<<<<< HEAD
ENTRY(sys32_ptrace_wrapper)
=======
	.globl	sys32_ptrace_wrapper
sys32_ptrace_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# long
	lgfr	%r3,%r3			# long
	llgtr	%r4,%r4			# long
	llgfr	%r5,%r5			# long
	jg	compat_sys_ptrace	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_alarm_wrapper)
	llgfr	%r2,%r2			# unsigned int
	jg	sys_alarm		# branch to system call

ENTRY(compat_sys_utime_wrapper)
=======
	.globl	sys32_alarm_wrapper
sys32_alarm_wrapper:
	llgfr	%r2,%r2			# unsigned int
	jg	sys_alarm		# branch to system call

	.globl	compat_sys_utime_wrapper
compat_sys_utime_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# struct compat_utimbuf *
	jg	compat_sys_utime	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_access_wrapper)
=======
	.globl	sys32_access_wrapper
sys32_access_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	lgfr	%r3,%r3			# int
	jg	sys_access		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_nice_wrapper)
=======
	.globl	sys32_nice_wrapper
sys32_nice_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	jg	sys_nice		# branch to system call

#sys32_sync_wrapper			# void

<<<<<<< HEAD
ENTRY(sys32_kill_wrapper)
=======
	.globl	sys32_kill_wrapper
sys32_kill_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	jg	sys_kill		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_rename_wrapper)
=======
	.globl	sys32_rename_wrapper
sys32_rename_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	llgtr	%r3,%r3			# const char *
	jg	sys_rename		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_mkdir_wrapper)
=======
	.globl	sys32_mkdir_wrapper
sys32_mkdir_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	lgfr	%r3,%r3			# int
	jg	sys_mkdir		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_rmdir_wrapper)
	llgtr	%r2,%r2			# const char *
	jg	sys_rmdir		# branch to system call

ENTRY(sys32_dup_wrapper)
	llgfr	%r2,%r2			# unsigned int
	jg	sys_dup			# branch to system call

ENTRY(sys32_pipe_wrapper)
	llgtr	%r2,%r2			# u32 *
	jg	sys_pipe		# branch to system call

ENTRY(compat_sys_times_wrapper)
	llgtr	%r2,%r2			# struct compat_tms *
	jg	compat_sys_times	# branch to system call

ENTRY(sys32_brk_wrapper)
	llgtr	%r2,%r2			# unsigned long
	jg	sys_brk			# branch to system call

ENTRY(sys32_setgid16_wrapper)
=======
	.globl	sys32_rmdir_wrapper
sys32_rmdir_wrapper:
	llgtr	%r2,%r2			# const char *
	jg	sys_rmdir		# branch to system call

	.globl	sys32_dup_wrapper
sys32_dup_wrapper:
	llgfr	%r2,%r2			# unsigned int
	jg	sys_dup			# branch to system call

	.globl	sys32_pipe_wrapper
sys32_pipe_wrapper:
	llgtr	%r2,%r2			# u32 *
	jg	sys_pipe		# branch to system call

	.globl	compat_sys_times_wrapper
compat_sys_times_wrapper:
	llgtr	%r2,%r2			# struct compat_tms *
	jg	compat_sys_times	# branch to system call

	.globl	sys32_brk_wrapper
sys32_brk_wrapper:
	llgtr	%r2,%r2			# unsigned long
	jg	sys_brk			# branch to system call

	.globl	sys32_setgid16_wrapper
sys32_setgid16_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# __kernel_old_gid_emu31_t
	jg	sys32_setgid16		# branch to system call

#sys32_getgid16_wrapper			# void

<<<<<<< HEAD
ENTRY(sys32_signal_wrapper)
=======
	.globl sys32_signal_wrapper
sys32_signal_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# __sighandler_t
	jg	sys_signal

#sys32_geteuid16_wrapper		# void

#sys32_getegid16_wrapper		# void

<<<<<<< HEAD
ENTRY(sys32_acct_wrapper)
	llgtr	%r2,%r2			# char *
	jg	sys_acct		# branch to system call

ENTRY(sys32_umount_wrapper)
=======
	.globl	sys32_acct_wrapper
sys32_acct_wrapper:
	llgtr	%r2,%r2			# char *
	jg	sys_acct		# branch to system call

	.globl	sys32_umount_wrapper
sys32_umount_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	lgfr	%r3,%r3			# int
	jg	sys_umount		# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_ioctl_wrapper)
=======
	.globl	compat_sys_ioctl_wrapper
compat_sys_ioctl_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgfr	%r3,%r3			# unsigned int
	llgfr	%r4,%r4			# unsigned int
	jg	compat_sys_ioctl	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_fcntl_wrapper)
=======
	.globl	compat_sys_fcntl_wrapper
compat_sys_fcntl_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgfr	%r3,%r3			# unsigned int
	llgfr	%r4,%r4			# unsigned long
	jg	compat_sys_fcntl	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_setpgid_wrapper)
=======
	.globl	sys32_setpgid_wrapper
sys32_setpgid_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# pid_t
	lgfr	%r3,%r3			# pid_t
	jg	sys_setpgid		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_umask_wrapper)
	lgfr	%r2,%r2			# int
	jg	sys_umask		# branch to system call

ENTRY(sys32_chroot_wrapper)
	llgtr	%r2,%r2			# char *
	jg	sys_chroot		# branch to system call

ENTRY(sys32_ustat_wrapper)
=======
	.globl	sys32_umask_wrapper
sys32_umask_wrapper:
	lgfr	%r2,%r2			# int
	jg	sys_umask		# branch to system call

	.globl	sys32_chroot_wrapper
sys32_chroot_wrapper:
	llgtr	%r2,%r2			# char *
	jg	sys_chroot		# branch to system call

	.globl sys32_ustat_wrapper
sys32_ustat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# dev_t
	llgtr	%r3,%r3			# struct ustat *
	jg	compat_sys_ustat

<<<<<<< HEAD
ENTRY(sys32_dup2_wrapper)
=======
	.globl	sys32_dup2_wrapper
sys32_dup2_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgfr	%r3,%r3			# unsigned int
	jg	sys_dup2		# branch to system call

#sys32_getppid_wrapper			# void

#sys32_getpgrp_wrapper			# void

#sys32_setsid_wrapper			# void

<<<<<<< HEAD
ENTRY(sys32_sigaction_wrapper)
=======
	.globl	sys32_sigaction_wrapper
sys32_sigaction_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# const struct old_sigaction *
	llgtr	%r4,%r4			# struct old_sigaction32 *
	jg	sys32_sigaction		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_setreuid16_wrapper)
=======
	.globl	sys32_setreuid16_wrapper
sys32_setreuid16_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# __kernel_old_uid_emu31_t
	llgfr	%r3,%r3			# __kernel_old_uid_emu31_t
	jg	sys32_setreuid16	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_setregid16_wrapper)
=======
	.globl	sys32_setregid16_wrapper
sys32_setregid16_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# __kernel_old_gid_emu31_t
	llgfr	%r3,%r3			# __kernel_old_gid_emu31_t
	jg	sys32_setregid16	# branch to system call

<<<<<<< HEAD
ENTRY(sys_sigsuspend_wrapper)
=======
	.globl sys_sigsuspend_wrapper
sys_sigsuspend_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	llgfr	%r4,%r4			# old_sigset_t
	jg	sys_sigsuspend

<<<<<<< HEAD
ENTRY(compat_sys_sigpending_wrapper)
	llgtr	%r2,%r2			# compat_old_sigset_t *
	jg	compat_sys_sigpending	# branch to system call

ENTRY(sys32_sethostname_wrapper)
=======
	.globl	compat_sys_sigpending_wrapper
compat_sys_sigpending_wrapper:
	llgtr	%r2,%r2			# compat_old_sigset_t *
	jg	compat_sys_sigpending	# branch to system call

	.globl	sys32_sethostname_wrapper
sys32_sethostname_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	lgfr	%r3,%r3			# int
	jg	sys_sethostname		# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_setrlimit_wrapper)
=======
	.globl	compat_sys_setrlimit_wrapper
compat_sys_setrlimit_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# struct rlimit_emu31 *
	jg	compat_sys_setrlimit	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_old_getrlimit_wrapper)
=======
	.globl	compat_sys_old_getrlimit_wrapper
compat_sys_old_getrlimit_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# struct rlimit_emu31 *
	jg	compat_sys_old_getrlimit # branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_getrlimit_wrapper)
=======
	.globl	compat_sys_getrlimit_wrapper
compat_sys_getrlimit_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# struct rlimit_emu31 *
	jg	compat_sys_getrlimit	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_mmap2_wrapper)
	llgtr	%r2,%r2			# struct mmap_arg_struct_emu31 *
	jg	sys32_mmap2			# branch to system call

ENTRY(compat_sys_getrusage_wrapper)
=======
	.globl	sys32_mmap2_wrapper
sys32_mmap2_wrapper:
	llgtr	%r2,%r2			# struct mmap_arg_struct_emu31 *
	jg	sys32_mmap2			# branch to system call

	.globl	compat_sys_getrusage_wrapper
compat_sys_getrusage_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# struct rusage_emu31 *
	jg	compat_sys_getrusage	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_gettimeofday_wrapper)
=======
	.globl	compat_sys_gettimeofday_wrapper
compat_sys_gettimeofday_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# struct timeval_emu31 *
	llgtr	%r3,%r3			# struct timezone *
	jg	compat_sys_gettimeofday	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_settimeofday_wrapper)
=======
	.globl	compat_sys_settimeofday_wrapper
compat_sys_settimeofday_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# struct timeval_emu31 *
	llgtr	%r3,%r3			# struct timezone *
	jg	compat_sys_settimeofday	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_getgroups16_wrapper)
=======
	.globl	sys32_getgroups16_wrapper
sys32_getgroups16_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# __kernel_old_gid_emu31_t *
	jg	sys32_getgroups16	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_setgroups16_wrapper)
=======
	.globl	sys32_setgroups16_wrapper
sys32_setgroups16_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# __kernel_old_gid_emu31_t *
	jg	sys32_setgroups16	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_symlink_wrapper)
=======
	.globl	sys32_symlink_wrapper
sys32_symlink_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	llgtr	%r3,%r3			# const char *
	jg	sys_symlink		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_readlink_wrapper)
=======
	.globl	sys32_readlink_wrapper
sys32_readlink_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	llgtr	%r3,%r3			# char *
	lgfr	%r4,%r4			# int
	jg	sys_readlink		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_uselib_wrapper)
	llgtr	%r2,%r2			# const char *
	jg	sys_uselib		# branch to system call

ENTRY(sys32_swapon_wrapper)
=======
	.globl	sys32_uselib_wrapper
sys32_uselib_wrapper:
	llgtr	%r2,%r2			# const char *
	jg	sys_uselib		# branch to system call

	.globl	sys32_swapon_wrapper
sys32_swapon_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	lgfr	%r3,%r3			# int
	jg	sys_swapon		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_reboot_wrapper)
=======
	.globl	sys32_reboot_wrapper
sys32_reboot_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	llgfr	%r4,%r4			# unsigned int
	llgtr	%r5,%r5			# void *
	jg	sys_reboot		# branch to system call

<<<<<<< HEAD
ENTRY(old32_readdir_wrapper)
=======
	.globl	old32_readdir_wrapper
old32_readdir_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# void *
	llgfr	%r4,%r4			# unsigned int
	jg	compat_sys_old_readdir	# branch to system call

<<<<<<< HEAD
ENTRY(old32_mmap_wrapper)
	llgtr	%r2,%r2			# struct mmap_arg_struct_emu31 *
	jg	old32_mmap		# branch to system call

ENTRY(sys32_munmap_wrapper)
=======
	.globl	old32_mmap_wrapper
old32_mmap_wrapper:
	llgtr	%r2,%r2			# struct mmap_arg_struct_emu31 *
	jg	old32_mmap		# branch to system call

	.globl	sys32_munmap_wrapper
sys32_munmap_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned long
	llgfr	%r3,%r3			# size_t
	jg	sys_munmap		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_truncate_wrapper)
=======
	.globl	sys32_truncate_wrapper
sys32_truncate_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	lgfr	%r3,%r3			# long
	jg	sys_truncate		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_ftruncate_wrapper)
=======
	.globl	sys32_ftruncate_wrapper
sys32_ftruncate_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgfr	%r3,%r3			# unsigned long
	jg	sys_ftruncate		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_fchmod_wrapper)
=======
	.globl	sys32_fchmod_wrapper
sys32_fchmod_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgfr	%r3,%r3			# mode_t
	jg	sys_fchmod		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_fchown16_wrapper)
=======
	.globl	sys32_fchown16_wrapper
sys32_fchown16_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgfr	%r3,%r3			# compat_uid_t
	llgfr	%r4,%r4			# compat_uid_t
	jg	sys32_fchown16		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_getpriority_wrapper)
=======
	.globl	sys32_getpriority_wrapper
sys32_getpriority_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	jg	sys_getpriority		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_setpriority_wrapper)
=======
	.globl	sys32_setpriority_wrapper
sys32_setpriority_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	lgfr	%r4,%r4			# int
	jg	sys_setpriority		# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_statfs_wrapper)
=======
	.globl	compat_sys_statfs_wrapper
compat_sys_statfs_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# struct compat_statfs *
	jg	compat_sys_statfs	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_fstatfs_wrapper)
=======
	.globl	compat_sys_fstatfs_wrapper
compat_sys_fstatfs_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# struct compat_statfs *
	jg	compat_sys_fstatfs	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_socketcall_wrapper)
=======
	.globl	compat_sys_socketcall_wrapper
compat_sys_socketcall_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# u32 *
	jg	compat_sys_socketcall	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_syslog_wrapper)
=======
	.globl	sys32_syslog_wrapper
sys32_syslog_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# char *
	lgfr	%r4,%r4			# int
	jg	sys_syslog		# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_setitimer_wrapper)
=======
	.globl	compat_sys_setitimer_wrapper
compat_sys_setitimer_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# struct itimerval_emu31 *
	llgtr	%r4,%r4			# struct itimerval_emu31 *
	jg	compat_sys_setitimer	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_getitimer_wrapper)
=======
	.globl	compat_sys_getitimer_wrapper
compat_sys_getitimer_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# struct itimerval_emu31 *
	jg	compat_sys_getitimer	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_newstat_wrapper)
=======
	.globl	compat_sys_newstat_wrapper
compat_sys_newstat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# struct stat_emu31 *
	jg	compat_sys_newstat	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_newlstat_wrapper)
=======
	.globl	compat_sys_newlstat_wrapper
compat_sys_newlstat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# struct stat_emu31 *
	jg	compat_sys_newlstat	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_newfstat_wrapper)
=======
	.globl	compat_sys_newfstat_wrapper
compat_sys_newfstat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# struct stat_emu31 *
	jg	compat_sys_newfstat	# branch to system call

#sys32_vhangup_wrapper			# void

<<<<<<< HEAD
ENTRY(compat_sys_wait4_wrapper)
=======
	.globl	compat_sys_wait4_wrapper
compat_sys_wait4_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# pid_t
	llgtr	%r3,%r3			# unsigned int *
	lgfr	%r4,%r4			# int
	llgtr	%r5,%r5			# struct rusage *
	jg	compat_sys_wait4	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_swapoff_wrapper)
	llgtr	%r2,%r2			# const char *
	jg	sys_swapoff		# branch to system call

ENTRY(compat_sys_sysinfo_wrapper)
	llgtr	%r2,%r2			# struct sysinfo_emu31 *
	jg	compat_sys_sysinfo	# branch to system call

ENTRY(sys32_ipc_wrapper)
=======
	.globl	sys32_swapoff_wrapper
sys32_swapoff_wrapper:
	llgtr	%r2,%r2			# const char *
	jg	sys_swapoff		# branch to system call

	.globl	compat_sys_sysinfo_wrapper
compat_sys_sysinfo_wrapper:
	llgtr	%r2,%r2			# struct sysinfo_emu31 *
	jg	compat_sys_sysinfo	# branch to system call

	.globl	sys32_ipc_wrapper
sys32_ipc_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# uint
	lgfr	%r3,%r3			# int
	lgfr	%r4,%r4			# int
	lgfr	%r5,%r5			# int
	llgfr	%r6,%r6			# u32
	jg	sys32_ipc		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_fsync_wrapper)
=======
	.globl	sys32_fsync_wrapper
sys32_fsync_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	jg	sys_fsync		# branch to system call

#sys32_sigreturn_wrapper		# done in sigreturn_glue

#sys32_clone_wrapper			# done in clone_glue

<<<<<<< HEAD
ENTRY(sys32_setdomainname_wrapper)
=======
	.globl	sys32_setdomainname_wrapper
sys32_setdomainname_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	lgfr	%r3,%r3			# int
	jg	sys_setdomainname	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_newuname_wrapper)
	llgtr	%r2,%r2			# struct new_utsname *
	jg	sys_newuname		# branch to system call

ENTRY(compat_sys_adjtimex_wrapper)
	llgtr	%r2,%r2			# struct compat_timex *
	jg	compat_sys_adjtimex	# branch to system call

ENTRY(sys32_mprotect_wrapper)
=======
	.globl	sys32_newuname_wrapper
sys32_newuname_wrapper:
	llgtr	%r2,%r2			# struct new_utsname *
	jg	sys_newuname		# branch to system call

	.globl	compat_sys_adjtimex_wrapper
compat_sys_adjtimex_wrapper:
	llgtr	%r2,%r2			# struct compat_timex *
	jg	compat_sys_adjtimex	# branch to system call

	.globl	sys32_mprotect_wrapper
sys32_mprotect_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# unsigned long (actually pointer
	llgfr	%r3,%r3			# size_t
	llgfr	%r4,%r4			# unsigned long
	jg	sys_mprotect		# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_sigprocmask_wrapper)
=======
	.globl	compat_sys_sigprocmask_wrapper
compat_sys_sigprocmask_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# compat_old_sigset_t *
	llgtr	%r4,%r4			# compat_old_sigset_t *
	jg	compat_sys_sigprocmask		# branch to system call

<<<<<<< HEAD
ENTRY(sys_init_module_wrapper)
=======
	.globl	sys_init_module_wrapper
sys_init_module_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# void *
	llgfr	%r3,%r3			# unsigned long
	llgtr	%r4,%r4			# char *
	jg	sys_init_module		# branch to system call

<<<<<<< HEAD
ENTRY(sys_delete_module_wrapper)
=======
	.globl	sys_delete_module_wrapper
sys_delete_module_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	llgfr	%r3,%r3			# unsigned int
	jg	sys_delete_module	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_quotactl_wrapper)
=======
	.globl	sys32_quotactl_wrapper
sys32_quotactl_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# const char *
	llgfr	%r4,%r4			# qid_t
	llgtr	%r5,%r5			# caddr_t
	jg	sys_quotactl		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_getpgid_wrapper)
	lgfr	%r2,%r2			# pid_t
	jg	sys_getpgid		# branch to system call

ENTRY(sys32_fchdir_wrapper)
	llgfr	%r2,%r2			# unsigned int
	jg	sys_fchdir		# branch to system call

ENTRY(sys32_bdflush_wrapper)
=======
	.globl	sys32_getpgid_wrapper
sys32_getpgid_wrapper:
	lgfr	%r2,%r2			# pid_t
	jg	sys_getpgid		# branch to system call

	.globl	sys32_fchdir_wrapper
sys32_fchdir_wrapper:
	llgfr	%r2,%r2			# unsigned int
	jg	sys_fchdir		# branch to system call

	.globl	sys32_bdflush_wrapper
sys32_bdflush_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# long
	jg	sys_bdflush		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_sysfs_wrapper)
=======
	.globl	sys32_sysfs_wrapper
sys32_sysfs_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgfr	%r3,%r3			# unsigned long
	llgfr	%r4,%r4			# unsigned long
	jg	sys_sysfs		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_personality_wrapper)
	llgfr	%r2,%r2			# unsigned int
	jg	sys_s390_personality	# branch to system call

ENTRY(sys32_setfsuid16_wrapper)
	llgfr	%r2,%r2			# __kernel_old_uid_emu31_t
	jg	sys32_setfsuid16	# branch to system call

ENTRY(sys32_setfsgid16_wrapper)
	llgfr	%r2,%r2			# __kernel_old_gid_emu31_t
	jg	sys32_setfsgid16	# branch to system call

ENTRY(sys32_llseek_wrapper)
=======
	.globl	sys32_personality_wrapper
sys32_personality_wrapper:
	llgfr	%r2,%r2			# unsigned int
	jg	sys_s390_personality	# branch to system call

	.globl	sys32_setfsuid16_wrapper
sys32_setfsuid16_wrapper:
	llgfr	%r2,%r2			# __kernel_old_uid_emu31_t
	jg	sys32_setfsuid16	# branch to system call

	.globl	sys32_setfsgid16_wrapper
sys32_setfsgid16_wrapper:
	llgfr	%r2,%r2			# __kernel_old_gid_emu31_t
	jg	sys32_setfsgid16	# branch to system call

	.globl	sys32_llseek_wrapper
sys32_llseek_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgfr	%r3,%r3			# unsigned long
	llgfr	%r4,%r4			# unsigned long
	llgtr	%r5,%r5			# loff_t *
	llgfr	%r6,%r6			# unsigned int
	jg	sys_llseek		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_getdents_wrapper)
=======
	.globl	sys32_getdents_wrapper
sys32_getdents_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# void *
	llgfr	%r4,%r4			# unsigned int
	jg	compat_sys_getdents	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_select_wrapper)
=======
	.globl	compat_sys_select_wrapper
compat_sys_select_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# compat_fd_set *
	llgtr	%r4,%r4			# compat_fd_set *
	llgtr	%r5,%r5			# compat_fd_set *
	llgtr	%r6,%r6			# struct compat_timeval *
	jg	compat_sys_select	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_flock_wrapper)
=======
	.globl	sys32_flock_wrapper
sys32_flock_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgfr	%r3,%r3			# unsigned int
	jg	sys_flock		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_msync_wrapper)
=======
	.globl	sys32_msync_wrapper
sys32_msync_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned long
	llgfr	%r3,%r3			# size_t
	lgfr	%r4,%r4			# int
	jg	sys_msync		# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_readv_wrapper)
=======
	.globl	compat_sys_readv_wrapper
compat_sys_readv_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# const struct compat_iovec *
	llgfr	%r4,%r4			# unsigned long
	jg	compat_sys_readv	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_writev_wrapper)
=======
	.globl	compat_sys_writev_wrapper
compat_sys_writev_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# const struct compat_iovec *
	llgfr	%r4,%r4			# unsigned long
	jg	compat_sys_writev	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_getsid_wrapper)
	lgfr	%r2,%r2			# pid_t
	jg	sys_getsid		# branch to system call

ENTRY(sys32_fdatasync_wrapper)
	llgfr	%r2,%r2			# unsigned int
	jg	sys_fdatasync		# branch to system call

ENTRY(sys32_mlock_wrapper)
=======
	.globl	sys32_getsid_wrapper
sys32_getsid_wrapper:
	lgfr	%r2,%r2			# pid_t
	jg	sys_getsid		# branch to system call

	.globl	sys32_fdatasync_wrapper
sys32_fdatasync_wrapper:
	llgfr	%r2,%r2			# unsigned int
	jg	sys_fdatasync		# branch to system call

	.globl	sys32_mlock_wrapper
sys32_mlock_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned long
	llgfr	%r3,%r3			# size_t
	jg	sys_mlock		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_munlock_wrapper)
=======
	.globl	sys32_munlock_wrapper
sys32_munlock_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned long
	llgfr	%r3,%r3			# size_t
	jg	sys_munlock		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_mlockall_wrapper)
=======
	.globl	sys32_mlockall_wrapper
sys32_mlockall_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	jg	sys_mlockall		# branch to system call

#sys32_munlockall_wrapper		# void

<<<<<<< HEAD
ENTRY(sys32_sched_setparam_wrapper)
=======
	.globl	sys32_sched_setparam_wrapper
sys32_sched_setparam_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# pid_t
	llgtr	%r3,%r3			# struct sched_param *
	jg	sys_sched_setparam	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_sched_getparam_wrapper)
=======
	.globl	sys32_sched_getparam_wrapper
sys32_sched_getparam_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# pid_t
	llgtr	%r3,%r3			# struct sched_param *
	jg	sys_sched_getparam	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_sched_setscheduler_wrapper)
=======
	.globl	sys32_sched_setscheduler_wrapper
sys32_sched_setscheduler_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# pid_t
	lgfr	%r3,%r3			# int
	llgtr	%r4,%r4			# struct sched_param *
	jg	sys_sched_setscheduler	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_sched_getscheduler_wrapper)
=======
	.globl	sys32_sched_getscheduler_wrapper
sys32_sched_getscheduler_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# pid_t
	jg	sys_sched_getscheduler	# branch to system call

#sys32_sched_yield_wrapper		# void

<<<<<<< HEAD
ENTRY(sys32_sched_get_priority_max_wrapper)
	lgfr	%r2,%r2			# int
	jg	sys_sched_get_priority_max	# branch to system call

ENTRY(sys32_sched_get_priority_min_wrapper)
	lgfr	%r2,%r2			# int
	jg	sys_sched_get_priority_min	# branch to system call

ENTRY(sys32_sched_rr_get_interval_wrapper)
=======
	.globl	sys32_sched_get_priority_max_wrapper
sys32_sched_get_priority_max_wrapper:
	lgfr	%r2,%r2			# int
	jg	sys_sched_get_priority_max	# branch to system call

	.globl	sys32_sched_get_priority_min_wrapper
sys32_sched_get_priority_min_wrapper:
	lgfr	%r2,%r2			# int
	jg	sys_sched_get_priority_min	# branch to system call

	.globl	sys32_sched_rr_get_interval_wrapper
sys32_sched_rr_get_interval_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# pid_t
	llgtr	%r3,%r3			# struct compat_timespec *
	jg	sys32_sched_rr_get_interval	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_nanosleep_wrapper)
=======
	.globl	compat_sys_nanosleep_wrapper
compat_sys_nanosleep_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# struct compat_timespec *
	llgtr	%r3,%r3			# struct compat_timespec *
	jg	compat_sys_nanosleep		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_mremap_wrapper)
=======
	.globl	sys32_mremap_wrapper
sys32_mremap_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned long
	llgfr	%r3,%r3			# unsigned long
	llgfr	%r4,%r4			# unsigned long
	llgfr	%r5,%r5			# unsigned long
	llgfr	%r6,%r6			# unsigned long
	jg	sys_mremap		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_setresuid16_wrapper)
=======
	.globl	sys32_setresuid16_wrapper
sys32_setresuid16_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# __kernel_old_uid_emu31_t
	llgfr	%r3,%r3			# __kernel_old_uid_emu31_t
	llgfr	%r4,%r4			# __kernel_old_uid_emu31_t
	jg	sys32_setresuid16	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_getresuid16_wrapper)
=======
	.globl	sys32_getresuid16_wrapper
sys32_getresuid16_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# __kernel_old_uid_emu31_t *
	llgtr	%r3,%r3			# __kernel_old_uid_emu31_t *
	llgtr	%r4,%r4			# __kernel_old_uid_emu31_t *
	jg	sys32_getresuid16	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_poll_wrapper)
	llgtr	%r2,%r2			# struct pollfd *
	llgfr	%r3,%r3			# unsigned int
	lgfr	%r4,%r4			# int
	jg	sys_poll		# branch to system call

ENTRY(sys32_setresgid16_wrapper)
=======
	.globl	sys32_poll_wrapper
sys32_poll_wrapper:
	llgtr	%r2,%r2			# struct pollfd *
	llgfr	%r3,%r3			# unsigned int
	lgfr	%r4,%r4			# long
	jg	sys_poll		# branch to system call

	.globl	compat_sys_nfsservctl_wrapper
compat_sys_nfsservctl_wrapper:
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# struct compat_nfsctl_arg*
	llgtr	%r4,%r4			# union compat_nfsctl_res*
	jg	compat_sys_nfsservctl	# branch to system call

	.globl	sys32_setresgid16_wrapper
sys32_setresgid16_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# __kernel_old_gid_emu31_t
	llgfr	%r3,%r3			# __kernel_old_gid_emu31_t
	llgfr	%r4,%r4			# __kernel_old_gid_emu31_t
	jg	sys32_setresgid16	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_getresgid16_wrapper)
=======
	.globl	sys32_getresgid16_wrapper
sys32_getresgid16_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# __kernel_old_gid_emu31_t *
	llgtr	%r3,%r3			# __kernel_old_gid_emu31_t *
	llgtr	%r4,%r4			# __kernel_old_gid_emu31_t *
	jg	sys32_getresgid16	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_prctl_wrapper)
=======
	.globl	sys32_prctl_wrapper
sys32_prctl_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgfr	%r3,%r3			# unsigned long
	llgfr	%r4,%r4			# unsigned long
	llgfr	%r5,%r5			# unsigned long
	llgfr	%r6,%r6			# unsigned long
	jg	sys_prctl		# branch to system call

#sys32_rt_sigreturn_wrapper		# done in rt_sigreturn_glue

<<<<<<< HEAD
ENTRY(sys32_rt_sigaction_wrapper)
=======
	.globl	sys32_rt_sigaction_wrapper
sys32_rt_sigaction_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# const struct sigaction_emu31 *
	llgtr	%r4,%r4			# const struct sigaction_emu31 *
	llgfr	%r5,%r5			# size_t
	jg	sys32_rt_sigaction	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_rt_sigprocmask_wrapper)
=======
	.globl	sys32_rt_sigprocmask_wrapper
sys32_rt_sigprocmask_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# old_sigset_emu31 *
	llgtr	%r4,%r4			# old_sigset_emu31 *
	llgfr	%r5,%r5			# size_t
	jg	sys32_rt_sigprocmask	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_rt_sigpending_wrapper)
=======
	.globl	sys32_rt_sigpending_wrapper
sys32_rt_sigpending_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# sigset_emu31 *
	llgfr	%r3,%r3			# size_t
	jg	sys32_rt_sigpending	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_rt_sigtimedwait_wrapper)
=======
	.globl	compat_sys_rt_sigtimedwait_wrapper
compat_sys_rt_sigtimedwait_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const sigset_emu31_t *
	llgtr	%r3,%r3			# siginfo_emu31_t *
	llgtr	%r4,%r4			# const struct compat_timespec *
	llgfr	%r5,%r5			# size_t
	jg	compat_sys_rt_sigtimedwait	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_rt_sigqueueinfo_wrapper)
=======
	.globl	sys32_rt_sigqueueinfo_wrapper
sys32_rt_sigqueueinfo_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	llgtr	%r4,%r4			# siginfo_emu31_t *
	jg	sys32_rt_sigqueueinfo	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_rt_sigsuspend_wrapper)
=======
	.globl compat_sys_rt_sigsuspend_wrapper
compat_sys_rt_sigsuspend_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# compat_sigset_t *
	llgfr	%r3,%r3			# compat_size_t
	jg	compat_sys_rt_sigsuspend

<<<<<<< HEAD
ENTRY(sys32_pread64_wrapper)
=======
	.globl	sys32_pread64_wrapper
sys32_pread64_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# char *
	llgfr	%r4,%r4			# size_t
	llgfr	%r5,%r5			# u32
	llgfr	%r6,%r6			# u32
	jg	sys32_pread64		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_pwrite64_wrapper)
=======
	.globl	sys32_pwrite64_wrapper
sys32_pwrite64_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# const char *
	llgfr	%r4,%r4			# size_t
	llgfr	%r5,%r5			# u32
	llgfr	%r6,%r6			# u32
	jg	sys32_pwrite64		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_chown16_wrapper)
=======
	.globl	sys32_chown16_wrapper
sys32_chown16_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	llgfr	%r3,%r3			# __kernel_old_uid_emu31_t
	llgfr	%r4,%r4			# __kernel_old_gid_emu31_t
	jg	sys32_chown16		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_getcwd_wrapper)
=======
	.globl	sys32_getcwd_wrapper
sys32_getcwd_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgfr	%r3,%r3			# unsigned long
	jg	sys_getcwd		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_capget_wrapper)
=======
	.globl	sys32_capget_wrapper
sys32_capget_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# cap_user_header_t
	llgtr	%r3,%r3			# cap_user_data_t
	jg	sys_capget		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_capset_wrapper)
=======
	.globl	sys32_capset_wrapper
sys32_capset_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# cap_user_header_t
	llgtr	%r3,%r3			# const cap_user_data_t
	jg	sys_capset		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_sigaltstack_wrapper)
=======
	.globl sys32_sigaltstack_wrapper
sys32_sigaltstack_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const stack_emu31_t *
	llgtr	%r3,%r3			# stack_emu31_t *
	jg	sys32_sigaltstack

<<<<<<< HEAD
ENTRY(sys32_sendfile_wrapper)
=======
	.globl	sys32_sendfile_wrapper
sys32_sendfile_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	llgtr	%r4,%r4			# __kernel_off_emu31_t *
	llgfr	%r5,%r5			# size_t
	jg	sys32_sendfile		# branch to system call

#sys32_vfork_wrapper			# done in vfork_glue

<<<<<<< HEAD
ENTRY(sys32_truncate64_wrapper)
=======
	.globl	sys32_truncate64_wrapper
sys32_truncate64_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	llgfr	%r3,%r3			# unsigned long
	llgfr	%r4,%r4			# unsigned long
	jg	sys32_truncate64	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_ftruncate64_wrapper)
=======
	.globl	sys32_ftruncate64_wrapper
sys32_ftruncate64_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgfr	%r3,%r3			# unsigned long
	llgfr	%r4,%r4			# unsigned long
	jg	sys32_ftruncate64	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_lchown_wrapper)
=======
	.globl sys32_lchown_wrapper
sys32_lchown_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	llgfr	%r3,%r3			# uid_t
	llgfr	%r4,%r4			# gid_t
	jg	sys_lchown		# branch to system call

#sys32_getuid_wrapper			# void
#sys32_getgid_wrapper			# void
#sys32_geteuid_wrapper			# void
#sys32_getegid_wrapper			# void

<<<<<<< HEAD
ENTRY(sys32_setreuid_wrapper)
=======
	.globl sys32_setreuid_wrapper
sys32_setreuid_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# uid_t
	llgfr	%r3,%r3			# uid_t
	jg	sys_setreuid		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_setregid_wrapper)
=======
	.globl sys32_setregid_wrapper
sys32_setregid_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# gid_t
	llgfr	%r3,%r3			# gid_t
	jg	sys_setregid		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_getgroups_wrapper)
=======
	.globl	sys32_getgroups_wrapper
sys32_getgroups_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# gid_t *
	jg	sys_getgroups		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_setgroups_wrapper)
=======
	.globl	sys32_setgroups_wrapper
sys32_setgroups_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# gid_t *
	jg	sys_setgroups		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_fchown_wrapper)
=======
	.globl sys32_fchown_wrapper
sys32_fchown_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgfr	%r3,%r3			# uid_t
	llgfr	%r4,%r4			# gid_t
	jg	sys_fchown		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_setresuid_wrapper)
=======
	.globl sys32_setresuid_wrapper
sys32_setresuid_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# uid_t
	llgfr	%r3,%r3			# uid_t
	llgfr	%r4,%r4			# uid_t
	jg	sys_setresuid		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_getresuid_wrapper)
=======
	.globl sys32_getresuid_wrapper
sys32_getresuid_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# uid_t *
	llgtr	%r3,%r3			# uid_t *
	llgtr	%r4,%r4			# uid_t *
	jg	sys_getresuid		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_setresgid_wrapper)
=======
	.globl sys32_setresgid_wrapper
sys32_setresgid_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# gid_t
	llgfr	%r3,%r3			# gid_t
	llgfr	%r4,%r4			# gid_t
	jg	sys_setresgid		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_getresgid_wrapper)
=======
	.globl sys32_getresgid_wrapper
sys32_getresgid_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# gid_t *
	llgtr	%r3,%r3			# gid_t *
	llgtr	%r4,%r4			# gid_t *
	jg	sys_getresgid		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_chown_wrapper)
=======
	.globl sys32_chown_wrapper
sys32_chown_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	llgfr	%r3,%r3			# uid_t
	llgfr	%r4,%r4			# gid_t
	jg	sys_chown		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_setuid_wrapper)
	llgfr	%r2,%r2			# uid_t
	jg	sys_setuid		# branch to system call

ENTRY(sys32_setgid_wrapper)
	llgfr	%r2,%r2			# gid_t
	jg	sys_setgid		# branch to system call

ENTRY(sys32_setfsuid_wrapper)
	llgfr	%r2,%r2			# uid_t
	jg	sys_setfsuid		# branch to system call

ENTRY(sys32_setfsgid_wrapper)
	llgfr	%r2,%r2			# gid_t
	jg	sys_setfsgid		# branch to system call

ENTRY(sys32_pivot_root_wrapper)
=======
	.globl sys32_setuid_wrapper
sys32_setuid_wrapper:
	llgfr	%r2,%r2			# uid_t
	jg	sys_setuid		# branch to system call

	.globl sys32_setgid_wrapper
sys32_setgid_wrapper:
	llgfr	%r2,%r2			# gid_t
	jg	sys_setgid		# branch to system call

	.globl sys32_setfsuid_wrapper
sys32_setfsuid_wrapper:
	llgfr	%r2,%r2			# uid_t
	jg	sys_setfsuid		# branch to system call

	.globl sys32_setfsgid_wrapper
sys32_setfsgid_wrapper:
	llgfr	%r2,%r2			# gid_t
	jg	sys_setfsgid		# branch to system call

	.globl	sys32_pivot_root_wrapper
sys32_pivot_root_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	llgtr	%r3,%r3			# const char *
	jg	sys_pivot_root		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_mincore_wrapper)
=======
	.globl	sys32_mincore_wrapper
sys32_mincore_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned long
	llgfr	%r3,%r3			# size_t
	llgtr	%r4,%r4			# unsigned char *
	jg	sys_mincore		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_madvise_wrapper)
=======
	.globl	sys32_madvise_wrapper
sys32_madvise_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned long
	llgfr	%r3,%r3			# size_t
	lgfr	%r4,%r4			# int
	jg	sys_madvise		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_getdents64_wrapper)
=======
	.globl	sys32_getdents64_wrapper
sys32_getdents64_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# void *
	llgfr	%r4,%r4			# unsigned int
	jg	sys_getdents64		# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_fcntl64_wrapper)
=======
	.globl	compat_sys_fcntl64_wrapper
compat_sys_fcntl64_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgfr	%r3,%r3			# unsigned int
	llgfr	%r4,%r4			# unsigned long
	jg	compat_sys_fcntl64	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_stat64_wrapper)
=======
	.globl	sys32_stat64_wrapper
sys32_stat64_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# struct stat64 *
	jg	sys32_stat64		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_lstat64_wrapper)
=======
	.globl	sys32_lstat64_wrapper
sys32_lstat64_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# struct stat64 *
	jg	sys32_lstat64		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_stime_wrapper)
	llgtr	%r2,%r2			# long *
	jg	compat_sys_stime	# branch to system call

ENTRY(sys32_sysctl_wrapper)
	llgtr	%r2,%r2 		# struct compat_sysctl_args *
	jg	compat_sys_sysctl

ENTRY(sys32_fstat64_wrapper)
=======
	.globl	sys32_stime_wrapper
sys32_stime_wrapper:
	llgtr	%r2,%r2			# long *
	jg	compat_sys_stime	# branch to system call

	.globl	sys32_sysctl_wrapper
sys32_sysctl_wrapper:
	llgtr	%r2,%r2 		# struct compat_sysctl_args *
	jg	compat_sys_sysctl

	.globl	sys32_fstat64_wrapper
sys32_fstat64_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned long
	llgtr	%r3,%r3			# struct stat64 *
	jg	sys32_fstat64		# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_futex_wrapper)
=======
	.globl	compat_sys_futex_wrapper
compat_sys_futex_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# u32 *
	lgfr	%r3,%r3			# int
	lgfr	%r4,%r4			# int
	llgtr	%r5,%r5			# struct compat_timespec *
	llgtr	%r6,%r6			# u32 *
	lgf	%r0,164(%r15)		# int
	stg	%r0,160(%r15)
	jg	compat_sys_futex	# branch to system call

<<<<<<< HEAD
ENTRY(sys32_setxattr_wrapper)
=======
	.globl	sys32_setxattr_wrapper
sys32_setxattr_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# char *
	llgtr	%r4,%r4			# void *
	llgfr	%r5,%r5			# size_t
	lgfr	%r6,%r6			# int
	jg	sys_setxattr

<<<<<<< HEAD
ENTRY(sys32_lsetxattr_wrapper)
=======
	.globl	sys32_lsetxattr_wrapper
sys32_lsetxattr_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# char *
	llgtr	%r4,%r4			# void *
	llgfr	%r5,%r5			# size_t
	lgfr	%r6,%r6			# int
	jg	sys_lsetxattr

<<<<<<< HEAD
ENTRY(sys32_fsetxattr_wrapper)
=======
	.globl	sys32_fsetxattr_wrapper
sys32_fsetxattr_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# char *
	llgtr	%r4,%r4			# void *
	llgfr	%r5,%r5			# size_t
	lgfr	%r6,%r6			# int
	jg	sys_fsetxattr

<<<<<<< HEAD
ENTRY(sys32_getxattr_wrapper)
=======
	.globl	sys32_getxattr_wrapper
sys32_getxattr_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# char *
	llgtr	%r4,%r4			# void *
	llgfr	%r5,%r5			# size_t
	jg	sys_getxattr

<<<<<<< HEAD
ENTRY(sys32_lgetxattr_wrapper)
=======
	.globl	sys32_lgetxattr_wrapper
sys32_lgetxattr_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# char *
	llgtr	%r4,%r4			# void *
	llgfr	%r5,%r5			# size_t
	jg	sys_lgetxattr

<<<<<<< HEAD
ENTRY(sys32_fgetxattr_wrapper)
=======
	.globl	sys32_fgetxattr_wrapper
sys32_fgetxattr_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# char *
	llgtr	%r4,%r4			# void *
	llgfr	%r5,%r5			# size_t
	jg	sys_fgetxattr

<<<<<<< HEAD
ENTRY(sys32_listxattr_wrapper)
=======
	.globl	sys32_listxattr_wrapper
sys32_listxattr_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# char *
	llgfr	%r4,%r4			# size_t
	jg	sys_listxattr

<<<<<<< HEAD
ENTRY(sys32_llistxattr_wrapper)
=======
	.globl	sys32_llistxattr_wrapper
sys32_llistxattr_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# char *
	llgfr	%r4,%r4			# size_t
	jg	sys_llistxattr

<<<<<<< HEAD
ENTRY(sys32_flistxattr_wrapper)
=======
	.globl	sys32_flistxattr_wrapper
sys32_flistxattr_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# char *
	llgfr	%r4,%r4			# size_t
	jg	sys_flistxattr

<<<<<<< HEAD
ENTRY(sys32_removexattr_wrapper)
=======
	.globl	sys32_removexattr_wrapper
sys32_removexattr_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# char *
	jg	sys_removexattr

<<<<<<< HEAD
ENTRY(sys32_lremovexattr_wrapper)
=======
	.globl	sys32_lremovexattr_wrapper
sys32_lremovexattr_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# char *
	jg	sys_lremovexattr

<<<<<<< HEAD
ENTRY(sys32_fremovexattr_wrapper)
=======
	.globl	sys32_fremovexattr_wrapper
sys32_fremovexattr_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# char *
	jg	sys_fremovexattr

<<<<<<< HEAD
ENTRY(sys32_sched_setaffinity_wrapper)
=======
	.globl	sys32_sched_setaffinity_wrapper
sys32_sched_setaffinity_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgfr	%r3,%r3			# unsigned int
	llgtr	%r4,%r4			# unsigned long *
	jg	compat_sys_sched_setaffinity

<<<<<<< HEAD
ENTRY(sys32_sched_getaffinity_wrapper)
=======
	.globl	sys32_sched_getaffinity_wrapper
sys32_sched_getaffinity_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgfr	%r3,%r3			# unsigned int
	llgtr	%r4,%r4			# unsigned long *
	jg	compat_sys_sched_getaffinity

<<<<<<< HEAD
ENTRY(sys32_exit_group_wrapper)
	lgfr	%r2,%r2			# int
	jg	sys_exit_group		# branch to system call

ENTRY(sys32_set_tid_address_wrapper)
	llgtr	%r2,%r2			# int *
	jg	sys_set_tid_address	# branch to system call

ENTRY(sys_epoll_create_wrapper)
	lgfr	%r2,%r2			# int
	jg	sys_epoll_create	# branch to system call

ENTRY(sys_epoll_ctl_wrapper)
=======
	.globl	sys32_exit_group_wrapper
sys32_exit_group_wrapper:
	lgfr	%r2,%r2			# int
	jg	sys_exit_group		# branch to system call

	.globl	sys32_set_tid_address_wrapper
sys32_set_tid_address_wrapper:
	llgtr	%r2,%r2			# int *
	jg	sys_set_tid_address	# branch to system call

	.globl	sys_epoll_create_wrapper
sys_epoll_create_wrapper:
	lgfr	%r2,%r2			# int
	jg	sys_epoll_create	# branch to system call

	.globl	sys_epoll_ctl_wrapper
sys_epoll_ctl_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	lgfr	%r4,%r4			# int
	llgtr	%r5,%r5			# struct epoll_event *
	jg	sys_epoll_ctl		# branch to system call

<<<<<<< HEAD
ENTRY(sys_epoll_wait_wrapper)
=======
	.globl	sys_epoll_wait_wrapper
sys_epoll_wait_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# struct epoll_event *
	lgfr	%r4,%r4			# int
	lgfr	%r5,%r5			# int
	jg	sys_epoll_wait		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_lookup_dcookie_wrapper)
=======
	.globl	sys32_lookup_dcookie_wrapper
sys32_lookup_dcookie_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	sllg	%r2,%r2,32		# get high word of 64bit dcookie
	or	%r2,%r3			# get low word of 64bit dcookie
	llgtr	%r3,%r4			# char *
	llgfr	%r4,%r5			# size_t
	jg	sys_lookup_dcookie

<<<<<<< HEAD
ENTRY(sys32_fadvise64_wrapper)
=======
	.globl	sys32_fadvise64_wrapper
sys32_fadvise64_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	sllg	%r3,%r3,32		# get high word of 64bit loff_t
	or	%r3,%r4			# get low word of 64bit loff_t
	llgfr	%r4,%r5			# size_t (unsigned long)
	lgfr	%r5,%r6			# int
	jg	sys32_fadvise64

<<<<<<< HEAD
ENTRY(sys32_fadvise64_64_wrapper)
	llgtr	%r2,%r2			# struct fadvise64_64_args *
	jg	sys32_fadvise64_64

ENTRY(sys32_clock_settime_wrapper)
=======
	.globl	sys32_fadvise64_64_wrapper
sys32_fadvise64_64_wrapper:
	llgtr	%r2,%r2			# struct fadvise64_64_args *
	jg	sys32_fadvise64_64

	.globl	sys32_clock_settime_wrapper
sys32_clock_settime_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# clockid_t (int)
	llgtr	%r3,%r3			# struct compat_timespec *
	jg	compat_sys_clock_settime

<<<<<<< HEAD
ENTRY(sys32_clock_gettime_wrapper)
=======
	.globl	sys32_clock_gettime_wrapper
sys32_clock_gettime_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# clockid_t (int)
	llgtr	%r3,%r3			# struct compat_timespec *
	jg	compat_sys_clock_gettime

<<<<<<< HEAD
ENTRY(sys32_clock_getres_wrapper)
=======
	.globl	sys32_clock_getres_wrapper
sys32_clock_getres_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# clockid_t (int)
	llgtr	%r3,%r3			# struct compat_timespec *
	jg	compat_sys_clock_getres

<<<<<<< HEAD
ENTRY(sys32_clock_nanosleep_wrapper)
=======
	.globl	sys32_clock_nanosleep_wrapper
sys32_clock_nanosleep_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# clockid_t (int)
	lgfr	%r3,%r3			# int
	llgtr	%r4,%r4			# struct compat_timespec *
	llgtr	%r5,%r5			# struct compat_timespec *
	jg	compat_sys_clock_nanosleep

<<<<<<< HEAD
ENTRY(sys32_timer_create_wrapper)
=======
	.globl	sys32_timer_create_wrapper
sys32_timer_create_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# timer_t (int)
	llgtr	%r3,%r3			# struct compat_sigevent *
	llgtr	%r4,%r4			# timer_t *
	jg	compat_sys_timer_create

<<<<<<< HEAD
ENTRY(sys32_timer_settime_wrapper)
=======
	.globl	sys32_timer_settime_wrapper
sys32_timer_settime_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# timer_t (int)
	lgfr	%r3,%r3			# int
	llgtr	%r4,%r4			# struct compat_itimerspec *
	llgtr	%r5,%r5			# struct compat_itimerspec *
	jg	compat_sys_timer_settime

<<<<<<< HEAD
ENTRY(sys32_timer_gettime_wrapper)
=======
	.globl	sys32_timer_gettime_wrapper
sys32_timer_gettime_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# timer_t (int)
	llgtr	%r3,%r3			# struct compat_itimerspec *
	jg	compat_sys_timer_gettime

<<<<<<< HEAD
ENTRY(sys32_timer_getoverrun_wrapper)
	lgfr	%r2,%r2			# timer_t (int)
	jg	sys_timer_getoverrun

ENTRY(sys32_timer_delete_wrapper)
	lgfr	%r2,%r2			# timer_t (int)
	jg	sys_timer_delete

ENTRY(sys32_io_setup_wrapper)
=======
	.globl	sys32_timer_getoverrun_wrapper
sys32_timer_getoverrun_wrapper:
	lgfr	%r2,%r2			# timer_t (int)
	jg	sys_timer_getoverrun

	.globl	sys32_timer_delete_wrapper
sys32_timer_delete_wrapper:
	lgfr	%r2,%r2			# timer_t (int)
	jg	sys_timer_delete

	.globl	sys32_io_setup_wrapper
sys32_io_setup_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# u32 *
	jg	compat_sys_io_setup

<<<<<<< HEAD
ENTRY(sys32_io_destroy_wrapper)
	llgfr	%r2,%r2			# (aio_context_t) u32
	jg	sys_io_destroy

ENTRY(sys32_io_getevents_wrapper)
=======
	.globl	sys32_io_destroy_wrapper
sys32_io_destroy_wrapper:
	llgfr	%r2,%r2			# (aio_context_t) u32
	jg	sys_io_destroy

	.globl	sys32_io_getevents_wrapper
sys32_io_getevents_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# (aio_context_t) u32
	lgfr	%r3,%r3			# long
	lgfr	%r4,%r4			# long
	llgtr	%r5,%r5			# struct io_event *
	llgtr	%r6,%r6			# struct compat_timespec *
	jg	compat_sys_io_getevents

<<<<<<< HEAD
ENTRY(sys32_io_submit_wrapper)
=======
	.globl	sys32_io_submit_wrapper
sys32_io_submit_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# (aio_context_t) u32
	lgfr	%r3,%r3			# long
	llgtr	%r4,%r4			# struct iocb **
	jg	compat_sys_io_submit

<<<<<<< HEAD
ENTRY(sys32_io_cancel_wrapper)
=======
	.globl	sys32_io_cancel_wrapper
sys32_io_cancel_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# (aio_context_t) u32
	llgtr	%r3,%r3			# struct iocb *
	llgtr	%r4,%r4			# struct io_event *
	jg	sys_io_cancel

<<<<<<< HEAD
ENTRY(compat_sys_statfs64_wrapper)
=======
	.globl compat_sys_statfs64_wrapper
compat_sys_statfs64_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	llgfr	%r3,%r3			# compat_size_t
	llgtr	%r4,%r4			# struct compat_statfs64 *
	jg	compat_sys_statfs64

<<<<<<< HEAD
ENTRY(compat_sys_fstatfs64_wrapper)
=======
	.globl compat_sys_fstatfs64_wrapper
compat_sys_fstatfs64_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int fd
	llgfr	%r3,%r3			# compat_size_t
	llgtr	%r4,%r4			# struct compat_statfs64 *
	jg	compat_sys_fstatfs64

<<<<<<< HEAD
ENTRY(compat_sys_mq_open_wrapper)
=======
	.globl	compat_sys_mq_open_wrapper
compat_sys_mq_open_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	lgfr	%r3,%r3			# int
	llgfr	%r4,%r4			# mode_t
	llgtr	%r5,%r5			# struct compat_mq_attr *
	jg	compat_sys_mq_open

<<<<<<< HEAD
ENTRY(sys32_mq_unlink_wrapper)
	llgtr	%r2,%r2			# const char *
	jg	sys_mq_unlink

ENTRY(compat_sys_mq_timedsend_wrapper)
=======
	.globl	sys32_mq_unlink_wrapper
sys32_mq_unlink_wrapper:
	llgtr	%r2,%r2			# const char *
	jg	sys_mq_unlink

	.globl	compat_sys_mq_timedsend_wrapper
compat_sys_mq_timedsend_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# mqd_t
	llgtr	%r3,%r3			# const char *
	llgfr	%r4,%r4			# size_t
	llgfr	%r5,%r5			# unsigned int
	llgtr	%r6,%r6			# const struct compat_timespec *
	jg	compat_sys_mq_timedsend

<<<<<<< HEAD
ENTRY(compat_sys_mq_timedreceive_wrapper)
=======
	.globl	compat_sys_mq_timedreceive_wrapper
compat_sys_mq_timedreceive_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# mqd_t
	llgtr	%r3,%r3			# char *
	llgfr	%r4,%r4			# size_t
	llgtr	%r5,%r5			# unsigned int *
	llgtr	%r6,%r6			# const struct compat_timespec *
	jg	compat_sys_mq_timedreceive

<<<<<<< HEAD
ENTRY(compat_sys_mq_notify_wrapper)
=======
	.globl	compat_sys_mq_notify_wrapper
compat_sys_mq_notify_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# mqd_t
	llgtr	%r3,%r3			# struct compat_sigevent *
	jg	compat_sys_mq_notify

<<<<<<< HEAD
ENTRY(compat_sys_mq_getsetattr_wrapper)
=======
	.globl	compat_sys_mq_getsetattr_wrapper
compat_sys_mq_getsetattr_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# mqd_t
	llgtr	%r3,%r3			# struct compat_mq_attr *
	llgtr	%r4,%r4			# struct compat_mq_attr *
	jg	compat_sys_mq_getsetattr

<<<<<<< HEAD
ENTRY(compat_sys_add_key_wrapper)
=======
	.globl	compat_sys_add_key_wrapper
compat_sys_add_key_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	llgtr	%r3,%r3			# const char *
	llgtr	%r4,%r4			# const void *
	llgfr	%r5,%r5			# size_t
	llgfr	%r6,%r6			# (key_serial_t) u32
	jg	sys_add_key

<<<<<<< HEAD
ENTRY(compat_sys_request_key_wrapper)
=======
	.globl	compat_sys_request_key_wrapper
compat_sys_request_key_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	llgtr	%r3,%r3			# const char *
	llgtr	%r4,%r4			# const void *
	llgfr	%r5,%r5			# (key_serial_t) u32
	jg	sys_request_key

<<<<<<< HEAD
ENTRY(sys32_remap_file_pages_wrapper)
=======
	.globl	sys32_remap_file_pages_wrapper
sys32_remap_file_pages_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned long
	llgfr	%r3,%r3			# unsigned long
	llgfr	%r4,%r4			# unsigned long
	llgfr	%r5,%r5			# unsigned long
	llgfr	%r6,%r6			# unsigned long
	jg	sys_remap_file_pages

<<<<<<< HEAD
ENTRY(compat_sys_waitid_wrapper)
=======
	.globl	compat_sys_waitid_wrapper
compat_sys_waitid_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# pid_t
	llgtr	%r4,%r4			# siginfo_emu31_t *
	lgfr	%r5,%r5			# int
	llgtr	%r6,%r6			# struct rusage_emu31 *
	jg	compat_sys_waitid

<<<<<<< HEAD
ENTRY(compat_sys_kexec_load_wrapper)
=======
	.globl	compat_sys_kexec_load_wrapper
compat_sys_kexec_load_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned long
	llgfr	%r3,%r3			# unsigned long
	llgtr	%r4,%r4			# struct kexec_segment *
	llgfr	%r5,%r5			# unsigned long
	jg	compat_sys_kexec_load

<<<<<<< HEAD
ENTRY(sys_ioprio_set_wrapper)
=======
	.globl	sys_ioprio_set_wrapper
sys_ioprio_set_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	lgfr	%r4,%r4			# int
	jg	sys_ioprio_set

<<<<<<< HEAD
ENTRY(sys_ioprio_get_wrapper)
=======
	.globl	sys_ioprio_get_wrapper
sys_ioprio_get_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	jg	sys_ioprio_get

<<<<<<< HEAD
ENTRY(sys_inotify_add_watch_wrapper)
=======
	.globl	sys_inotify_add_watch_wrapper
sys_inotify_add_watch_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# const char *
	llgfr	%r4,%r4			# u32
	jg	sys_inotify_add_watch

<<<<<<< HEAD
ENTRY(sys_inotify_rm_watch_wrapper)
=======
	.globl	sys_inotify_rm_watch_wrapper
sys_inotify_rm_watch_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgfr	%r3,%r3			# u32
	jg	sys_inotify_rm_watch

<<<<<<< HEAD
ENTRY(compat_sys_openat_wrapper)
=======
	.globl compat_sys_openat_wrapper
compat_sys_openat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# const char *
	lgfr	%r4,%r4			# int
	lgfr	%r5,%r5			# int
	jg	compat_sys_openat

<<<<<<< HEAD
ENTRY(sys_mkdirat_wrapper)
=======
	.globl sys_mkdirat_wrapper
sys_mkdirat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# const char *
	lgfr	%r4,%r4			# int
	jg	sys_mkdirat

<<<<<<< HEAD
ENTRY(sys_mknodat_wrapper)
=======
	.globl sys_mknodat_wrapper
sys_mknodat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# const char *
	lgfr	%r4,%r4			# int
	llgfr	%r5,%r5			# unsigned int
	jg	sys_mknodat

<<<<<<< HEAD
ENTRY(sys_fchownat_wrapper)
=======
	.globl sys_fchownat_wrapper
sys_fchownat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# const char *
	llgfr	%r4,%r4			# uid_t
	llgfr	%r5,%r5			# gid_t
	lgfr	%r6,%r6			# int
	jg	sys_fchownat

<<<<<<< HEAD
ENTRY(compat_sys_futimesat_wrapper)
=======
	.globl compat_sys_futimesat_wrapper
compat_sys_futimesat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# char *
	llgtr	%r4,%r4			# struct timeval *
	jg	compat_sys_futimesat

<<<<<<< HEAD
ENTRY(sys32_fstatat64_wrapper)
=======
	.globl sys32_fstatat64_wrapper
sys32_fstatat64_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# char *
	llgtr	%r4,%r4			# struct stat64 *
	lgfr	%r5,%r5			# int
	jg	sys32_fstatat64

<<<<<<< HEAD
ENTRY(sys_unlinkat_wrapper)
=======
	.globl sys_unlinkat_wrapper
sys_unlinkat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# const char *
	lgfr	%r4,%r4			# int
	jg	sys_unlinkat

<<<<<<< HEAD
ENTRY(sys_renameat_wrapper)
=======
	.globl sys_renameat_wrapper
sys_renameat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# const char *
	lgfr	%r4,%r4			# int
	llgtr	%r5,%r5			# const char *
	jg	sys_renameat

<<<<<<< HEAD
ENTRY(sys_linkat_wrapper)
=======
	.globl sys_linkat_wrapper
sys_linkat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# const char *
	lgfr	%r4,%r4			# int
	llgtr	%r5,%r5			# const char *
	lgfr	%r6,%r6			# int
	jg	sys_linkat

<<<<<<< HEAD
ENTRY(sys_symlinkat_wrapper)
=======
	.globl sys_symlinkat_wrapper
sys_symlinkat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const char *
	lgfr	%r3,%r3			# int
	llgtr	%r4,%r4			# const char *
	jg	sys_symlinkat

<<<<<<< HEAD
ENTRY(sys_readlinkat_wrapper)
=======
	.globl sys_readlinkat_wrapper
sys_readlinkat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# const char *
	llgtr	%r4,%r4			# char *
	lgfr	%r5,%r5			# int
	jg	sys_readlinkat

<<<<<<< HEAD
ENTRY(sys_fchmodat_wrapper)
=======
	.globl sys_fchmodat_wrapper
sys_fchmodat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# const char *
	llgfr	%r4,%r4			# mode_t
	jg	sys_fchmodat

<<<<<<< HEAD
ENTRY(sys_faccessat_wrapper)
=======
	.globl sys_faccessat_wrapper
sys_faccessat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# const char *
	lgfr	%r4,%r4			# int
	jg	sys_faccessat

<<<<<<< HEAD
ENTRY(compat_sys_pselect6_wrapper)
=======
	.globl compat_sys_pselect6_wrapper
compat_sys_pselect6_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# fd_set *
	llgtr	%r4,%r4			# fd_set *
	llgtr	%r5,%r5			# fd_set *
	llgtr	%r6,%r6			# struct timespec *
	llgt	%r0,164(%r15)		# void *
	stg	%r0,160(%r15)
	jg	compat_sys_pselect6

<<<<<<< HEAD
ENTRY(compat_sys_ppoll_wrapper)
=======
	.globl compat_sys_ppoll_wrapper
compat_sys_ppoll_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# struct pollfd *
	llgfr	%r3,%r3			# unsigned int
	llgtr	%r4,%r4			# struct timespec *
	llgtr	%r5,%r5			# const sigset_t *
	llgfr	%r6,%r6			# size_t
	jg	compat_sys_ppoll

<<<<<<< HEAD
ENTRY(sys_unshare_wrapper)
	llgfr	%r2,%r2			# unsigned long
	jg	sys_unshare

ENTRY(compat_sys_set_robust_list_wrapper)
=======
	.globl sys_unshare_wrapper
sys_unshare_wrapper:
	llgfr	%r2,%r2			# unsigned long
	jg	sys_unshare

	.globl compat_sys_set_robust_list_wrapper
compat_sys_set_robust_list_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# struct compat_robust_list_head *
	llgfr	%r3,%r3			# size_t
	jg	compat_sys_set_robust_list

<<<<<<< HEAD
ENTRY(compat_sys_get_robust_list_wrapper)
=======
	.globl compat_sys_get_robust_list_wrapper
compat_sys_get_robust_list_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# compat_uptr_t_t *
	llgtr	%r4,%r4			# compat_size_t *
	jg	compat_sys_get_robust_list

<<<<<<< HEAD
ENTRY(sys_splice_wrapper)
=======
	.globl sys_splice_wrapper
sys_splice_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# loff_t *
	lgfr	%r4,%r4			# int
	llgtr	%r5,%r5			# loff_t *
	llgfr	%r6,%r6			# size_t
	llgf	%r0,164(%r15)		# unsigned int
	stg	%r0,160(%r15)
	jg	sys_splice

<<<<<<< HEAD
ENTRY(sys_sync_file_range_wrapper)
=======
	.globl	sys_sync_file_range_wrapper
sys_sync_file_range_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	sllg	%r3,%r3,32		# get high word of 64bit loff_t
	or	%r3,%r4			# get low word of 64bit loff_t
	sllg	%r4,%r5,32		# get high word of 64bit loff_t
	or	%r4,%r6			# get low word of 64bit loff_t
	llgf	%r5,164(%r15)		# unsigned int
	jg	sys_sync_file_range

<<<<<<< HEAD
ENTRY(sys_tee_wrapper)
=======
	.globl	sys_tee_wrapper
sys_tee_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	llgfr	%r4,%r4			# size_t
	llgfr	%r5,%r5			# unsigned int
	jg	sys_tee

<<<<<<< HEAD
ENTRY(compat_sys_vmsplice_wrapper)
=======
	.globl compat_sys_vmsplice_wrapper
compat_sys_vmsplice_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# compat_iovec *
	llgfr	%r4,%r4			# unsigned int
	llgfr	%r5,%r5			# unsigned int
	jg	compat_sys_vmsplice

<<<<<<< HEAD
ENTRY(sys_getcpu_wrapper)
=======
	.globl	sys_getcpu_wrapper
sys_getcpu_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# unsigned *
	llgtr	%r3,%r3			# unsigned *
	llgtr	%r4,%r4			# struct getcpu_cache *
	jg	sys_getcpu

<<<<<<< HEAD
ENTRY(compat_sys_epoll_pwait_wrapper)
=======
	.globl	compat_sys_epoll_pwait_wrapper
compat_sys_epoll_pwait_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# struct compat_epoll_event *
	lgfr	%r4,%r4			# int
	lgfr	%r5,%r5			# int
	llgtr	%r6,%r6			# compat_sigset_t *
	llgf	%r0,164(%r15)		# compat_size_t
	stg	%r0,160(%r15)
	jg	compat_sys_epoll_pwait

<<<<<<< HEAD
ENTRY(compat_sys_utimes_wrapper)
=======
	.globl	compat_sys_utimes_wrapper
compat_sys_utimes_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# struct compat_timeval *
	jg	compat_sys_utimes

<<<<<<< HEAD
ENTRY(compat_sys_utimensat_wrapper)
=======
	.globl	compat_sys_utimensat_wrapper
compat_sys_utimensat_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgtr	%r3,%r3			# char *
	llgtr	%r4,%r4			# struct compat_timespec *
	lgfr	%r5,%r5			# int
	jg	compat_sys_utimensat

<<<<<<< HEAD
ENTRY(compat_sys_signalfd_wrapper)
=======
	.globl	compat_sys_signalfd_wrapper
compat_sys_signalfd_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# compat_sigset_t *
	llgfr	%r4,%r4			# compat_size_t
	jg	compat_sys_signalfd

<<<<<<< HEAD
ENTRY(sys_eventfd_wrapper)
	llgfr	%r2,%r2			# unsigned int
	jg	sys_eventfd

ENTRY(sys_fallocate_wrapper)
=======
	.globl	sys_eventfd_wrapper
sys_eventfd_wrapper:
	llgfr	%r2,%r2			# unsigned int
	jg	sys_eventfd

	.globl	sys_fallocate_wrapper
sys_fallocate_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	sllg	%r4,%r4,32		# get high word of 64bit loff_t
	lr	%r4,%r5			# get low word of 64bit loff_t
	sllg	%r5,%r6,32		# get high word of 64bit loff_t
	l	%r5,164(%r15)		# get low word of 64bit loff_t
	jg	sys_fallocate

<<<<<<< HEAD
ENTRY(sys_timerfd_create_wrapper)
=======
	.globl	sys_timerfd_create_wrapper
sys_timerfd_create_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	jg	sys_timerfd_create

<<<<<<< HEAD
ENTRY(compat_sys_timerfd_settime_wrapper)
=======
	.globl	compat_sys_timerfd_settime_wrapper
compat_sys_timerfd_settime_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	llgtr	%r4,%r4			# struct compat_itimerspec *
	llgtr	%r5,%r5			# struct compat_itimerspec *
	jg	compat_sys_timerfd_settime

<<<<<<< HEAD
ENTRY(compat_sys_timerfd_gettime_wrapper)
=======
	.globl	compat_sys_timerfd_gettime_wrapper
compat_sys_timerfd_gettime_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# struct compat_itimerspec *
	jg	compat_sys_timerfd_gettime

<<<<<<< HEAD
ENTRY(compat_sys_signalfd4_wrapper)
=======
	.globl compat_sys_signalfd4_wrapper
compat_sys_signalfd4_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# compat_sigset_t *
	llgfr	%r4,%r4			# compat_size_t
	lgfr	%r5,%r5			# int
	jg	compat_sys_signalfd4

<<<<<<< HEAD
ENTRY(sys_eventfd2_wrapper)
=======
	.globl sys_eventfd2_wrapper
sys_eventfd2_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	lgfr	%r3,%r3			# int
	jg	sys_eventfd2

<<<<<<< HEAD
ENTRY(sys_inotify_init1_wrapper)
	lgfr	%r2,%r2			# int
	jg	sys_inotify_init1

ENTRY(sys_pipe2_wrapper)
=======
	.globl	sys_inotify_init1_wrapper
sys_inotify_init1_wrapper:
	lgfr	%r2,%r2			# int
	jg	sys_inotify_init1

	.globl	sys_pipe2_wrapper
sys_pipe2_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# u32 *
	lgfr	%r3,%r3			# int
	jg	sys_pipe2		# branch to system call

<<<<<<< HEAD
ENTRY(sys_dup3_wrapper)
=======
	.globl	sys_dup3_wrapper
sys_dup3_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgfr	%r3,%r3			# unsigned int
	lgfr	%r4,%r4			# int
	jg	sys_dup3		# branch to system call

<<<<<<< HEAD
ENTRY(sys_epoll_create1_wrapper)
	lgfr	%r2,%r2			# int
	jg	sys_epoll_create1	# branch to system call

ENTRY(sys32_readahead_wrapper)
=======
	.globl	sys_epoll_create1_wrapper
sys_epoll_create1_wrapper:
	lgfr	%r2,%r2			# int
	jg	sys_epoll_create1	# branch to system call

	.globl	sys32_readahead_wrapper
sys32_readahead_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgfr	%r3,%r3			# u32
	llgfr	%r4,%r4			# u32
	lgfr	%r5,%r5			# s32
	jg	sys32_readahead		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_sendfile64_wrapper)
=======
	.globl	sys32_sendfile64_wrapper
sys32_sendfile64_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	llgtr	%r4,%r4			# compat_loff_t *
	lgfr	%r5,%r5			# s32
	jg	sys32_sendfile64	# branch to system call

<<<<<<< HEAD
ENTRY(sys_tkill_wrapper)
=======
	.globl	sys_tkill_wrapper
sys_tkill_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# pid_t
	lgfr	%r3,%r3			# int
	jg	sys_tkill		# branch to system call

<<<<<<< HEAD
ENTRY(sys_tgkill_wrapper)
=======
	.globl	sys_tgkill_wrapper
sys_tgkill_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# pid_t
	lgfr	%r3,%r3			# pid_t
	lgfr	%r4,%r4			# int
	jg	sys_tgkill		# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_keyctl_wrapper)
=======
	.globl	compat_sys_keyctl_wrapper
compat_sys_keyctl_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# u32
	llgfr	%r3,%r3			# u32
	llgfr	%r4,%r4			# u32
	llgfr	%r5,%r5			# u32
	llgfr	%r6,%r6			# u32
	jg	compat_sys_keyctl	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_preadv_wrapper)
=======
	.globl	compat_sys_preadv_wrapper
compat_sys_preadv_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned long
	llgtr	%r3,%r3			# compat_iovec *
	llgfr	%r4,%r4			# unsigned long
	llgfr	%r5,%r5			# u32
	llgfr	%r6,%r6			# u32
	jg	compat_sys_preadv	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_pwritev_wrapper)
=======
	.globl	compat_sys_pwritev_wrapper
compat_sys_pwritev_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned long
	llgtr	%r3,%r3			# compat_iovec *
	llgfr	%r4,%r4			# unsigned long
	llgfr	%r5,%r5			# u32
	llgfr	%r6,%r6			# u32
	jg	compat_sys_pwritev	# branch to system call

<<<<<<< HEAD
ENTRY(compat_sys_rt_tgsigqueueinfo_wrapper)
=======
	.globl	compat_sys_rt_tgsigqueueinfo_wrapper
compat_sys_rt_tgsigqueueinfo_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# compat_pid_t
	lgfr	%r3,%r3			# compat_pid_t
	lgfr	%r4,%r4			# int
	llgtr	%r5,%r5			# struct compat_siginfo *
	jg	compat_sys_rt_tgsigqueueinfo_wrapper # branch to system call

<<<<<<< HEAD
ENTRY(sys_perf_event_open_wrapper)
=======
	.globl	sys_perf_event_open_wrapper
sys_perf_event_open_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# const struct perf_event_attr *
	lgfr	%r3,%r3			# pid_t
	lgfr	%r4,%r4			# int
	lgfr	%r5,%r5			# int
	llgfr	%r6,%r6			# unsigned long
	jg	sys_perf_event_open	# branch to system call

<<<<<<< HEAD
ENTRY(sys_clone_wrapper)
=======
	.globl	sys_clone_wrapper
sys_clone_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned long
	llgfr	%r3,%r3			# unsigned long
	llgtr	%r4,%r4			# int *
	llgtr	%r5,%r5			# int *
	jg	sys_clone		# branch to system call

<<<<<<< HEAD
ENTRY(sys32_execve_wrapper)
=======
	.globl	sys32_execve_wrapper
sys32_execve_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgtr	%r2,%r2			# char *
	llgtr	%r3,%r3			# compat_uptr_t *
	llgtr	%r4,%r4			# compat_uptr_t *
	jg	sys32_execve		# branch to system call

<<<<<<< HEAD
ENTRY(sys_fanotify_init_wrapper)
=======
	.globl	sys_fanotify_init_wrapper
sys_fanotify_init_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	llgfr	%r2,%r2			# unsigned int
	llgfr	%r3,%r3			# unsigned int
	jg	sys_fanotify_init	# branch to system call

<<<<<<< HEAD
ENTRY(sys_fanotify_mark_wrapper)
=======
	.globl	sys_fanotify_mark_wrapper
sys_fanotify_mark_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgfr	%r3,%r3			# unsigned int
	sllg	%r4,%r4,32		# get high word of 64bit mask
	lr	%r4,%r5			# get low word of 64bit mask
	llgfr	%r5,%r6			# unsigned int
	llgt	%r6,164(%r15)		# char *
	jg	sys_fanotify_mark	# branch to system call

<<<<<<< HEAD
ENTRY(sys_prlimit64_wrapper)
=======
	.globl	sys_prlimit64_wrapper
sys_prlimit64_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# pid_t
	llgfr	%r3,%r3			# unsigned int
	llgtr	%r4,%r4			# const struct rlimit64 __user *
	llgtr	%r5,%r5			# struct rlimit64 __user *
	jg	sys_prlimit64		# branch to system call

<<<<<<< HEAD
ENTRY(sys_name_to_handle_at_wrapper)
=======
	.globl	sys_name_to_handle_at_wrapper
sys_name_to_handle_at_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# const char __user *
	llgtr	%r4,%r4			# struct file_handle __user *
	llgtr	%r5,%r5			# int __user *
	lgfr	%r6,%r6			# int
	jg	sys_name_to_handle_at

<<<<<<< HEAD
ENTRY(compat_sys_open_by_handle_at_wrapper)
=======
	.globl	compat_sys_open_by_handle_at_wrapper
compat_sys_open_by_handle_at_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# int
	llgtr	%r3,%r3			# struct file_handle __user *
	lgfr	%r4,%r4			# int
	jg	compat_sys_open_by_handle_at

<<<<<<< HEAD
ENTRY(compat_sys_clock_adjtime_wrapper)
=======
	.globl	compat_sys_clock_adjtime_wrapper
compat_sys_clock_adjtime_wrapper:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	lgfr	%r2,%r2			# clockid_t (int)
	llgtr	%r3,%r3			# struct compat_timex __user *
	jg	compat_sys_clock_adjtime

<<<<<<< HEAD
ENTRY(sys_syncfs_wrapper)
	lgfr	%r2,%r2			# int
	jg	sys_syncfs

ENTRY(sys_setns_wrapper)
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	jg	sys_setns

ENTRY(compat_sys_process_vm_readv_wrapper)
	lgfr	%r2,%r2			# compat_pid_t
	llgtr	%r3,%r3			# struct compat_iovec __user *
	llgfr	%r4,%r4			# unsigned long
	llgtr	%r5,%r5			# struct compat_iovec __user *
	llgfr	%r6,%r6			# unsigned long
	llgf	%r0,164(%r15)		# unsigned long
	stg	%r0,160(%r15)
	jg	compat_sys_process_vm_readv

ENTRY(compat_sys_process_vm_writev_wrapper)
	lgfr	%r2,%r2			# compat_pid_t
	llgtr	%r3,%r3			# struct compat_iovec __user *
	llgfr	%r4,%r4			# unsigned long
	llgtr	%r5,%r5			# struct compat_iovec __user *
	llgfr	%r6,%r6			# unsigned long
	llgf	%r0,164(%r15)		# unsigned long
	stg	%r0,160(%r15)
	jg	compat_sys_process_vm_writev
=======
	.globl	sys_syncfs_wrapper
sys_syncfs_wrapper:
	lgfr	%r2,%r2			# int
	jg	sys_syncfs

	.globl	sys_setns_wrapper
sys_setns_wrapper:
	lgfr	%r2,%r2			# int
	lgfr	%r3,%r3			# int
	jg	sys_setns
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
