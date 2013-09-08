#ifndef _ASM_X86_IDLE_H
#define _ASM_X86_IDLE_H

<<<<<<< HEAD
#define IDLE_START 1
#define IDLE_END 2

struct notifier_block;
void idle_notifier_register(struct notifier_block *n);
void idle_notifier_unregister(struct notifier_block *n);

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#ifdef CONFIG_X86_64
void enter_idle(void);
void exit_idle(void);
#else /* !CONFIG_X86_64 */
static inline void enter_idle(void) { }
static inline void exit_idle(void) { }
<<<<<<< HEAD
static inline void __exit_idle(void) { }
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#endif /* CONFIG_X86_64 */

void amd_e400_remove_cpu(int cpu);

#endif /* _ASM_X86_IDLE_H */
