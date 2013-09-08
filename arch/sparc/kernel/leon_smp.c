/* leon_smp.c: Sparc-Leon SMP support.
 *
 * based on sun4m_smp.c
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 2009 Daniel Hellstrom (daniel@gaisler.com) Aeroflex Gaisler AB
 * Copyright (C) 2009 Konrad Eisele (konrad@gaisler.com) Aeroflex Gaisler AB
 */

#include <asm/head.h>

#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/threads.h>
#include <linux/smp.h>
#include <linux/interrupt.h>
#include <linux/kernel_stat.h>
#include <linux/of.h>
#include <linux/init.h>
#include <linux/spinlock.h>
#include <linux/mm.h>
#include <linux/swap.h>
#include <linux/profile.h>
#include <linux/pm.h>
#include <linux/delay.h>
#include <linux/gfp.h>
<<<<<<< HEAD
#include <linux/cpu.h>
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#include <asm/cacheflush.h>
#include <asm/tlbflush.h>

#include <asm/ptrace.h>
<<<<<<< HEAD
#include <linux/atomic.h>
=======
#include <asm/atomic.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <asm/irq_regs.h>
#include <asm/traps.h>

#include <asm/delay.h>
#include <asm/irq.h>
#include <asm/page.h>
#include <asm/pgalloc.h>
#include <asm/pgtable.h>
#include <asm/oplib.h>
#include <asm/cpudata.h>
#include <asm/asi.h>
#include <asm/leon.h>
#include <asm/leon_amba.h>

#include "kernel.h"

#ifdef CONFIG_SPARC_LEON

#include "irq.h"

extern ctxd_t *srmmu_ctx_table_phys;
static int smp_processors_ready;
extern volatile unsigned long cpu_callin_map[NR_CPUS];
extern cpumask_t smp_commenced_mask;
void __init leon_configure_cache_smp(void);
static void leon_ipi_init(void);

/* IRQ number of LEON IPIs */
int leon_ipi_irq = LEON3_IRQ_IPI_DEFAULT;

static inline unsigned long do_swap(volatile unsigned long *ptr,
				    unsigned long val)
{
	__asm__ __volatile__("swapa [%2] %3, %0\n\t" : "=&r"(val)
			     : "0"(val), "r"(ptr), "i"(ASI_LEON_DCACHE_MISS)
			     : "memory");
	return val;
}

static void smp_setup_percpu_timer(void);

void __cpuinit leon_callin(void)
{
	int cpuid = hard_smpleon_processor_id();

	local_flush_cache_all();
	local_flush_tlb_all();
	leon_configure_cache_smp();

<<<<<<< HEAD
	notify_cpu_starting(cpuid);

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	/* Get our local ticker going. */
	smp_setup_percpu_timer();

	calibrate_delay();
	smp_store_cpu_info(cpuid);

	local_flush_cache_all();
	local_flush_tlb_all();

	/*
	 * Unblock the master CPU _only_ when the scheduler state
	 * of all secondary CPUs will be up-to-date, so after
	 * the SMP initialization the master will be just allowed
	 * to call the scheduler code.
	 * Allow master to continue.
	 */
	do_swap(&cpu_callin_map[cpuid], 1);

	local_flush_cache_all();
	local_flush_tlb_all();

	/* Fix idle thread fields. */
	__asm__ __volatile__("ld [%0], %%g6\n\t" : : "r"(&current_set[cpuid])
			     : "memory" /* paranoid */);

	/* Attach to the address space of init_task. */
	atomic_inc(&init_mm.mm_count);
	current->active_mm = &init_mm;

	while (!cpumask_test_cpu(cpuid, &smp_commenced_mask))
		mb();

	local_irq_enable();
	set_cpu_online(cpuid, true);
}

/*
 *	Cycle through the processors asking the PROM to start each one.
 */

extern struct linux_prom_registers smp_penguin_ctable;

void __init leon_configure_cache_smp(void)
{
	unsigned long cfg = sparc_leon3_get_dcachecfg();
	int me = smp_processor_id();

	if (ASI_LEON3_SYSCTRL_CFG_SSIZE(cfg) > 4) {
		printk(KERN_INFO "Note: SMP with snooping only works on 4k cache, found %dk(0x%x) on cpu %d, disabling caches\n",
		     (unsigned int)ASI_LEON3_SYSCTRL_CFG_SSIZE(cfg),
		     (unsigned int)cfg, (unsigned int)me);
		sparc_leon3_disable_cache();
	} else {
		if (cfg & ASI_LEON3_SYSCTRL_CFG_SNOOPING) {
			sparc_leon3_enable_snooping();
		} else {
			printk(KERN_INFO "Note: You have to enable snooping in the vhdl model cpu %d, disabling caches\n",
			     me);
			sparc_leon3_disable_cache();
		}
	}

	local_flush_cache_all();
	local_flush_tlb_all();
}

