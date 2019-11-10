GPP=g++
GCCFLAGS=-g -std=c++11

%.o: %.cpp
	$(GPP) -c $(GCCFLAGS) $<

all: main.o GrafList.o 
	$(GPP) -o main main.o GrafList.o
	
clean:
	rm *.o main
