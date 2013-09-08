/*
 * Baboon Custom IC Management
 *
 * The Baboon custom IC controls the IDE, PCMCIA and media bay on the
 * PowerBook 190. It multiplexes multiple interrupt sources onto the
 * Nubus slot $C interrupt.
 */

#include <linux/types.h>
#include <linux/kernel.h>
<<<<<<< HEAD
#include <linux/irq.h>

=======
#include <linux/mm.h>
#include <linux/delay.h>
#include <linux/init.h>

#include <asm/traps.h>
#include <asm/bootinfo.h>
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <asm/macintosh.h>
#include <asm/macints.h>
#include <asm/mac_baboon.h>

/* #define DEBUG_IRQS */

<<<<<<< HEAD
int baboon_present;
static volatile struct baboon *baboon;
=======
extern void mac_enable_irq(unsigned int);
extern void mac_disable_irq(unsigned int);

int baboon_present;
static volatile struct baboon *baboon;
static unsigned char baboon_disabled;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#if 0
extern int macide_ack_intr(struct ata_channel *);
#endif

/*
 * Baboon initialization.
 */

void __init baboon_init(void)
{
	if (macintosh_config->ident != MAC_MODEL_PB190) {
		baboon = NULL;
		baboon_present = 0;
		return;
	}

	baboon = (struct baboon *) BABOON_BASE;
	baboon_present = 1;

	printk("Baboon detected at %p\n", baboon);
}

/*
 * Baboon interrupt handler. This works a lot like a VIA.
 */

<<<<<<< HEAD
static void baboon_irq(unsigned int irq, struct irq_desc *desc)
=======
static irqreturn_t baboon_irq(int irq, void *dev_id)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	int irq_bit, irq_num;
	unsigned char events;

#ifdef DEBUG_IRQS
	printk("baboon_irq: mb_control %02X mb_ifr %02X mb_status %02X\n",
		(uint) baboon->mb_control, (uint) baboon->mb_ifr,
		(uint) baboon->mb_status);
#endif

<<<<<<< HEAD
	events = baboon->mb_ifr & 0x07;
	if (!events)
		return;
=======
	if (!(events = baboon->mb_ifr & 0x07))
		return IRQ_NONE;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	irq_num = IRQ_BABOON_0;
	irq_bit = 1;
	do {
	        if (events & irq_bit) {
			baboon->mb_ifr &= ~irq_bit;
<<<<<<< HEAD
			generic_handle_irq(irq_num);
=======
			m68k_handle_int(irq_num);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		}
		irq_bit <<= 1;
		irq_num++;
	} while(events >= irq_bit);
#if 0
	if (baboon->mb_ifr & 0x02) macide_ack_intr(NULL);
	/* for now we need to smash all interrupts */
	baboon->mb_ifr &= ~events;
#endif
<<<<<<< HEAD
=======
	return IRQ_HANDLED;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

/*
 * Register the Baboon interrupt dispatcher on nubus slot $C.
 */

void __init baboon_register_interrupts(void)
{
<<<<<<< HEAD
	irq_set_chained_handler(IRQ_NUBUS_C, baboon_irq);
}

/*
 * The means for masking individual Baboon interrupts remains a mystery.
 * However, since we only use the IDE IRQ, we can just enable/disable all
 * Baboon interrupts. If/when we handle more than one Baboon IRQ, we must
 * either figure out how to mask them individually or else implement the
 * same workaround that's used for NuBus slots (see nubus_disabled and
 * via_nubus_irq_shutdown).
=======
	baboon_disabled = 0;
	if (request_irq(IRQ_NUBUS_C, baboon_irq, 0, "baboon", (void *)baboon))
		pr_err("Couldn't register baboon interrupt\n");
}

/*
 * The means for masking individual baboon interrupts remains a mystery, so
 * enable the umbrella interrupt only when no baboon interrupt is disabled.
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
 */

void baboon_irq_enable(int irq)
{
<<<<<<< HEAD
=======
	int irq_idx = IRQ_IDX(irq);

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#ifdef DEBUG_IRQUSE
	printk("baboon_irq_enable(%d)\n", irq);
#endif

<<<<<<< HEAD
	mac_irq_enable(irq_get_irq_data(IRQ_NUBUS_C));
=======
	baboon_disabled &= ~(1 << irq_idx);
	if (!baboon_disabled)
		mac_enable_irq(IRQ_NUBUS_C);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

void baboon_irq_disable(int irq)
{
<<<<<<< HEAD
=======
	int irq_idx = IRQ_IDX(irq);

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#ifdef DEBUG_IRQUSE
	printk("baboon_irq_disable(%d)\n", irq);
#endif

<<<<<<< HEAD
	mac_irq_disable(irq_get_irq_data(IRQ_NUBUS_C));
=======
	baboon_disabled |= 1 << irq_idx;
	if (baboon_disabled)
		mac_disable_irq(IRQ_NUBUS_C);
}

void baboon_irq_clear(int irq)
{
	int irq_idx = IRQ_IDX(irq);

	baboon->mb_ifr &= ~(1 << irq_idx);
}

int baboon_irq_pending(int irq)
{
	int irq_idx = IRQ_IDX(irq);

	return baboon->mb_ifr & (1 << irq_idx);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}
