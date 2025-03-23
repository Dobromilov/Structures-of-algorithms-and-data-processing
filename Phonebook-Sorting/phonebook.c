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
