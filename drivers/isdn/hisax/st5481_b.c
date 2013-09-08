/*
 * Driver for ST5481 USB ISDN modem
 *
 * Author       Frode Isaksen
 * Copyright    2001 by Frode Isaksen      <fisaksen@bewan.com>
 *              2001 by Kai Germaschewski  <kai.germaschewski@gmx.de>
<<<<<<< HEAD
 *
=======
 * 
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#include <linux/init.h>
#include <linux/gfp.h>
#include <linux/usb.h>
#include <linux/netdevice.h>
#include <linux/bitrev.h>
#include "st5481.h"

static inline void B_L1L2(struct st5481_bcs *bcs, int pr, void *arg)
{
	struct hisax_if *ifc = (struct hisax_if *) &bcs->b_if;

	ifc->l1l2(ifc, pr, arg);
}

/*
 * Encode and transmit next frame.
 */
<<<<<<< HEAD
static void usb_b_out(struct st5481_bcs *bcs, int buf_nr)
=======
static void usb_b_out(struct st5481_bcs *bcs,int buf_nr)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	struct st5481_b_out *b_out = &bcs->b_out;
	struct st5481_adapter *adapter = bcs->adapter;
	struct urb *urb;
<<<<<<< HEAD
	unsigned int packet_size, offset;
	int len, buf_size, bytes_sent;
	int i;
	struct sk_buff *skb;

	if (test_and_set_bit(buf_nr, &b_out->busy)) {
		DBG(4, "ep %d urb %d busy", (bcs->channel + 1) * 2, buf_nr);
=======
	unsigned int packet_size,offset;
	int len,buf_size,bytes_sent;
	int i;
	struct sk_buff *skb;
	
	if (test_and_set_bit(buf_nr, &b_out->busy)) {
		DBG(4,"ep %d urb %d busy",(bcs->channel+1)*2,buf_nr);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		return;
	}
	urb = b_out->urb[buf_nr];

	// Adjust isoc buffer size according to flow state
<<<<<<< HEAD
	if (b_out->flow_event & (OUT_DOWN | OUT_UNDERRUN)) {
		buf_size = NUM_ISO_PACKETS_B * SIZE_ISO_PACKETS_B_OUT + B_FLOW_ADJUST;
		packet_size = SIZE_ISO_PACKETS_B_OUT + B_FLOW_ADJUST;
		DBG(4, "B%d,adjust flow,add %d bytes", bcs->channel + 1, B_FLOW_ADJUST);
	} else if (b_out->flow_event & OUT_UP) {
		buf_size = NUM_ISO_PACKETS_B * SIZE_ISO_PACKETS_B_OUT - B_FLOW_ADJUST;
		packet_size = SIZE_ISO_PACKETS_B_OUT - B_FLOW_ADJUST;
		DBG(4, "B%d,adjust flow,remove %d bytes", bcs->channel + 1, B_FLOW_ADJUST);
	} else {
		buf_size = NUM_ISO_PACKETS_B * SIZE_ISO_PACKETS_B_OUT;
=======
	if(b_out->flow_event & (OUT_DOWN | OUT_UNDERRUN)) {
		buf_size = NUM_ISO_PACKETS_B*SIZE_ISO_PACKETS_B_OUT + B_FLOW_ADJUST;
		packet_size = SIZE_ISO_PACKETS_B_OUT + B_FLOW_ADJUST;
		DBG(4,"B%d,adjust flow,add %d bytes",bcs->channel+1,B_FLOW_ADJUST);
	} else if(b_out->flow_event & OUT_UP){
		buf_size = NUM_ISO_PACKETS_B*SIZE_ISO_PACKETS_B_OUT - B_FLOW_ADJUST;
		packet_size = SIZE_ISO_PACKETS_B_OUT - B_FLOW_ADJUST;
		DBG(4,"B%d,adjust flow,remove %d bytes",bcs->channel+1,B_FLOW_ADJUST);
	} else {
		buf_size = NUM_ISO_PACKETS_B*SIZE_ISO_PACKETS_B_OUT;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		packet_size = 8;
	}
	b_out->flow_event = 0;

	len = 0;
	while (len < buf_size) {
		if ((skb = b_out->tx_skb)) {
			DBG_SKB(0x100, skb);
<<<<<<< HEAD
			DBG(4, "B%d,len=%d", bcs->channel + 1, skb->len);

			if (bcs->mode == L1_MODE_TRANS) {
=======
			DBG(4,"B%d,len=%d",bcs->channel+1,skb->len);
			
			if (bcs->mode == L1_MODE_TRANS) {	
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
				bytes_sent = buf_size - len;
				if (skb->len < bytes_sent)
					bytes_sent = skb->len;
				{	/* swap tx bytes to get hearable audio data */
					register unsigned char *src  = skb->data;
<<<<<<< HEAD
					register unsigned char *dest = urb->transfer_buffer + len;
=======
					register unsigned char *dest = urb->transfer_buffer+len;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
					register unsigned int count;
					for (count = 0; count < bytes_sent; count++)
						*dest++ = bitrev8(*src++);
				}
				len += bytes_sent;
			} else {
				len += isdnhdlc_encode(&b_out->hdlc_state,
						       skb->data, skb->len, &bytes_sent,
<<<<<<< HEAD
						       urb->transfer_buffer + len, buf_size-len);
=======
						       urb->transfer_buffer+len, buf_size-len);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			}

			skb_pull(skb, bytes_sent);

			if (!skb->len) {
				// Frame sent
				b_out->tx_skb = NULL;
				B_L1L2(bcs, PH_DATA | CONFIRM, (void *)(unsigned long) skb->truesize);
				dev_kfree_skb_any(skb);

<<<<<<< HEAD
/*				if (!(bcs->tx_skb = skb_dequeue(&bcs->sq))) { */
/*					st5481B_sched_event(bcs, B_XMTBUFREADY); */
/*				} */
			}
		} else {
			if (bcs->mode == L1_MODE_TRANS) {
				memset(urb->transfer_buffer + len, 0xff, buf_size-len);
=======
/* 				if (!(bcs->tx_skb = skb_dequeue(&bcs->sq))) { */
/* 					st5481B_sched_event(bcs, B_XMTBUFREADY); */
/* 				} */
			}
		} else {
			if (bcs->mode == L1_MODE_TRANS) {
				memset(urb->transfer_buffer+len, 0xff, buf_size-len);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
				len = buf_size;
			} else {
				// Send flags
				len += isdnhdlc_encode(&b_out->hdlc_state,
						       NULL, 0, &bytes_sent,
<<<<<<< HEAD
						       urb->transfer_buffer + len, buf_size-len);
			}
		}
=======
						       urb->transfer_buffer+len, buf_size-len);
			}
		}	
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}

	// Prepare the URB
	for (i = 0, offset = 0; offset < len; i++) {
		urb->iso_frame_desc[i].offset = offset;
		urb->iso_frame_desc[i].length = packet_size;
		offset += packet_size;
		packet_size = SIZE_ISO_PACKETS_B_OUT;
	}
	urb->transfer_buffer_length = len;
	urb->number_of_packets = i;
	urb->dev = adapter->usb_dev;

