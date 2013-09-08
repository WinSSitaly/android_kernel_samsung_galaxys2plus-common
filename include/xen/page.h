#ifndef _XEN_PAGE_H
#define _XEN_PAGE_H

#include <asm/xen/page.h>

<<<<<<< HEAD
struct xen_memory_region {
	phys_addr_t start;
	phys_addr_t size;
};

#define XEN_EXTRA_MEM_MAX_REGIONS 128 /* == E820MAX */

extern __initdata
struct xen_memory_region xen_extra_mem[XEN_EXTRA_MEM_MAX_REGIONS];

extern unsigned long xen_released_pages;
=======
extern phys_addr_t xen_extra_mem_start, xen_extra_mem_size;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#endif	/* _XEN_PAGE_H */
