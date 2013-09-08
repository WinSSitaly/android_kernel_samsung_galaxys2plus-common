#
# Makefile for the MB93090-MB00 motherboard stuff
#

ifeq "$(CONFIG_PCI)" "y"
<<<<<<< HEAD
obj-y := pci-frv.o pci-irq.o pci-vdk.o
=======
obj-y := pci-frv.o pci-irq.o pci-vdk.o pci-iomap.o
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

ifeq "$(CONFIG_MMU)" "y"
obj-y += pci-dma.o
else
obj-y += pci-dma-nommu.o
endif
endif

obj-$(CONFIG_MTD) += flash.o
