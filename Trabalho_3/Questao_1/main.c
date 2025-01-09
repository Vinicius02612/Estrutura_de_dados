#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define MAX_STATES 10000 // Número máximo de configurações
#define MAX_DISCOS 4     // Número de discos (4 neste problema)

int grafo[MAX_STATES][MAX_STATES]; // Matriz de adjacência
int estados[MAX_STATES][MAX_DISCOS]; // Estados (configurações dos discos)
int estado_inicial[MAX_DISCOS] = {0, 0, 0, 0}; // Todos os discos no pino A
int estado_final[MAX_DISCOS] = {2, 2, 2, 2};   // Todos os discos no pino C
int num_estados = 0;

// Função para verificar se um movimento é válido
int movimento_valido(int *estado_atual, int disco, int pino_destino) {
    int estado = 1;
    for (int i = 0; i < disco; i++) {
        if (estado_atual[i] == pino_destino) {
            estado = 0; // Há um disco menor no destino
        }
    }
    return estado;
}

// Função para adicionar um novo estado ao grafo
int adicionar_estado(int *novo_estado) {
    for (int i = 0; i < num_estados; i++) {
        if (memcmp(estados[i], novo_estado, sizeof(int) * MAX_DISCOS) == 0) {
           return i;
        }
    }
    memcpy(estados[num_estados], novo_estado, sizeof(int) * MAX_DISCOS);
    return num_estados++;
}

// Gera o grafo de configurações possíveis
void gerar_grafo() {
    printf("Ta dando erro aqui na função gera grafo \n");
    int fila[MAX_STATES], inicio = 0, fim = 0;
    int estado_atual[MAX_DISCOS], novo_estado[MAX_DISCOS];// estado atual com 4 discos 

    int inicial_id = adicionar_estado(estado_inicial);
    fila[fim++] = inicial_id;

    while (inicio < fim) {
        printf("entrou aqui na repetição \n");
        int atual_id = fila[inicio++];
        memcpy(estado_atual, estados[atual_id], sizeof(int) * MAX_DISCOS);

        for (int disco = 0; disco < MAX_DISCOS; disco++) {
            for (int pino = 0; pino < 3; pino++) {
                if (estado_atual[disco] != pino && movimento_valido(estado_atual, disco, pino) == 0) {
                    memcpy(novo_estado, estado_atual, sizeof(int) * MAX_DISCOS);
                    novo_estado[disco] = pino;

                    int novo_id = adicionar_estado(novo_estado);
                    grafo[atual_id][novo_id] = 1;
                    grafo[novo_id][atual_id] = 1; // Grafo não direcionado

                    fila[fim++] = novo_id;
                }
            }
        }
    }
}

// Algoritmo de Dijkstra para encontrar o menor caminho
void dijkstra(int origem, int destino) {
    int dist[MAX_STATES], visitado[MAX_STATES];
    for (int i = 0; i < num_estados; i++) {
        dist[i] = INT_MAX;
        visitado[i] = 0;
    }
    dist[origem] = 0;

    for (int i = 0; i < num_estados; i++) {
        int u = -1;
        for (int j = 0; j < num_estados; j++) {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INT_MAX) break;
        visitado[u] = 1;

        for (int v = 0; v < num_estados; v++) {
            if (grafo[u][v] && dist[u] + grafo[u][v] < dist[v]) {
                dist[v] = dist[u] + grafo[u][v];
            }
        }
    }

    printf("Menor caminho do estado inicial ao final: %d  - %d\n", dist[destino], destino);
}

int main() {
    clock_t inicio, fim;
    double tempo_gasto;

    inicio = clock();

    gerar_grafo();

    int inicial_id = adicionar_estado(estado_inicial);
    int final_id = adicionar_estado(estado_final);

    dijkstra(inicial_id, final_id);

    fim = clock();
    tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Tempo gasto: %.6f segundos\n", tempo_gasto);

    return 0;
}
