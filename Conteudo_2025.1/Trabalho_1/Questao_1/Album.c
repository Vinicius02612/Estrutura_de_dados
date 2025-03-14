#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "prototipos.h"

/* Cada álbum deve ter,o título, o ano de lançamento, a quantidade de músicas e as Músicas (endereço da árvore binária para
Músicas). Para cada música deve se ter o título, e a quantidade de minutos. */


Dado_Album ler_dado_album() {
    Dado_Album dado;
    printf("Digite o título do álbum: ");
    scanf("%s", dado.titulo);
    printf("Digite o ano de lançamento: ");
    scanf("%d", &dado.ano_lancamento);
    dado.qtd_musicas = 0;
    dado.musica = NULL; // ponteio para a árvore de músicas
    return dado;
}



Arvore_Album *cria_arvore_album() {
    Arvore_Album *raiz;
    raiz = (Arvore_Album*)malloc(sizeof(Arvore_Album));
    if(raiz != NULL) {
        raiz = NULL;
    }
    return raiz;
}

Arvore_Album *aloca_arvore_album(Dado_Album dado) {
    Arvore_Album *novo;
    novo = (Arvore_Album*)malloc(sizeof(Arvore_Album));
    if(novo != NULL) {
        novo->dado = dado;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

int insere_album(Arvore_Album **raiz, Dado_Album dado) {
    int inseriu;
    if(*raiz == NULL) {
        *raiz = aloca_arvore_album(dado);
        inseriu = 1;
    } else {
        if(strcmp(dado.titulo, (*raiz)->dado.titulo) < 0) {
            inseriu = insere_album(&(*raiz)->esq, dado);
        } else  if(strcmp(dado.titulo, (*raiz)->dado.titulo) > 0){
            inseriu = insere_album(&(*raiz)->dir, dado);
        }else if(strcmp(dado.titulo, (*raiz)->dado.titulo) == 0){
            inseriu = 0;
        }
    }
    return inseriu;
}


int buscar_album(Arvore_Album *raiz_album, char titulo[50], Arvore_Album *encontrado){
    int encontrou;
    if(raiz_album == NULL) {
        encontrou = 0;
    } else {
        if(strcmp(titulo, raiz_album->dado.titulo) == 0) {
            encontrado = raiz_album;
            encontrou = 1;
        } else {
            if(strcmp(titulo, raiz_album->dado.titulo) < 0) {
                encontrou = buscar_album(raiz_album->esq, titulo, encontrado);
            } else if(strcmp(titulo, raiz_album->dado.titulo) > 0) {
                encontrou = buscar_album(raiz_album->dir, titulo, encontrado);
            }else{
                encontrou = 0;
            }
        }
    }
    return encontrou;
} 


void imprime_arvore_album(Arvore_Album *raiz){
    if(raiz != NULL) {
        imprime_arvore_album(raiz->esq);
        printf("Título: %s\n", raiz->dado.titulo);
        printf("Ano de lançamento: %d\n", raiz->dado.ano_lancamento);
        printf("Quantidade de músicas: %d\n", raiz->dado.qtd_musicas);
        imprime_arvore_album(raiz->dir);
    }
}

void liberar_arvore_album(Arvore_Album *raiz){
    if(raiz != NULL) {
        liberar_arvore_album(raiz->esq);
        liberar_arvore_album(raiz->dir);
        free(raiz);
    }
}