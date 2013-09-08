ivtv-objs	:= ivtv-routing.o ivtv-cards.o ivtv-controls.o \
		   ivtv-driver.o ivtv-fileops.o ivtv-firmware.o \
		   ivtv-gpio.o ivtv-i2c.o ivtv-ioctl.o ivtv-irq.o \
		   ivtv-mailbox.o ivtv-queue.o ivtv-streams.o ivtv-udma.o \
		   ivtv-vbi.o ivtv-yuv.o

obj-$(CONFIG_VIDEO_IVTV) += ivtv.o
obj-$(CONFIG_VIDEO_FB_IVTV) += ivtvfb.o

<<<<<<< HEAD
ccflags-y += -I$(srctree)/drivers/media/video
ccflags-y += -I$(srctree)/drivers/media/common/tuners
ccflags-y += -I$(srctree)/drivers/media/dvb/dvb-core
ccflags-y += -I$(srctree)/drivers/media/dvb/frontends
=======
EXTRA_CFLAGS += -Idrivers/media/video
EXTRA_CFLAGS += -Idrivers/media/common/tuners
EXTRA_CFLAGS += -Idrivers/media/dvb/dvb-core
EXTRA_CFLAGS += -Idrivers/media/dvb/frontends
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

