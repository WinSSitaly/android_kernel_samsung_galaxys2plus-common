# Makefile for USB tools

CC = $(CROSS_COMPILE)gcc
PTHREAD_LIBS = -lpthread
WARNINGS = -Wall -Wextra
<<<<<<< HEAD
CFLAGS = $(WARNINGS) -g $(PTHREAD_LIBS) -I../include
=======
CFLAGS = $(WARNINGS) -g $(PTHREAD_LIBS)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

all: testusb ffs-test
%: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) testusb ffs-test
