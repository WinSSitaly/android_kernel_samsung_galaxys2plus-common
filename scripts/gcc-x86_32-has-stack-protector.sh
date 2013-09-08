#!/bin/sh

<<<<<<< HEAD
echo "int foo(void) { char X[200]; return 3; }" | $* -S -x c -c -O0 -fstack-protector - -o - 2> /dev/null | grep -q "%gs"
=======
echo "int foo(void) { char X[200]; return 3; }" | $* -S -xc -c -O0 -fstack-protector - -o - 2> /dev/null | grep -q "%gs"
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
if [ "$?" -eq "0" ] ; then
	echo y
else
	echo n
fi
