#ifndef MEMORIA_H
#define MEMORIA_H

#include "utils_numeros.h"

#define TAM_PALAVRA 32
#define TAM_ENDERECO 10

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

typedef enum{
	ESCRITA,
	LEITURA
}Operacao;

//Cria uma nova memória Cache.
Cache nova_Cache(int qtd_total_palavras, int tamanho_bloco);

//Printa na tela o [bloco] da [cache].
void cache_printa_bloco(Cache cache, int bloco);

//Verifica [endereço] na [cache]. Retorna HIT ou MISS.
int cache_buscaB(Cache cache, int *endereco);
int cache_buscaD(Cache cache, int endereco);

//Retorna os dados da [cache] correspondentes a [endereco].
int cache_lerB(Cache cache, int *endereco);
int cache_lerD(Cache cache, int endereco);

//Insere o bloco de [endereco] da [memoria_principal] na [cache].
void cache_insereB(Cache cache, int *memoria_principal, int *endereco);
void cache_insereD(Cache cache, int *memoria_principal, int endereco);


//Faz a leitura na memória cache.
int *cache_leituraB(Cache cache, int *memoria_principal, int *endereco);
int *cache_leituraD(Cache cache, int *memoria_principal, int endereco);

//Escreve os dados na cache.
void cache_escreveB(Cache cache, int *memoria_principal, int *endereco);

#endif //MEMORIA_H
