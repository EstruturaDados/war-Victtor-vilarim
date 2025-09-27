#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define tamanho_tabuleiro 5

typedef struct
{
    char nome[30];
    char cor[10];
    int Qnt_tropas;

} mundo;

void detalhe(int vezes)
{
    static int n = 1;
    for (size_t i = 0; i < vezes; i++)
    {
        if ((vezes / 2) == i)
        {
            printf("exercito %d", n);
            n++;
        }
        printf("=");
    }
    printf("\n");
}

void ler(const char *prompt, char *text, int tamanho)
{
    while (1)
    {
        printf("%s", prompt);
        if (fgets(text, tamanho, stdin) == NULL)
        {
            printf("Erro de leitura\n");
            break;
        }

        size_t len = strlen(text);
        if (len > 0 && text[len - 1] == '\n')
        {
            text[len - 1] = '\0';
            break;
        }
        else
        {
            int ch;
            int i = 1;
            while ((ch = getchar()) != '\n' && EOF != '\n')
            {
                i++;
            }
            printf("Digite %d caracteres a menos\n", i);
        }
    }
}

int Ler_int(const char *prompt, int tamanho)
{
    int valor;
    char buffer[64];
    while (1)
    {
        printf(prompt);
        if (fgets(buffer, tamanho, stdin) == NULL)
        {
            printf("Erro na leitura, tente novamente");
            continue;
        }
        if (sscanf(buffer, "%d", &valor) == 1)
            return valor;
        continue;
    }
}

void menu(int *qnt, int *ctrl)
{
    printf("\n===Menu do Jogo===\n");
    if (*qnt < tamanho_tabuleiro)
        printf("1 - Adicionar exercito\n");
    else if(*ctrl != 0)
        printf("2 - Visualizar exercito\n");
    printf("3 - Sair\n");
    return;
}

void main()
{
    int controle = 1;
    char buffer[64];
    mundo jogo[tamanho_tabuleiro];

    int opcao;
    int quantidade_exercitos = 0;

    menu(&quantidade_exercitos, &controle);
    opcao = Ler_int("Sua escolha: ", sizeof(buffer));

    while (opcao < 3 && opcao > 0)
    {
        if (opcao == 1)
        {
            ler("Qual o Nome do exercito? ", jogo[quantidade_exercitos].nome, sizeof(buffer));

            jogo[quantidade_exercitos].Qnt_tropas = Ler_int("Digite o numero de Tropas: ", sizeof(buffer));

            ler("Qual a Cor do exercito? ", jogo[quantidade_exercitos].cor, sizeof(buffer));

            printf("\nExercito registrado!\n");

            quantidade_exercitos++;
        }
        else if (opcao == 2 && quantidade_exercitos == tamanho_tabuleiro && controle == 1)
        {
            controle = 0;
            for (size_t i = 0; i < quantidade_exercitos; i++)
            {
                detalhe(20);
                printf("Nome: %s\n", jogo[i].nome);
                printf("Cor: %s\n", jogo[i].cor);
                printf("%d Tropas\n", jogo[i].Qnt_tropas);
            }
        }
    novamente:
        menu(&quantidade_exercitos, &controle);
        opcao = Ler_int("Sua escolha: ", sizeof(int));
        if (opcao >= 3 || opcao <= 0)
            printf("Saindo...");
        else if ((quantidade_exercitos == tamanho_tabuleiro) && opcao == 1)
            goto novamente;
        else if (opcao == 2 && controle == 0)
            goto novamente;
        
    }
}
