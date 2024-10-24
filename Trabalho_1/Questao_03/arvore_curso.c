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
        novo_curso->altura = 0;
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
    curso.disciplinas = cria_arvore_disciplina();
    return curso;
}

int pega_altura(Arvore_curso *raiz){
    if(raiz == NULL){
        return -1;
    }else{
        return raiz->altura;
    }
   
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void atualizar_altura(Arvore_curso *raiz){

    if(raiz != NULL){
        raiz->altura = 1 + max(pega_altura(raiz->esq), pega_altura(raiz->dir));
    }
}

void rotacao_direita(Arvore_curso **raiz){
    Arvore_curso *aux;
    aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;
    
    atualizar_altura(*raiz);
    atualizar_altura(aux);
    *raiz = aux;
}


void rotacao_esquerda(Arvore_curso **raiz){
    Arvore_curso *aux;
    aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;
   
    atualizar_altura(*raiz);
    atualizar_altura(aux);
    *raiz = aux;
}

//balanceamento da arvore 
void balancear_arvore(Arvore_curso **raiz) {
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

/* Função para inserir um curso na arvore */
int inserir_curso(Arvore_curso **raiz, Dado_curso curso){
    int inseriu;

    if(*raiz == NULL){
        *raiz = aloca_no_curso(curso);
        inseriu = 1;
    }else if(curso.codigo_curso < (*raiz)->curso.codigo_curso){
        inseriu = inserir_curso(&((*raiz)->esq), curso);
    }else if(curso.codigo_curso > (*raiz)->curso.codigo_curso){
        inseriu = inserir_curso(&((*raiz)->dir), curso);
    }else{
        inseriu = 0;
    }
    balancear_arvore(raiz);
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

Arvore_curso *buscar_curso(Arvore_curso *raiz_curso, int codigo_curso){
    Arvore_curso *curso;
    if(raiz_curso != NULL){
        if(raiz_curso->curso.codigo_curso == codigo_curso){
            curso = raiz_curso;
        }else if(codigo_curso < raiz_curso->curso.codigo_curso){
            curso = buscar_curso(raiz_curso->esq, codigo_curso);
        }else{
            curso = buscar_curso(raiz_curso->dir, codigo_curso);
        }
    }
    return curso;
}

void imprime_dado_curso(Dado_curso curso){
    printf(
        "\nCodigo do curso: %d \n "
        "Nome do curso: %s \n"
        "Carga Horária %d \n"
        "Quantidade de Periodos %d \n",curso.codigo_curso, curso.nome_curso, curso.carga_horaria, curso.quantidade_periodos);
   if(curso.disciplinas != NULL){
        printf("Disciplinas do curso %s \n",curso.nome_curso);
        imprimir_arvore_disciplina(curso.disciplinas);
   }
}

void imprime_arvore_cursos(Arvore_curso *raiz){
    if(raiz != NULL){
        imprime_arvore_cursos(raiz->esq);
        imprime_dado_curso(raiz->curso);
        imprime_arvore_cursos(raiz->dir);
    }
}

//viii) Mostrar todas as disciplinas de um determinado curso
void mostrar_disciplinas_de_curso(Arvore_curso *raiz_curso, int codigo_curso){
    Dado_curso curso;
    curso = buscar_dado_curso(raiz_curso, codigo_curso);
    if(curso.disciplinas != NULL){
        imprime_dado_curso(curso);
    }else{
        printf("Curso sem disciplinas cadastradas\n");
    }
}

// ix) Mostrar todas as disciplinas de um determinado período de um curso.
void mostrar_disciplinas_de_periodo_curso(Arvore_curso *raiz_curso, int numero_periodo, int codigo_curso){
    Dado_curso curso;
    curso = buscar_dado_curso(raiz_curso, codigo_curso);
    
    if(curso.disciplinas != NULL){
        if(curso.disciplinas->disciplina.numero_periodo == numero_periodo){
            imprimir_arvore_disciplina(curso.disciplinas);
        }
    }
    

}

//Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horária da disciplina.
void mostrar_nota_disciplina_aluno(Arvore_curso *raiz_curso,Lista_alunos *lst_alunos, int codigo_disciplina, int matricula){
    Dado_aluno aluno = buscar_aluno(lst_alunos, matricula);
    Arvore_notas *nota = buscar_nota_aluno(aluno.notas, codigo_disciplina);

    imprime_arvore_notas(nota);


}


/* xiii)Remover uma disciplina de um determinado curso desde que não tenha nenhum aluno matriculado na
mesma. */
int remover_disciplina_curso(Arvore_curso *raiz_curso, int codigo_disciplina, int codigo_curso){
    int status = 0;
    Arvore_curso *curso = buscar_curso(raiz_curso, codigo_curso);
    imprime_arvore_cursos(curso);
    if(curso->curso.disciplinas != NULL){
        status = remover_disciplina(&curso->curso.disciplinas, codigo_disciplina);
    }
    return status;
}


/* Mostrar o histórico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva
nota organizadas pelo período que a disciplina está cadastrada no curso. */
void mostrar_historico_aluno(Arvore_curso *raiz_curso, Lista_alunos *lst_alunos, int matricula){
    Lista_alunos *aluno = buscar_aluno_por_matricula(lst_alunos, matricula);
    Arvore_curso *curso = buscar_curso(raiz_curso, aluno->aluno.codigo_curso);
    if(aluno->aluno.codigo_curso == curso->curso.codigo_curso){
        printf("Nome do curso: %s\n", curso->curso.nome_curso);
        imprimir_arvore_disciplina(curso->curso.disciplinas);
        imprime_arvore_notas(aluno->aluno.notas);
    }


}

//libera arvore curso
void libera_arvore_curso(Arvore_curso *raiz){
    if(raiz != NULL){
        libera_arvore_curso(raiz->esq);
        libera_arvore_curso(raiz->dir);
        free(raiz);
    }
}