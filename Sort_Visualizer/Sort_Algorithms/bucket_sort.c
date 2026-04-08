#include "sort_trace.h"
#include <stdlib.h>
#include <math.h>

/*
Bucket sort for integers.
Uses buckets + insertion sort inside each bucket.
Writes are traced when rebuilding the array.
*/

typedef struct {
  int *data;
  int count;
  int capacity;
} IntBucket;

static void bucket_push(IntBucket *bucket, int value) {
  if (bucket->count >= bucket->capacity) {
    int new_capacity = bucket->capacity == 0 ? 8 : bucket->capacity * 2;
    int *next = (int *)realloc(bucket->data, new_capacity * sizeof(int));
    if (!next) {
      return;
    }
    bucket->data = next;
    bucket->capacity = new_capacity;
  }
  bucket->data[bucket->count++] = value;
}

static void bucket_insertion_sort(IntBucket *bucket) {
  for (int i = 1; i < bucket->count; i++) {
    int temp = bucket->data[i];
    int j = i;
    while (j > 0 && bucket->data[j - 1] > temp) {
      bucket->data[j] = bucket->data[j - 1];
      j--;
    }
    bucket->data[j] = temp;
  }
}

void bucketSort(int array[], int size, Trace *trace) {
  if (size <= 1) {
    return;
  }

  int min = array[0];
  int max = array[0];
  for (int i = 1; i < size; i++) {
    if (array[i] < min) min = array[i];
    if (array[i] > max) max = array[i];
  }

  int bucket_count = (int)sqrt((double)size);
  if (bucket_count < 1) bucket_count = 1;

  IntBucket *buckets = (IntBucket *)calloc(bucket_count, sizeof(IntBucket));
  if (!buckets) {
    return;
  }

  int range = max - min + 1;
  for (int i = 0; i < size; i++) {
    int normalized = array[i] - min;
    int index = (normalized * bucket_count) / range;
    if (index < 0) index = 0;
    if (index >= bucket_count) index = bucket_count - 1;
    bucket_push(&buckets[index], array[i]);
  }

  for (int i = 0; i < bucket_count; i++) {
    bucket_insertion_sort(&buckets[i]);
  }

  int idx = 0;
  for (int i = 0; i < bucket_count; i++) {
    for (int j = 0; j < buckets[i].count; j++) {
      trace_write(trace, array, idx, buckets[i].data[j]);
      idx++;
    }
    free(buckets[i].data);
  }

  free(buckets);
}
