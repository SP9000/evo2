LIBS  = -levo2 -lSDL2
CFLAGS = -Wall -L..

SRC=$(wildcard *.c) 

test: $(SRC) 
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm test
