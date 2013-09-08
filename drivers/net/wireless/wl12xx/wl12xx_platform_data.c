<<<<<<< HEAD
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 2010-2011 Texas Instruments, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <linux/module.h>
#include <linux/err.h>
#include <linux/wl12xx.h>

<<<<<<< HEAD
static struct wl12xx_platform_data *platform_data;
=======
static const struct wl12xx_platform_data *platform_data;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

int __init wl12xx_set_platform_data(const struct wl12xx_platform_data *data)
{
	if (platform_data)
		return -EBUSY;
	if (!data)
		return -EINVAL;

	platform_data = kmemdup(data, sizeof(*data), GFP_KERNEL);
	if (!platform_data)
		return -ENOMEM;

	return 0;
}

<<<<<<< HEAD
struct wl12xx_platform_data *wl12xx_get_platform_data(void)
=======
const struct wl12xx_platform_data *wl12xx_get_platform_data(void)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	if (!platform_data)
		return ERR_PTR(-ENODEV);

	return platform_data;
}
EXPORT_SYMBOL(wl12xx_get_platform_data);
