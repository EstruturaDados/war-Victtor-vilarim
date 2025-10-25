#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

char buffer[64];

typedef struct
{
    char nome[30];
    char cor[10];
    int Qnt_tropas;
    int jogador;

} mundo;

void detalhe(int vezes, int *n)
{
    puts("");
    for (size_t i = 0; i < vezes; i++)
    {
        if (*n != -1 && i == vezes / 2)
            if ((vezes / 2) == i)
                printf("exercito %d", *n + 1);

        printf("=");
    }
    puts("");
}

void ler(const char *prompt, char *text, int tamanho)
{
    while (1)
    {
        printf("%s", prompt);
        if (fgets(text, tamanho, stdin) == NULL) // le e verifica se houve erro como: ctrl + c
        {
            printf("Erro de leitura\n");
            break;
        }

        size_t len = strlen(text);
        if (len > 0 && text[len - 1] == '\n') // se tem algo digitado e o ultimo caracter for enter
        {
            text[len - 1] = '\0'; // substitui por fim da string
            break;
        }
        else // limpa o stdin
        {
            int ch;
            int i = 1;
            while ((ch = getchar()) != '\n' && ch != EOF)
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
        printf("%s", prompt);
        if (fgets(buffer, tamanho, stdin) == NULL)
        {
            printf("Erro na leitura, tente novamente\n");
            continue;
        }
        if (sscanf(buffer, "%d", &valor) == 1) // converte a string em numero
            return valor;
        puts("Digite um número válido!");
    }
}

void menu(int jogadores, mundo *jogo, int player); // para trabalhar melhor a funcao

int lancar_dado(int lados)
{
    return (rand() % lados) + 1;
}

int verificar(mundo *jogo, int jogadores, int player)
{
    char cor_do_jogador[10];
    strcpy(cor_do_jogador, jogo[player].cor);

    for (size_t i = 0; i < jogadores; i++)
        if (strcmp(jogo[i].cor, cor_do_jogador) != 0) // se houver uma cor diferente
            return 0;
    return 1;
}

int main()
{
    // possibilita a aleatoriedade
    srand(time(NULL));

    // escolhe a quantidade de jogadores
    int jogadores = Ler_int("Quantos jogadores irao jogar? ", sizeof(buffer));
    int player = Ler_int("E Qual jogador voce sera? ", sizeof(buffer)) - 1;

    mundo *jogo;
    jogo = (mundo *)calloc(jogadores, sizeof(mundo));

    if (jogo == NULL)
    {
        printf("Erro ao alocar jogadores\n");
        exit(1);
    }

    // onde o jogo acontece
    while (1)
        menu(jogadores, jogo, player);

    free(jogo);
    return 0;
}

// funcao Menu ====================
void menu(int jogadores, mundo *jogo, int player)
{
    static int qntd_jogadores; // para impedir outras acoes sem ter adicionado todos os jogadores

    puts("\n===================");
    puts("1 - Adicionar exercito");
    puts("2 - Visualizar exercito");
    puts("3 - Atacar");
    puts("4 - sair");
    puts("===================\n");

    // escolha do menu
    int escolha = Ler_int("Sua escolha: ", sizeof(buffer));

    if (escolha == 1 && qntd_jogadores != jogadores) // adicionando exercito
    {
        for (size_t i = 0; i < jogadores; i++)
        {
            jogo[i].jogador = i;
            detalhe(20, &jogo[i].jogador);

            ler("Nome do exercito: ", jogo[i].nome, (int)sizeof(jogo[i].nome));
            jogo[i].Qnt_tropas = Ler_int("Tropas: ", sizeof(buffer));
            ler("Cor do exercito: ", jogo[i].cor, (int)sizeof(jogo[i].cor));

            qntd_jogadores += 1;
            puts("Exercito adicionado!");
        }
    }
    else if (escolha == 2 && qntd_jogadores == jogadores) // visualizando exercitos
    {
        for (size_t i = 0; i < jogadores; i++)
        {
            detalhe(20, &jogo[i].jogador);
            printf("Nome: %s\n", jogo[i].nome);
            printf("Quantidade de tropas: %d\n", jogo[i].Qnt_tropas);
            printf("Cor: %s\n", jogo[i].cor);
        }
    }
    else if (escolha == 3 && qntd_jogadores == jogadores) // ataque
    {
        int ataque, defesa;

        for (int i = 0; i < jogadores; i++) // todos os jogadores jogam no round
        {
            detalhe(20, &jogo[i].jogador);

        novamente:
            if (jogo[i].jogador == player) // Turno do jogador ========
            {
                puts("Quem voce quer atacar?");
                for (int j = 0; j < jogadores; j++)
                {
                    if (j == player || !(strcmp(jogo[j].cor, jogo[player].cor))) // nao mostra o nome do jogador e nem a sua propria cor
                        continue;
                    printf("\t%d - %s\n", j + 1, jogo[j].nome);
                }

                ataque = Ler_int("Numero do inimigo: ", sizeof(buffer)) - 1;
                int igual = strcmp(jogo[ataque].cor, jogo[i].cor);

                if (ataque == player || ataque < 0 || ataque >= jogadores || !igual) // impede o jogador de se atacar ou atacar a mesma cor ou escolher um valor invalido
                {
                    puts("Escolha invalida!");
                    goto novamente;
                }

                Sleep(1000);
                int dado_jogador = lancar_dado(6);
                Sleep(1000);
                int dado_inimigo = lancar_dado(6);

                printf("Voce rola o dado e tira %d\n", dado_jogador);
                printf("O inimigo rola o dado e tira %d\n", dado_inimigo);

                if (dado_jogador > dado_inimigo)
                {
                    puts("Seu ataque funcionou!");
                    jogo[i].Qnt_tropas++;
                    jogo[ataque].Qnt_tropas--;
                }
                else if (dado_jogador < dado_inimigo)
                {
                    puts("Seu ataque falhou!");
                    jogo[i].Qnt_tropas--;
                }
                else
                {
                    puts("Empate!");
                    jogo[i].Qnt_tropas--;
                    jogo[ataque].Qnt_tropas--;
                }

                if (jogo[player].Qnt_tropas < 1)
                {
                    puts("Voce perdeu o jogo! Tente novamente!");
                    free(jogo);
                    exit(0);
                }
                else if (jogo[ataque].Qnt_tropas < 1)
                {
                    printf("%s caiu! Agora pertence a %s.\n", jogo[ataque].nome, jogo[i].nome);
                    strcpy(jogo[ataque].cor, jogo[i].cor);
                    jogo[ataque].Qnt_tropas += 1;
                    if (verificar(jogo, jogadores, player))
                    {
                        puts("\nObrigado por jogar!");
                        puts("==========Voce venceu o jogo!==========");
                        free(jogo);
                        exit(0);
                    }
                }
            }
            else // Turno da maquina ========
            {
                Sleep(1000);
                int alvo = lancar_dado(jogadores) - 1;
                int igual = strcmp(jogo[alvo].cor, jogo[i].cor); // retorna zero se igual

                if (alvo == i || !igual) // zero é falso
                {
                    puts("Pensando...");
                    goto novamente; // nao se ataca
                }
                int dado_atk = lancar_dado(6);
                int dado_def = lancar_dado(6);

                alvo == player ? printf("O jogador %d escolheu atacar voce!\n", i + 1) : printf("O jogador %d ataca o jogador %d!\n", i + 1, alvo + 1);
                printf("Ataque: %d  |  Defesa: %d\n", dado_atk, dado_def);

                if (dado_atk > dado_def)
                {
                    puts("Ataque bem sucedido!");
                    jogo[i].Qnt_tropas++;
                    jogo[alvo].Qnt_tropas--;
                }
                else if (dado_atk < dado_def)
                {
                    puts("O ataque falhou!");
                    jogo[i].Qnt_tropas--;
                }
                else
                {
                    puts("Empate!");
                    jogo[i].Qnt_tropas--;
                    jogo[alvo].Qnt_tropas--;
                }

                if (jogo[player].Qnt_tropas < 1)
                {
                    puts("Voce perdeu o jogo!");
                    free(jogo);
                    exit(0);
                }
                else if (jogo[i].Qnt_tropas < 1)
                {
                    printf("%s caiu! Agora pertence a %s.\n", jogo[i].nome, jogo[alvo].nome);
                    strcpy(jogo[i].cor, jogo[alvo].cor);
                    jogo[i].Qnt_tropas += 1;

                    if (verificar(jogo, jogadores, player))
                    {
                        puts("\nObrigado por jogar!");
                        puts("==========Voce venceu o jogo!==========");
                        free(jogo);
                        exit(0);
                    }

                    if (jogo[alvo].Qnt_tropas < 1) // se ocorrer um empate
                    {
                        printf("%s caiu! Agora pertence a %s.\n", jogo[alvo].nome, jogo[i].nome);
                        strcpy(jogo[alvo].cor, jogo[i].cor);
                        jogo[alvo].Qnt_tropas += 1;

                        if (verificar(jogo, jogadores, player))
                        {
                            puts("\nObrigado por jogar!");
                            puts("==========Voce venceu o jogo!==========");
                            free(jogo);
                            exit(0);
                        }
                    }
                }
                else if (jogo[alvo].Qnt_tropas < 1)
                {
                    printf("%s caiu! Agora pertence a %s.\n", jogo[alvo].nome, jogo[i].nome);
                    strcpy(jogo[alvo].cor, jogo[i].cor);
                    jogo[alvo].Qnt_tropas += 1;

                    if (verificar(jogo, jogadores, player))
                    {
                        puts("\nObrigado por jogar!");
                        puts("==========Voce venceu o jogo!==========");
                        free(jogo);
                        exit(0);
                    }
                }
            }
        }
    }
    else if (escolha < 1 || escolha > 3) // sair
    {
        free(jogo);
        exit(0);
    }
}
