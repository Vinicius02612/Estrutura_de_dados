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

int pega_altura(Arvore_notas *raiz){
    if(raiz == NULL){
        return -1;
    }else{
        return raiz->altura;
    }
   
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void atualizar_altura(Arvore_notas *raiz){

    if(raiz != NULL){
        raiz->altura = 1 + max(pega_altura(raiz->esq), pega_altura(raiz->dir));
    }
}

void rotacao_direita(Arvore_notas **raiz){
    Arvore_notas *aux;
    aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;
    
    atualizar_altura(*raiz);
    atualizar_altura(aux);
    *raiz = aux;
}

void rotacao_esquerda(Arvore_notas **raiz){
    Arvore_notas *aux;
    aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;
   
    atualizar_altura(*raiz);
    atualizar_altura(aux);
    *raiz = aux;
}

void balancear_arvore(Arvore_notas **raiz) {
    atualizar_altura(*raiz);

    int fb = pega_altura((*raiz)->esq) - pega_altura((*raiz)->dir);
    if (fb > 1) {
        if (pega_altura((*raiz)->esq->esq) >= pega_altura((*raiz)->esq->dir)) {
            rotacao_direita(raiz);
        } else {
            rotacao_esquerda(&(*raiz)->esq);
            rotacao_direita(raiz);
        }
    } else if (fb < -1) {
        if (pega_altura((*raiz)->dir->dir) >= pega_altura((*raiz)->dir->esq)) {
            rotacao_esquerda(raiz);
        } else {
            rotacao_direita(&(*raiz)->dir);
            rotacao_esquerda(raiz);
        }
    }
}

int inserir_arvore_nota(Arvore_notas **raiz_notas, Dado_nota nota){
    int inseriu = 0;
    if(*raiz_notas == NULL){
        *raiz_notas = aloca_no_nota(nota);
        inseriu = 1;
    }else if(nota.codigo_disciplina < (*raiz_notas)->nota.codigo_disciplina){
        inseriu = inserir_arvore_nota(&((*raiz_notas)->esq), nota);
    }else if(nota.codigo_disciplina > (*raiz_notas)->nota.codigo_disciplina){
        inseriu = inserir_arvore_nota(&((*raiz_notas)->dir), nota);
    }else{
        inseriu = 0;
    }
    balancear_arvore(raiz_notas);
    return inseriu;
}

Arvore_notas *buscar_nota_aluno(Arvore_notas *raiz_notas, int codigo_disciplina){
    Arvore_notas *nota;
    if(raiz_notas != NULL){
        if(raiz_notas->nota.codigo_disciplina == codigo_disciplina){
            nota = raiz_notas;
        }else if(codigo_disciplina < raiz_notas->nota.codigo_disciplina){
            nota = buscar_nota_aluno(raiz_notas->esq, codigo_disciplina);
        }else{
            nota = buscar_nota_aluno(raiz_notas->dir, codigo_disciplina);
        }
    }
    return nota;
}

int inserir_nota_aluno(Lista_alunos *lst_alunos, int matricula, Dado_nota nota ){

   int status = 0;
   Lista_alunos *aluno_notas = buscar_aluno_por_matricula(lst_alunos, matricula);

   status = inserir_arvore_nota(&aluno_notas->aluno.notas, nota);
  

   return status;

}

void imprime_dado_nota(Dado_nota nota){
    printf("---------------------------\n");
    printf("Codigo disciplina: %d\n", nota.codigo_disciplina);
    printf("Nota final: %.2f\n", nota.nota_final);
    printf("Semestre cursado: %d\n", nota.semestre_cursado);
    printf("---------------------------\n");
}

void imprime_arvore_notas(Arvore_notas *raiz_notas){
    if(raiz_notas != NULL){
        imprime_arvore_notas(raiz_notas->esq);
        imprime_dado_nota(raiz_notas->nota);
        imprime_arvore_notas(raiz_notas->dir);
    }
}

// liberar a arvore de notas
void libera_arvore_notas(Arvore_notas *raiz){
    if(raiz != NULL){
        libera_arvore_notas(raiz->esq);
        libera_arvore_notas(raiz->dir);
        free(raiz);
    }
}