GPP=g++
GCCFLAGS=-g

%.o: %.cpp
	$(GPP) -c  $(GCCFLAGS) $<

all: main.o Operacions.o Racional.o
	$(GPP) -o main main.o Operacions.o Racional.o
	
clean:
	rm *.o main
