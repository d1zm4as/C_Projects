CC ?= cc
CFLAGS ?= -Wall -Wextra -I.
LDFLAGS ?=

.PHONY: clean

all: dnscli


dnscli: dnscli.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

dnscli.o: dnscli.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o dnscli
