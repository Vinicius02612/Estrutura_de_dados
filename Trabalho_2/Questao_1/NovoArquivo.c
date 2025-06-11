#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------------- Definições Gerais ----------------------------
typedef enum { VERMELHO, PRETO } Cor;

// -------------------------- Estrutura de CEP -----------------------------
typedef struct NoCEP
{
	int cep;
	Cor cor;
	struct NoCEP *esq, *dir, *pai;
} NoCEP;

// -------------------------- Estrutura de Cidade --------------------------
typedef struct NoCidade
{
	char nome[100];
	int populacao;
	NoCEP *ceps;
	Cor cor;
	struct NoCidade *esq, *dir, *pai;
} NoCidade;

// -------------------------- Estrutura de Estado --------------------------
typedef struct Estado
{
	char nome[100];
	char capital[100];
	int qtdCidades;
	int populacao;
	NoCidade *cidades;
	struct Estado *ant, *prox;
} Estado;

// -------------------------- Lista de Estados -----------------------------
typedef struct
{
	Estado *inicio;
} ListaEstados;

// -------------------------- Estrutura de Pessoa --------------------------
typedef struct NoPessoa
{
	char cpf[15];
	char nome[100];
	int cep_natal;
	int cep_moradia;
	int dia, mes, ano;
	Cor cor;
	struct NoPessoa *esq, *dir, *pai;
} NoPessoa;

// -------------------------- Variáveis Globais ----------------------------
ListaEstados listaEstados = {NULL};
NoPessoa *pessoas = NULL;

// -------------------------- Protótipos (parte 1) -------------------------
Estado *criarEstado(const char *nome, const char *capital, int populacao);
void inserirEstadoOrdenado(ListaEstados *lista, Estado *novoEstado);
void imprimirEstados(ListaEstados *lista);

NoCidade *inserirCidadeRB(NoCidade *raiz, NoCidade *novaCidade);
NoCidade *criarCidade(const char *nome, int populacao);
void inserirCidadeEmEstado(Estado *estado, const char *nomeCidade, int populacao);

NoCEP *inserirCEPRB(NoCEP *raiz, NoCEP *novoCEP);
NoCEP *criarCEP(int cep);
void inserirCEPEmCidade(Estado *estado, const char *nomeCidade, int cep);

NoPessoa *criarPessoa(const char *cpf, const char *nome, int cep_natal, int cep_moradia, int d, int m, int a);
NoPessoa *inserirPessoaRB(NoPessoa *raiz, NoPessoa *novaPessoa);
int validarData(int d, int m, int a);
int existeCEP(int cep);
void cadastrarPessoa(const char *cpf, const char *nome, int cep_natal, int cep_moradia, int d, int m, int a);

