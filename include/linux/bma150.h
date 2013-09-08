<<<<<<< HEAD
/*
 * Copyright (c) 2011 Bosch Sensortec GmbH
 * Copyright (c) 2011 Unixphere
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
=======
/*****************************************************************************
* Copyright 2010 Broadcom Corporation.  All rights reserved.
*
* Unless you and Broadcom execute a separate written software license
* agreement governing use of this software, this software is licensed to you
* under the terms of the GNU General Public License version 2, available at
* http://www.broadcom.com/licenses/GPLv2.php (the "GPL"). 
*
* Notwithstanding the above, under no circumstances may you combine this
* software in any way with any other Broadcom software provided under a
* license other than the GPL, without Broadcom's express prior written
* consent.
*****************************************************************************/
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#ifndef _BMA150_H_
#define _BMA150_H_

<<<<<<< HEAD
#define BMA150_DRIVER		"bma150"

struct bma150_cfg {
	bool any_motion_int;		/* Set to enable any-motion interrupt */
	bool hg_int;			/* Set to enable high-G interrupt */
	bool lg_int;			/* Set to enable low-G interrupt */
	unsigned char any_motion_dur;	/* Any-motion duration */
	unsigned char any_motion_thres;	/* Any-motion threshold */
	unsigned char hg_hyst;		/* High-G hysterisis */
	unsigned char hg_dur;		/* High-G duration */
	unsigned char hg_thres;		/* High-G threshold */
	unsigned char lg_hyst;		/* Low-G hysterisis */
	unsigned char lg_dur;		/* Low-G duration */
	unsigned char lg_thres;		/* Low-G threshold */
	unsigned char range;		/* BMA0150_RANGE_xxx (in G) */
	unsigned char bandwidth;	/* BMA0150_BW_xxx (in Hz) */
};

struct bma150_platform_data {
	struct bma150_cfg cfg;
	int (*irq_gpio_cfg)(void);
};

#endif /* _BMA150_H_ */
=======
/* 
 * The output of the sensor may have to be modified depending on how it is
 * mounted on the PCB.
 * In the following order:
 * y_dir_rev, x_dir_rev, z_dir_rev
 * would mean x -> -y, y-> -x, z-> -z
 */
typedef enum
{
   x_dir,
   y_dir,
   z_dir,
   x_dir_rev,
   y_dir_rev,
   z_dir_rev
} bma150_axis_change_enum;

struct t_bma150_axis_change
{
   int x_change;
   int y_change;
   int z_change;
}; 
  
   
/* The two I2C slave device addresses the driver supports. */
#define BMA150_DRIVER_SLAVE_NUMBER_0x38    0x38
#define BMA150_DRIVER_NAME                 "bma150"

#endif    /* _BMA150_H_ */

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
