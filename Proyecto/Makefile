GPP=g++
GCCFLAGS=-g -std=c++11

%.o: %.cpp
	$(GPP) -c  $(GCCFLAGS) $<

all: main.o SimmetricMatrix.o MatriuDispersa.o 
	$(GPP) -o main main.o SimmetricMatrix.o MatriuDispersa.o
	
clean:
	rm *.o main
