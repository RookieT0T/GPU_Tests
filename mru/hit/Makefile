HIPOPTS = --amdgpu-target=gfx900,gfx906 --save-temps

HIP_PATH ?= /opt/rocm/hip

CC := $(HIP_PATH)/bin/hipcc

SRC = hit.cpp

EXE = hit


release:
	$(CC) $(HIPOPTS) $(SRC) -o $(EXE) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *.o *~ $(EXE)

run:
	./$(EXE)

profile:
	rocprof ./$(EXE)

events:
	rocprof  --events elapsed_cycles_sm ./$(EXE)