// -------------------------- Função Principal -----------------------------
int main()
{
	int opcao, cep, popCidade, cep_natal, cep_moradia, d, m, a;
	char nome[100], capital[100], nomeEstado[100], nomeCidade[100], cpf[15];
	int populacao;
	Estado *est;
	do
	{
		printf("\n======= MENU =======\n");
		printf("1. Cadastrar Estado\n");
		printf("2. Cadastrar Cidade\n");
		printf("3. Cadastrar CEP\n");
		printf("4. Cadastrar Pessoa\n");
		printf("5. Imprimir Estados\n");
		printf("6. Remover CEP\n");
		printf("7. Remover Pessoa\n");
		printf("8. Estado mais populoso\n");
		printf("9. População da capital de um estado\n");
		printf("10. Cidade mais populosa sem ser capital\n");
		printf("11. Pessoas que não moram na cidade natal\n");
		printf("12. Nome da cidade natal a partir de um CEP\n");
		printf("13. Pessoas nascidas em uma cidade que não moram nela\n");
		printf("14. Pessoas que moram em uma cidade que não nasceram nela\n");
		printf("0. Sair\n");
		printf("Escolha: ");
		scanf("%d", &opcao);
		getchar(); // Limpar o buffer do teclado

		switch(opcao)
		{
		case 1:
			printf("Nome do Estado: ");
			fgets(nome, sizeof(nome), stdin);
			nome[strcspn(nome, "\n")] = 0;
			printf("Nome da Capital: ");
			fgets(capital, sizeof(capital), stdin);
			capital[strcspn(capital, "\n")] = 0;
			printf("População: ");
			scanf("%d", &populacao);
			Estado *novo = criarEstado(nome, capital, populacao);
			inserirEstadoOrdenado(&listaEstados, novo);
			break;

		case 2:
			printf("Nome do Estado: ");
			fgets(nomeEstado, sizeof(nomeEstado), stdin);
			nomeEstado[strcspn(nomeEstado, "\n")] = 0;
			printf("Nome da Cidade: ");
			fgets(nomeCidade, sizeof(nomeCidade), stdin);
			nomeCidade[strcspn(nomeCidade, "\n")] = 0;
			printf("População da Cidade: ");
			scanf("%d", &popCidade);
			Estado *est = listaEstados.inicio;
			while (est && strcmp(est->nome, nomeEstado) != 0)
				est = est->prox;
			if (est) inserirCidadeEmEstado(est, nomeCidade, popCidade);
			else printf("Estado nao encontrado.\n");
			break;

		case 3:
			printf("Estado: ");
			fgets(nomeEstado, sizeof(nomeEstado), stdin);
			nomeEstado[strcspn(nomeEstado, "\n")] = 0;
			printf("Cidade: ");
			fgets(nomeCidade, sizeof(nomeCidade), stdin);
			nomeCidade[strcspn(nomeCidade, "\n")] = 0;
			printf("CEP: ");
			scanf("%d", &cep);
			est = listaEstados.inicio;
			while (est && strcmp(est->nome, nomeEstado) != 0)
				est = est->prox;
			if (est) inserirCEPEmCidade(est, nomeCidade, cep);
			else printf("Estado nao encontrado.\n");
			break;
		case 4:

			printf("CPF: ");
			fgets(cpf, sizeof(cpf), stdin);
			cpf[strcspn(cpf, "\n")] = 0;
			printf("Nome: ");
			fgets(nome, sizeof(nome), stdin);
			nome[strcspn(nome, "\n")] = 0;
			printf("CEP Natal: ");
			scanf("%d", &cep_natal);
			printf("CEP Moradia: ");
			scanf("%d", &cep_moradia);
			printf("Data Nascimento (DD MM AAAA): ");
			scanf("%d %d %d", &d, &m, &a);
			cadastrarPessoa(cpf, nome, cep_natal, cep_moradia, d, m, a);
			break;
		case 5:

			imprimirEstados(&listaEstados);
			break;
		case 6:
			printf("Nome do Estado: ");
			fgets(nomeEstado, sizeof(nomeEstado), stdin);
			nomeEstado[strcspn(nomeEstado, "\n")] = 0;
			printf("Nome da Cidade: ");
			fgets(nomeCidade, sizeof(nomeCidade), stdin);
			nomeCidade[strcspn(nomeCidade, "\n")] = 0;
			printf("CEP a remover: ");
			scanf("%d", &cep);
			est = listaEstados.inicio;
			while (est && strcmp(est->nome, nomeEstado) != 0) est = est->prox;
			if (est)
			{
				if (removerCEP(est, nomeCidade, cep)) printf("CEP removido com sucesso.\n");
				else printf("Nao foi possivel remover o CEP.\n");
			}
			else printf("Estado nao encontrado.\n");
			break;
		case 7:
			printf("CPF da pessoa a remover: ");
			fgets(cpf, sizeof(cpf), stdin);
			cpf[strcspn(cpf, "\n")] = 0;
			removerPessoa(cpf);
			printf("Pessoa removida (se existia).\n");
			break;
		case 8:

			estadoMaisPopuloso();
			break;
		case 9:
			populacaoCapital();
			break;
		case 10:
			cidadeMaisPopulosaSemCapital();
			break;
		case 11:

			pessoasNaoMoramNaCidadeNatal();
			break;
		case 12:

			cidadePorCEPNatal();
			break;
		case 13:

			pessoasNascidasQueNaoMoram();

		case 14:
			pessoasQueMoramMasNaoNasceram();
			break;

		}
	}
	while (opcao != 0);

	return 0;
}
// ---------------------- Funções de Estados ----------------------------

