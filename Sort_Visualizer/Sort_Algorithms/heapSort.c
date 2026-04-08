#include "sort_trace.h"

/*

Dado o array,

int array[] = {2,0,9,8,1,5,4,3,15,7};

Esse array pode ser reprensentada como uma árovere binária


ex:                                            
                                (2)
                               /   \
                              /     \
                            (0)     (9)
                           /  \      /  \
                          /   (1)   (5)  (4)
                        (8)   / 
                        / \  (7)
                      /    \
                    (3)    (15)



A regra é seguinte o nó pai, vai ter um filho esquerda com o index(2i+1) e pra direita com (2i+2)

ex:

o nó pai (2) tem o index(0) ele vai ter um filho pra direita seguindo regra(2i+2, 2(0)+2 = array[2], 9)

o nó pai (2) tem o index(0) ele vai ter um filho pra esquerda seguindo regra(2i+1, 2(0)+1 = array[1], 0)

e a mesma lógica vai ser aplicada para o resto dos nós 


heap -> é uma árvore binária que obedece as seguintes condições ->

1 - Todos os níveis com execessão do ultimo estão cheios

2 - os valores dos nós pais não são menores que os valores do nós filhos




*/


static void swap_int(int arr[], int i, int j, Trace *trace)
{
    trace_swap(trace, arr, i, j);
}


static void heapify(int arr[], int N, int i, Trace *trace)
{
    
    int largest = i;

    
    int left = 2 * i + 1;

    
    int right = 2 * i + 2;

    
    if (left < N) {
        trace_compare(trace, left, largest);
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }

    if (right < N) {
        trace_compare(trace, right, largest);
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }

    
    if (largest != i) {

        swap_int(arr, i, largest, trace);

        
        heapify(arr, N, largest, trace);
    }
}

void heapSort(int arr[], int N, Trace *trace)
{

    for (int i = N / 2 - 1; i >= 0; i--)

        heapify(arr, N, i, trace);

    for (int i = N - 1; i >= 0; i--) {

        swap_int(arr, 0, i, trace);

        heapify(arr, i, 0, trace);
    }
}
