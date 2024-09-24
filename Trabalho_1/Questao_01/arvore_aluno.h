
// Estrutura para guardar os dados da disciplina
// ++++++++++++++++++++++++inicio da estrutura disciplina +++++++++++++++++++++
typedef struct dado_disciplina{ 
    int codigo_disciplina;
    char nome_disciplina[50];
    int carga_horaria;
    int numero_periodo;
}Dado_disciplina;

typedef struct arvore_disciplina {
    struct dado_disciplina disciplina;
    struct arvore_disciplina *esq;
    struct arvore_disciplina *dir;
}Arvore_disciplina; 
//++++++++++++++++++++++++fim da estrutura disciplina ++++++++++++++++++++++++

// Estrutura para guardar os dados do curso
// ++++++++++++++++++++++++inicio da estrutura curso +++++++++++++++++++++
typedef struct dado_curso{ 
    int codigo_curso;
    char nome_curso[50];
    int carga_horaria;
    int quantidade_periodos;
    struct arvore_disciplina *disciplinas;
}Dado_curso;

typedef struct arvore_curso {
    struct dado_curso curso;
    struct arvore_curso *esq;
    struct arvore_curso *dir;
}Arvore_curso; 
// /++++++++++++++++++++++++fim da estrutura curso ++++++++++++++++++++++++


//++++++++++++++++++++++++Inicio da estrutura matricula ++++++++++++++++++++++++
typedef struct arvore_matricula{
    int codigo_disciplina;
    struct arvore_matricula *esq;
    struct arvore_matricula *dir;
}Arvore_matricula;
//++++++++++++++++++++++++fim da estrutura matricula ++++++++++++++++++++++++

//Estrutura para guardar os dados da nota de cada aluno
//++++++++++++++++++++++++Inicio da estrutura nota ++++++++++++++++++++++++
typedef struct dado_nota {
    int codigo_disciplina;
    float nota_final;
    int semestre_cursado; 
}Dado_nota;

typedef struct arvore_notas {

    struct dado_nota nota;
    struct arvore_notas *esq;
    struct arvore_notas *dir;

}Arvore_notas;
//++++++++++++++++++++++++Fim  da estrutura nota ++++++++++++++++++++++++

//++++++++++++++++++++++++Inicio da estrutura aluno ++++++++++++++++++++++++
//estrura para guardar os dados do aluno
typedef struct dado_aluno {
    int matricula;
    char nome[50];
    int codigo_curso;
    struct arvore_notas *notas;
    struct arvore_matricula *matriculas;
}Dado_aluno;

// lista  de alunos
typedef struct lista_aluno  {
    
    struct dado_aluno aluno;
    struct lista_aluno *prox;

}Lista_alunos;
//++++++++++++++++++++++++Fim  da estrutura aluno ++++++++++++++++++++++++

// PROTÓTIPOS DAS FUNÇÕES DO PROGRAMA

// Funções para manipular a lista de alunos
Lista_alunos *cria_lista_alunos();
Dado_aluno lerDadosAluno();
int inserir_aluno(Lista_alunos *lista, Dado_aluno aluno, Arvore_curso *raiz_curso);
void mostrar_aluno_de_curso(Lista_alunos *lista, int codigo_curso);
void imprime_dado_aluno(Dado_aluno aluno);
void imprimir_lista_alunos(Lista_alunos *lista);

// Funções para manipular a árvore cursos
Arvore_curso *cria_arvore_curso();
Dado_curso lerDadosCurso();
int inserir_curso(Arvore_curso **raiz_curso, Dado_curso curso);
Arvore_curso *buscar_curso(Arvore_curso *raiz_curso, int codigo_curso);
void imprime_arvore_cursos(Arvore_curso *raiz);
// Funções para manipular a árvore disciplinas
Arvore_disciplina *cria_arvore_disciplina();
Dado_disciplina lerDadosDisciplina();
Arvore_disciplina *inserir_disciplina(Arvore_disciplina **raiz_disciplina, Dado_disciplina disciplina);
int remover_disciplina(Arvore_disciplina *raiz_disciplina, int codigo_disciplina);
Arvore_disciplina *buscar_disciplina(Arvore_disciplina *raiz_disciplina, int codigo_disciplina);
void mostrar_disciplinas_de_curso(Arvore_disciplina *raiz_disciplina, int codigo_curso);
void mostrar_disciplinas_de_periodo_curso(Arvore_disciplina *raiz_disciplina, int numero_periodo, int codigo_curso);
void mostrar_disciplina_de_aluno_matriculado(Arvore_disciplina *raiz_disciplina, Arvore_matricula *raiz_matricula, int matricula);
int adicionar_disciplina_curso(Arvore_curso *raiz, Dado_disciplina disciplina, int codigo_curso);
void imprimir_arvore_disciplinas(Arvore_disciplina *raiz);

Arvore_matricula *cria_arvore_matricula();
Arvore_matricula *aloca_no_matricula(int codigo_disciplina);
int inserir_arvore_matricula(Arvore_matricula **raiz_matricula, int codigo_disciplina);
int remover_arvore_matricula(Arvore_matricula **raiz_matricula, int codigo_disciplina);

Arvore_notas *cria_arvore_notas();
Dado_nota lerDadosNota();
Arvore_notas *aloca_no_nota(Dado_nota nota);
int inserir_arvore_nota(Arvore_notas **raiz_notas, Dado_nota nota);
Arvore_notas *buscar_nota(Arvore_notas *raiz_notas, int codigo_disciplina);