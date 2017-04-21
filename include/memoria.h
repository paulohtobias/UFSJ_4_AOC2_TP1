#include <stdio.h>
#include <stdlib.h>

//Funções auxiliares de matriz e vetor.
int *vetor1d(int d1);
int **vetor2d(int d1, int d2);
int ***vetor3d(int d1, int d2, int d3);

#define TAM_PALAVRA 32

struct s_Cache{
	int qtd_palavras_por_bloco;
	int bits_palavras;
	int **endereco_palavra;

	int qtd_blocos;
	int bits_blocos;
	int **endereco_bloco;

	int **tag;
	int bits_tags;
	int a;

	int *bit_validade;

	int ***memoria;
};
typedef struct s_Cache* Cache;

Cache nova_Cache(int qtd_total_palavras, int qtd_palavras_por_bloco);
