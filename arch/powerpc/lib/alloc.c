#include <linux/types.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/bootmem.h>
#include <linux/string.h>
<<<<<<< HEAD
#include <asm/setup.h>

=======

#include <asm/system.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

void * __init_refok zalloc_maybe_bootmem(size_t size, gfp_t mask)
{
	void *p;

	if (mem_init_done)
		p = kzalloc(size, mask);
	else {
		p = alloc_bootmem(size);
		if (p)
			memset(p, 0, size);
	}
	return p;
}
