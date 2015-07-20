LIBS  = -levo2 -lSDL2
CFLAGS = -Wall -L..

SRC=$(wildcard *.c) 

test: $(SRC)
	gcc -o $@ $(SRC) $(CFLAGS) $(LIBS)

clean:
	rm test
