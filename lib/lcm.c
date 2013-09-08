#include <linux/kernel.h>
#include <linux/gcd.h>
<<<<<<< HEAD
#include <linux/export.h>
#include <linux/lcm.h>
=======
#include <linux/module.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

/* Lowest common multiple */
unsigned long lcm(unsigned long a, unsigned long b)
{
	if (a && b)
		return (a * b) / gcd(a, b);
	else if (b)
		return b;

	return a;
}
EXPORT_SYMBOL_GPL(lcm);
