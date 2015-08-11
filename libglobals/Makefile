CC = gcc
CFLAGS = -g -O2

all: libglobals.so useglobals

libglobals.so: libglobals.c
	$(CC) -shared $< -o $@ -fPIC

useglobals: useglobals.c libglobals.so
	$(CC) $< -o $@ -lglobals -L.

%.o : %.c
	$(CC) $(CFLAGS) -c $<

run: all
	@LD_LIBRARY_PATH=$(PWD):$(LD_LIBRARY_PATH) ./useglobals

.depend: useglobals.c libglobals.c
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ > ./.depend;

include .depend
