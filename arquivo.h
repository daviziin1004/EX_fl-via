#include <iostream>
#include <string.h>

							   //+---------+----------+
struct reg  {                  //| Reservas|  Espaço  |
	char nome[20];	           //+---------+----------+
	char tel[20];	           //|  status |  1 byte  |
	char email[20];            //|  email  | 20 bytes |
	char status;               //|  tel    | 20 bytes |
};                             //|  nome   | 20 bytes |
							   //+---------+----------+

// ---- Função para calcular o número de registros no arquivo -----

int tamanho(FILE *arq)
{
    fseek(arq, 0, SEEK_END);
    return ftell(arq) / sizeof(reg);
}

// ------------- Função para cadastrar mais uma pessoa ------------

void cadastrar(FILE *arq)
{
    reg contato;  // Declaração de uma variável do tipo 'reg' chamada 'contato'
    char confirma;  // Declaração de uma variável do tipo char chamada 'confirma'

    contato.status = ' ';  // Inicialização do campo 'status' da estrutura 'contato' com espaço
    memset(contato.nome, 0, sizeof(contato.nome));  // Inicializa o campo 'nome' com zeros
    memset(contato.tel, 0, sizeof(contato.tel));  // Inicializa o campo 'tel' com zeros
    memset(contato.email, 0, sizeof(contato.email));  // Inicializa o campo 'email' com zeros

    fflush(stdin);  // Limpa o buffer de entrada

    // Exibe mensagem indicando o início do processo de cadastro
    printf("Cadastrando novo registro:\n");
    // Imprime o número do próximo registro
    printf("\nNumero do registro: %d\n", tamanho(arq) + 1);

    // Lê informações do novo registro
    printf("Nome..........: ");
    fgets(contato.nome, sizeof(contato.nome), stdin);
    contato.nome[strcspn(contato.nome, "\n")] = '\0';

    printf("Telefone......: ");
    fgets(contato.tel, sizeof(contato.tel), stdin);
    contato.tel[strcspn(contato.tel, "\n")] = '\0';

    printf("E-mail........: ");
    fgets(contato.email, sizeof(contato.email), stdin);
    contato.email[strcspn(contato.email, "\n")] = '\0';

    // Solicita confirmação do usuário
    printf("\nConfirma <s/n>: ");
    fflush(stdin);
    scanf(" %c", &confirma);

    // Se o usuário confirmar, grava o registro no arquivo
    if (toupper(confirma) == 'S')
    {
        printf("\nGravando...\n\n");
        fseek(arq, 0, SEEK_END);
        fwrite(&contato, sizeof(reg), 1, arq);
    }

    system("pause");
}

// ---- Função para consultar um registro no arquivo por código ----

void consultar(FILE *arq)
{
    reg contato;
    int nr;

    printf("\nConsulta pelo codigo\n");
    printf("\nInforme o Codigo...: ");
    scanf("%d", &nr);

    // Verifica se o número de registro é válido
    if ((nr <= tamanho(arq)) && (nr > 0))
    {
        fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
        fread(&contato, sizeof(reg), 1, arq);

        // Verifica se o registro está ativo
        if (contato.status == ' ')
        {
            printf("\nNome......: %s", contato.nome);
            printf("\nTelefone..: %s", contato.tel);
            printf("\nE-mail....: %s\n\n", contato.email);
        }
        else
        {
            printf("\nRegistro excluido! \n");
        }
    }
    else
    {
        printf("\nNumero de registro invalido!\n");
    }

    system("pause");
}

// ------------- Função para gerar um arquivo de texto ------------

void gerararqtxt(FILE *arq)
{
    FILE *arqtxt = fopen("C:\\registro\\arquivo.txt", "w");

    if (!arqtxt)
    {
        printf("Não foi possível criar esse arquivo!\n");
        system("pause");
        return;
    }

    // Imprime cabeçalho no arquivo de texto
    fprintf(arqtxt, "Nome                Telefone    E-mail                   Status\n");
    fprintf(arqtxt, "================================================================\n");

    int nr;
    reg contato;

    // Loop para percorrer os registros do arquivo original
    for (nr = 0; nr < tamanho(arq); nr++)
    {
        fseek(arq, nr * sizeof(reg), SEEK_SET);
        fread(&contato, sizeof(reg), 1, arq);

        // Imprime os dados no arquivo de texto
        fprintf(arqtxt, "%-20s%-12s%-25s- %c\n", contato.nome, contato.tel, contato.email, contato.status);
    }

    fclose(arqtxt);
}

// ----------- Função para excluir um registro no arquivo ----------

void excluir(FILE *arq)
{
    reg contato;
    char confirma;
    int nr;

    // Solicita o código do registro a ser excluído
    printf("\nInforme o codigo do registro para excluir: ");
    scanf("%d", &nr);

    // Verifica se o número de registro é válido
    if ((nr <= tamanho(arq)) && (nr > 0))
    {
        fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
        fread(&contato, sizeof(reg), 1, arq);

        // Verifica se o registro está ativo
        if (contato.status == ' ')
        {
            printf("\nNome......: %s", contato.nome);
            printf("\nTelefone..: %s", contato.tel);
            printf("\nE-mail....: %s\n", contato.email);
            printf("\nConfirma a exclusao: <s/n>\n");
            fflush(stdin);
            scanf(" %c", &confirma);

            // Se o usuário confirmar, exclui o registro
            if (toupper(confirma) == 'S')
            {
                printf("\nExcluindo...\n\n");
                fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
                contato.status = '*';
                fwrite(&contato, sizeof(reg), 1, arq);
            }
        }
        else
        {
            printf("Registro inexistente! \n");
        }
    }
    else
    {
        printf("\nNumero de registro invalido!\n");
    }

    system("pause");
}


