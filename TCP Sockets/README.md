# TCP Sockets (C)

Simple TCP client example in C.

## What it does

- Opens a TCP connection to a hardcoded IP on port `80`.
- Sends an HTTP `HEAD` request.
- Prints the received response headers.

## Build and run

```bash
gcc sockets.c -o sockets
./sockets
```

## Notes

The target IP is currently hardcoded in `sockets.c` (`#define IP ...`).
