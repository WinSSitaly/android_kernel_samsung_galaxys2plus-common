/*
 * isac.c   ISAC specific routines
 *
 * Author       Karsten Keil <keil@isdn4linux.de>
 *
 * Copyright 2009  by Karsten Keil <keil@isdn4linux.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

<<<<<<< HEAD
#include <linux/irqreturn.h>
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/mISDNhw.h>
#include "ipac.h"


#define DBUSY_TIMER_VALUE	80
#define ARCOFI_USE		1

#define ISAC_REV		"2.0"

MODULE_AUTHOR("Karsten Keil");
MODULE_VERSION(ISAC_REV);
MODULE_LICENSE("GPL v2");

#define ReadISAC(is, o)		(is->read_reg(is->dch.hw, o + is->off))
#define	WriteISAC(is, o, v)	(is->write_reg(is->dch.hw, o + is->off, v))
#define ReadHSCX(h, o)		(h->ip->read_reg(h->ip->hw, h->off + o))
#define WriteHSCX(h, o, v)	(h->ip->write_reg(h->ip->hw, h->off + o, v))
#define ReadIPAC(ip, o)		(ip->read_reg(ip->hw, o))
#define WriteIPAC(ip, o, v)	(ip->write_reg(ip->hw, o, v))

static inline void
ph_command(struct isac_hw *isac, u8 command)
{
	pr_debug("%s: ph_command %x\n", isac->name, command);
	if (isac->type & IPAC_TYPE_ISACX)
		WriteISAC(isac, ISACX_CIX0, (command << 4) | 0xE);
	else
		WriteISAC(isac, ISAC_CIX0, (command << 2) | 3);
}

static void
isac_ph_state_change(struct isac_hw *isac)
{
	switch (isac->state) {
	case (ISAC_IND_RS):
	case (ISAC_IND_EI):
		ph_command(isac, ISAC_CMD_DUI);
	}
	schedule_event(&isac->dch, FLG_PHCHANGE);
}

static void
isac_ph_state_bh(struct dchannel *dch)
{
	struct isac_hw *isac = container_of(dch, struct isac_hw, dch);

	switch (isac->state) {
	case ISAC_IND_RS:
	case ISAC_IND_EI:
		dch->state = 0;
		l1_event(dch->l1, HW_RESET_IND);
		break;
	case ISAC_IND_DID:
		dch->state = 3;
		l1_event(dch->l1, HW_DEACT_CNF);
		break;
	case ISAC_IND_DR:
		dch->state = 3;
		l1_event(dch->l1, HW_DEACT_IND);
		break;
	case ISAC_IND_PU:
		dch->state = 4;
		l1_event(dch->l1, HW_POWERUP_IND);
		break;
	case ISAC_IND_RSY:
		if (dch->state <= 5) {
			dch->state = 5;
			l1_event(dch->l1, ANYSIGNAL);
		} else {
			dch->state = 8;
			l1_event(dch->l1, LOSTFRAMING);
		}
		break;
	case ISAC_IND_ARD:
		dch->state = 6;
		l1_event(dch->l1, INFO2);
		break;
	case ISAC_IND_AI8:
		dch->state = 7;
		l1_event(dch->l1, INFO4_P8);
		break;
	case ISAC_IND_AI10:
		dch->state = 7;
		l1_event(dch->l1, INFO4_P10);
		break;
	}
	pr_debug("%s: TE newstate %x\n", isac->name, dch->state);
}

void
isac_empty_fifo(struct isac_hw *isac, int count)
{
	u8 *ptr;

	pr_debug("%s: %s  %d\n", isac->name, __func__, count);

	if (!isac->dch.rx_skb) {
		isac->dch.rx_skb = mI_alloc_skb(isac->dch.maxlen, GFP_ATOMIC);
		if (!isac->dch.rx_skb) {
			pr_info("%s: D receive out of memory\n", isac->name);
			WriteISAC(isac, ISAC_CMDR, 0x80);
			return;
		}
	}
	if ((isac->dch.rx_skb->len + count) >= isac->dch.maxlen) {
		pr_debug("%s: %s overrun %d\n", isac->name, __func__,
<<<<<<< HEAD
			 isac->dch.rx_skb->len + count);
=======
			    isac->dch.rx_skb->len + count);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		WriteISAC(isac, ISAC_CMDR, 0x80);
		return;
	}
	ptr = skb_put(isac->dch.rx_skb, count);
	isac->read_fifo(isac->dch.hw, isac->off, ptr, count);
	WriteISAC(isac, ISAC_CMDR, 0x80);
	if (isac->dch.debug & DEBUG_HW_DFIFO) {
		char	pfx[MISDN_MAX_IDLEN + 16];

		snprintf(pfx, MISDN_MAX_IDLEN + 15, "D-recv %s %d ",
<<<<<<< HEAD
			 isac->name, count);
=======
			isac->name, count);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		print_hex_dump_bytes(pfx, DUMP_PREFIX_OFFSET, ptr, count);
	}
}

static void
isac_fill_fifo(struct isac_hw *isac)
{
	int count, more;
	u8 *ptr;

	if (!isac->dch.tx_skb)
		return;
	count = isac->dch.tx_skb->len - isac->dch.tx_idx;
	if (count <= 0)
		return;

	more = 0;
	if (count > 32) {
		more = !0;
		count = 32;
	}
	pr_debug("%s: %s  %d\n", isac->name, __func__, count);
	ptr = isac->dch.tx_skb->data + isac->dch.tx_idx;
	isac->dch.tx_idx += count;
	isac->write_fifo(isac->dch.hw, isac->off, ptr, count);
	WriteISAC(isac, ISAC_CMDR, more ? 0x8 : 0xa);
	if (test_and_set_bit(FLG_BUSY_TIMER, &isac->dch.Flags)) {
		pr_debug("%s: %s dbusytimer running\n", isac->name, __func__);
		del_timer(&isac->dch.timer);
	}
	init_timer(&isac->dch.timer);
	isac->dch.timer.expires = jiffies + ((DBUSY_TIMER_VALUE * HZ)/1000);
	add_timer(&isac->dch.timer);
	if (isac->dch.debug & DEBUG_HW_DFIFO) {
		char	pfx[MISDN_MAX_IDLEN + 16];

		snprintf(pfx, MISDN_MAX_IDLEN + 15, "D-send %s %d ",
<<<<<<< HEAD
			 isac->name, count);
=======
			isac->name, count);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		print_hex_dump_bytes(pfx, DUMP_PREFIX_OFFSET, ptr, count);
	}
}

static void
isac_rme_irq(struct isac_hw *isac)
{
	u8 val, count;

	val = ReadISAC(isac, ISAC_RSTA);
	if ((val & 0x70) != 0x20) {
		if (val & 0x40) {
			pr_debug("%s: ISAC RDO\n", isac->name);
#ifdef ERROR_STATISTIC
			isac->dch.err_rx++;
#endif
		}
		if (!(val & 0x20)) {
			pr_debug("%s: ISAC CRC error\n", isac->name);
#ifdef ERROR_STATISTIC
			isac->dch.err_crc++;
#endif
		}
		WriteISAC(isac, ISAC_CMDR, 0x80);
		if (isac->dch.rx_skb)
			dev_kfree_skb(isac->dch.rx_skb);
		isac->dch.rx_skb = NULL;
	} else {
		count = ReadISAC(isac, ISAC_RBCL) & 0x1f;
		if (count == 0)
			count = 32;
		isac_empty_fifo(isac, count);
		recv_Dchannel(&isac->dch);
	}
}

static void
isac_xpr_irq(struct isac_hw *isac)
{
	if (test_and_clear_bit(FLG_BUSY_TIMER, &isac->dch.Flags))
		del_timer(&isac->dch.timer);
	if (isac->dch.tx_skb && isac->dch.tx_idx < isac->dch.tx_skb->len) {
		isac_fill_fifo(isac);
	} else {
		if (isac->dch.tx_skb)
			dev_kfree_skb(isac->dch.tx_skb);
		if (get_next_dframe(&isac->dch))
			isac_fill_fifo(isac);
	}
}

static void
isac_retransmit(struct isac_hw *isac)
{
	if (test_and_clear_bit(FLG_BUSY_TIMER, &isac->dch.Flags))
		del_timer(&isac->dch.timer);
	if (test_bit(FLG_TX_BUSY, &isac->dch.Flags)) {
		/* Restart frame */
		isac->dch.tx_idx = 0;
		isac_fill_fifo(isac);
	} else if (isac->dch.tx_skb) { /* should not happen */
		pr_info("%s: tx_skb exist but not busy\n", isac->name);
		test_and_set_bit(FLG_TX_BUSY, &isac->dch.Flags);
		isac->dch.tx_idx = 0;
		isac_fill_fifo(isac);
	} else {
		pr_info("%s: ISAC XDU no TX_BUSY\n", isac->name);
		if (get_next_dframe(&isac->dch))
			isac_fill_fifo(isac);
	}
}

