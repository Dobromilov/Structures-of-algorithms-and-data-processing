#include <stdlib.h>
#include <time.h>
#include  <stdio.h>
#define N 10

typedef struct Node {
    int data;           
    struct Node *next;  
} node_t;


node_t *NewNode(int data){
    node_t *n = malloc(sizeof(node_t));
    n->data=data;
    n->next=NULL;
    return n;
}

// === queue ===

typedef struct{
    node_t *front;
    node_t *rear;
}queue_t;


void initqueue(queue_t *q){
    q->front=q->rear=NULL;
}


// Добавление элемента в конец очереди
void enqueue(queue_t *q, int data){
    node_t *n=NewNode(data);
    if (q->rear ==NULL){
        q->front=n;
        q->rear=n;
    } else {
        q->rear->next=n;
        q->rear=n;
    }
}


// Удаление элемента из начала очереди
int dequeue(queue_t *q){
    if (q->front == NULL) {
        exit(EXIT_FAILURE);
    }
    node_t *n = q->front;
    int value = n->data;
    q->front=n->next;
    
    if (q->front==NULL){
        q->rear=NULL;
    }
    
    free(n);
    
    return value;
}


void fillQueueAscending(queue_t *q, int n){
    for (int i=1; i<=n;i++){
        enqueue(q,i);
    }
}


void fillQueueDescending(queue_t *q, int n) {
    for (int i = n; i >= 1; i--) {
        enqueue(q, i);
    }
}


void fillQueueRandom(queue_t *q, int n, int minVal, int maxVal) {
    for (int i = 0; i < n; i++) {
        int num = minVal + rand() % (maxVal - minVal + 1);
        enqueue(q, num);
    }
}


// === stack ===

typedef struct {
    node_t *top;
}stack_t;


void initstack(stack_t *s){
    s->top=NULL;
}


void push(stack_t *s, int data){
    node_t *n=NewNode(data);
    n->next = s->top; //Устанавливаем ссылку на старую вершину
    s->top = n;
}


int pop(stack_t *s){
    if (!s->top){
        fprintf(stderr, "Error: pop from empty stack\n");
        exit(EXIT_FAILURE);
    }
    node_t *n = s->top;
    int value = n->data;
    s->top=n->next;
    free(n);
    return value;
}


void clearstack(stack_t *s) {
    node_t *current = s->top;
    while (current) {
        node_t *tmp = current;
        current = current->next;
        free(tmp);
    }
    s->top = NULL;
}


void fillstackascending(stack_t *s, int n) {
    for (int i = 1; i <= n; i++) { 
        push(s, i);        
    }
}


void fillstackdescending(stack_t *s, int n) {
    for (int i = n; i >= 1; i--) { 
        push(s, i);
    }
}


void fillstackrandom(stack_t *s, int n, int minVal, int maxVal) {
    for (int i = 0; i < n; i++) {
        int num = minVal + rand() % (maxVal - minVal + 1); 
        push(s, num); 
    }
}


void clearqueue(queue_t *q){
    node_t *current = q->front;
    while (current != NULL){
        node_t *tmp = current;
        current = current->next;
        free(tmp);
    }
    
    q->front=q->rear=NULL;
}


void printlist(node_t *head) {
    node_t *current=head;
    while (current){
        printf("%d ",current->data);
        current=current->next;
    }
    printf("\n");
}


void printforward(node_t *head) {
    if (!head){
        printf("\n");
        return;
    } else {
        printf("%d ",head->data);
        printforward(head->next);
    }
}


void printbackward(node_t *head) {
    if (!head){
        return;
    }
    printbackward(head->next);
    printf("%d ", head->data);
}

// ======== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ========

int countseries(node_t *head) {
    if (!head) return 0;
    int series = 1;
    node_t *current = head;
    while (current->next) {
        if (current->data > current->next->data) {
            series++;
        }
        current = current->next;
    }
    return series;
}


int calculatechecksum(node_t *head) {
    int sum = 0;
    node_t *current = head;
    while (current) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}


