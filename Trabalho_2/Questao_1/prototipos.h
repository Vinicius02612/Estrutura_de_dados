#include "stdio.h"
#include "stdlib.h"
#include "string.h"


struct dadoPessoa
{
    char cpf[15];
    char nome[100];
    int cep_natal;
    int cep_moradia;
    int dia, mes, ano; // Data de nascimento
};


typedef struct Pessoa
{
    struct dadoPessoa dado;
    struct Pessoa *esquerda;
    struct Pessoa *direita;
    int cor; // 0 para vermelho, 1 para preto
} Pessoa;





struct dadoCep{
    int cep;
};

typedef struct Ceps {
    struct dadoCep dado;
    struct Ceps *esquerda;
    struct Ceps *direita;
    int cor; // 0 para vermelho, 1 para preto
} Ceps;

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
int inserir_estado(Estado **inicio, Estado *novo);
void exibir_estados(Estado *inicio);
void liberar_estados(Estado *inicio);
int buscar_estado(Estado *inicio, const char *nome_estado);

struct dadoCidade Ler_dados_Cidade();
Cidade* criar_cidade(struct dadoCidade dado);
int insere_cidades_arovreRB(Cidade **raiz, struct dadoCidade dado);
void exibir_cidades(Cidade *raiz);
void liberar_cidades(Cidade *raiz);
int cor_cidade(Cidade *no);
Cidade *rotacionar_esquerda_cidade(Cidade *no);
Cidade *rotacionar_direita_cidade(Cidade *no);
void troca_cor_cidade(Cidade *no);
Cidade* balancear_cidade(Cidade *raiz);
Cidade* move_red_esq_cidade(Cidade *raiz);
Cidade* move_red_dir_cidade(Cidade *raiz);
Cidade* procuraMenor_cidade(Cidade *raiz);
Cidade* remove_menor_cidade(Cidade *raiz);
Cidade *remover_no_cidade(Cidade **raiz, const char *nome);
Cidade *remove_arvore_cidade(Cidade **raiz, const char *nome);
Cidade *rotacionar_direita_cidade(Cidade *raiz);
Cidade *rotacionar_esquerda_cidade(Cidade *raiz);

struct dadoCep Ler_dados_Cep();
Ceps* criar_cep(int cep);
int insere_cep_arvoreRB(Ceps **raiz, struct dadoCep dado);
void exibir_ceps(Ceps *raiz);
void liberar_ceps(Ceps *raiz);
Ceps *remover_no_cep(Ceps **raiz, int cep);
int remove_arvore_cep(Ceps **raiz, int cep);
Ceps *remove_menor(Ceps *raiz);
int cor(Ceps *no);
Ceps *balancear_cep(Ceps *raiz);
Ceps *move_red_esq(Ceps *raiz);
Ceps *move_red_dir(Ceps *raiz);
Ceps *rotacionar_direita(Ceps *raiz);
Ceps *rotacionar_esquerda(Ceps *raiz);
Ceps *procuraMenor_cep(Ceps *raiz);
void troca_cor(Ceps *no);

struct dadoPessoa Ler_dados_Pessoa();
Pessoa* criar_pessoa(struct dadoPessoa dado);
int insere_pessoa_arvoreRB(Pessoa **raiz, struct dadoPessoa dado);
void exibir_pessoas(Pessoa *raiz);
void liberar_pessoas(Pessoa *raiz);
int remover_no_pessoa(Pessoa **raiz, const char *cpf);
int remover_arvore_pessoa(Pessoa **raiz, const char *cpf);
int cor_arvore_pessoa(Pessoa *no);
Pessoa* rotacionar_esquerda_pessoa(Pessoa *no);
Pessoa* rotacionar_direita_pessoa(Pessoa *no); 
void troca_cor_pessoa(Pessoa *no);
Pessoa* move_red_esq_pessoa(Pessoa *no);
Pessoa* move_red_dir_pessoa(Pessoa *no);
Pessoa* balancear_pessoa(Pessoa *no);
Pessoa* procuraMenor_pessoa(Pessoa *raiz);

