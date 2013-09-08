#ifndef __ASMARM_HWCAP_H
#define __ASMARM_HWCAP_H

/*
 * HWCAP flags - for elf_hwcap (in kernel) and AT_HWCAP
 */
<<<<<<< HEAD
#define HWCAP_SWP	(1 << 0)
#define HWCAP_HALF	(1 << 1)
#define HWCAP_THUMB	(1 << 2)
#define HWCAP_26BIT	(1 << 3)	/* Play it safe */
#define HWCAP_FAST_MULT	(1 << 4)
#define HWCAP_FPA	(1 << 5)
#define HWCAP_VFP	(1 << 6)
#define HWCAP_EDSP	(1 << 7)
#define HWCAP_JAVA	(1 << 8)
#define HWCAP_IWMMXT	(1 << 9)
#define HWCAP_CRUNCH	(1 << 10)
#define HWCAP_THUMBEE	(1 << 11)
#define HWCAP_NEON	(1 << 12)
#define HWCAP_VFPv3	(1 << 13)
#define HWCAP_VFPv3D16	(1 << 14)	/* also set for VFPv4-D16 */
#define HWCAP_TLS	(1 << 15)
#define HWCAP_VFPv4	(1 << 16)
#define HWCAP_IDIVA	(1 << 17)
#define HWCAP_IDIVT	(1 << 18)
#define HWCAP_VFPD32	(1 << 19)	/* set if VFP has 32 regs (not 16) */
#define HWCAP_IDIV	(HWCAP_IDIVA | HWCAP_IDIVT)

#if defined(__KERNEL__)
#if !defined(__ASSEMBLY__)
=======
#define HWCAP_SWP	1
#define HWCAP_HALF	2
#define HWCAP_THUMB	4
#define HWCAP_26BIT	8	/* Play it safe */
#define HWCAP_FAST_MULT	16
#define HWCAP_FPA	32
#define HWCAP_VFP	64
#define HWCAP_EDSP	128
#define HWCAP_JAVA	256
#define HWCAP_IWMMXT	512
#define HWCAP_CRUNCH	1024
#define HWCAP_THUMBEE	2048
#define HWCAP_NEON	4096
#define HWCAP_VFPv3	8192
#define HWCAP_VFPv3D16	16384
#define HWCAP_TLS	32768

#if defined(__KERNEL__) && !defined(__ASSEMBLY__)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
/*
 * This yields a mask that user programs can use to figure out what
 * instruction set this cpu supports.
 */
#define ELF_HWCAP	(elf_hwcap)
extern unsigned int elf_hwcap;
#endif
<<<<<<< HEAD
#endif
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#endif
