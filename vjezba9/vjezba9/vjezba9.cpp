#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void exchangeSort(int* , int);
void selectionSort(int*, int);
void insertionSort(int*, int);
void bubbleSort(int*, int);

int main() {
    int N1 = 100000;
    int* arr;
    DWORD t1, t2,t3,t4;

    srand((unsigned)time(NULL));

    arr = (int*)malloc(N1 * sizeof(int));

    for (int i = 0; i < N1; i++)
        arr[i] = rand() % 10000;


 //   t1 = GetTickCount();
 //   exchangeSort(arr, N1);
 //   t2 = GetTickCount();

 //   printf("Broj podataka: %d \nVrijeme sortiranja (Exchange sort): %lu ms\n",N1, t2 - t1);
	////15891 ms za 100000 elemenata
 //   

    t3 = GetTickCount();
    selectionSort(arr, N1);
    t4 = GetTickCount();
    printf("Vrijeme sortiranja(Selection sort) : %lu ms\n", t4 - t3);
	//7359 ms za 100000 elemenata

 //   t1 = GetTickCount();
 //   insertionSort(arr, N1);
 //   t2 = GetTickCount();

 //   printf("Broj podataka: %d \nVrijeme sortiranja (Insertion sort): %lu ms\n", N1, t2 - t1);
 //   //15891 ms za 100000 elemenata

 //   t3 = GetTickCount();
 //   bubbleSort(arr, N1);
 //   t4 = GetTickCount();
 //   printf("Vrijeme sortiranja(Bubble sort) : %lu ms\n", t4 - t3);
 //   //7359 ms za 100000 elemenata
  
    free(arr);
    return 0;
}

void exchangeSort(int* a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

void selectionSort(int* a, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;

        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }

        if (min != i) {
            int temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
}

void insertionSort(int* a, int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}
void bubbleSort(int* a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

