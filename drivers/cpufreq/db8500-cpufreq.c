/*
 * Copyright (C) STMicroelectronics 2009
 * Copyright (C) ST-Ericsson SA 2010
 *
 * License Terms: GNU General Public License v2
 * Author: Sundar Iyer <sundar.iyer@stericsson.com>
 * Author: Martin Persson <martin.persson@stericsson.com>
 * Author: Jonas Aaberg <jonas.aberg@stericsson.com>
 *
 */
#include <linux/kernel.h>
#include <linux/cpufreq.h>
#include <linux/delay.h>
#include <linux/slab.h>
<<<<<<< HEAD
#include <linux/mfd/dbx500-prcmu.h>
=======
#include <linux/mfd/db8500-prcmu.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <mach/id.h>

static struct cpufreq_frequency_table freq_table[] = {
	[0] = {
		.index = 0,
<<<<<<< HEAD
		.frequency = 200000,
	},
	[1] = {
		.index = 1,
		.frequency = 400000,
	},
	[2] = {
		.index = 2,
		.frequency = 800000,
	},
	[3] = {
		/* Used for MAX_OPP, if available */
		.index = 3,
		.frequency = CPUFREQ_TABLE_END,
	},
	[4] = {
		.index = 4,
		.frequency = CPUFREQ_TABLE_END,
	},
};

static enum arm_opp idx2opp[] = {
	ARM_EXTCLK,
=======
		.frequency = 300000,
	},
	[1] = {
		.index = 1,
		.frequency = 600000,
	},
	[2] = {
		/* Used for MAX_OPP, if available */
		.index = 2,
		.frequency = CPUFREQ_TABLE_END,
	},
	[3] = {
		.index = 3,
		.frequency = CPUFREQ_TABLE_END,
	},
};

static enum arm_opp idx2opp[] = {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	ARM_50_OPP,
	ARM_100_OPP,
	ARM_MAX_OPP
};

static struct freq_attr *db8500_cpufreq_attr[] = {
	&cpufreq_freq_attr_scaling_available_freqs,
	NULL,
};

static int db8500_cpufreq_verify_speed(struct cpufreq_policy *policy)
{
	return cpufreq_frequency_table_verify(policy, freq_table);
}

static int db8500_cpufreq_target(struct cpufreq_policy *policy,
				unsigned int target_freq,
				unsigned int relation)
{
	struct cpufreq_freqs freqs;
	unsigned int idx;

	/* scale the target frequency to one of the extremes supported */
	if (target_freq < policy->cpuinfo.min_freq)
		target_freq = policy->cpuinfo.min_freq;
	if (target_freq > policy->cpuinfo.max_freq)
		target_freq = policy->cpuinfo.max_freq;

	/* Lookup the next frequency */
	if (cpufreq_frequency_table_target
	    (policy, freq_table, target_freq, relation, &idx)) {
		return -EINVAL;
	}

	freqs.old = policy->cur;
	freqs.new = freq_table[idx].frequency;
<<<<<<< HEAD
=======
	freqs.cpu = policy->cpu;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	if (freqs.old == freqs.new)
		return 0;

	/* pre-change notification */
<<<<<<< HEAD
	for_each_cpu(freqs.cpu, policy->cpus)
		cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);
=======
	cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	/* request the PRCM unit for opp change */
	if (prcmu_set_arm_opp(idx2opp[idx])) {
		pr_err("db8500-cpufreq:  Failed to set OPP level\n");
		return -EINVAL;
	}

	/* post change notification */
<<<<<<< HEAD
	for_each_cpu(freqs.cpu, policy->cpus)
		cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);
=======
	cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	return 0;
}

static unsigned int db8500_cpufreq_getspeed(unsigned int cpu)
{
	int i;
	/* request the prcm to get the current ARM opp */
	for (i = 0; prcmu_get_arm_opp() != idx2opp[i]; i++)
		;
	return freq_table[i].frequency;
}

static int __cpuinit db8500_cpufreq_init(struct cpufreq_policy *policy)
{
<<<<<<< HEAD
	int i, res;

	BUILD_BUG_ON(ARRAY_SIZE(idx2opp) + 1 != ARRAY_SIZE(freq_table));

	if (prcmu_has_arm_maxopp())
		freq_table[3].frequency = 1000000;

	pr_info("db8500-cpufreq : Available frequencies:\n");
	for (i = 0; freq_table[i].frequency != CPUFREQ_TABLE_END; i++)
		pr_info("  %d Mhz\n", freq_table[i].frequency/1000);
=======
	int res;
	int i;

	BUILD_BUG_ON(ARRAY_SIZE(idx2opp) + 1 != ARRAY_SIZE(freq_table));

	if (cpu_is_u8500v2() && !prcmu_is_u8400()) {
		freq_table[0].frequency = 400000;
		freq_table[1].frequency = 800000;
		if (prcmu_has_arm_maxopp())
			freq_table[2].frequency = 1000000;
	}
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	/* get policy fields based on the table */
	res = cpufreq_frequency_table_cpuinfo(policy, freq_table);
	if (!res)
		cpufreq_frequency_table_get_attr(freq_table, policy->cpu);
	else {
		pr_err("db8500-cpufreq : Failed to read policy table\n");
		return res;
	}

	policy->min = policy->cpuinfo.min_freq;
	policy->max = policy->cpuinfo.max_freq;
	policy->cur = db8500_cpufreq_getspeed(policy->cpu);
<<<<<<< HEAD
=======

	for (i = 0; freq_table[i].frequency != policy->cur; i++)
		;

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	policy->governor = CPUFREQ_DEFAULT_GOVERNOR;

	/*
	 * FIXME : Need to take time measurement across the target()
	 *	   function with no/some/all drivers in the notification
	 *	   list.
	 */
	policy->cpuinfo.transition_latency = 20 * 1000; /* in ns */

	/* policy sharing between dual CPUs */
<<<<<<< HEAD
	cpumask_copy(policy->cpus, cpu_present_mask);
=======
	cpumask_copy(policy->cpus, &cpu_present_map);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	policy->shared_type = CPUFREQ_SHARED_TYPE_ALL;

	return 0;
}

static struct cpufreq_driver db8500_cpufreq_driver = {
	.flags  = CPUFREQ_STICKY,
	.verify = db8500_cpufreq_verify_speed,
	.target = db8500_cpufreq_target,
	.get    = db8500_cpufreq_getspeed,
	.init   = db8500_cpufreq_init,
	.name   = "DB8500",
	.attr   = db8500_cpufreq_attr,
};

static int __init db8500_cpufreq_register(void)
{
	if (!cpu_is_u8500v20_or_later())
		return -ENODEV;

	pr_info("cpufreq for DB8500 started\n");
	return cpufreq_register_driver(&db8500_cpufreq_driver);
}
device_initcall(db8500_cpufreq_register);
