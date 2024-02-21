#include "arvore.h"

void exibirMenu() {
    printf("\n===== Menu =====\n");
    printf("1. Inserir elemento\n");
    printf("2. Excluir elemento\n");
    printf("3. Exibir arvore em ordem\n");
    printf("4. Verificar se a arvore eh AVL\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    // Inicialize a árvore AVL
    PONT minhaArvore = NULL;

    int opcao;
    bool alterou;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                // Inserir elemento
                TIPOCHAVE chave;
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &chave);

                inserirAVL(&minhaArvore, chave, &alterou);
                if (alterou) {
                    printf("Elemento inserido com sucesso!\n");
                } else {
                    printf("Elemento já existe na árvore!\n");
                }
                break;
            }
            case 2: {
                // Excluir elemento
                TIPOCHAVE chave;
                printf("Digite o valor a ser excluído: ");
                scanf("%d", &chave);

                bool excluido = excluirAVL(&minhaArvore, chave, &alterou);
                if (excluido) {
                    printf("Elemento excluído com sucesso!\n");
                } else {
                    printf("Elemento não encontrado na árvore!\n");
                }
                break;
            }
            case 3:
                // Exibir árvore em ordem
                printf("Árvore em ordem: ");
                exibirArvoreEmOrdem(minhaArvore);
                printf("\n");
                break;
            case 4:
                // Verificar se a árvore é AVL
                if (ehAVL(minhaArvore)) {
                    printf("A árvore é AVL!\n");
                } else {
                    printf("A árvore não é AVL!\n");
                }
                break;
            case 5:
                // Sair
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 5);

    // Destrua a árvore antes de sair do programa
    destruirArvore(&minhaArvore);

    return 0;
}