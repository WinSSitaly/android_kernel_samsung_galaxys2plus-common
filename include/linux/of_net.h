/*
 * OF helpers for network devices.
 *
 * This file is released under the GPLv2
 */

#ifndef __LINUX_OF_NET_H
#define __LINUX_OF_NET_H

#ifdef CONFIG_OF_NET
#include <linux/of.h>
<<<<<<< HEAD
extern const int of_get_phy_mode(struct device_node *np);
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
extern const void *of_get_mac_address(struct device_node *np);
#endif

#endif /* __LINUX_OF_NET_H */
