<<<<<<< HEAD
#if defined(CONFIG_MMU) && !defined(CONFIG_COLDFIRE)
=======
#ifdef CONFIG_MMU
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include "entry_mm.S"
#else
#include "entry_no.S"
#endif
