/*
 * Generic PWM backlight driver data - see drivers/video/backlight/pwm_bl.c
 */
#ifndef __LINUX_PWM_BACKLIGHT_H
#define __LINUX_PWM_BACKLIGHT_H

#include <linux/backlight.h>

struct platform_pwm_backlight_data {
<<<<<<< HEAD
	int pwm_id;
=======
	const char *pwm_name;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	unsigned int max_brightness;
	unsigned int dft_brightness;
	unsigned int lth_brightness;
	unsigned int pwm_period_ns;
<<<<<<< HEAD
	int (*init)(struct device *dev);
	int (*notify)(struct device *dev, int brightness);
	void (*notify_after)(struct device *dev, int brightness);
=======
	unsigned int polarity;
	int enable_gpio;
	int (*init)(struct device *dev);
	int (*notify)(struct device *dev, int brightness);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	void (*exit)(struct device *dev);
	int (*check_fb)(struct device *dev, struct fb_info *info);
};

#endif
