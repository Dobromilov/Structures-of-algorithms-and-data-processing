# Binary Search

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>  

int binary_search(int array[], int size, int search, int *comparisons) {
    int L = 0;
    int R = size - 1;
    
    while (L <= R) {
        int mid = (L + R) / 2;
        (*comparisons)++; 
        if (array[mid] == search) {
            return mid;
        }
        (*comparisons)++;
        if (array[mid] < search) {
            L = mid + 1;
        } else {
            R = mid - 1;
        }
    }
    return -1;
}

int binary_search_up(int array[], int size, int search, int *comparisons) {
    int L = 0;
    int R = size - 1;

    while (L < R) {
        int mid = L + (R - L) / 2;
        (*comparisons)++;
        if (array[mid] < search) {
            L = mid + 1;
        } else {
            R = mid;
        }
    }
    (*comparisons)++;    
    if (L < size && array[L] == search) {
        return L;
    } else {
        return -1;
    }
}

void filling_in_the_array(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = i + 1;
    }
}

int main(void) {
    srand(time(NULL));


    int search;
    scanf("%d",&search);
    

    printf("Трудоемкость двоичного поиска элемента\n");
    printf("+--------+-----------------+-----------------+\n");
    printf("|   N    |  Cф I версия    |  Cф II версия   |\n");
    printf("+--------+-----------------+-----------------+\n");

    for (int size = 100; size <= 1000; size += 100) {
        int array[size];
        filling_in_the_array(array, size);

        int comparisons1 = 0;
        int comparisons2 = 0;

        binary_search(array, size, search, &comparisons1);
        binary_search_up(array, size, search, &comparisons2);

        printf("| %5d  | %8d        | %8d        |\n", size, comparisons1, comparisons2);
    }

    printf("+--------+-----------------+-----------------+\n");

    return 0;
}
```
# Описание программы: Сравнение трудоемкости двух версий двоичного поиска

Этот проект на языке C реализует две версии двоичного поиска и сравнивает их трудоемкость (количество сравнений) для различных размеров массива. Программа заполняет массив последовательными числами и выполняет поиск заданного элемента, используя две разные версии двоичного поиска. Результаты выводятся в виде таблицы.

## Структура программы

### 1. **Функция `binary_search`**
   - **Описание**: Классическая реализация двоичного поиска. Алгоритм работает на отсортированном массиве и ищет элемент, сравнивая его с серединой массива. Если элемент найден, возвращается его индекс. Если элемент меньше середины, поиск продолжается в левой половине массива, иначе — в правой.
   - **Параметры**:
     - `array[]`: Отсортированный массив, в котором выполняется поиск.
     - `size`: Размер массива.
     - `search`: Элемент, который нужно найти.
     - `*comparisons`: Указатель на переменную, которая хранит количество сравнений.
   - **Возвращаемое значение**: Индекс найденного элемента или `-1`, если элемент не найден.

### 2. **Функция `binary_search_up`**
   - **Описание**: Модифицированная версия двоичного поиска. Основное отличие заключается в том, что при равенстве элемента с серединой массива поиск продолжается в левой половине, что может уменьшить количество сравнений в некоторых случаях.
   - **Параметры**: Аналогичны функции `binary_search`.
   - **Возвращаемое значение**: Индекс найденного элемента или `-1`, если элемент не найден.

### 3. **Функция `filling_in_the_array`**
   - **Описание**: Заполняет массив последовательными числами от 1 до `size`.
   - **Параметры**:
     - `array[]`: Массив, который нужно заполнить.
     - `size`: Размер массива.

### 4. **Функция `main`**
   - **Описание**: Основная функция программы. Она:
     1. Запрашивает у пользователя элемент для поиска.
     2. Заполняет массив числами от 1 до `size` (размер массива изменяется от 100 до 1000 с шагом 100).
     3. Выполняет поиск элемента с использованием обеих версий двоичного поиска.
     4. Выводит результаты в виде таблицы, где для каждого размера массива указано количество сравнений для обеих версий.

### 5. **Таблица результатов**
   - Программа выводит таблицу, которая содержит:
     - Размер массива (`N`).
     - Количество сравнений для первой версии двоичного поиска (`Cф I версия`).
     - Количество сравнений для второй версии двоичного поиска (`Cф II версия`).

## Пример вывода

```
Трудоемкость двоичного поиска элемента
+--------+-----------------+-----------------+
|   N    |  Cф I версия    |  Cф II версия   |
+--------+-----------------+-----------------+
|   100  |        7        |        7        |
|   200  |        8        |        8        |
|   300  |        9        |        9        |
|   ...  |      ...        |      ...        |
|  1000  |       10        |       10        |
+--------+-----------------+-----------------+
```


# Задание на 5+

### Разработать подпрограммы поиска в упорядоченном массиве всех элементов с заданным ключом (две версии) BSearchAll1 и BSearchAll2., ключ поиска передается в подпрограмму в качестве параметра или вводится с клавиатуры.

```c
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
```

### Основные функции

1. **`BSearchAll1`**:
   - Реализует классический двоичный поиск с последующим поиском всех вхождений элемента в массиве.
   - После нахождения элемента проверяет соседние элементы (влево и вправо) для подсчета всех вхождений.
   - Возвращает количество найденных элементов и увеличивает счетчик сравнений.

2. **`BSearchAll2`**:
   - Реализует модифицированный двоичный поиск, который находит первое вхождение элемента.
   - После нахождения первого вхождения проверяет соседние элементы для подсчета всех вхождений.
   - Возвращает количество найденных элементов и увеличивает счетчик сравнений.

3. **`fillArray`**:
   - Заполняет массив случайными числами и сортирует его по возрастанию.
   - Используется для подготовки тестовых данных.

4. **`main`**:
   - Генерирует массивы различных размеров (от 100 до 1000 с шагом 100).
   - Для каждого массива выполняет поиск с использованием обеих версий алгоритма.
   - Записывает результаты (размер массива и количество сравнений) в файл `data.txt`.
   - Создает скрипт для `gnuplot` и генерирует график, который сохраняется в файл `output.png`.

---

### Как работает программа

1. Пользователь вводит ключ поиска (целое число).
2. Программа создает массивы различных размеров, заполняет их случайными числами и сортирует.
3. Для каждого массива выполняются обе версии поиска, и подсчитывается количество сравнений.
4. Результаты записываются в файл `data.txt`.
5. Создается скрипт для `gnuplot`, который строит график зависимости количества сравнений от размера массива.
6. График сохраняется в файл `output.png`.

---

### Зависимости

- Для компиляции и запуска программы требуется компилятор C (например, `gcc`).
- Для визуализации результатов требуется установленный `gnuplot`.

---

### Пример вывода

```
Введите ключ поиска: 42

Трудоемкость двоичного поиска всех элементов
+--------+-------------------+-------------------+
|   N    |  Cф All I версия  |  Cф All II версия |
+--------+-------------------+-------------------+
|   100  |        15         |        12         |
|   200  |        18         |        14         |
|   300  |        20         |        16         |
|   ...  |        ...        |        ...        |
|  1000  |        25         |        20         |
+--------+-------------------+-------------------+
График сохранен в output.png
```

![image](https://github.com/user-attachments/assets/07b0b96d-82f7-4d02-ba54-cc305bcb0e08)

---

### Файлы

- `bin_5plus.c` — исходный код программы.
- `data.txt` — файл с результатами сравнений.
- `plot_script.txt` — скрипт для `gnuplot`.
- `output.png` — график сравнения трудоемкости.
