#ifndef MODBUS_RTU_H
#define MODBUS_RTU_H

#include <stddef.h>
#include <stdint.h>

size_t modbus_rtu_build_read_holding(uint8_t slave, uint16_t start_addr,
                                     uint16_t quantity, uint8_t *out,
                                     size_t out_size);

int modbus_rtu_parse_read_holding_response(const uint8_t *frame, size_t len,
                                           uint8_t *out_bytes, size_t out_size,
                                           size_t *out_len);

#endif
