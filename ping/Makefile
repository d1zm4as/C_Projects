flags = -O2 -Wall -std=c2x
ldflags = -lbu

.PHONY: all clean

all: clean ping

ping: ping.o
	cc $(flags) $^ -o $@ $(ldflags)

ping.o: ping.C ping.H
	cc $(flags) -c $<

clean:
	rm -f *.o ping
