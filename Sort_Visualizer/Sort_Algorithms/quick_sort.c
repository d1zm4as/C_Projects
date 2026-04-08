#include "sort_trace.h"

/*
int a[] = {4,9,8,3,6,1,0};

pivot = 3, o item do meio (que a mediana aritmetica)

A ordenação funciona com o uso de duas variáveis, uma pela esquerda(satisfazendo a condição de ser menor doq o pivot, caso contrario a variavel precisa ser alterada) e outra para direita(satisfazendo a condição de ser maior doq o pivot, caso contrario a variavel precisa ser alterada)

int a[] = {4,9,8,3,6,1,0};


esq = a[0] == 4, é maior doq o pivot 3, então precisa ser trocada
dir = a[6]== 0, é menor doq o pivot 3, então precisa ser trocada
ex= a[0] e a[6], logo 4 e 0, respectivamente, o a[6] é maior doq o pivot e o a [0] é menor ou igual, logo o valor das  posições serão trocadas.

1! - int a[] = {0,9,8,3,6,1,4}; apos a a troca tanto a variavel esq quanto a varial dir satisfazem as condições estabelecidas, logo ambas avançam mais em direção ao pivot

esq = a[1] == 9, é maior doq o pivot 3, então precisa ser trocada
dir = a[5]== 1, é menor doq o pivot 3, então precisa ser trocada
ex= a[1] e a[5], logo 9 e 1  respectivamente, o a[1] é maior doq o pivot e o a [5] é menor ou igual, logo o valor das  posições serão trocadas.

2! - int a[] = {0,1,8,3,6,9,4}; apos a a troca tanto a variavel e  quanto a varial dir satisfazem as condições estabelecidas, logo ambas avançam mais em direção ao pivot

esq = a[2] == 8, é maior doq o pivot 3, então precisa ser trocada
dir = a[4]== 6, é maior doq o pivot 3, então a variavel dir segue em direção ao pivot
dir = a[3]==3, dir assume o valor do pivot
ex= a[2] e a[3], logo 8 e 3  respectivamente, o a[2] é maior doq o pivot e o a [3] é menor ou igual, logo o valor das  posições serão trocadas.

3! - int a[] = {0,1,3,8,6,9,4}; apos as trocar pode-se assumir que não há mais valores para serem trocadas na parte esqueda do array(a[i] <=pivot)

{8,6,9,4} sobra esse sub-array para ser ordenado, a mesma logica de ordenação vai ser usada neste sub-array





*/



static void swap_int(int array[], int i, int j, Trace *trace) {
  trace_swap(trace, array, i, j);
}

static int partition(int array[], int low, int high, Trace *trace) {
  
  int pivot = array[high];
  
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    trace_compare(trace, j, high);
    if (array[j] <= pivot) {
        
      i++;
      
      swap_int(array, i, j, trace);
    }
  }

  swap_int(array, i + 1, high, trace);
  
  return (i + 1);
}

void quickSort(int array[], int low, int high, Trace *trace) {
  if (low < high) {
    
    int pi = partition(array, low, high, trace);
    
    quickSort(array, low, pi - 1, trace);
    
    quickSort(array, pi + 1, high, trace);
  }
}
