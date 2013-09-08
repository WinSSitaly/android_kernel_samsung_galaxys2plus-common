/*
 * Touch Screen driver for Renesas MIGO-R Platform
 *
 * Copyright (c) 2008 Magnus Damm
 * Copyright (c) 2007 Ujjwal Pande <ujjwal@kenati.com>,
 *  Kenati Technologies Pvt Ltd.
 *
 * This file is free software; you can redistribute it and/or
 * modify it under the terms of the GNU  General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/pm.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <linux/i2c.h>
#include <linux/timer.h>

#define EVENT_PENDOWN 1
#define EVENT_REPEAT  2
#define EVENT_PENUP   3

struct migor_ts_priv {
	struct i2c_client *client;
	struct input_dev *input;
<<<<<<< HEAD
=======
	struct delayed_work work;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	int irq;
};

static const u_int8_t migor_ts_ena_seq[17] = { 0x33, 0x22, 0x11,
					       0x01, 0x06, 0x07, };
static const u_int8_t migor_ts_dis_seq[17] = { };

<<<<<<< HEAD
static irqreturn_t migor_ts_isr(int irq, void *dev_id)
{
	struct migor_ts_priv *priv = dev_id;
=======
static void migor_ts_poscheck(struct work_struct *work)
{
	struct migor_ts_priv *priv = container_of(work,
						  struct migor_ts_priv,
						  work.work);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	unsigned short xpos, ypos;
	unsigned char event;
	u_int8_t buf[16];

<<<<<<< HEAD
	/*
	 * The touch screen controller chip is hooked up to the CPU
	 * using I2C and a single interrupt line. The interrupt line
	 * is pulled low whenever someone taps the screen. To deassert
	 * the interrupt line we need to acknowledge the interrupt by
	 * communicating with the controller over the slow i2c bus.
	 *
	 * Since I2C bus controller may sleep we are using threaded
	 * IRQ here.
	 */

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	memset(buf, 0, sizeof(buf));

	/* Set Index 0 */
	buf[0] = 0;
	if (i2c_master_send(priv->client, buf, 1) != 1) {
		dev_err(&priv->client->dev, "Unable to write i2c index\n");
		goto out;
	}

	/* Now do Page Read */
	if (i2c_master_recv(priv->client, buf, sizeof(buf)) != sizeof(buf)) {
		dev_err(&priv->client->dev, "Unable to read i2c page\n");
		goto out;
	}

	ypos = ((buf[9] & 0x03) << 8 | buf[8]);
	xpos = ((buf[11] & 0x03) << 8 | buf[10]);
	event = buf[12];

<<<<<<< HEAD
	switch (event) {
	case EVENT_PENDOWN:
	case EVENT_REPEAT:
=======
	if (event == EVENT_PENDOWN || event == EVENT_REPEAT) {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		input_report_key(priv->input, BTN_TOUCH, 1);
		input_report_abs(priv->input, ABS_X, ypos); /*X-Y swap*/
		input_report_abs(priv->input, ABS_Y, xpos);
		input_sync(priv->input);
<<<<<<< HEAD
		break;

	case EVENT_PENUP:
		input_report_key(priv->input, BTN_TOUCH, 0);
		input_sync(priv->input);
		break;
	}

 out:
	return IRQ_HANDLED;
}

=======
	} else if (event == EVENT_PENUP) {
		input_report_key(priv->input, BTN_TOUCH, 0);
		input_sync(priv->input);
	}
 out:
	enable_irq(priv->irq);
}

static irqreturn_t migor_ts_isr(int irq, void *dev_id)
{
	struct migor_ts_priv *priv = dev_id;

	/* the touch screen controller chip is hooked up to the cpu
	 * using i2c and a single interrupt line. the interrupt line
	 * is pulled low whenever someone taps the screen. to deassert
	 * the interrupt line we need to acknowledge the interrupt by
	 * communicating with the controller over the slow i2c bus.
	 *
	 * we can't acknowledge from interrupt context since the i2c
	 * bus controller may sleep, so we just disable the interrupt
	 * here and handle the acknowledge using delayed work.
	 */

	disable_irq_nosync(irq);
	schedule_delayed_work(&priv->work, HZ / 20);

	return IRQ_HANDLED;
}


>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
static int migor_ts_open(struct input_dev *dev)
{
	struct migor_ts_priv *priv = input_get_drvdata(dev);
	struct i2c_client *client = priv->client;
	int count;

	/* enable controller */
	count = i2c_master_send(client, migor_ts_ena_seq,
				sizeof(migor_ts_ena_seq));
	if (count != sizeof(migor_ts_ena_seq)) {
		dev_err(&client->dev, "Unable to enable touchscreen.\n");
		return -ENXIO;
	}

	return 0;
}

static void migor_ts_close(struct input_dev *dev)
{
	struct migor_ts_priv *priv = input_get_drvdata(dev);
	struct i2c_client *client = priv->client;

	disable_irq(priv->irq);

<<<<<<< HEAD
=======
	/* cancel pending work and wait for migor_ts_poscheck() to finish */
	if (cancel_delayed_work_sync(&priv->work)) {
		/*
		 * if migor_ts_poscheck was canceled we need to enable IRQ
		 * here to balance disable done in migor_ts_isr.
		 */
		enable_irq(priv->irq);
	}

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	/* disable controller */
	i2c_master_send(client, migor_ts_dis_seq, sizeof(migor_ts_dis_seq));

	enable_irq(priv->irq);
}

