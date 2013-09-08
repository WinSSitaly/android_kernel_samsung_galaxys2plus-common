/*
 * arch/arm/mach-vt8500/include/mach/system.h
 *
 */
#include <asm/io.h>

/* PM Software Reset request register */
#define VT8500_PMSR_VIRT	0xf8130060

<<<<<<< HEAD
=======
static inline void arch_idle(void)
{
	cpu_do_idle();
}

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
static inline void arch_reset(char mode, const char *cmd)
{
	writel(1, VT8500_PMSR_VIRT);
}
