<<<<<<< HEAD
ifeq ($(CONFIG_SA1111),y)
   zreladdr-y	+= 0xc0208000
else
   zreladdr-y	+= 0xc0008000
=======
   zreladdr-y	:= 0xc0008000
ifeq ($(CONFIG_ARCH_SA1100),y)
   zreladdr-$(CONFIG_SA1111)		:= 0xc0208000
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
endif
params_phys-y	:= 0xc0000100
initrd_phys-y	:= 0xc0800000

