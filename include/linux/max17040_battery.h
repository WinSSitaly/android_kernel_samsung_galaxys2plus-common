/*
 *  Copyright (C) 2009 Samsung Electronics
 *  Minkyu Kang <mk7.kang@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __MAX17040_BATTERY_H_
#define __MAX17040_BATTERY_H_

<<<<<<< HEAD
=======
#define HW_MAX17040_SLAVE_ADDR    0x36
#define HW_MAX17040_DRIVER_NAME   "max17040"

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
struct max17040_platform_data {
	int (*battery_online)(void);
	int (*charger_online)(void);
	int (*charger_enable)(void);
<<<<<<< HEAD
=======

#if defined(CONFIG_BCM_CMP_BATTERY_MULTI) || defined(CONFIG_BCM_CMP_BATTERY_MULTI_MODULE)
	int gpio_ac_power;
	int ac_power_on_level;
	int gpio_charger;
	int battery_max_voltage;
#endif
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
};

#endif
