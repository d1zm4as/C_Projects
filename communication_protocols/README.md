# Communication Protocols (C)

A small collection of communication protocol notes and C implementations.

## Structure

- `common/` shared utilities (CRC, ring buffer, hex dump)
- `protocols/uart/` UART framing example
- `protocols/spi/` SPI command/response framing example
- `protocols/i2c/` I2C device access example
- `protocols/udp/` UDP echo client/server (POSIX sockets)
- `protocols/tcp/` TCP echo client/server (POSIX sockets)
- `protocols/can/` CAN frame serialization example
- `protocols/modbus_rtu/` Modbus RTU read holding registers example
- `protocols/mqtt/` MQTT packet encoding example
- `protocols/zigbee/` Zigbee APS frame serialization example

## Build (examples)

Each protocol folder contains a README with a simple compile command.
There is also a top-level Makefile for building all examples at once.

## Notes

These are minimal, educational examples and not production drivers.
