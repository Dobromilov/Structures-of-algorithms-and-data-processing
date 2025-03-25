#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Определяем структуру контакта
typedef struct {
    char surname[50];
    char name[50];
    char phone[20];
    int age;
} Contact;

// Перечисления для ключа сортировки и направления
typedef enum {
    SORT_BY_SURNAME, 
    SORT_BY_NAME, 
    SORT_BY_PHONE, 
    SORT_BY_SURNAME_AND_NAME,
    SORT_BY_SURNAME_AND_AGE
} SortKey;

typedef enum {
    SORT_ASCENDING, 
    SORT_DESCENDING
} SortDirection;

// Глобальные переменные для текущих ключа и направления сортировки
SortKey currentKey = SORT_BY_SURNAME;
SortDirection currentDirection = SORT_ASCENDING;

// Функция сравнения для сортировки
int less(const Contact *a, const Contact *b) {
    int result = 0;

    switch (currentKey) {
        case SORT_BY_SURNAME:
            result = strcmp(a->surname, b->surname);
            break;
        case SORT_BY_NAME:
            result = strcmp(a->name, b->name);
            break;
        case SORT_BY_PHONE:
            result = strcmp(a->phone, b->phone);
            break;
        case SORT_BY_SURNAME_AND_NAME:
            result = strcmp(a->surname, b->surname);
            if (result == 0) {
                result = strcmp(a->name, b->name);
            }
            break;
        case SORT_BY_SURNAME_AND_AGE:
            result = strcmp(a->surname, b->surname);
            if (result == 0) {
                result = a->age - b->age;
            }
            break;
    }

    return (currentDirection == SORT_DESCENDING) ? -result : result;
}

// Функция сортировки вставками
void insertionSort(Contact arr[], int n) {
    for (int i = 1; i < n; i++) {
        Contact key = arr[i];
        int j = i - 1;

        while (j >= 0 && less(&arr[j], &key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Функция печати контактов
void printContacts(Contact arr[], int n) {
    printf("+-----------------+-----------------+-----------------+------+\n");
    printf("| %-15s | %-15s | %-15s | %-4s |\n", "Surname", "Name", "Phone", "Age");
    printf("+-----------------+-----------------+-----------------+------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %-15s | %-15s | %-15s | %-4d |\n", 
               arr[i].surname, arr[i].name, arr[i].phone, arr[i].age);
    }
    printf("+-----------------+-----------------+-----------------+------+\n");
}

int main() {
    // Инициализация генератора случайных чисел
    srand(time(NULL));
    
    Contact contacts[] = {
        {"Ivanov", "Ivan", "1234567", 20},
        {"Petrov", "Petr", "7654321", 21},
        {"Sidorov", "Sidor", "9876543", 20},
        {"Ivanov", "Alexey", "5555555", 19},
        {"Alekseev", "Aleksey", "3333333", 14}
    };

    int n = sizeof(contacts) / sizeof(contacts[0]);

    printf("Original phonebook:\n");
    printContacts(contacts, n);

    int sortKey;
    printf("Choose sorting key (0 - Surname, 1 - Name, 2 - Phone, 3 - Surname and Name, 4 - Surname and Age): ");
    scanf("%d", &sortKey);
    currentKey = (SortKey)sortKey;

    int sortDirection;
    printf("Choose sorting direction (0 - Ascending, 1 - Descending): ");
    scanf("%d", &sortDirection);
    currentDirection = (SortDirection)sortDirection;

    insertionSort(contacts, n);
    printf("\nSorted phonebook:\n");
    printContacts(contacts, n);

    char searchKey[50];
    printf("\nEnter search key: ");
    scanf("%s", searchKey);

    int found = 0;
    printf("\nSearch results:\n");
    printf("+-----------------+-----------------+-----------------+------+\n");
    printf("| %-15s | %-15s | %-15s | %-4s |\n", "Surname", "Name", "Phone", "Age");
    printf("+-----------------+-----------------+-----------------+------+\n");
    for (int i = 0; i < n; i++) {
        if ((currentKey == SORT_BY_SURNAME && strcmp(contacts[i].surname, searchKey) == 0) ||
            (currentKey == SORT_BY_NAME && strcmp(contacts[i].name, searchKey) == 0) ||
            (currentKey == SORT_BY_PHONE && strcmp(contacts[i].phone, searchKey) == 0) ||
            (currentKey == SORT_BY_SURNAME_AND_NAME && strcmp(contacts[i].surname, searchKey) == 0) ||
            (currentKey == SORT_BY_SURNAME_AND_AGE && strcmp(contacts[i].surname, searchKey) == 0)) {
            printf("| %-15s | %-15s | %-15s | %-4d |\n", 
                   contacts[i].surname, contacts[i].name, contacts[i].phone, contacts[i].age);
            found = 1;
        }
    }
    printf("+-----------------+-----------------+-----------------+------+\n");

    if (!found) {
        printf("Contact not found.\n");
    }

    return 0;
}
