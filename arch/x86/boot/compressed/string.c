#include "misc.h"
<<<<<<< HEAD

int memcmp(const void *s1, const void *s2, size_t len)
{
	u8 diff;
	asm("repe; cmpsb; setnz %0"
	    : "=qm" (diff), "+D" (s1), "+S" (s2), "+c" (len));
	return diff;
}

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include "../string.c"