Estado *criarEstado(const char *nome, const char *capital, int populacao)
{
	Estado *novo = (Estado *)malloc(sizeof(Estado));
	if (novo != NULL)
	{
		strcpy(novo->nome, nome);
		strcpy(novo->capital, capital);
		novo->populacao = populacao;
		novo->qtdCidades = 1;
		novo->cidades = NULL;
		novo->ant = NULL;
		novo->prox = NULL;
	}
	return novo;
}

void inserirEstadoOrdenado(ListaEstados *lista, Estado *novoEstado)
{
	Estado *atual = lista->inicio, *anterior = NULL;
	while (atual != NULL && strcmp(atual->nome, novoEstado->nome) < 0)
	{
		anterior = atual;
		atual = atual->prox;
	}

	if (anterior == NULL)
	{
		novoEstado->prox = lista->inicio;
		if (lista->inicio) lista->inicio->ant = novoEstado;
		lista->inicio = novoEstado;
	}
	else
	{
		novoEstado->prox = anterior->prox;
		novoEstado->ant = anterior;
		if (anterior->prox) anterior->prox->ant = novoEstado;
		anterior->prox = novoEstado;
	}
}

void imprimirEstados(ListaEstados *lista)
{
	Estado *p = lista->inicio;
	while (p != NULL)
	{
		printf("\nEstado: %s\nCapital: %s\nPopulação: %d\nCidades: %d\n",
			   p->nome, p->capital, p->populacao, p->qtdCidades);
		p = p->prox;
	}
}
// ---------------------- Funções Auxiliares RB Cidade ------------------------

void rotacaoEsquerdaCidade(NoCidade **raiz, NoCidade *x)
{
	NoCidade *y = x->dir;
	x->dir = y->esq;
	if (y->esq) y->esq->pai = x;
	y->pai = x->pai;
	if (!x->pai) *raiz = y;
	else if (x == x->pai->esq) x->pai->esq = y;
	else x->pai->dir = y;
	y->esq = x;
	x->pai = y;
}

void rotacaoDireitaCidade(NoCidade **raiz, NoCidade *x)
{
	NoCidade *y = x->esq;
	x->esq = y->dir;
	if (y->dir) y->dir->pai = x;
	y->pai = x->pai;
	if (!x->pai) *raiz = y;
	else if (x == x->pai->dir) x->pai->dir = y;
	else x->pai->esq = y;
	y->dir = x;
	x->pai = y;
}

void balancearInsercaoCidade(NoCidade **raiz, NoCidade *z)
{
	while (z->pai && z->pai->cor == VERMELHO)
	{
		NoCidade *tio = NULL;
		if (z->pai == z->pai->pai->esq)
		{
			tio = z->pai->pai->dir;
			if (tio && tio->cor == VERMELHO)
			{
				z->pai->cor = PRETO;
				tio->cor = PRETO;
				z->pai->pai->cor = VERMELHO;
				z = z->pai->pai;
			}
			else
			{
				if (z == z->pai->dir)
				{
					z = z->pai;
					rotacaoEsquerdaCidade(raiz, z);
				}
				z->pai->cor = PRETO;
				z->pai->pai->cor = VERMELHO;
				rotacaoDireitaCidade(raiz, z->pai->pai);
			}
		}
		else
		{
			tio = z->pai->pai->esq;
			if (tio && tio->cor == VERMELHO)
			{
				z->pai->cor = PRETO;
				tio->cor = PRETO;
				z->pai->pai->cor = VERMELHO;
				z = z->pai->pai;
			}
			else
			{
				if (z == z->pai->esq)
				{
					z = z->pai;
					rotacaoDireitaCidade(raiz, z);
				}
				z->pai->cor = PRETO;
				z->pai->pai->cor = VERMELHO;
				rotacaoEsquerdaCidade(raiz, z->pai->pai);
			}
		}
	}
	(*raiz)->cor = PRETO;
}

