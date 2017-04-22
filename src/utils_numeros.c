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

int btoi(int *bin, Intervalo tamanho){
	int i, num = 0;

	for(i=tamanho.fim; i>=tamanho.inicio; i--){
		num+=(bin[i]<<(tamanho.fim-i));
	}
	return num;
}

int *itob(int num){
	int *bin = vetor1d(TAM_PALAVRA);
	int i;

	for(i=TAM_PALAVRA-1; i>=0; i--){
		bin[i] = (num>>(TAM_PALAVRA-i-1) & 1);
	}
	return bin;
}

int num_bits(int num){
	int qtd, temp = num;

	for(qtd=0; temp>1; qtd++){
		temp>>=1;
	}

	return qtd;
}

void mostra(int *bin, Intervalo t){
	int i;
	for(i=t.inicio; i<=t.fim; i++){
		printf("%d", bin[i]);
	}
}
