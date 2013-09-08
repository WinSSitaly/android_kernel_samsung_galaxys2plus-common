/*
 * altera_uart.h -- Altera UART driver defines.
 */

#ifndef	__ALTUART_H
#define	__ALTUART_H

<<<<<<< HEAD
=======
#include <linux/init.h>

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
struct altera_uart_platform_uart {
	unsigned long mapbase;	/* Physical address base */
	unsigned int irq;	/* Interrupt vector */
	unsigned int uartclk;	/* UART clock rate */
	unsigned int bus_shift;	/* Bus shift (address stride) */
};

<<<<<<< HEAD
=======
int __init early_altera_uart_setup(struct altera_uart_platform_uart *platp);

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#endif /* __ALTUART_H */
