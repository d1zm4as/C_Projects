# TCP Server (C)

Minimal TCP server example in C.

## What it does

- Creates a TCP socket.
- Binds to `0.0.0.0:8181`.
- Accepts one incoming client connection.
- Reads up to 511 bytes and responds with `httpd v1.0`.

## Build and run

```bash
gcc server.c -o server
./server
```

Then connect from another terminal using `nc` or `telnet`.
