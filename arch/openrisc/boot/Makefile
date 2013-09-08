

ifneq '$(CONFIG_OPENRISC_BUILTIN_DTB)' '""'
BUILTIN_DTB := $(patsubst "%",%,$(CONFIG_OPENRISC_BUILTIN_DTB)).dtb.o
else
BUILTIN_DTB :=
endif
obj-y += $(BUILTIN_DTB)

clean-files := *.dtb.S

#DTC_FLAGS ?= -p 1024

<<<<<<< HEAD
$(obj)/%.dtb: $(src)/dts/%.dts FORCE
	$(call if_changed_dep,dtc)
=======
$(obj)/%.dtb: $(src)/dts/%.dts
	$(call cmd,dtc)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
