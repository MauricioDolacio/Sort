#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Funcao Swap: troca de valores com ajuda de um auxiliar
int swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

//selectionSort [1]
void selectionSort(int v[], int n) {
    int i, j, minor, aux;
    for(i = 0; i < n-1; i++) {
        minor = i;
        for(j = i+1; j < n; j++) {
            if(v[minor] > v[j])
                minor = j;
        }
        if(i != minor) {
            swap(&v[i], &v[minor]);
        }
    }
}



//bubbleSort [2]
void bubbleSort(int v[], int n) {
    int i, prox, aux, f = n;
    do{
        prox = 0;
        for(i = 0; i < f-1; i++) {
            if(v[i] > v[i+1]) {
                swap(&v[i], &v[i+1]);
                prox = i;
            }
        }
        f--;
    } while(prox != 0);
}



//insertionSort [3]
void insertionSort(int v[], int n) {
    int i, j, aux;
    for(i = 1; i < n; i++) {
        aux = v[i];
        for(j = i; (j > 0) && (aux < v[j - 1]); j--)
            v[j] = v[j-1];
        v[j] = aux;
    }
}



//binaryInsertionSort [4]
int binarySearch(int v[], int i, int menor, int maior) {
    if (maior <= menor)
        return (i > v[menor]) ? (menor + 1) : menor;
    int mid = (menor + maior) / 2;
    if (i == v[mid])
        return mid + 1;
    if (i > v[mid])
        return binarySearch(v, i, mid + 1, maior);
    return binarySearch(v, i, menor, mid - 1);
}

void biInsertionSort(int v[], int n) {
    int i, loc, j, k, aux;
    for (i = 1; i < n; ++i) {
        j = i - 1;
        aux = v[i];
        loc = binarySearch(v, aux, 0, j);
        while (j >= loc) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = aux;
    }
}


//quickSort [5]
void quickSort(int v[], int start, int end) {
    if (start >= end) return;
    int p = start, left = start + 1, right = end; 
    while (left <= right) {
        while(left <= end && v[left] <= v[p]) left++; 
        while(right > start && v[right] >= v[p]) right--;
        if (left > right) swap(&v[p], &v[right]); 
        else swap(&v[left], &v[right]);
    }
    quickSort(v, start, right - 1); 
    quickSort(v, right + 1, end);
}



//heapSort [6]
void createHeap(int v[], int i, int f) {
    int aux = v[i];
    int j = i*2+1;
    while(j <= f) {
        if(j < f) {
            if(v[j] < v[j+1]) {
                j = j + 1;
            }
        }
        if(aux < v[j]) {
            v[i] = v[j];
            i = j;
            j = 2*i+1;
        } else {
            j = f + 1;
        }
    }
    v[i] = aux;
}

void heapSort(int v[], int n) {
    int i, aux;
    for(i = (n-1)/2; i >= 0; i--) {
        createHeap(v, i, n-1);
    }
    for(i = n-1; i >= 1; i--) {
        swap(&v[0], &v[i]);
        createHeap(v, 0, i-1);
    }
}



//mergeSort [7]
void merge(int v[], int inicio, int m, int fim) {
    int *aux, p1, p2, tam, i, j, k;
    int fim1 = 0, fim2= 0;
    tam = fim-inicio+1;
    p1 = inicio;
    p2 = m+1;
    aux = (int *) malloc(tam*sizeof(int));
    if(aux != NULL) {
        for(i = 0; i < tam; i++) {
            if(!fim1 && !fim2) {
                if(v[p1] < v[p2])
                    aux[i] = v[p1++];
                else
                    aux[i] = v[p2++];
                if(p1 > m) 
                    fim1 = 1;
                if(p2 > fim) 
                    fim2 = 1;
            } else {
                if(!fim1)
                    aux[i] = v[p1++];
                else
                    aux[i] = v[p2++];
            }
        }
        for(j=0, k=inicio; j < tam; j++, k++)
            v[k] = aux[j];
    }
    free(aux);
}

