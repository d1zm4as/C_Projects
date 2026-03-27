# TCP Echo Example

Minimal TCP echo server and client using POSIX sockets.

## Build

From `protocols/tcp/`:

```bash
gcc src/tcp_echo_server.c -o tcp_echo_server
gcc src/tcp_echo_client.c -o tcp_echo_client
```

## Run

In one terminal:

```bash
./tcp_echo_server 9001
```

In another terminal:

```bash
./tcp_echo_client 127.0.0.1 9001 "hello"
```
