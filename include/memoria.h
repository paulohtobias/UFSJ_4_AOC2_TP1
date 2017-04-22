#ifndef MEMORIA_H
#define MEMORIA_H

#include "utils_numeros.h"

struct s_Cache{
	//Palavras
	int tamanho_bloco;
	Intervalo bits_palavras; //Intervalo de bits que serão necessários para endereçar as palavras

	//Blocos
	int qtd_blocos;
	Intervalo bits_blocos; //Intervalo de bits que serão necessários para endereçar os blocos

	//Tags
	int *tag;
	Intervalo bits_tags;

	//Bit Validade
	int *bit_validade;

	//Matriz de dados
	int **data;
};
typedef struct s_Cache* Cache;

typedef enum{
	MISS,
	HIT
}Busca_Resultado;

Cache nova_Cache(int qtd_total_palavras, int tamanho_bloco);

int cache_busca(Cache cache, int *endereco);

#endif //MEMORIA_H
