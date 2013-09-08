#ifndef __linux_video_edid_h__
#define __linux_video_edid_h__

<<<<<<< HEAD
=======
#if !defined(__KERNEL__) || defined(CONFIG_X86)

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
struct edid_info {
	unsigned char dummy[128];
};

#ifdef __KERNEL__
<<<<<<< HEAD
#ifdef CONFIG_X86
extern struct edid_info edid_info;
#endif
=======
extern struct edid_info edid_info;
#endif /* __KERNEL__ */

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#endif

#endif /* __linux_video_edid_h__ */
