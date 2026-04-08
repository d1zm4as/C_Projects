#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include "sort_trace.h"

void bubbleSort(int arr[], int n, Trace *trace);
void InsertionSort(int array[], int tam, Trace *trace);
void selectionSort(int array[], int tam, Trace *trace);
void heapSort(int arr[], int N, Trace *trace);
void quickSort(int array[], int low, int high, Trace *trace);
void mergeSort(int arr[], int l, int r, Trace *trace);
void shellSort(int array[], int size, Trace *trace);
void countingSort(int array[], int size, int max_value, Trace *trace);
void radixSort(int array[], int size, Trace *trace);
void bucketSort(int array[], int size, Trace *trace);

#endif
