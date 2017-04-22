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

//Converte binário para inteiro.
int btoi(int bin[], Intervalo tamanho);

//Converte inteiro para binário.
int *itob(int num, int tam);

//Retorna quantos bits são precisos para representar os números de 0 a [num - 1]
int num_bits(int num);

//Mostra um numero binário na tela.
void mostra(int *bin, Intervalo t);

#endif //UTILS_NUMEROS_H
