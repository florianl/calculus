PROG = calculus
CC = gcc
CFLAGS += -g -pedantic -Wall -DVERSION='$(date "+%Y%m%d")' -std=c99
LDFLAGS += -L../lib -lcalculus -lfl
INCLUDES += -I../include

.PHONY = all

CFILES = 	calculus.c

all: compile
	$(CC) $(CFILES:.c=.o) $(INCLUDES) $(LDFLAGS) -o $(PROG)

compile:
	for CFILE in $(CFILES); do		\
		$(CC) $(CFLAGS) $(INCLUDES) -c $$CFILE;	\
	done

clean:
	rm -f *.o $(PROG)
