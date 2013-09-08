#include <linux/kernel.h>
<<<<<<< HEAD
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/page-debug-flags.h>
#include <linux/poison.h>
#include <linux/ratelimit.h>
=======
#include <linux/mm.h>
#include <linux/page-debug-flags.h>
#include <linux/poison.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

static inline void set_page_poison(struct page *page)
{
	__set_bit(PAGE_DEBUG_FLAG_POISON, &page->debug_flags);
}

static inline void clear_page_poison(struct page *page)
{
	__clear_bit(PAGE_DEBUG_FLAG_POISON, &page->debug_flags);
}

static inline bool page_poison(struct page *page)
{
	return test_bit(PAGE_DEBUG_FLAG_POISON, &page->debug_flags);
}

<<<<<<< HEAD
static void poison_page(struct page *page)
{
	void *addr = kmap_atomic(page);

	set_page_poison(page);
	memset(addr, PAGE_POISON, PAGE_SIZE);
	kunmap_atomic(addr);
=======
static void poison_highpage(struct page *page)
{
	/*
	 * Page poisoning for highmem pages is not implemented.
	 *
	 * This can be called from interrupt contexts.
	 * So we need to create a new kmap_atomic slot for this
	 * application and it will need interrupt protection.
	 */
}

static void poison_page(struct page *page)
{
	void *addr;

	if (PageHighMem(page)) {
		poison_highpage(page);
		return;
	}
	set_page_poison(page);
	addr = page_address(page);
	memset(addr, PAGE_POISON, PAGE_SIZE);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

static void poison_pages(struct page *page, int n)
{
	int i;

	for (i = 0; i < n; i++)
		poison_page(page + i);
}

static bool single_bit_flip(unsigned char a, unsigned char b)
{
	unsigned char error = a ^ b;

	return error && !(error & (error - 1));
}

static void check_poison_mem(unsigned char *mem, size_t bytes)
{
<<<<<<< HEAD
	static DEFINE_RATELIMIT_STATE(ratelimit, 5 * HZ, 10);
	unsigned char *start;
	unsigned char *end;

	start = memchr_inv(mem, PAGE_POISON, bytes);
	if (!start)
=======
	unsigned char *start;
	unsigned char *end;

	for (start = mem; start < mem + bytes; start++) {
		if (*start != PAGE_POISON)
			break;
	}
	if (start == mem + bytes)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		return;

	for (end = mem + bytes - 1; end > start; end--) {
		if (*end != PAGE_POISON)
			break;
	}

<<<<<<< HEAD
	if (!__ratelimit(&ratelimit))
=======
	if (!printk_ratelimit())
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		return;
	else if (start == end && single_bit_flip(*start, PAGE_POISON))
		printk(KERN_ERR "pagealloc: single bit error\n");
	else
		printk(KERN_ERR "pagealloc: memory corruption\n");

	print_hex_dump(KERN_ERR, "", DUMP_PREFIX_ADDRESS, 16, 1, start,
			end - start + 1, 1);
	dump_stack();
}

<<<<<<< HEAD
static void unpoison_page(struct page *page)
{
	void *addr;

	if (!page_poison(page))
		return;

	addr = kmap_atomic(page);
	check_poison_mem(addr, PAGE_SIZE);
	clear_page_poison(page);
	kunmap_atomic(addr);
=======
static void unpoison_highpage(struct page *page)
{
	/*
	 * See comment in poison_highpage().
	 * Highmem pages should not be poisoned for now
	 */
	BUG_ON(page_poison(page));
}

static void unpoison_page(struct page *page)
{
	if (PageHighMem(page)) {
		unpoison_highpage(page);
		return;
	}
	if (page_poison(page)) {
		void *addr = page_address(page);

		check_poison_mem(addr, PAGE_SIZE);
		clear_page_poison(page);
	}
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

static void unpoison_pages(struct page *page, int n)
{
	int i;

	for (i = 0; i < n; i++)
		unpoison_page(page + i);
}

void kernel_map_pages(struct page *page, int numpages, int enable)
{
<<<<<<< HEAD
=======
	if (!debug_pagealloc_enabled)
		return;

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (enable)
		unpoison_pages(page, numpages);
	else
		poison_pages(page, numpages);
}
