#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

#include <stddef.h>
#include <stdint.h>

typedef int (*i2c_write_fn)(uint8_t addr, const uint8_t *data, size_t len, void *ctx);
typedef int (*i2c_read_fn)(uint8_t addr, uint8_t *data, size_t len, void *ctx);

typedef struct {
    i2c_write_fn write;
    i2c_read_fn read;
    void *ctx;
} i2c_bus_t;

int i2c_write_reg(i2c_bus_t *bus, uint8_t addr, uint8_t reg,
                  const uint8_t *data, size_t len);

int i2c_read_reg(i2c_bus_t *bus, uint8_t addr, uint8_t reg,
                 uint8_t *data, size_t len);

#endif
