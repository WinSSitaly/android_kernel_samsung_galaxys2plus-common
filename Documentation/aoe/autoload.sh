#!/bin/sh
# set aoe to autoload by installing the
<<<<<<< HEAD
# aliases in /etc/modprobe.d/

f=/etc/modprobe.d/aoe.conf
=======
# aliases in /etc/modprobe.conf

f=/etc/modprobe.conf
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

if test ! -r $f || test ! -w $f; then
	echo "cannot configure $f for module autoloading" 1>&2
	exit 1
fi

grep major-152 $f >/dev/null
if [ $? = 1 ]; then
	echo alias block-major-152 aoe >> $f
	echo alias char-major-152 aoe >> $f
fi

