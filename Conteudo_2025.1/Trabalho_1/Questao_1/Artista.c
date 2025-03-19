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
    int inseriu;
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

void imprime_dado_artista(Dado_Artista dado){

    printf("---------------------------\n");
    printf("\nNome: %s\n", dado.nome);
    printf("\nTipo: %s\n", dado.tipo);
    printf("\nEstilo: %s\n", dado.estilo);
    printf("\nNúmero de álbuns: %d\n", dado.num_albuns);
    if(dado.album != NULL){
        imprime_arvore_album(dado.album);
    }else{
        printf("Nenhum album cadastrado\n");
    }
    printf("---------------------------\n");

}
void imprime_arvore_artista(Arvore_Artista *raiz){
    if(raiz != NULL) {
        imprime_arvore_artista(raiz->esq);
        imprime_dado_artista(raiz->dado);
        imprime_arvore_artista(raiz->dir);
    }
}
/* Mostrar todos os artistas cadastrados de um determinado tipo. */
void mostrar_artista_por_tipo(Arvore_Artista *raiz_artista, char tipo[50]){
    if(raiz_artista != NULL){
        if(strcmp(tipo, raiz_artista->dado.tipo)==0){
            imprime_dado_artista(raiz_artista->dado);
        }
        mostrar_artista_por_tipo(raiz_artista->esq,tipo);
        mostrar_artista_por_tipo(raiz_artista->dir,tipo);
    }
}

/* Mostrar todos os artistas cadastrados de um determinado estilo musical. */
void mostrar_all_artistas_com_estilo_musical(Arvore_Artista *raiz_artista, char estilo[50]){
     if(raiz_artista != NULL){
        if(strcmp(estilo, raiz_artista->dado.estilo)==0){
            imprime_dado_artista(raiz_artista->dado);
        }
        mostrar_artista_por_tipo(raiz_artista->esq,estilo);
        mostrar_artista_por_tipo(raiz_artista->dir,estilo);
    }
}

/* Mostrar todos os albuns de um determinado Artista */
void mostrar_all_albuns_de_um_artista(Arvore_Artista *raiz_artista, char nome[50]){
  
    if(raiz_artista != NULL){
        if(strcmp(nome, raiz_artista->dado.nome)==0){
            imprime_arvore_album(raiz_artista->dado.album);
        }
        mostrar_all_albuns_de_um_artista(raiz_artista->esq,nome);
        mostrar_all_albuns_de_um_artista(raiz_artista->dir,nome);
    }
}

/* Mostrar todos os albuns de determinado ano de um artista */
void mostrar_all_albuns_artista_ano(Arvore_Artista *raiz_artista, char nome[50], int ano){
    if(raiz_artista != NULL){
        if(strcmp(nome, raiz_artista->dado.nome)==0 && raiz_artista->dado.album->dado.ano_lancamento == ano){
            mostra_dado_album(raiz_artista->dado.album->dado);
        }
        mostrar_all_albuns_artista_ano(raiz_artista->esq,nome,ano);
        mostrar_all_albuns_artista_ano(raiz_artista->dir,nome,ano);
    }else{
        printf("Nenhum artista cadastrado com esse nome\n");
    }
}

/* Mostrar todos as musicas de album de uma artista... */
void mostrar_all_musicas_album_artista(Arvore_Artista *raiz_artista, char nomeArtista[50], char nomeAlbum[50]){
    Arvore_Artista *artista;
    Arvore_Album *album;
    int album_encontrado;
    album_encontrado = 0;

    if(raiz_artista != NULL){
        artista = buscar_artista_tow(raiz_artista, nomeArtista);
        if(artista != NULL){
            if(artista->dado.album != NULL){
                album_encontrado = buscar_album(artista->dado.album, nomeAlbum, &album);
                if(album_encontrado){
                    imprime_arvore_musica(album->dado.musica);
                }else{
                    printf("Nenhum album cadastrado com esse nome\n");
                }
            }else{
                printf("Nenhum album cadastrado\n");
            }
        }else{
            printf("Nenhum artista cadastrado com esse nome\n");
        }

    }
}
void libera_arvore_artista(Arvore_Artista *raiz){
    if(raiz != NULL) {
        libera_arvore_artista(raiz->esq);
        libera_arvore_artista(raiz->dir);
        free(raiz);
    }
}