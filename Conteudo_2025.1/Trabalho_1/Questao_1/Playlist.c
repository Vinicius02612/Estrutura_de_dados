#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "prototipos.h"

Arvore_Playlist *cria_arvore_playlist()
{
    Arvore_Playlist *raiz;
    raiz = (Arvore_Playlist *)malloc(sizeof(Arvore_Playlist));
    if (raiz != NULL)
    {
        raiz = NULL;
    }
    return raiz;
}

Dado_Playlist ler_dado_playlist()
{
    Dado_Playlist dado_playlist;
    printf("DIGITE O NOME DA PLAYLIST: \n");
    scanf("%s", dado_playlist.nomePlaylist);
    dado_playlist.musica = cria_arvore_musica();
    return dado_playlist;
}

Arvore_Playlist *aloca_no_playlist(Dado_Playlist dado)
{
    Arvore_Playlist *novo;
    novo = (Arvore_Playlist *)malloc(sizeof(Arvore_Playlist));
    if (novo != NULL)
    {
        novo->dado = dado;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

int insere_playlist(Arvore_Playlist **raiz, Dado_Playlist dado)
{
    int inseriu;
    if (*raiz == NULL)
    {
        *raiz = aloca_no_playlist(dado);
        inseriu = 1;
    }
    else
    {
        if (strcmp(dado.nomePlaylist, (*raiz)->dado.nomePlaylist) < 0)
        {
            inseriu = insere_playlist(&(*raiz)->esq, dado);
        }
        else if (strcmp(dado.nomePlaylist, (*raiz)->dado.nomePlaylist) > 0)
        {
            inseriu = insere_playlist(&(*raiz)->dir, dado);
        }
        else if (strcmp(dado.nomePlaylist, (*raiz)->dado.nomePlaylist) == 0)
        {
            inseriu = 0;
        }
    }
    return inseriu;
}

int ehFolha(Arvore_Playlist *raiz)
{
    int eh_folha;
    if (raiz->esq == NULL && raiz->dir == NULL)
    {
        eh_folha = 1;
    }
    else
    {
        eh_folha = 0;
    }
    return eh_folha;
}


Arvore_Playlist *pega_um_filho(Arvore_Playlist *raiz)
{
    Arvore_Playlist *auxiliar_filho;
    auxiliar_filho = NULL;

    if (raiz->esq != NULL){
        auxiliar_filho = raiz->esq;
    }else if(raiz->dir != NULL){
        auxiliar_filho = raiz->dir;
    }
    return auxiliar_filho;
}

Arvore_Playlist *buscar_menor_direita(Arvore_Playlist *raiz)
{

    Arvore_Playlist *no_atual = raiz;
    if (raiz != NULL)
    {
        while (no_atual->esq != NULL)
        {
            no_atual = no_atual->esq;
        }
    }

    return no_atual;
}

int remover_dado_playList(Arvore_Playlist **raiz, char nome[50])
{
    int removeu;
    Arvore_Playlist *filho_escolhido;
    filho_escolhido = NULL;
    if (*raiz != NULL)
    {
        if (strcmp(nome, (*raiz)->dado.nomePlaylist) == 0) {// encontrou o nó a ser removido
            if (ehFolha(*raiz)){ // caso do nó ser folha
                Arvore_Playlist *auxiliar_playlist;
                auxiliar_playlist = *raiz;
                *raiz = NULL;
                free(auxiliar_playlist);
            }else if ((*raiz)->esq != NULL || (*raiz)->dir != NULL){ // tem dois filhos, pega um filho da esquerda ou da direita e substitui o nó da raiz  
                Arvore_Playlist *auxiliar_playlist;
                filho_escolhido = pega_um_filho(*raiz);
                auxiliar_playlist = *raiz;
                *raiz = filho_escolhido;
                free(auxiliar_playlist);
            }else{ // buscar na subárvore da direita o menor elemento mais a esquerda da raiz
                Arvore_Playlist *menor;
                menor = buscar_menor_direita((*raiz)->dir);
                (*raiz)->dado = menor->dado;
                removeu = remover_dado_playList(&(*raiz)->esq, menor->dado.nomePlaylist);
            }
            removeu = 1;
        }
        else{
            if (strcmp(nome, (*raiz)->dado.nomePlaylist) < 0){
                removeu = remover_dado_playList(&(*raiz)->esq, nome);
            }else if (strcmp(nome, (*raiz)->dado.nomePlaylist) > 0){
                removeu = remover_dado_playList(&(*raiz)->dir, nome);
            }else{
                removeu = 0;
            }
        }
    }
    return removeu;
}

void mostrar_playlist_nome(Arvore_Playlist *raiz, char nome[50])
{
    if (raiz != NULL)
    {
        if (strcmp(nome, raiz->dado.nomePlaylist) == 0)
        {
            printf("Nome da Playlist: %s\n", raiz->dado.nomePlaylist);
        }
        else
        {
            mostrar_playlist_nome(raiz->esq, nome);
            mostrar_playlist_nome(raiz->dir, nome);
        }
    }
}

void imprime_arvore_playlist(Arvore_Playlist *raiz)
{
    if (raiz != NULL)
    {
        imprime_arvore_playlist(raiz->esq);
        printf("Nome da Playlist: %s\n", raiz->dado.nomePlaylist);
        imprime_arvore_playlist(raiz->dir);
    }
}

void libera_arvore_playlist(Arvore_Playlist *raiz)
{
    if (raiz != NULL)
    {
        libera_arvore_playlist(raiz->esq);
        libera_arvore_playlist(raiz->dir);
        free(raiz);
    }
}

void MenuPlayList(Arvore_Playlist **raiz_playList, Arvore_Artista *raiz_artista)
{   
    int opc, status_inseriu, status_remover;
    Dado_Playlist dado_playlist;

    do{
        printf("\n--- MENU DE PLAYLIST ---\n"
            "1 - Criar playlist\n"
            "2 - Mostrar dados de uma playlist\n"
            "3 - Remover música de uma playlist\n"
            "4 - Remover playlist\n"
            "5 - Imprimir playlists\n"
            "6 - Inserir música em uma playlist\n"
            "0 - Voltar\n"
            "Escolha uma opção: \n"
        );
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            dado_playlist = ler_dado_playlist();
            status_inseriu = insere_playlist(raiz_playList,dado_playlist);
            if (status_inseriu != 0){
                printf("Playlist criada com sucesso\n");
            }else{
                printf("Não foi possível cadastrar a playlist\n");
            }
            break;
        case 2:
            printf("DIGITE O NOME DA PLAYLIST: \n");
            char nomePlaylist[50];
            scanf("%s", nomePlaylist);
            mostrar_playlist_nome(*raiz_playList, nomePlaylist);
            break;
        case 3:
            printf("DIGITE O NOME DA PLAYLIST: \n");
            char nomePlaylistRemover[50];
            scanf("%s", nomePlaylistRemover);
            status_remover = remover_musica(&(*raiz_playList)->dado.musica, nomePlaylistRemover);
            if (status_remover != 0){
                printf("Playlist removida com sucesso\n");
            }else{
                printf("Não foi possível remover a playlist\n");
            }
            break;
        default:
            break;
        }

    }while (opc != 0);
   
   
}