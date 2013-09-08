/*
 * Strings for the various x86 power flags
 *
 * This file must not contain any executable code.
 */

#include <asm/cpufeature.h>

const char *const x86_power_flags[32] = {
	"ts",	/* temperature sensor */
	"fid",  /* frequency id control */
	"vid",  /* voltage id control */
	"ttp",  /* thermal trip */
	"tm",
	"stc",
	"100mhzsteps",
	"hwpstate",
	"",	/* tsc invariant mapped to constant_tsc */
<<<<<<< HEAD
	"cpb",  /* core performance boost */
	"eff_freq_ro", /* Readonly aperf/mperf */
=======
		/* nothing */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
};
