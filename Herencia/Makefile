GPP=g++
GCCFLAGS=-g -std=c++11

%.o: %.cpp
	$(GPP) -c  $(GCCFLAGS) $<

all: main.o Biblioteca.o Book.o Borrow.o Data.o Magazine.o Publicacio.o
	$(GPP) -o main main.o Biblioteca.o Book.o Borrow.o Data.o Magazine.o Publicacio.o
	
clean:
	rm *.o main
