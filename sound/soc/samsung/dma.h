/*
 *  dma.h --
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
<<<<<<< HEAD
 *  ALSA PCM interface for the Samsung SoC
=======
 *  ALSA PCM interface for the Samsung S3C24xx CPU
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
 */

#ifndef _S3C_AUDIO_H
#define _S3C_AUDIO_H

struct s3c_dma_params {
	struct s3c2410_dma_client *client;	/* stream identifier */
	int channel;				/* Channel ID */
	dma_addr_t dma_addr;
	int dma_size;			/* Size of the DMA transfer */
<<<<<<< HEAD
	unsigned ch;
	struct samsung_dma_ops *ops;
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
};

#endif
