/*
 * Provide a default dump_stack() function for architectures
 * which don't implement their own.
 */

#include <linux/kernel.h>
<<<<<<< HEAD
#include <linux/export.h>
=======
#include <linux/module.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

void dump_stack(void)
{
	printk(KERN_NOTICE
		"This architecture does not implement dump_stack()\n");
}

EXPORT_SYMBOL(dump_stack);
