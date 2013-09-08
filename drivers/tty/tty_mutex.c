#include <linux/tty.h>
#include <linux/module.h>
#include <linux/kallsyms.h>
#include <linux/semaphore.h>
#include <linux/sched.h>

/*
 * The 'big tty mutex'
 *
 * This mutex is taken and released by tty_lock() and tty_unlock(),
 * replacing the older big kernel lock.
 * It can no longer be taken recursively, and does not get
 * released implicitly while sleeping.
 *
 * Don't use in new code.
 */
static DEFINE_MUTEX(big_tty_mutex);
<<<<<<< HEAD
=======
struct task_struct *__big_tty_mutex_owner;
EXPORT_SYMBOL_GPL(__big_tty_mutex_owner);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

/*
 * Getting the big tty mutex.
 */
void __lockfunc tty_lock(void)
{
<<<<<<< HEAD
	mutex_lock(&big_tty_mutex);
=======
	struct task_struct *task = current;

	WARN_ON(__big_tty_mutex_owner == task);

	mutex_lock(&big_tty_mutex);
	__big_tty_mutex_owner = task;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}
EXPORT_SYMBOL(tty_lock);

void __lockfunc tty_unlock(void)
{
<<<<<<< HEAD
=======
	struct task_struct *task = current;

	WARN_ON(__big_tty_mutex_owner != task);
	__big_tty_mutex_owner = NULL;

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	mutex_unlock(&big_tty_mutex);
}
EXPORT_SYMBOL(tty_unlock);
