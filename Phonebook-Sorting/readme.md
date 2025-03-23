
# Phonebook Sorting Program

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Определяем структуру контакта
typedef struct {
    char surname[50];
    char name[50];
    char phone[20];
    char address[100];
} Contact;

// Перечисления для ключа сортировки
typedef enum {SORT_BY_SURNAME, SORT_BY_NAME, SORT_BY_PHONE} SortKey;
typedef enum {SORT_ASCENDING, SORT_DESCENDING} SortDirection;

// Глобальные переменные для текущих ключа и направления сортировки
SortKey currentKey = SORT_BY_SURNAME;
SortDirection currentDirection = SORT_ASCENDING;

// Функция сравнения для qsort
int compareContacts(const void *a, const void *b) {
    const Contact *contactA = (const Contact *)a;
    const Contact *contactB = (const Contact *)b;
    int result = 0;

    switch (currentKey) {
        case SORT_BY_SURNAME: result = strcmp(contactA->surname, contactB->surname); break;
        case SORT_BY_NAME: result = strcmp(contactA->name, contactB->name); break;
        case SORT_BY_PHONE: result = strcmp(contactA->phone, contactB->phone); break;
    }

    return (currentDirection == SORT_DESCENDING) ? -result : result;
}

// Функция сравнения для bsearch
int searchCompare(const void *key, const void *element) {
    const char *searchKey = (const char *)key;
    const Contact *contact = (const Contact *)element;

    // Поиск осуществляется по основному полю сортировки
    if (currentKey == SORT_BY_SURNAME) {
        return strcmp(searchKey, contact->surname);
    } else if (currentKey == SORT_BY_NAME) {
        return strcmp(searchKey, contact->name);
    } else {
        return strcmp(searchKey, contact->phone);
    }
}

// Функция печати контактов
void printContacts(Contact arr[], int n) {
    printf("+-----------------+-----------------+-----------------+---------------------+\n");
    printf("| %-15s | %-15s | %-15s | %-20s |\n", "Surname", "Name", "Phone", "Address");
    printf("+-----------------+-----------------+-----------------+---------------------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %-15s | %-15s | %-15s | %-20s |\n", arr[i].surname, arr[i].name, arr[i].phone, arr[i].address);
    }
    printf("+-----------------+-----------------+-----------------+---------------------+\n");
}

int main() {
    Contact contacts[] = {
        {"Ivanov", "Ivan", "1234567", "Mira str. 10"},
        {"Petrov", "Petr", "7654321", "Lenina str. 5"},
        {"Sidorov", "Sidor", "9876543", "Pushkina str. 15"},
        {"Ivanov", "Alexey", "5555555", "Gagarina str. 20"},
        {"Alekseev", "Aleksey", "3333333", "Kirova str. 25"}
    };

    int n = sizeof(contacts) / sizeof(contacts[0]);

    // Выводим оригинальный справочник
    printf("Original phonebook:\n");
    printContacts(contacts, n);

    // Выбор ключа сортировки
    int sortKey;
    printf("Choose sorting key (0 - Surname, 1 - Name, 2 - Phone): ");
    scanf("%d", &sortKey);
    currentKey = sortKey;

    // Выбор направления сортировки
    int sortDirection;
    printf("Choose sorting direction (0 - Ascending, 1 - Descending): ");
    scanf("%d", &sortDirection);
    currentDirection = sortDirection;

    // Сортировка массива
    qsort(contacts, n, sizeof(Contact), compareContacts);
    printf("\nSorted phonebook:\n");
    printContacts(contacts, n);

    // Поиск элемента
    char searchKey[50];
    printf("\nEnter search key: ");
    scanf("%s", searchKey);

    Contact *found = (Contact *)bsearch(searchKey, contacts, n, sizeof(Contact), searchCompare);

    if (found) {
        printf("\nContact found:\n");
        printf("+-----------------+-----------------+-----------------+---------------------+\n");
        printf("| %-15s | %-15s | %-15s | %-20s |\n", found->surname, found->name, found->phone, found->address);
        printf("+-----------------+-----------------+-----------------+---------------------+\n");
    } else {
        printf("\nContact not found.\n");
    }

    return 0;
}
```

Это программа на языке Си, реализующая систему управления телефонной книгой. Она позволяет пользователям сохранять контактную информацию в виде массива структур, сортировать контакты на основе различных полей (фамилия, имя или номер телефона) и выполнять поиск конкретного контакта с помощью бинарного поиска. Программа демонстрирует использование функций сортировки (`qsort`) и поиска (`bsearch`) из стандартной библиотеки C, а также пользовательской логики сравнения.

## Особенности
- ** Хранилище данных**: Хранит контакты в виде массива структур "Контакты", каждая из которых содержит фамилию, имя, номер телефона и адрес.
- **Сортировка**: Поддерживает сортировку по фамилии, имени или номеру телефона в порядке возрастания или убывания.
- **Поиск**: Позволяет выполнять поиск контакта по текущему ключу сортировки с помощью бинарного поиска.
- **Удобная печать**: Отображает телефонную книгу в виде отформатированной таблицы.

## Структура кода

### Заголовки
Программа включает в себя следующие стандартные библиотеки языка Си:
- `<stdio.h>`: Для операций ввода-вывода (например, `printf`, `scanf`).
- `<string.h>`: Для функций сравнения строк (например, `strcmp`).
- `<stdlib.h>`: Для функций сортировки и поиска (`qsort`, `bsearch`).

### Определения данных
- **Структура**: 
```c
typedef struct {
      фамилия, обозначенная символом[50];
      имя, обозначенное символом[50];
      телефон, обозначенный символом[20];
      адрес, обозначенный символом[100];
  } Контактное лицо;
