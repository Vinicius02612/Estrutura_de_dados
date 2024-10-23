#include <stdio.h>
#include <stdlib.h>
#include "prototipos.h"

void test_insertions() {
    
    Lista_alunos* lst_alunos;
    lst_alunos = NULL;

    Arvore_curso* arvore_curso;
    arvore_curso = cria_arvore_curso();

    Dado_curso curso;
    int codigo_curso = 100, status, status_teste, tam = 10;

    curso.codigo_curso = codigo_curso;
    sprintf(curso.nome_curso, "Curso %d", codigo_curso);

    curso.quantidade_periodos = 10;
    curso.carga_horaria = 1000;
    curso.disciplinas = cria_arvore_disciplina();


    status = inserir_curso(&arvore_curso, curso);
    
    if(status == 1){
        for(int i = 0; i < tam; i++){
            Dado_aluno aluno;
            aluno.matricula = i*1234;
            sprintf(aluno.nome, "Aluno %d", i);
            aluno.codigo_curso = codigo_curso;
            status_teste = inserir_aluno(&lst_alunos, aluno, arvore_curso);
        }

        // inserir 10 disciplinas no curso
        for(int i = 0; i < tam; i++){
            Dado_disciplina disciplina;
            disciplina.codigo_disciplina = i*1234;
            sprintf(disciplina.nome_disciplina, "Disciplina %d", i);
            disciplina.carga_horaria = i* 10;
            disciplina.codigo_disciplina = i;
            disciplina.numero_periodo = i;
            status_teste = adicionar_disciplina_curso(arvore_curso, disciplina, codigo_curso);
        }

        // inserir notas para os alunos
        for(int i = 0; i < tam; i++){
            Dado_nota nota;
            nota.codigo_disciplina = i*1234;
            nota.nota_final = 10;
            nota.semestre_cursado = i;
            status_teste = inserir_nota_aluno(lst_alunos,2468, nota);
        }
       /*  status = remover_disciplina_curso(arvore_curso, 3, codigo_curso);
        if(status == 1){
            printf("Disciplina removida com sucesso\n");
        }else{
            printf("Erro ao remover disciplina\n");
        } */

      /*   imprimir_lista_alunos(lst_alunos);
        imprime_arvore_notas(lst_alunos->aluno.notas);
 */
        
    }
    //imprimir_arvore_disciplina(arvore_curso->curso.disciplinas);

    //Mostrar todas as disciplinas de um determinado período de um curso.
   // mostrar_disciplinas_de_periodo_curso(arvore_curso,3,codigo_curso);

    //Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horária da disciplina.
    //mostrar_nota_disciplina_aluno(arvore_curso,lst_alunos,1234,1234);

    mostrar_historico_aluno(arvore_curso, lst_alunos,2468);
    




    // inserir 10 alunos na lista de alunos
   
}

void test_buscar_aluno() {
    printf("Testando a função buscar_aluno\n");
}

int main() {
    // Run the tests
    test_insertions();
    test_buscar_aluno();

    return 0;
}