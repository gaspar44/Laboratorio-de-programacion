GPP=g++
GCCFLAGS=-g -std=c++11

%.o: %.cpp
	$(GPP) -c  $(GCCFLAGS) $<

all: main.o Tramesa.o Exercici.o LliuramentsEstudiant.o 
	$(GPP) -o main main.o Tramesa.o Exercici.o LliuramentsEstudiant.o 
	
clean:
	rm *.o main
