#include "memoria.h"

int hits = 0;
int misses = 0;

#include "memoria.h"

Endereco calcula_endereco(int enderecoD, int palavras, int blocos, int tam_bloco){
    Endereco endereco;

    endereco.palavra = enderecoD % tam_bloco;
    endereco.bloco = (enderecoD / tam_bloco) % blocos;
    endereco.tag = enderecoD / palavras;

    return endereco;
}

Cache nova_Cache(int palavras, int tam_bloco){
    Cache cache = malloc(sizeof(struct s_Cache));

    cache->hit = 0;
    cache->miss = 0;

    cache->palavras = palavras;
    cache->blocos = palavras / tam_bloco;
    cache->tam_bloco = tam_bloco;

    cache->tag = vetor1d(cache->blocos);
    cache->validade = vetor1d(cache->blocos);

    cache->dados = vetor2d(cache->blocos, cache->tam_bloco);

    return cache;
}

void free_Cache(Cache cache){
    free(cache->tag);
    free(cache->validade);

    int i;
    for(i=0; i<cache->blocos; i++){
        free(cache->dados[i]);
        cache->dados[i] = NULL;
    }
    free(cache->dados);

    free(cache);
}

void cache_printa(Cache cache){
    int i, j;

    for(i=0; i<cache->blocos; i++){
        printf("Bloco %d:\n", i);
        for(j=0; j<cache->tam_bloco; j++){
            printf("\t<%3d>: %d\n", j, cache->dados[i][j]);
        }
        printf("\n");
    }
}

int cache_busca(Cache cache, int endereco){
    Endereco e = calcula_endereco(endereco, cache->palavras, cache->blocos, cache->tam_bloco);
    if(cache->tag[e.bloco] == e.tag && cache->validade[e.bloco] == 1){
        cache->hit++;
        return 1;
    }else{
        cache->miss++;
        return 0;
    }
}

void cache_insere(int *memoria_principal, Cache cache, int endereco){
    Endereco e = calcula_endereco(endereco, cache->palavras, cache->blocos, cache->tam_bloco);

    cache->tag[e.bloco] = e.tag;
    cache->validade[e.bloco] = 1;

    int base = endereco - e.palavra;
    int i;
    for(i=0; i<cache->tam_bloco; i++){
        cache->dados[e.bloco][i] = memoria_principal[base + i];
    }
}