#include "memoria.h"

Cache nova_Cache(int qtd_total_palavras, int tamanho_bloco){
	Cache cache = malloc(sizeof(struct s_Cache));

	//Calculando quantos blocos serão necessários.
	cache->qtd_blocos = qtd_total_palavras / tamanho_bloco;
	cache->tamanho_bloco = tamanho_bloco;

	//Calculando o intervalo de quantos bits necessários para endereçar a palavra.
	cache->bits_palavras = novo_Intervalo(TAM_ENDERECO - num_bits(cache->tamanho_bloco), TAM_ENDERECO - 1);

	//Calculando o intervalo de bits necessários para endereçar os blocos.
	cache->bits_blocos = novo_Intervalo(cache->bits_palavras.inicio - num_bits(cache->qtd_blocos), cache->bits_palavras.inicio - 1);

	//Calculando quantos bits serão necessários para endereçar as tags.
	cache->bits_tags = novo_Intervalo(0, cache->bits_blocos.inicio - 1);
	cache->tag = vetor1d(cache->qtd_blocos);

	//Inicializando os bits de validade como 0.
	cache->bit_validade = vetor1d(cache->qtd_blocos);

	cache->data = vetor2d(cache->qtd_blocos, cache->tamanho_bloco);

	return cache;
}

int cache_buscaB(Cache cache, int *endereco){
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
int cache_buscaD(Cache cache, int endereco){
	cache_buscaB(cache, itob(endereco, TAM_ENDERECO));
}

int cache_lerB(Cache cache, int *endereco){
	//Fazendo o mapeamento do endereço fornecido.
	int endereco_bloco = btoi(endereco, cache->bits_blocos);
	int endereco_palavra = btoi(endereco, cache->bits_palavras);

	return cache->data[endereco_bloco][endereco_palavra];
}
int cache_lerD(Cache cache, int endereco){
	cache_lerB(cache, itob(endereco, TAM_ENDERECO));
}

void cache_insereB(Cache cache, int *memoria_principal, int *endereco){
	int i;

	//Busca em [endereco] o numero do bloco e tag.
	int endereco_bloco = btoi(endereco, cache->bits_blocos);
	int tag = btoi(endereco, cache->bits_tags);

	//Calcula a base do endereço do bloco na memória principal.
	int endereco_bloco_incial = btoi(endereco, novo_Intervalo(0, cache->bits_blocos.fim)) << cache->bits_palavras.qtd;

	printf("Endereco Bloco: %d\n", endereco_bloco);
	printf("Tag: %d\n", tag);
	printf("Base: %d\n", endereco_bloco_incial);getchar();

	cache->tag[endereco_bloco] = tag; //Seta a nova tag.
	cache->bit_validade[endereco_bloco] = 1; //Seta o bit de validade.

	for(i=0; i<(1<<cache->bits_palavras.qtd); i++){ //Copia os dados do bloco da [memoria_principal] para a [cache].
		cache->data[endereco_bloco][i] = memoria_principal[endereco_bloco_incial + i];
	}
}

void cache_insereD(Cache cache, int *memoria_principal, int endereco){
	cache_insereB(cache, memoria_principal, itob(endereco, TAM_ENDERECO));
}

void cache_printa_bloco(Cache cache, int bloco){
	int i;

	printf("Bloco %d (", bloco);
	mostra( itob(bloco, cache->bits_blocos.qtd), novo_Intervalo(0, cache->bits_blocos.qtd-1) );
	printf(") | ");

	printf("Tag: %d (", cache->tag[bloco]);
	mostra( itob(cache->tag[bloco], cache->bits_tags.qtd), novo_Intervalo(0, cache->bits_tags.qtd-1) );
	printf(") | ");

	printf("Validade: '%c'\n", cache->bit_validade[bloco]?'Y':'N');

	for(i=0; i<cache->tamanho_bloco; i++){
		printf("\t");
		int *ib = itob(i, cache->bits_palavras.qtd);
		mostra( ib, novo_Intervalo(0, cache->bits_palavras.qtd-1) );
		printf("|%d: <%d>\n", i, cache->data[bloco][i]);
	}
	printf("\n");
}
