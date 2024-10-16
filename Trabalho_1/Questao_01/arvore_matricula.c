#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "prototipos.h"


Arvore_matricula *cria_arvore_matricula(){
    Arvore_matricula *raiz;
    raiz = (Arvore_matricula*)malloc(sizeof(Arvore_matricula));
    if(raiz != NULL){
        raiz = NULL;
    }
    return raiz;
}

Arvore_matricula *aloca_no_matricula(int codigo_disciplina){
    Arvore_matricula *novo_matricula;
    novo_matricula = (Arvore_matricula*)malloc(sizeof(Arvore_matricula));
    if(novo_matricula != NULL){
        novo_matricula->codigo_disciplina = codigo_disciplina;
        novo_matricula->esq = NULL;
        novo_matricula->dir = NULL;
    }
    return novo_matricula;
}

int inserir_arvore_matricula(Arvore_matricula **raiz_matricula, int codigo_disciplina){
    int inseriu = 0;
    if(*raiz_matricula == NULL){
       *raiz_matricula = aloca_no_matricula(codigo_disciplina);
       inseriu = 1;
    }else if(codigo_disciplina < (*raiz_matricula)->codigo_disciplina){
        inseriu = inserir_arvore_matricula(&((*raiz_matricula)->esq), codigo_disciplina);
    }else{
        inseriu = inserir_arvore_matricula(&((*raiz_matricula)->dir), codigo_disciplina);
    }
    return inseriu;
}

int verifica_disciplina_matriculada(Arvore_matricula *raiz_matricula, int codigo_disciplina){
    int status = 0;
    if(raiz_matricula != NULL){
        if(raiz_matricula->codigo_disciplina == codigo_disciplina){
            status = 1;
        }else if(codigo_disciplina < raiz_matricula->codigo_disciplina){
            status = verifica_disciplina_matriculada(raiz_matricula->esq, codigo_disciplina);
        }else{
            status = verifica_disciplina_matriculada(raiz_matricula->dir, codigo_disciplina);
        }
    }
    return status;
}

void imprime_avore_matricula(Arvore_matricula *raiz){
    if(raiz != NULL){
        imprime_avore_matricula(raiz->esq);
        printf("Codigo da disciplina: %d\n", raiz->codigo_disciplina);
        imprime_avore_matricula(raiz->dir);
    }
}
