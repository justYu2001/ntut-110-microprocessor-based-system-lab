.PHONY: all clean

CROSS_COMPILE = aarch64-linux-gnu-
CXX = $(CROSS_COMPILE)g++
CXXFLAGS = -std=c++11

EXE = L2Program

all:clean $(OBJ)
	$(CXX) -o $(EXE) lab2_1.cpp

clean:
	rm -f $(EXE)