void leon_smp_setbroadcast(unsigned int mask)
{
	int broadcast =
	    ((LEON3_BYPASS_LOAD_PA(&(leon3_irqctrl_regs->mpstatus)) >>
	      LEON3_IRQMPSTATUS_BROADCAST) & 1);
	if (!broadcast) {
		prom_printf("######## !!!! The irqmp-ctrl must have broadcast enabled, smp wont work !!!!! ####### nr cpus: %d\n",
		     leon_smp_nrcpus());
		if (leon_smp_nrcpus() > 1) {
			BUG();
		} else {
			prom_printf("continue anyway\n");
			return;
		}
	}
	LEON_BYPASS_STORE_PA(&(leon3_irqctrl_regs->mpbroadcast), mask);
}

unsigned int leon_smp_getbroadcast(void)
{
	unsigned int mask;
	mask = LEON_BYPASS_LOAD_PA(&(leon3_irqctrl_regs->mpbroadcast));
	return mask;
}

int leon_smp_nrcpus(void)
{
	int nrcpu =
	    ((LEON3_BYPASS_LOAD_PA(&(leon3_irqctrl_regs->mpstatus)) >>
	      LEON3_IRQMPSTATUS_CPUNR) & 0xf) + 1;
	return nrcpu;
}

void __init leon_boot_cpus(void)
{
	int nrcpu = leon_smp_nrcpus();
	int me = smp_processor_id();

	/* Setup IPI */
	leon_ipi_init();

	printk(KERN_INFO "%d:(%d:%d) cpus mpirq at 0x%x\n", (unsigned int)me,
	       (unsigned int)nrcpu, (unsigned int)NR_CPUS,
	       (unsigned int)&(leon3_irqctrl_regs->mpstatus));

	leon_enable_irq_cpu(LEON3_IRQ_CROSS_CALL, me);
	leon_enable_irq_cpu(LEON3_IRQ_TICKER, me);
	leon_enable_irq_cpu(leon_ipi_irq, me);

	leon_smp_setbroadcast(1 << LEON3_IRQ_TICKER);

	leon_configure_cache_smp();
	smp_setup_percpu_timer();
	local_flush_cache_all();

}

int __cpuinit leon_boot_one_cpu(int i)
{

	struct task_struct *p;
	int timeout;

	/* Cook up an idler for this guy. */
	p = fork_idle(i);

	current_set[i] = task_thread_info(p);

	/* See trampoline.S:leon_smp_cpu_startup for details...
	 * Initialize the contexts table
	 * Since the call to prom_startcpu() trashes the structure,
	 * we need to re-initialize it for each cpu
	 */
	smp_penguin_ctable.which_io = 0;
	smp_penguin_ctable.phys_addr = (unsigned int)srmmu_ctx_table_phys;
	smp_penguin_ctable.reg_size = 0;

	/* whirrr, whirrr, whirrrrrrrrr... */
	printk(KERN_INFO "Starting CPU %d : (irqmp: 0x%x)\n", (unsigned int)i,
	       (unsigned int)&leon3_irqctrl_regs->mpstatus);
	local_flush_cache_all();

	/* Make sure all IRQs are of from the start for this new CPU */
	LEON_BYPASS_STORE_PA(&leon3_irqctrl_regs->mask[i], 0);

	/* Wake one CPU */
	LEON_BYPASS_STORE_PA(&(leon3_irqctrl_regs->mpstatus), 1 << i);

	/* wheee... it's going... */
	for (timeout = 0; timeout < 10000; timeout++) {
		if (cpu_callin_map[i])
			break;
		udelay(200);
	}
	printk(KERN_INFO "Started CPU %d\n", (unsigned int)i);

	if (!(cpu_callin_map[i])) {
		printk(KERN_ERR "Processor %d is stuck.\n", i);
		return -ENODEV;
	} else {
		leon_enable_irq_cpu(LEON3_IRQ_CROSS_CALL, i);
		leon_enable_irq_cpu(LEON3_IRQ_TICKER, i);
		leon_enable_irq_cpu(leon_ipi_irq, i);
	}

	local_flush_cache_all();
	return 0;
}