int main(void) {
    srand((unsigned)time(NULL));

    stack_t s;
    initstack(&s);

    // --- ДЕМОНСТРАЦИЯ СТЕКА ---

    // 1) Заполнение по возрастанию
    printf("=== Стек: заполнение по возрастанию ===\n");
    fillstackascending(&s, N);
    printlist(s.top);
    printf("Контрольная сумма: %d\n", calculatechecksum(s.top));
    printf("Количество серий: %d\n", countseries(s.top));
    printf("Рекурсивный прямой обход: "); printforward(s.top); printf("\n");
    printf("Рекурсивный обратный обход: "); printbackward(s.top); printf("\n");
    printf("Извлечён элемент: %d\n", pop(&s));
    printf("После извлечения: "); printlist(s.top);
    clearstack(&s);
    printf("\n");

    // 2) Заполнение по убыванию
    printf("=== Стек: заполнение по убыванию ===\n");
    initstack(&s);
    fillstackdescending(&s, N);
    printlist(s.top);
    printf("Контрольная сумма: %d\n", calculatechecksum(s.top));
    printf("Количество серий: %d\n", countseries(s.top));
    printf("Рекурсивный прямой обход: "); printforward(s.top); printf("\n");
    printf("Рекурсивный обратный обход: "); printbackward(s.top); printf("\n");
    printf("Извлечён элемент: %d\n", pop(&s));
    printf("После извлечения: "); printlist(s.top);
    clearstack(&s);
    printf("\n");

    // 3) Случайное заполнение
    printf("=== Стек: случайное заполнение ===\n");
    initstack(&s);
    fillstackrandom(&s, N, 10, 99);
    printlist(s.top);
    printf("Контрольная сумма: %d\n", calculatechecksum(s.top));
    printf("Количество серий: %d\n", countseries(s.top));
    printf("Рекурсивный прямой обход: "); printforward(s.top); printf("\n");
    printf("Рекурсивный обратный обход: "); printbackward(s.top); printf("\n");
    printf("Извлечён элемент: %d\n", pop(&s));
    printf("После извлечения: "); printlist(s.top);
    clearstack(&s);
    printf("\n");

    // --- ДЕМОНСТРАЦИЯ ОЧЕРЕДИ ---

    queue_t q;
    initqueue(&q);

    // 4) Заполнение по возрастанию
    printf("=== Очередь: заполнение по возрастанию ===\n");
    fillQueueAscending(&q, N);
    printlist(q.front);
    printf("Контрольная сумма: %d\n", calculatechecksum(q.front));
    printf("Количество серий: %d\n", countseries(q.front));
    printf("Рекурсивный прямой обход: "); printforward(q.front); printf("\n");
    printf("Рекурсивный обратный обход: "); printbackward(q.front); printf("\n");
    printf("Удалён элемент: %d\n", dequeue(&q));
    printf("После удаления: "); printlist(q.front);
    clearqueue(&q);
    printf("\n");

    // 5) Заполнение по убыванию
    printf("=== Очередь: заполнение по убыванию ===\n");
    initqueue(&q);
    fillQueueDescending(&q, N);
    printlist(q.front);
    printf("Контрольная сумма: %d\n", calculatechecksum(q.front));
    printf("Количество серий: %d\n", countseries(q.front));
    printf("Рекурсивный прямой обход: "); printforward(q.front); printf("\n");
    printf("Рекурсивный обратный обход: "); printbackward(q.front); printf("\n");
    printf("Удалён элемент: %d\n", dequeue(&q));
    printf("После удаления: "); printlist(q.front);
    clearqueue(&q);
    printf("\n");

    // 6) Случайное заполнение
    printf("=== Очередь: случайное заполнение ===\n");
    initqueue(&q);
    fillQueueRandom(&q, N, 10, 99);
    printlist(q.front);
    printf("Контрольная сумма: %d\n", calculatechecksum(q.front));
    printf("Количество серий: %d\n", countseries(q.front));
    printf("Рекурсивный прямой обход: "); printforward(q.front); printf("\n");
    printf("Рекурсивный обратный обход: "); printbackward(q.front); printf("\n");
    printf("Удалён элемент: %d\n", dequeue(&q));
    printf("После удаления: "); printlist(q.front);
    clearqueue(&q);

    return 0;
}
