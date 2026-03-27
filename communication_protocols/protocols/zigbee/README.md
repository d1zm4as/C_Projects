# Zigbee APS Frame Example

This is a simplified APS data frame serializer (not a full Zigbee stack).

Format used in this example:

- Destination Endpoint (1 byte)
- Cluster ID (2 bytes, little-endian)
- Profile ID (2 bytes, little-endian)
- Source Endpoint (1 byte)
- Payload (0-64 bytes)

## Build

From `protocols/zigbee/`:

```bash
gcc -Iinclude -I../../common src/zigbee_aps.c src/zigbee_example.c \
  ../../common/hex_dump.c -o zigbee_example
```

## Run

```bash
./zigbee_example
```
