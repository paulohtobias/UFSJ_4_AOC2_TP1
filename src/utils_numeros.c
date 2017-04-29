#include "utils_numeros.h"

int *vetor1d(int d1){
	int *v1 = calloc(d1, sizeof(int));
	return v1;
}
int **vetor2d(int d1, int d2){
	int i;
	int **v2 = malloc(d1 * sizeof(int*));
	for(i=0; i<d1; i++){
		v2[i] = vetor1d(d2);
	}
	return v2;
}

Intervalo novo_Intervalo(int inicio, int fim){
	Intervalo tamanho;

	tamanho.inicio = inicio;
	tamanho.fim = fim;
	tamanho.qtd = fim - inicio + 1;

	return tamanho;
}

int calcula_bits(int num){
	int i;
	int n = num;
	for(i=0; n>1; i++){
		n>>=1;
	}
	return i;
}