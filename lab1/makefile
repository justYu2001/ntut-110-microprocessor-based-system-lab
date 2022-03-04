.PHONY: all clean

CROSS_COMPILE = aarch64-linux-gnu-
CXX = $(CROSS_COMPILE)g++
CXXFLAGS = -std=c++11

HEADER = circular_sector.h ellipse.h sort.h triangle.h
SRC = circular_sector.cpp ellipse.cpp sort.cpp triangle.cpp
OBJ = circular_sector.o ellipse.o sort.o triangle.o
EXE = lab1

all:clean $(OBJ)
	$(CXX) $(OBJ) main.cpp -o $(EXE)
%.o:%.c
	$(CXX) -c $< -o $@

clean:
	rm -f *.o
	rm -f $(EXE)