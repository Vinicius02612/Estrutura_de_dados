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

int inserir_disciplina(Arvore_disciplina **raiz_disciplina, Dado_disciplina disciplina){
    int inseriu = 0;
    if(*raiz_disciplina == NULL){
        *raiz_disciplina = aloca_no_disciplina(disciplina);
        inseriu = 1;
    }else if(disciplina.codigo_disciplina < (*raiz_disciplina)->disciplina.codigo_disciplina){
       inseriu = inserir_disciplina(&((*raiz_disciplina)->esq), disciplina);
    }else{
        inseriu = inserir_disciplina(&((*raiz_disciplina)->dir), disciplina);
    }
    return inseriu;
}

int verifica_periodo( Dado_curso curso, Dado_disciplina disciplina  ){
    int status = 0;
    
    if((disciplina.numero_periodo >=  1) &&  (disciplina.numero_periodo <= curso.quantidade_periodos) ){
            status = 1;
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
    int adicionou, status;
    Arvore_curso *arvore_curso;
    Dado_curso curso;
    if(raiz_curso != NULL){
        curso = buscar_dado_curso(raiz_curso, codigo_curso);
        Arvore_disciplina *arv_disciplina;
        arv_disciplina = curso.disciplinas;
        if(verifica_periodo(curso, disciplina) != 0 && verifica_carga_horaria(disciplina) != 0){
            status = inserir_disciplina(&arv_disciplina, disciplina);
            if(status != 0){
                adicionou = 1;
            }
        }   
    }
    return adicionou;
}

Dado_disciplina buscar_disciplina(Arvore_disciplina *raiz_disciplina, int codigo_disciplina){
    Dado_disciplina disciplina;
    if(raiz_disciplina != NULL){
        if(raiz_disciplina->disciplina.codigo_disciplina == codigo_disciplina){
            disciplina = raiz_disciplina->disciplina;
        }else if(codigo_disciplina < raiz_disciplina->disciplina.codigo_disciplina){
            disciplina = buscar_disciplina(raiz_disciplina->esq, codigo_disciplina);
        }else{
            disciplina = buscar_disciplina(raiz_disciplina->dir, codigo_disciplina);
        }
    }
    return disciplina;
}

Arvore_disciplina *procura_menor_dir(Arvore_disciplina *raiz){
    Arvore_disciplina *aux = raiz;
    while(aux->esq != NULL){
        aux = aux->esq;
    }
    return aux;
}


int remover_disciplina(Arvore_disciplina **raiz_disciplina, int codigo_disciplina){
    int status = 0;
    if(*raiz_disciplina != NULL){
        if((*raiz_disciplina)->disciplina.codigo_disciplina == codigo_disciplina){
            if((*raiz_disciplina)->esq == NULL && (*raiz_disciplina)->dir == NULL){ // no folha
                free(*raiz_disciplina);
                *raiz_disciplina = NULL;
            }else if((*raiz_disciplina)->esq == NULL){
                Arvore_disciplina *aux = *raiz_disciplina;
                *raiz_disciplina = (*raiz_disciplina)->dir;
                free(aux);
            }else if((*raiz_disciplina)->dir == NULL){
                Arvore_disciplina *aux = *raiz_disciplina;
                *raiz_disciplina = (*raiz_disciplina)->esq;
                free(aux);
            }else{
                Arvore_disciplina *aux = procura_menor_dir((*raiz_disciplina)->dir);
                (*raiz_disciplina)->disciplina = aux->disciplina;
                status = remover_disciplina(&((*raiz_disciplina)->esq), aux->disciplina.codigo_disciplina);
            }
            status = 1;
        }else if(codigo_disciplina < (*raiz_disciplina)->disciplina.codigo_disciplina){
            status = remover_disciplina(&((*raiz_disciplina)->esq), codigo_disciplina);
        }else if(codigo_disciplina > (*raiz_disciplina)->disciplina.codigo_disciplina){
            status = remover_disciplina(&((*raiz_disciplina)->dir), codigo_disciplina);
        }
    }
    return status;

}

void imprmir_dado_disciplina(Dado_disciplina disciplina){
    printf("---------------------------\n"
            "Codigo da disciplina: %d\n"
            "Nome da disciplina: %s\n"
            "Carga Horária %d\n"
            "Numero de Periodos %d\n"
            "---------------------------\n",
            disciplina.codigo_disciplina, 
            disciplina.nome_disciplina, 
            disciplina.carga_horaria, 
            disciplina.numero_periodo
           );
           
}

void imprimir_arvore_disciplina(Arvore_disciplina *raiz){
    if(raiz != NULL){
        imprimir_arvore_disciplina(raiz->esq);
        imprmir_dado_disciplina(raiz->disciplina);
        imprimir_arvore_disciplina(raiz->dir);
    }
}

//liberar arvore disciplina
void libera_arvore_disciplina(Arvore_disciplina *raiz){
    if(raiz != NULL){
        libera_arvore_disciplina(raiz->esq);
        libera_arvore_disciplina(raiz->dir);
        free(raiz);
    }
}