#include "stdio.h"
#include "stdlib.h"
#include "prototipos.h"


Arvore_notas *cria_arvore_notas(){
    Arvore_notas *raiz;
    raiz = (Arvore_notas*)malloc(sizeof(Arvore_notas));
    if(raiz != NULL){
        raiz = NULL;
    }
    return raiz;
}

Arvore_notas *aloca_no_nota(Dado_nota nota){
    Arvore_notas *novo_nota;
    novo_nota = (Arvore_notas*)malloc(sizeof(Arvore_notas));
    if(novo_nota != NULL){
        novo_nota->nota = nota;
        novo_nota->esq = NULL;
        novo_nota->dir = NULL;
    }
    return novo_nota;
}

Dado_nota lerDadosNota(){
    Dado_nota nota;
    printf("Digite o codigo da disciplina: ");
    scanf("%d", &nota.codigo_disciplina);
    printf("Digite a nota final: ");
    scanf("%f", &nota.nota_final);
    printf("Digite o semestre cursado: ");
    scanf("%d", &nota.semestre_cursado);
    return nota;
}



int inserir_arvore_nota(Arvore_notas **raiz_notas, Dado_nota nota){
    int inseriu = 0;
    if(*raiz_notas == NULL){
        *raiz_notas = aloca_no_nota(nota);
        inseriu = 1;
    }else if(nota.codigo_disciplina < (*raiz_notas)->nota.codigo_disciplina){
        inseriu = inserir_arvore_nota(&((*raiz_notas)->esq), nota);
    }else{
        inseriu = inserir_arvore_nota(&((*raiz_notas)->dir), nota);
    }
    return inseriu;
}