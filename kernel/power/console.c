/*
<<<<<<< HEAD
 * Functions for saving/restoring console.
=======
 * drivers/power/process.c - Functions for saving/restoring console.
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
 *
 * Originally from swsusp.
 */

#include <linux/vt_kern.h>
#include <linux/kbd_kern.h>
#include <linux/vt.h>
#include <linux/module.h>
#include "power.h"

<<<<<<< HEAD
=======
#if defined(CONFIG_VT) && defined(CONFIG_VT_CONSOLE)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#define SUSPEND_CONSOLE	(MAX_NR_CONSOLES-1)

static int orig_fgconsole, orig_kmsg;

int pm_prepare_console(void)
{
	orig_fgconsole = vt_move_to_console(SUSPEND_CONSOLE, 1);
	if (orig_fgconsole < 0)
		return 1;

	orig_kmsg = vt_kmsg_redirect(SUSPEND_CONSOLE);
	return 0;
}

void pm_restore_console(void)
{
	if (orig_fgconsole >= 0) {
		vt_move_to_console(orig_fgconsole, 0);
		vt_kmsg_redirect(orig_kmsg);
	}
}
<<<<<<< HEAD
=======
#endif
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
