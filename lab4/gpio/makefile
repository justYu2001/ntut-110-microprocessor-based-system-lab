.PHONY: all clean

CROSS_COMPILE = aarch64-linux-gnu-
CXX = $(CROSS_COMPILE)g++
CXXFLAGS = -std=c++11

HEADER = gpio.h
SRC = gpio.cpp
OBJ = gpio.o
EXE = gpio

all:clean $(OBJ)
	$(CXX) $(OBJ) main.cpp -o $(EXE)

%.o:%.c
	$(CXX) -c $< -o $@

clean:
	rm -f *.o
	rm -f $(EXE)