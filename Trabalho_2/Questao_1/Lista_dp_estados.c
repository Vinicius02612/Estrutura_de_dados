#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "prototipos.h"
/* Uma lista duplamente encadeada de Estados do Brasil, a qual deve conter os seguintes campos em cada 
nó: Nome do Estado, nome da Capital, a quantidade de cidades do estado, o tamanho da população e 
um endereço para árvore vermelha-preta de cidades do estado. A lista deve ser ordenada pelo nome do 
Estado.  */




Estado* criar_estado(struct dadoEstado dado) {
    Estado *novo = (Estado *) malloc(sizeof(Estado));
    if (novo != NULL) {
        novo->dado = dado;
        novo->anterior = NULL;
        novo->proximo = NULL;
    }
    return novo;
}

struct dadoEstado Ler_dados_Estado() {
    struct dadoEstado dado;
    printf("Digite o nome do estado: ");
    fgets(dado.nome, sizeof(dado.nome), stdin);
   

    printf("Digite o nome da capital: ");
    fgets(dado.capital, sizeof(dado.capital), stdin);

   
    printf("Digite a população: ");
    scanf("%ld", &dado.populacao);
    
    // Limpa o buffer do teclado
    while (getchar() != '\n');

    return dado;
}
void inserir_estado(Estado **inicio, Estado *novo) {
    if (*inicio == NULL) {
        *inicio = novo;
        return;
    }

    Estado *atual = *inicio;
    while (atual != NULL && strcmp(novo->dado.nome, atual->dado.nome) > 0) {
        atual = atual->proximo;
    }

    if (atual == *inicio) {
        // Inserir no início
        novo->proximo = *inicio;
        (*inicio)->anterior = novo;
        *inicio = novo;
    } else if (atual == NULL) {
        // Inserir no final
        Estado *ultimo = *inicio;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = novo;
        novo->anterior = ultimo;
    } else {
        // Inserir no meio
        novo->proximo = atual;
        novo->anterior = atual->anterior;
        atual->anterior->proximo = novo;
        atual->anterior = novo;
    }
}


void mostra_dado_menu(struct dadoEstado dado) {
     printf("Estado: %s | Capital: %s | População: %ld | Qtd Cidades: %d\n",
            dado.nome, dado.capital, dado.populacao, dado.qtd_cidades);
}

void exibir_estados(Estado *inicio) {
    Estado *atual = inicio;
    printf("\n--- Lista de Estados ---\n");
    while (atual != NULL) {
        mostra_dado_menu(atual->dado);
        printf("-------------------------\n"); 
        atual = atual->proximo;
    }
}


void liberar_estados(Estado *inicio) {
    Estado *atual = inicio;
    while (atual != NULL) {
        Estado *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}
