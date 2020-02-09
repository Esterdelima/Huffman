#ifndef COMPRESS_H
#define COMPRESS_H
#include "header.h"

// FUNCOES DE FILA

/** @return returns queue */
PRIORITY_QUEUE* create_priority_queue();

/** @param frequence: */
/** @param queue: */
void fill_priority_queue(lli* frequence, PRIORITY_QUEUE* queue);

/** @param new_node: */
/** @param queue: */
void enqueue(NODE* new_node, PRIORITY_QUEUE* queue); 

/** @param current: */
void print_queue(NODE* current);

// FUNCOES NODE

/** @param priority: */
/** @param caracter: */
/** @param left: */
/** @param right: */
/** @return returns */
NODE* create_node(lli priority, uchar caracter, NODE* left, NODE* right);

// FUNCOES ARRAY DE FREQUENCIA

/** @param frequence: */
void create_freq_array(lli* frequence);

/** @param frequence: */
void fill_freq_array(lli* frequence);

// FUNCOES ARVORE DE HUFFMAN

/** @param queue: */
/** @return returns */
NODE* create_huff_tree(PRIORITY_QUEUE* queue);

/** @param current: */
void print_tree(NODE* current);

/** @param tree: */
/** @param file: */
void get_pre_order_tree(NODE* tree, FILE* file);

/** @param current: */
/** @return returns */
bool is_leaf(NODE* current);

// FUNCOES DE HASH

/** @return returns new_hash */
HASH* create_hash();

/** @param hash: */
void print_hash(HASH* hash);

// FUNCOES NOVA CODIFICACAO

/** @param hash: */
/** @param tree: */
/** @param size: */
/** @param byte: */
void new_codification(HASH* hash, NODE* tree, int size, ushort byte);

/** @param frequency: */
void create_freq_array(lli* frequence);

/** @param tree: */
/** @param tree: */
/** @return returns */
bool is_bit_i_set(ushort byte, int i);

// CALCULAR LIXO, TAMANHO DA ÁRVORE E MONTAR O CABEÇALHO

ushort create_file_header(HASH* hash, lli frequence[], NODE* tree, uchar trash, ushort size_tree);

void write_header(ushort header, FILE *compact_file);

/** @param tree: */
/** @return returns */
ushort get_size_tree(NODE* tree);

/** @param hash: */
/** @param frequence: */
/** @return returns */
uchar get_trash(HASH* hash, lli* frequence);

// COMPACTAR ARQUIVO TESTE

/** @param arq_compact: */
/** @param hash: */
/** @param trash_size: */
void compact_file(FILE* arq_compact, HASH* hash, uchar trash_size);

// DESCOMPACTACAO

void descompact(); 

/** @param str: a pointer to the*/
/** @param i: a pointer to the */
/** @return returns  */
NODE* construct_tree(uchar *str, int *i);

#endif