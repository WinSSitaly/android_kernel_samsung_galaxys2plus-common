/*
 * OMAP3/OMAP4 Voltage Management Routines
 *
 * Author: Thara Gopinath	<thara@ti.com>
 *
 * Copyright (C) 2007 Texas Instruments, Inc.
 * Rajendra Nayak <rnayak@ti.com>
 * Lesly A M <x0080970@ti.com>
 *
 * Copyright (C) 2008 Nokia Corporation
 * Kalle Jokiniemi
 *
 * Copyright (C) 2010 Texas Instruments, Inc.
 * Thara Gopinath <thara@ti.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/init.h>

<<<<<<< HEAD
#include "common.h"
=======
#include <plat/common.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#include "prm-regbits-44xx.h"
#include "prm44xx.h"
#include "prcm44xx.h"
#include "prminst44xx.h"
#include "voltage.h"
#include "omap_opp_data.h"
#include "vc.h"
#include "vp.h"

<<<<<<< HEAD
static const struct omap_vfsm_instance omap4_vdd_mpu_vfsm = {
	.voltsetup_reg = OMAP4_PRM_VOLTSETUP_MPU_RET_SLEEP_OFFSET,
};

static const struct omap_vfsm_instance omap4_vdd_iva_vfsm = {
	.voltsetup_reg = OMAP4_PRM_VOLTSETUP_IVA_RET_SLEEP_OFFSET,
};

static const struct omap_vfsm_instance omap4_vdd_core_vfsm = {
	.voltsetup_reg = OMAP4_PRM_VOLTSETUP_CORE_RET_SLEEP_OFFSET,
};

static struct voltagedomain omap4_voltdm_mpu = {
	.name = "mpu",
	.scalable = true,
	.read = omap4_prm_vcvp_read,
	.write = omap4_prm_vcvp_write,
	.rmw = omap4_prm_vcvp_rmw,
	.vc = &omap4_vc_mpu,
	.vfsm = &omap4_vdd_mpu_vfsm,
	.vp = &omap4_vp_mpu,
};

static struct voltagedomain omap4_voltdm_iva = {
	.name = "iva",
	.scalable = true,
	.read = omap4_prm_vcvp_read,
	.write = omap4_prm_vcvp_write,
	.rmw = omap4_prm_vcvp_rmw,
	.vc = &omap4_vc_iva,
	.vfsm = &omap4_vdd_iva_vfsm,
	.vp = &omap4_vp_iva,
};

static struct voltagedomain omap4_voltdm_core = {
	.name = "core",
	.scalable = true,
	.read = omap4_prm_vcvp_read,
	.write = omap4_prm_vcvp_write,
	.rmw = omap4_prm_vcvp_rmw,
	.vc = &omap4_vc_core,
	.vfsm = &omap4_vdd_core_vfsm,
	.vp = &omap4_vp_core,
};

static struct voltagedomain omap4_voltdm_wkup = {
	.name = "wakeup",
};

static struct voltagedomain *voltagedomains_omap4[] __initdata = {
	&omap4_voltdm_mpu,
	&omap4_voltdm_iva,
	&omap4_voltdm_core,
	&omap4_voltdm_wkup,
	NULL,
};

static const char *sys_clk_name __initdata = "sys_clkin_ck";

void __init omap44xx_voltagedomains_init(void)
{
	struct voltagedomain *voltdm;
	int i;
=======
static const struct omap_vfsm_instance_data omap4_vdd_mpu_vfsm_data = {
	.voltsetup_reg = OMAP4_PRM_VOLTSETUP_MPU_RET_SLEEP_OFFSET,
};

static struct omap_vdd_info omap4_vdd_mpu_info = {
	.vp_data = &omap4_vp_mpu_data,
	.vc_data = &omap4_vc_mpu_data,
	.vfsm = &omap4_vdd_mpu_vfsm_data,
	.voltdm = {
		.name = "mpu",
	},
};

static const struct omap_vfsm_instance_data omap4_vdd_iva_vfsm_data = {
	.voltsetup_reg = OMAP4_PRM_VOLTSETUP_IVA_RET_SLEEP_OFFSET,
};

static struct omap_vdd_info omap4_vdd_iva_info = {
	.vp_data = &omap4_vp_iva_data,
	.vc_data = &omap4_vc_iva_data,
	.vfsm = &omap4_vdd_iva_vfsm_data,
	.voltdm = {
		.name = "iva",
	},
};

static const struct omap_vfsm_instance_data omap4_vdd_core_vfsm_data = {
	.voltsetup_reg = OMAP4_PRM_VOLTSETUP_CORE_RET_SLEEP_OFFSET,
};

static struct omap_vdd_info omap4_vdd_core_info = {
	.vp_data = &omap4_vp_core_data,
	.vc_data = &omap4_vc_core_data,
	.vfsm = &omap4_vdd_core_vfsm_data,
	.voltdm = {
		.name = "core",
	},
};

/* OMAP4 VDD structures */
static struct omap_vdd_info *omap4_vdd_info[] = {
	&omap4_vdd_mpu_info,
	&omap4_vdd_iva_info,
	&omap4_vdd_core_info,
};

/* OMAP4 specific voltage init functions */
static int __init omap44xx_voltage_early_init(void)
{
	s16 prm_mod = OMAP4430_PRM_DEVICE_INST;
	s16 prm_irqst_ocp_mod = OMAP4430_PRM_OCP_SOCKET_INST;

	if (!cpu_is_omap44xx())
		return 0;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	/*
	 * XXX Will depend on the process, validation, and binning
	 * for the currently-running IC
	 */
<<<<<<< HEAD
#ifdef CONFIG_PM_OPP
	omap4_voltdm_mpu.volt_data = omap44xx_vdd_mpu_volt_data;
	omap4_voltdm_iva.volt_data = omap44xx_vdd_iva_volt_data;
	omap4_voltdm_core.volt_data = omap44xx_vdd_core_volt_data;
#endif

	for (i = 0; voltdm = voltagedomains_omap4[i], voltdm; i++)
		voltdm->sys_clk.name = sys_clk_name;

	voltdm_init(voltagedomains_omap4);
};
=======
	omap4_vdd_mpu_info.volt_data = omap44xx_vdd_mpu_volt_data;
	omap4_vdd_iva_info.volt_data = omap44xx_vdd_iva_volt_data;
	omap4_vdd_core_info.volt_data = omap44xx_vdd_core_volt_data;

	return omap_voltage_early_init(prm_mod, prm_irqst_ocp_mod,
				       omap4_vdd_info,
				       ARRAY_SIZE(omap4_vdd_info));
};
core_initcall(omap44xx_voltage_early_init);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
