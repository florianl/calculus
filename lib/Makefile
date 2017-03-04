PROG = libcalculus.so
CC = gcc
FLEX = flex
CFLAGS += -g -pedantic -Wall -DVERSION='$(date "+%Y%m%d")' -std=c99 -fPIC
LDFLAGS += -lfl -shared
FLEXFLAGS += -Cfr

.PHONY = all

CFILES = 	tools.c

LFILES =	parse.lex

all: compile
	$(CC) $(CFILES:.c=.o) $(LFILES:.lex=.o) $(LDFLAGS) -o $(PROG)

compile:
	for CFILE in $(CFILES); do		\
		$(CC) $(CFLAGS) -c $$CFILE;	\
	done
	for LEXFILE in $(LFILES); do		\
		make generate LFILE=$$LEXFILE;	\
		$(CC) $(CFLAGS) -c $$(echo $$LEXFILE | sed 's/\.lex/\.c/g') -o  $$(echo $$LEXFILE | sed 's/\.lex/\.o/g');		\
	done

generate:
	$(eval FCFILE = $(LFILE:.lex=.c))
	if [ -f $(FCFILE) ] ; then 		\
		rm $(FCFILE);			\
	fi
	$(FLEX) $(FLEXFLAGS) -o $(FCFILE) $(LFILE)

flexclean:
	$(eval FCFILES = $(LFILES:.lex=.c))
	for FCFILE in $(FCFILES); do		\
		if [ -f $$FCFILE ] ; then rm $$FCFILE; fi	\
	done

clean: flexclean
	rm -f *.o *.so