static void
isac_mos_irq(struct isac_hw *isac)
{
	u8 val;
	int ret;

	val = ReadISAC(isac, ISAC_MOSR);
	pr_debug("%s: ISAC MOSR %02x\n", isac->name, val);
#if ARCOFI_USE
	if (val & 0x08) {
		if (!isac->mon_rx) {
			isac->mon_rx = kmalloc(MAX_MON_FRAME, GFP_ATOMIC);
			if (!isac->mon_rx) {
				pr_info("%s: ISAC MON RX out of memory!\n",
					isac->name);
				isac->mocr &= 0xf0;
				isac->mocr |= 0x0a;
				WriteISAC(isac, ISAC_MOCR, isac->mocr);
				goto afterMONR0;
			} else
				isac->mon_rxp = 0;
		}
		if (isac->mon_rxp >= MAX_MON_FRAME) {
			isac->mocr &= 0xf0;
			isac->mocr |= 0x0a;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			isac->mon_rxp = 0;
			pr_debug("%s: ISAC MON RX overflow!\n", isac->name);
			goto afterMONR0;
		}
		isac->mon_rx[isac->mon_rxp++] = ReadISAC(isac, ISAC_MOR0);
		pr_debug("%s: ISAC MOR0 %02x\n", isac->name,
<<<<<<< HEAD
			 isac->mon_rx[isac->mon_rxp - 1]);
=======
			isac->mon_rx[isac->mon_rxp - 1]);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		if (isac->mon_rxp == 1) {
			isac->mocr |= 0x04;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
		}
	}
afterMONR0:
	if (val & 0x80) {
		if (!isac->mon_rx) {
			isac->mon_rx = kmalloc(MAX_MON_FRAME, GFP_ATOMIC);
			if (!isac->mon_rx) {
				pr_info("%s: ISAC MON RX out of memory!\n",
					isac->name);
				isac->mocr &= 0x0f;
				isac->mocr |= 0xa0;
				WriteISAC(isac, ISAC_MOCR, isac->mocr);
				goto afterMONR1;
			} else
				isac->mon_rxp = 0;
		}
		if (isac->mon_rxp >= MAX_MON_FRAME) {
			isac->mocr &= 0x0f;
			isac->mocr |= 0xa0;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			isac->mon_rxp = 0;
			pr_debug("%s: ISAC MON RX overflow!\n", isac->name);
			goto afterMONR1;
		}
		isac->mon_rx[isac->mon_rxp++] = ReadISAC(isac, ISAC_MOR1);
		pr_debug("%s: ISAC MOR1 %02x\n", isac->name,
<<<<<<< HEAD
			 isac->mon_rx[isac->mon_rxp - 1]);
=======
			isac->mon_rx[isac->mon_rxp - 1]);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		isac->mocr |= 0x40;
		WriteISAC(isac, ISAC_MOCR, isac->mocr);
	}
afterMONR1:
	if (val & 0x04) {
		isac->mocr &= 0xf0;
		WriteISAC(isac, ISAC_MOCR, isac->mocr);
		isac->mocr |= 0x0a;
		WriteISAC(isac, ISAC_MOCR, isac->mocr);
		if (isac->monitor) {
			ret = isac->monitor(isac->dch.hw, MONITOR_RX_0,
<<<<<<< HEAD
					    isac->mon_rx, isac->mon_rxp);
=======
				isac->mon_rx, isac->mon_rxp);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			if (ret)
				kfree(isac->mon_rx);
		} else {
			pr_info("%s: MONITOR 0 received %d but no user\n",
				isac->name, isac->mon_rxp);
			kfree(isac->mon_rx);
		}
		isac->mon_rx = NULL;
		isac->mon_rxp = 0;
	}
	if (val & 0x40) {
		isac->mocr &= 0x0f;
		WriteISAC(isac, ISAC_MOCR, isac->mocr);
		isac->mocr |= 0xa0;
		WriteISAC(isac, ISAC_MOCR, isac->mocr);
		if (isac->monitor) {
			ret = isac->monitor(isac->dch.hw, MONITOR_RX_1,
<<<<<<< HEAD
					    isac->mon_rx, isac->mon_rxp);
=======
				isac->mon_rx, isac->mon_rxp);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			if (ret)
				kfree(isac->mon_rx);
		} else {
			pr_info("%s: MONITOR 1 received %d but no user\n",
				isac->name, isac->mon_rxp);
			kfree(isac->mon_rx);
		}
		isac->mon_rx = NULL;
		isac->mon_rxp = 0;
	}
	if (val & 0x02) {
		if ((!isac->mon_tx) || (isac->mon_txc &&
<<<<<<< HEAD
					(isac->mon_txp >= isac->mon_txc) && !(val & 0x08))) {
=======
			(isac->mon_txp >= isac->mon_txc) && !(val & 0x08))) {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			isac->mocr &= 0xf0;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			isac->mocr |= 0x0a;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			if (isac->mon_txc && (isac->mon_txp >= isac->mon_txc)) {
				if (isac->monitor)
					ret = isac->monitor(isac->dch.hw,
<<<<<<< HEAD
							    MONITOR_TX_0, NULL, 0);
=======
						MONITOR_TX_0, NULL, 0);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			}
			kfree(isac->mon_tx);
			isac->mon_tx = NULL;
			isac->mon_txc = 0;
			isac->mon_txp = 0;
			goto AfterMOX0;
		}
		if (isac->mon_txc && (isac->mon_txp >= isac->mon_txc)) {
			if (isac->monitor)
				ret = isac->monitor(isac->dch.hw,
<<<<<<< HEAD
						    MONITOR_TX_0, NULL, 0);
=======
					MONITOR_TX_0, NULL, 0);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			kfree(isac->mon_tx);
			isac->mon_tx = NULL;
			isac->mon_txc = 0;
			isac->mon_txp = 0;
			goto AfterMOX0;
		}
		WriteISAC(isac, ISAC_MOX0, isac->mon_tx[isac->mon_txp++]);
		pr_debug("%s: ISAC %02x -> MOX0\n", isac->name,
<<<<<<< HEAD
			 isac->mon_tx[isac->mon_txp - 1]);
=======
			isac->mon_tx[isac->mon_txp - 1]);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}
AfterMOX0:
	if (val & 0x20) {
		if ((!isac->mon_tx) || (isac->mon_txc &&
<<<<<<< HEAD
					(isac->mon_txp >= isac->mon_txc) && !(val & 0x80))) {
=======
			(isac->mon_txp >= isac->mon_txc) && !(val & 0x80))) {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			isac->mocr &= 0x0f;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			isac->mocr |= 0xa0;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			if (isac->mon_txc && (isac->mon_txp >= isac->mon_txc)) {
				if (isac->monitor)
					ret = isac->monitor(isac->dch.hw,
<<<<<<< HEAD
							    MONITOR_TX_1, NULL, 0);
=======
						MONITOR_TX_1, NULL, 0);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			}
			kfree(isac->mon_tx);
			isac->mon_tx = NULL;
			isac->mon_txc = 0;
			isac->mon_txp = 0;
			goto AfterMOX1;
		}
		if (isac->mon_txc && (isac->mon_txp >= isac->mon_txc)) {
			if (isac->monitor)
				ret = isac->monitor(isac->dch.hw,
<<<<<<< HEAD
						    MONITOR_TX_1, NULL, 0);
=======
					MONITOR_TX_1, NULL, 0);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			kfree(isac->mon_tx);
			isac->mon_tx = NULL;
			isac->mon_txc = 0;
			isac->mon_txp = 0;
			goto AfterMOX1;
		}
		WriteISAC(isac, ISAC_MOX1, isac->mon_tx[isac->mon_txp++]);
		pr_debug("%s: ISAC %02x -> MOX1\n", isac->name,
<<<<<<< HEAD
			 isac->mon_tx[isac->mon_txp - 1]);
=======
			isac->mon_tx[isac->mon_txp - 1]);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}
AfterMOX1:
	val = 0; /* dummy to avoid warning */
#endif
}

static void
isac_cisq_irq(struct isac_hw *isac) {
	u8 val;

	val = ReadISAC(isac, ISAC_CIR0);
	pr_debug("%s: ISAC CIR0 %02X\n", isac->name, val);
	if (val & 2) {
		pr_debug("%s: ph_state change %x->%x\n", isac->name,
<<<<<<< HEAD
			 isac->state, (val >> 2) & 0xf);
=======
			isac->state, (val >> 2) & 0xf);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		isac->state = (val >> 2) & 0xf;
		isac_ph_state_change(isac);
	}
	if (val & 1) {
		val = ReadISAC(isac, ISAC_CIR1);
		pr_debug("%s: ISAC CIR1 %02X\n", isac->name, val);
	}
}

