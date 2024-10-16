#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "prototipos.h"



Arvore_disciplina *cria_arvore_disciplina(){
    Arvore_disciplina *raiz;
    raiz = (Arvore_disciplina*)malloc(sizeof(Arvore_disciplina));
    if(raiz != NULL){
        raiz = NULL;
    }
    return raiz;
}

Arvore_disciplina *aloca_no_disciplina(Dado_disciplina disciplina){
    Arvore_disciplina *novo_disciplina;
    novo_disciplina = (Arvore_disciplina*)malloc(sizeof(Arvore_disciplina));
    if(novo_disciplina != NULL){
        novo_disciplina->disciplina = disciplina;
        novo_disciplina->esq = NULL;
        novo_disciplina->dir = NULL;
    }
    return novo_disciplina;
}

Dado_disciplina lerDadosDisciplina(){
    Dado_disciplina disciplina;
    printf("Digite o codigo da disciplina: ");
    scanf("%d", &disciplina.codigo_disciplina);
    printf("Digite o nome da disciplina: ");
    scanf("%s", disciplina.nome_disciplina);
    printf("Digite a carga horaria da disciplina: ");
    scanf("%d", &disciplina.carga_horaria);
    printf("Digite o semestre da disciplina: ");
    scanf("%d", &disciplina.numero_periodo);
    return disciplina;
}

Arvore_disciplina *inserir_disciplina(Arvore_disciplina **raiz_disciplina, Dado_disciplina disciplina){
    if(*raiz_disciplina == NULL){
        *raiz_disciplina = aloca_no_disciplina(disciplina);
    }else if(disciplina.codigo_disciplina < (*raiz_disciplina)->disciplina.codigo_disciplina){
        (*raiz_disciplina)->esq = inserir_disciplina(&((*raiz_disciplina)->esq), disciplina);
    }else{
        (*raiz_disciplina)->dir = inserir_disciplina(&((*raiz_disciplina)->dir), disciplina);
    }
    return *raiz_disciplina;
}

int verifica_periodo( Arvore_curso *raiz_curso, Dado_disciplina disciplina  ){
    int status = 0;
    if(raiz_curso != NULL){
        if( (disciplina.numero_periodo <  1) &&  (disciplina.numero_periodo <= raiz_curso->curso.quantidade_periodos) ){
            status = 1;
        }
    }
    return status;
}
 

int verifica_carga_horaria(Dado_disciplina disciplina){
    int status = 0 ,resto_carga_horaria;
    resto_carga_horaria = (disciplina.carga_horaria % 15);
    if(resto_carga_horaria == 0 && disciplina.carga_horaria >= 30 && disciplina.carga_horaria <= 90){
        status = 1;
    }
    return status;
}


//adicionar disciplina ao curso
int adicionar_disciplina_curso(Arvore_curso *raiz_curso, Dado_disciplina disciplina, int codigo_curso){
    int adicionou = 0;
    Dado_curso curso;
    if(raiz_curso != NULL){
        curso = buscar_dado_curso(raiz_curso, codigo_curso);
        if(verifica_periodo(raiz_curso, disciplina) != 0 && verifica_carga_horaria(disciplina) != 0){
            curso.disciplinas = inserir_disciplina(&(curso.disciplinas), disciplina);
            adicionou = 1;
        }   
    }
    return adicionou;
}


void imprmir_dado_disciplina(Dado_disciplina disciplina){
    printf("Codigo da disciplina: %d | \n Nome da disciplina: %s |\n Carga Horária %d |\n Numero de Periodos %d |\n",disciplina.codigo_disciplina, disciplina.nome_disciplina, disciplina.carga_horaria, disciplina.numero_periodo);
}

void imprimir_arvore_disciplina(Arvore_disciplina *raiz){
    if(raiz != NULL){
        imprimir_arvore_disciplina(raiz->esq);
        imprmir_dado_disciplina(raiz->disciplina);
        imprimir_arvore_disciplina(raiz->dir);
    }
}