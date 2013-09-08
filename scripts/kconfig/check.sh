#!/bin/sh
# Needed for systems without gettext
<<<<<<< HEAD
$* -x c -o /dev/null - > /dev/null 2>&1 << EOF
=======
$* -xc -o /dev/null - > /dev/null 2>&1 << EOF
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <libintl.h>
int main()
{
	gettext("");
	return 0;
}
EOF
if [ ! "$?" -eq "0"  ]; then
	echo -DKBUILD_NO_NLS;
fi

