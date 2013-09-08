<<<<<<< HEAD
#!/bin/sh
=======
#!/bin/sh -x

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

if [ -r Makefile ]; then
	make distclean
fi

<<<<<<< HEAD
FILES="aclocal.m4 autom4te.cache compile config.guess config.h.in config.log \
       config.status config.sub configure cscope.out depcomp install-sh      \
       libsrc/Makefile libsrc/Makefile.in libtool ltmain.sh Makefile         \
       Makefile.in missing src/Makefile src/Makefile.in"

rm -vRf $FILES
=======
FILES="configure cscope.out Makefile.in depcomp compile config.guess config.sub config.h.in~ config.log config.status ltmain.sh libtool config.h.in autom4te.cache missing aclocal.m4 install-sh cmd/Makefile.in lib/Makefile.in Makefile lib/Makefile cmd/Makefile"

rm -Rf $FILES
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
