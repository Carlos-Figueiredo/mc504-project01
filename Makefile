CC = gcc
CFLAGS = -g -pthread -std=c99

PROGRAMS = cigar  \ cigar_generalized \ cigar_presentation \ ascii_animation

all: $(PROGRAMS)

clean:
	rm -f *.o *~ $(PROGRAMS)
