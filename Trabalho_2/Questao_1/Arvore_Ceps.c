#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "prototipos.h"
#define RED 1
#define BLACK 0


struct dadoCep Ler_dados_Cep() {
    struct dadoCep dado;
    printf("Digite o CEP: ");
    scanf("%d", &dado.cep);
    // Limpa o buffer do teclado
    while (getchar() != '\n');
    return dado;
}

Ceps* criar_cep(int cep) {
    Ceps *novo = (Ceps *) malloc(sizeof(Ceps));
    if (novo != NULL) {
        novo->dado.cep = cep;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->cor = 0; // Inicialmente vermelho
    }
    return novo;
}



int cor(Ceps *no) {
    if (no == NULL) {
        return BLACK; // Nulo é considerado preto
    }
    return no->cor; // Retorna a cor do nó
}

void troca_cor(Ceps *no) {
   no->cor = !no->cor; // Inverte a cor do nó
   if (no->esquerda != NULL) {
       no->esquerda->cor = !no->esquerda->cor; // Inverte a cor do filho esquerdo
   }
   if(no->direita != NULL) {
       no->direita->cor = !no->direita->cor; // Inverte a cor do filho direito
   }
}

Ceps *rotacionar_esquerda(Ceps *raiz) {
    Ceps *novo = raiz->direita;
    raiz->direita = novo->esquerda;
    novo->esquerda = raiz;
    novo->cor = raiz->cor;
    raiz->cor = RED; // A raiz agora é vermelha
    return novo;
}

Ceps *rotacionar_direita(Ceps *raiz) {
    Ceps *novo = raiz->esquerda;
    raiz->esquerda = novo->direita;
    novo->direita = raiz;
    novo->cor = raiz->cor;
    raiz->cor = RED; // A raiz agora é vermelha
    return novo;
}

Ceps *procuraMenor_cep(Ceps *raiz) {
    Ceps *no1 = raiz;
    Ceps *no2 = raiz->esquerda;
    while (no2 != NULL) {
        no1 = no2;
        no2 = no2->esquerda;
    }
    return no1;
}

Ceps *move_red_dir(Ceps *raiz){
    troca_cor(raiz);
    if(cor(raiz->esquerda->esquerda) == RED){
        raiz = rotacionar_direita(raiz->direita);
        troca_cor(raiz);
    }
    return raiz;
}

Ceps *move_red_esq(Ceps *raiz){
    troca_cor(raiz);
    if(cor(raiz->direita->esquerda) == RED){
        raiz->direita = rotacionar_esquerda(raiz->direita);
        raiz = rotacionar_direita(raiz);
        troca_cor(raiz);
    }
    return raiz;
}

Ceps *balancear_cep(Ceps *raiz) {
    if (cor(raiz->direita) == RED) {
        raiz = rotacionar_esquerda(raiz);
    }
    if (cor(raiz->esquerda) == RED && cor(raiz->esquerda->esquerda) == RED) {
        raiz = rotacionar_direita(raiz);
    }
    if (cor(raiz->esquerda) == RED && cor(raiz->direita) == RED) {
        troca_cor(raiz);
    }
    return raiz;
}

int insere_cep_arvoreRB(Ceps **raiz, struct dadoCep dado) {
    int inseriu = 0;
    if (*raiz == NULL) {
        *raiz = criar_cep(dado.cep);
        inseriu = 1;
    } else if (dado.cep < (*raiz)->dado.cep) {
        inseriu = insere_cep_arvoreRB(&((*raiz)->esquerda), dado);
    } else if (dado.cep > (*raiz)->dado.cep) {
        inseriu = insere_cep_arvoreRB(&((*raiz)->direita), dado);
    }
    *raiz  =  balancear_cep(*raiz);
    return inseriu;
}

void exibir_ceps(Ceps *raiz) {
    if (raiz != NULL) {
        exibir_ceps(raiz->esquerda);
        printf("CEP: %d\n", raiz->dado.cep);
        exibir_ceps(raiz->direita);
    }
}

void liberar_ceps(Ceps *raiz) {
    if (raiz != NULL) {
        liberar_ceps(raiz->esquerda);
        liberar_ceps(raiz->direita);
        free(raiz);
    }
}

Ceps *remove_menor(Ceps *raiz){
    Ceps *temp;
    if(raiz->esquerda == NULL){
        temp = raiz->direita;
        free(raiz);
        return temp; // Retorna o filho direito ou NULL se não houver
    }
    if(cor(raiz->esquerda) == BLACK && cor(raiz->esquerda->esquerda) == BLACK){
        raiz = move_red_esq(raiz);
    }
    raiz->esquerda = remove_menor(raiz->esquerda);
    return balancear_cep(raiz);
}


Ceps *remover_no_cep(Ceps **raiz, int cep) {
    
    if(*raiz != NULL){
        if(cep < (*raiz)->dado.cep){
            if(cor((*raiz)->esquerda) == BLACK && cor((*raiz)->direita) == BLACK){
                *raiz = move_red_left(*raiz);
            }
            (*raiz)->esquerda = remover_no_cep(&((*raiz)->esquerda), cep);  
        }else{
            if(cor((*raiz)->esquerda) == RED){
                *raiz = rotacionar_direita(*raiz);
            }
            if(cep == (*raiz)->dado.cep && (*raiz)->direita == NULL){
                free(*raiz);
                *raiz = NULL;
                return 1; // CEP removido com sucesso
            }
            if(cor((*raiz)->direita) == BLACK && cor((*raiz)->direita->esquerda) == BLACK){
                *raiz = move_red_dir(*raiz);
            }
            if(cep == (*raiz)->dado.cep){
                Ceps *auxiliar_menor = procuraMenor_cep((*raiz)->direita);
                (*raiz)->dado.cep = auxiliar_menor->dado.cep;
                (*raiz)->direita = remove_menor(&((*raiz)->direita));
            }else{
                (*raiz)->direita = remover_no_cep(&((*raiz)->direita), cep);
            }
        }
    }
    *raiz = balancear_cep(*raiz);
    return *raiz; 

}

int remove_arvore_cep(Ceps **raiz_ceps, int cep){
    int  removeu = 0;
    if(*raiz_ceps != NULL){
        *raiz_ceps = remover_no_cep(raiz_ceps, cep);
        if(*raiz_ceps != NULL){
            (*raiz_ceps)->cor = BLACK; // Garantir que a raiz seja preta
            removeu = 1; // CEP removido com sucesso
        }
    }
    return removeu;
}