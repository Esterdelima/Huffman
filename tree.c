#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct node NODE;
typedef struct priority_queue PRIORITY_QUEUE;

struct node
{
    unsigned char item;
    int priority;
    NODE *next; 
    NODE *right;
    NODE *left;
};
struct priority_queue
{
    int size;
    NODE *head;
};
NODE *create_tree(NODE * R_node, NODE *L_node)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node -> right = R_node;
    new_node -> left = L_node;
    return new_node;
}
PRIORITY_QUEUE *create_pq()
{
    PRIORITY_QUEUE *new_queue = malloc(sizeof(PRIORITY_QUEUE));
    new_queue -> head = NULL;
    new_queue ->size = 0;
    return new_queue; 
}
void enqueue(PRIORITY_QUEUE *pq,char i,int frequencia,NODE *new_node)
{
        new_node->item  = i;
        new_node->  priority =frequencia;
        if(pq != NULL ||frequencia < pq->head->priority)
        {
            new_node -> next = pq->head;
            pq->head = new_node;
        }
        else{
            NODE *current = pq->head;
            while(current->next != NULL && current->next->priority >frequencia )
            {
                current = current->next;
            }
            new_node -> next = current->next;
            current -> next = new_node;
        }
        pq ->size++;
}
NODE *dequeue(PRIORITY_QUEUE *pq)
{
    if(pq == NULL)
    {
        printf("Priority Queue undeflow");
        return NULL;
    }
    else
    {
        pq-> size--;
        NODE *node = pq->head;
        pq->head = pq->head->next;
        return node;
    }
    
}
void print_tree(NODE *root)
{
    if(root != NULL)
    {
        printf("%c",root->item);
        print_tree(root->left);
        print_tree(root->right);
    }
}

/*int fseek(FILE *fp,long numbytes,int origem); -----------> ele pode pular para outra parte do arquivo,de acordo com oque passar.
 
int rewind(FILE *fp); ---- > voltar para o começo do arquivo 
*/
int main(){
    FILE *arq;
    arq = fopen("input.txt","rb");
    PRIORITY_QUEUE *pq = create_pq();
    int array[257];
    unsigned char c;
   for(int i = 0 ;  i<257; i++)
   {
       array[i] = 0;
   }
    
    while(fscanf(arq,"%c",&c) != EOF)
    {
        array[c] += 1; 
        
    }
    for(int j = 0;j<257;j++)
    {
        if(array[j] != 0)
        {
            NODE * new_node = malloc(sizeof(NODE));
            new_node -> next = NULL;
            enqueue(pq,j,array[j],new_node);
        }
    }
    while(pq->size >1)
    {
        NODE *R_node = dequeue(pq);
        NODE *L_node = dequeue(pq);
        NODE *tree_node = create_tree(R_node,L_node);
        enqueue(pq,'*',R_node->priority+ L_node->priority,tree_node);
    }
    print_tree(pq->head);
    printf("\n");
    
}
