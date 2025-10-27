#include "base.h"

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
    };

    // onde o jogo acontece
    menu(jogadores, jogo, player);

    free(jogo);
    return 0;
}