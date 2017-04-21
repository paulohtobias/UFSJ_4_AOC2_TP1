#include "memoria.h"

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
int ***vetor3d(int d1, int d2, int d3){
	int i;
	int ***v3 = malloc(d1 * sizeof(int**));
	for(i=0; i<d1; i++){
		v3[i] = vetor2d(d2, d3);
	}
	return v3;
}

Cache nova_Chace(int qtd_total_palavras, int qtd_palavras_por_bloco){
	Cache memoria = malloc(sizeof(struct s_Cache));
	
	memoria->qtd_blocos = qtd_total_palavras / qtd_palavras_por_bloco;
	memoria->qtd_palavras_por_bloco = qtd_palavras_por_bloco;
	
	//Calculando quantos bits serão necessários para endereçar a palavra.
	int qpb = qtd_palavras_por_bloco;
	for(memoria->bits_palavras = 0; qpb > 1; qpb>>=1, memoria->bits_palavras++){}
	memoria->endereco_palavra = vetor2d(memoria->qtd_palavras_por_bloco, memoria->bits_palavras);
	
	//Calculando quantos bits serão necessários para endereçar os blocos.
	int qb = memoria->qtd_blocos;
	for(memoria->bits_blocos = 0; qb > 1; qb>>=1, memoria->bits_blocos++){}
	memoria->endereco_bloco = vetor2d(memoria->qtd_blocos, memoria->bits_blocos);
	
	//Calculando quantos bits serão necessários para endereçar as tags.
	memoria->bits_tags = TAM_PALAVRA - memoria->bits_palavras - memoria->bits_blocos;
	memoria->tag = vetor2d(memoria->qtd_blocos, memoria->bits_tags);
	
	//Inicializando os bits de validade como 0.
	memoria->bit_validade = vetor1d(memoria->qtd_blocos);
	
	memoria->memoria = vetor3d(memoria->qtd_blocos, memoria->qtd_palavras_por_bloco, TAM_PALAVRA);
	
	return memoria;
}

int bits(qpb){
	printf("===== %d =====\n", qpb);
	int i;
	for(i=0; qpb > 1; i++){
		printf("%d: %d >> ", i, qpb);
		//qpb = qpb >> 1;
		qpb>>=1;
		printf("%d\n", qpb);
	}
	printf("BITS: %d\n\n", i);
	
	return 0;
}

int main(){
	int i;
	for(i=1; i<=1024; i*=2){
		bits(i);
	}
}