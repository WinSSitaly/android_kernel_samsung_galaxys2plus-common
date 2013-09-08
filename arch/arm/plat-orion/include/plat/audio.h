#ifndef __PLAT_AUDIO_H
#define __PLAT_AUDIO_H

<<<<<<< HEAD
struct kirkwood_asoc_platform_data {
=======
#include <linux/mbus.h>

struct kirkwood_asoc_platform_data {
	u32 tclk;
	struct mbus_dram_target_info *dram;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	int burst;
};
#endif
