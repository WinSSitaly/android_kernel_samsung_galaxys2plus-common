/*
 * Uniprocessor-only support functions.  The counterpart to kernel/smp.c
 */

#include <linux/interrupt.h>
#include <linux/kernel.h>
<<<<<<< HEAD
#include <linux/export.h>
=======
#include <linux/module.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <linux/smp.h>

int smp_call_function_single(int cpu, void (*func) (void *info), void *info,
				int wait)
{
	WARN_ON(cpu != 0);

	local_irq_disable();
	(func)(info);
	local_irq_enable();

	return 0;
}
EXPORT_SYMBOL(smp_call_function_single);
