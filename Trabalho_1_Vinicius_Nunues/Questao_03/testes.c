#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include <time.h>

#include "prototipos.h"


void insercao_arvore_curso(){
    printf("Insercao de curso\n");
    Arvore_curso *arvore_curso;
    arvore_curso = cria_arvore_curso();
    //inseir 10 cursos de forma crescente
    for(int i = 0; i < 10; i++){
        Dado_curso curso;
        curso.codigo_curso = i;
        
        sprintf(curso.nome_curso, "Curso %d", i);
        curso.carga_horaria = i*1000;
        curso.quantidade_periodos = i*2;

        int status = inserir_curso(&arvore_curso, curso);
        if(status == 1){
            printf("Curso inserido com sucesso\n");
        }
    }

    imprime_arvore_cursos(arvore_curso);

}


void buscar_nota_aluno_disciplina(){
   
    
}
    

int main(){
    
    insercao_arvore_curso();
    //buscar_nota_aluno_disciplina();

    return 0;
}
