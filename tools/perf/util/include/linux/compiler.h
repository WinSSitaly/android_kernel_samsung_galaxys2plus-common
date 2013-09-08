#ifndef _PERF_LINUX_COMPILER_H_
#define _PERF_LINUX_COMPILER_H_

#ifndef __always_inline
#define __always_inline	inline
#endif
#define __user
<<<<<<< HEAD
#ifndef __attribute_const__
#define __attribute_const__
#endif
=======
#define __attribute_const__
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#define __used		__attribute__((__unused__))

#endif
