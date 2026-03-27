# UDP Echo Example

Small UDP echo server and client using POSIX sockets.

## Build

From `protocols/udp/`:

```bash
gcc src/udp_echo_server.c -o udp_echo_server
gcc src/udp_echo_client.c -o udp_echo_client
```

## Run

In one terminal:

```bash
./udp_echo_server 9000
```

In another terminal:

```bash
./udp_echo_client 127.0.0.1 9000 "hello"
```
