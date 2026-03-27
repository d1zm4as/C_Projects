#ifndef HEX_DUMP_H
#define HEX_DUMP_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void hex_dump(FILE *out, const uint8_t *data, size_t len, size_t bytes_per_line);

#endif
