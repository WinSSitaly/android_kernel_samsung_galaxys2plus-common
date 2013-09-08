#include <linux/module.h>
<<<<<<< HEAD
#include <linux/kvm_host.h>
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <asm/ftrace.h>

#ifdef CONFIG_FUNCTION_TRACER
EXPORT_SYMBOL(_mcount);
#endif
<<<<<<< HEAD
#if defined(CONFIG_KVM) || defined(CONFIG_KVM_MODULE)
EXPORT_SYMBOL(sie64a);
#endif
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
