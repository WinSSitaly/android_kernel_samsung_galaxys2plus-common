
#include <linux/kernel.h>
<<<<<<< HEAD
#include <linux/export.h>
=======
#include <linux/module.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

/**
 * int_sqrt - rough approximation to sqrt
 * @x: integer of which to calculate the sqrt
 *
 * A very rough approximation to the sqrt() function.
 */
unsigned long int_sqrt(unsigned long x)
{
	unsigned long op, res, one;

	op = x;
	res = 0;

	one = 1UL << (BITS_PER_LONG - 2);
	while (one > op)
		one >>= 2;

	while (one != 0) {
		if (op >= res + one) {
			op = op - (res + one);
			res = res +  2 * one;
		}
		res /= 2;
		one /= 4;
	}
	return res;
}
EXPORT_SYMBOL(int_sqrt);
