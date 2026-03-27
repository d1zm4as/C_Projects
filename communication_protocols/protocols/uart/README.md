# UART Framing Example

This example defines a simple UART frame:

- Start-of-frame: `0x7E`
- Length: 1 byte
- Payload: `N` bytes
- CRC-16 (IBM): 2 bytes (LSB first), calculated over the payload

## Build

From `protocols/uart/`:

```bash
gcc -Iinclude -I../../common src/uart_framing.c src/uart_example.c \
  ../../common/crc16.c ../../common/hex_dump.c -o uart_example
```

## Run

```bash
./uart_example
```
