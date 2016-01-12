LIBS  = -levo2 -lSDL2 -framework OpenGL -lglew
CFLAGS = -Wall -I.. -L..

SRC=$(wildcard *.c) 
CSRC=$(wildcard ../components/*.c) 
SSRC=$(wildcard ../systems/*.c)

test: $(SRC) $(CSRC) $(SSRC)
	gcc -o $@ $(SRC) $(CSRC) $(SSRC) $(CFLAGS) $(LIBS)

clean:
	rm test
