# I2C Register Access Example

This example models a register-based I2C device with helper functions:

- `i2c_write_reg` writes a register and payload
- `i2c_read_reg` writes a register address, then reads back bytes

## Build

From `protocols/i2c/`:

```bash
gcc -Iinclude src/i2c_device.c src/i2c_example.c -o i2c_example
```

## Run

```bash
./i2c_example
```
