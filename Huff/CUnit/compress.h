#ifndef QUEUE_H
#define QUEUE_H
#include "header.h"

void fill_freq_array(lli* frequence);

bool is_bit_i_set(ushort byte, int i);

void new_codification(HASH* hash, NODE* tree, int size, ushort byte);

void write_header(ushort header, FILE* compact_file);

ushort create_file_header(HASH* hash, lli frequence[], NODE* tree, uchar trash, ushort size_tree);

ushort get_size_tree(NODE* tree);

uchar get_trash(HASH* hash, lli* frequence);

void compact_file(FILE* compacted_file, HASH* hash, uchar trash_size);

#endif
