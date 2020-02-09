#ifndef QUEUE_H
#define QUEUE_H
#include "header.h"

PRIORITY_QUEUE* create_priority_queue();

void fill_priority_queue(lli frequence[], PRIORITY_QUEUE* queue);

void enqueue(NODE* new_node, PRIORITY_QUEUE* queue);

NODE* dequeue(PRIORITY_QUEUE* queue);

#endif
