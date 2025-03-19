#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"



Dado_Musica ler_dado_musica(){
    Dado_Musica dado;
    
    printf("Digite o nome da música: ");
    scanf("%s", dado.titulo);

    printf("Digite a duracao da musica: ");
    scanf("%d", &dado.duracao);

    return dado;
}


Arvore_Musica *cria_arvore_musica(){
    Arvore_Musica *raiz;
    raiz = (Arvore_Musica*)malloc(sizeof(Arvore_Musica));
    if(raiz != NULL) {
        raiz = NULL;
    }
    return raiz;
}


Arvore_Musica *aloca_no_musica(Dado_Musica dado){
    Arvore_Musica *novo;
    novo = (Arvore_Musica*)malloc(sizeof(Arvore_Musica));
    if(novo != NULL) {
        novo->dado = dado;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}
/* 
Retorno da função strcmp:
-1, se o primeiro parâmetro for menor que o segundo
0, se os parâmetros forem iguais
1, se o primeiro parâmetro for maior que o segundo

 */

int insere_musica(Arvore_Musica **raiz, Dado_Musica dado){
    int inseriu;
    if(*raiz == NULL) {
        *raiz = aloca_no_musica(dado);
        inseriu = 1;
    } else {
        if(strcmp(dado.titulo, (*raiz)->dado.titulo) <  0) {
            inseriu = insere_musica(&(*raiz)->esq, dado);
        } else if(strcmp(dado.titulo, (*raiz)->dado.titulo) > 0) {
            inseriu = insere_musica(&(*raiz)->dir, dado);
        }else if(strcmp(dado.titulo, (*raiz)->dado.titulo) == 0){
            inseriu = 0;
        }
    }
    return inseriu;
}

int insere_musica_album(Arvore_Album **raiz_album, Dado_Musica dado_musica){
    int inseriu;

    if(*raiz_album == NULL){
        inseriu = 0;
    }else{
        inseriu = insere_musica(&(*raiz_album)->dado.musica, dado_musica);
        if(inseriu != 0){
            (*raiz_album)->dado.qtd_musicas++;
        }
    }
    return inseriu;

}

void imprime_arvore_musica(Arvore_Musica *raiz){
    if(raiz != NULL) {
        imprime_arvore_musica(raiz->esq);
        printf("Título: %s\n", raiz->dado.titulo);
        printf("Duração: %d\n", raiz->dado.duracao);
        imprime_arvore_musica(raiz->dir);
    }
}


void libera_arvore_musica(Arvore_Musica *raiz){
    if(raiz != NULL) {
        libera_arvore_musica(raiz->esq);
        libera_arvore_musica(raiz->dir);
        free(raiz);
    }
}