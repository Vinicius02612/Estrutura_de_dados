#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 5
#define BLOCK_SIZE (1024 * 1024) // 1MB

typedef struct Node {
    char status; // 'L' para livre, 'O' para ocupado
    int bloco_inicial;
    int bloco_final;
    unsigned long endereco_inicial;
    unsigned long endereco_final;
    struct Node *children[MAX_CHILDREN];
    int num_children;
    struct Node *parent;
    struct Node *next; // para lista simples dos nós folha
} Node;

typedef struct {
    Node *root;
    Node *leaf_head;
    int total_blocos;
    unsigned long memoria_total;
} Arvore45;

// Função para criar um novo nó
Node* criar_no(char status, int bloco_inicial, int bloco_final, unsigned long endereco_inicial, unsigned long endereco_final) {
    Node *no = (Node*)malloc(sizeof(Node));
    no->status = status;
    no->bloco_inicial = bloco_inicial;
    no->bloco_final = bloco_final;
    no->endereco_inicial = endereco_inicial;
    no->endereco_final = endereco_final;
    no->num_children = 0;
    no->parent = NULL;
    no->next = NULL;
    memset(no->children, 0, sizeof(no->children));
    return no;
}

// Função para inserir nó folha na lista
void inserir_folha(Arvore45 *arvore, Node *no) {
    if (!arvore->leaf_head) {
        arvore->leaf_head = no;
    } else {
        Node *tmp = arvore->leaf_head;
        while (tmp->next) tmp = tmp->next;
        tmp->next = no;
    }
}

// Cadastro dos nós
void cadastrar_nos(Arvore45 *arvore) {
    char status;
    unsigned long endereco_inicial, endereco_final;
    int bloco_inicial = 0, bloco_final;
    int contador = 0;

    printf("Informe o tamanho total da memoria em MB: ");
    scanf("%lu", &arvore->memoria_total);
    arvore->memoria_total *= BLOCK_SIZE;
    arvore->total_blocos = arvore->memoria_total / BLOCK_SIZE;

    printf("Cadastro do primeiro nó:\n");
    printf("Status (L para livre, O para ocupado): ");
    scanf(" %c", &status);
    printf("Endereco inicial: ");
    scanf("%lu", &endereco_inicial);
    printf("Endereco final: ");
    scanf("%lu", &endereco_final);

    bloco_final = (endereco_final / BLOCK_SIZE);
    Node *no = criar_no(status, bloco_inicial, bloco_final, endereco_inicial, endereco_final);
    inserir_folha(arvore, no);
    contador++;

    while (endereco_final < arvore->memoria_total - 1) {
        bloco_inicial = bloco_final + 1;
        printf("\nCadastro do próximo nó:\n");
        status = (status == 'L') ? 'O' : 'L';
        printf("Status: %c\n", status);
        endereco_inicial = bloco_inicial * BLOCK_SIZE;
        printf("Endereco inicial: %lu\n", endereco_inicial);
        printf("Endereco final: ");
        scanf("%lu", &endereco_final);
        bloco_final = (endereco_final / BLOCK_SIZE);
        Node *novo_no = criar_no(status, bloco_inicial, bloco_final, endereco_inicial, endereco_final);
        inserir_folha(arvore, novo_no);
        contador++;
        if (endereco_final >= arvore->memoria_total - 1) break;
    }
}

// Função para imprimir os nós folha
void imprimir_nos(Arvore45 *arvore) {
    Node *tmp = arvore->leaf_head;
    printf("\nNÓS DA MEMÓRIA:\n");
    while (tmp) {
        printf("[%c] Blocos %d-%d | Endereços %lu-%lu\n", tmp->status, tmp->bloco_inicial, tmp->bloco_final, tmp->endereco_inicial, tmp->endereco_final);
        tmp = tmp->next;
    }
}

// Função para concatenar nós adjacentes com mesmo status
void concatenar_nos(Arvore45 *arvore) {
    Node *tmp = arvore->leaf_head;
    while (tmp && tmp->next) {
        if (tmp->status == tmp->next->status && tmp->bloco_final + 1 == tmp->next->bloco_inicial) {
            Node *remover = tmp->next;
            tmp->bloco_final = remover->bloco_final;
            tmp->endereco_final = remover->endereco_final;
            tmp->next = remover->next;
            free(remover);
        } else {
            tmp = tmp->next;
        }
    }
}

