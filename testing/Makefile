LIBS  = -levo2 -lSDL2
CFLAGS = -Wall -L..

SRC=$(wildcard *.c) 
CSRC=$(wildcard ../components/*.c) 

test: $(SRC) $(CSRC)
	gcc -o $@ $(SRC) $(CSRC) $(CFLAGS) $(LIBS)

clean:
	rm test
