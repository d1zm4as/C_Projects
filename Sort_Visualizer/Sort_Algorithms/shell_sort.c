#include "sort_trace.h"

/*
Shell sort using gap sequence n/2, n/4, ... , 1.
*/

void shellSort(int array[], int size, Trace *trace) {
  for (int gap = size / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < size; i++) {
      int temp = array[i];
      int j = i;
      while (j >= gap) {
        trace_compare(trace, j - gap, j);
        if (array[j - gap] <= temp) {
          break;
        }
        trace_write(trace, array, j, array[j - gap]);
        j -= gap;
      }
      trace_write(trace, array, j, temp);
    }
  }
}