<<<<<<< HEAD
	DBG_ISO_PACKET(0x200, urb);
=======
	DBG_ISO_PACKET(0x200,urb);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	SUBMIT_URB(urb, GFP_NOIO);
}

/*
 * Start transferring (flags or data) on the B channel, since
 * FIFO counters has been set to a non-zero value.
 */
static void st5481B_start_xfer(void *context)
{
	struct st5481_bcs *bcs = context;

<<<<<<< HEAD
	DBG(4, "B%d", bcs->channel + 1);

	// Start transmitting (flags or data) on B channel

	usb_b_out(bcs, 0);
	usb_b_out(bcs, 1);
=======
	DBG(4,"B%d",bcs->channel+1);

	// Start transmitting (flags or data) on B channel

	usb_b_out(bcs,0);
	usb_b_out(bcs,1);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

/*
 * If the adapter has only 2 LEDs, the green
 * LED will blink with a rate depending
 * on the number of channels opened.
 */
static void led_blink(struct st5481_adapter *adapter)
{
	u_char leds = adapter->leds;

	// 50 frames/sec for each channel
	if (++adapter->led_counter % 50) {
		return;
	}

	if (adapter->led_counter % 100) {
		leds |= GREEN_LED;
	} else {
		leds &= ~GREEN_LED;
	}
<<<<<<< HEAD

=======
	
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	st5481_usb_device_ctrl_msg(adapter, GPIO_OUT, leds, NULL, NULL);
}

static void usb_b_out_complete(struct urb *urb)
{
	struct st5481_bcs *bcs = urb->context;
	struct st5481_b_out *b_out = &bcs->b_out;
	struct st5481_adapter *adapter = bcs->adapter;
	int buf_nr;
<<<<<<< HEAD

=======
	
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	buf_nr = get_buf_nr(b_out->urb, urb);
	test_and_clear_bit(buf_nr, &b_out->busy);

	if (unlikely(urb->status < 0)) {
		switch (urb->status) {
<<<<<<< HEAD
		case -ENOENT:
		case -ESHUTDOWN:
		case -ECONNRESET:
			DBG(4, "urb killed status %d", urb->status);
			return; // Give up
		default:
			WARNING("urb status %d", urb->status);
			if (b_out->busy == 0) {
				st5481_usb_pipe_reset(adapter, (bcs->channel + 1) * 2 | USB_DIR_OUT, NULL, NULL);
			}
			break;
		}
	}

	usb_b_out(bcs, buf_nr);
=======
			case -ENOENT:
			case -ESHUTDOWN:
			case -ECONNRESET:
				DBG(4,"urb killed status %d", urb->status);
				return; // Give up
			default: 
				WARNING("urb status %d",urb->status);
				if (b_out->busy == 0) {
					st5481_usb_pipe_reset(adapter, (bcs->channel+1)*2 | USB_DIR_OUT, NULL, NULL);
				}
				break;
		}
	}

	usb_b_out(bcs,buf_nr);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	if (adapter->number_of_leds == 2)
		led_blink(adapter);
}

