#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "arvore_aluno.h"


int main(){
    int opcao, status;
    //criar menu de opções para o usuário
    Lista_alunos *lst_aluno;
    Arvore_curso *arvore_curso;
    arvore_curso = cria_arvore_curso();
    lst_aluno = cria_lista_alunos();

    do{
        printf("1 - Inserir curso\n");
        printf("2 - Inserir alunos\n");
        printf("3 - Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                Dado_curso curso;
                curso = lerDadosCurso();
                status = inserir_curso(&arvore_curso, curso);
                if(status == 1){
                    printf("curso inserido com sucesso\n");
                }else{
                    printf("Erro ao inserir curso\n");
                }
                break;
            case 2:
                Dado_aluno aluno;
                aluno = lerDadosAluno();
                status = inserir_aluno(lst_aluno, aluno, arvore_curso);
                if(status == 1){
                    printf("Aluno inserido com sucesso\n");
                }else{
                    printf("Erro ao inserir aluno,\n verifque se existe curso cadastrado com esse código\n");
                }
                break;
                imprimir_lista_alunos(lst_aluno);
                break;
            case 3:
                //sair
                break;
            default:
                printf("Opcao invalida\n");
        }
    }while(opcao != 0);
}