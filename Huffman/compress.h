#ifndef COMPRESS_H
#define COMPRESS_H
#include "header.h"

// prenche o rray com caracter e fraquencia 
/** @param frequence: array/ string de frequencias */
/** @param input_filename: arquivo de entrada para leitura*/
/** @return void */
void fill_freq_array(lli* frequence, char input_filename[50]);


//cria a lista de prioridade e preenche com 0.
/** @return returns queue */
PRIORITY_QUEUE* create_priority_queue();

//preenche a fila e aloca a frenquencia na posiççao do nó
/** @param frequence: */
/** @param queue: */
/** @return void */
void fill_priority_queue(lli frequence[256], PRIORITY_QUEUE* queue);


// enfileira e posiciona o nó na posiçao certa.
/** @param new_node: */
/** @param queue: */
/** @return void*/
void enqueue(NODE* new_node, PRIORITY_QUEUE* queue); 

/*desinfileira a fila */
/** @param  queue: */
/** @return nó: */
NODE* dequeue(PRIORITY_QUEUE* queue);


// faz a alocação na mémoria e trata os ponteiros soltos
/** @param priority: */
/** @param caracter: */
/** @param left: */
/** @param right: */
/** @return node: */
NODE* create_node(lli priority, uchar caracter, NODE* left, NODE* right);

// codifica a árvore do Huffman
/** @param queue: */
/** @return returns */
NODE* create_huff_tree(PRIORITY_QUEUE* queue);

// ver o tamanho da arvore.
/** @param tree: */
/** @return returns */
ushort get_size_tree(NODE* tree);

// imprime a arvore no arquivo.
/** @param tree: */
/** @param file: */
void print_tree(NODE* tree, FILE* compacted_file);

// verifica se é folha da arvore.
/** @param current: */
/** @return returns */
bool is_leaf(NODE* current);

// FUNCOES DE HASH

//cria a Hash
/** @return returns new_hash */
HASH* create_hash();

// FUNCOES NOVA CODIFICACAO


// dá a codificação da arvore de Huffman
/** @param hash: */
/** @param tree: */
/** @param size: */
/** @param byte: */
void new_codification(HASH* hash, NODE* tree, int size, ushort byte);

// verifica se o birt está setado.
/** @param tree: */
/** @param tree: */
/** @return returns */
bool is_bit_i_set(ushort byte, int i);


// xver o tamanho do lixo.
/** @param hash: */
/** @param frequence: */
/** @return returns */
uchar get_trash(HASH* hash, lli* frequence);

// cria o cabeçalho
ushort create_header(HASH* hash, NODE* tree, uchar trash, ushort tree_size);

// escreve no arquivo o cabeçalho.
void write_header(ushort header, FILE *compact_file);

//compactar o arquivo e escreve no arquivo compactado.
/** @param arq_compact: */
/** @param hash: */
/** @param trash_size: */
void compact_file(FILE* arq_compact, char input_filename[50], HASH* hash, uchar trash);

int compress();

#endif