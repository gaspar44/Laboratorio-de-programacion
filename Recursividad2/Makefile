GPP=g++
GCCFLAGS=-g -std=c++11

%.o: %.cpp
	$(GPP) -c $(GCCFLAGS) $<

all: main.o Exercici2.o 
	$(GPP) -o main main.o Exercici2.o
	
clean:
	rm *.o main
