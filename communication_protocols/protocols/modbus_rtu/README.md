# Modbus RTU Read Holding Registers Example

Builds a Modbus RTU request (function `0x03`) and parses a mock response.

## Build

From `protocols/modbus_rtu/`:

```bash
gcc -Iinclude -I../../common src/modbus_rtu.c src/modbus_example.c \
  ../../common/crc16.c ../../common/hex_dump.c -o modbus_example
```

## Run

```bash
./modbus_example
```
