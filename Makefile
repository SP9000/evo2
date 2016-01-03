LIBS  = -lm -lSDL2 -lglew -framework OpenGL
CFLAGS = -shared -Wall -fPIC

SRC=$(wildcard *.c)
TESTSRC=$(wildcard testing/*.c)
BASECSRC=$(wildcard components/*.c) # base components for engine

libevo2.so: $(SRC) $(BASECSRC)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

test: $(TESTSRC) libevo2.so 
	cd testing && $(MAKE)
	mv testing/test .

clean:
	rm libevo2.so
	rm test
	cd testing && $(MAKE) clean
