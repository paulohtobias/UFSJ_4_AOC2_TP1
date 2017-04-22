#include "memoria.h"

Cache nova_Cache(int qtd_total_palavras, int tamanho_bloco){
	Cache cache = malloc(sizeof(struct s_Cache));

	//Calculando quantos blocos serão necessários.
	cache->qtd_blocos = qtd_total_palavras / tamanho_bloco;
	cache->tamanho_bloco = tamanho_bloco;

	//Calculando o intervalo de quantos bits necessários para endereçar a palavra.
	cache->bits_palavras = novo_Intervalo(TAM_ENDERECO - num_bits(cache->tamanho_bloco), TAM_ENDERECO - 1);

	//Calculando o intervalo de bits necessários para endereçar os blocos.
	cache->bits_blocos = novo_Intervalo(cache->bits_palavras.inicio - num_bits(cache->qtd_blocos), cache->bits_palavras.fim - num_bits(cache->qtd_blocos));

	//Calculando quantos bits serão necessários para endereçar as tags.
	cache->bits_tags = novo_Intervalo(0, cache->bits_blocos.inicio - 1);
	cache->tag = vetor1d(cache->qtd_blocos);

	//Inicializando os bits de validade como 0.
	cache->bit_validade = vetor1d(cache->qtd_blocos);

	cache->data = vetor2d(cache->qtd_blocos, cache->tamanho_bloco);

	return cache;
}

int cache_busca(Cache cache, int *endereco){
	//Fazendo o mapeamento do endereço fornecido.
	int endereco_bloco = btoi(endereco, cache->bits_blocos);
	int tag = btoi(endereco, cache->bits_tags);

	//Checa o bit de validade.
	if(cache->bit_validade[endereco_bloco] == 0){
		return MISS;
	}

	//Checa a tag.
	if(cache->tag[endereco_bloco] != tag){
		return MISS;
	}

	//Se tudo estiver ok, então a palavra poderá ser recuperada.
	return HIT;
}

int cache_ler(Cache cache, int *endereco){
	//Fazendo o mapeamento do endereço fornecido.
	int endereco_bloco = btoi(endereco, cache->bits_blocos);
	int endereco_palavra = btoi(endereco, cache->bits_palavras);

	return cache->data[endereco_bloco][endereco_palavra];
}
