#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "arvore_aluno.h"



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

Lista_alunos *cria_lista_alunos(){
    Lista_alunos *lst_aluno;
    lst_aluno = (Lista_alunos*) malloc(sizeof(Lista_alunos));
    if(lst_aluno != NULL){
        lst_aluno->prox = NULL;
    }
    return lst_aluno;
}

Dado_aluno lerDadosAluno(){
    Dado_aluno aluno;
    printf("Digite a matricula do aluno: ");
    scanf("%d", &aluno.matricula);
    printf("Digite o nome do aluno: ");
    scanf("%s", aluno.nome);
    printf("Digite o codigo do curso do aluno: ");
    scanf("%d", &aluno.codigo_curso);
    aluno.matriculas = NULL; //arvore de matriculas
    aluno.notas = NULL; //arvore de notas
    return aluno;
}


int inserir_aluno(Lista_alunos *lst_aluno, Dado_aluno aluno, Arvore_curso *raiz){
    int inseriu = 0;

    if(verifica_codigo_curso(raiz, aluno.codigo_curso) != 0){
        Lista_alunos *novo;
        novo = (Lista_alunos*) malloc(sizeof(Lista_alunos));
        if(novo != NULL){
            novo->aluno = aluno;
            if(lst_aluno == NULL){ // insere no inicio
                novo->prox = NULL;
                inseriu = 1;
            }else{
                Lista_alunos *anterior, *atual = lst_aluno;
                // procurar a posição de inserção de acordo com o nome do aluno
                while(atual != NULL && strcmp(atual->aluno.nome, aluno.nome) < 0){
                    anterior = atual;
                    atual = atual->prox;
                    inseriu = 1;
                }
                if(atual == lst_aluno){
                    novo->prox = lst_aluno;
                    lst_aluno = novo;
                    inseriu = 1;
                }else{
                    novo->prox = atual;
                    anterior->prox = novo;
                    inseriu = 1;
                }
            }
        }
    }
    return inseriu;
}

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


int inserir_arvore_nota(Arvore_notas **raiz_notas, Dado_nota nota){
    int inseriu = 0;
    if(*raiz_notas == NULL){
        *raiz_notas = aloca_no_nota(nota);
        inseriu = 1;
    }else if(nota.codigo_disciplina < (*raiz_notas)->nota.codigo_disciplina){
        inseriu = inserir_nota(&((*raiz_notas)->esq), nota);
    }else{
        inseriu = inserir_nota(&((*raiz_notas)->dir), nota);
    }
    return inseriu;
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

void imprime_dado_curso(Dado_curso curso){
    printf("Codigo do curso: %d | \n Nome do curso: %s |\n Carga Horária %d |\n Quantidade de Periodos %d |\n",curso.codigo_curso, curso.nome_curso, curso.carga_horaria, curso.quantidade_periodos);
   if(curso.disciplinas != NULL){
        printf("Disciplinas do curso\n");
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
void imprime_dado_aluno(Dado_aluno aluno){
    printf("Matricula: %d\n", aluno.matricula);
    printf("Nome: %s\n", aluno.nome);
    printf("Codigo do curso: %d\n", aluno.codigo_curso);
}

void imprimir_lista_alunos(Lista_alunos *lst_aluno){
    Lista_alunos *aux;
    aux = lst_aluno->prox;
    while(aux != NULL){
        imprime_dado_aluno(aux->aluno);
        aux = aux->prox;
    }
}