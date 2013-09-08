#include <linux/bio.h>
#include <linux/io.h>
<<<<<<< HEAD
#include <linux/export.h>
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <xen/page.h>

bool xen_biovec_phys_mergeable(const struct bio_vec *vec1,
			       const struct bio_vec *vec2)
{
	unsigned long mfn1 = pfn_to_mfn(page_to_pfn(vec1->bv_page));
	unsigned long mfn2 = pfn_to_mfn(page_to_pfn(vec2->bv_page));

	return __BIOVEC_PHYS_MERGEABLE(vec1, vec2) &&
		((mfn1 == mfn2) || ((mfn1+1) == mfn2));
}
<<<<<<< HEAD
EXPORT_SYMBOL(xen_biovec_phys_mergeable);
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
