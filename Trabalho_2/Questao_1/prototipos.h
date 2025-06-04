#include "stdio.h"
#include "stdlib.h"
#include "string.h"


struct dadoCidade {
    char nome[50];
    int populacao;
};

typedef struct Cidade {
    struct dadoCidade dado;
    struct Cidade *esquerda;
    struct Cidade *direita;
    int cor; // 0 para vermelho, 1 para preto
} Cidade;


struct dadoEstado{
    char nome[50];
    char capital[50];
    int qtd_cidades;
    int populacao;
    Cidade *arvore_cidades; // Endereço para árvore vermelha-preta de cidades do estado
};

typedef struct Estado {
    struct  dadoEstado dado;
    struct Estado *proximo;
    struct Estado *anterior;
} Estado;

Estado* criar_estado(struct dadoEstado dado);
struct dadoEstado Ler_dados_Estado();
void inserir_estado(Estado **inicio, Estado *novo);
void exibir_estados(Estado *inicio);
void liberar_estados(Estado *inicio);