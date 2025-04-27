# Merge Sort для очереди на связном списке
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int count;
} Queue;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void initQueue(Queue* q) {
    q->head = q->tail = NULL;
    q->count = 0;
}

void enqueue(Queue* q, long long int data) {
    Node* newNode = createNode(data);
    if (q->tail == NULL) {
        q->head = q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
    q->count++;
}

void fillQueueAscending(Queue* q, int n) {
    for (int i = 1; i <= n; i++) {
        enqueue(q, i);
    }
}

void fillQueueDescending(Queue* q, int n) {
    for (int i = n; i >= 1; i--) {
        enqueue(q, i);}}

void fillQueueRandom(Queue* q, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        enqueue(q, rand() % (2*n));
    }
}

void freeQueue(Queue* q) {
    Node* current = q->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);}
    q->head = q->tail = NULL;
    q->count = 0;
}

void MoveNode(Queue* dest, Queue* src, int* M) {
    if (src->head == NULL) return;
    Node* node = src->head;
    src->head = src->head->next;
    if (src->head == NULL) src->tail = NULL;
    src->count--;
    node->next = NULL;
    if (dest->tail == NULL) {
        dest->head = dest->tail = node;
    } else {
        dest->tail->next = node;
        dest->tail = node;}
    dest->count++;
    (*M)++;
}

void Merge(Queue* a, int q, Queue* b, int r, Queue* c, int* M, int* C) {
    while (q > 0 && r > 0) {
        (*C)++;
        if (a->head->data <= b->head->data) {
            MoveNode(c, a, M);
            q--;
        } else {
            MoveNode(c, b, M);
            r--;}}
    
    while (q > 0) {
        MoveNode(c, a, M);
        q--;}
    
    while (r > 0) {
        MoveNode(c, b, M);
        r--;}
}

void Split(Queue* S, Queue* a, Queue* b) {
    initQueue(a);
    initQueue(b);
    if (S->head == NULL) return;
    Node* slow = S->head;
    Node* fast = S->head->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;}}
    a->head = S->head;
    a->tail = slow;
    b->head = slow->next;
    b->tail = S->tail;
    Node* current = a->head;
    a->count = 0;
    while (current != NULL && current != b->head) {
        a->count++;
        current = current->next;}
    b->count = S->count - a->count;
    if (a->tail) a->tail->next = NULL;
}

int MergeSort(Queue* S) {
    if (S->head == NULL || S->head->next == NULL) return 0;
    Queue a, b;
    Split(S, &a, &b);
    int M_left = MergeSort(&a);
    int M_right = MergeSort(&b);
    int M = 0, C = 0;
    Queue temp;
    initQueue(&temp);
    Merge(&a, a.count, &b, b.count, &temp, &M, &C);
    *S = temp;
    return M + C + M_left + M_right;
}

int teor_C(int n) {
    return (int)(n * ceil(log2(n)));
}

int teor_M(int n) {
    return (int)(n * ceil(log2(n))) + n;
}

int teor(int n) {
    return teor_C(n) + teor_M(n);
}

