#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "prototipos.h"
/* 
#include "lista_alunos.c"
#include "arvore_curso.c"
#include "arvore_disciplinas.c"
#include "arvore_matricula.c"
#include "arvore_notas.c"
 */







int main(){
    int opcao, status;
    //criar menu de opções para o usuário
    Lista_alunos *lst_aluno;
    Arvore_curso *arvore_curso;
    Arvore_matricula *arvore_matricula;

    arvore_curso = NULL;
    arvore_matricula = NULL;
    lst_aluno = NULL;


    int codigo_matricula;
    do{
        printf("\n\nEscolha uma opcao\n"
            "1 - Inserir curso\n"
            "2 - Inserir alunos\n"
            "3 - Inserir Disciplina em curso\n"
            "4 - Inserir matricula aluno\n"
            "5 - Listar alunos\n"
            "6 - Inserir notas\n"
            "7 - Inserir matricula em disciplina\n"
            "8 - Mostrar todos os alunos de um determinado curso\n"
            "9 - Mostrar todos os cursos do Campus\n"
            "10 - Mostrar todas as disciplinas de um determinado curso\n"
            "11 - Mostrar todas as disciplinas de um determinado período de um curso.\n"
            "12 - Mostrar todas as disciplinas que um determinado aluno está matriculado\n"
            "13 - Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno.\n"
            "14 -Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horária da disciplina \n"
            "15 - Remover uma disciplina de um determinado curso desde que não tenha nenhum aluno matriculado na mesma. "
            "16 - Remover uma disciplina da árvore de matrícula de um determinado aluno."
            "17 - Mostrar o histórico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva \nnota organizadas pelo período que a disciplina está cadastrada no curso.\n"
        );

        scanf("%d", &opcao);
        switch(opcao){
            case 1: // cadastrar curso
                Dado_curso curso;
                curso = lerDadosCurso();
                status = inserir_curso(&arvore_curso, curso);
                if(status == 1){
                    printf("curso inserido com sucesso\n");
                }else{
                    printf("Erro ao inserir curso\n");
                }
                break;
            case 2: // cadastrar aluno
                Dado_aluno aluno;
                aluno = lerDadosAluno();
                status = inserir_aluno(&lst_aluno, aluno, arvore_curso);
                if(status == 1){
                    printf("Aluno inserido com sucesso\n");
                }else{
                    printf("Erro ao inserir aluno,\n verifque se existe curso cadastrado com esse código\n");
                }
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
            case 4:
                // inserir matrciula
                printf("Digite o codigo da matricula: ");
                scanf("%d", &codigo_matricula);
                status = inserir_arvore_matricula(&arvore_matricula, codigo_matricula);
                if(status == 1){
                    printf("Matricula inserida com sucesso\n");
                }else{
                    printf("Erro ao inserir matricula\n");
                }
            case 5:
                imprimir_lista_alunos(lst_aluno);
                break;
            default:
                printf("Opcao invalida\n");
        }
    }while(opcao != 0);

    imprime_arvore_cursos(arvore_curso);
    


    return 0;
}