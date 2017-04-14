CC = gcc
CFLAGS = -g -pthread --std=c99

PROGRAMS = cigar  \

all: $(PROGRAMS)

cigar:
	$(CC) $(CFLAGS) cigar.c -o cigar

clean:
	rm -f *.o *~ $(PROGRAMS)
