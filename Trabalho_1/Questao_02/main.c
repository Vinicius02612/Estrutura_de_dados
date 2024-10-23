#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include <time.h>

#include "../Questao_01/prototipos.h"


void insercao_arvore_curso(){
    printf("Insercao de curso\n");
    int status;
    clock_t t_inicio, t_fim;
    double tempo_gasto, tempo_total = 0.0, tempo_total_inverso = 0.0;
    Arvore_curso *arvore_curso;
    arvore_curso = cria_arvore_curso();

    srand(time(NULL));


    int codigos[10];

    for (int i = 0; i < 10; i++) {
        codigos[i] = rand() % 55; 
    }
    // inserir 10 cursos de forma crescente
   
    for(int i = 0; i < 10; i++){
        
        Dado_curso curso;
        curso.codigo_curso = codigos[i];
        sprintf(curso.nome_curso, "Curso %d", i);
        curso.carga_horaria = i*1000;
        curso.quantidade_periodos = i*2;
        
        t_inicio = clock();
        status = inserir_curso(&arvore_curso, curso);
        t_fim = clock();
        tempo_gasto = ((double)t_fim - t_inicio) / CLOCKS_PER_SEC * 1000000;

        printf("Tempo gasto para inserir o curso %d: %f\n", curso.codigo_curso, tempo_gasto);

        tempo_total += tempo_gasto;
    }
    printf("Tempo total gasto para inserir 10 cursos: %f\n\n\n", tempo_total);
   

     //inverter ordem de insercao do curso
    for(int i = 10; i > 0; i--){
        
        Dado_curso curso;
        curso.codigo_curso = codigos[i];
        sprintf(curso.nome_curso, "Curso %d", i);
        curso.carga_horaria = i*1000;
        curso.quantidade_periodos = i*2;
        t_inicio = clock();
        status = inserir_curso(&arvore_curso, curso);
        t_fim = clock();
        // calcular tempo em milisegundos
        tempo_gasto = ((double)t_fim - t_inicio) / CLOCKS_PER_SEC *1000000;

        printf("Tempo gasto para inserir o curso %d: %f\n", curso.codigo_curso, tempo_gasto);
       
        tempo_total_inverso += tempo_gasto;
        
    } 

    printf("Tempo total gasto para inserir 10 cursos de forma inversa: %f\n", tempo_total_inverso);

}


int main(){
    
    insercao_arvore_curso();

    return 0;
}