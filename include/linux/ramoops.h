#ifndef __RAMOOPS_H
#define __RAMOOPS_H

/*
 * Ramoops platform data
 * @mem_size	memory size for ramoops
 * @mem_address	physical memory address to contain ramoops
 */

struct ramoops_platform_data {
	unsigned long	mem_size;
	unsigned long	mem_address;
<<<<<<< HEAD
	unsigned long	record_size;
	int		dump_oops;
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
};

#endif
