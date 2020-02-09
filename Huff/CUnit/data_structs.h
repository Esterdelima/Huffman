#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

#define lli long long int
typedef unsigned char uchar;
typedef unsigned short ushort;

typedef struct element ELEMENT;
typedef struct hash_table HASH;
typedef struct node NODE;
typedef struct priority_queue PRIORITY_QUEUE;


struct element 
{
    int size; 
    void* code; // ushort
};

struct hash_table 
{
    ELEMENT* array[256];
};

struct node 
{
    lli priority;
    void *caracter; // uchar
    NODE *next; 
    NODE *left; 
    NODE *right; 
};

struct priority_queue 
{
    lli size;
    NODE *head; 
};

#endif