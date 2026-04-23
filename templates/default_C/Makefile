flags = -O2 -Wall -std=c2x
ldflags = -lbu

.PHONY: all clean

all: clean PROJECTNAME

PROJECTNAME: PROJECTNAME.o
	cc $(flags) $^ -o $@ $(ldflags)

PROJECTNAME.o: PROJECTNAME.C PROJECTNAME.H
	cc $(flags) -c $<

clean:
	rm -f *.o PROJECTNAME