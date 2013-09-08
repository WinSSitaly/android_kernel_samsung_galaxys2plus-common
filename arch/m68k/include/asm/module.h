#ifndef _ASM_M68K_MODULE_H
#define _ASM_M68K_MODULE_H

<<<<<<< HEAD
enum m68k_fixup_type {
	m68k_fixup_memoffset,
	m68k_fixup_vnode_shift,
};

struct m68k_fixup_info {
	enum m68k_fixup_type type;
	void *addr;
};
=======
#ifdef CONFIG_MMU
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

struct mod_arch_specific {
	struct m68k_fixup_info *fixup_start, *fixup_end;
};

<<<<<<< HEAD
#ifdef CONFIG_MMU

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#define MODULE_ARCH_INIT {				\
	.fixup_start		= __start_fixup,	\
	.fixup_end		= __stop_fixup,		\
}


<<<<<<< HEAD
=======
enum m68k_fixup_type {
	m68k_fixup_memoffset,
	m68k_fixup_vnode_shift,
};

struct m68k_fixup_info {
	enum m68k_fixup_type type;
	void *addr;
};

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#define m68k_fixup(type, addr)			\
	"	.section \".m68k_fixup\",\"aw\"\n"	\
	"	.long " #type "," #addr "\n"	\
	"	.previous\n"

<<<<<<< HEAD
#endif /* CONFIG_MMU */

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
extern struct m68k_fixup_info __start_fixup[], __stop_fixup[];

struct module;
extern void module_fixup(struct module *mod, struct m68k_fixup_info *start,
			 struct m68k_fixup_info *end);

<<<<<<< HEAD
=======
#else

struct mod_arch_specific {
};

#endif /* CONFIG_MMU */

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#define Elf_Shdr Elf32_Shdr
#define Elf_Sym Elf32_Sym
#define Elf_Ehdr Elf32_Ehdr

#endif /* _ASM_M68K_MODULE_H */
