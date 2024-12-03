#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include <time.h>

#include "../Questao_03/prototipos.h"


void insercao_arvore_curso(){
    printf("Insercao de curso\n");
    int status;
    clock_t t_inicio, t_fim;
    double tempo_gasto, tempo_total = 0.0, tempo_total_inverso = 0.0;
    Arvore_curso *arvore_curso;
    arvore_curso = cria_arvore_curso();

    srand(time(NULL));


    int codigos[30];

    for (int i = 0; i < 30; i++) {
        codigos[i] =  rand() % 100; 
    }
    // inserir 10 cursos de forma crescente
   
    for(int i = 0; i < 30; i++){
        
        Dado_curso curso;
        curso.codigo_curso = codigos[i];
        sprintf(curso.nome_curso, "Curso %d", i);
        curso.carga_horaria = i*1000;
        curso.quantidade_periodos = i*2;
        
        t_inicio = clock();
        status = inserir_curso(&arvore_curso, curso);
        t_fim = clock();
        tempo_gasto = ((double)t_fim - t_inicio) / CLOCKS_PER_SEC * 1000;



        tempo_total += tempo_gasto;
    }
    printf("Tempo total gasto para inserir 10 cursos: %f\n\n\n", tempo_total);
   

     //inverter ordem de insercao do curso
    for(int i = 30; i >= 0; i--){
        
        Dado_curso curso;
        curso.codigo_curso = codigos[i];
        sprintf(curso.nome_curso, "Curso %d", i);
        curso.carga_horaria = i*1000;
        curso.quantidade_periodos = i*2;
        t_inicio = clock();
        status = inserir_curso(&arvore_curso, curso);
        t_fim = clock();
        // calcular tempo em milisegundos
        tempo_gasto = ((double)t_fim - t_inicio) / CLOCKS_PER_SEC * 1000;


       
        tempo_total_inverso += tempo_gasto;
        
    } 

    printf("Tempo total gasto para inserir 10 cursos de forma inversa: %f\n", tempo_total_inverso);

}


void buscar_nota_aluno_disciplina(){
    printf("Busca de nota de aluno\n");
    Arvore_curso *arvore_curso;
    Dado_curso curso;
    Lista_alunos *lst_aluno;

    arvore_curso = cria_arvore_curso();
    lst_aluno = cria_lista_alunos();



    int status;
    clock_t t_inicio, t_fim;
    double tempo_gasto, tempo_total = 0.0, tempo_total_inverso = 0.0;



    strcpy(curso.nome_curso, "Sistemas");
    curso.carga_horaria =3200;
    curso.codigo_curso = 123;
    curso.quantidade_periodos = 8;

    status = inserir_curso(&arvore_curso, curso);
    if(status == 1){
        // inserir 10 disciplinas
        for(int i = 0; i < 10; i++){
            Dado_disciplina disciplina;
            disciplina.codigo_disciplina = i;
            sprintf(disciplina.nome_disciplina, "Disciplina %d", i);
            disciplina.carga_horaria = i*10;
            disciplina.numero_periodo = i;
            status = adicionar_disciplina_curso(arvore_curso, disciplina, curso.codigo_curso);
            if(status == 1){
                printf("Disciplina %d inserida com sucesso\n", disciplina.codigo_disciplina);
            }else{
                printf("Erro ao inserir disciplina %d carga hrs %d\n", disciplina.codigo_disciplina, disciplina.carga_horaria);
            }
        }

        // inserir 10 alunos
        for(int i = 0; i < 10; i++){
            Dado_aluno aluno;
            aluno.matricula = i;
            sprintf(aluno.nome, "Aluno %d", i);
            aluno.codigo_curso = curso.codigo_curso;
            status = inserir_aluno(&lst_aluno, aluno, arvore_curso);
            if(status == 1){
                printf("Aluno %d inserido com sucesso\n", aluno.matricula);
            }
        }

        // inserir 10 notas
        for(int i = 0; i < 10; i++){
            Dado_nota nota;
            nota.codigo_disciplina = i;
            nota.nota_final = i*10;
            nota.semestre_cursado = i;
            status = inserir_nota_aluno(lst_aluno, i, nota);
            if(status == 1){
                printf("Nota %d inserida com sucesso\n", nota.codigo_disciplina);
            }
        }
    }
    
}
    

int main(){
    
    insercao_arvore_curso();
    //buscar_nota_aluno_disciplina();

    return 0;
}