static int migor_ts_probe(struct i2c_client *client,
			  const struct i2c_device_id *idp)
{
	struct migor_ts_priv *priv;
	struct input_dev *input;
	int error;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
<<<<<<< HEAD
	input = input_allocate_device();
	if (!priv || !input) {
		dev_err(&client->dev, "failed to allocate memory\n");
		error = -ENOMEM;
		goto err_free_mem;
	}

	priv->client = client;
	priv->input = input;
	priv->irq = client->irq;

	input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	__set_bit(BTN_TOUCH, input->keybit);
=======
	if (!priv) {
		dev_err(&client->dev, "failed to allocate driver data\n");
		error = -ENOMEM;
		goto err0;
	}

	dev_set_drvdata(&client->dev, priv);

	input = input_allocate_device();
	if (!input) {
		dev_err(&client->dev, "Failed to allocate input device.\n");
		error = -ENOMEM;
		goto err1;
	}

	input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	input_set_abs_params(input, ABS_X, 95, 955, 0, 0);
	input_set_abs_params(input, ABS_Y, 85, 935, 0, 0);

	input->name = client->name;
	input->id.bustype = BUS_I2C;
	input->dev.parent = &client->dev;

	input->open = migor_ts_open;
	input->close = migor_ts_close;

	input_set_drvdata(input, priv);

<<<<<<< HEAD
	error = request_threaded_irq(priv->irq, NULL, migor_ts_isr,
                                     IRQF_TRIGGER_LOW | IRQF_ONESHOT,
                                     client->name, priv);
	if (error) {
		dev_err(&client->dev, "Unable to request touchscreen IRQ.\n");
		goto err_free_mem;
	}

	error = input_register_device(input);
	if (error)
		goto err_free_irq;

	i2c_set_clientdata(client, priv);
	device_init_wakeup(&client->dev, 1);

	return 0;

 err_free_irq:
	free_irq(priv->irq, priv);
 err_free_mem:
	input_free_device(input);
	kfree(priv);
=======
	priv->client = client;
	priv->input = input;
	INIT_DELAYED_WORK(&priv->work, migor_ts_poscheck);
	priv->irq = client->irq;

	error = input_register_device(input);
	if (error)
		goto err1;

	error = request_irq(priv->irq, migor_ts_isr, IRQF_TRIGGER_LOW,
			    client->name, priv);
	if (error) {
		dev_err(&client->dev, "Unable to request touchscreen IRQ.\n");
		goto err2;
	}

	device_init_wakeup(&client->dev, 1);
	return 0;

 err2:
	input_unregister_device(input);
	input = NULL; /* so we dont try to free it below */
 err1:
	input_free_device(input);
	kfree(priv);
 err0:
	dev_set_drvdata(&client->dev, NULL);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	return error;
}

static int migor_ts_remove(struct i2c_client *client)
{
<<<<<<< HEAD
	struct migor_ts_priv *priv = i2c_get_clientdata(client);
=======
	struct migor_ts_priv *priv = dev_get_drvdata(&client->dev);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	free_irq(priv->irq, priv);
	input_unregister_device(priv->input);
	kfree(priv);

	dev_set_drvdata(&client->dev, NULL);

	return 0;
}

static int migor_ts_suspend(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
<<<<<<< HEAD
	struct migor_ts_priv *priv = i2c_get_clientdata(client);
=======
	struct migor_ts_priv *priv = dev_get_drvdata(&client->dev);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	if (device_may_wakeup(&client->dev))
		enable_irq_wake(priv->irq);

	return 0;
}

static int migor_ts_resume(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
<<<<<<< HEAD
	struct migor_ts_priv *priv = i2c_get_clientdata(client);
=======
	struct migor_ts_priv *priv = dev_get_drvdata(&client->dev);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	if (device_may_wakeup(&client->dev))
		disable_irq_wake(priv->irq);

	return 0;
}

static SIMPLE_DEV_PM_OPS(migor_ts_pm, migor_ts_suspend, migor_ts_resume);

static const struct i2c_device_id migor_ts_id[] = {
	{ "migor_ts", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, migor_ts);

static struct i2c_driver migor_ts_driver = {
	.driver = {
		.name = "migor_ts",
		.pm = &migor_ts_pm,
	},
	.probe = migor_ts_probe,
	.remove = migor_ts_remove,
	.id_table = migor_ts_id,
};

<<<<<<< HEAD
module_i2c_driver(migor_ts_driver);
=======
static int __init migor_ts_init(void)
{
	return i2c_add_driver(&migor_ts_driver);
}

static void __exit migor_ts_exit(void)
{
	i2c_del_driver(&migor_ts_driver);
}
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

MODULE_DESCRIPTION("MigoR Touchscreen driver");
MODULE_AUTHOR("Magnus Damm <damm@opensource.se>");
MODULE_LICENSE("GPL");
<<<<<<< HEAD
=======

module_init(migor_ts_init);
module_exit(migor_ts_exit);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
