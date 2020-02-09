#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long int lli;
typedef struct node NODE;
typedef struct priority_queue PRIORITY_QUEUE;
typedef struct heap HEAP;
#define MAX_SIZE 10000

// O valor do indice representa a prioridade

struct node {
    lli priority;
    NODE* next;
};

struct priority_queue {
    lli size;
    NODE* head;
};

struct heap {
    lli size;
    lli array[MAX_SIZE];
};

NODE* create_node(lli priority) {
    NODE* new_node = (NODE*) malloc(sizeof(NODE));
    new_node -> priority = priority;
    new_node -> next = NULL;
    return new_node;
}

HEAP* create_heap() {
    HEAP* heap = (HEAP*) malloc(sizeof(HEAP));

    heap->size = 0;
    
    for (lli i = 0; i < MAX_SIZE; ++i) {
        heap->array[i] = 0;
    }

    return heap;
}

PRIORITY_QUEUE* create_priority_queue() {
    PRIORITY_QUEUE* queue = (PRIORITY_QUEUE*) malloc(sizeof(PRIORITY_QUEUE));

    queue -> head = NULL; 
    queue -> size = 0;

    return queue;
};

void priority_queue_enqueue(PRIORITY_QUEUE* queue, lli priority, lli* count) {
    NODE* new_node = create_node(priority);

    if (queue -> head == NULL || new_node -> priority <= queue -> head -> priority) {
        *count += 1;
        new_node -> next = queue -> head;
        queue -> head = new_node;
    } else {
        NODE* current = queue -> head;

        while (current -> next != NULL && current-> next-> priority < new_node -> priority) {
            *count += 1;
            current = current->next;
        }
        new_node -> next = current -> next;
        current -> next = new_node;
    }
    queue -> size += 1;
}

void swap(HEAP* heap, lli dad, lli son) {
    lli aux;

    aux = heap->array[dad];
    heap->array[dad] = heap->array[son];
    heap->array[son] = aux;
}

void heap_enqueue(HEAP* heap, lli priority, lli* count) {
    lli i = heap->size;
    heap->array[i] = priority;
    heap->size += 1;

    *count += 1;
    
    while(i > 0 && heap->array[i / 2] >= heap->array[i]) {
        *count += 1;
        swap(heap, i / 2, i);
        i = i / 2;
    }
}

int main() {
    PRIORITY_QUEUE* queue = create_priority_queue();
    HEAP* heap = create_heap();
    lli count_priority_queue = 0;
	lli count_heap = 0;
    lli random_number;
    lli i;

    FILE* output = fopen("fila_com_e_sem_heap", "wb");
    fprintf(output, "value without_heap with_heap\n");
    
	printf("Iniciando a inserção nas filas\n");
	for(i = 0; i < MAX_SIZE; i++) {
        random_number = rand() % 1000; // gera numero aleatorio entre 0 e 1000 (mil)

		priority_queue_enqueue(queue, random_number, &count_priority_queue);
		heap_enqueue(heap, random_number, &count_heap);

		fprintf(output, "%lld %lld %lld\n", random_number, count_priority_queue, count_heap);
		
		count_priority_queue = 0;
		count_heap = 0;
	}

    printf("Inserção nas filas concluida com sucesso\n");

	fclose(output);
    return 0;
}