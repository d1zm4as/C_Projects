#include "hex_dump.h"

void hex_dump(FILE *out, const uint8_t *data, size_t len, size_t bytes_per_line)
{
    size_t i;

    if (!out || !data || bytes_per_line == 0) {
        return;
    }

    for (i = 0; i < len; ++i) {
        if (i % bytes_per_line == 0) {
            fprintf(out, "%08zx  ", i);
        }

        fprintf(out, "%02X ", data[i]);

        if ((i + 1) % bytes_per_line == 0 || i + 1 == len) {
            size_t j;
            size_t line_start = i - (i % bytes_per_line);
            size_t line_end = i;

            fprintf(out, " ");
            for (j = line_start; j <= line_end; ++j) {
                uint8_t c = data[j];
                if (c >= 32 && c <= 126) {
                    fputc(c, out);
                } else {
                    fputc('.', out);
                }
            }
            fputc('\n', out);
        }
    }
}
