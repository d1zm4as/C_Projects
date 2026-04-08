#include "sort_trace.h"
#include <stdlib.h>

static void trace_ensure_capacity(Trace *trace, int extra) {
    if (!trace) {
        return;
    }
    int needed = trace->count + extra;
    if (needed <= trace->capacity) {
        return;
    }
    int new_capacity = trace->capacity > 0 ? trace->capacity : 128;
    while (new_capacity < needed) {
        new_capacity *= 2;
    }
    Operation *new_ops = (Operation *)realloc(trace->ops, new_capacity * sizeof(Operation));
    if (!new_ops) {
        return;
    }
    trace->ops = new_ops;
    trace->capacity = new_capacity;
}

void trace_init(Trace *trace) {
    if (!trace) {
        return;
    }
    trace->ops = NULL;
    trace->count = 0;
    trace->capacity = 0;
}

void trace_reset(Trace *trace) {
    if (!trace) {
        return;
    }
    trace->count = 0;
}

void trace_free(Trace *trace) {
    if (!trace) {
        return;
    }
    free(trace->ops);
    trace->ops = NULL;
    trace->count = 0;
    trace->capacity = 0;
}

void trace_swap(Trace *trace, int *arr, int i, int j) {
    if (trace) {
        trace_ensure_capacity(trace, 1);
        if (trace->count < trace->capacity) {
            trace->ops[trace->count++] = (Operation){OP_SWAP, i, j, 0};
        }
    }
    if (arr) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void trace_write(Trace *trace, int *arr, int i, int value) {
    if (trace) {
        trace_ensure_capacity(trace, 1);
        if (trace->count < trace->capacity) {
            trace->ops[trace->count++] = (Operation){OP_WRITE, i, -1, value};
        }
    }
    if (arr) {
        arr[i] = value;
    }
}

void trace_compare(Trace *trace, int i, int j) {
    if (trace) {
        trace_ensure_capacity(trace, 1);
        if (trace->count < trace->capacity) {
            trace->ops[trace->count++] = (Operation){OP_COMPARE, i, j, 0};
        }
    }
}
