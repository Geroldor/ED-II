#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int prioridade;
    int tempoEspera;
} Processo;

void inserirProcesso(Processo* heap, int* tamanhoAtual, Processo novoProcesso, int tipoHeap) {
    int i = (*tamanhoAtual)++;
    if (tipoHeap == 1) {
        while (i > 0 && heap[(i - 1) / 2].prioridade < novoProcesso.prioridade) {
            heap[i] = heap[(i - 1) / 2];
            i = (i - 1) / 2;
        }
    } else {
        while (i > 0 && heap[(i - 1) / 2].tempoEspera > novoProcesso.tempoEspera) {
            heap[i] = heap[(i - 1) / 2];
            i = (i - 1) / 2;
        }
    }
    heap[i] = novoProcesso;
}

void inserir(Processo* heapMax, Processo* heapMin, int* tamanhoMax, int* tamanhoMin, int n){
    for (int i = 0; i < n; i++) {
        Processo p;
        printf("Digite o PID do processo %d: ", i + 1);
        scanf("%d", &p.pid);
        printf("Digite a prioridade do processo %d: ", i + 1);
        scanf("%d", &p.prioridade);
        printf("Digite o tempo de espera do processo %d: ", i + 1);
        scanf("%d", &p.tempoEspera);
        inserirProcesso(heapMax, tamanhoMax, p, 1);
        inserirProcesso(heapMin, tamanhoMin, p, 2);
    }
}

Processo removerProcessoTopo(Processo* heap, int* tamanhoAtual, int tipoHeap) {
    Processo removido = heap[0];
    heap[0] = heap[--(*tamanhoAtual)];
    int i = 0;
    int filho = 2 * i + 1;
    if (tipoHeap == 1) {
        while (filho < *tamanhoAtual) {
            if (filho < *tamanhoAtual - 1 && heap[filho].prioridade < heap[filho + 1].prioridade) {
                filho++;
            }
            if (heap[i].prioridade < heap[filho].prioridade) {
                Processo temp = heap[i];
                heap[i] = heap[filho];
                heap[filho] = temp;
                i = filho;
                filho = 2 * i + 1;
            } else {
                break;
            }
        }
    } else {
        while (filho < *tamanhoAtual) {
            if (filho < *tamanhoAtual - 1 && heap[filho].tempoEspera > heap[filho + 1].tempoEspera) {
                filho++;
            }
            if (heap[i].tempoEspera > heap[filho].tempoEspera) {
                Processo temp = heap[i];
                heap[i] = heap[filho];
                heap[filho] = temp;
                i = filho;
                filho = 2 * i + 1;
            } else {
                break;
            }
        }
    }
    return removido;
}

int heapVazio(int tamanhoAtual) {
    return tamanhoAtual == 0;
}

void imprimirProcessos(Processo* heap, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("PID: %d, Prioridade: %d, Tempo de Espera: %d\n", heap[i].pid, heap[i].prioridade, heap[i].tempoEspera);
    }
}

int main() {
    int n;
    printf("Digite a quantidade de processos: ");
    scanf("%d", &n);
    Processo* heapMax = (Processo*)malloc(n * sizeof(Processo));
    Processo* heapMin = (Processo*)malloc(n * sizeof(Processo));
    int tamanhoMax = 0;
    int tamanhoMin = 0;
    inserir(heapMax, heapMin, &tamanhoMax, &tamanhoMin, n);
    printf("\nHeap Máximo:\n");
    imprimirProcessos(heapMax, tamanhoMax);
    printf("\nHeap Mínimo:\n");
    imprimirProcessos(heapMin, tamanhoMin);
    free(heapMax);
    free(heapMin);
    return 0;
}