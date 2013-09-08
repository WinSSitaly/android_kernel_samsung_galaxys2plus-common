#ifndef _M68K_ATARI_STRAM_H
#define _M68K_ATARI_STRAM_H

/*
 * Functions for Atari ST-RAM management
 */

/* public interface */
<<<<<<< HEAD
void *atari_stram_alloc(unsigned long size, const char *owner);
=======
void *atari_stram_alloc(long size, const char *owner);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
void atari_stram_free(void *);

/* functions called internally by other parts of the kernel */
void atari_stram_init(void);
void atari_stram_reserve_pages(void *start_mem);
<<<<<<< HEAD
=======
void atari_stram_mem_init_hook (void);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#endif /*_M68K_ATARI_STRAM_H */
