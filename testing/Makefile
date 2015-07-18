LIBS  = -levo2
CFLAGS = -Wall -L..

SRC=$(wildcard *.c)

test: $(SRC) 
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm test
