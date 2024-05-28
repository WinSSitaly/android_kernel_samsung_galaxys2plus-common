/*
 *  linux/arch/arm/mm/nommu.c
 *
 * ARM uCLinux supporting functions.
 */
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/pagemap.h>
#include <linux/io.h>
#include <linux/memblock.h>

#include <asm/cacheflush.h>
#include <asm/sections.h>
#include <asm/page.h>
#include <asm/setup.h>
<<<<<<< HEAD
#include <asm/traps.h>
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <asm/mach/arch.h>

#include "mm.h"

void __init arm_mm_memblock_reserve(void)
{
	/*
	 * Register the exception vector page.
	 * some architectures which the DRAM is the exception vector to trap,
	 * alloc_page breaks with error, although it is not NULL, but "0."
	 */
	memblock_reserve(CONFIG_VECTORS_BASE, PAGE_SIZE);
}

void __init sanity_check_meminfo(void)
{
<<<<<<< HEAD
	phys_addr_t end = bank_phys_end(&meminfo.bank[meminfo.nr_banks - 1]);
	high_memory = __va(end - 1) + 1;
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

/*
 * paging_init() sets up the page tables, initialises the zone memory
 * maps, and sets up the zero page, bad page and bad page tables.
 */
void __init paging_init(struct machine_desc *mdesc)
{
<<<<<<< HEAD
	early_trap_init((void *)CONFIG_VECTORS_BASE);
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	bootmem_init();
}

/*
 * We don't need to do anything here for nommu machines.
 */
<<<<<<< HEAD
void setup_mm_for_reboot(void)
=======
void setup_mm_for_reboot(char mode)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
}

void flush_dcache_page(struct page *page)
{
	__cpuc_flush_dcache_area(page_address(page), PAGE_SIZE);
}
EXPORT_SYMBOL(flush_dcache_page);

<<<<<<< HEAD
void flush_kernel_dcache_page(struct page *page)
{
	__cpuc_flush_dcache_area(page_address(page), PAGE_SIZE);
}
EXPORT_SYMBOL(flush_kernel_dcache_page);

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
void copy_to_user_page(struct vm_area_struct *vma, struct page *page,
		       unsigned long uaddr, void *dst, const void *src,
		       unsigned long len)
{
	memcpy(dst, src, len);
	if (vma->vm_flags & VM_EXEC)
		__cpuc_coherent_user_range(uaddr, uaddr + len);
}

void __iomem *__arm_ioremap_pfn(unsigned long pfn, unsigned long offset,
				size_t size, unsigned int mtype)
{
	if (pfn >= (0x100000000ULL >> PAGE_SHIFT))
		return NULL;
	return (void __iomem *) (offset + (pfn << PAGE_SHIFT));
}
EXPORT_SYMBOL(__arm_ioremap_pfn);

void __iomem *__arm_ioremap_pfn_caller(unsigned long pfn, unsigned long offset,
			   size_t size, unsigned int mtype, void *caller)
{
	return __arm_ioremap_pfn(pfn, offset, size, mtype);
}

void __iomem *__arm_ioremap(unsigned long phys_addr, size_t size,
			    unsigned int mtype)
{
	return (void __iomem *)phys_addr;
}
EXPORT_SYMBOL(__arm_ioremap);

<<<<<<< HEAD
void __iomem * (*arch_ioremap_caller)(unsigned long, size_t, unsigned int, void *);

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
void __iomem *__arm_ioremap_caller(unsigned long phys_addr, size_t size,
				   unsigned int mtype, void *caller)
{
	return __arm_ioremap(phys_addr, size, mtype);
}

<<<<<<< HEAD
void (*arch_iounmap)(volatile void __iomem *);

void __arm_iounmap(volatile void __iomem *addr)
{
}
EXPORT_SYMBOL(__arm_iounmap);
=======
void __iounmap(volatile void __iomem *addr)
{
}
EXPORT_SYMBOL(__iounmap);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
