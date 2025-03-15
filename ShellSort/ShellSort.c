#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int M;
    int C;
} Metrics;

// Прототипы функций
void shellSort(int arr[], int n, Metrics *metrics, int steps[], int steps_count);
void insertSort(int arr[], int n, Metrics *metrics);
void knuthSteps(int n, int *steps, int *steps_count);
void generateArray(int arr[], int n);
void copyArray(int src[], int dest[], int n);
void printKnuthSteps(int steps[], int count);

// Реализация сортировки Шелла
void shellSort(int arr[], int n, Metrics *metrics, int steps[], int steps_count) {
    metrics->M = 0;
    metrics->C = 0;
    
    for (int s = 0; s < steps_count; s++) {
        int h = steps[s];
        for (int i = h; i < n; i++) {
            int temp = arr[i];
            metrics->M++;
            int j;
            for (j = i; j >= h; j -= h) {
                metrics->C++;
                if (arr[j - h] <= temp) break;
                arr[j] = arr[j - h];
                metrics->M++;
            }
            arr[j] = temp;
            metrics->M++;
        }
    }
}

// Реализация сортировки вставками
void insertSort(int arr[], int n, Metrics *metrics) {
    metrics->M = 0;
    metrics->C = 0;
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        metrics->M++;
        int j = i - 1;
        
        while (j >= 0) {
            metrics->C++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                metrics->M++;
                j--;
            } else break;
        }
        arr[j + 1] = key;
        metrics->M++;
    }
}

// Генерация шагов по Кнуту
void knuthSteps(int n, int *steps, int *steps_count) {
    *steps_count = 0;
    int h = 1;
    while (h <= n / 3) {
        h = 3 * h + 1;
    }
    while (h > 0) {
        steps[(*steps_count)++] = h;
        h = (h - 1) / 3;
    }
}

// Генерация случайного массива
void generateArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

// Копирование массива
void copyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Вывод шагов Кнута
void printKnuthSteps(int steps[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%d", steps[i]);
        if (i != count - 1) printf(", ");
    }
}

int main() {
    srand(time(NULL));
    int sizes[] = {100, 200, 300, 400, 500};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    printf("+------+---------------------+----------------+----------------+\n");
    printf("|  n   | Шаги Кнута          | Insert Mф+Cф   | Shell Mф+Cф    |\n");
    printf("+------+---------------------+----------------+----------------+\n");
    
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int *arr = malloc(n * sizeof(int));
        int *arr_copy = malloc(n * sizeof(int));
        generateArray(arr, n);
        copyArray(arr, arr_copy, n);
        
        int steps[20];
        int steps_count;
        knuthSteps(n, steps, &steps_count);
        
        Metrics shell_metrics;
        shellSort(arr, n, &shell_metrics, steps, steps_count);
        
        Metrics insert_metrics;
        insertSort(arr_copy, n, &insert_metrics);
        
        printf("| %-4d | ", n);
        printKnuthSteps(steps, steps_count);
        printf(" %*s | %-14d | %-14d |\n", 
            18 - (steps_count * 3 - 1), "",  // Выравнивание шагов Кнута
            insert_metrics.M + insert_metrics.C, 
            shell_metrics.M + shell_metrics.C
        );
        
        free(arr);
        free(arr_copy);
    }
    printf("+------+---------------------+----------------+----------------+\n");
    return 0;
}