void __init leon_smp_done(void)
{

	int i, first;
	int *prev;

	/* setup cpu list for irq rotation */
	first = 0;
	prev = &first;
	for (i = 0; i < NR_CPUS; i++) {
		if (cpu_online(i)) {
			*prev = i;
			prev = &cpu_data(i).next;
		}
	}
	*prev = first;
	local_flush_cache_all();

	/* Free unneeded trap tables */
	if (!cpu_present(1)) {
		ClearPageReserved(virt_to_page(&trapbase_cpu1));
		init_page_count(virt_to_page(&trapbase_cpu1));
		free_page((unsigned long)&trapbase_cpu1);
		totalram_pages++;
		num_physpages++;
	}
	if (!cpu_present(2)) {
		ClearPageReserved(virt_to_page(&trapbase_cpu2));
		init_page_count(virt_to_page(&trapbase_cpu2));
		free_page((unsigned long)&trapbase_cpu2);
		totalram_pages++;
		num_physpages++;
	}
	if (!cpu_present(3)) {
		ClearPageReserved(virt_to_page(&trapbase_cpu3));
		init_page_count(virt_to_page(&trapbase_cpu3));
		free_page((unsigned long)&trapbase_cpu3);
		totalram_pages++;
		num_physpages++;
	}
	/* Ok, they are spinning and ready to go. */
	smp_processors_ready = 1;

}

void leon_irq_rotate(int cpu)
{
}

struct leon_ipi_work {
	int single;
	int msk;
	int resched;
};

static DEFINE_PER_CPU_SHARED_ALIGNED(struct leon_ipi_work, leon_ipi_work);

/* Initialize IPIs on the LEON, in order to save IRQ resources only one IRQ
 * is used for all three types of IPIs.
 */
static void __init leon_ipi_init(void)
{
	int cpu, len;
	struct leon_ipi_work *work;
	struct property *pp;
	struct device_node *rootnp;
	struct tt_entry *trap_table;
	unsigned long flags;

	/* Find IPI IRQ or stick with default value */
	rootnp = of_find_node_by_path("/ambapp0");
	if (rootnp) {
		pp = of_find_property(rootnp, "ipi_num", &len);
		if (pp && (*(int *)pp->value))
			leon_ipi_irq = *(int *)pp->value;
	}
	printk(KERN_INFO "leon: SMP IPIs at IRQ %d\n", leon_ipi_irq);

	/* Adjust so that we jump directly to smpleon_ipi */
	local_irq_save(flags);
	trap_table = &sparc_ttable[SP_TRAP_IRQ1 + (leon_ipi_irq - 1)];
	trap_table->inst_three += smpleon_ipi - real_irq_entry;
	local_flush_cache_all();
	local_irq_restore(flags);

	for_each_possible_cpu(cpu) {
		work = &per_cpu(leon_ipi_work, cpu);
		work->single = work->msk = work->resched = 0;
	}
}

static void leon_ipi_single(int cpu)
{
	struct leon_ipi_work *work = &per_cpu(leon_ipi_work, cpu);

	/* Mark work */
	work->single = 1;

	/* Generate IRQ on the CPU */
	set_cpu_int(cpu, leon_ipi_irq);
}

static void leon_ipi_mask_one(int cpu)
{
	struct leon_ipi_work *work = &per_cpu(leon_ipi_work, cpu);

	/* Mark work */
	work->msk = 1;

	/* Generate IRQ on the CPU */
	set_cpu_int(cpu, leon_ipi_irq);
}

static void leon_ipi_resched(int cpu)
{
	struct leon_ipi_work *work = &per_cpu(leon_ipi_work, cpu);

	/* Mark work */
	work->resched = 1;

	/* Generate IRQ on the CPU (any IRQ will cause resched) */
	set_cpu_int(cpu, leon_ipi_irq);
}

void leonsmp_ipi_interrupt(void)
{
	struct leon_ipi_work *work = &__get_cpu_var(leon_ipi_work);

	if (work->single) {
		work->single = 0;
		smp_call_function_single_interrupt();
	}
	if (work->msk) {
		work->msk = 0;
		smp_call_function_interrupt();
	}
	if (work->resched) {
		work->resched = 0;
		smp_resched_interrupt();
	}
}

static struct smp_funcall {
	smpfunc_t func;
	unsigned long arg1;
	unsigned long arg2;
	unsigned long arg3;
	unsigned long arg4;
	unsigned long arg5;
	unsigned long processors_in[NR_CPUS];	/* Set when ipi entered. */
	unsigned long processors_out[NR_CPUS];	/* Set when ipi exited. */
} ccall_info;

static DEFINE_SPINLOCK(cross_call_lock);

