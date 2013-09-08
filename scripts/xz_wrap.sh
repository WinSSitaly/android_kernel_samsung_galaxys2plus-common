#!/bin/sh
#
# This is a wrapper for xz to compress the kernel image using appropriate
# compression options depending on the architecture.
#
# Author: Lasse Collin <lasse.collin@tukaani.org>
#
# This file has been put into the public domain.
# You can do whatever you want with this file.
#

BCJ=
LZMA2OPTS=

<<<<<<< HEAD
case $SRCARCH in
	x86)            BCJ=--x86 ;;
=======
case $ARCH in
	x86|x86_64)     BCJ=--x86 ;;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	powerpc)        BCJ=--powerpc ;;
	ia64)           BCJ=--ia64; LZMA2OPTS=pb=4 ;;
	arm)            BCJ=--arm ;;
	sparc)          BCJ=--sparc ;;
esac

exec xz --check=crc32 $BCJ --lzma2=$LZMA2OPTS,dict=32MiB
