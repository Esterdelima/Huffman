#include <stdio.h>
#include <stdlib.h>

#define TRUE 1

int main()
{
    while (TRUE)
    {
        printf("Escolha o que deseja fazer primeiro:\n 1.Descompactar;\n 2.Compactar;\n 0.Sair;\n");
        int option;

        scanf("%d", &option);

        if (option == 1)
        {
            //compress();
        }

        else if (option == 2)
        {
           //unpack();
        }

        else if(option == 0)
        {
            break;
        }

        else
        {
            printf("\nPor favor, digite um numero valido.\n\n");
        }
        
    }

    return 0;
}