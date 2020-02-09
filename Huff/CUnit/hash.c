#include "header.h"
#include "hash.h"

HASH* create_hash()
{
    HASH* new_hash = (HASH*) malloc(sizeof(HASH));

    for (int i = 0; i < 256; i++)
    {
        new_hash -> array[i] = NULL;
    }
    return new_hash;
}