#
# Makefile for the kernel SAA7146 FULL TS DVB device driver
# and the AV7110 DVB device driver
#

dvb-ttpci-objs := av7110_hw.o av7110_v4l.o av7110_av.o av7110_ca.o av7110.o av7110_ipack.o

ifdef CONFIG_INPUT_EVDEV
dvb-ttpci-objs += av7110_ir.o
endif

obj-$(CONFIG_TTPCI_EEPROM) += ttpci-eeprom.o
obj-$(CONFIG_DVB_BUDGET_CORE) += budget-core.o
obj-$(CONFIG_DVB_BUDGET) += budget.o
obj-$(CONFIG_DVB_BUDGET_AV) += budget-av.o
obj-$(CONFIG_DVB_BUDGET_CI) += budget-ci.o
obj-$(CONFIG_DVB_BUDGET_PATCH) += budget-patch.o
obj-$(CONFIG_DVB_AV7110) += dvb-ttpci.o

<<<<<<< HEAD
ccflags-y += -Idrivers/media/dvb/dvb-core/ -Idrivers/media/dvb/frontends/
ccflags-y += -Idrivers/media/common/tuners
=======
EXTRA_CFLAGS += -Idrivers/media/dvb/dvb-core/ -Idrivers/media/dvb/frontends/
EXTRA_CFLAGS += -Idrivers/media/common/tuners
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
