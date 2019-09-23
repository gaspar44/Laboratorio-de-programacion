GPP=g++
GCCFLAGS=-g

%.o: %.cpp
	$(GPP) -c  $(GCCFLAGS) $<

all: main.o Hora.o 
	$(GPP) -o main main.o Hora.o
	
clean:
	rm *.o main
