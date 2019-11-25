GPP=g++
GCCFLAGS=-g #-std=c++11

%.o: %.cpp
	$(GPP) -c  $(GCCFLAGS) $<

all: main.o MatriuSparse.o Tree.o
	$(GPP) -o main main.o MatriuSparse.o Tree.o
	
clean:
	rm *.o main
