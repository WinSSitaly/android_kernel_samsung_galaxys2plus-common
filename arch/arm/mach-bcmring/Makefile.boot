# Address where decompressor will be written and eventually executed.
#
# default to SDRAM
<<<<<<< HEAD
zreladdr-y      += $(CONFIG_BCM_ZRELADDR)
=======
zreladdr-y      := $(CONFIG_BCM_ZRELADDR)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
params_phys-y   := 0x00000800

