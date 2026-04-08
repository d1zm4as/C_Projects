#include "sort_trace.h"

/*
Radix sort (LSD) for non-negative integers.
Uses counting sort per digit.
*/

static int getMax(int array[], int size) {
  int max = array[0];
  for (int i = 1; i < size; i++) {
    if (array[i] > max) {
      max = array[i];
    }
  }
  return max;
}

static void countingSortByDigit(int array[], int size, int exp, Trace *trace) {
  int output[size];
  int count[10] = {0};

  for (int i = 0; i < size; i++) {
    int digit = (array[i] / exp) % 10;
    count[digit]++;
  }

  for (int i = 1; i < 10; i++) {
    count[i] += count[i - 1];
  }

  for (int i = size - 1; i >= 0; i--) {
    int digit = (array[i] / exp) % 10;
    output[count[digit] - 1] = array[i];
    count[digit]--;
  }

  for (int i = 0; i < size; i++) {
    trace_write(trace, array, i, output[i]);
  }
}

void radixSort(int array[], int size, Trace *trace) {
  int max = getMax(array, size);
  for (int exp = 1; max / exp > 0; exp *= 10) {
    countingSortByDigit(array, size, exp, trace);
  }
}
