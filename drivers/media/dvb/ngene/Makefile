#
# Makefile for the nGene device driver
#

ngene-objs := ngene-core.o ngene-i2c.o ngene-cards.o ngene-dvb.o

obj-$(CONFIG_DVB_NGENE) += ngene.o

<<<<<<< HEAD
ccflags-y += -Idrivers/media/dvb/dvb-core/
ccflags-y += -Idrivers/media/dvb/frontends/
ccflags-y += -Idrivers/media/common/tuners/

# For the staging CI driver cxd2099
ccflags-y += -Idrivers/staging/media/cxd2099/
=======
EXTRA_CFLAGS += -Idrivers/media/dvb/dvb-core/
EXTRA_CFLAGS += -Idrivers/media/dvb/frontends/
EXTRA_CFLAGS += -Idrivers/media/common/tuners/

# For the staging CI driver cxd2099
EXTRA_CFLAGS += -Idrivers/staging/cxd2099/
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
