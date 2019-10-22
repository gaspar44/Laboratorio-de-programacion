GPP=g++
GCCFLAGS=-g -std=c++11

%.o: %.cpp
	$(GPP) -c $(GCCFLAGS) $<

all: main.o Hash.o
	$(GPP) -o main main.o Hash.o
	
clean:
	rm *.o main
