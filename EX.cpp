#include <iostream>
#include <string.h>
#include "arquivo.h"

int main()
{
    int op;
    FILE *arq;

    // Tenta abrir o arquivo para leitura e gravação binária
    if ((arq = fopen("C:\\registro\\guarda.txt", "rb+")) == NULL)
    {
        // Se falhar, tenta criar o arquivo
        if ((arq = fopen("C:\\registro\\guarda.txt", "wb+")) == NULL)
        {
            // Exibe mensagem de erro e encerra o programa
            printf("Falha ao abrir o arquivo!\n");
            system("pause");
            return 1;
        }
    }

    // Loop do menu principal
    do
    {
        system("CLS");
        // Exibe opções do menu
        printf("\n======= AGENDA ======= \n");
		printf("1.Cadastrar\n");
		printf("2.Consultar por codigo\n");
		printf("3.Gerar arquivo\n");
		printf("4.Excluir registro\n");
		printf("5.Sair\n");
		printf("===========Contatos:%d=\n", tamanho(arq));
        printf("Opcao: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            cadastrar(arq);
            break;
        case 2:
            consultar(arq);
            break;
        case 3:
            gerararqtxt(arq);
            break;
        case 4:
            excluir(arq);
            break;
        case 5:
            fclose(arq);
            break;
        }
    } while (op != 5);

    return 0;
}
