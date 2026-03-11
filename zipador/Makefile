flags = -O2 -Wall -std=c2x
ldflags =

.PHONY: all clean

all: clean zipador

zipador: zipador.o
	cc $(flags) $^ -o $@ $(ldflags)

zipador.o: zipador.c zipador.h
	cc $(flags) -c $<

clean:
	rm -f *.o zipador
