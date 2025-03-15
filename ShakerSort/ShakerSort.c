#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5

int BubbleSort(int arr[], int n) {
    int comparisons = 0;
    int swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
            }
        }
    }
    return 3 * swaps + comparisons;
}

int ShakerSort(int A[], int n) {
    int left = 0, right = n - 1;
    int swapped = 1;
    int comparisons = 0;
    int swaps = 0;

    while (left < right && swapped) {
        swapped = 0;
        for (int i = left; i < right; i++) {
            comparisons++;
            if (A[i] > A[i + 1]) {
                int temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
                swaps++;
                swapped = 1;
            }
        }
        if (!swapped) break;
        right--;

        for (int i = right; i > left; i--) {
            comparisons++;
            if (A[i] < A[i - 1]) {
                int temp = A[i];
                A[i] = A[i - 1];
                A[i - 1] = temp;
                swaps++;
                swapped = 1;
            }
        }
        left++;
    }
    return 3 * swaps + comparisons;
}

void fillArray(int arr[], int n, int type) {
    if (type == 0) { // Убывающий
        for (int i = 0; i < n; i++)
            arr[i] = n - i;
    } else if (type == 1) { // Случайный
        for (int i = 0; i < n; i++)
            arr[i] = rand() % 1000;
    } else { // Возрастающий
        for (int i = 0; i < n; i++)
            arr[i] = i + 1;
    }
}

int main() {
    srand(time(NULL));
    int sizes[SIZE] = {100, 200, 300, 400, 500};

    // Заголовок таблицы
    printf("+------+---------------------+---------------------+\n");
    printf("|  n   | BubbleSort          | ShakerSort          |\n");
    printf("|      | Убыв.  Случ.  Возр. | Убыв.  Случ.  Возр. |\n");
    printf("+------+---------------------+---------------------+\n");

    for (int i = 0; i < SIZE; i++) {
        int n = sizes[i];
        int arr[n];
        int resBubble[3], resShaker[3];

        for (int j = 0; j < 3; j++) {
            fillArray(arr, n, j);
            resBubble[j] = BubbleSort(arr, n);
            fillArray(arr, n, j);
            resShaker[j] = ShakerSort(arr, n);
        }

        // Вывод строки таблицы
        printf("| %-4d | %-5d  %-5d  %-5d | %-5d  %-5d  %-5d |\n", 
               n, 
               resBubble[0], resBubble[1], resBubble[2], 
               resShaker[0], resShaker[1], resShaker[2]);
    }

    // Завершение таблицы
    printf("+------+---------------------+---------------------+\n");

    return 0;
}