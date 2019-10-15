GPP=g++
GCCFLAGS=-g -std=c++11

%.o: %.cpp
	$(GPP) -c  $(GCCFLAGS) $<

all: main.o Matriu.o MatriuDispersa.o 
	$(GPP) -o main main.o Matriu.o MatriuDispersa.o
	
clean:
	rm *.o main
