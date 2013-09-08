/*
 *	Variables and functions used by the code in sleep.c
 */

#include <asm/trampoline.h>
<<<<<<< HEAD
#include <linux/linkage.h>
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

extern unsigned long saved_video_mode;
extern long saved_magic;

extern int wakeup_pmode_return;

<<<<<<< HEAD
extern u8 wake_sleep_flags;
extern asmlinkage void acpi_enter_s3(void);

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
extern unsigned long acpi_copy_wakeup_routine(unsigned long);
extern void wakeup_long64(void);

extern void do_suspend_lowlevel(void);
