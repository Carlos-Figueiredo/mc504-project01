CC = gcc
CFLAGS = -g -pthread -std=c99

PROGRAMS = cigar  \ cigar_generalized \ cigar_presentation \ ascii_animation

all: $(PROGRAMS)

presentation:
	gcc -pthread -std=c99 cigar_generalized_presentation.c  ascii_animation.c -o cigar_presentation_generalized

clean:
	rm -f *.o *~ $(PROGRAMS)
