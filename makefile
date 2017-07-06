APPNAME := bin/program
SOURCES := $(wildcard src/*.cpp src/*.cu src/*.c)
OBJECTS := $(patsubst src%,obj%, $(patsubst %.cu,%.device.o, $(patsubst %.cpp,%.o, $(patsubst %.c,%.o, $(SOURCES)))))

INCLUDE := 
LIBPATH := 
LIBS    := 

FLAGS    := -Wall 
CCFLAGS  := $(FLAGS)
GLFLAGS  := 
CXXFLAGS := $(FLAGS) -std=c++11

GENCODE_FLAGS := -gencode arch=compute_20,code=sm_20 -gencode arch=compute_30,code=sm_30 -gencode
arch=compute_35,code=sm_35
NVCCFLAGS     := $(GENCODE_FLAGS) --compiler-options -fno-strict-aliasing -lineinfo -use_fast_math -Xptxas -dlcm=cg

CC   := gcc
CXX  := g++
NVCC := /usr/local/cuda/bin/nvcc

UNAME_S := $(shell uname -s)
ifeq ($(OS),Windows_NT)
	CCFLAGS += -D WIN32 -lopengl32 -lmingw32 -lSDL2main -lSDL2
	INCLUDE += -Iinclude/
	LIBPATH += -Llib/
	APPNAME = bin/program.exe
	CC = mingw32-gcc.exe
	CXX = mingw32-g++.exe
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        CCFLAGS += -D AMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            CCFLAGS += -D AMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            CCFLAGS += -D IA32
        endif
    endif
else
    ifeq ($(UNAME_S),Linux)
        CCFLAGS += -D LINUX
	GLFLAGS += -lGL -lGLU -lSDL2main -lSDL2
	INCLUDE += -I/usr/include
	LIBPATH += -L/usr/share
    endif
    ifeq ($(UNAME_S),Darwin)
        CCFLAGS += -D OSX -lSDL2 -lSDL2main
	GLFLAGS += -framework OpenGL
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        CCFLAGS += -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CCFLAGS += -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CCFLAGS += -D ARM
    endif
endif


trgl:
	$(CC) $(INCLUDE) -g -D TRGL_MODE -c src/TRGL/TRGL.c -o src/TRGL/TRGL.o
	$(CC) $(INCLUDE) -g -D TRGL_MODE -c src/main.c  -o obj/main.o
	$(CC) $(OBJECTS) -g src/TRGL/TRGL.o $(CCFLAGS) -DTRGL_MODE -lSDL2main -lSDL2 $(INCLUDE) $(LIBPATH) -o $(APPNAME)  $(LIBS)

%.o: ../src/%.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

%.o: ../src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

%.device.o: ../src/%.cu
	$(NVCC) $(NVCCFLAGS) -c $< -o $@

opengl:
#	$(CC) $(INCLUDE) -g -c src/logic.c -o obj/logic.o
	$(CC) $(INCLUDE) -g -c src/main.c  -o obj/main.o
	$(CC) $(OBJECTS) -g $(CCFLAGS) $(GLFLAGS) $(INCLUDE) $(LIBPATH) -o $(APPNAME)  $(LIBS)

clean:
	rm -rf obj/*
	rm -f $(APPNAME)
cleanwindows:
	del obj\main.o
	del obj\logic.o
	del $(APPNAME)
run:
	./bin/program
