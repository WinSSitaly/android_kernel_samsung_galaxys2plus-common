#
# Makefile for key management
#

obj-y := \
	gc.o \
	key.o \
	keyring.o \
	keyctl.o \
	permission.o \
	process_keys.o \
	request_key.o \
	request_key_auth.o \
	user_defined.o

obj-$(CONFIG_TRUSTED_KEYS) += trusted.o
<<<<<<< HEAD
obj-$(CONFIG_ENCRYPTED_KEYS) += encrypted-keys/
=======
obj-$(CONFIG_ENCRYPTED_KEYS) += encrypted.o
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
obj-$(CONFIG_KEYS_COMPAT) += compat.o
obj-$(CONFIG_PROC_FS) += proc.o
obj-$(CONFIG_SYSCTL) += sysctl.o
