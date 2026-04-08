#include "sort_trace.h"
#include <stdlib.h>

/*
Counting sort for non-negative integers.
Time: O(n + k) where k is max value.
*/

void countingSort(int array[], int size, int max_value, Trace *trace) {
  int *count = (int *)calloc(max_value + 1, sizeof(int));
  int *output = (int *)malloc(size * sizeof(int));

  for (int i = 0; i < size; i++) {
    count[array[i]]++;
  }

  for (int i = 1; i <= max_value; i++) {
    count[i] += count[i - 1];
  }

  for (int i = size - 1; i >= 0; i--) {
    output[count[array[i]] - 1] = array[i];
    count[array[i]]--;
  }

  for (int i = 0; i < size; i++) {
    trace_write(trace, array, i, output[i]);
  }

  free(count);
  free(output);
}
