#
# ia64/platform/dig/Makefile
#
# Copyright (C) 1999 Silicon Graphics, Inc.
# Copyright (C) Srinivasa Thirumalachar (sprasad@engr.sgi.com)
#

obj-y := setup.o
<<<<<<< HEAD
ifeq ($(CONFIG_INTEL_IOMMU), y)
=======
ifeq ($(CONFIG_DMAR), y)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
obj-$(CONFIG_IA64_GENERIC) += machvec.o machvec_vtd.o
else
obj-$(CONFIG_IA64_GENERIC) += machvec.o
endif

