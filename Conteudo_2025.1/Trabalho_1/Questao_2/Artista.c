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

void rotacionaEsq_artista(Arvore_Artista **raiz) {
    Arvore_Artista *temp = (*raiz)->dir;
    (*raiz)->dir = temp->esq;
    temp->esq = *raiz;
    *raiz = temp;
}

void rotacionaDir_artista(Arvore_Artista **raiz) {
    Arvore_Artista *temp = (*raiz)->esq;
    (*raiz)->esq = temp->dir;
    temp->dir = *raiz;
    *raiz = temp;
}


int maior_altura_artista(int a, int b) {
    return (a > b) ? a : b;
}

int pegaAltura_artista(Arvore_Artista *raiz) {
    int altura;
    if(raiz != NULL){
        altura =  raiz->altura;
    }else{
        altura = -1;
    }
    return altura;
}

void atualiza_altura_artista(Arvore_Artista *raiz){
    if(raiz != NULL){
        raiz->altura = maior_altura_artista(pegaAltura_artista(raiz->esq), pegaAltura_artista(raiz->dir)) + 1;
    }
}

void balanceamento_artista(Arvore_Artista **raiz){
    int fator_balanceamento = pegaAltura_artista((*raiz)->esq) - pegaAltura_artista((*raiz)->dir);
    if(fator_balanceamento > 1) {
        if(pegaAltura_artista((*raiz)->esq->esq) >= pegaAltura_artista((*raiz)->esq->dir)) {
            rotacionaDir_artista(raiz);
        } else {
            rotacionaEsq_artista(&(*raiz)->esq);
            rotacionaDir_artista(raiz);
        }
    } else if(fator_balanceamento < -1) {
        if(pegaAltura_artista((*raiz)->dir->dir) >= pegaAltura_artista((*raiz)->dir->esq)) {
            rotacionaEsq_artista(raiz);
        } else {
            rotacionaDir_artista(&(*raiz)->dir);
            rotacionaEsq_artista(raiz);
        }
    }
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
    if(inseriu == 1) {
        balanceamento_artista(raiz);
        atualiza_altura_artista(*raiz);
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

Arvore_Artista *ehSoUmFilho(Arvore_Artista *raiz){
    Arvore_Artista *temp;
    temp = NULL;
    if(raiz->esq == NULL){
        temp = raiz->dir;
    }else{
        temp = raiz->esq;
    }
    return temp;

}

int remover_artista(Arvore_Artista **raiz, char nome[50]) {
    int removeu;
    Arvore_Artista *artista;
    artista = NULL;
    if(*raiz != NULL) {
        
    }
    return removeu;
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


/* ix) Mostrar todos os álbuns de um determinado ano de um artista. */
void mostrar_all_albuns_artista_ano(Arvore_Artista *raiz_artista, char nome[50], int ano){
    Arvore_Artista *artista_arv =  NULL;
    if(raiz_artista != NULL){
        artista_arv = buscar_artista_tow(raiz_artista, nome);
        if(artista_arv != NULL){
            if(artista_arv->dado.album != NULL){
                if(artista_arv->dado.album->dado.ano_lancamento == ano){
                    mostra_dado_album(artista_arv->dado.album->dado);
                }else{
                    printf("Nenhum album cadastrado com esse ano\n");
                }
            }else{
                printf("Nenhum album cadastrado\n");
            }
        }
        
        mostrar_all_albuns_artista_ano(raiz_artista->esq,nome,ano);
        mostrar_all_albuns_artista_ano(raiz_artista->dir,nome,ano);
    }else{
        printf("Nenhum artista cadastrado com esse nome\n");
    }
}

/* x) Mostrar todas as músicas de um determinado álbum de um determinado artista. */
void mostrar_all_musicas_album_artista(Arvore_Artista *raiz_artista, char nomeArtista[50], char nomeAlbum[50]){
    Arvore_Artista *artista;
    Arvore_Album *album;
    int album_encontrado;
    album_encontrado = 0;

    if(raiz_artista != NULL){
        artista = buscar_artista_tow(raiz_artista, nomeArtista);
        if(artista != NULL){
            imprime_arvore_album(artista->dado.album);
        }else{
            printf("Nenhum artista cadastrado com esse nome\n");
        }
    }
}


/* xi) Mostrar todos os álbuns de um determinado ano de todos os artistas cadastrados. */
void mostrar_all_albuns_artista_ano_todos(Arvore_Artista *raiz_artista, int ano){
    if(raiz_artista != NULL){
        if(raiz_artista->dado.album != NULL){
            if(raiz_artista->dado.album->dado.ano_lancamento == ano){
                mostra_dado_album(raiz_artista->dado.album->dado);
            }
        }
        mostrar_all_albuns_artista_ano_todos(raiz_artista->esq,ano);
        mostrar_all_albuns_artista_ano_todos(raiz_artista->dir,ano);
    }
}


/* xii) Mostrar os dados de uma determinada Música (usuário entrar com o título da música): nome artista,
título do álbum, ano de lançamento */
void mostrar_dados_musica(Arvore_Artista *raiz_artista, char nomeMusica[50]){
    Arvore_Musica *musica;
    if(raiz_artista != NULL){
        musica = buscar_musica(raiz_artista->dado.album->dado.musica, nomeMusica);
        if(musica != NULL){
            printf("Artista: %s\n", raiz_artista->dado.nome);
            mostra_dado_musica(musica->dado);
        }else{
            printf("Nenhuma musica cadastrada com esse nome\n");
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