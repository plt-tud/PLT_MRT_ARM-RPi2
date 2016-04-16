CROSSPREFIX=/opt/arm-cross-hf/bin/arm-linux-gnueabihf-
AS=$(CROSSPREFIX)as
CC=$(CROSSPREFIX)gcc
CFLAGS=-Wall -static -std=c99
DLCFLAGS=-Wall  -std=c99
AFLAGS=-Wa,-gstubs
INCLUDES=-I./include
LIBRARIES=-L./lib 

CDEPS="rpi.c"

.PHONY: debug

debug:  clean ua_namespace.o
	$(CC) $(CFLAGS) $(AFLAGS) $(INCLUDES) $(LIBRARIES) -Wl,-rpath=./ -g -o ua_blinker main.c ua_namespace.o lib/libopen62541-static.a lib/libbcm2835.a -lpthread -ldl
stable: clean ua_namespace.o
	$(CC) $(CFLAGS) $(AFLAGS) $(INCLUDES) $(LIBRARIES) -Wl,-rpath=./ -O2 -o ua_blinker main.c ua_namespace.o lib/libopen62541-static.a lib/libbcm2835.a -lpthread -ldl
	
%.o: %.c %.h
	$(CC) $(CFLAGS)  $(AFLAGS) $(INCLUDES) $(LIBRARIES)  -g -c -o $@ $< $(CFLAGS)

clean:
	rm -vfr *~ ua_blinker *.o