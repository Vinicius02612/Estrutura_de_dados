#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "prototipos.h"



/* Função para criar arvore binaria */
Arvore_curso *cria_arvore_curso(){
    Arvore_curso *raiz;
    raiz = (Arvore_curso*)malloc(sizeof(Arvore_curso));
    if(raiz != NULL){
        raiz = NULL;
    }
    return raiz;
}
//aloca no da arvore
Arvore_curso *aloca_no_curso(Dado_curso curso){
    Arvore_curso *novo_curso;
    novo_curso = (Arvore_curso*)malloc(sizeof(Arvore_curso));
    if(novo_curso!=NULL){
        novo_curso->curso = curso;
        novo_curso->esq = NULL;
        novo_curso->dir = NULL;
    }
   
    return novo_curso;
}

Dado_curso lerDadosCurso(){
    Dado_curso curso;
    printf("Digite o codigo do curso: ");
    scanf("%d", &curso.codigo_curso);
    printf("Digite o nome do curso: ");
    scanf("%s", curso.nome_curso);
    printf("Digite a carga horaria do curso: ");
    scanf("%d", &curso.carga_horaria);
    printf("Digite a quantidade de periodos do curso: ");
    scanf("%d", &curso.quantidade_periodos);
    curso.disciplinas = NULL;
    return curso;
}

/* Função para inserir um curso na arvore */
int inserir_curso(Arvore_curso **raiz, Dado_curso curso){
    printf("Inserindo curso\n");
    int inseriu = 0;
    if(*raiz == NULL){
        printf("raiz nula\n");
        *raiz = aloca_no_curso(curso);
        inseriu = 1;
    }else if(curso.codigo_curso < (*raiz)->curso.codigo_curso){
        inseriu = inserir_curso(&((*raiz)->esq), curso);
    }else{
        inseriu = inserir_curso(&((*raiz)->dir), curso);
    }
    return inseriu;
}

int verifica_codigo_curso(Arvore_curso *raiz, int codigo_curso){
    int encontrou = 0;
    if(raiz != NULL){
        if(raiz->curso.codigo_curso == codigo_curso){
            encontrou = 1;
        }else if(codigo_curso < raiz->curso.codigo_curso){
            encontrou = verifica_codigo_curso(raiz->esq, codigo_curso);
        }else{
            encontrou = verifica_codigo_curso(raiz->dir, codigo_curso);
        }
    }
   return encontrou;
}


Dado_curso buscar_dado_curso(Arvore_curso *raiz, int codigo_curso){
    Dado_curso curso;
    if(raiz != NULL){
        if(raiz->curso.codigo_curso == codigo_curso){
            curso = raiz->curso;
        }else if(codigo_curso < raiz->curso.codigo_curso){
            curso = buscar_dado_curso(raiz->esq, codigo_curso);
        }else{
            curso = buscar_dado_curso(raiz->dir, codigo_curso);
        }
    }
    return curso;
}

void mostrar_disciplinas_de_curso(Arvore_curso *raiz_curso, int codigo_curso){
    Dado_curso curso;
    curso = buscar_dado_curso(raiz_curso, codigo_curso);
    if(curso.disciplinas != NULL){
        printf("Disciplinas do curso %s\n", curso.nome_curso);
        imprimir_arvore_disciplina(curso.disciplinas);
    }else{
        printf("Curso sem disciplinas cadastradas\n");
    }
}

void imprime_dado_curso(Dado_curso curso){
    printf("Codigo do curso: %d | \n Nome do curso: %s |\n Carga Horária %d |\n Quantidade de Periodos %d |\n",curso.codigo_curso, curso.nome_curso, curso.carga_horaria, curso.quantidade_periodos);
   if(curso.disciplinas != NULL){
        printf("Disciplinas do curso\n");
        //imprimir_arvore_disciplinas(curso.disciplinas);
   }
}

void imprime_arvore_cursos(Arvore_curso *raiz){
    if(raiz != NULL){
        imprime_arvore_cursos(raiz->esq);
        imprime_dado_curso(raiz->curso);
        imprime_arvore_cursos(raiz->dir);
    }
}