static void
isacsx_cic_irq(struct isac_hw *isac)
{
	u8 val;

	val = ReadISAC(isac, ISACX_CIR0);
	pr_debug("%s: ISACX CIR0 %02X\n", isac->name, val);
	if (val & ISACX_CIR0_CIC0) {
		pr_debug("%s: ph_state change %x->%x\n", isac->name,
<<<<<<< HEAD
			 isac->state, val >> 4);
=======
			isac->state, val >> 4);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		isac->state = val >> 4;
		isac_ph_state_change(isac);
	}
}

static void
isacsx_rme_irq(struct isac_hw *isac)
{
	int count;
	u8 val;

	val = ReadISAC(isac, ISACX_RSTAD);
	if ((val & (ISACX_RSTAD_VFR |
		    ISACX_RSTAD_RDO |
		    ISACX_RSTAD_CRC |
		    ISACX_RSTAD_RAB))
	    != (ISACX_RSTAD_VFR | ISACX_RSTAD_CRC)) {
		pr_debug("%s: RSTAD %#x, dropped\n", isac->name, val);
#ifdef ERROR_STATISTIC
		if (val & ISACX_RSTAD_CRC)
			isac->dch.err_rx++;
		else
			isac->dch.err_crc++;
#endif
		WriteISAC(isac, ISACX_CMDRD, ISACX_CMDRD_RMC);
		if (isac->dch.rx_skb)
			dev_kfree_skb(isac->dch.rx_skb);
		isac->dch.rx_skb = NULL;
	} else {
		count = ReadISAC(isac, ISACX_RBCLD) & 0x1f;
		if (count == 0)
			count = 32;
		isac_empty_fifo(isac, count);
		if (isac->dch.rx_skb) {
			skb_trim(isac->dch.rx_skb, isac->dch.rx_skb->len - 1);
			pr_debug("%s: dchannel received %d\n", isac->name,
<<<<<<< HEAD
				 isac->dch.rx_skb->len);
=======
				isac->dch.rx_skb->len);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			recv_Dchannel(&isac->dch);
		}
	}
}

irqreturn_t
mISDNisac_irq(struct isac_hw *isac, u8 val)
{
	if (unlikely(!val))
		return IRQ_NONE;
	pr_debug("%s: ISAC interrupt %02x\n", isac->name, val);
	if (isac->type & IPAC_TYPE_ISACX) {
		if (val & ISACX__CIC)
			isacsx_cic_irq(isac);
		if (val & ISACX__ICD) {
			val = ReadISAC(isac, ISACX_ISTAD);
			pr_debug("%s: ISTAD %02x\n", isac->name, val);
			if (val & ISACX_D_XDU) {
				pr_debug("%s: ISAC XDU\n", isac->name);
#ifdef ERROR_STATISTIC
				isac->dch.err_tx++;
#endif
				isac_retransmit(isac);
			}
			if (val & ISACX_D_XMR) {
				pr_debug("%s: ISAC XMR\n", isac->name);
#ifdef ERROR_STATISTIC
				isac->dch.err_tx++;
#endif
				isac_retransmit(isac);
			}
			if (val & ISACX_D_XPR)
				isac_xpr_irq(isac);
			if (val & ISACX_D_RFO) {
				pr_debug("%s: ISAC RFO\n", isac->name);
				WriteISAC(isac, ISACX_CMDRD, ISACX_CMDRD_RMC);
			}
			if (val & ISACX_D_RME)
				isacsx_rme_irq(isac);
			if (val & ISACX_D_RPF)
				isac_empty_fifo(isac, 0x20);
		}
	} else {
		if (val & 0x80)	/* RME */
			isac_rme_irq(isac);
		if (val & 0x40)	/* RPF */
			isac_empty_fifo(isac, 32);
		if (val & 0x10)	/* XPR */
			isac_xpr_irq(isac);
		if (val & 0x04)	/* CISQ */
			isac_cisq_irq(isac);
		if (val & 0x20)	/* RSC - never */
			pr_debug("%s: ISAC RSC interrupt\n", isac->name);
		if (val & 0x02)	/* SIN - never */
			pr_debug("%s: ISAC SIN interrupt\n", isac->name);
		if (val & 0x01) {	/* EXI */
			val = ReadISAC(isac, ISAC_EXIR);
			pr_debug("%s: ISAC EXIR %02x\n", isac->name, val);
			if (val & 0x80)	/* XMR */
				pr_debug("%s: ISAC XMR\n", isac->name);
			if (val & 0x40) { /* XDU */
				pr_debug("%s: ISAC XDU\n", isac->name);
#ifdef ERROR_STATISTIC
				isac->dch.err_tx++;
#endif
				isac_retransmit(isac);
			}
			if (val & 0x04)	/* MOS */
				isac_mos_irq(isac);
		}
	}
	return IRQ_HANDLED;
}
EXPORT_SYMBOL(mISDNisac_irq);

static int
isac_l1hw(struct mISDNchannel *ch, struct sk_buff *skb)
{
	struct mISDNdevice	*dev = container_of(ch, struct mISDNdevice, D);
	struct dchannel		*dch = container_of(dev, struct dchannel, dev);
	struct isac_hw		*isac = container_of(dch, struct isac_hw, dch);
	int			ret = -EINVAL;
	struct mISDNhead	*hh = mISDN_HEAD_P(skb);
	u32			id;
	u_long			flags;

	switch (hh->prim) {
	case PH_DATA_REQ:
		spin_lock_irqsave(isac->hwlock, flags);
		ret = dchannel_senddata(dch, skb);
		if (ret > 0) { /* direct TX */
			id = hh->id; /* skb can be freed */
			isac_fill_fifo(isac);
			ret = 0;
			spin_unlock_irqrestore(isac->hwlock, flags);
			queue_ch_frame(ch, PH_DATA_CNF, id, NULL);
		} else
			spin_unlock_irqrestore(isac->hwlock, flags);
		return ret;
	case PH_ACTIVATE_REQ:
		ret = l1_event(dch->l1, hh->prim);
		break;
	case PH_DEACTIVATE_REQ:
		test_and_clear_bit(FLG_L2_ACTIVATED, &dch->Flags);
		ret = l1_event(dch->l1, hh->prim);
		break;
	}

	if (!ret)
		dev_kfree_skb(skb);
	return ret;
}

static int
isac_ctrl(struct isac_hw *isac, u32 cmd, u_long para)
{
	u8 tl = 0;
	u_long flags;

	switch (cmd) {
	case HW_TESTLOOP:
		spin_lock_irqsave(isac->hwlock, flags);
		if (!(isac->type & IPAC_TYPE_ISACX)) {
			/* TODO: implement for IPAC_TYPE_ISACX */
			if (para & 1) /* B1 */
				tl |= 0x0c;
			else if (para & 2) /* B2 */
				tl |= 0x3;
			/* we only support IOM2 mode */
			WriteISAC(isac, ISAC_SPCR, tl);
			if (tl)
				WriteISAC(isac, ISAC_ADF1, 0x8);
			else
				WriteISAC(isac, ISAC_ADF1, 0x0);
		}
		spin_unlock_irqrestore(isac->hwlock, flags);
		break;
	default:
		pr_debug("%s: %s unknown command %x %lx\n", isac->name,
<<<<<<< HEAD
			 __func__, cmd, para);
=======
			__func__, cmd, para);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		return -1;
	}
	return 0;
}

