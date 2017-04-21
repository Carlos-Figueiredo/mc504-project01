CC = gcc
CFLAGS = -g -pthread -std=c99

PROGRAMS = cigar  \ cigar_generalized

all: $(PROGRAMS)

clean:
	rm -f *.o *~ $(PROGRAMS)