// ---------------------- Inserção Cidade RB ------------------------

NoCidade *criarCidade(const char *nome, int populacao)
{
	NoCidade *nova = (NoCidade *)malloc(sizeof(NoCidade));
	if (nova)
	{
		strcpy(nova->nome, nome);
		nova->populacao = populacao;
		nova->ceps = NULL;
		nova->esq = nova->dir = nova->pai = NULL;
		nova->cor = VERMELHO;
	}
	return nova;
}

NoCidade *inserirCidadeRB(NoCidade *raiz, NoCidade *nova)
{
	NoCidade *y = NULL, *x = raiz;
	while (x != NULL)
	{
		y = x;
		if (strcmp(nova->nome, x->nome) < 0) x = x->esq;
		else x = x->dir;
	}

	nova->pai = y;
	if (!y) raiz = nova;
	else if (strcmp(nova->nome, y->nome) < 0) y->esq = nova;
	else y->dir = nova;

	balancearInsercaoCidade(&raiz, nova);
	return raiz;
}

// ---------------------- Inserção em Estado ------------------------

void inserirCidadeEmEstado(Estado *estado, const char *nomeCidade, int populacao)
{
	NoCidade *nova = criarCidade(nomeCidade, populacao);
	if (nova)
	{
		estado->cidades = inserirCidadeRB(estado->cidades, nova);
		estado->populacao += estado->cidades->populacao;
		estado->qtdCidades++;
	}
}
// ---------------------- Funções Auxiliares RB CEP ------------------------

void rotacaoEsquerdaCEP(NoCEP **raiz, NoCEP *x)
{
	NoCEP *y = x->dir;
	x->dir = y->esq;
	if (y->esq) y->esq->pai = x;
	y->pai = x->pai;
	if (!x->pai) *raiz = y;
	else if (x == x->pai->esq) x->pai->esq = y;
	else x->pai->dir = y;
	y->esq = x;
	x->pai = y;
}

void rotacaoDireitaCEP(NoCEP **raiz, NoCEP *x)
{
	NoCEP *y = x->esq;
	x->esq = y->dir;
	if (y->dir) y->dir->pai = x;
	y->pai = x->pai;
	if (!x->pai) *raiz = y;
	else if (x == x->pai->dir) x->pai->dir = y;
	else x->pai->esq = y;
	y->dir = x;
	x->pai = y;
}

void balancearInsercaoCEP(NoCEP **raiz, NoCEP *z)
{
	while (z->pai && z->pai->cor == VERMELHO)
	{
		NoCEP *tio = NULL;
		if (z->pai == z->pai->pai->esq)
		{
			tio = z->pai->pai->dir;
			if (tio && tio->cor == VERMELHO)
			{
				z->pai->cor = PRETO;
				tio->cor = PRETO;
				z->pai->pai->cor = VERMELHO;
				z = z->pai->pai;
			}
			else
			{
				if (z == z->pai->dir)
				{
					z = z->pai;
					rotacaoEsquerdaCEP(raiz, z);
				}
				z->pai->cor = PRETO;
				z->pai->pai->cor = VERMELHO;
				rotacaoDireitaCEP(raiz, z->pai->pai);
			}
		}
		else
		{
			tio = z->pai->pai->esq;
			if (tio && tio->cor == VERMELHO)
			{
				z->pai->cor = PRETO;
				tio->cor = PRETO;
				z->pai->pai->cor = VERMELHO;
				z = z->pai->pai;
			}
			else
			{
				if (z == z->pai->esq)
				{
					z = z->pai;
					rotacaoDireitaCEP(raiz, z);
				}
				z->pai->cor = PRETO;
				z->pai->pai->cor = VERMELHO;
				rotacaoEsquerdaCEP(raiz, z->pai->pai);
			}
		}
	}
	(*raiz)->cor = PRETO;
}

// ---------------------- Inserção CEP RB ------------------------

NoCEP *criarCEP(int cep)
{
	NoCEP *novo = (NoCEP *)malloc(sizeof(NoCEP));
	if (novo)
	{
		novo->cep = cep;
		novo->esq = novo->dir = novo->pai = NULL;
		novo->cor = VERMELHO;
	}
	return novo;
}