int main() {
    int sizes[] = {100, 200, 300, 400, 500};
    int num_sizes = sizeof(sizes)/sizeof(sizes[0]);
    
    
    
    printf("|   N   |  M+C   | Факт. значения M+C\n");
    printf("|       | Теория | Убыв. | Случ. | Возр. |\n");

    
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int t = teor(n);
        int u, r, v;
        Queue q_dec;
        initQueue(&q_dec);
        fillQueueDescending(&q_dec, n);
        u = MergeSort(&q_dec);
        freeQueue(&q_dec);
        Queue q_rand;
        initQueue(&q_rand);
        fillQueueRandom(&q_rand, n);
        r = MergeSort(&q_rand);
        freeQueue(&q_rand);
        Queue q_inc;
        initQueue(&q_inc);
        fillQueueAscending(&q_inc, n);
        v = MergeSort(&q_inc);
        freeQueue(&q_inc);
        
        printf("|  %d  |  %4d  |  %4d |  %d |  %d |\n", n, t, u, r, v);
        printf("|_______|________|_______|_______|_______|\n");
    }
}
```

Проект реализует алгоритм сортировки слиянием (Merge Sort) для очереди, основанной на связном списке. Код написан на языке C и включает:
- Реализацию очереди с операциями `enqueue`, `split`, `merge`.
- Подсчет операций сравнения (`C`) и перемещений (`M`) для анализа сложности.
- Сравнение теоретических и фактических значений `M+C` для разных сценариев данных (возрастающих, убывающих, случайных).

---

## 📌 Особенности
- **Структуры данных**:
  - `Node`: Узел списка с полями `data` (значение) и `next` (указатель на следующий узел).
  - `Queue`: Очередь с указателями `head` (начало) и `tail` (конец), а также счетчиком элементов `count`.
- **Алгоритм**:
  - Рекурсивное разделение (`Split`) с использованием метода "быстрого и медленного" указателя.
  - Слияние (`Merge`) двух отсортированных очередей с подсчетом операций.
  - Сортировка (`MergeSort`) с возвратом общего числа операций `M+C`.
- **Тестирование**:
  - Замеры для размеров `N = 100, 200, 300, 400, 500`.
  - Сравнение с теорией: `M+C = n⌈log₂n⌉ + n + n⌈log₂n⌉`.

---

## 🛠 Структура кода

### Основные функции
| Функция                 | Описание                                                                 |
|-------------------------|-------------------------------------------------------------------------|
| `createNode`            | Создает новый узел с заданным значением.                                |
| `enqueue`               | Добавляет элемент в конец очереди.                                      |
| `fillQueueAscending`    | Заполняет очередь числами от 1 до `n`.                                  |
| `fillQueueDescending`   | Заполняет очередь числами от `n` до 1.                                  |
| `fillQueueRandom`       | Заполняет очередь случайными числами (от 0 до `2n`).                    |
| `Split`                 | Делит очередь на две части.                                             |
| `Merge`                 | Сливает две отсортированные очереди в одну.                             |
| `MergeSort`             | Рекурсивно сортирует очередь и возвращает число операций `M+C`.         |

### Вспомогательные функции
| Функция          | Описание                                   |
|------------------|-------------------------------------------|
| `initQueue`      | Инициализирует пустую очередь.            |
| `freeQueue`      | Освобождает память, занятую очередью.     |
| `teor_C`, `teor_M` | Рассчитывает теоретические значения `C` и `M`. |

---

## 📊 Результаты тестирования
Программа выводит таблицу сравнения теоретических и фактических значений `M+C` для трех случаев:
1. **Убывающий порядок** (худший случай для Merge Sort).
2. **Случайный порядок**.
3. **Возрастающий порядок** (лучший случай).

Пример вывода:
```
|   N   |  M+C   | Факт. значения M+C
|       | Теория | Убыв. | Случ. | Возр. |
|  100  |  1500  |   988 |  1216 |  1028 |
|_______|________|_______|_______|_______|
```

---

## 🚀 Как использовать
1. Скомпилируйте код:
   ```bash
   gcc merge_sort_queue.c -o merge_sort -lm
   ```
2. Запустите:
   ```bash
   ./merge_sort
   ```
3. Результаты выводятся в консоль в виде таблицы.

---

## 📚 Теоретическая основа
- **Сложность Merge Sort**:
  - **Время**: O(n log n) для всех случаев.
  - **Память**: O(n) (для массивов), O(1) для связных списков (изменение указателей).
- **Формулы**:
  - Число сравнений: `C = n⌈log₂n⌉`.
  - Число перемещений: `M = n⌈log₂n⌉ + n`.

---

## 🔄 Возможные улучшения
1. **Оптимизация памяти**: Использовать итеративный MergeSort для уменьшения стека вызовов.
2. **Визуализация**: Добавить вывод отсортированной очереди для проверки.
3. **Расширенное тестирование**: Поддержка больших размеров (N > 1000).