static int
isac_l1cmd(struct dchannel *dch, u32 cmd)
{
	struct isac_hw *isac = container_of(dch, struct isac_hw, dch);
	u_long flags;

	pr_debug("%s: cmd(%x) state(%02x)\n", isac->name, cmd, isac->state);
	switch (cmd) {
	case INFO3_P8:
		spin_lock_irqsave(isac->hwlock, flags);
		ph_command(isac, ISAC_CMD_AR8);
		spin_unlock_irqrestore(isac->hwlock, flags);
		break;
	case INFO3_P10:
		spin_lock_irqsave(isac->hwlock, flags);
		ph_command(isac, ISAC_CMD_AR10);
		spin_unlock_irqrestore(isac->hwlock, flags);
		break;
	case HW_RESET_REQ:
		spin_lock_irqsave(isac->hwlock, flags);
		if ((isac->state == ISAC_IND_EI) ||
		    (isac->state == ISAC_IND_DR) ||
		    (isac->state == ISAC_IND_RS))
			ph_command(isac, ISAC_CMD_TIM);
		else
			ph_command(isac, ISAC_CMD_RS);
		spin_unlock_irqrestore(isac->hwlock, flags);
		break;
	case HW_DEACT_REQ:
		skb_queue_purge(&dch->squeue);
		if (dch->tx_skb) {
			dev_kfree_skb(dch->tx_skb);
			dch->tx_skb = NULL;
		}
		dch->tx_idx = 0;
		if (dch->rx_skb) {
			dev_kfree_skb(dch->rx_skb);
			dch->rx_skb = NULL;
		}
		test_and_clear_bit(FLG_TX_BUSY, &dch->Flags);
		if (test_and_clear_bit(FLG_BUSY_TIMER, &dch->Flags))
			del_timer(&dch->timer);
		break;
	case HW_POWERUP_REQ:
		spin_lock_irqsave(isac->hwlock, flags);
		ph_command(isac, ISAC_CMD_TIM);
		spin_unlock_irqrestore(isac->hwlock, flags);
		break;
	case PH_ACTIVATE_IND:
		test_and_set_bit(FLG_ACTIVE, &dch->Flags);
		_queue_data(&dch->dev.D, cmd, MISDN_ID_ANY, 0, NULL,
<<<<<<< HEAD
			    GFP_ATOMIC);
=======
			GFP_ATOMIC);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		break;
	case PH_DEACTIVATE_IND:
		test_and_clear_bit(FLG_ACTIVE, &dch->Flags);
		_queue_data(&dch->dev.D, cmd, MISDN_ID_ANY, 0, NULL,
<<<<<<< HEAD
			    GFP_ATOMIC);
		break;
	default:
		pr_debug("%s: %s unknown command %x\n", isac->name,
			 __func__, cmd);
=======
			GFP_ATOMIC);
		break;
	default:
		pr_debug("%s: %s unknown command %x\n", isac->name,
			__func__, cmd);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		return -1;
	}
	return 0;
}

static void
isac_release(struct isac_hw *isac)
{
	if (isac->type & IPAC_TYPE_ISACX)
		WriteISAC(isac, ISACX_MASK, 0xff);
	else
		WriteISAC(isac, ISAC_MASK, 0xff);
	if (isac->dch.timer.function != NULL) {
		del_timer(&isac->dch.timer);
		isac->dch.timer.function = NULL;
	}
	kfree(isac->mon_rx);
	isac->mon_rx = NULL;
	kfree(isac->mon_tx);
	isac->mon_tx = NULL;
	if (isac->dch.l1)
		l1_event(isac->dch.l1, CLOSE_CHANNEL);
	mISDN_freedchannel(&isac->dch);
}

static void
dbusy_timer_handler(struct isac_hw *isac)
{
	int rbch, star;
	u_long flags;

	if (test_bit(FLG_BUSY_TIMER, &isac->dch.Flags)) {
		spin_lock_irqsave(isac->hwlock, flags);
		rbch = ReadISAC(isac, ISAC_RBCH);
		star = ReadISAC(isac, ISAC_STAR);
		pr_debug("%s: D-Channel Busy RBCH %02x STAR %02x\n",
<<<<<<< HEAD
			 isac->name, rbch, star);
=======
			isac->name, rbch, star);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		if (rbch & ISAC_RBCH_XAC) /* D-Channel Busy */
			test_and_set_bit(FLG_L1_BUSY, &isac->dch.Flags);
		else {
			/* discard frame; reset transceiver */
			test_and_clear_bit(FLG_BUSY_TIMER, &isac->dch.Flags);
			if (isac->dch.tx_idx)
				isac->dch.tx_idx = 0;
			else
				pr_info("%s: ISAC D-Channel Busy no tx_idx\n",
					isac->name);
			/* Transmitter reset */
			WriteISAC(isac, ISAC_CMDR, 0x01);
		}
		spin_unlock_irqrestore(isac->hwlock, flags);
	}
}

static int
open_dchannel(struct isac_hw *isac, struct channel_req *rq)
{
	pr_debug("%s: %s dev(%d) open from %p\n", isac->name, __func__,
<<<<<<< HEAD
		 isac->dch.dev.id, __builtin_return_address(1));
=======
		isac->dch.dev.id, __builtin_return_address(1));
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (rq->protocol != ISDN_P_TE_S0)
		return -EINVAL;
	if (rq->adr.channel == 1)
		/* E-Channel not supported */
		return -EINVAL;
	rq->ch = &isac->dch.dev.D;
	rq->ch->protocol = rq->protocol;
	if (isac->dch.state == 7)
		_queue_data(rq->ch, PH_ACTIVATE_IND, MISDN_ID_ANY,
<<<<<<< HEAD
			    0, NULL, GFP_KERNEL);
=======
		    0, NULL, GFP_KERNEL);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	return 0;
}

static const char *ISACVer[] =
{"2086/2186 V1.1", "2085 B1", "2085 B2",
 "2085 V2.3"};

static int
isac_init(struct isac_hw *isac)
{
	u8 val;
	int err = 0;

	if (!isac->dch.l1) {
		err = create_l1(&isac->dch, isac_l1cmd);
		if (err)
			return err;
	}
	isac->mon_tx = NULL;
	isac->mon_rx = NULL;
	isac->dch.timer.function = (void *) dbusy_timer_handler;
	isac->dch.timer.data = (long)isac;
	init_timer(&isac->dch.timer);
	isac->mocr = 0xaa;
	if (isac->type & IPAC_TYPE_ISACX) {
		/* Disable all IRQ */
		WriteISAC(isac, ISACX_MASK, 0xff);
		val = ReadISAC(isac, ISACX_STARD);
		pr_debug("%s: ISACX STARD %x\n", isac->name, val);
		val = ReadISAC(isac, ISACX_ISTAD);
		pr_debug("%s: ISACX ISTAD %x\n", isac->name, val);
		val = ReadISAC(isac, ISACX_ISTA);
		pr_debug("%s: ISACX ISTA %x\n", isac->name, val);
		/* clear LDD */
		WriteISAC(isac, ISACX_TR_CONF0, 0x00);
		/* enable transmitter */
		WriteISAC(isac, ISACX_TR_CONF2, 0x00);
		/* transparent mode 0, RAC, stop/go */
		WriteISAC(isac, ISACX_MODED, 0xc9);
		/* all HDLC IRQ unmasked */
		val = ReadISAC(isac, ISACX_ID);
		if (isac->dch.debug & DEBUG_HW)
			pr_notice("%s: ISACX Design ID %x\n",
<<<<<<< HEAD
				  isac->name, val & 0x3f);
=======
				isac->name, val & 0x3f);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		val = ReadISAC(isac, ISACX_CIR0);
		pr_debug("%s: ISACX CIR0 %02X\n", isac->name, val);
		isac->state = val >> 4;
		isac_ph_state_change(isac);
		ph_command(isac, ISAC_CMD_RS);
		WriteISAC(isac, ISACX_MASK, IPACX__ON);
		WriteISAC(isac, ISACX_MASKD, 0x00);
	} else { /* old isac */
		WriteISAC(isac, ISAC_MASK, 0xff);
		val = ReadISAC(isac, ISAC_STAR);
		pr_debug("%s: ISAC STAR %x\n", isac->name, val);
		val = ReadISAC(isac, ISAC_MODE);
		pr_debug("%s: ISAC MODE %x\n", isac->name, val);
		val = ReadISAC(isac, ISAC_ADF2);
		pr_debug("%s: ISAC ADF2 %x\n", isac->name, val);
		val = ReadISAC(isac, ISAC_ISTA);
		pr_debug("%s: ISAC ISTA %x\n", isac->name, val);
		if (val & 0x01) {
			val = ReadISAC(isac, ISAC_EXIR);
			pr_debug("%s: ISAC EXIR %x\n", isac->name, val);
		}
		val = ReadISAC(isac, ISAC_RBCH);
		if (isac->dch.debug & DEBUG_HW)
			pr_notice("%s: ISAC version (%x): %s\n", isac->name,
<<<<<<< HEAD
				  val, ISACVer[(val >> 5) & 3]);
=======
				val, ISACVer[(val >> 5) & 3]);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		isac->type |= ((val >> 5) & 3);
		if (!isac->adf2)
			isac->adf2 = 0x80;
		if (!(isac->adf2 & 0x80)) { /* only IOM 2 Mode */
			pr_info("%s: only support IOM2 mode but adf2=%02x\n",
				isac->name, isac->adf2);
			isac_release(isac);
			return -EINVAL;
		}
		WriteISAC(isac, ISAC_ADF2, isac->adf2);
		WriteISAC(isac, ISAC_SQXR, 0x2f);
		WriteISAC(isac, ISAC_SPCR, 0x00);
		WriteISAC(isac, ISAC_STCR, 0x70);
		WriteISAC(isac, ISAC_MODE, 0xc9);
		WriteISAC(isac, ISAC_TIMR, 0x00);
		WriteISAC(isac, ISAC_ADF1, 0x00);
		val = ReadISAC(isac, ISAC_CIR0);
		pr_debug("%s: ISAC CIR0 %x\n", isac->name, val);
		isac->state = (val >> 2) & 0xf;
		isac_ph_state_change(isac);
		ph_command(isac, ISAC_CMD_RS);
		WriteISAC(isac, ISAC_MASK, 0);
	}
	return err;
}

