GPP=g++
GCCFLAGS=-g -std=c++11

%.o: %.cpp
	$(GPP) -c  $(GCCFLAGS) $<

all: main.o Persona.o 
	$(GPP) -o main main.o Persona.o
	
clean:
	rm *.o main
