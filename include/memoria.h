#ifndef MEMORIA_H
#define MEMORIA_H

#include "utils_numeros.h"

#define TAM_PALAVRA 32
#define TAM_ENDERECO 10
#define TAM_MP 1024

typedef struct{
    int tag;
    int bloco;
    int palavra;
}Endereco;

Endereco calcula_endereco(int enderecoD, int palavras, int blocos, int tam_bloco);

struct s_Cache{
    int hit;
    int miss;
    
    int palavras;
    int blocos;
    int tam_bloco;

    int *tag;
    int *validade;

    int **dados;
};

typedef struct s_Cache *Cache;

Cache nova_Cache(int palavras, int tam_bloco);

void free_Cache(Cache cache);

int cache_busca(Cache cache, int endereco);

void cache_insere(int *memoria_principal, Cache cache, int endereco);

#endif //MEMORIA_H