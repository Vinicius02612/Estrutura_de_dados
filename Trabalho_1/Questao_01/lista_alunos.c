#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "prototipos.h"


Lista_alunos *cria_lista_alunos(){
    Lista_alunos *lst_aluno;
    lst_aluno = (Lista_alunos*) malloc(sizeof(Lista_alunos));
    if(lst_aluno != NULL){
        lst_aluno = NULL;
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

// lista encadeada de alunos
int inserir_aluno(Lista_alunos **lst_aluno, Dado_aluno aluno, Arvore_curso *raiz){
    int inseriu;

    if(verifica_codigo_curso(raiz, aluno.codigo_curso) != 0){ // se exite um curso cadastrado!
        Lista_alunos *novo;
        novo = (Lista_alunos*) malloc(sizeof(Lista_alunos));
        if(novo != NULL){
            novo->aluno = aluno;
            if(*lst_aluno == NULL){ // insere no inicio
                novo->prox = NULL;
                *lst_aluno = novo; 
                inseriu = 1;
            }else{
                Lista_alunos *anterior, *atual;
                atual = *lst_aluno;
                anterior = NULL;
                // procurar a posição de inserção de acordo com o nome do aluno
                while(atual != NULL && strcmp(atual->aluno.nome, aluno.nome) < 0){
                    anterior = atual;
                    atual = atual->prox;
                }
                if(atual == *lst_aluno){
                    novo->prox = *lst_aluno;
                    *lst_aluno = novo;
                    inseriu = 1;
                }else{
                    novo->prox = atual;
                    anterior->prox = novo;
                    inseriu = 1;
                }
            }
        }
    }else{
        inseriu = 0;
    }
    return inseriu;
}


void imprime_dado_aluno(Dado_aluno aluno){
    printf("Matricula: %d\n", aluno.matricula);
    printf("Nome: %s\n", aluno.nome);
    printf("Codigo do curso: %d\n", aluno.codigo_curso);
}

void imprimir_lista_alunos(Lista_alunos *lst_aluno){
    Lista_alunos *aux;
    aux = lst_aluno;
    while(aux != NULL){
        imprime_dado_aluno(aux->aluno);
        if(aux->aluno.matriculas != NULL && aux->aluno.notas != NULL){
            imprime_avore_matricula(aux->aluno.matriculas);
            imprime_arvore_notas(aux->aluno.notas);
        }
        aux = aux->prox;
    }
}

void libera_aluno( Lista_alunos *lst_aluno){
    Lista_alunos *aux;
    aux = lst_aluno;
    while (aux != NULL)
    {
        Lista_alunos *temp = aux;
        aux = aux->prox;
        free(temp);
    }
    
}