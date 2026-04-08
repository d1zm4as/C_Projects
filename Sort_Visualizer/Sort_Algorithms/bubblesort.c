#include "sort_trace.h"


/*
O algoritimo funciona comparando os items adjacentes do a, o que tende a jogar os items maiores para o lado direito(fim) e os menores para a esquerda.

ex:


int a[] = {8,4,5,6,0,2,1};

bubbleSort(a);

1º comparar o int a[n] com o item a[n+1], no caso o 8 com o 4, 8>4 então os lugares serão trocados
int a[] = {4,8,5,6,0,2,1};
2º Agora será comparado o 8 com o 5. 8>5, então os lugares serão trocados
int a[] = {4,5,8,6,0,2,1};

3º A mesma lógica será usada para todos os elementos que se encaixam no padrão elemento x<8.
int a[] = {4,5,6,0,2,1,8}; -> o item 8 ja está em ordem !ent a gente volta pro começo.

4º int a[] = {4,5,6,0,2,1,8};, o item a[n], no caso 4 ja está em ordem em comparação com o item a[n+1], ent o item a[n](o item inicial de comparação) será o 5

5º O mesmo comportamento se repete , o item a[n], no caso 4 ja está em ordem em comparação com o item a[n+1]
int a[] = {4,5,6,0,2,1,8};

indo um pouco mais rápido ->
int a[] = {4,5,0,6,2,1,8};
int a[] = {4,5,0,2,6,1,8};
int a[] = {4,5,0,2,1,6,8}; -> o 6 está ordenado em comparação ao 8(6<8) e o 8 é o último num da lista
int a[] = {4,0,5,2,1,6,8};
int a[] = {4,0,2,5,1,6,8};
int a[] = {4,0,2,1,5,6,8}; -> o 5 está ordenado em comparação ao 6(5<6),o 6 está ordenado em comparação ao 8(6<8) e o 8 é o último num da lista
int a[] = {0,4,2,1,5,6,8};
int a[] = {0,2,4,1,5,6,8};
int a[] = {0,2,1,4,5,6,8};
int a[] = {0,2,1,4,5,6,8};
int a[] = {0,1,2,4,5,6,8}; -> fim da ordenação

O(n²),percorre muitas vezes o mesmo a,todo processo é muito redundante, Não é eficiente, existem outras formas de organização de as que são O(log n), que são bem mais rápidos.

*/

// C program for implementation of Bubble sort

 
static void swap_int(int arr[], int i, int j, Trace *trace)
{
    trace_swap(trace, arr, i, j);
}

// A function to implement bubble sort
void bubbleSort(int arr[], int n, Trace *trace)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++) {
            trace_compare(trace, j, j + 1);
            if (arr[j] > arr[j + 1]) {
                swap_int(arr, j, j + 1, trace);
            }
        }
}
