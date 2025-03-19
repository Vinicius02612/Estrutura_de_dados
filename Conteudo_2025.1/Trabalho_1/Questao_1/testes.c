#include "stdio.h"
#include "stdlib.h"
#include "prototipos.h"

int  test_insercao_Artista(Arvore_Artista **arvore_artista){

    Dado_Artista dado_artista;
    int status;
    for(int i = 0; i < 10; i++){
        sprintf(dado_artista.nome, "Artista %d", i);
        sprintf(dado_artista.tipo, "Tipo %d", i);
        sprintf(dado_artista.estilo, "Estilo %d", i);
        status = insere_artista(arvore_artista, dado_artista);
    }
    return status;
    
}


int teste_insercao_album( Arvore_Artista *arvore_artista){
    Dado_Album dado_album;
    int status;
    for(int i = 0; i < 10; i++){
        sprintf(dado_album.titulo, "Album %d", i);
        dado_album.ano_lancamento, 2000 + i;
        status = insere_album(&arvore_artista->dado.album, dado_album);
    }

    return status;
}

int teste_buscar_artista_tipo(Arvore_Artista *raiz_artista, char tipo[50]){
    int status, encontrou;
    status = buscar_artista(raiz_artista, tipo);
    if(status != 0){
        encontrou = 1;
    }else{
        encontrou = 0;
    }
    return status;
}

int main(){
    Arvore_Artista *arvore_artista;
    Arvore_Album *arvore_album;
    Arvore_Musica *arvore_musica;

    int status_artista, status_album, status_musica;
    char nomeArtista[50], tituloAlbum[50],tipoArtista[50],estilo[50];



    arvore_artista = cria_arvore_artista();
    status_artista = test_insercao_Artista(&arvore_artista);
    if(status_artista != 0){
        printf("Teste de inserção Artista PASSED\n");
    }else{
        printf("Teste de inserção Artista FAILED\n");
    }

    imprime_arvore_artista(arvore_artista);


    //teste buscar artista por tipo
    status_artista = teste_buscar_artista_tipo(arvore_artista, estilo);
    if(status_artista != 0){
        printf("Teste de buscar artista por tipo PASSED\n");
    }else{
        printf("Teste de buscar artista por tipo FAILED\n");
    }

    
    


    return 0;
}