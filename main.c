#include "memoria.h"

int main(int argc, char *argv[]){
	int i;

	int mp[TAM_MP];
	for(i=0; i<TAM_MP; i++){
		mp[i] = i;
	}

	int palavras, tam_bloco;
	Cache cache = NULL;
	for(palavras = 32; palavras <= 256; palavras<<=1){
		for(tam_bloco = 1; tam_bloco <= 8; tam_bloco<<=1){
			FILE *in = fopen("trace.txt", "r");

			int blocos = palavras / tam_bloco;
			
			cache = nova_Cache(palavras, tam_bloco);

			int endereco;
			char modo[8], bin[11];
			int leituraHit=0, leituraMiss=0;
			int escritaHit=0, escritaMiss=0;
			while(!feof(in)){
				fscanf(in, "%s %s %d\n", modo, bin, &endereco);
				if(!cache_busca(cache, endereco)){
					cache_insere(mp, cache, endereco);
					if(modo[0] == 'e')
						escritaMiss++;
					else
						leituraMiss++;
				}else{
					if(modo[0] == 'e')
						escritaHit++;
					else
						leituraHit++;
				}
			}

			//cache_printa(cache);
			char log_name[50];

			sprintf(log_name, "log/log [%d x %d].txt", blocos, tam_bloco);
			FILE *out = fopen(log_name, "w");

			fprintf(out, "Cache: %d palavras divididas em %d blocos com %d palavras cada.\n\n", palavras, blocos, tam_bloco);
			fprintf(out, "Hit: %d | Miss: %d\n", cache->hit, cache->miss);
			fprintf(out, "Leituras (H|M|T): (%d|%d|%d)\n"
						"Escritas (H|M|T): (%d|%d|%d)\n"
						"Total: %d\n",
						leituraHit, leituraMiss, leituraHit + leituraMiss,
						escritaHit, escritaMiss, escritaHit + escritaMiss,
						leituraHit + leituraMiss + escritaHit + escritaMiss);
			
			free_Cache(cache);
			fclose(out);
			fclose(in);
			cache = NULL;
		}
	}

	return 0;
}
