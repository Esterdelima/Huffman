#include "header.h"
#include "compress.h"
#include <stdbool.h>

typedef struct node NODE;
typedef struct element ELEMENT;
typedef struct hash_table HASH;
typedef struct hash_node HASH_NODE;
typedef struct priority_queue PRIORITY_QUEUE;

// FUNCOES FILA DE PRIORIDADE

PRIORITY_QUEUE *create_priority_queue()
{
    PRIORITY_QUEUE *queue = (PRIORITY_QUEUE *)malloc(sizeof(PRIORITY_QUEUE));
    queue->head = NULL;
    queue->size = 0;

    return queue;
};

void fill_priority_queue(lli *frequence, PRIORITY_QUEUE *queue)
{
    for (int i = 0; i < 256; i++)
    {
        if (frequence[i] != 0)
        {
            NODE *new_node = create_node(frequence[i], i, NULL, NULL);
            enqueue(new_node, queue);
        }
    }
}

void enqueue(NODE *new_node, PRIORITY_QUEUE *queue)
{
    if (queue->head == NULL || new_node->priority <= queue->head->priority)
    {
        new_node->next = queue->head;
        queue->head = new_node;
    }
    else
    {
        NODE *current = queue->head;

        while (current->next != NULL && current->next->priority < new_node->priority)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    queue->size += 1;
}

NODE *dequeue(PRIORITY_QUEUE *queue)
{
    if (queue->head == NULL)
    {
        printf("QUEUE UNDERFLOW\n");
        return NULL;
    }
    queue->size -= 1;
    NODE *first_node = queue->head;
    queue->head = queue->head->next;
    first_node->next = NULL;

    return first_node;
}

void print_queue(NODE *current)
{
    while (current != NULL)
    {
        printf("%c %lld\n", current->caracter, current->priority);
        current = current->next;
    }
    printf("\n");
}

// FUNCOES NODE

NODE *create_node(lli priority, uchar caracter, NODE *left, NODE *right)
{

    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    new_node->priority = priority;
    new_node->caracter = caracter; // representacao do caracter na ASCII.
    new_node->left = left;
    new_node->right = right;
    new_node->next = NULL;

    return new_node;
}

// FUNCOES ARRAY DE FREQUENCIA

void create_freq_array(lli *frequence)
{
    for (int i = 0; i < 256; i++)
    {
        frequence[i] = 0;
    }
}

void fill_freq_array(lli *frequence, FILE* file)
{
    uchar caracter;

    while (fscanf(file, "%c", &caracter) != EOF)
    {
        frequence[caracter] += 1;
    }
    fclose(file);
}

// FUNCOES ARVORE DE HUFFMAN

NODE *create_huff_tree(PRIORITY_QUEUE *queue)
{
    while (queue->size > 1)
    {
        NODE *left_node = dequeue(queue);
        NODE *right_node = dequeue(queue);

        lli sum = left_node->priority + right_node->priority;
        NODE *tree_node = create_node(sum, '*', left_node, right_node);

        enqueue(tree_node, queue);
    }
    //print_queue(queue->head);
    return queue->head;
}

ushort tree_size(NODE *current)
{

    if (current->left == NULL && current->right == NULL)
    {
        if (current->caracter == '*' || current->caracter == '\\')
        {
            return 2;
        }

        else
        {
            return 1;
        }
    }

    return 1 + tree_size(current->left) + tree_size(current->right);
}

void print_pre_order(NODE *bt, FILE *compressed)
{
    if (bt != NULL)
    {
        if (bt->left == NULL && bt->right == NULL && bt->caracter == '*')
        {
            char string[3];
            string[0] = '\\';
            string[1] = '*';
            string[2] = '\0';
            fprintf(compressed, string);
        }
        else fputc(bt->caracter, compressed); 
        print_pre_order(bt->left, compressed);
        print_pre_order(bt->right, compressed);
    }
}

// FUNCOES DE HASH

HASH *create_hash()
{
    HASH *new_hash = (HASH *)malloc(sizeof(HASH));
    for (int i = 0; i < 256; i++)
    {
        new_hash->array[i] = NULL;
    }
    return new_hash;
}

void print_hash(HASH *hash)
{
    for (int i = 0; i < 256; i++)
    {
        if (hash->array[i] != NULL)
        {
            ushort byte = hash->array[i]->code;
            int size = hash->array[i]->size;

            printf("caracter: %c size: %d ", i, size);

            for (int j = 7; j >= 0; j--)
            {
                printf("%d", is_bit_i_set(byte, j));
            }
            printf("\n");
        }
    }
}

// NOVA CODIFICACAO

bool is_bit_i_set(ushort byte, int i)
{
    ushort temp = 1 << i;
    return temp & byte;
}

void new_codification(HASH *hash, NODE *tree, int size, ushort byte)
{
    if (tree->left == NULL && tree->right == NULL)
    { // cheguei numa folha.

        int index = tree->caracter;// pego a representação inteira do caracter(posicao na hash).
        ELEMENT *element = (ELEMENT *)malloc(sizeof(ELEMENT)); // no vazio.

        element->size = size;
        element->code = byte;
        hash->array[index] = element;
        return;
    }

    byte <<= 1;
    new_codification(hash, tree->left, size + 1, byte);

    byte++; // poe 1 no primeiro bit do byte.
    new_codification(hash, tree->right, size + 1, byte);
}

//printando no arq.

ushort take_trash(HASH *hash, lli frequence[])
{
    lli total_bit = 0;

    for (int i = 0; i < 256; i++)
    {
        if (frequence[i] != 0)
        {
            total_bit += hash->array[i]->size * frequence[i];
        }
    }
    if (total_bit % 8 == 0)
    {
        return 0;
    }

    else
    {
        lli conversor = (total_bit / 8) + 1;

        conversor *= 8;

        ushort trash_size = conversor - total_bit;
        
        return trash_size;
    }
}

void create_header(int trash, int size_tree, FILE *compacted)
{
    unsigned char byte;
    printf("%d", trash);
	byte = trash << 5 | size_tree >> 8;
	fprintf(compacted, "%c", byte);
	byte = size_tree;
	fprintf(compacted, "%c", byte);
}

int main()
{
    PRIORITY_QUEUE *queue = create_priority_queue();

    lli frequence[256];

    FILE *file = fopen("file.txt", "rb");

    create_freq_array(frequence);

    fill_freq_array(frequence, file);

    rewind(file);

    fill_priority_queue(frequence, queue);

    NODE *tree = create_huff_tree(queue);

    HASH *hash = create_hash();

    new_codification(hash, tree, 0, 0);

    print_hash(hash);

    ushort trash_size = take_trash(hash, frequence);
    printf("%d\n", trash_size);

    ushort  size_tree = tree_size(tree);
    printf("%d\n\n", size_tree);

    FILE * compacted = fopen("compressed.txt.huff", "wb");

    create_header(trash_size, size_tree, compacted);

    print_pre_order(tree, compacted);

    fclose(compacted);
    fclose(file);

    return 0;
}