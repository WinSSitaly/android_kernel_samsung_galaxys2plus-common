/* This handles the memory map.. */

<<<<<<< HEAD
#if defined(CONFIG_RAMBASE)
#define PAGE_OFFSET_RAW		CONFIG_RAMBASE
#elif defined(CONFIG_SUN3)
#define PAGE_OFFSET_RAW		0x0E000000
#else
#define PAGE_OFFSET_RAW		0x00000000
=======
#ifdef CONFIG_MMU
#ifndef CONFIG_SUN3
#define PAGE_OFFSET_RAW		0x00000000
#else
#define PAGE_OFFSET_RAW		0x0E000000
#endif
#else
#define	PAGE_OFFSET_RAW		CONFIG_RAMBASE
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#endif
