/*
 * common EDAC components that must be in kernel
 *
 * Author: Dave Jiang <djiang@mvista.com>
 *
 * 2007 (c) MontaVista Software, Inc.
 * 2010 (c) Advanced Micro Devices Inc.
 *	    Borislav Petkov <borislav.petkov@amd.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 */
#include <linux/module.h>
#include <linux/edac.h>
<<<<<<< HEAD
#include <linux/atomic.h>
#include <linux/device.h>
=======
#include <asm/atomic.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <asm/edac.h>

int edac_op_state = EDAC_OPSTATE_INVAL;
EXPORT_SYMBOL_GPL(edac_op_state);

atomic_t edac_handlers = ATOMIC_INIT(0);
EXPORT_SYMBOL_GPL(edac_handlers);

int edac_err_assert = 0;
EXPORT_SYMBOL_GPL(edac_err_assert);

<<<<<<< HEAD
static atomic_t edac_subsys_valid = ATOMIC_INIT(0);
=======
static atomic_t edac_class_valid = ATOMIC_INIT(0);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

/*
 * called to determine if there is an EDAC driver interested in
 * knowing an event (such as NMI) occurred
 */
int edac_handler_set(void)
{
	if (edac_op_state == EDAC_OPSTATE_POLL)
		return 0;

	return atomic_read(&edac_handlers);
}
EXPORT_SYMBOL_GPL(edac_handler_set);

/*
 * handler for NMI type of interrupts to assert error
 */
void edac_atomic_assert_error(void)
{
	edac_err_assert++;
}
EXPORT_SYMBOL_GPL(edac_atomic_assert_error);

/*
 * sysfs object: /sys/devices/system/edac
 *	need to export to other files
 */
<<<<<<< HEAD
struct bus_type edac_subsys = {
	.name = "edac",
	.dev_name = "edac",
};
EXPORT_SYMBOL_GPL(edac_subsys);

/* return pointer to the 'edac' node in sysfs */
struct bus_type *edac_get_sysfs_subsys(void)
{
	int err = 0;

	if (atomic_read(&edac_subsys_valid))
		goto out;

	/* create the /sys/devices/system/edac directory */
	err = subsys_system_register(&edac_subsys, NULL);
=======
struct sysdev_class edac_class = {
	.name = "edac",
};
EXPORT_SYMBOL_GPL(edac_class);

/* return pointer to the 'edac' node in sysfs */
struct sysdev_class *edac_get_sysfs_class(void)
{
	int err = 0;

	if (atomic_read(&edac_class_valid))
		goto out;

	/* create the /sys/devices/system/edac directory */
	err = sysdev_class_register(&edac_class);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (err) {
		printk(KERN_ERR "Error registering toplevel EDAC sysfs dir\n");
		return NULL;
	}

out:
<<<<<<< HEAD
	atomic_inc(&edac_subsys_valid);
	return &edac_subsys;
}
EXPORT_SYMBOL_GPL(edac_get_sysfs_subsys);

void edac_put_sysfs_subsys(void)
{
	/* last user unregisters it */
	if (atomic_dec_and_test(&edac_subsys_valid))
		bus_unregister(&edac_subsys);
}
EXPORT_SYMBOL_GPL(edac_put_sysfs_subsys);
=======
	atomic_inc(&edac_class_valid);
	return &edac_class;
}
EXPORT_SYMBOL_GPL(edac_get_sysfs_class);

void edac_put_sysfs_class(void)
{
	/* last user unregisters it */
	if (atomic_dec_and_test(&edac_class_valid))
		sysdev_class_unregister(&edac_class);
}
EXPORT_SYMBOL_GPL(edac_put_sysfs_class);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
