CC=cc
CFLAGS=-O2 -std=c11 -Wall -Wextra -pedantic -D_POSIX_C_SOURCE=200809L

BIN=fib_bench
SRC=main.c bigint.c user_fib.c

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

clean:
	rm -f $(BIN)
