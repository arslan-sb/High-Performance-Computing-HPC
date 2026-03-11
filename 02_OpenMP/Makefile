CC      = gcc
CFLAGS  = -fopenmp -O2 -Wall

TARGETS = hello_openmp parallel_for

.PHONY: all clean

all: $(TARGETS)

hello_openmp: hello_openmp.c
	$(CC) $(CFLAGS) -o $@ $<

parallel_for: parallel_for.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)