int
mISDNisac_init(struct isac_hw *isac, void *hw)
{
	mISDN_initdchannel(&isac->dch, MAX_DFRAME_LEN_L1, isac_ph_state_bh);
	isac->dch.hw = hw;
	isac->dch.dev.D.send = isac_l1hw;
	isac->init = isac_init;
	isac->release = isac_release;
	isac->ctrl = isac_ctrl;
	isac->open = open_dchannel;
	isac->dch.dev.Dprotocols = (1 << ISDN_P_TE_S0);
	isac->dch.dev.nrbchan = 2;
	return 0;
}
EXPORT_SYMBOL(mISDNisac_init);

static void
waitforCEC(struct hscx_hw *hx)
{
	u8 starb, to = 50;

	while (to) {
		starb = ReadHSCX(hx, IPAC_STARB);
		if (!(starb & 0x04))
			break;
		udelay(1);
		to--;
	}
	if (to < 50)
		pr_debug("%s: B%1d CEC %d us\n", hx->ip->name, hx->bch.nr,
<<<<<<< HEAD
			 50 - to);
=======
			50 - to);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (!to)
		pr_info("%s: B%1d CEC timeout\n", hx->ip->name, hx->bch.nr);
}


static void
waitforXFW(struct hscx_hw *hx)
{
	u8 starb, to = 50;

	while (to) {
		starb = ReadHSCX(hx, IPAC_STARB);
		if ((starb & 0x44) == 0x40)
			break;
		udelay(1);
		to--;
	}
	if (to < 50)
		pr_debug("%s: B%1d XFW %d us\n", hx->ip->name, hx->bch.nr,
<<<<<<< HEAD
			 50 - to);
=======
			50 - to);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (!to)
		pr_info("%s: B%1d XFW timeout\n", hx->ip->name, hx->bch.nr);
}

static void
hscx_cmdr(struct hscx_hw *hx, u8 cmd)
{
	if (hx->ip->type & IPAC_TYPE_IPACX)
		WriteHSCX(hx, IPACX_CMDRB, cmd);
	else {
		waitforCEC(hx);
		WriteHSCX(hx, IPAC_CMDRB, cmd);
	}
}

static void
hscx_empty_fifo(struct hscx_hw *hscx, u8 count)
{
	u8 *p;

	pr_debug("%s: B%1d %d\n", hscx->ip->name, hscx->bch.nr, count);
	if (!hscx->bch.rx_skb) {
		hscx->bch.rx_skb = mI_alloc_skb(hscx->bch.maxlen, GFP_ATOMIC);
		if (!hscx->bch.rx_skb) {
			pr_info("%s: B receive out of memory\n",
				hscx->ip->name);
			hscx_cmdr(hscx, 0x80); /* RMC */
			return;
		}
	}
	if ((hscx->bch.rx_skb->len + count) > hscx->bch.maxlen) {
		pr_debug("%s: overrun %d\n", hscx->ip->name,
<<<<<<< HEAD
			 hscx->bch.rx_skb->len + count);
=======
			hscx->bch.rx_skb->len + count);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		skb_trim(hscx->bch.rx_skb, 0);
		hscx_cmdr(hscx, 0x80); /* RMC */
		return;
	}
	p = skb_put(hscx->bch.rx_skb, count);

	if (hscx->ip->type & IPAC_TYPE_IPACX)
		hscx->ip->read_fifo(hscx->ip->hw,
<<<<<<< HEAD
				    hscx->off + IPACX_RFIFOB, p, count);
	else
		hscx->ip->read_fifo(hscx->ip->hw,
				    hscx->off, p, count);
=======
			hscx->off + IPACX_RFIFOB, p, count);
	else
		hscx->ip->read_fifo(hscx->ip->hw,
			hscx->off, p, count);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	hscx_cmdr(hscx, 0x80); /* RMC */

	if (hscx->bch.debug & DEBUG_HW_BFIFO) {
		snprintf(hscx->log, 64, "B%1d-recv %s %d ",
<<<<<<< HEAD
			 hscx->bch.nr, hscx->ip->name, count);
=======
			hscx->bch.nr, hscx->ip->name, count);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		print_hex_dump_bytes(hscx->log, DUMP_PREFIX_OFFSET, p, count);
	}
}

static void
hscx_fill_fifo(struct hscx_hw *hscx)
{
	int count, more;
	u8 *p;

	if (!hscx->bch.tx_skb)
		return;
	count = hscx->bch.tx_skb->len - hscx->bch.tx_idx;
	if (count <= 0)
		return;
	p = hscx->bch.tx_skb->data + hscx->bch.tx_idx;

	more = test_bit(FLG_TRANSPARENT, &hscx->bch.Flags) ? 1 : 0;
	if (count > hscx->fifo_size) {
		count = hscx->fifo_size;
		more = 1;
	}
	pr_debug("%s: B%1d %d/%d/%d\n", hscx->ip->name, hscx->bch.nr, count,
<<<<<<< HEAD
		 hscx->bch.tx_idx, hscx->bch.tx_skb->len);
=======
		hscx->bch.tx_idx, hscx->bch.tx_skb->len);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	hscx->bch.tx_idx += count;

	if (hscx->ip->type & IPAC_TYPE_IPACX)
		hscx->ip->write_fifo(hscx->ip->hw,
<<<<<<< HEAD
				     hscx->off + IPACX_XFIFOB, p, count);
	else {
		waitforXFW(hscx);
		hscx->ip->write_fifo(hscx->ip->hw,
				     hscx->off, p, count);
=======
			hscx->off + IPACX_XFIFOB, p, count);
	else {
		waitforXFW(hscx);
		hscx->ip->write_fifo(hscx->ip->hw,
			hscx->off, p, count);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}
	hscx_cmdr(hscx, more ? 0x08 : 0x0a);

	if (hscx->bch.debug & DEBUG_HW_BFIFO) {
		snprintf(hscx->log, 64, "B%1d-send %s %d ",
<<<<<<< HEAD
			 hscx->bch.nr, hscx->ip->name, count);
=======
			hscx->bch.nr, hscx->ip->name, count);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		print_hex_dump_bytes(hscx->log, DUMP_PREFIX_OFFSET, p, count);
	}
}

static void
hscx_xpr(struct hscx_hw *hx)
{
	if (hx->bch.tx_skb && hx->bch.tx_idx < hx->bch.tx_skb->len)
		hscx_fill_fifo(hx);
	else {
		if (hx->bch.tx_skb) {
			/* send confirm, on trans, free on hdlc. */
			if (test_bit(FLG_TRANSPARENT, &hx->bch.Flags))
				confirm_Bsend(&hx->bch);
			dev_kfree_skb(hx->bch.tx_skb);
		}
		if (get_next_bframe(&hx->bch))
			hscx_fill_fifo(hx);
	}
}

static void
ipac_rme(struct hscx_hw *hx)
{
	int count;
	u8 rstab;

	if (hx->ip->type & IPAC_TYPE_IPACX)
		rstab = ReadHSCX(hx, IPACX_RSTAB);
	else
		rstab = ReadHSCX(hx, IPAC_RSTAB);
	pr_debug("%s: B%1d RSTAB %02x\n", hx->ip->name, hx->bch.nr, rstab);
	if ((rstab & 0xf0) != 0xa0) {
		/* !(VFR && !RDO && CRC && !RAB) */
		if (!(rstab & 0x80)) {
			if (hx->bch.debug & DEBUG_HW_BCHANNEL)
				pr_notice("%s: B%1d invalid frame\n",
<<<<<<< HEAD
					  hx->ip->name, hx->bch.nr);
=======
					hx->ip->name, hx->bch.nr);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		}
		if (rstab & 0x40) {
			if (hx->bch.debug & DEBUG_HW_BCHANNEL)
				pr_notice("%s: B%1d RDO proto=%x\n",
<<<<<<< HEAD
					  hx->ip->name, hx->bch.nr,
					  hx->bch.state);
=======
					hx->ip->name, hx->bch.nr,
					hx->bch.state);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		}
		if (!(rstab & 0x20)) {
			if (hx->bch.debug & DEBUG_HW_BCHANNEL)
				pr_notice("%s: B%1d CRC error\n",
<<<<<<< HEAD
					  hx->ip->name, hx->bch.nr);
=======
					hx->ip->name, hx->bch.nr);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		}
		hscx_cmdr(hx, 0x80); /* Do RMC */
		return;
	}
	if (hx->ip->type & IPAC_TYPE_IPACX)
		count = ReadHSCX(hx, IPACX_RBCLB);
	else
		count = ReadHSCX(hx, IPAC_RBCLB);
	count &= (hx->fifo_size - 1);
	if (count == 0)
		count = hx->fifo_size;
	hscx_empty_fifo(hx, count);
	if (!hx->bch.rx_skb)
		return;
	if (hx->bch.rx_skb->len < 2) {
		pr_debug("%s: B%1d frame to short %d\n",
<<<<<<< HEAD
			 hx->ip->name, hx->bch.nr, hx->bch.rx_skb->len);
=======
			hx->ip->name, hx->bch.nr, hx->bch.rx_skb->len);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		skb_trim(hx->bch.rx_skb, 0);
	} else {
		skb_trim(hx->bch.rx_skb, hx->bch.rx_skb->len - 1);
		recv_Bchannel(&hx->bch, 0);
	}
}