/*
 * Start or stop the transfer on the B channel.
 */
static void st5481B_mode(struct st5481_bcs *bcs, int mode)
{
	struct st5481_b_out *b_out = &bcs->b_out;
	struct st5481_adapter *adapter = bcs->adapter;

<<<<<<< HEAD
	DBG(4, "B%d,mode=%d", bcs->channel + 1, mode);
=======
	DBG(4,"B%d,mode=%d", bcs->channel + 1, mode);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	if (bcs->mode == mode)
		return;

	bcs->mode = mode;

	// Cancel all USB transfers on this B channel
	usb_unlink_urb(b_out->urb[0]);
	usb_unlink_urb(b_out->urb[1]);
	b_out->busy = 0;

	st5481_in_mode(&bcs->b_in, mode);
	if (bcs->mode != L1_MODE_NULL) {
		// Open the B channel
		if (bcs->mode != L1_MODE_TRANS) {
			u32 features = HDLC_BITREVERSE;
			if (bcs->mode == L1_MODE_HDLC_56K)
				features |= HDLC_56KBIT;
			isdnhdlc_out_init(&b_out->hdlc_state, features);
		}
<<<<<<< HEAD
		st5481_usb_pipe_reset(adapter, (bcs->channel + 1) * 2, NULL, NULL);

		// Enable B channel interrupts
		st5481_usb_device_ctrl_msg(adapter, FFMSK_B1 + (bcs->channel * 2),
					   OUT_UP + OUT_DOWN + OUT_UNDERRUN, NULL, NULL);

		// Enable B channel FIFOs
		st5481_usb_device_ctrl_msg(adapter, OUT_B1_COUNTER+(bcs->channel * 2), 32, st5481B_start_xfer, bcs);
=======
		st5481_usb_pipe_reset(adapter, (bcs->channel+1)*2, NULL, NULL);
	
		// Enable B channel interrupts
		st5481_usb_device_ctrl_msg(adapter, FFMSK_B1+(bcs->channel*2), 
				    OUT_UP+OUT_DOWN+OUT_UNDERRUN, NULL, NULL);

		// Enable B channel FIFOs
		st5481_usb_device_ctrl_msg(adapter, OUT_B1_COUNTER+(bcs->channel*2), 32, st5481B_start_xfer, bcs);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		if (adapter->number_of_leds == 4) {
			if (bcs->channel == 0) {
				adapter->leds |= B1_LED;
			} else {
				adapter->leds |= B2_LED;
			}
		}
	} else {
		// Disble B channel interrupts
<<<<<<< HEAD
		st5481_usb_device_ctrl_msg(adapter, FFMSK_B1+(bcs->channel * 2), 0, NULL, NULL);

		// Disable B channel FIFOs
		st5481_usb_device_ctrl_msg(adapter, OUT_B1_COUNTER+(bcs->channel * 2), 0, NULL, NULL);
=======
		st5481_usb_device_ctrl_msg(adapter, FFMSK_B1+(bcs->channel*2), 0, NULL, NULL);

		// Disable B channel FIFOs
		st5481_usb_device_ctrl_msg(adapter, OUT_B1_COUNTER+(bcs->channel*2), 0, NULL, NULL);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

		if (adapter->number_of_leds == 4) {
			if (bcs->channel == 0) {
				adapter->leds &= ~B1_LED;
			} else {
				adapter->leds &= ~B2_LED;
			}
		} else {
			st5481_usb_device_ctrl_msg(adapter, GPIO_OUT, adapter->leds, NULL, NULL);
		}
		if (b_out->tx_skb) {
			dev_kfree_skb_any(b_out->tx_skb);
			b_out->tx_skb = NULL;
		}
<<<<<<< HEAD

=======
		
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}
}

