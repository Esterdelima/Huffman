#include "header.h"
#include "compress.h"
#include "descompress.h"
#include "compress.c"
#include "descompress.c"

void menu()
{
    printf("\n=============================\n");
    printf("\n\tHUFFMAN\n");
    printf("\n=============================\n");

    while(1)
    {
        int choice;
        printf("\nEscolha uma opção:\n\n1 >> Compress\n\n2 >> Descompress\n\n3 >> Exit\n\n");
    
        scanf("%d", &choice);

        //char name[200];

        if(choice == 1)
        {
            //printf("\nDigite o nome do arquivo:\n\n");

            //scanf("%s", name);

            //FILE* file = fopen(name, "rb");

            if(file == NULL)
            {
                printf("Empty file\n");
                break;
            }
            
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

            printf("\n\nO arquivo foi compactado com sucesso!\n\n");

            fclose(compacted_file);
        }

        else if(choice == 2)
        {
            descompact();
            printf("\n\nO arquivo foi descompactado com sucesso!\n\n");
            break;
        }

        else if(choice == 3) return;
        
        else
        {
            printf("\n\nOperação inválida. Tente novamente.\n\n");
            return;
        }
    }
    return;   
}