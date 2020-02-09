#ifndef TREE_H
#define TREE_H
#include "header.h"
#include "queue.h"

NODE* create_node(lli priority, uchar caracter, NODE* left, NODE* right);

NODE* create_huff_tree(PRIORITY_QUEUE* queue);

bool is_leaf(NODE* current);

#endif