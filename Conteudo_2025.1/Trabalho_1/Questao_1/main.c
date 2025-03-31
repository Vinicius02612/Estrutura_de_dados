#include "stdio.h"
#include "stdlib.h"
#include "prototipos.h"


int main(){
    int opcao, status, status_busca,ano;
    char nomeArtista[50], tituloAlbum[50],tipoArtista[50],estilo[50];

    Dado_Artista dado_artista;
    Dado_Album dado_album;
    Dado_Musica dado_musica;


    Arvore_Artista *arvore_artista;
    arvore_artista = cria_arvore_artista();

    Arvore_Artista *artista;

    Arvore_Album *album,*album_encontrado;
    album_encontrado = NULL;
    


    
    do{
        printf("\n\nEscolha uma opcao\n"
            "1 - Cadastrar Artista \n"
            "2 - Cadastrar Album\n"
            "3 - Cadastrar Musica\n"
            "4 - Mostrar todos os artistas cadastrados.\n"
            "5 - Mostrar todos os artistas cadastrados de um determinado tipo.\n"
            "6 - Mostrar todos os artistas cadastrados de um determinado estilo musical.\n"
            "7 - Mostrar todos os artistas cadastrados de um determinado estilo musical e tipo de artista.\n"
            "8 - Mostrar todos os album de uma artista.\n"
            "9 - Mostrar todos os albuns de um determinado ano de um artista.\n"
            "10 - Mostrar todas as músicas de um determinado álbum de um determinado artista.\n"
            "0 - Sair\n"
        );

        scanf("%d", &opcao);
        switch(opcao){
            case 1: // cadastrar Artisa
               dado_artista = ler_dado_artista();
               status = insere_artista(&arvore_artista, dado_artista);
               if(status != 0){
                    printf("Artista cadastrado com sucesso\n");
               }else{
                    printf("Não foi possivel cadastrar o artista\n");
               }
                break;
            case 2: // cadastrar Album
                printf("ESCOLHA UM ARTISTA ABAIXO PARA CADASTRAR O ALBUM\n");
                imprime_arvore_artista(arvore_artista);
                printf("Digite o nome do artista: ");
                scanf("%s", nomeArtista);
                dado_album = ler_dado_album();
                status = insere_album_artista(&arvore_artista, dado_album, nomeArtista);
                if(status != 0){
                    printf("Album cadastrado com sucesso\n");
                }

                break;
            case 3: // cadastrar Musica
                printf("ESCOLHA UM ALBUM ABAIXO PARA CADASTRAR A MUSICA\n");
                imprime_arvore_album(arvore_artista->dado.album);
                printf("Digite o titulo do album: ");
                scanf("%s", tituloAlbum);
                status_busca = buscar_album(arvore_artista->dado.album, tituloAlbum, &album_encontrado);

                if(status_busca != 0){
                    dado_musica = ler_dado_musica();
                    status =  insere_musica_album(&album_encontrado, dado_musica);
                    if(status != 0){
                        printf("Musica cadastrada com sucesso\n");
                    }
                }else{
                    printf("Album não encontrado\n");
                }
                break;
            case 4: // Mostrar todos os artistas cadastrados
                imprime_arvore_artista(arvore_artista);
                break;
            case 5:
                // Mostar todos os artistas cadastrados de um determinado tipo
                printf("DIGITE O TIPO DO ARTISTA");
                scanf("%s", tipoArtista);
                mostrar_artista_por_tipo(arvore_artista, tipoArtista);
                break;
            case 6:
                /* Mostrar todos os artistas cadastrados de um determinado estilo musical. */
                printf("DIGITE O ESTILO MUSICAL: \n");
                scanf("%s", estilo);
                mostrar_all_artistas_com_estilo_musical(arvore_artista,estilo);
                break;
            case 7:
                /* Mostrar todos os artistas cadastrados de um determinado estilo musical e tipo de artista. */
                printf("DIGITE O ESTILO MUSICAL: \n");
                scanf("%s", estilo);
                printf("DIGITE O TIPO DO ARTISTA: \n");
                scanf("%s", tipoArtista);
                break;
            case 8:
                /* Mostrar todos as musicas de album de uma artista... */
                printf("DIGITE O NOME DO ARTISTA: \n");
                scanf("%s", nomeArtista);
                printf("DIGITE O NOME DO ALBUM: \n");
                scanf("%s", tituloAlbum);
                mostrar_all_musicas_album_artista(arvore_artista, nomeArtista, tituloAlbum);
                break;
            case 9:
                /* Mostrar todos os albuns de um determinado ano de um artista */
                printf("DIGITE O NOME DO ARTISTA: \n");
                scanf("%s", nomeArtista);
                printf("DIGITE O ANO DO ALBUM: \n");
                scanf("%d", &ano);
                mostrar_all_albuns_artista_ano(arvore_artista, nomeArtista, ano);
                break;
            case 10:
                /* x) Mostrar todas as músicas de um determinado álbum de um determinado artista. */
                printf("DIGITE O NOME DO ARTISTA: \n");
                scanf("%s", nomeArtista);
                printf("DIGITE O NOME DO ALBUM: \n");
                scanf("%s", tituloAlbum);
                mostrar_all_musicas_album_artista(arvore_artista, nomeArtista, tituloAlbum);
                
                break;
                
               
            default:
                printf("Opcao invalida\n");
        }
    }while(opcao != 0);
    imprime_arvore_artista(arvore_artista);
    libera_arvore_artista(arvore_artista);

    


    return 0;
}