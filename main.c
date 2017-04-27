#include "memoria.h"

int expo2(int e){
	return 1<<e;
}

int main(){
	int i;

	int pal = 32, bl = 4;
	Cache cache = nova_Cache(pal, bl);

	int mp[1024];
	for(i=0; i<1024; i++){
		mp[i] = i;
	}

	cache_insereD(cache, mp, 37);

	for(i=0; i<cache->qtd_blocos; i++){
		cache_printa_bloco(cache, i);
	}

	for(i=0; i<45; i++)
		printf("BUSCA(%d): %d\n", i, cache_buscaD(cache, i));

	return 0;
}