NoCEP *inserirCEPRB(NoCEP *raiz, NoCEP *novo)
{
	NoCEP *y = NULL, *x = raiz;
	while (x != NULL)
	{
		y = x;
		if (novo->cep < x->cep) x = x->esq;
		else x = x->dir;
	}

	novo->pai = y;
	if (!y) raiz = novo;
	else if (novo->cep < y->cep) y->esq = novo;
	else y->dir = novo;

	balancearInsercaoCEP(&raiz, novo);
	return raiz;
}

// ---------------------- Inserção CEP em Cidade ------------------------

void inserirCEPEmCidade(Estado *estado, const char *nomeCidade, int cep)
{
	NoCidade *cidade = estado->cidades;
	while (cidade)
	{
		int cmp = strcmp(nomeCidade, cidade->nome);
		if (cmp == 0)
		{
			NoCEP *novo = criarCEP(cep);
			if (novo) cidade->ceps = inserirCEPRB(cidade->ceps, novo);
			cidade = NULL;
		}
		else if (cmp < 0) cidade = cidade->esq;
		else cidade = cidade->dir;
	}
}
// ---------------------- Validação de Data ------------------------

int validarData(int d, int m, int a)
{
	int valido = 0;
	if (a >= 1900 && a <= 2100)
	{
		if (m >= 1 && m <= 12)
		{
			int diasNoMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			if ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) diasNoMes[1] = 29;
			if (d >= 1 && d <= diasNoMes[m - 1]) valido = 1;
		}
	}
	return valido;
}

// ---------------------- Verificação de CEP ------------------------

int existeCEPNo(NoCEP *raiz, int cep)
{
	while (raiz)
	{
		if (cep == raiz->cep) return 1;
		else if (cep < raiz->cep) raiz = raiz->esq;
		else raiz = raiz->dir;
	}
	return 0;
}

int buscarCEPEmCidade(NoCidade *cidade, int cep)
{
	return cidade ? existeCEPNo(cidade->ceps, cep) : 0;
}

int buscarCEPEmEstado(Estado *estado, int cep)
{
	NoCidade *cidade = estado->cidades;
	while (cidade)
	{
		if (buscarCEPEmCidade(cidade, cep)) return 1;
		int dir = buscarCEPEmCidade(cidade->dir, cep);
		int esq = buscarCEPEmCidade(cidade->esq, cep);
		if (dir || esq) return 1;
		cidade = NULL;
	}
	return 0;
}

int existeCEP(int cep)
{
	Estado *e = listaEstados.inicio;
	while (e)
	{
		if (buscarCEPEmEstado(e, cep)) return 1;
		e = e->prox;
	}
	return 0;
}

// ---------------------- Funções Auxiliares Pessoa ------------------------

void rotacaoEsquerdaPessoa(NoPessoa **raiz, NoPessoa *x)
{
	NoPessoa *y = x->dir;
	x->dir = y->esq;
	if (y->esq) y->esq->pai = x;
	y->pai = x->pai;
	if (!x->pai) *raiz = y;
	else if (x == x->pai->esq) x->pai->esq = y;
	else x->pai->dir = y;
	y->esq = x;
	x->pai = y;
}

void rotacaoDireitaPessoa(NoPessoa **raiz, NoPessoa *x)
{
	NoPessoa *y = x->esq;
	x->esq = y->dir;
	if (y->dir) y->dir->pai = x;
	y->pai = x->pai;
	if (!x->pai) *raiz = y;
	else if (x == x->pai->dir) x->pai->dir = y;
	else x->pai->esq = y;
	y->dir = x;
	x->pai = y;
}

