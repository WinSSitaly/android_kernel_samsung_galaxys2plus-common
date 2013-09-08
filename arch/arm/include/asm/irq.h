#ifndef __ASM_ARM_IRQ_H
#define __ASM_ARM_IRQ_H

<<<<<<< HEAD
#define NR_IRQS_LEGACY	16

#ifndef CONFIG_SPARSE_IRQ
#include <mach/irqs.h>
#else
#define NR_IRQS NR_IRQS_LEGACY
#endif
=======
#include <mach/irqs.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#ifndef irq_canonicalize
#define irq_canonicalize(i)	(i)
#endif

<<<<<<< HEAD
=======
#define NR_IRQS_LEGACY	16

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
/*
 * Use this value to indicate lack of interrupt
 * capability
 */
#ifndef NO_IRQ
#define NO_IRQ	((unsigned int)(-1))
#endif

#ifndef __ASSEMBLY__
struct irqaction;
struct pt_regs;
extern void migrate_irqs(void);

extern void asm_do_IRQ(unsigned int, struct pt_regs *);
<<<<<<< HEAD
void handle_IRQ(unsigned int, struct pt_regs *);
void init_IRQ(void);

=======
void init_IRQ(void);

void arch_trigger_all_cpu_backtrace(void);
#define arch_trigger_all_cpu_backtrace arch_trigger_all_cpu_backtrace

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#endif

#endif