static void
ipac_irq(struct hscx_hw *hx, u8 ista)
{
	u8 istab, m, exirb = 0;

	if (hx->ip->type & IPAC_TYPE_IPACX)
		istab = ReadHSCX(hx, IPACX_ISTAB);
	else if (hx->ip->type & IPAC_TYPE_IPAC) {
		istab = ReadHSCX(hx, IPAC_ISTAB);
		m = (hx->bch.nr & 1) ? IPAC__EXA : IPAC__EXB;
		if (m & ista) {
			exirb = ReadHSCX(hx, IPAC_EXIRB);
			pr_debug("%s: B%1d EXIRB %02x\n", hx->ip->name,
<<<<<<< HEAD
				 hx->bch.nr, exirb);
=======
				hx->bch.nr, exirb);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		}
	} else if (hx->bch.nr & 2) { /* HSCX B */
		if (ista & (HSCX__EXA | HSCX__ICA))
			ipac_irq(&hx->ip->hscx[0], ista);
		if (ista & HSCX__EXB) {
			exirb = ReadHSCX(hx, IPAC_EXIRB);
			pr_debug("%s: B%1d EXIRB %02x\n", hx->ip->name,
<<<<<<< HEAD
				 hx->bch.nr, exirb);
=======
				hx->bch.nr, exirb);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		}
		istab = ista & 0xF8;
	} else { /* HSCX A */
		istab = ReadHSCX(hx, IPAC_ISTAB);
		if (ista & HSCX__EXA) {
			exirb = ReadHSCX(hx, IPAC_EXIRB);
			pr_debug("%s: B%1d EXIRB %02x\n", hx->ip->name,
<<<<<<< HEAD
				 hx->bch.nr, exirb);
=======
				hx->bch.nr, exirb);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		}
		istab = istab & 0xF8;
	}
	if (exirb & IPAC_B_XDU)
		istab |= IPACX_B_XDU;
	if (exirb & IPAC_B_RFO)
		istab |= IPACX_B_RFO;
	pr_debug("%s: B%1d ISTAB %02x\n", hx->ip->name, hx->bch.nr, istab);

	if (!test_bit(FLG_ACTIVE, &hx->bch.Flags))
		return;

	if (istab & IPACX_B_RME)
		ipac_rme(hx);

	if (istab & IPACX_B_RPF) {
		hscx_empty_fifo(hx, hx->fifo_size);
		if (test_bit(FLG_TRANSPARENT, &hx->bch.Flags)) {
			/* receive transparent audio data */
			if (hx->bch.rx_skb)
				recv_Bchannel(&hx->bch, 0);
		}
	}

	if (istab & IPACX_B_RFO) {
		pr_debug("%s: B%1d RFO error\n", hx->ip->name, hx->bch.nr);
		hscx_cmdr(hx, 0x40);	/* RRES */
	}

	if (istab & IPACX_B_XPR)
		hscx_xpr(hx);

	if (istab & IPACX_B_XDU) {
		if (test_bit(FLG_TRANSPARENT, &hx->bch.Flags)) {
			hscx_fill_fifo(hx);
			return;
		}
		pr_debug("%s: B%1d XDU error at len %d\n", hx->ip->name,
<<<<<<< HEAD
			 hx->bch.nr, hx->bch.tx_idx);
=======
			hx->bch.nr, hx->bch.tx_idx);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		hx->bch.tx_idx = 0;
		hscx_cmdr(hx, 0x01);	/* XRES */
	}
}

irqreturn_t
mISDNipac_irq(struct ipac_hw *ipac, int maxloop)
{
	int cnt = maxloop + 1;
	u8 ista, istad;
	struct isac_hw  *isac = &ipac->isac;

	if (ipac->type & IPAC_TYPE_IPACX) {
		ista = ReadIPAC(ipac, ISACX_ISTA);
		while (ista && cnt--) {
			pr_debug("%s: ISTA %02x\n", ipac->name, ista);
			if (ista & IPACX__ICA)
				ipac_irq(&ipac->hscx[0], ista);
			if (ista & IPACX__ICB)
				ipac_irq(&ipac->hscx[1], ista);
			if (ista & (ISACX__ICD | ISACX__CIC))
				mISDNisac_irq(&ipac->isac, ista);
			ista = ReadIPAC(ipac, ISACX_ISTA);
		}
	} else if (ipac->type & IPAC_TYPE_IPAC) {
		ista = ReadIPAC(ipac, IPAC_ISTA);
		while (ista && cnt--) {
			pr_debug("%s: ISTA %02x\n", ipac->name, ista);
			if (ista & (IPAC__ICD | IPAC__EXD)) {
				istad = ReadISAC(isac, ISAC_ISTA);
				pr_debug("%s: ISTAD %02x\n", ipac->name, istad);
				if (istad & IPAC_D_TIN2)
					pr_debug("%s TIN2 irq\n", ipac->name);
				if (ista & IPAC__EXD)
					istad |= 1; /* ISAC EXI */
				mISDNisac_irq(isac, istad);
			}
			if (ista & (IPAC__ICA | IPAC__EXA))
				ipac_irq(&ipac->hscx[0], ista);
			if (ista & (IPAC__ICB | IPAC__EXB))
				ipac_irq(&ipac->hscx[1], ista);
			ista = ReadIPAC(ipac, IPAC_ISTA);
		}
	} else if (ipac->type & IPAC_TYPE_HSCX) {
		while (cnt) {
			ista = ReadIPAC(ipac, IPAC_ISTAB + ipac->hscx[1].off);
			pr_debug("%s: B2 ISTA %02x\n", ipac->name, ista);
			if (ista)
				ipac_irq(&ipac->hscx[1], ista);
			istad = ReadISAC(isac, ISAC_ISTA);
			pr_debug("%s: ISTAD %02x\n", ipac->name, istad);
			if (istad)
				mISDNisac_irq(isac, istad);
			if (0 == (ista | istad))
				break;
			cnt--;
		}
	}
	if (cnt > maxloop) /* only for ISAC/HSCX without PCI IRQ test */
		return IRQ_NONE;
	if (cnt < maxloop)
		pr_debug("%s: %d irqloops cpu%d\n", ipac->name,
<<<<<<< HEAD
			 maxloop - cnt, smp_processor_id());
	if (maxloop && !cnt)
		pr_notice("%s: %d IRQ LOOP cpu%d\n", ipac->name,
			  maxloop, smp_processor_id());
=======
			maxloop - cnt, smp_processor_id());
	if (maxloop && !cnt)
		pr_notice("%s: %d IRQ LOOP cpu%d\n", ipac->name,
			maxloop, smp_processor_id());
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	return IRQ_HANDLED;
}
EXPORT_SYMBOL(mISDNipac_irq);

