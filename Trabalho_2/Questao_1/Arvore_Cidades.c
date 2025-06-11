#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "prototipos.h"

#define RED 1
#define BLACK 0

struct dadoCidade Ler_dados_Cidade() {
    struct dadoCidade dado;
    printf("Digite o nome da cidade: ");
    fgets(dado.nome, sizeof(dado.nome), stdin);
    printf("Digite a população: ");
    scanf("%d", &dado.populacao);
    
    // Limpa o buffer do teclado
    while (getchar() != '\n');
    
    return dado;
}

int cor_arvore_cidade(Cidade *no) {
    if (no == NULL) {
        return BLACK; // Nulo é considerado preto
    }
    return no->cor; // Retorna a cor do nó
}

void troca_cor_cidade(Cidade *no) {
    no->cor = !no->cor; // Inverte a cor do nó
    if (no->esquerda != NULL) {
        no->esquerda->cor = !no->esquerda->cor; // Inverte a cor do filho esquerdo
    }
    if (no->direita != NULL) {
        no->direita->cor = !no->direita->cor; // Inverte a cor do filho direito
    }
}

Cidade *rotacionar_esquerda_cidade(Cidade *raiz) {
    Cidade *novo = raiz->direita;
    raiz->direita = novo->esquerda;
    novo->esquerda = raiz;
    novo->cor = raiz->cor;
    raiz->cor = RED; // A raiz agora é vermelha
    return novo;
}

Cidade *rotacionar_direita_cidade(Cidade *raiz) {
    Cidade *novo = raiz->esquerda;
    raiz->esquerda = novo->direita;
    novo->direita = raiz;
    novo->cor = raiz->cor;
    raiz->cor = RED; // A raiz agora é vermelha
    return novo;
}

Cidade *move_red_esq_cidade(Cidade *raiz) {
    troca_cor_cidade(raiz);
    if (cor_arvore_cidade(raiz->direita->esquerda) == RED) {
        raiz->direita = rotacionar_direita_cidade(raiz->direita);
        raiz = rotacionar_esquerda_cidade(raiz);
        troca_cor_cidade(raiz);
    }
    return raiz;
}

Cidade *move_red_dir_cidade(Cidade *raiz) {
    troca_cor_cidade(raiz);
    if (cor_arvore_cidade(raiz->esquerda->esquerda) == RED) {
        raiz = rotacionar_direita_cidade(raiz);
        troca_cor_cidade(raiz);
    }
    return raiz;
}

Cidade *procuraMenor_cidade(Cidade *raiz) {
    Cidade *no1 = raiz;
    Cidade *no2 = raiz->esquerda;
    while (no2 != NULL) {
        no1 = no2;
        no2 = no2->esquerda;
    }
    return no1; // Retorna o menor nó encontrado
}

Cidade *balancear_cidade(Cidade *raiz) {
    if (cor_arvore_cidade(raiz->direita) == RED) {
        raiz = rotacionar_esquerda_cidade(raiz);
    }
    if (cor_arvore_cidade(raiz->esquerda) == RED && cor_arvore_cidade(raiz->esquerda->esquerda) == RED) {
        raiz = rotacionar_direita_cidade(raiz);
    }
    if (cor_arvore_cidade(raiz->esquerda) == RED && cor_arvore_cidade(raiz->direita) == RED) {
        troca_cor_cidade(raiz);
    }
    return raiz;

}

Cidade *remove_menor_cidade(Cidade *raiz) {
    Cidade *temp;
    if (raiz->esquerda == NULL) {
        temp = raiz->direita;
        free(raiz);
        return temp; // Retorna o filho direito ou NULL se não houver
    }
    if (cor_arvore_cidade(raiz->esquerda) == BLACK && cor_arvore_cidade(raiz->esquerda->esquerda) == BLACK) {
        raiz = move_red_esq_cidade(raiz);
    }
    raiz->esquerda = remove_menor_cidade(raiz->esquerda);
    return balancear_cidade(raiz);
}

Cidade *remover_no_cidade(Cidade **raiz, const char *nome) {
    if (*raiz != NULL) {
        if (strcmp(nome, (*raiz)->dado.nome) < 0) {
            if (cor_arvore_cidade((*raiz)->esquerda) == BLACK && cor_arvore_cidade((*raiz)->direita) == BLACK) {
                *raiz = move_red_esq_cidade(*raiz);
            }
            (*raiz)->esquerda = remover_no_cidade(&((*raiz)->esquerda), nome);
        } else {
            if (cor_arvore_cidade((*raiz)->esquerda) == RED) {
                *raiz = rotacionar_direita_cidade(*raiz);
            }
            if (strcmp(nome, (*raiz)->dado.nome) == 0 && (*raiz)->direita == NULL) {
                free(*raiz);
                *raiz = NULL;
                return NULL; // Cidade removida com sucesso
            }
            if (cor_arvore_cidade((*raiz)->direita) == BLACK && cor_arvore_cidade((*raiz)->direita->esquerda) == BLACK) {
                *raiz = move_red_dir_cidade(*raiz);
            }
            if (strcmp(nome, (*raiz)->dado.nome) == 0) {
                Cidade *auxiliar_menor = procuraMenor_cidade((*raiz)->direita);
                (*raiz)->dado = auxiliar_menor->dado; // Copia os dados do menor nó
                (*raiz)->direita = remove_menor_cidade(&((*raiz)->direita));
            }else	{
                (*raiz)->direita = remover_no_cidade(&((*raiz)->direita), nome);
            }
        }
    }
    *raiz = balancear_cidade(*raiz);
    return *raiz;
}


int remove_arvore_cidade(Cidade **raiz_cidade, const char *nome) {
    int removeu = 0;
    if (*raiz_cidade != NULL) {
        Cidade *no_removido = remover_no_cidade(raiz_cidade, nome);
        if (no_removido == NULL) {
            (*raiz_cidade)->cor = BLACK; 
            removeu = 1; // Cidade removida com sucesso
        }
    }
    return removeu;
}


Cidade* criar_cidade(struct dadoCidade dado) {
    Cidade *nova = (Cidade *) malloc(sizeof(Cidade));
    if (nova != NULL) {
        nova->dado = dado;
        nova->esquerda = NULL;
        nova->direita = NULL;
        nova->cor = 0; // Inicialmente vermelho
    }
    return nova;
}

// Função para inserir uma cidade na árvore vermelha-preta
int insere_cidades_arovreRB(Cidade **raiz_cidade, struct dadoCidade dado){
    int inseriu = 0;
    if(*raiz_cidade == NULL){
        *raiz_cidade = criar_cidade(dado);
        inseriu =1;
    }else if(strcmp(dado.nome, (*raiz_cidade)->dado.nome) < 0){
        inseriu = insere_cidades_arovreRB(&((*raiz_cidade)->esquerda), dado);
    }else if(strcmp(dado.nome, (*raiz_cidade)->dado.nome) > 0){
        inseriu = insere_cidades_arovreRB(&((*raiz_cidade)->direita), dado);
    }
    *raiz_cidade = balancear_cidade(*raiz_cidade);
    return inseriu;
}

void exibir_cidades(Cidade *raiz) {
    if (raiz != NULL) {
        exibir_cidades(raiz->esquerda);
        printf("Cidade: %s, População: %d\n", raiz->dado.nome, raiz->dado.populacao);
        exibir_cidades(raiz->direita);
    }
}

void liberar_cidades(Cidade *raiz) {
    if (raiz != NULL) {
        liberar_cidades(raiz->esquerda);
        liberar_cidades(raiz->direita);
        free(raiz);
    }
}