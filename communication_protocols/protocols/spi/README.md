# SPI Command Packet Example

Simple packet format:

- Sync: `0xA5`
- Command: 1 byte
- Length: 1 byte
- Payload: `N` bytes
- Checksum: XOR of Command + Length + Payload

## Build

From `protocols/spi/`:

```bash
gcc -Iinclude src/spi_protocol.c src/spi_example.c -o spi_example
```

## Run

```bash
./spi_example
```
