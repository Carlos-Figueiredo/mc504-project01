CC = gcc
CFLAGS = -g -pthread -std=c99

PROGRAMS = cigar  \

all: $(PROGRAMS)

clean:
	rm -f *.o *~ $(PROGRAMS)
