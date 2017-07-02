APPNAME := bin/program
SOURCES := $(wildcard src/*.cpp src/*.cu src/*.c)
OBJECTS := $(patsubst src%,obj%, $(patsubst %.cu,%.device.o, $(patsubst %.cpp,%.o, $(patsubst %.c,%.o, $(SOURCES)))))

INCLUDE := -I/usr/include
LIBPATH := -L/usr/lib
LIBS    := 

FLAGS    := -Wall 
CCFLAGS  := $(FLAGS)
CXXFLAGS := $(FLAGS) -std=c++11
FFLAGS   := -lSDL2main -lSDL2

GENCODE_FLAGS := -gencode arch=compute_20,code=sm_20 -gencode arch=compute_30,code=sm_30 -gencode
arch=compute_35,code=sm_35
NVCCFLAGS     := $(GENCODE_FLAGS) --compiler-options -fno-strict-aliasing -lineinfo -use_fast_math -Xptxas -dlcm=cg

CC   := gcc
CXX  := g++
NVCC := /usr/local/cuda/bin/nvcc

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	$(CCFLAGS) += -framework OpenGL
endif

ifeq ($(UNAME_S),Darwin)
        FFLAGS += -framework OpenGL
    endif

all: $(OBJECTS)
	$(CC) $(OBJECTS) $(CCFLAGS) $(INCLUDE) $(LIBPATH) -o $(APPNAME)  $(LIBS)

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

opengl:	$(OBJECTS)
	$(CC) $(OBJECTS) $(CCFLAGS) $(FFLAGS) $(INCLUDE) $(LIBPATH) -o $(APPNAME)  $(LIBS)

trgl:
	$(CC) $(CCFLAGS) $(INCLUDE) -D TRGL_MODE -c src/TRGL/TRGL.c -o src/TRGL/TRGL.o
	$(CC) $(CCFLAGS) $(INCLUDE) -D TRGL_MODE -c src/logic.c -o obj/logic.o
	$(CC) $(CCFLAGS) $(INCLUDE) -D TRGL_MODE -c src/main.c  -o obj/main.o
	$(CC) $(OBJECTS) src/TRGL/TRGL.o $(CCFLAGS) -DTRGL_MODE -lSDL2main -lSDL2 $(INCLUDE) $(LIBPATH) -o $(APPNAME)  $(LIBS)
clean:
	rm -rf obj/*
	rm -f $(APPNAME)
run:
	./bin/program
