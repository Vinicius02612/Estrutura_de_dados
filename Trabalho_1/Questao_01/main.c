#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "arvore_aluno.h"


int main(){
    int opcao, status;
    //criar menu de opções para o usuário
    Lista_alunos *lst_aluno;
    Arvore_disciplina *arvore_disciplina;
    Arvore_curso *arvore_curso;

    arvore_curso = cria_arvore_curso();
    arvore_disciplina = cria_arvore_disciplina();
    lst_aluno = cria_lista_alunos();

    do{
        printf("1 - Inserir curso\n");
        printf("2 - Inserir alunos\n");
        printf("3 - Inserir Disciplina em curso\n");
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
                Dado_disciplina disciplina;
                disciplina = lerDadosDisciplina();
                printf("Curso disponiveis\n");
                imprime_arvore_cursos(arvore_curso);
                int codigo_curso;
                printf("Digite o codigo do curso: ");
                scanf("%d", &codigo_curso);
                status = adicionar_disciplina_curso(arvore_curso, disciplina, codigo_curso);
                if(status == 1){
                    printf("Disciplina inserida com sucesso\n");
                }else{
                    printf("Erro ao inserir disciplina,\n verifque se existe curso cadastrado com esse código\n");
                }
                break;
            default:
                printf("Opcao invalida\n");
        }
    }while(opcao != 0);

    imprime_arvore_cursos(arvore_curso);
    imprimir_lista_alunos(lst_aluno);


    return 0;
}