static int st5481_setup_b_out(struct st5481_bcs *bcs)
{
	struct usb_device *dev = bcs->adapter->usb_dev;
	struct usb_interface *intf;
	struct usb_host_interface *altsetting = NULL;
	struct usb_host_endpoint *endpoint;
<<<<<<< HEAD
	struct st5481_b_out *b_out = &bcs->b_out;

	DBG(4, "");
=======
  	struct st5481_b_out *b_out = &bcs->b_out;

	DBG(4,"");
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	intf = usb_ifnum_to_if(dev, 0);
	if (intf)
		altsetting = usb_altnum_to_altsetting(intf, 3);
	if (!altsetting)
		return -ENXIO;

	// Allocate URBs and buffers for the B channel out
	endpoint = &altsetting->endpoint[EP_B1_OUT - 1 + bcs->channel * 2];

<<<<<<< HEAD
	DBG(4, "endpoint address=%02x,packet size=%d",
	    endpoint->desc.bEndpointAddress, le16_to_cpu(endpoint->desc.wMaxPacketSize));

	// Allocate memory for 8000bytes/sec + extra bytes if underrun
	return st5481_setup_isocpipes(b_out->urb, dev,
=======
	DBG(4,"endpoint address=%02x,packet size=%d",
	    endpoint->desc.bEndpointAddress, le16_to_cpu(endpoint->desc.wMaxPacketSize));

	// Allocate memory for 8000bytes/sec + extra bytes if underrun
	return st5481_setup_isocpipes(b_out->urb, dev, 
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
				      usb_sndisocpipe(dev, endpoint->desc.bEndpointAddress),
				      NUM_ISO_PACKETS_B, SIZE_ISO_PACKETS_B_OUT,
				      NUM_ISO_PACKETS_B * SIZE_ISO_PACKETS_B_OUT + B_FLOW_ADJUST,
				      usb_b_out_complete, bcs);
}

static void st5481_release_b_out(struct st5481_bcs *bcs)
{
	struct st5481_b_out *b_out = &bcs->b_out;

<<<<<<< HEAD
	DBG(4, "");
=======
	DBG(4,"");
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	st5481_release_isocpipes(b_out->urb);
}

int st5481_setup_b(struct st5481_bcs *bcs)
{
	int retval;

<<<<<<< HEAD
	DBG(4, "");
=======
	DBG(4,"");
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	retval = st5481_setup_b_out(bcs);
	if (retval)
		goto err;
	bcs->b_in.bufsize = HSCX_BUFMAX;
	bcs->b_in.num_packets = NUM_ISO_PACKETS_B;
	bcs->b_in.packet_size = SIZE_ISO_PACKETS_B_IN;
	bcs->b_in.ep = (bcs->channel ? EP_B2_IN : EP_B1_IN) | USB_DIR_IN;
	bcs->b_in.counter = bcs->channel ? IN_B2_COUNTER : IN_B1_COUNTER;
	bcs->b_in.adapter = bcs->adapter;
	bcs->b_in.hisax_if = &bcs->b_if.ifc;
	retval = st5481_setup_in(&bcs->b_in);
	if (retval)
		goto err_b_out;


	return 0;

<<<<<<< HEAD
err_b_out:
	st5481_release_b_out(bcs);
err:
=======
 err_b_out:
	st5481_release_b_out(bcs);
 err:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	return retval;
}

/*
 * Release buffers and URBs for the B channels
 */
void st5481_release_b(struct st5481_bcs *bcs)
{
<<<<<<< HEAD
	DBG(4, "");
=======
	DBG(4,"");
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	st5481_release_in(&bcs->b_in);
	st5481_release_b_out(bcs);
}

/*
 * st5481_b_l2l1 is the entry point for upper layer routines that want to
 * transmit on the B channel.  PH_DATA | REQUEST is a normal packet that
 * we either start transmitting (if idle) or queue (if busy).
 * PH_PULL | REQUEST can be called to request a callback message
 * (PH_PULL | CONFIRM)
 * once the link is idle.  After a "pull" callback, the upper layer
 * routines can use PH_PULL | INDICATION to send data.
 */
void st5481_b_l2l1(struct hisax_if *ifc, int pr, void *arg)
{
	struct st5481_bcs *bcs = ifc->priv;
	struct sk_buff *skb = arg;
	long mode;

	DBG(4, "");

	switch (pr) {
	case PH_DATA | REQUEST:
		BUG_ON(bcs->b_out.tx_skb);
		bcs->b_out.tx_skb = skb;
		break;
	case PH_ACTIVATE | REQUEST:
		mode = (long) arg;
<<<<<<< HEAD
		DBG(4, "B%d,PH_ACTIVATE_REQUEST %ld", bcs->channel + 1, mode);
=======
		DBG(4,"B%d,PH_ACTIVATE_REQUEST %ld", bcs->channel + 1, mode);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		st5481B_mode(bcs, mode);
		B_L1L2(bcs, PH_ACTIVATE | INDICATION, NULL);
		break;
	case PH_DEACTIVATE | REQUEST:
<<<<<<< HEAD
		DBG(4, "B%d,PH_DEACTIVATE_REQUEST", bcs->channel + 1);
=======
		DBG(4,"B%d,PH_DEACTIVATE_REQUEST", bcs->channel + 1);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		st5481B_mode(bcs, L1_MODE_NULL);
		B_L1L2(bcs, PH_DEACTIVATE | INDICATION, NULL);
		break;
	default:
		WARNING("pr %#x\n", pr);
	}
}
