PLATFORM = sdl
LIBS  = -lm -lSDL2 -lglew -framework OpenGL
INCLUDE = -I. -Icomponents -Isystems
CFLAGS = -shared -Wall -fPIC --std=c11

SRC=$(wildcard *.c)
TESTSRC=$(wildcard testing/*.c)
BASECSRC=$(wildcard components/*.c) # base components for engine
PLATSRC=$(wildcard platform/$(PLATFORM)/*.c) # platform specific source

libevo2.so: $(SRC) $(BASECSRC) $(PLATSRC)
	gcc -o $@ $^ $(CFLAGS) $(INCLUDE) $(LIBS)

test: $(TESTSRC) libevo2.so 
	cd testing && $(MAKE)
	mv testing/test .

clean:
	rm libevo2.so
	rm test
	cd testing && $(MAKE) clean
