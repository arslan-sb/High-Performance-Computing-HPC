NVCC      = nvcc
# Override SM on the command line: make SM=sm_89
SM        ?= sm_75
NVCCFLAGS = -O2 -arch=$(SM)

TARGETS = hello_gpu vector_addition

.PHONY: all clean

all: $(TARGETS)

hello_gpu: hello_gpu.cu
	$(NVCC) $(NVCCFLAGS) -o $@ $<

vector_addition: vector_addition.cu
	$(NVCC) $(NVCCFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)
