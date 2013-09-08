<<<<<<< HEAD
/*
 * nvec_kbd: keyboard driver for a NVIDIA compliant embedded controller
 *
 * Copyright (C) 2011 The AC100 Kernel Team <ac100@lists.launchpad.net>
 *
 * Authors:  Pierre-Hugues Husson <phhusson@free.fr>
 *           Marc Dietrich <marvin24@gmx.de>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 */

#include <linux/module.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/delay.h>
#include <linux/platform_device.h>

#include "nvec-keytable.h"
#include "nvec.h"

#define ACK_KBD_EVENT {'\x05', '\xed', '\x01'}

static const char led_on[3] = "\x05\xed\x07";
static const char led_off[3] = "\x05\xed\x00";
static unsigned char keycodes[ARRAY_SIZE(code_tab_102us)
			      + ARRAY_SIZE(extcode_tab_us102)];
=======
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/delay.h>
#include "nvec-keytable.h"
#include "nvec.h"

#define ACK_KBD_EVENT {'\x05','\xed','\x01'}

static unsigned char keycodes[ARRAY_SIZE(code_tab_102us)
			+ ARRAY_SIZE(extcode_tab_us102)];
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

struct nvec_keys {
	struct input_dev *input;
	struct notifier_block notifier;
	struct nvec_chip *nvec;
<<<<<<< HEAD
	bool caps_lock;
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
};

static struct nvec_keys keys_dev;

<<<<<<< HEAD
static void nvec_kbd_toggle_led(void)
{
	keys_dev.caps_lock = !keys_dev.caps_lock;

	if (keys_dev.caps_lock)
		nvec_write_async(keys_dev.nvec, led_on, sizeof(led_on));
	else
		nvec_write_async(keys_dev.nvec, led_off, sizeof(led_off));
}

static int nvec_keys_notifier(struct notifier_block *nb,
			      unsigned long event_type, void *data)
=======
static int nvec_keys_notifier(struct notifier_block *nb,
				unsigned long event_type, void *data)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	int code, state;
	unsigned char *msg = (unsigned char *)data;

	if (event_type == NVEC_KB_EVT) {
<<<<<<< HEAD
		int _size = (msg[0] & (3 << 5)) >> 5;

/* power on/off button */
		if (_size == NVEC_VAR_SIZE)
			return NOTIFY_STOP;

		if (_size == NVEC_3BYTES)
=======
		nvec_size _size = (msg[0] & (3 << 5)) >> 5;

/* power on/off button */
		if(_size == NVEC_VAR_SIZE)
			return NOTIFY_STOP;

		if(_size == NVEC_3BYTES)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			msg++;

		code = msg[1] & 0x7f;
		state = msg[1] & 0x80;

<<<<<<< HEAD
		if (code_tabs[_size][code] == KEY_CAPSLOCK && state)
			nvec_kbd_toggle_led();

		input_report_key(keys_dev.input, code_tabs[_size][code],
				 !state);
=======
		input_report_key(keys_dev.input, code_tabs[_size][code], !state);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		input_sync(keys_dev.input);

		return NOTIFY_STOP;
	}

	return NOTIFY_DONE;
}

static int nvec_kbd_event(struct input_dev *dev, unsigned int type,
<<<<<<< HEAD
			  unsigned int code, int value)
=======
				unsigned int code, int value)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	unsigned char buf[] = ACK_KBD_EVENT;
	struct nvec_chip *nvec = keys_dev.nvec;

<<<<<<< HEAD
	if (type == EV_REP)
		return 0;

	if (type != EV_LED)
		return -1;

	if (code != LED_CAPSL)
=======
	if(type==EV_REP)
		return 0;

	if(type!=EV_LED)
		return -1;

	if(code!=LED_CAPSL)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		return -1;

	buf[2] = !!value;
	nvec_write_async(nvec, buf, sizeof(buf));

	return 0;
}

<<<<<<< HEAD
static int __devinit nvec_kbd_probe(struct platform_device *pdev)
{
	struct nvec_chip *nvec = dev_get_drvdata(pdev->dev.parent);
=======
int __init nvec_kbd_init(struct nvec_chip *nvec)
{
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	int i, j, err;
	struct input_dev *idev;

	j = 0;

<<<<<<< HEAD
	for (i = 0; i < ARRAY_SIZE(code_tab_102us); ++i)
		keycodes[j++] = code_tab_102us[i];

	for (i = 0; i < ARRAY_SIZE(extcode_tab_us102); ++i)
		keycodes[j++] = extcode_tab_us102[i];

	idev = input_allocate_device();
	idev->name = "nvec keyboard";
	idev->phys = "nvec";
=======
	for(i = 0; i < ARRAY_SIZE(code_tab_102us); ++i)
		keycodes[j++] = code_tab_102us[i];

	for(i = 0; i < ARRAY_SIZE(extcode_tab_us102); ++i)
		keycodes[j++]=extcode_tab_us102[i];

	idev = input_allocate_device();
	idev->name = "Tegra nvec keyboard";
	idev->phys = "i2c3_slave/nvec";
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	idev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP) | BIT_MASK(EV_LED);
	idev->ledbit[0] = BIT_MASK(LED_CAPSL);
	idev->event = nvec_kbd_event;
	idev->keycode = keycodes;
	idev->keycodesize = sizeof(unsigned char);
	idev->keycodemax = ARRAY_SIZE(keycodes);

<<<<<<< HEAD
	for (i = 0; i < ARRAY_SIZE(keycodes); ++i)
=======
	for( i = 0; i < ARRAY_SIZE(keycodes); ++i)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		set_bit(keycodes[i], idev->keybit);

	clear_bit(0, idev->keybit);
	err = input_register_device(idev);
<<<<<<< HEAD
	if (err)
=======
	if(err)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		goto fail;

	keys_dev.input = idev;
	keys_dev.notifier.notifier_call = nvec_keys_notifier;
	keys_dev.nvec = nvec;
	nvec_register_notifier(nvec, &keys_dev.notifier, 0);

	/* Enable keyboard */
	nvec_write_async(nvec, "\x05\xf4", 2);

	/* keyboard reset? */
	nvec_write_async(nvec, "\x05\x03\x01\x01", 4);
	nvec_write_async(nvec, "\x05\x04\x01", 3);
	nvec_write_async(nvec, "\x06\x01\xff\x03", 4);
/*	FIXME
	wait until keyboard reset is finished
	or until we have a sync write */
	mdelay(1000);

<<<<<<< HEAD
	/* Disable caps lock LED */
	nvec_write_async(nvec, led_off, sizeof(led_off));

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	return 0;

fail:
	input_free_device(idev);
	return err;
}
<<<<<<< HEAD

static struct platform_driver nvec_kbd_driver = {
	.probe  = nvec_kbd_probe,
	.driver = {
		.name = "nvec-kbd",
		.owner = THIS_MODULE,
	},
};

static int __init nvec_kbd_init(void)
{
	return platform_driver_register(&nvec_kbd_driver);
}

module_init(nvec_kbd_init);

MODULE_AUTHOR("Marc Dietrich <marvin24@gmx.de>");
MODULE_DESCRIPTION("NVEC keyboard driver");
MODULE_LICENSE("GPL");
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
