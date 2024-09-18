#include <stdio.h>
#include <stdlib.h>
#include "arvore_aluno.h"

void test_insertions() {
    // Create a new tree
    Lista_alunos* lst_alunos;
    lst_alunos = cria_lista_alunos();

    Arvore_curso* arvore_curso;
    arvore_curso = cria_arvore_curso();

    Dado_curso curso;
    int codigo_curso = 100;
    curso.codigo_curso = codigo_curso;
    sprintf(curso.nome_curso, "Curso %d", codigo_curso);
    curso.quantidade_periodos = 10;
    curso.carga_horaria = 1000;
    curso.disciplinas = NULL;

    // Insert a course
    int status = inserir_curso(&arvore_curso, curso);

   // inserir 10 alunos na lista de alunos
   for(int i = 0; i < 10; i++){
        Dado_aluno aluno;
        aluno.matricula = i*1234;
        sprintf(aluno.nome, "Aluno %d", i);
        aluno.codigo_curso = codigo_curso;
        aluno.matriculas = NULL;
        aluno.notas = NULL;
        status = inserir_aluno(lst_alunos, aluno, arvore_curso);
        if(status == 1){
            printf("Aluno %d inserido com sucesso  com matricula %d\n", i, aluno.matricula);
        }else{
            printf("Erro ao inserir aluno,\n verifque se existe curso cadastrado com esse código\n");
        }
    }

    // inserir 10 disciplinas no curso
    for(int i = 0; i < 10; i++){
        Dado_disciplina disciplina;
        disciplina.codigo_disciplina = i*1234;
        sprintf(disciplina.nome_disciplina, "Disciplina %d", i);
        disciplina.carga_horaria = 100;
        disciplina.codigo_disciplina = i;
        status = adicionar_disciplina_curso(arvore_curso, disciplina, codigo_curso);
        if(status == 1){
            printf("Disciplina %d inserida com sucesso  com codigo %d\n", i, disciplina.codigo_disciplina);
        }else{
            printf("Erro ao inserir disciplina,\n verifque se existe curso cadastrado com esse código\n");
        }
    }

    
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