static int
hscx_mode(struct hscx_hw *hscx, u32 bprotocol)
{
	pr_debug("%s: HSCX %c protocol %x-->%x ch %d\n", hscx->ip->name,
<<<<<<< HEAD
		 '@' + hscx->bch.nr, hscx->bch.state, bprotocol, hscx->bch.nr);
=======
		'@' + hscx->bch.nr, hscx->bch.state, bprotocol, hscx->bch.nr);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (hscx->ip->type & IPAC_TYPE_IPACX) {
		if (hscx->bch.nr & 1) { /* B1 and ICA */
			WriteIPAC(hscx->ip, ISACX_BCHA_TSDP_BC1, 0x80);
			WriteIPAC(hscx->ip, ISACX_BCHA_CR, 0x88);
		} else { /* B2 and ICB */
			WriteIPAC(hscx->ip, ISACX_BCHB_TSDP_BC1, 0x81);
			WriteIPAC(hscx->ip, ISACX_BCHB_CR, 0x88);
		}
		switch (bprotocol) {
		case ISDN_P_NONE: /* init */
			WriteHSCX(hscx, IPACX_MODEB, 0xC0);	/* rec off */
			WriteHSCX(hscx, IPACX_EXMB,  0x30);	/* std adj. */
			WriteHSCX(hscx, IPACX_MASKB, 0xFF);	/* ints off */
			hscx_cmdr(hscx, 0x41);
			test_and_clear_bit(FLG_HDLC, &hscx->bch.Flags);
			test_and_clear_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			break;
		case ISDN_P_B_RAW:
			WriteHSCX(hscx, IPACX_MODEB, 0x88);	/* ex trans */
			WriteHSCX(hscx, IPACX_EXMB,  0x00);	/* trans */
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPACX_MASKB, IPACX_B_ON);
			test_and_set_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			break;
		case ISDN_P_B_HDLC:
			WriteHSCX(hscx, IPACX_MODEB, 0xC0);	/* trans */
			WriteHSCX(hscx, IPACX_EXMB,  0x00);	/* hdlc,crc */
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPACX_MASKB, IPACX_B_ON);
			test_and_set_bit(FLG_HDLC, &hscx->bch.Flags);
			break;
		default:
			pr_info("%s: protocol not known %x\n", hscx->ip->name,
				bprotocol);
			return -ENOPROTOOPT;
		}
	} else if (hscx->ip->type & IPAC_TYPE_IPAC) { /* IPAC */
		WriteHSCX(hscx, IPAC_CCR1, 0x82);
		WriteHSCX(hscx, IPAC_CCR2, 0x30);
		WriteHSCX(hscx, IPAC_XCCR, 0x07);
		WriteHSCX(hscx, IPAC_RCCR, 0x07);
		WriteHSCX(hscx, IPAC_TSAX, hscx->slot);
		WriteHSCX(hscx, IPAC_TSAR, hscx->slot);
		switch (bprotocol) {
		case ISDN_P_NONE:
			WriteHSCX(hscx, IPAC_TSAX, 0x1F);
			WriteHSCX(hscx, IPAC_TSAR, 0x1F);
			WriteHSCX(hscx, IPAC_MODEB, 0x84);
			WriteHSCX(hscx, IPAC_CCR1, 0x82);
			WriteHSCX(hscx, IPAC_MASKB, 0xFF);	/* ints off */
			test_and_clear_bit(FLG_HDLC, &hscx->bch.Flags);
			test_and_clear_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			break;
		case ISDN_P_B_RAW:
			WriteHSCX(hscx, IPAC_MODEB, 0xe4);	/* ex trans */
			WriteHSCX(hscx, IPAC_CCR1, 0x82);
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPAC_MASKB, 0);
			test_and_set_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			break;
		case ISDN_P_B_HDLC:
			WriteHSCX(hscx, IPAC_MODEB, 0x8c);
			WriteHSCX(hscx, IPAC_CCR1, 0x8a);
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPAC_MASKB, 0);
			test_and_set_bit(FLG_HDLC, &hscx->bch.Flags);
			break;
		default:
			pr_info("%s: protocol not known %x\n", hscx->ip->name,
				bprotocol);
			return -ENOPROTOOPT;
		}
	} else if (hscx->ip->type & IPAC_TYPE_HSCX) { /* HSCX */
		WriteHSCX(hscx, IPAC_CCR1, 0x85);
		WriteHSCX(hscx, IPAC_CCR2, 0x30);
		WriteHSCX(hscx, IPAC_XCCR, 0x07);
		WriteHSCX(hscx, IPAC_RCCR, 0x07);
		WriteHSCX(hscx, IPAC_TSAX, hscx->slot);
		WriteHSCX(hscx, IPAC_TSAR, hscx->slot);
		switch (bprotocol) {
		case ISDN_P_NONE:
			WriteHSCX(hscx, IPAC_TSAX, 0x1F);
			WriteHSCX(hscx, IPAC_TSAR, 0x1F);
			WriteHSCX(hscx, IPAC_MODEB, 0x84);
			WriteHSCX(hscx, IPAC_CCR1, 0x85);
			WriteHSCX(hscx, IPAC_MASKB, 0xFF);	/* ints off */
			test_and_clear_bit(FLG_HDLC, &hscx->bch.Flags);
			test_and_clear_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			break;
		case ISDN_P_B_RAW:
			WriteHSCX(hscx, IPAC_MODEB, 0xe4);	/* ex trans */
			WriteHSCX(hscx, IPAC_CCR1, 0x85);
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPAC_MASKB, 0);
			test_and_set_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			break;
		case ISDN_P_B_HDLC:
			WriteHSCX(hscx, IPAC_MODEB, 0x8c);
			WriteHSCX(hscx, IPAC_CCR1, 0x8d);
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPAC_MASKB, 0);
			test_and_set_bit(FLG_HDLC, &hscx->bch.Flags);
			break;
		default:
			pr_info("%s: protocol not known %x\n", hscx->ip->name,
				bprotocol);
			return -ENOPROTOOPT;
		}
	} else
		return -EINVAL;
	hscx->bch.state = bprotocol;
	return 0;
}

static int
hscx_l2l1(struct mISDNchannel *ch, struct sk_buff *skb)
{
	struct bchannel *bch = container_of(ch, struct bchannel, ch);
	struct hscx_hw	*hx = container_of(bch, struct hscx_hw, bch);
	int ret = -EINVAL;
	struct mISDNhead *hh = mISDN_HEAD_P(skb);
	u32 id;
	u_long flags;

	switch (hh->prim) {
	case PH_DATA_REQ:
		spin_lock_irqsave(hx->ip->hwlock, flags);
		ret = bchannel_senddata(bch, skb);
		if (ret > 0) { /* direct TX */
			id = hh->id; /* skb can be freed */
			ret = 0;
			hscx_fill_fifo(hx);
			spin_unlock_irqrestore(hx->ip->hwlock, flags);
			if (!test_bit(FLG_TRANSPARENT, &bch->Flags))
				queue_ch_frame(ch, PH_DATA_CNF, id, NULL);
		} else
			spin_unlock_irqrestore(hx->ip->hwlock, flags);
		return ret;
	case PH_ACTIVATE_REQ:
		spin_lock_irqsave(hx->ip->hwlock, flags);
		if (!test_and_set_bit(FLG_ACTIVE, &bch->Flags))
			ret = hscx_mode(hx, ch->protocol);
		else
			ret = 0;
		spin_unlock_irqrestore(hx->ip->hwlock, flags);
		if (!ret)
			_queue_data(ch, PH_ACTIVATE_IND, MISDN_ID_ANY, 0,
<<<<<<< HEAD
				    NULL, GFP_KERNEL);
=======
				NULL, GFP_KERNEL);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		break;
	case PH_DEACTIVATE_REQ:
		spin_lock_irqsave(hx->ip->hwlock, flags);
		mISDN_clear_bchannel(bch);
		hscx_mode(hx, ISDN_P_NONE);
		spin_unlock_irqrestore(hx->ip->hwlock, flags);
		_queue_data(ch, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
<<<<<<< HEAD
			    NULL, GFP_KERNEL);
=======
			NULL, GFP_KERNEL);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		ret = 0;
		break;
	default:
		pr_info("%s: %s unknown prim(%x,%x)\n",
			hx->ip->name, __func__, hh->prim, hh->id);
		ret = -EINVAL;
	}
	if (!ret)
		dev_kfree_skb(skb);
	return ret;
}

static int
channel_bctrl(struct bchannel *bch, struct mISDN_ctrl_req *cq)
{
	int	ret = 0;

	switch (cq->op) {
	case MISDN_CTRL_GETOP:
		cq->op = 0;
		break;
<<<<<<< HEAD
		/* Nothing implemented yet */
=======
	/* Nothing implemented yet */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	case MISDN_CTRL_FILL_EMPTY:
	default:
		pr_info("%s: unknown Op %x\n", __func__, cq->op);
		ret = -EINVAL;
		break;
	}
	return ret;
}

static int
hscx_bctrl(struct mISDNchannel *ch, u32 cmd, void *arg)
{
	struct bchannel *bch = container_of(ch, struct bchannel, ch);
	struct hscx_hw	*hx = container_of(bch, struct hscx_hw, bch);
	int ret = -EINVAL;
	u_long flags;

	pr_debug("%s: %s cmd:%x %p\n", hx->ip->name, __func__, cmd, arg);
	switch (cmd) {
	case CLOSE_CHANNEL:
		test_and_clear_bit(FLG_OPEN, &bch->Flags);
		if (test_bit(FLG_ACTIVE, &bch->Flags)) {
			spin_lock_irqsave(hx->ip->hwlock, flags);
			mISDN_freebchannel(bch);
			hscx_mode(hx, ISDN_P_NONE);
			spin_unlock_irqrestore(hx->ip->hwlock, flags);
		} else {
			skb_queue_purge(&bch->rqueue);
			bch->rcount = 0;
		}
		ch->protocol = ISDN_P_NONE;
		ch->peer = NULL;
		module_put(hx->ip->owner);
		ret = 0;
		break;
	case CONTROL_CHANNEL:
		ret = channel_bctrl(bch, arg);
		break;
	default:
		pr_info("%s: %s unknown prim(%x)\n",
			hx->ip->name, __func__, cmd);
	}
	return ret;
}

