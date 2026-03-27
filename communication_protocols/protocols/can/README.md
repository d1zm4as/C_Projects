# CAN Frame Serialization Example

This is a user-space serialization example for a standard 11-bit CAN ID.
It packs data as: ID (2 bytes), DLC (1 byte), DATA (0-8 bytes).

## Build

From `protocols/can/`:

```bash
gcc -Iinclude -I../../common src/can_frame.c src/can_example.c \
  ../../common/hex_dump.c -o can_example
```

## Run

```bash
./can_example
```
