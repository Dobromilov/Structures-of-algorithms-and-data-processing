#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int BSearchAll1(int array[], int size, int search, int *comparisons) {
    int count = 0;
    int L = 0;
    int R = size - 1;
    
    while (L <= R) {
        (*comparisons)++;
        int mid = (L + R) / 2;
        if (array[mid] == search) {
            count++;
            int i = mid - 1;
            while (i >= 0 && array[i] == search) {
                (*comparisons)++;
                count++;
                i--;
            }
            i = mid + 1;
            while (i < size && array[i] == search) {
                (*comparisons)++;
                count++;
                i++;
            }
            return count;
        }
        if (array[mid] < search) {
            (*comparisons)++;
            L = mid + 1;
        } else {
            (*comparisons)++;
            R = mid - 1;
        }
    }
    return count; 
}

int BSearchAll2(int array[], int size, int search, int *comparisons) {
    int count = 0;
    int L = 0;
    int R = size - 1;
    
    while (L < R) {
        (*comparisons)++;
        int mid = L + (R - L) / 2;
        if (array[mid] < search) {
            (*comparisons)++;
            L = mid + 1;
        } else {
            (*comparisons)++;
            R = mid;
        }
    }
    
    if (L < size && array[L] == search) {
        count = 1;
        int i = L - 1;
        while (i >= 0 && array[i] == search) {
            (*comparisons)++;
            count++;
            i--;
        }
        i = L + 1;
        while (i < size && array[i] == search) {
            (*comparisons)++;
            count++;
            i++;
        }
    }
    return count;
}

void fillArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100;
        for (int j = 0; j < i; j++) {
            if (array[j] > array[i]) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

int main() {
    srand(time(NULL));
    
    int search;
    printf("Введите ключ поиска: ");
    scanf("%d", &search);
    
    FILE *dataFile = fopen("data.txt", "w");
    if (!dataFile) {
        printf("Ошибка открытия файла!\n");
        return 1;
    }
    
    printf("\nТрудоемкость двоичного поиска всех элементов\n");
    printf("+--------+-------------------+-------------------+\n");
    printf("|   N    |  Cф All I версия  |  Cф All II версия |\n");
    printf("+--------+-------------------+-------------------+\n");

    for (int size = 100; size <= 1000; size += 100) {
        int array[size];
        fillArray(array, size);
        
        int comparisons1 = 0;
        int comparisons2 = 0;
        
        BSearchAll1(array, size, search, &comparisons1);
        BSearchAll2(array, size, search, &comparisons2);
        
        printf("| %5d  | %10d        | %10d        |\n", size, comparisons1, comparisons2);
        fprintf(dataFile, "%d %d %d\n", size, comparisons1, comparisons2);
    }
    
    printf("+--------+-------------------+-------------------+\n");
    fclose(dataFile);

    // Создаем скрипт для gnuplot
    FILE *plotFile = fopen("plot_script.txt", "w");
    if (!plotFile) {
        printf("Ошибка создания скрипта!\n");
        return 1;
    }
    
    fprintf(plotFile,
        "set title 'Сравнение трудоемкости поиска'\n"
        "set xlabel 'Размер массива (N)'\n"
        "set ylabel 'Число сравнений (Cф)'\n"
        "set grid\n"
        "set key left top\n"
        "set terminal pngcairo\n"
        "set output 'output.png'\n"
        "plot 'data.txt' using 1:2 with linespoints title 'BSearchAll1', "
        "'data.txt' using 1:3 with linespoints title 'BSearchAll2'\n"
    );
    fclose(plotFile);

    // Запуск gnuplot
    system("gnuplot plot_script.txt");
    
    printf("График сохранен в output.png\n");
    return 0;
}
