# MQTT Packet Encoding Example

Encodes basic MQTT packets (CONNECT and PINGREQ) without sockets.

## Build

From `protocols/mqtt/`:

```bash
gcc -Iinclude -I../../common src/mqtt_simple.c src/mqtt_example.c \
  ../../common/hex_dump.c -o mqtt_example
```

## Run

```bash
./mqtt_example
```
