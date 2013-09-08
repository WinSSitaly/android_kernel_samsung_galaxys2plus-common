<<<<<<< HEAD
#if defined(CONFIG_MMU) && !defined(CONFIG_COLDFIRE)
PHDRS
{
  text PT_LOAD FILEHDR PHDRS FLAGS (7);
  data PT_LOAD FLAGS (7);
}
#ifdef CONFIG_SUN3
#include "vmlinux-sun3.lds"
#else
#include "vmlinux-std.lds"
#endif
#else
#include "vmlinux-nommu.lds"
=======
#ifdef CONFIG_MMU
#include "vmlinux.lds_mm.S"
#else
#include "vmlinux.lds_no.S"
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#endif
