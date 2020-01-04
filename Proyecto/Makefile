GPP=g++
GCCFLAGS=-g -std=c++11

%.o: %.cpp
	$(GPP) -c  $(GCCFLAGS) $<

all: main.o MatriuSparse.o Heap.o Comunitat.o Graph.o
	$(GPP) -o main main.o MatriuSparse.o Heap.o Comunitat.o Graph.o
	
clean:
	rm *.o main
