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
        if(strcmp(dado.nomePlaylist, (*raiz)->dado.nomePlaylist) < 0) {
            inseriu = insere_playlist(&(*raiz)->esq, dado);
        } else if(strcmp(dado.nomePlaylist, (*raiz)->dado.nomePlaylist) > 0) {
            inseriu = insere_playlist(&(*raiz)->dir, dado);
        }else if(strcmp(dado.nomePlaylist, (*raiz)->dado.nomePlaylist) == 0){
            inseriu = 0;
        }
    }
    return inseriu;
}


int ehFolha(Arvore_Playlist *raiz){
    int eh_folha;
    if(raiz->esq == NULL && raiz->dir == NULL){
        eh_folha = 1;
    }else{
        eh_folha = 0;
    }
    return eh_folha;
}

Arvore_Playlist *pega_um_filho(Arvore_Playlist *raiz){
    Arvore_Playlist *auxiliar_filho;
    auxiliar_filho = NULL;

    if(raiz->esq == NULL){
        auxiliar_filho = raiz->dir;
    }else{
        auxiliar_filho = raiz->esq;
    }
    return auxiliar_filho;
}

Arvore_Playlist *buscar_menor_direita(Arvore_Playlist *raiz){

    Arvore_Playlist *no_atual = raiz;
    if(raiz != NULL){
        while(no_atual->esq != NULL){
            no_atual = no_atual->esq;
        }
    }

    return no_atual;
}

int remover_dado_playList(Arvore_Playlist **raiz, char nome){
    int removeu;
    Arvore_Playlist *auxiliar_playlist, *filho_escolhido;
    auxiliar_playlist = NULL;
    if(*raiz != NULL){
        if(strcmp(nome,(*raiz)->dado.nomePlaylist) == 0){
            if(ehFolha(*raiz)){// caso do nó ser folha
                auxiliar_playlist = *raiz;
                *raiz = NULL;
                free(auxiliar_playlist);
            }else if(filho_escolhido = pega_um_filho(*raiz) != NULL){ //tem dois filhos, pega um filho da esquerda ou da direita
               auxiliar_playlist = *raiz;
               raiz = filho_escolhido;
                free(auxiliar_playlist);
            }else{
                Arvore_Playlist *menor;
                menor = buscar_menor_direita(*raiz);
                *raiz = menor;
                menor = (*raiz)->esq;
                free(auxiliar_playlist);
            }
            removeu = 1;
        }else{
            if(strcmp(nome, (*raiz)->dado.nomePlaylist) < 0){
                removeu = remover_dado_playList(&(*raiz)->esq, nome);
            }else if(strcmp(nome, (*raiz)->dado.nomePlaylist) > 0){
                removeu = remover_dado_playList(&(*raiz)->dir, nome);
            }else{
                removeu = 0;
            }
        }
    }
    return removeu;
}
