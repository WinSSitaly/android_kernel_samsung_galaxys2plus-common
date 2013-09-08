#include <linux/kernel.h>
#include <linux/gcd.h>
<<<<<<< HEAD
#include <linux/export.h>
=======
#include <linux/module.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

/* Greatest common divisor */
unsigned long gcd(unsigned long a, unsigned long b)
{
	unsigned long r;

	if (a < b)
		swap(a, b);
<<<<<<< HEAD

	if (!b)
		return a;
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	while ((r = a % b) != 0) {
		a = b;
		b = r;
	}
	return b;
}
EXPORT_SYMBOL_GPL(gcd);
