############################################################################
# Makefile for building and installing libmcp3204
############################################################################

RM := rm -rf

PREFIX = /usr

CC = gcc
CFLAGS = -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP
LDFLAGS = -shared
SOURCES = libmcp3204.c
OBJECTS = $(SOURCES:.c=.o)
	
all: libmcp3204.so

libmcp3204.so: $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

libmcp3204.o: $(SOURCES)
	$(CC) $(CFLAGS) $< -o $@

clean:
	-$(RM) libmcp3204.o libmcp3204.so libmcp3204.d

# Install the library in $(prefix)
install: 
	install -m 0644 libmcp3204.so $(PREFIX)/lib
	install -m 0644 libmcp3204.h $(PREFIX)/include

# Uninstall the library 
uninstall:
	-$(RM) $(PREFIX)/lib/libmcp3204.so $(PREFIX)/include/libmcp3204.h


