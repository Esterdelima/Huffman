#ifndef COMPRESS_H
#define COMPRESS_H
#include "header.h"

// FUNCOES DE FILA

PRIORITY_QUEUE* create_priority_queue();

void fill_priority_queue(lli* frequence, PRIORITY_QUEUE* queue);

void enqueue(NODE* new_node, PRIORITY_QUEUE* queue);

void print_queue(NODE* current);

// FUNCOES NODE

NODE* create_node(lli priority, uchar caracter, NODE* left, NODE* right);

// FUNCOES ARRAY DE FREQUENCIA

void create_freq_array(lli* frequence);

void fill_freq_array(lli* frequence, FILE * file);

// FUNCOES ARVORE DE HUFFMAN

NODE* create_huff_tree(PRIORITY_QUEUE* queue);

ushort tree_size(NODE* current);

// FUNCOES DE HASH

HASH* create_hash();

void print_hash(HASH* hash);

// FUNCOES NOVA CODIFICACAO

void new_codification(HASH* hash, NODE* tree, int size, ushort byte);

void create_freq_array(lli* frequence);

bool is_bit_i_set(ushort byte, int i);

#endif