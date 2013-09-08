#ifndef BCM63XX_GPIO_H
#define BCM63XX_GPIO_H

#include <linux/init.h>
<<<<<<< HEAD
#include <bcm63xx_cpu.h>
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

int __init bcm63xx_gpio_init(void);

static inline unsigned long bcm63xx_gpio_count(void)
{
	switch (bcm63xx_get_cpu_id()) {
	case BCM6358_CPU_ID:
		return 40;
	case BCM6338_CPU_ID:
		return 8;
	case BCM6345_CPU_ID:
		return 16;
<<<<<<< HEAD
	case BCM6368_CPU_ID:
		return 38;
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	case BCM6348_CPU_ID:
	default:
		return 37;
	}
}

#define BCM63XX_GPIO_DIR_OUT	0x0
#define BCM63XX_GPIO_DIR_IN	0x1

#endif /* !BCM63XX_GPIO_H */