/* Cross calls must be serialized, at least currently. */
static void leon_cross_call(smpfunc_t func, cpumask_t mask, unsigned long arg1,
			    unsigned long arg2, unsigned long arg3,
			    unsigned long arg4)
{
	if (smp_processors_ready) {
		register int high = NR_CPUS - 1;
		unsigned long flags;

		spin_lock_irqsave(&cross_call_lock, flags);

		{
			/* If you make changes here, make sure gcc generates proper code... */
			register smpfunc_t f asm("i0") = func;
			register unsigned long a1 asm("i1") = arg1;
			register unsigned long a2 asm("i2") = arg2;
			register unsigned long a3 asm("i3") = arg3;
			register unsigned long a4 asm("i4") = arg4;
			register unsigned long a5 asm("i5") = 0;

			__asm__ __volatile__("std %0, [%6]\n\t"
					     "std %2, [%6 + 8]\n\t"
					     "std %4, [%6 + 16]\n\t" : :
					     "r"(f), "r"(a1), "r"(a2), "r"(a3),
					     "r"(a4), "r"(a5),
					     "r"(&ccall_info.func));
		}

		/* Init receive/complete mapping, plus fire the IPI's off. */
		{
			register int i;

			cpumask_clear_cpu(smp_processor_id(), &mask);
			cpumask_and(&mask, cpu_online_mask, &mask);
			for (i = 0; i <= high; i++) {
				if (cpumask_test_cpu(i, &mask)) {
					ccall_info.processors_in[i] = 0;
					ccall_info.processors_out[i] = 0;
					set_cpu_int(i, LEON3_IRQ_CROSS_CALL);

				}
			}
		}

		{
			register int i;

			i = 0;
			do {
				if (!cpumask_test_cpu(i, &mask))
					continue;

				while (!ccall_info.processors_in[i])
					barrier();
			} while (++i <= high);

			i = 0;
			do {
				if (!cpumask_test_cpu(i, &mask))
					continue;

				while (!ccall_info.processors_out[i])
					barrier();
			} while (++i <= high);
		}

		spin_unlock_irqrestore(&cross_call_lock, flags);
	}
}

/* Running cross calls. */
void leon_cross_call_irq(void)
{
	int i = smp_processor_id();

	ccall_info.processors_in[i] = 1;
	ccall_info.func(ccall_info.arg1, ccall_info.arg2, ccall_info.arg3,
			ccall_info.arg4, ccall_info.arg5);
	ccall_info.processors_out[i] = 1;
}

irqreturn_t leon_percpu_timer_interrupt(int irq, void *unused)
{
	int cpu = smp_processor_id();

	leon_clear_profile_irq(cpu);

	profile_tick(CPU_PROFILING);

	if (!--prof_counter(cpu)) {
		int user = user_mode(get_irq_regs());

		update_process_times(user);

		prof_counter(cpu) = prof_multiplier(cpu);
	}

	return IRQ_HANDLED;
}

static void __init smp_setup_percpu_timer(void)
{
	int cpu = smp_processor_id();

	prof_counter(cpu) = prof_multiplier(cpu) = 1;
}

void __init leon_blackbox_id(unsigned *addr)
{
	int rd = *addr & 0x3e000000;
	int rs1 = rd >> 11;

	/* patch places where ___b_hard_smp_processor_id appears */
	addr[0] = 0x81444000 | rd;	/* rd %asr17, reg */
	addr[1] = 0x8130201c | rd | rs1;	/* srl reg, 0x1c, reg */
	addr[2] = 0x01000000;	/* nop */
}

void __init leon_blackbox_current(unsigned *addr)
{
	int rd = *addr & 0x3e000000;
	int rs1 = rd >> 11;

	/* patch LOAD_CURRENT macro where ___b_load_current appears */
	addr[0] = 0x81444000 | rd;	/* rd %asr17, reg */
	addr[2] = 0x8130201c | rd | rs1;	/* srl reg, 0x1c, reg */
	addr[4] = 0x81282002 | rd | rs1;	/* sll reg, 0x2, reg */

}

void __init leon_init_smp(void)
{
	/* Patch ipi15 trap table */
	t_nmi[1] = t_nmi[1] + (linux_trap_ipi15_leon - linux_trap_ipi15_sun4m);

	BTFIXUPSET_BLACKBOX(hard_smp_processor_id, leon_blackbox_id);
	BTFIXUPSET_BLACKBOX(load_current, leon_blackbox_current);
	BTFIXUPSET_CALL(smp_cross_call, leon_cross_call, BTFIXUPCALL_NORM);
	BTFIXUPSET_CALL(__hard_smp_processor_id, __leon_processor_id,
			BTFIXUPCALL_NORM);
	BTFIXUPSET_CALL(smp_ipi_resched, leon_ipi_resched, BTFIXUPCALL_NORM);
	BTFIXUPSET_CALL(smp_ipi_single, leon_ipi_single, BTFIXUPCALL_NORM);
	BTFIXUPSET_CALL(smp_ipi_mask_one, leon_ipi_mask_one, BTFIXUPCALL_NORM);
}

#endif /* CONFIG_SPARC_LEON */
