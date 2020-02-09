#include "decompress.h"

NODE* construct_tree(uchar str[], int *i) 
{
   if (str[*i] != '*') 
   { // no folha
        if (str[*i] == '\\') *i += 1;
        
        NODE* leaf = create_node(0, str[*i], NULL, NULL);
        
        return leaf;
   }
   else 
   {
        NODE* tree = create_node(0, '*', NULL, NULL);

        *i += 1;
        tree->left = construct_tree(str, i);

        *i += 1;
        tree->right = construct_tree(str, i);

        return tree;
   }
}

// FUNCAO DE DESCOMPRESSAO

void descompact(FILE *compacted_file, char output_filename[256], NODE *tree, lli quant_bytes, ushort trash) 
{
    // DESCOMPACTAR
    NODE* current = tree; 
    uchar byte = 0;
    int limit = 0;

    FILE* descompacted_file = fopen(output_filename, "wb");

    for (quant_bytes; quant_bytes > 0; quant_bytes--) 
    { // conta os bytes percorridos.
        fscanf(compacted_file, "%c", &byte);
        
        if (quant_bytes == 1) 
        { // ultimo byte com o lixo (so verificamos esse byte ate o seu lixo).
            limit = trash; 
        }

        for (int i = 7; i >= limit; i--)
        {
            if (is_bit_i_set(byte, i)) 
            {
                current = current -> right; // 1 -> direita (bit setado com 1)
            } 
            else 
            {
                current = current -> left; // 0 -> esquerda (bit setado com 0)
            }
            if (is_leaf(current)) 
            { // folha, hora de printar o caracter no novo arquivo :D.
                fputc(*(uchar*) (current -> caracter), descompacted_file);
                current = tree; // ponteiro pro inicio da arvore.
            }
        }
    }
    fclose(descompacted_file);
}

int decompress()
{
    char input_filename[256];
    char output_filename[256];
    printf("\nDigite o nome do arquivo:\n\n");

    scanf("%s", input_filename);
    int size = strlen(input_filename) - 5; // 5 pelos 5 caracteres do ".huff"
    int i;

    for(i = 0; i < size; i++) {
        output_filename[i] = input_filename[i];
    }
    output_filename[i] = '\0';

    FILE* file = fopen(input_filename, "rb");

    if(file == NULL)
    {
        printf("Empty file\n");
        return 0;
    }

    FILE* compacted_file = fopen(input_filename, "rb"); // arquivo de escrita compactada
    
    uchar byte_1, byte_2;  // retirar os 2 primeiros bytes do cabeçalho para pegar o lixo e tamanho da árvore.
    
    fscanf(compacted_file, "%c", &byte_1); // pego o primeiro byte do arquivo compactado (que contem os 3 bits de lixo).
    fscanf(compacted_file, "%c", &byte_2); // pego o segundo byte do arquivo compactado (com parte do tamanho da arvore).

    // PEGAR O LIXO E O TAMANHO DA ARVORE

    ushort trash = byte_1 >> 5; // elimina os 5 bits do tamanho da arvore.
    ushort size_tree = byte_1 << 11;   // anda 8 bits pra passar pro byte + a esquerda, +3 pra sumir c os 3 bits de lixo.
    size_tree >>= 3;            // os 3 bits de lixo voltam zerados.
    size_tree |= byte_2;        // recebe o restante do tamanho da arvore no 2 byte.

    uchar str[size_tree];       // salva a arvore em pre ordem

    // le a arvore em pre ordem no arquivo compacatado.

    for (i = 0; i < size_tree; i++) 
    { 
        fscanf(compacted_file, "%c", &str[i]);
    }
    // CONSTRUIR A ARVORE
    i = 0;
    NODE* tree = construct_tree(str, &i);

    // CONTAR OS BYTES DO ARQUIVO

    lli quant_bytes = 0;
    uchar byte; // so pra ler e contar os bytes msm

    while (fscanf(compacted_file, "%c", &byte) != EOF) 
    {
        quant_bytes++;
    }

    fseek(compacted_file, 2 + size_tree, SEEK_SET); // função de percorrer o arquivo a partir de um ponto especifico.

    descompact(compacted_file, output_filename, tree, quant_bytes, trash);
    fclose(compacted_file);

    return 1;
}