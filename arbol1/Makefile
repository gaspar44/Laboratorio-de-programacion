GPP=g++
GCCFLAGS=-g #-std=c++11

%.o: %.cpp
	$(GPP) -c  $(GCCFLAGS) $<

all: main.o Data.o Tasca.o
	$(GPP) -o main main.o Data.o Tasca.o
	
clean:
	rm *.o main
