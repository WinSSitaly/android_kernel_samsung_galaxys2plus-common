#ifndef _LINUX_PCA953X_H
#define _LINUX_PCA953X_H

#include <linux/types.h>
#include <linux/i2c.h>
<<<<<<< HEAD
=======
#include <linux/i2c-kona.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

/* platform data for the PCA9539 16-bit I/O expander driver */

struct pca953x_platform_data {
<<<<<<< HEAD
=======
	struct i2c_slave_platform_data i2c_pdata;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	/* number of the first GPIO */
	unsigned	gpio_base;

	/* initial polarity inversion setting */
	uint16_t	invert;

	/* interrupt base */
	int		irq_base;

	void		*context;	/* param to setup/teardown */

	int		(*setup)(struct i2c_client *client,
				unsigned gpio, unsigned ngpio,
				void *context);
	int		(*teardown)(struct i2c_client *client,
				unsigned gpio, unsigned ngpio,
				void *context);
	const char	*const *names;
};

#endif /* _LINUX_PCA953X_H */
