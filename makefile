APPNAME := bin/program
SOURCES := $(wildcard src/*.cpp src/*.cu src/*.c)
OBJECTS := $(patsubst src%,obj%, $(patsubst %.cu,%.device.o, $(patsubst %.cpp,%.o, $(patsubst %.c,%.o, $(SOURCES)))))

INCLUDE := -I/usr/include
LIBPATH := -L/usr/lib
LIBS    := 

FLAGS    := -Wall -lSDL2main -lSDL2
CCFLAGS  := $(FLAGS)
CXXFLAGS := $(FLAGS) -std=c++11

GENCODE_FLAGS := -gencode arch=compute_20,code=sm_20 -gencode arch=compute_30,code=sm_30 -gencode
arch=compute_35,code=sm_35
NVCCFLAGS     := $(GENCODE_FLAGS) --compiler-options -fno-strict-aliasing -lineinfo -use_fast_math -Xptxas -dlcm=cg

CC   := gcc
CXX  := g++
NVCC := /usr/local/cuda/bin/nvcc

all: $(OBJECTS)
	$(CXX) $(OBJECTS) $(CCFLAGS) $(INCLUDE) $(LIBPATH) -o $(APPNAME)  $(LIBS)

ojj/cmdline.o: src/cmdline.c
	$(CC) -Wno-unused-but-set-variable -c $< -o $@

src/cmdline.c: src/cmdline.ggo
	gengetopt --input=src/cmdline.ggo --output-dir=src --include-getopt

%.o: ../src/%.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

%.o: ../src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

%.device.o: ../src/%.cu
	$(NVCC) $(NVCCFLAGS) -c $< -o $@

clean:
	rm -rf obj/*
	rm -f $(APPNAME)

