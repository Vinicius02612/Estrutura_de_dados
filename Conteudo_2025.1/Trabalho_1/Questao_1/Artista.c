#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "prototipos.h"


Dado_Artista ler_dado_artista() {
    Dado_Artista dado;
    printf("Digite o nome do artista: ");
    scanf("%s", dado.nome);
    printf("Digite o tipo do artista: ");
    scanf("%s", dado.tipo);
    printf("Digite o estilo musical: ");
    scanf("%s", dado.estilo);
    dado.num_albuns = 0;
    dado.album = NULL;
    return dado;
}

Arvore_Artista *cria_arvore_artista() {
    Arvore_Artista *raiz;
    raiz = (Arvore_Artista*)malloc(sizeof(Arvore_Artista));
    if(raiz != NULL) {
        raiz = NULL;
    }
    return raiz;
}

Arvore_Artista *aloca_no_artista(Dado_Artista dado) {
    Arvore_Artista *novo;
    novo = (Arvore_Artista*)malloc(sizeof(Arvore_Artista));
    if(novo != NULL) {
        novo->dado = dado;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

int insere_artista(Arvore_Artista **raiz, Dado_Artista dado) {
    int inseriu = 0;
    if(*raiz == NULL) {
        *raiz = aloca_no_artista(dado);
        inseriu = 1;
    } else {
        if(strcmp(dado.nome, (*raiz)->dado.nome) < 0) {
            inseriu = insere_artista(&(*raiz)->esq, dado);
        } else if(strcmp(dado.nome, (*raiz)->dado.nome) > 0) {
            inseriu = insere_artista(&(*raiz)->dir, dado);
        }else if(strcmp(dado.nome, (*raiz)->dado.nome) == 0){
            inseriu = 0;
        }
    }
    return inseriu;
}

int buscar_artista(Arvore_Artista *raiz, char nome[50]){

    int encontrou;
    if(raiz == NULL) {
        encontrou = 0;
    } else {
        if(strcmp(nome, raiz->dado.nome) == 0) {
            encontrou = 1;
        } else {
            if(strcmp(nome, raiz->dado.nome) < 0) {
                encontrou = buscar_artista(raiz->esq, nome);
            } else if(strcmp(nome, raiz->dado.nome) > 0) {
                encontrou = buscar_artista(raiz->dir, nome);
            }else{
                encontrou = 0;
            }
        }
    }
    return encontrou;
}

Arvore_Artista *buscar_artista_tow(Arvore_Artista *raiz, char nome[50]){
    Arvore_Artista *artista;
    if(raiz == NULL) {
        artista = NULL;
    } else {
        if(strcmp(nome, raiz->dado.nome) == 0) {
            artista = raiz;
        } else {
            if(strcmp(nome, raiz->dado.nome) < 0) {
                artista = buscar_artista_tow(raiz->esq, nome);
            } else if(strcmp(nome, raiz->dado.nome) > 0) {
                artista = buscar_artista_tow(raiz->dir, nome);
            }else{
                artista = NULL;
            }
        }
    }
    return artista;
}

int insere_album_artista(Arvore_Artista **raiz_artista, Dado_Album dado_album, char nome_artista[50]){
    int inseriu;
    Arvore_Artista *busca_artista;
    busca_artista = NULL;
    if(*raiz_artista != NULL){
        busca_artista = buscar_artista_tow(*raiz_artista, nome_artista);
        if(busca_artista != NULL){
            inseriu = insere_album(&busca_artista->dado.album, dado_album);
            if(inseriu){
                busca_artista->dado.num_albuns += 1;
            }
        }

    }
    return inseriu;
}

void imprime_arvore_artista(Arvore_Artista *raiz){
    if(raiz != NULL) {
        imprime_arvore_artista(raiz->esq);
        printf("Nome: %s\n", raiz->dado.nome);
        printf("Tipo: %s\n", raiz->dado.tipo);
        printf("Estilo: %s\n", raiz->dado.estilo);
        printf("Número de álbuns: %d\n", raiz->dado.num_albuns);
        if(raiz->dado.album != NULL){
            imprime_arvore_album(raiz->dado.album);
        }else{
            printf("Nenhum album cadastrado\n");
        }
        imprime_arvore_artista(raiz->dir);
    }
}
void libera_arvore_artista(Arvore_Artista *raiz){
    if(raiz != NULL) {
        libera_arvore_artista(raiz->esq);
        libera_arvore_artista(raiz->dir);
        free(raiz);
    }
}