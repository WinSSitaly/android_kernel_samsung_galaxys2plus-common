#ifndef _SPARC64_PGALLOC_H
#define _SPARC64_PGALLOC_H

#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/slab.h>
<<<<<<< HEAD
=======
#include <linux/quicklist.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#include <asm/spitfire.h>
#include <asm/cpudata.h>
#include <asm/cacheflush.h>
#include <asm/page.h>

/* Page table allocation/freeing. */

<<<<<<< HEAD
extern struct kmem_cache *pgtable_cache;

static inline pgd_t *pgd_alloc(struct mm_struct *mm)
{
	return kmem_cache_alloc(pgtable_cache, GFP_KERNEL);
=======
static inline pgd_t *pgd_alloc(struct mm_struct *mm)
{
	return quicklist_alloc(0, GFP_KERNEL, NULL);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

static inline void pgd_free(struct mm_struct *mm, pgd_t *pgd)
{
<<<<<<< HEAD
	kmem_cache_free(pgtable_cache, pgd);
=======
	quicklist_free(0, NULL, pgd);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

#define pud_populate(MM, PUD, PMD)	pud_set(PUD, PMD)

static inline pmd_t *pmd_alloc_one(struct mm_struct *mm, unsigned long addr)
{
<<<<<<< HEAD
	return kmem_cache_alloc(pgtable_cache,
				GFP_KERNEL|__GFP_REPEAT);
=======
	return quicklist_alloc(0, GFP_KERNEL, NULL);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

static inline void pmd_free(struct mm_struct *mm, pmd_t *pmd)
{
<<<<<<< HEAD
	kmem_cache_free(pgtable_cache, pmd);
=======
	quicklist_free(0, NULL, pmd);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

static inline pte_t *pte_alloc_one_kernel(struct mm_struct *mm,
					  unsigned long address)
{
<<<<<<< HEAD
	return (pte_t *)__get_free_page(GFP_KERNEL | __GFP_REPEAT | __GFP_ZERO);
=======
	return quicklist_alloc(0, GFP_KERNEL, NULL);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

static inline pgtable_t pte_alloc_one(struct mm_struct *mm,
					unsigned long address)
{
	struct page *page;
<<<<<<< HEAD
	pte_t *pte;

	pte = pte_alloc_one_kernel(mm, address);
	if (!pte)
		return NULL;
	page = virt_to_page(pte);
=======
	void *pg;

	pg = quicklist_alloc(0, GFP_KERNEL, NULL);
	if (!pg)
		return NULL;
	page = virt_to_page(pg);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	pgtable_page_ctor(page);
	return page;
}

static inline void pte_free_kernel(struct mm_struct *mm, pte_t *pte)
{
<<<<<<< HEAD
	free_page((unsigned long)pte);
=======
	quicklist_free(0, NULL, pte);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

static inline void pte_free(struct mm_struct *mm, pgtable_t ptepage)
{
	pgtable_page_dtor(ptepage);
<<<<<<< HEAD
	__free_page(ptepage);
}

=======
	quicklist_free_page(0, NULL, ptepage);
}


>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#define pmd_populate_kernel(MM, PMD, PTE)	pmd_set(PMD, PTE)
#define pmd_populate(MM,PMD,PTE_PAGE)		\
	pmd_populate_kernel(MM,PMD,page_address(PTE_PAGE))
#define pmd_pgtable(pmd) pmd_page(pmd)

<<<<<<< HEAD
#define check_pgt_cache()	do { } while (0)

static inline void pgtable_free(void *table, bool is_page)
{
	if (is_page)
		free_page((unsigned long)table);
	else
		kmem_cache_free(pgtable_cache, table);
}

#ifdef CONFIG_SMP

struct mmu_gather;
extern void tlb_remove_table(struct mmu_gather *, void *);

static inline void pgtable_free_tlb(struct mmu_gather *tlb, void *table, bool is_page)
{
	unsigned long pgf = (unsigned long)table;
	if (is_page)
		pgf |= 0x1UL;
	tlb_remove_table(tlb, (void *)pgf);
}

static inline void __tlb_remove_table(void *_table)
{
	void *table = (void *)((unsigned long)_table & ~0x1UL);
	bool is_page = false;

	if ((unsigned long)_table & 0x1UL)
		is_page = true;
	pgtable_free(table, is_page);
}
#else /* CONFIG_SMP */
static inline void pgtable_free_tlb(struct mmu_gather *tlb, void *table, bool is_page)
{
	pgtable_free(table, is_page);
}
#endif /* !CONFIG_SMP */

static inline void __pte_free_tlb(struct mmu_gather *tlb, struct page *ptepage,
				  unsigned long address)
{
	pgtable_page_dtor(ptepage);
	pgtable_free_tlb(tlb, page_address(ptepage), true);
}

#define __pmd_free_tlb(tlb, pmd, addr)		      \
	pgtable_free_tlb(tlb, pmd, false)
=======
static inline void check_pgt_cache(void)
{
	quicklist_trim(0, NULL, 25, 16);
}

#define __pte_free_tlb(tlb, pte, addr)	pte_free((tlb)->mm, pte)
#define __pmd_free_tlb(tlb, pmd, addr)	pmd_free((tlb)->mm, pmd)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#endif /* _SPARC64_PGALLOC_H */
