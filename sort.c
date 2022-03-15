#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*imprimir a lista inteira*/
void print_lista(int max, int lista[])
{
    for(int i = 0; i < max; i++)
        printf("%d ", lista[i]);
}

/*trocar dois elementos da lista*/
void troca(int lista[], int x, int y)
{
    int aux = lista[x];
    lista[x] = lista[y];
    lista[y] = aux;
}

/*insertion sort*/
void insertion_sort(int max, int lista[])
{
    int aux, j;
    for(int i = 1; i < max; i++) {
        aux = lista[i];
        j = i;
        while(j > 0 && lista[j-1] > aux) {
            lista[j] = lista[j-1];
            j--;
        }
        lista[j] = aux;
    }
}

/*selection sort*/
void selection_sort(int max, int lista[])
{
    int menor, aux;
    for(int i = 0; i < max-1; i++) {
        menor = i;
        for(int j = i; j < max; j++) {
            if(lista[j] < lista[menor])
                menor = j;
        }
        aux = lista[i];
        lista[i] = lista[menor];
        lista[menor] = aux;
    }
}

/*bubble sort*/
void bubble_sort(int max, int lista[])
{
    int aux;
    char troca;
    do {
        troca = 'F';
        for(int i = 0; i < max-1; i++) {
            if(lista[i] > lista[i+1]) {
                aux = lista[i];
                lista[i] = lista[i+1];
                lista[i+1] = aux;
                troca = 'T';
            }
        }
    }while(troca == 'T');
}

/*heap sort*/
void heapify(int max, int lista[], int i)
{
    int maior = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if(l < max && lista[l] > lista[maior])
        maior = l;
    if(r < max && lista[r] > lista[maior])
        maior = r;
    
    if(maior != i) {
        troca(lista, i, maior);
        heapify(max, lista, maior);
    }
}

void construir_heap(int max, int lista[])
{
    for(int i = max / 2 - 1; i >= 0; i--)
        heapify(max, lista, i);
}

void heap_sort(int max, int lista[])
{
    construir_heap(max, lista);
    for (int i = max - 1; i > 0; i--) {
        troca(lista, 0, i);
        heapify(i, lista, 0);
    }
}

/*merge sort*/
void merge_sort(int lista[], int ini, int fim)
{
    if(ini < fim) {
        int meio = (ini + fim) / 2;
        merge_sort(lista, ini, meio);
        merge_sort(lista, meio + 1, fim);

        merge(lista, ini, meio, fim);
    }
}

void merge(int lista[], int ini, int meio, int fim)
{
    int aux[fim];
    int i = ini, j = meio + 1, k = ini;
    while(i <= meio && j <= fim) {
        if(lista[i] <= lista[j]) {
            aux[k] = lista[i];
            i++;
        }
        else {
            aux[k] = lista[j];
            j++;
        }
        k++;
    }
    while(i <= meio) {
        aux[k] = lista[i];
        k++;
        i++;
    }
    while(j <= fim) {
        aux[k] = lista[j];
        k++;
        j++;
    }

    for(i = ini; i <= fim; i++)
        lista[i] = aux[i];
}

/*quick sort*/
void quick_sort(int lista[], int ini, int fim)
{
	int i = ini, j = fim - 1;
    int meio = (ini + fim) / 2;
	int pivo = lista[meio];
	while(i <= j) {
		while(lista[i] < pivo && i < fim)
			i++;
		while(lista[j] > pivo && j > ini)
			j--;
		if(i <= j) {
			troca(lista, i, j);
			i++;
			j--;
		}
	}
	if(j > ini)
		quick_sort(lista, ini, j+1);
	if(i < fim)
		quick_sort(lista, i, fim);
}

int main(int argc, char const *argv[])
{
    int op, op2;
    printf("Algoritimos disponiveis:\n");
    printf("(1) Insertion Sort\n(2) Selection Sort\n(3) Bubble Sort\n(4) Heap Sort\n(5) Merge Sort\n(6) Quick Sort\n>> ");
    scanf("%d", &op);

    printf("Qual arquivo de numeros deseja ordenar?\n");
    printf("(1) MIL\n(2) CINCO MIL\n(3) DEZ MIL\n(4) VINTE MIL\n(5) CINQUENTA MIL\n(6) SETENTA E CINCO MIL\n(7) CEM MIL\n>> ");
    scanf("%d", &op2);

    int max;
    FILE *arq;
    switch (op2) {
    case 1:
        max = 1000;
        arq = fopen("1000.txt", "r");
        break;
    case 2:
        max = 5000;
        arq = fopen("5000.txt", "r");
        break;
    case 3:
        max = 10000;
        arq = fopen("10000.txt", "r");
        break;
    case 4:
        max = 20000;
        arq = fopen("20000.txt", "r");
        break;
    case 5:
        max = 50000;
        arq = fopen("50000.txt", "r");
        break;
    case 6:
        max = 75000;
        arq = fopen("75000.txt", "r");
        break;
    case 7:
        max = 100000;
        arq = fopen("100000.txt", "r");
        break;
    default:
        break;
    }

    int i = 0, lista[max], num;
    while(fscanf(arq, "%d", &num) != EOF) {
        lista[i] = num;
        i++;
    }
    fclose(arq);

    clock_t tempo;
    tempo = clock();

    switch (op)
    {
    case 1:
        insertion_sort(max, lista);
        break;
    case 2:
        selection_sort(max, lista);
        break;
    case 3:
        bubble_sort(max, lista);
        break;
    case 4:
        heap_sort(max, lista);
        break;
    case 5:
        merge_sort(lista, 0, max-1);
        break;
    case 6:
        quick_sort(lista, 0, max);
        break;
    default:
        break;
    }

    tempo = clock() - tempo;
    double tempo_execucao = (double)(tempo) / CLOCKS_PER_SEC;
    printf("\nTempo de Execucao: %.4fs", tempo_execucao);
    return 0;
}