void mergeSort(int v[], int i, int f) {
    int m;
    if(i < f) {
        m = floor((i+f)/2);
        mergeSort(v, i, m);
        mergeSort(v, m+1, f);
        merge(v, i, m, f);
    }
}



//bucketSort [8]
#define SIZE 5
struct bucket {
    int qtd;
    int value[SIZE];
};

void bucketSort(int v[], int n) {
    int i, j, maior, menor, nBuckets, pos;
    struct bucket *bck;
    
    maior = menor = v[0];
    for(i = 1; i < n; i++) {
        if(v[i] > maior) 
            maior = v[i];
        if(v[i] < menor)
            menor = v[i];
    }
    
    nBuckets = (maior - menor) / SIZE + 1;
    bck = (struct bucket *) malloc(nBuckets * sizeof(struct bucket));
    for (i = 0; i < nBuckets; i++)
        bck[i].qtd = 0;
    
    for(i = 0; i < n; i++) {
        pos = (v[i] - menor) / SIZE;
        bck[pos].value[bck[pos].qtd] = v[i];
        bck[pos].qtd++;
    }
    
    pos = 0;
    for(i = 0; i < nBuckets; i++) {
        selectionSort(bck[i].value, bck[i].qtd);
        for(j = 0; j < bck[i].qtd; j++) {
            v[pos] = bck[i].value[j];
            pos++;
        }
    }
}



//Main
int main(void) {
    int i, n, met, vet[1000], prox = 0;
    printf("---- ALGORITIMO DE SORTEAMENTO ----\n");
    printf("[1] - selectionSort \n[2] - BubbleSort \n[3] - insertionSort \n[4] - binaryInsertionSort \n[5] - quickSort \n[6] - heapSort \n[7] - mergeSort \n[8] - bucketSort \n");
    //Pede ao usuario para que selecione um dos métodos inserindo um numero
    while(prox == 0) {
        printf("\nDigite o numero do metodo que deseja utilizar: ");
        scanf("%d", &met);
        if(met > 0 && met < 9) {
            prox = 1;
        } else {
            printf("Digite um numero valido!\n");
        }
    }
    
    //Pede ao usuario para que insira a quantidade de numeros que terão na lista
    prox = 0;
    while(prox == 0) {
        printf("\nDigite a quantidade de numeros que deseja colocar: ");
        scanf("%d", &n);
        if(n > 0) {
            prox = 1;
        } else {
            printf("Digite um numero valido!\n");
        }
    }
    
    //Pede ao usuario para que insira os numeros que deseja ordenar
    printf("\nDigite os numeros a serem ordenados: ");
    for (i = 0; i < n; i++) scanf("%d", &vet[i]);
    
    //Verifica qual método foi escolhido e ordena a lista
    prox = 0;
    while(prox == 0) {
        if(met == 1) {
            printf("\n---- Metodo selectionSort ----");
            selectionSort(vet, n);
            prox = 1;
        }
        if(met == 2) {
            printf("\n---- Metodo bubbleSort ----");
            bubbleSort(vet, n);
            prox = 1;
        }
        if(met == 3) {
            printf("\n---- Metodo insertionSort ----");
            insertionSort(vet, n);
            prox = 1;
        }
        if(met == 4) {
            printf("\n---- Metodo binaryInsertionSort ----");
            biInsertionSort(vet, n);
            prox = 1;
        }
        if(met == 5) {
            printf("\n---- Metodo quickSort ----");
            int f = n - 1;
            quickSort(vet, 0, f);
            prox = 1;
        }
        if(met == 6) {
            printf("\n---- Metodo heapSort ----");
            heapSort(vet, n);
            prox = 1;
        }
        if(met == 7) {
            printf("\n---- Metodo mergeSort ----");
            int f = n - 1;
            mergeSort(vet, 0, f);
            prox = 1;
        }
        if(met == 8) {
            printf("\n---- Metodo bucketSort ----");
            bucketSort(vet, n);
            prox = 1;
        }
    }
    
    //Imprime a lista ordenada
    printf("\n\nConclusao: \n");
    for(int i=0; i<n; i++){
        printf("%d ", vet[i]);
    }
    printf("\n");
    system ("pause");
}
