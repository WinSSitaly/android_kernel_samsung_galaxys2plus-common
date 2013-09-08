# Note: the following conditions must always be true:
#   ZRELADDR == virt_to_phys(TEXTADDR)
#   PARAMS_PHYS must be within 4MB of ZRELADDR
#   INITRD_PHYS must be in RAM

<<<<<<< HEAD
   zreladdr-y	+= 0x00008000
=======
   zreladdr-y	:= 0x00008000
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
params_phys-y	:= 0x00000100
initrd_phys-y	:= 0x00800000
