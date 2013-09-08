<<<<<<< HEAD
#ifndef __ASM_IDMAP_H
#define __ASM_IDMAP_H

#include <linux/compiler.h>
#include <asm/pgtable.h>

/* Tag a function as requiring to be executed via an identity mapping. */
#define __idmap __section(.idmap.text) noinline notrace

extern pgd_t *idmap_pgd;

void setup_mm_for_reboot(void);

#endif	/* __ASM_IDMAP_H */
=======
#ifndef _ARM_IDMAP_H
#define _ARM_IDMAP_H

#include <asm/page.h>
#include <asm/sections.h>

void identity_mapping_add(pgd_t *pgd, unsigned long addr, unsigned long end);
void identity_mapping_del(pgd_t *pgd, unsigned long addr, unsigned long end);

/* Page reserved below swapper. */
#define RESERVE_STACK_PAGE	(unsigned long)swapper_pg_dir

void setup_mm_for_reboot(char mode, pgd_t *pgd);

#endif	/* _ARM_IDMAP_H */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
