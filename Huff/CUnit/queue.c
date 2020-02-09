#include "header.h"
#include "queue.h"

PRIORITY_QUEUE* create_priority_queue()
{
    PRIORITY_QUEUE* queue = (PRIORITY_QUEUE*) malloc(sizeof(PRIORITY_QUEUE));

    queue -> head = NULL; 
    queue -> size = 0;

    return queue;
};

void fill_priority_queue(lli frequence[], PRIORITY_QUEUE* queue)
{
    for (int i = 0; i < 256; i++)
    {
        if (frequence[i] != 0)
        {
            NODE* new_node = create_node(frequence[i], i, NULL, NULL);
            enqueue(new_node, queue);
        }
    }
}

void enqueue(NODE* new_node, PRIORITY_QUEUE* queue)
{
    if (queue -> head == NULL || new_node -> priority <= queue -> head -> priority)
    {
        new_node -> next = queue -> head;
        queue -> head = new_node;
    } 
    else
    {
        NODE* current = queue -> head;

        while (current -> next != NULL && current-> next-> priority < new_node -> priority)
        {
            current = current->next;
        }
        new_node -> next = current -> next;
        current -> next = new_node;
    }
    queue -> size += 1;
}

NODE* dequeue(PRIORITY_QUEUE* queue)
{
    if (queue -> head == NULL)
    {
        printf("QUEUE UNDERFLOW\n");
        return NULL;
    }
    queue -> size -= 1;
    NODE* first_node = queue -> head;
    queue -> head = queue -> head -> next;
    first_node -> next = NULL;
    
    return first_node;
}

