#include "i2c_device.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    uint8_t regs[256];
    uint8_t current_reg;
} mock_device_t;

static int mock_write(uint8_t addr, const uint8_t *data, size_t len, void *ctx)
{
    mock_device_t *dev = (mock_device_t *)ctx;

    (void)addr;

    if (!dev || !data || len == 0) {
        return -1;
    }

    dev->current_reg = data[0];
    if (len > 1) {
        size_t payload_len = len - 1;
        for (size_t i = 0; i < payload_len; ++i) {
            dev->regs[(uint8_t)(dev->current_reg + i)] = data[1 + i];
        }
        dev->current_reg = (uint8_t)(dev->current_reg + payload_len);
    }

    return 0;
}

static int mock_read(uint8_t addr, uint8_t *data, size_t len, void *ctx)
{
    mock_device_t *dev = (mock_device_t *)ctx;

    (void)addr;

    if (!dev || !data) {
        return -1;
    }

    for (size_t i = 0; i < len; ++i) {
        data[i] = dev->regs[dev->current_reg++];
    }

    return 0;
}

int main(void)
{
    mock_device_t device;
    i2c_bus_t bus;
    uint8_t read_back[4];

    memset(&device, 0, sizeof(device));

    bus.write = mock_write;
    bus.read = mock_read;
    bus.ctx = &device;

    if (i2c_write_reg(&bus, 0x50, 0x10, (uint8_t[]){ 0xDE, 0xAD, 0xBE, 0xEF }, 4) != 0) {
        printf("Write failed\n");
        return 1;
    }

    if (i2c_read_reg(&bus, 0x50, 0x10, read_back, sizeof(read_back)) != 0) {
        printf("Read failed\n");
        return 1;
    }

    printf("Read back: ");
    for (size_t i = 0; i < sizeof(read_back); ++i) {
        printf("%02X ", read_back[i]);
    }
    printf("\n");

    return 0;
}