void balancearInsercaoPessoa(NoPessoa **raiz, NoPessoa *z)
{
	while (z->pai && z->pai->cor == VERMELHO)
	{
		NoPessoa *tio = NULL;
		if (z->pai == z->pai->pai->esq)
		{
			tio = z->pai->pai->dir;
			if (tio && tio->cor == VERMELHO)
			{
				z->pai->cor = PRETO;
				tio->cor = PRETO;
				z->pai->pai->cor = VERMELHO;
				z = z->pai->pai;
			}
			else
			{
				if (z == z->pai->dir)
				{
					z = z->pai;
					rotacaoEsquerdaPessoa(raiz, z);
				}
				z->pai->cor = PRETO;
				z->pai->pai->cor = VERMELHO;
				rotacaoDireitaPessoa(raiz, z->pai->pai);
			}
		}
		else
		{
			tio = z->pai->pai->esq;
			if (tio && tio->cor == VERMELHO)
			{
				z->pai->cor = PRETO;
				tio->cor = PRETO;
				z->pai->pai->cor = VERMELHO;
				z = z->pai->pai;
			}
			else
			{
				if (z == z->pai->esq)
				{
					z = z->pai;
					rotacaoDireitaPessoa(raiz, z);
				}
				z->pai->cor = PRETO;
				z->pai->pai->cor = VERMELHO;
				rotacaoEsquerdaPessoa(raiz, z->pai->pai);
			}
		}
	}
	(*raiz)->cor = PRETO;
}

// ---------------------- Criação e Inserção Pessoa ------------------------

NoPessoa *criarPessoa(const char *cpf, const char *nome, int cep_natal, int cep_moradia, int d, int m, int a)
{
	NoPessoa *nova = (NoPessoa *)malloc(sizeof(NoPessoa));
	if (nova)
	{
		strcpy(nova->cpf, cpf);
		strcpy(nova->nome, nome);
		nova->cep_natal = cep_natal;
		nova->cep_moradia = cep_moradia;
		nova->dia = d;
		nova->mes = m;
		nova->ano = a;
		nova->cor = VERMELHO;
		nova->esq = nova->dir = nova->pai = NULL;
	}
	return nova;
}

NoPessoa *inserirPessoaRB(NoPessoa *raiz, NoPessoa *nova)
{
	NoPessoa *y = NULL, *x = raiz;
	while (x)
	{
		y = x;
		if (strcmp(nova->cpf, x->cpf) < 0) x = x->esq;
		else x = x->dir;
	}

	nova->pai = y;
	if (!y) raiz = nova;
	else if (strcmp(nova->cpf, y->cpf) < 0) y->esq = nova;
	else y->dir = nova;

	balancearInsercaoPessoa(&raiz, nova);
	return raiz;
}

void cadastrarPessoa(const char *cpf, const char *nome, int cep_natal, int cep_moradia, int d, int m, int a)
{
	if (!validarData(d, m, a))
	{
		printf("Data invalida.\n");
		return;
	}
	if (!existeCEP(cep_natal) || !existeCEP(cep_moradia))
	{
		printf("CEP de nascimento ou moradia nao encontrados.\n");
		return;
	}
	NoPessoa *nova = criarPessoa(cpf, nome, cep_natal, cep_moradia, d, m, a);
	if (nova) pessoas = inserirPessoaRB(pessoas, nova);
}
int cepEmUsoPorPessoa(NoPessoa *raiz, int cep)
{
	if (!raiz) return 0;
	if (raiz->cep_natal == cep || raiz->cep_moradia == cep) return 1;
	if (cepEmUsoPorPessoa(raiz->esq, cep)) return 1;
	if (cepEmUsoPorPessoa(raiz->dir, cep)) return 1;
	return 0;
}
NoCEP *minimoCEP(NoCEP *raiz)
{
	while (raiz && raiz->esq) raiz = raiz->esq;
	return raiz;
}

