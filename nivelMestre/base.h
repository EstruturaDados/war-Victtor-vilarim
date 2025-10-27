#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

extern char buffer[64];

typedef struct
{
    char nome[30];
    char cor[10];
    int Qnt_tropas;
    int jogador;

} mundo;

void detalhe(int vezes, int *n);

void ler(const char *prompt, char *text, int tamanho);

int Ler_int(const char *prompt, int tamanho);

void adicionar(mundo *jogo, int jogadores, int *qntd_jogadores, int escolha);

void visualizar(mundo *jogo, int jogadores, int qntd_jogadores, int escolha);

void atacar(mundo *jogo, int jogadores, int qntd_jogadores, int escolha, int player, int *missao, int *target, int media);

void missoes(int missao, int alvo, int media, mundo *jogo, int jogadores, size_t i, int dado_ataque, int dado_defesa);

void visualizar_missao(int *missao, int *alvo, int media, size_t i, mundo *jogo, int jogadores, int qntd_jogadores);

void menu(int jogadores, mundo *jogo, int player);

int lancar_dado(int lados);

int verificar(mundo *jogo, int jogadores, int player);

#endif
