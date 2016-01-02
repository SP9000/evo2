LIBS  = -levo2 -lSDL2
CFLAGS = -Wall -L..

SRC=$(wildcard *.c) 
CSRC=$(wildcard ../components/*.c) 
SSRC=$(wildcard ../systems/*.c)

test: $(SRC) $(CSRC) $(SSRC)
	gcc -o $@ $(SRC) $(CSRC) $(SSRC) $(CFLAGS) $(LIBS)

clean:
	rm test
