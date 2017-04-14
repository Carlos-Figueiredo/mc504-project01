CC = gcc
CFLAGS = -g -pthread

PROGRAMS = cigar.c  \

all: $(PROGRAMS)

clean:
	rm -f *.o *~ $(PROGRAMS)
