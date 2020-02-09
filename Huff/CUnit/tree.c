#include "header.h"
#include "queue.h"
#include "tree.h"


NODE* create_node(lli priority, uchar caracter, NODE* left, NODE* right)
{
    NODE* new_node = (NODE*) malloc(sizeof(NODE));
    // parte do cast do caracter *void
    uchar* aux = (uchar*) malloc(sizeof(uchar)); // aloco para nao ser uma variavel temporaria na funcao.
    *aux = caracter;
    new_node -> caracter = aux; // representacao do caracter na ASCII.

    new_node -> priority = priority;
    new_node -> left = left;
    new_node -> right = right;
    new_node -> next = NULL;

    return new_node;
}

NODE* create_huff_tree(PRIORITY_QUEUE* queue)
{
    while (queue -> size > 1)
    {
        NODE* left_node = dequeue(queue);
        NODE* right_node = dequeue(queue);
        
        lli sum = left_node -> priority + right_node -> priority;
        NODE* tree_node = create_node(sum, '*', left_node, right_node);

        enqueue(tree_node, queue);
    }
    return queue -> head;
}

bool is_leaf(NODE* current)
{
    if (current -> left == NULL && current -> right == NULL) return true;
    else return false;
}