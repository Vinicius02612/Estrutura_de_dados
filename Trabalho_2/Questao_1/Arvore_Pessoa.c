#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "prototipos.h"

#define RED 1
#define BLACK 0

struct dadoPessoa Ler_dados_Pessoa() {
    struct dadoPessoa dado;
    printf("Digite o CPF: ");
    fgets(dado.cpf, sizeof(dado.cpf), stdin);
    printf("Digite o nome: ");
    fgets(dado.nome, sizeof(dado.nome), stdin);
    printf("Digite o CEP de natal: ");
    scanf("%d", &dado.cep_natal);
    printf("Digite o CEP de moradia: ");
    scanf("%d", &dado.cep_moradia);
    printf("Digite a data de nascimento (dia mes ano): ");
    scanf("%d %d %d", &dado.dia, &dado.mes, &dado.ano);
    
    // Limpa o buffer do teclado
    while (getchar() != '\n');
    
    return dado;
}

Pessoa *criar_pessoa(struct dadoPessoa dado) {
    Pessoa *nova = (Pessoa *) malloc(sizeof(Pessoa));
    if (nova != NULL) {
        nova->dado = dado;
        nova->esquerda = NULL;
        nova->direita = NULL;
        nova->cor = RED; // Inicialmente vermelho
    }
    return nova;
}

int cor_arvore_pessoa(Pessoa *no) {
    if (no == NULL) {
        return BLACK; // Nulo é considerado preto
    }
    return no->cor; // Retorna a cor do nó
}

void troca_cor_pessoa(Pessoa *no) {
    no->cor = !no->cor; // Inverte a cor do nó
    if (no->esquerda != NULL) {
        no->esquerda->cor = !no->esquerda->cor; // Inverte a cor do filho esquerdo
    }
    if (no->direita != NULL) {
        no->direita->cor = !no->direita->cor; // Inverte a cor do filho direito
    }
}


Pessoa *procuraMenor_pessoa(Pessoa *raiz) {
    Pessoa *no1 = raiz;
    Pessoa *no2 = raiz->esquerda;
    while (no2 != NULL) {
        no1 = no2;
        no2 = no2->esquerda;
    }
    return no1; // Retorna o menor nó encontrado
}


Pessoa *rotacionar_esquerda_pessoa(Pessoa *raiz) {
    Pessoa *novo = raiz->direita;
    raiz->direita = novo->esquerda;
    novo->esquerda = raiz;
    novo->cor = raiz->cor;
    raiz->cor = RED; // A raiz agora é vermelha
    return novo;
}


Pessoa *rotacionar_direita_pessoa(Pessoa *raiz) {
    Pessoa *novo = raiz->esquerda;
    raiz->esquerda = novo->direita;
    novo->direita = raiz;
    novo->cor = raiz->cor;
    raiz->cor = RED; // A raiz agora é vermelha
    return novo;
}

Pessoa *move_red_esq_pessoa(Pessoa *raiz) {
    troca_cor_pessoa(raiz);
    if (cor_arvore_pessoa(raiz->direita->esquerda) == RED) {
        raiz->direita = rotacionar_direita_pessoa(raiz->direita);
        raiz = rotacionar_esquerda_pessoa(raiz);
        troca_cor_pessoa(raiz);
    }
    return raiz;
}

Pessoa *move_red_dir_pessoa(Pessoa *raiz) {
    troca_cor_pessoa(raiz);
    if (cor_arvore_pessoa(raiz->esquerda->esquerda) == RED) {
        raiz = rotacionar_direita_pessoa(raiz);
        troca_cor_pessoa(raiz);
    }
    return raiz;
}

Pessoa *balancear_pessoa(Pessoa *raiz) {
    if (cor_arvore_pessoa(raiz->direita) == RED) {
        raiz = rotacionar_esquerda_pessoa(raiz);
    }
    if (cor_arvore_pessoa(raiz->esquerda) == RED && cor_arvore_pessoa(raiz->esquerda->esquerda) == RED) {
        raiz = rotacionar_direita_pessoa(raiz);
    }
    if (cor_arvore_pessoa(raiz->esquerda) == RED && cor_arvore_pessoa(raiz->direita) == RED) {
        troca_cor_pessoa(raiz);
    }
    return raiz;
}