NoCEP *removerCEPRB(NoCEP *raiz, int cep)
{
	if (!raiz) return NULL;

	if (cep < raiz->cep) raiz->esq = removerCEPRB(raiz->esq, cep);
	else if (cep > raiz->cep) raiz->dir = removerCEPRB(raiz->dir, cep);
	else
	{
		if (!raiz->esq || !raiz->dir)
		{
			NoCEP *temp = raiz->esq ? raiz->esq : raiz->dir;
			free(raiz);
			return temp;
		}
		else
		{
			NoCEP *sucessor = minimoCEP(raiz->dir);
			raiz->cep = sucessor->cep;
			raiz->dir = removerCEPRB(raiz->dir, sucessor->cep);
		}
	}
	return raiz;
}
int removerCEPDeCidade(NoCidade *cidade, int cep)
{
	if (!cidade) return 0;
	if (existeCEPNo(cidade->ceps, cep) && !cepEmUsoPorPessoa(pessoas, cep))
	{
		cidade->ceps = removerCEPRB(cidade->ceps, cep);
		return 1;
	}
	return 0;
}

int removerCEP(Estado *estado, const char *nomeCidade, int cep)
{
	NoCidade *cidade = estado->cidades;
	while (cidade)
	{
		int cmp = strcmp(nomeCidade, cidade->nome);
		if (cmp == 0) return removerCEPDeCidade(cidade, cep);
		cidade = (cmp < 0) ? cidade->esq : cidade->dir;
	}
	return 0;
}
NoPessoa *minimoPessoa(NoPessoa *raiz)
{
	while (raiz && raiz->esq) raiz = raiz->esq;
	return raiz;
}

NoPessoa *removerPessoaRB(NoPessoa *raiz, const char *cpf)
{
	if (!raiz) return NULL;

	int cmp = strcmp(cpf, raiz->cpf);
	if (cmp < 0) raiz->esq = removerPessoaRB(raiz->esq, cpf);
	else if (cmp > 0) raiz->dir = removerPessoaRB(raiz->dir, cpf);
	else
	{
		if (!raiz->esq || !raiz->dir)
		{
			NoPessoa *temp = raiz->esq ? raiz->esq : raiz->dir;
			free(raiz);
			return temp;
		}
		else
		{
			NoPessoa *sucessor = minimoPessoa(raiz->dir);
			strcpy(raiz->cpf, sucessor->cpf);
			strcpy(raiz->nome, sucessor->nome);
			raiz->cep_natal = sucessor->cep_natal;
			raiz->cep_moradia = sucessor->cep_moradia;
			raiz->dia = sucessor->dia;
			raiz->mes = sucessor->mes;
			raiz->ano = sucessor->ano;
			raiz->dir = removerPessoaRB(raiz->dir, sucessor->cpf);
		}
	}
	return raiz;
}

void removerPessoa(const char *cpf)
{
	pessoas = removerPessoaRB(pessoas, cpf);
}
void estadoMaisPopuloso()
{
	Estado *p = listaEstados.inicio, *maior = NULL;
	while (p)
	{
		if (!maior || p->populacao > maior->populacao)
			maior = p;
		p = p->prox;
	}
	if (maior) printf("Estado mais populoso: %s (%d habitantes)\n", maior->nome, maior->populacao);
	else printf("Nenhum estado cadastrado.\n");
}
int compararStrings(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char a = (*s1 >= 'A' && *s1 <= 'Z') ? *s1 + 32 : *s1;
        char b = (*s2 >= 'A' && *s2 <= 'Z') ? *s2 + 32 : *s2;
        if (a != b) return 0;
        s1++;
        s2++;
    }
    return *s1 == *s2;
}