// Função para alocar blocos
void alocar_blocos(Arvore45 *arvore) {
    int quantidade;
    printf("Quantidade de blocos a alocar: ");
    scanf("%d", &quantidade);

    Node *tmp = arvore->leaf_head;
    while (tmp) {
        int blocos_livres = tmp->bloco_final - tmp->bloco_inicial + 1;
        if (tmp->status == 'L' && blocos_livres >= quantidade) {
            printf("Alocando nos blocos %d-%d\n", tmp->bloco_inicial, tmp->bloco_inicial + quantidade - 1);
            if (blocos_livres == quantidade) {
                tmp->status = 'O';
            } else {
                // Split node
                Node *novo_no = criar_no('L', tmp->bloco_inicial + quantidade, tmp->bloco_final,
                                         tmp->endereco_inicial + quantidade * BLOCK_SIZE, tmp->endereco_final);
                novo_no->next = tmp->next;
                tmp->next = novo_no;
                tmp->bloco_final = tmp->bloco_inicial + quantidade - 1;
                tmp->endereco_final = tmp->endereco_inicial + (quantidade * BLOCK_SIZE) - 1;
                tmp->status = 'O';
            }
            concatenar_nos(arvore);
            return;
        }
        tmp = tmp->next;
    }
    printf("Nao ha blocos livres suficientes.\n");
}

// Função para liberar blocos
void liberar_blocos(Arvore45 *arvore) {
    int bloco_inicio, bloco_fim;
    printf("Informe o bloco inicial a liberar: ");
    scanf("%d", &bloco_inicio);
    printf("Informe o bloco final a liberar: ");
    scanf("%d", &bloco_fim);

    Node *tmp = arvore->leaf_head, *prev = NULL;
    while (tmp) {
        if (tmp->bloco_inicial <= bloco_inicio && tmp->bloco_final >= bloco_fim && tmp->status == 'O') {
            if (tmp->bloco_inicial == bloco_inicio && tmp->bloco_final == bloco_fim) {
                tmp->status = 'L';
            } else if (tmp->bloco_inicial == bloco_inicio) {
                // Split right
                Node *novo_no = criar_no('O', bloco_fim + 1, tmp->bloco_final,
                                         (bloco_fim + 1) * BLOCK_SIZE, tmp->endereco_final);
                novo_no->next = tmp->next;
                tmp->next = novo_no;
                tmp->bloco_final = bloco_fim;
                tmp->endereco_final = (bloco_fim + 1) * BLOCK_SIZE - 1;
                tmp->status = 'L';
            } else if (tmp->bloco_final == bloco_fim) {
                // Split left
                Node *novo_no = criar_no('O', tmp->bloco_inicial, bloco_inicio - 1,
                                         tmp->endereco_inicial, bloco_inicio * BLOCK_SIZE - 1);
                novo_no->next = tmp;
                if (prev) prev->next = novo_no;
                else arvore->leaf_head = novo_no;
                tmp->bloco_inicial = bloco_inicio;
                tmp->endereco_inicial = bloco_inicio * BLOCK_SIZE;
                tmp->status = 'L';
            } else {
                // Split both sides
                Node *no_esq = criar_no('O', tmp->bloco_inicial, bloco_inicio - 1,
                                        tmp->endereco_inicial, bloco_inicio * BLOCK_SIZE - 1);
                Node *no_dir = criar_no('O', bloco_fim + 1, tmp->bloco_final,
                                        (bloco_fim + 1) * BLOCK_SIZE, tmp->endereco_final);
                no_esq->next = tmp;
                tmp->next = no_dir;
                if (prev) prev->next = no_esq;
                else arvore->leaf_head = no_esq;
                tmp->bloco_inicial = bloco_inicio;
                tmp->bloco_final = bloco_fim;
                tmp->endereco_inicial = bloco_inicio * BLOCK_SIZE;
                tmp->endereco_final = (bloco_fim + 1) * BLOCK_SIZE - 1;
                tmp->status = 'L';
            }
            concatenar_nos(arvore);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    printf("Nao foi possivel liberar os blocos informados.\n");
}

int main() {
    Arvore45 arvore = {0};
    int opcao;
    cadastrar_nos(&arvore);

    do {
        printf("\n1 - Imprimir nós\n2 - Alocar blocos\n3 - Liberar blocos\n0 - Sair\nOpcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                imprimir_nos(&arvore);
                break;
            case 2:
                alocar_blocos(&arvore);
                break;
            case 3:
                liberar_blocos(&arvore);
                break;
        }
    } while (opcao != 0);

    // Liberar memória
    Node *tmp = arvore.leaf_head;
    while (tmp) {
        Node *prox = tmp->next;
        free(tmp);
        tmp = prox;
    }
    return 0;
}