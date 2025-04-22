// PROTOTIPO DAS FUNÇÕES UTILIZADAS NO PROGRAMA PRINCIPAL

/*  Músicas  (endereço  da  árvore  binária  para 
Músicas). Para cada música deve se ter o título, e a quantidade de minutos */
typedef struct dado_musica {
    char titulo[50];
    int duracao;
} Dado_Musica;

typedef struct Arvore_Musica {
    Dado_Musica dado;
    struct Arvore_Musica *esq;
    struct Arvore_Musica *dir;
} Arvore_Musica;

/* 
Álbuns (endereço da árvore binária para Álbuns). Cada álbum deve ter,  
o  título,  o  ano  de  lançamento,  a  quantidade  de  músicas  e  as  Músicas
*/

typedef struct dado_album {
    char titulo[50];
    int ano_lancamento;
    int qtd_musicas;
    struct Arvore_Musica *musica;
} Dado_Album;


typedef struct Arvore_Album {
    Dado_Album dado;
    struct Arvore_Album *esq;
    struct Arvore_Album *dir;
    
} Arvore_Album;
/* 
E para cada artista deve se ter o nome do artista, tipo (cantor(a), Dupla, Banda, Grupo, ...), o estilo 
musical, o número de álbuns

 */
typedef struct dado_artista {
    char nome[50];
    char tipo[50];
    char estilo[50];
    int num_albuns ;
    struct Arvore_Album *album;
} Dado_Artista;



typedef struct Arvore_Artista {
    Dado_Artista dado;
    struct Arvore_Artista *esq;
    struct Arvore_Artista *dir;
} Arvore_Artista;



typedef struct dado_playlist{
    char nomePlaylist[50];
    struct Arvore_Musica *musica;
} Dado_Playlist;

typedef struct Arvore_Playslist{
    Dado_Playlist dado;
    struct Arvore_Playslist *esq;
    struct Arvore_Playslist *dir;
}Arvore_Playlist;


// Funções para manipulação da árvore de músicas
Dado_Musica ler_dado_musica();
Arvore_Musica *cria_arvore_musica();
int insere_musica(Arvore_Musica **raiz, Dado_Musica dado);
void imprime_arvore_musica(Arvore_Musica *raiz);
void libera_arvore_musica(Arvore_Musica *raiz);
int insere_musica_album(Arvore_Album **raiz_album, Dado_Musica dado_musica);
Arvore_Musica *buscar_musica(Arvore_Musica *raiz, char nomeMusica[50]);
void mostra_dado_musica(Dado_Musica dado);
Arvore_Musica *buscar_menor_musica_direita(Arvore_Musica *raiz);
Arvore_Musica *buscar_menor_musica_direita_itera(Arvore_Musica *raiz);
int remover_musica(Arvore_Musica **raiz, char nome[50]);
// Funções para manipulação da árvore de álbuns
Dado_Album ler_dado_album();
Arvore_Album *cria_arvore_album();
int insere_album(Arvore_Album **raiz, Dado_Album dado);
void imprime_arvore_album(Arvore_Album *raiz);
void libera_arvore_album(Arvore_Album *raiz);
int buscar_album(Arvore_Album *raiz_album, char titulo[50], Arvore_Album **encontrado);
void mostra_dado_album(Dado_Album dado);
void mostrar_dados_musica(Arvore_Artista *raiz_artista, char nomeMusica[50]);
// criar função para inserir um album a um artista
Dado_Artista ler_dado_artista();
Arvore_Artista *cria_arvore_artista();
int buscar_artista(Arvore_Artista *raiz, char nome[50]);
int insere_album_artista(Arvore_Artista **raiz,  Dado_Album dado_album, char nomeArtista[50]);
int remover_artista(Arvore_Artista **raiz, char nome[50]);
int insere_artista(Arvore_Artista **raiz, Dado_Artista dado);
void imprime_arvore_artista(Arvore_Artista *raiz);
void libera_arvore_artista(Arvore_Artista *raiz);
Arvore_Artista *buscar_artista_tow(Arvore_Artista *raiz, char nome[50]);
void mostrar_artista_por_tipo(Arvore_Artista *raiz_artista, char tipo[50]);
void imprime_dado_artista(Dado_Artista dado);
void mostrar_all_artistas_com_estilo_musical(Arvore_Artista *raiz_artista, char estilo[50]);
void mostrar_all_albuns_de_um_artista(Arvore_Artista *raiz_artista, char nome[50]);
void mostrar_all_musicas_album_artista(Arvore_Artista *raiz_artista, char nomeArtista[50], char nomeAlbum[50]);
void mostrar_all_albuns_artista_ano(Arvore_Artista *raiz_artista, char nome[50], int ano);
void mostrar_all_musicas_album_artista(Arvore_Artista *raiz_artista, char nomeArtista[50], char nomeAlbum[50]);
void mostrar_all_musicas_album_artista(Arvore_Artista *raiz_artista, char nomeArtista[50], char nomeAlbum[50]);

// Funções referentes a playlist
Dado_Playlist ler_dado_playlist();
Arvore_Playlist *cria_arvore_playlist();
Arvore_Playlist *aloca_no_playlist(Dado_Playlist dado);
Arvore_Playlist *buscar_menor_direita(Arvore_Playlist *raiz);
Arvore_Playlist *pega_um_filho(Arvore_Playlist *raiz);
Arvore_Playlist *buscar_playlist(Arvore_Playlist *raiz, char nomePlaylist[50]);
int ehFolha(Arvore_Playlist *raiz);
int remover_dado_playList(Arvore_Playlist **raiz, char nome[50]);
int insere_playlist(Arvore_Playlist **raiz, Dado_Playlist dado);
void mostrar_playlist_nome(Arvore_Playlist *raiz, char nome[50]);
void imprime_arvore_playlist(Arvore_Playlist *raiz);
void imprime_arvore_playlist(Arvore_Playlist *raiz);
void libera_arvore_playlist(Arvore_Playlist *raiz);
void MenuPlayList(Arvore_Playlist **raiz_playList, Arvore_Artista *raiz_artista);
