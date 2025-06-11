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
int  inserir_estado(Estado **inicio, Estado *novo) {
    int inseriu =0;
    if (*inicio != NULL) {
         Estado *atual = *inicio;
        while (atual != NULL && strcmp(novo->dado.nome, atual->dado.nome) > 0) {
            atual = atual->proximo;
        }

        if (atual == *inicio) {
            // Inserir no início
            novo->proximo = *inicio;
            (*inicio)->anterior = novo;
            *inicio = novo;
            inseriu = 1;
        } else if (atual == NULL) {
            // Inserir no final
            Estado *ultimo = *inicio;
            while (ultimo->proximo != NULL) {
                ultimo = ultimo->proximo;
            }
            ultimo->proximo = novo;
            novo->anterior = ultimo;
            inseriu = 1;
        } else {
            // Inserir no meio
            novo->proximo = atual;
            novo->anterior = atual->anterior;
            atual->anterior->proximo = novo;
            atual->anterior = novo;
            inseriu = 1;
        }
    }
    return inseriu;
}

int buscar_estado(Estado *inicio, const char *nome_estado){
    int achou = 0;
    Estado *atual = inicio;
    while (atual != NULL) {
        if (strcmp(atual->dado.nome, nome_estado) == 0) {
           achou = 1;
        }
        atual = atual->proximo;
    }
    return achou; // Estado não encontrado
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


/**/
Estado* estado_mais_populoso(Estado *inicio) {
    if (inicio == NULL) return NULL;
    Estado *mais_populoso = inicio;
    Estado *atual = inicio->proximo;
    while (atual != NULL) {
        if (atual->dado.populacao > mais_populoso->dado.populacao) {
            mais_populoso = atual;
        }
        atual = atual->proximo;
    }
    return mais_populoso;
}

int populacao_capital_estado(Estado *inicio, const char *nome_estado) {
    int populacao = -1; // Valor padrão para indicar que o estado não foi encontrado
    Estado *atual = inicio;
    while (atual != NULL) {
        if (strcmp(atual->dado.nome, nome_estado) == 0) {
            // Supondo que a população da capital é igual à população do estado
            // Se houver campo separado para população da capital, altere aqui
            populacao =  atual->dado.populacao;
        }
        atual = atual->proximo;
    }
    return populacao; 
}