#ifndef SORT_TRACE_H
#define SORT_TRACE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    OP_SWAP,
    OP_WRITE,
    OP_COMPARE
} OpType;

typedef struct {
    OpType type;
    int i;
    int j;
    int value;
} Operation;

typedef struct {
    Operation *ops;
    int count;
    int capacity;
} Trace;

void trace_init(Trace *trace);
void trace_reset(Trace *trace);
void trace_free(Trace *trace);
void trace_swap(Trace *trace, int *arr, int i, int j);
void trace_write(Trace *trace, int *arr, int i, int value);
void trace_compare(Trace *trace, int i, int j);

#ifdef __cplusplus
}
#endif

#endif
