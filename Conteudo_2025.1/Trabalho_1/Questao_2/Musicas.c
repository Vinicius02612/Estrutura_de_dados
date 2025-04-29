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

void rotacionaEsq_musica(Arvore_Musica **raiz) {
    Arvore_Musica *temp = (*raiz)->dir;
    (*raiz)->dir = temp->esq;
    temp->esq = *raiz;
    *raiz = temp;
}

void rotacionaDir_musica(Arvore_Musica **raiz) {
    Arvore_Musica *temp = (*raiz)->esq;
    (*raiz)->esq = temp->dir;
    temp->dir = *raiz;
    *raiz = temp;
}

int maior_altura_musica(int a, int b) {
    return (a > b) ? a : b;
}

int pegaAltura_musica(Arvore_Musica *raiz) {
    int altura;
    if(raiz == NULL) {
        altura = -1;
    } else {
        altura = raiz->altura;
    }
    return altura;
}

void atualiza_altura_musica(Arvore_Musica *raiz) {
    if(raiz != NULL) {
        raiz->altura = maior_altura_musica(pegaAltura_musica(raiz->esq), pegaAltura_musica(raiz->dir)) + 1;
    }
}


void balanceamento_musica(Arvore_Musica **raiz) {
    int fator_balanceamento = pegaAltura_musica((*raiz)->esq) - pegaAltura_musica((*raiz)->dir);
    if(fator_balanceamento > 1) {
        if(pegaAltura_musica((*raiz)->esq->esq) >= pegaAltura_musica((*raiz)->esq->dir)) {
            rotacionaDir_musica(raiz);
        } else {
            rotacionaEsq_musica(&(*raiz)->esq);
            rotacionaDir_musica(raiz);
        }
    } else if(fator_balanceamento < -1) {
        if(pegaAltura_musica((*raiz)->dir->dir) >= pegaAltura_musica((*raiz)->dir->esq)) {
            rotacionaEsq_musica(raiz);
        } else {
            rotacionaDir_musica(&(*raiz)->dir);
            rotacionaEsq_musica(raiz);
        }
    }
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
    if(inseriu == 1) {
        balanceamento_musica(raiz);
        atualiza_altura_musica(*raiz);
    }
    return inseriu;
}

// insere musica na arvore de albuns
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

//teste buscar menor usando recursão
Arvore_Musica *buscar_menor_musica_direita(Arvore_Musica *raiz){
    Arvore_Musica *menor_direita;
    menor_direita = NULL;
    if(raiz != NULL){
        if(raiz->esq == NULL){
            menor_direita = raiz;
        }else{
            menor_direita = buscar_menor_musica_direita(raiz->esq);
        }
    }
    return menor_direita;
}

//buscar menor usando iteração
Arvore_Musica *buscar_menor_musica_direita_itera(Arvore_Musica *raiz){
    Arvore_Musica *menor_direita;
    menor_direita = NULL;
    if(raiz != NULL){
        menor_direita = raiz;
        while(menor_direita->esq != NULL){
            menor_direita = menor_direita->esq;
        }
    }
    return menor_direita;
}

int ehFolha_Musica(Arvore_Musica *raiz){
    int eh_folha;
    if(raiz->esq == NULL && raiz->dir == NULL){
        eh_folha = 1;
    }else{
        eh_folha = 0;
    }
    return eh_folha;
}

Arvore_Musica *pega_um_filho_Musica(Arvore_Musica *raiz){
    Arvore_Musica *auxiliar_filho;
    auxiliar_filho = NULL;

    if(raiz->esq != NULL){
        auxiliar_filho = raiz->esq;
    }else if(raiz->dir != NULL){
        auxiliar_filho = raiz->dir;
    }
    return auxiliar_filho;
}

int remover_musica(Arvore_Musica **raiz, char nome[50]){
    int removeu;
    Arvore_Musica *musica_auxiliar, *filho_escolhido;
    filho_escolhido = NULL;
    musica_auxiliar = NULL;
    if(*raiz != NULL) {
        if(strcmp(nome, (*raiz)->dado.titulo) == 0) {
            if(ehFolha_Musica(*raiz)){
                musica_auxiliar = *raiz;
                *raiz = NULL;
                free(musica_auxiliar);
            }else if((*raiz)->esq != NULL || (*raiz)->dir != NULL){
                filho_escolhido = pega_um_filho_Musica(*raiz);
                musica_auxiliar = *raiz;
                *raiz = filho_escolhido;
                free(musica_auxiliar);
            }else{
                Arvore_Musica *menor_direita;
                menor_direita = buscar_menor_musica_direita((*raiz)->dir);
                (*raiz)->dado = menor_direita->dado;
                removeu = remover_musica(&(*raiz)->dir, menor_direita->dado.titulo);
            }
            removeu = 1;
        } else {
            if (strcmp(nome, (*raiz)->dado.titulo) < 0){
                removeu = remover_musica(&(*raiz)->esq, nome);
            }else if (strcmp(nome, (*raiz)->dado.titulo) > 0){
                removeu = remover_musica(&(*raiz)->dir, nome);
            }else{
                removeu = 0;
            }
        }

        if(removeu == 1) {
            balanceamento_musica(raiz);
            atualiza_altura_musica(*raiz);
        }
    }
    return removeu;
}


Arvore_Musica *buscar_musica(Arvore_Musica *raiz, char nomeMusica[50]){
    Arvore_Musica *muscia;

    if(raiz != NULL){
        if(raiz->dado.titulo == nomeMusica){
            muscia = raiz;
        }else if( strcmp(nomeMusica, raiz->dado.titulo)< 0){
            muscia = buscar_musica(raiz->esq, nomeMusica);
        }else{
            muscia = buscar_musica(raiz->dir, nomeMusica);
        }

    }
    return muscia;
}

void mostra_dado_musica(Dado_Musica dado){
    printf("---------------------------\n");
    printf("Título: %s\n", dado.titulo);
    printf("Duração: %d\n", dado.duracao);
    printf("---------------------------\n");
}

void imprime_arvore_musica(Arvore_Musica *raiz){
    if(raiz != NULL) {
        imprime_arvore_musica(raiz->esq);
        mostra_dado_musica(raiz->dado);
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