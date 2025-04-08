#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "prototipos.h"


Arvore_Playlist *cria_arvore_playlist(){
    Arvore_Playlist *raiz;
    raiz = (Arvore_Playlist*)malloc(sizeof(Arvore_Playlist));
    if(raiz != NULL) {
        raiz = NULL;
    }
    return raiz;
}

Arvore_Playlist *aloca_no_playlist(Dado_Playlist dado){
    Arvore_Playlist *novo;
    novo = (Arvore_Playlist*)malloc(sizeof(Arvore_Playlist));
    if(novo != NULL) {
        novo->dado = dado;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

int insere_playlist(Arvore_Playlist **raiz, Dado_Playlist dado){
    int inseriu;
    if(*raiz == NULL) {
        *raiz = aloca_no_playlist(dado);
        inseriu = 1;
    } else {
        if(strcmp(dado.nome, (*raiz)->dado.nome) < 0) {
            inseriu = insere_playlist(&(*raiz)->esq, dado);
        } else if(strcmp(dado.nome, (*raiz)->dado.nome) > 0) {
            inseriu = insere_playlist(&(*raiz)->dir, dado);
        }else if(strcmp(dado.nome, (*raiz)->dado.nome) == 0){
            inseriu = 0;
        }
    }
    return inseriu;
}