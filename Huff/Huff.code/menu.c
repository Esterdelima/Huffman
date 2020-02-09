#include "header.h"
#include "compress.h"
#include "descompress.h"
#include "compress.c"
#include "descompress.c"

void menu()
{
    printf("\n====================================\n");
    printf("\n            HUFFMAN\n");
    printf("\n====================================\n");

    while(1)
    {
        int choice, i;
        printf("\nEscolha uma opção:\n\n1 >> Compress\n\n2 >> Descompress\n\n3 >> Exit\n\n");
    
        scanf("%d", &choice);

        char name[256];

        switch(choice)
        {
            case 1:
            {                
                    lli frequence[256] = {0};

                    fill_freq_array(frequence);

                    PRIORITY_QUEUE* queue = create_priority_queue();
                    fill_priority_queue(frequence, queue);
                    //print_queue(queue->head);

                    NODE* tree = create_huff_tree(queue);
                    //print_tree(tree);

                    HASH* hash = create_hash();
                    new_codification(hash, tree, 0, 0); 
                    
                    //print_hash(hash);

                    FILE* compacted_file = fopen("video.mp4.huff", "wb"); // arquivo de escrita compactado.
                    
                    uchar trash = get_trash(hash, frequence); // trash so ocupa 3 bits, por isso so alocamos 1 byte para guardar o lixo.
                    ushort size_tree = get_size_tree(tree);
                    //printf("lixo %d\n arvore %u\n", trash, size_tree);

                    ushort header = create_file_header(hash, frequence, tree, trash, size_tree);
                    write_header(header, compacted_file); // escrever o cabeçalho no arquivo compactado.
                    
                    get_pre_order_tree(tree, compacted_file);
                    compact_file(compacted_file, hash, trash);

                    fclose(compacted_file);
                
            }

            case 2:
            {
                descompact();
            }

            case 3:
            {
                return;
            } 
        }
    }
    return;   
}