static void
free_ipac(struct ipac_hw *ipac)
{
	isac_release(&ipac->isac);
}

static const char *HSCXVer[] =
{"A1", "?1", "A2", "?3", "A3", "V2.1", "?6", "?7",
 "?8", "?9", "?10", "?11", "?12", "?13", "?14", "???"};



static void
hscx_init(struct hscx_hw *hx)
{
	u8 val;

	WriteHSCX(hx, IPAC_RAH2, 0xFF);
	WriteHSCX(hx, IPAC_XBCH, 0x00);
	WriteHSCX(hx, IPAC_RLCR, 0x00);

	if (hx->ip->type & IPAC_TYPE_HSCX) {
		WriteHSCX(hx, IPAC_CCR1, 0x85);
		val = ReadHSCX(hx, HSCX_VSTR);
		pr_debug("%s: HSCX VSTR %02x\n", hx->ip->name, val);
		if (hx->bch.debug & DEBUG_HW)
			pr_notice("%s: HSCX version %s\n", hx->ip->name,
<<<<<<< HEAD
				  HSCXVer[val & 0x0f]);
=======
				HSCXVer[val & 0x0f]);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	} else
		WriteHSCX(hx, IPAC_CCR1, 0x82);
	WriteHSCX(hx, IPAC_CCR2, 0x30);
	WriteHSCX(hx, IPAC_XCCR, 0x07);
	WriteHSCX(hx, IPAC_RCCR, 0x07);
}

static int
ipac_init(struct ipac_hw *ipac)
{
	u8 val;

	if (ipac->type & IPAC_TYPE_HSCX) {
		hscx_init(&ipac->hscx[0]);
		hscx_init(&ipac->hscx[1]);
		val = ReadIPAC(ipac, IPAC_ID);
	} else if (ipac->type & IPAC_TYPE_IPAC) {
		hscx_init(&ipac->hscx[0]);
		hscx_init(&ipac->hscx[1]);
		WriteIPAC(ipac, IPAC_MASK, IPAC__ON);
		val = ReadIPAC(ipac, IPAC_CONF);
		/* conf is default 0, but can be overwritten by card setup */
		pr_debug("%s: IPAC CONF %02x/%02x\n", ipac->name,
<<<<<<< HEAD
			 val, ipac->conf);
=======
			val, ipac->conf);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		WriteIPAC(ipac, IPAC_CONF, ipac->conf);
		val = ReadIPAC(ipac, IPAC_ID);
		if (ipac->hscx[0].bch.debug & DEBUG_HW)
			pr_notice("%s: IPAC Design ID %02x\n", ipac->name, val);
	}
	/* nothing special for IPACX to do here */
	return isac_init(&ipac->isac);
}

static int
open_bchannel(struct ipac_hw *ipac, struct channel_req *rq)
{
	struct bchannel		*bch;

<<<<<<< HEAD
	if (rq->adr.channel == 0 || rq->adr.channel > 2)
=======
	if (rq->adr.channel > 2)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		return -EINVAL;
	if (rq->protocol == ISDN_P_NONE)
		return -EINVAL;
	bch = &ipac->hscx[rq->adr.channel - 1].bch;
	if (test_and_set_bit(FLG_OPEN, &bch->Flags))
		return -EBUSY; /* b-channel can be only open once */
	test_and_clear_bit(FLG_FILLEMPTY, &bch->Flags);
	bch->ch.protocol = rq->protocol;
	rq->ch = &bch->ch;
	return 0;
}

static int
channel_ctrl(struct ipac_hw *ipac, struct mISDN_ctrl_req *cq)
{
	int	ret = 0;

	switch (cq->op) {
	case MISDN_CTRL_GETOP:
		cq->op = MISDN_CTRL_LOOP;
		break;
	case MISDN_CTRL_LOOP:
		/* cq->channel: 0 disable, 1 B1 loop 2 B2 loop, 3 both */
		if (cq->channel < 0 || cq->channel > 3) {
			ret = -EINVAL;
			break;
		}
		ret = ipac->ctrl(ipac, HW_TESTLOOP, cq->channel);
		break;
	default:
		pr_info("%s: unknown CTRL OP %x\n", ipac->name, cq->op);
		ret = -EINVAL;
		break;
	}
	return ret;
}

static int
ipac_dctrl(struct mISDNchannel *ch, u32 cmd, void *arg)
{
	struct mISDNdevice *dev = container_of(ch, struct mISDNdevice, D);
	struct dchannel *dch = container_of(dev, struct dchannel, dev);
	struct isac_hw *isac = container_of(dch, struct isac_hw, dch);
	struct ipac_hw *ipac = container_of(isac, struct ipac_hw, isac);
	struct channel_req *rq;
	int err = 0;

	pr_debug("%s: DCTRL: %x %p\n", ipac->name, cmd, arg);
	switch (cmd) {
	case OPEN_CHANNEL:
		rq = arg;
		if (rq->protocol == ISDN_P_TE_S0)
			err = open_dchannel(isac, rq);
		else
			err = open_bchannel(ipac, rq);
		if (err)
			break;
		if (!try_module_get(ipac->owner))
			pr_info("%s: cannot get module\n", ipac->name);
		break;
	case CLOSE_CHANNEL:
		pr_debug("%s: dev(%d) close from %p\n", ipac->name,
<<<<<<< HEAD
			 dch->dev.id, __builtin_return_address(0));
=======
			dch->dev.id, __builtin_return_address(0));
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		module_put(ipac->owner);
		break;
	case CONTROL_CHANNEL:
		err = channel_ctrl(ipac, arg);
		break;
	default:
		pr_debug("%s: unknown DCTRL command %x\n", ipac->name, cmd);
		return -EINVAL;
	}
	return err;
}

u32
mISDNipac_init(struct ipac_hw *ipac, void *hw)
{
	u32 ret;
	u8 i;

	ipac->hw = hw;
	if (ipac->isac.dch.debug & DEBUG_HW)
		pr_notice("%s: ipac type %x\n", ipac->name, ipac->type);
	if (ipac->type & IPAC_TYPE_HSCX) {
		ipac->isac.type = IPAC_TYPE_ISAC;
		ipac->hscx[0].off = 0;
		ipac->hscx[1].off = 0x40;
		ipac->hscx[0].fifo_size = 32;
		ipac->hscx[1].fifo_size = 32;
	} else if (ipac->type & IPAC_TYPE_IPAC) {
		ipac->isac.type = IPAC_TYPE_IPAC | IPAC_TYPE_ISAC;
		ipac->hscx[0].off = 0;
		ipac->hscx[1].off = 0x40;
		ipac->hscx[0].fifo_size = 64;
		ipac->hscx[1].fifo_size = 64;
	} else if (ipac->type & IPAC_TYPE_IPACX) {
		ipac->isac.type = IPAC_TYPE_IPACX | IPAC_TYPE_ISACX;
		ipac->hscx[0].off = IPACX_OFF_ICA;
		ipac->hscx[1].off = IPACX_OFF_ICB;
		ipac->hscx[0].fifo_size = 64;
		ipac->hscx[1].fifo_size = 64;
	} else
		return 0;

	mISDNisac_init(&ipac->isac, hw);

	ipac->isac.dch.dev.D.ctrl = ipac_dctrl;

	for (i = 0; i < 2; i++) {
		ipac->hscx[i].bch.nr = i + 1;
		set_channelmap(i + 1, ipac->isac.dch.dev.channelmap);
		list_add(&ipac->hscx[i].bch.ch.list,
<<<<<<< HEAD
			 &ipac->isac.dch.dev.bchannels);
=======
			&ipac->isac.dch.dev.bchannels);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		mISDN_initbchannel(&ipac->hscx[i].bch, MAX_DATA_MEM);
		ipac->hscx[i].bch.ch.nr = i + 1;
		ipac->hscx[i].bch.ch.send = &hscx_l2l1;
		ipac->hscx[i].bch.ch.ctrl = hscx_bctrl;
		ipac->hscx[i].bch.hw = hw;
		ipac->hscx[i].ip = ipac;
		/* default values for IOM time slots
		 * can be overwriten by card */
		ipac->hscx[i].slot = (i == 0) ? 0x2f : 0x03;
	}

	ipac->init = ipac_init;
	ipac->release = free_ipac;

	ret =	(1 << (ISDN_P_B_RAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDLC & ISDN_P_B_MASK));
	return ret;
}
EXPORT_SYMBOL(mISDNipac_init);

static int __init
isac_mod_init(void)
{
	pr_notice("mISDNipac module version %s\n", ISAC_REV);
	return 0;
}

static void __exit
isac_mod_cleanup(void)
{
	pr_notice("mISDNipac module unloaded\n");
}
module_init(isac_mod_init);
module_exit(isac_mod_cleanup);
