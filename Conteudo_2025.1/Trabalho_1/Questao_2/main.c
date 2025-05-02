#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include <time.h> 
#include <windows.h>



#include "../Questao_3/prototipos.h" 

void teste_insere_artista(Arvore_Artista **arvore_artista) {
    Dado_Artista artista;
    clock_t t_inicio, t_fim;
    double tempo_gasto;

    int status;

    t_inicio = clock(); // Início da medição
    for (int i = 0; i < 3000; i++) { // Insere 3000 elementos
        sprintf(artista.nome, "Artista %d_%d",  i);
        sprintf(artista.tipo, "Tipo %d", i);
        sprintf(artista.estilo, "Estilo %d", i);
        artista.album = cria_arvore_album();
        status = insere_artista(arvore_artista, artista);
    }
    t_fim = clock(); // Fim da medição
    //calcular media
    tempo_gasto += ((double)(t_fim - t_inicio)) / CLOCKS_PER_SEC; // Acumula o tempo gasto
    

    tempo_gasto /= 30; // Calcula a média
    printf("Tempo total para inserir 3000 artistas 10 vezes: %.6f segundos\n", tempo_gasto);
}

void teste_insere_album(Arvore_Album **raiz_album){
    int status;
    Dado_Album dado_album;

    for(int i = 0; i < 30; i++){
        sprintf(dado_album.titulo, "Album %d", i);
        dado_album.ano_lancamento = 2000 + i;
        dado_album.qtd_musicas = 0;
        dado_album.musica = cria_arvore_musica();
        status = insere_album(raiz_album, dado_album);
        
    }
   
}



void teste_insere_musica(Arvore_Album **raiz_album){
    Dado_Musica dado_musica;
    int status;
    for(int i = 0; i < 30; i++){
        sprintf(dado_musica.titulo, "Musica %d", i);
        dado_musica.duracao = 3 + i;
        status = insere_musica_album(raiz_album, dado_musica);
    }
}


/* void teste_busca_all_artista(Arvore_Artista *arvore_artista, char *nomeArtista, char *tituloAlbum){

    int resultado_busca_album;
    Arvore_Artista *artista;
    Arvore_Album *album;


    artista = buscar_artista_tow(arvore_artista, nomeArtista);
    if(artista != NULL){
        album = buscar_album_tow(artista->dado.album, tituloAlbum);
        if(album != NULL){
            imprime_arvore_musica(album->dado.musica);
        }
    }
}
 */

int main(){
    Arvore_Artista *arvore_artista;


    int status_artista, status_album, status_musica;
   
    // medir o tempo de inserção em segundo

    arvore_artista = cria_arvore_artista();
   
   teste_insere_artista(&arvore_artista);

    if(arvore_artista != NULL){
        teste_insere_album(&arvore_artista->dado.album);
        teste_insere_musica(&arvore_artista->dado.album);  
    }
    // buscar mostrar todas as musicas de um artista de um album
   


    return 0;
}