```
  Определяет структуру "Контакт" для хранения контактных данных с помощью массивов символов фиксированного размера для каждого поля.

- **Перечисления**:
```c
перечислением typedef {SORT_BY_SURNAME, SORT_BY_NAME, SORT_BY_PHONE} Сортировочный ключ;
  typedef перечисление {СОРТИРОВКА_ВЫСОТОГО, СОРТИРОВКА_ВЫСОТОГО} Направление сортировки;
```
  - `SortKey`: указывает поле для сортировки по (фамилия = 0, имя = 1, телефон = 2).
  - `SortDirection`: указывает направление сортировки (по возрастанию = 0, по убыванию = 1).

- **Глобальные переменные**:
```c
  Текущий ключ сортировки = ИМЯ_СОРТИРОВКИ;
  Текущее направление сортировки = ВОСХОДЯЩЕЕ направление СОРТИРОВКИ;
```
  По умолчанию сортировка производится по фамилии в порядке возрастания. Эти глобальные параметры обновляются в зависимости от пользовательского ввода.

### Функции

1. **`compareContacts`**
   ```c
   int compareContacts(const void *a, const void *b)
   ```
   - **Назначение**: Функция сравнения для `qsort`.
   - **Параметры**: Два указателя `void` (`a` и `b`) преобразованы в указатели `Contact`.
   - **Логика**: Сравнивает два контакта на основе "текущего ключа" (фамилия, имя или телефон), используя "strcmp". Корректирует результат на основе "текущего направления" (меняет порядок убывания).
   - **Возвращает**: целое число для порядка сортировки (`< 0`, если `a` стоит перед `b`, `> 0`, если после, `0`, если равно).

2. **`searchCompare`**
   ```c
   int searchCompare(const void *ключ, const void *элемент)
   ```
   - **Назначение**: Функция сравнения для `bsearch`.
   - **Параметры**: Указатель "void" на ключ поиска (преобразуется в "char*") и указатель "void" на "Контакт" (преобразуется в `Contact*`).
   - **Логика**: Сравнивает ключ поиска с полем, указанным в `currentKey`.
   - **Возвращает**: целое число для двоичного поиска (`< 0`, `> 0`, или `0`).

3. **`printContacts`**
   ```c
   аннулировать printContacts(Contact arr[], int n)
   ```
   - **Назначение**: Печать телефонной книги в виде отформатированной таблицы.
   - **Параметры**: Массив структур `Contact` и количество контактов (`n`).
   - **Логика**: использует `printf` со спецификаторами ширины для выравнивания столбцов в формате таблицы.

4. **`main`**
   - **Назначение**: Точка входа в программу.
   - **Логика**:
     1. Инициализирует примерный массив из 5 контактов.
     2. Распечатывает исходную телефонную книгу.
     3. Предлагает пользователю выбрать ключ сортировки и направление.
     4. Сортирует массив с помощью qsort.
     5. Распечатывает отсортированную телефонную книгу.
     6. Предлагает пользователю ввести ключ поиска.
     7. Выполняет поиск с помощью "bsearch" и отображает результат.

## Как это работает
1. **Инициализация**: Создается предопределенный массив структур "Contact" с использованием образцов данных.
2. **Сортировка**:
   - Пользователь вводит ключ сортировки (0, 1 или 2) и направление (0 или 1).
   - `qsort` сортирует массив, используя `compareContacts`.
3. **Поиск**:
   - Пользователь вводит ключ поиска (например, фамилию при сортировке по фамилии).
   - "bsearch" находит контакт, используя "searchCompare".
4. **Вывод**: Результаты отображаются в виде аккуратно отформатированной таблицы.

## Пример использования
```
Original phonebook:
+-----------------+-----------------+-----------------+---------------------+
| Surname        | Name           | Phone         | Address              |
+-----------------+-----------------+-----------------+---------------------+
| Ivanov         | Ivan           | 1234567       | Mira str. 10         |
| Petrov         | Petr           | 7654321       | Lenina str. 5        |
| Sidorov        | Sidor          | 9876543       | Pushkina str. 15     |
| Ivanov         | Alexey         | 5555555       | Gagarina str. 20     |
| Alekseev       | Aleksey        | 3333333       | Kirova str. 25       |
+-----------------+-----------------+-----------------+---------------------+

Choose sorting key (0 - Surname, 1 - Name, 2 - Phone): **0**  
Choose sorting direction (0 - Ascending, 1 - Descending): **0**  

Sorted phonebook:
+-----------------+-----------------+-----------------+---------------------+
| Alekseev       | Aleksey        | 3333333       | Kirova str. 25       |
| Ivanov         | Alexey         | 5555555       | Gagarina str. 20     |
| Ivanov         | Ivan           | 1234567       | Mira str. 10         |
| Petrov         | Petr           | 7654321       | Lenina str. 5        |
| Sidorov        | Sidor          | 9876543       | Pushkina str. 15     |
+-----------------+-----------------+-----------------+---------------------+

Enter search key: **Ivanov**  

Contact found:
+-----------------+-----------------+-----------------+---------------------+
| Ivanov         | Alexey         | 5555555       | Gagarina str. 20     |
+-----------------+-----------------+-----------------+---------------------+
```
## Ограничения
- Фиксированный размер массива (без динамического выделения).
- Поиск надежно работает только при первом совпадении, когда существуют дубликаты (например, две записи "Иванов").
- Проверка вводимых данных минимальна (принимаются допустимые целые числа и строки).

## Как запустить
1. **Требования**: Компилятор C (например, GCC).
2. **Скомпилировать**: `gcc -o phonebook phonebook.c`
3. **Запустите**: `./phonebook`
4. Следуйте инструкциям для сортировки и поиска.