void populacaoCapital() {
    char nomeEstado[100];
    printf("Nome do estado: ");
    fgets(nomeEstado, sizeof(nomeEstado), stdin);
    nomeEstado[strcspn(nomeEstado, "\n")] = 0;

    Estado *p = listaEstados.inicio;
    while (p && !compararStrings(p->nome, nomeEstado)) p = p->prox;

    if (!p) {
        printf("Estado nao encontrado.\n");
        return;
    }

    NoCidade *c = p->cidades;
    while (c) {
        int cmp = strcmp(c->nome, p->capital);
        if (cmp == 0) {
            printf("Populacao da capital %s: %d habitantes\n", c->nome, c->populacao);
            return;
        }
        c = (cmp < 0) ? c->esq : c->dir;
    }
    printf("Capital nao encontrada entre as cidades do estado.\n");
}
void cidadeMaisPopulosaSemCapital()
{
	char nomeEstado[100];
	printf("Nome do estado: ");
	fgets(nomeEstado, sizeof(nomeEstado), stdin);
	nomeEstado[strcspn(nomeEstado, "\n")] = 0;

	Estado *est = listaEstados.inicio;
	while (est && strcmp(est->nome, nomeEstado) != 0) est = est->prox;

	if (!est)
	{
		printf("Estado nao encontrado.\n");
		return;
	}

	NoCidade *maisPop = NULL;
	NoCidade *pilha[100];
	int topo = -1;
	NoCidade *atual = est->cidades;

	while (atual || topo >= 0)
	{
		while (atual)
		{
			pilha[++topo] = atual;
			atual = atual->esq;
		}
		atual = pilha[topo--];
		if (strcmp(atual->nome, est->capital) != 0)
		{
			if (!maisPop || atual->populacao > maisPop->populacao)
				maisPop = atual;
		}
		atual = atual->dir;
	}

	if (maisPop)
		printf("Cidade mais populosa (exceto a capital): %s (%d habitantes)\n", maisPop->nome, maisPop->populacao);
	else
		printf("Nenhuma cidade encontrada (exceto capital).\n");
}
int contarPessoasNaoMoramNaCidadeNatal(NoPessoa *r)
{
	if (!r) return 0;
	int atual = (r->cep_natal != r->cep_moradia);
	int esq = contarPessoasNaoMoramNaCidadeNatal(r->esq);
	int dir = contarPessoasNaoMoramNaCidadeNatal(r->dir);
	return atual + esq + dir;
}

void pessoasNaoMoramNaCidadeNatal()
{
	int total = contarPessoasNaoMoramNaCidadeNatal(pessoas);
	printf("Quantidade de pessoas que nao moram na cidade natal: %d\n", total);
}
void buscarCidadePorCEP(Estado *e, int cep, char *nomeCidade)
{
	if (!e) return;
	NoCidade *c = e->cidades;
	NoCidade *pilha[100];
	int topo = -1;

	while (c || topo >= 0)
	{
		while (c)
		{
			pilha[++topo] = c;
			c = c->esq;
		}
		c = pilha[topo--];

		if (existeCEPNo(c->ceps, cep))
		{
			strcpy(nomeCidade, c->nome);
			return;
		}

		c = c->dir;
	}
}

void cidadePorCEPNatal()
{
	int cep;
	printf("Digite o CEP: ");
	scanf("%d", &cep);

	Estado *e = listaEstados.inicio;
	char resultado[100] = "";
	while (e && resultado[0] == '\0')
	{
		buscarCidadePorCEP(e, cep, resultado);
		e = e->prox;
	}

	if (resultado[0] != '\0')
		printf("Cidade correspondente ao CEP %d: %s\n", cep, resultado);
	else
		printf("CEP nao encontrado.\n");
}
int contarNascidosQueNaoMoram(NoPessoa *r, int cep)
{
	if (!r) return 0;
	int atual = (r->cep_natal == cep && r->cep_moradia != cep);
	return atual + contarNascidosQueNaoMoram(r->esq, cep) + contarNascidosQueNaoMoram(r->dir, cep);
}

void pessoasNascidasQueNaoMoram()
{
	int cep;
	printf("Digite o CEP da cidade: ");
	scanf("%d", &cep);
	int total = contarNascidosQueNaoMoram(pessoas, cep);
	printf("Pessoas nascidas em %d que nao moram nela: %d\n", cep, total);
}
int contarMoradoresNaoNascidos(NoPessoa *r, int cep)
{
	if (!r) return 0;
	int atual = (r->cep_moradia == cep && r->cep_natal != cep);
	return atual + contarMoradoresNaoNascidos(r->esq, cep) + contarMoradoresNaoNascidos(r->dir, cep);
}

void pessoasQueMoramMasNaoNasceram()
{
	int cep;
	printf("Digite o CEP da cidade: ");
	scanf("%d", &cep);
	int total = contarMoradoresNaoNascidos(pessoas, cep);
	printf("Pessoas que moram em %d mas nao nasceram nela: %d\n", cep, total);
}
