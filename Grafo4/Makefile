GPP=g++
GCCFLAGS=-g -std=c++11

%.o: %.cpp
	$(GPP) -c $(GCCFLAGS) $<

all: main.o graf.o 
	$(GPP) -o main main.o graf.o
	
clean:
	rm *.o main
