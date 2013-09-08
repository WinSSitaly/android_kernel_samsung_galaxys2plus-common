<<<<<<< HEAD
# Those numbers are used only by the non-DT V2P-CA9 platform
# The DT-enabled ones require CONFIG_AUTO_ZRELADDR=y
   zreladdr-y	+= 0x60008000
params_phys-y	:= 0x60000100
initrd_phys-y	:= 0x60800000

dtb-$(CONFIG_ARCH_VEXPRESS_DT)	+= vexpress-v2p-ca5s.dtb \
				   vexpress-v2p-ca9.dtb \
				   vexpress-v2p-ca15-tc1.dtb
=======
   zreladdr-y	:= 0x60008000
params_phys-y	:= 0x60000100
initrd_phys-y	:= 0x60800000
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
