CC      = mpicc
CFLAGS  = -O2 -Wall

TARGETS = hello_mpi scatter_gather

.PHONY: all clean

all: $(TARGETS)

hello_mpi: hello_mpi.c
	$(CC) $(CFLAGS) -o $@ $<

scatter_gather: scatter_gather.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)
