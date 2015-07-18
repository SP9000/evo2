LIBS  = -lm
CFLAGS = -shared -Wall -fPIC

SRC=$(wildcard *.c)

libevo2.so: $(SRC)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

test: 
	cd testing && $(MAKE)
	mv testing/test .

clean:
	rm libevo2.so
	rm test
	cd testing && $(MAKE) clean
