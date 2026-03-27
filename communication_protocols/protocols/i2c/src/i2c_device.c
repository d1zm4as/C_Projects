#include "i2c_device.h"

int i2c_write_reg(i2c_bus_t *bus, uint8_t addr, uint8_t reg,
                  const uint8_t *data, size_t len)
{
    uint8_t buffer[1 + 32];

    if (!bus || !bus->write || (!data && len > 0) || len > 32) {
        return -1;
    }

    buffer[0] = reg;
    for (size_t i = 0; i < len; ++i) {
        buffer[1 + i] = data[i];
    }

    return bus->write(addr, buffer, 1 + len, bus->ctx);
}

int i2c_read_reg(i2c_bus_t *bus, uint8_t addr, uint8_t reg,
                 uint8_t *data, size_t len)
{
    if (!bus || !bus->write || !bus->read || !data) {
        return -1;
    }

    if (bus->write(addr, &reg, 1, bus->ctx) != 0) {
        return -1;
    }

    return bus->read(addr, data, len, bus->ctx);
}
