#ifndef UTILS_NUMEROS_H
#define UTILS_NUMEROS_H

#include <stdio.h>
#include <stdlib.h>

//Funções auxiliares de matriz e vetor.
int *vetor1d(int d1);
int **vetor2d(int d1, int d2);

typedef struct{
	int inicio; //Inicio do intervalo.
	int qtd; //Quantos elementos há no intervalo.
	int fim; //Fim do intervalo.
}Intervalo;

Intervalo novo_Intervalo(int inicio, int fim);

int calcula_bits(int num);

int sub_num(int num, int inicio);

#endif //UTILS_NUMEROS_H
