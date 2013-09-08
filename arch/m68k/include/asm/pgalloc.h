#ifndef M68K_PGALLOC_H
#define M68K_PGALLOC_H

#include <linux/mm.h>
#include <linux/highmem.h>
#include <asm/setup.h>

#ifdef CONFIG_MMU
#include <asm/virtconvert.h>
<<<<<<< HEAD
#if defined(CONFIG_COLDFIRE)
#include <asm/mcf_pgalloc.h>
#elif defined(CONFIG_SUN3)
=======
#ifdef CONFIG_SUN3
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <asm/sun3_pgalloc.h>
#else
#include <asm/motorola_pgalloc.h>
#endif

extern void m68k_setup_node(int node);
#endif

#endif /* M68K_PGALLOC_H */
