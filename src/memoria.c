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

Cache nova_Cache(int qtd_total_palavras, int qtd_palavras_por_bloco){
	Cache cache = malloc(sizeof(struct s_Cache));

	cache->qtd_blocos = qtd_total_palavras / qtd_palavras_por_bloco;
	cache->qtd_palavras_por_bloco = qtd_palavras_por_bloco;

	//Calculando quantos bits serão necessários para endereçar a palavra.
	int qpb = qtd_palavras_por_bloco;
	for(cache->bits_palavras = 0; qpb > 1; qpb>>=1, cache->bits_palavras++){}
	cache->endereco_palavra = vetor2d(cache->qtd_palavras_por_bloco, cache->bits_palavras);

	//Calculando quantos bits serão necessários para endereçar os blocos.
	int qb = cache->qtd_blocos;
	for(cache->bits_blocos = 0; qb > 1; qb>>=1, cache->bits_blocos++){}
	cache->endereco_bloco = vetor2d(cache->qtd_blocos, cache->bits_blocos);

	//Calculando quantos bits serão necessários para endereçar as tags.
	cache->bits_tags = TAM_PALAVRA - cache->bits_palavras - cache->bits_blocos;
	cache->tag = vetor2d(cache->qtd_blocos, cache->bits_tags);

	//Inicializando os bits de validade como 0.
	cache->bit_validade = vetor1d(cache->qtd_blocos);

	cache->memoria = vetor3d(cache->qtd_blocos, cache->qtd_palavras_por_bloco, TAM_PALAVRA);

	return cache;
}

int cache_busca(Cache cache, int *endereco){
	int i;
	int blocoI, blocoF;

	blocoF = TAM_PALAVRA - cache->bits_palavras;
	blocoI = blocoF - cache->bits_blocos;

	for(i=blocoI; i<blocoF; i++){}

	return 1;
}
