GPP=g++
GCCFLAGS= -g

%.o: %.c
	$(GPP) -c $(GCCFLAGS) $<

all: main.o Poligon.o Punt.o
	$(GPP) -o main main.o Poligon.o Punt.o
	
clean:
	rm *.o main