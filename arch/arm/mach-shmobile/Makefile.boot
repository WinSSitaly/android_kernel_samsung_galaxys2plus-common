__ZRELADDR	:= $(shell /bin/bash -c 'printf "0x%08x" \
		     $$[$(CONFIG_MEMORY_START) + 0x8000]')

<<<<<<< HEAD
   zreladdr-y   += $(__ZRELADDR)
=======
   zreladdr-y   := $(__ZRELADDR)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

# Unsupported legacy stuff
#
#params_phys-y (Instead: Pass atags pointer in r2)
#initrd_phys-y (Instead: Use compiled-in initramfs)