Pessoa *remove_menor_pessoa(Pessoa *raiz) {
    Pessoa *temp;
    if (raiz->esquerda == NULL) {
        temp = raiz->direita;
        free(raiz);
        return temp; // Retorna o filho direito ou NULL se não houver
    }
    if (cor_arvore_pessoa(raiz->esquerda) == BLACK && cor_arvore_pessoa(raiz->esquerda->esquerda) == BLACK) {
        raiz = balancear_pessoa(raiz);
    }
    raiz->esquerda = remove_menor_pessoa(raiz->esquerda);
    return balancear_pessoa(raiz);
}


int insere_pessoa_arvoreRB(Pessoa **raiz, struct dadoPessoa dado) {
    int inseriu = 0;
    if (*raiz == NULL) {
        *raiz = criar_pessoa(dado);
        inseriu = 1;
    } else if (strcmp(dado.cpf, (*raiz)->dado.cpf) < 0) {
        inseriu = insere_pessoa_arvoreRB(&((*raiz)->esquerda), dado);
    } else if (strcmp(dado.cpf, (*raiz)->dado.cpf) > 0) {
        inseriu = insere_pessoa_arvoreRB(&((*raiz)->direita), dado);
    }

    *raiz = balancear_pessoa(*raiz);
    return inseriu;
}

int remover_no_pessoa(Pessoa **raiz, const char *cpf) {
    int removeu = 0;
    if (*raiz != NULL) {
        if (strcmp(cpf, (*raiz)->dado.cpf) < 0) {
            if (cor_arvore_pessoa((*raiz)->esquerda) == BLACK && cor_arvore_pessoa((*raiz)->esquerda->esquerda) == BLACK) {
                *raiz = move_red_esq_pessoa(*raiz);
            }
            (*raiz)->esquerda = remover_pessoa(&((*raiz)->esquerda), cpf);
        } else {
            if (cor_arvore_pessoa((*raiz)->esquerda) == RED) {
                *raiz = rotacionar_direita_pessoa(*raiz);
            }
            if (strcmp(cpf, (*raiz)->dado.cpf) == 0 && (*raiz)->direita == NULL) {
                free(*raiz);
                *raiz = NULL;
                removeu = 1; // Pessoa removida com sucesso
            }
            if (cor_arvore_pessoa((*raiz)->direita) == BLACK && cor_arvore_pessoa((*raiz)->direita->esquerda) == BLACK) {
                *raiz = move_red_dir_pessoa(*raiz);
            }
            if (strcmp(cpf, (*raiz)->dado.cpf) == 0) {
                Pessoa *auxiliar_menor = procuraMenor_pessoa((*raiz)->direita);
                (*raiz)->dado = auxiliar_menor->dado; // Copia os dados do menor nó
                (*raiz)->direita = remove_menor_pessoa(&((*raiz)->direita));
            }else{
                (*raiz)->direita = remover_pessoa(&((*raiz)->direita), cpf);
            }
        }
    }
    *raiz = balancear_pessoa(*raiz);
    return removeu; // Retorna a raiz da árvore após remoção
}

int remover_arvore_pessoa(Pessoa **raiz, const char *cpf) {
    int removeu = 0;
    if (*raiz != NULL) {
        removeu = remover_no_pessoa(raiz, cpf);
        if (removeu) {
            if (*raiz != NULL) {
                (*raiz)->cor = BLACK; // A raiz deve ser sempre preta
            }
        }
    }
    return removeu;
}

void exibir_pessoas(Pessoa *raiz) {
    if (raiz != NULL) {
        exibir_pessoas(raiz->esquerda);
        printf("CPF: %s, Nome: %s, CEP Natal: %d, CEP Moradia: %d, Data Nascimento: %02d/%02d/%04d\n",
               raiz->dado.cpf, raiz->dado.nome, raiz->dado.cep_natal, raiz->dado.cep_moradia,
               raiz->dado.dia, raiz->dado.mes, raiz->dado.ano);
        exibir_pessoas(raiz->direita);
    }
}
void liberar_pessoas(Pessoa *raiz) {
    if (raiz != NULL) {
        liberar_pessoas(raiz->esquerda);
        liberar_pessoas(raiz->direita);
        free(raiz);
    }
}