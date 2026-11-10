#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "inventory.txt"

int carregar_estoque(char nomes[][100], int quantidades[]) {
    FILE *file = fopen(ARQUIVO, "r");
    if (file == NULL) {
        return 0; 
    }

    int total = 0;
    while (fscanf(file, "%s", nomes[total]) == 1) {
        fscanf(file, "%d", &quantidades[total]);
        total++;
    }
    
    fclose(file);
    return total;
}

void salvar_estoque(char nomes[][100], int quantidades[], int total) {
    FILE *file = fopen(ARQUIVO, "w"); 
    if (file != NULL) {
        for (int i = 0; i < total; i++) {
            fprintf(file, "%s\n%d\n", nomes[i], quantidades[i]);
        }
        fclose(file);
    }
}

int main() {
    int operador; 
    char nome_item[100];
    int quantidade = 0;
    int quantidade_removida = 0;

    char nomes_estoque[100][100];
    int qtd_estoque[100];
    int total_itens;

    do {
        total_itens = carregar_estoque(nomes_estoque, qtd_estoque);


        do {
            printf("\n==================================\n");
            printf("   Controle de Estoque\n");
            printf("==================================\n");
            printf("Selecione uma opcao:\n");
            printf("1. Adicionar Item\n");
            printf("2. Remover Item\n");
            printf("3. Listar Estoque\n");
            printf("4. Sair\n");
            printf("Opcao: ");
            

            if (scanf("%d", &operador) != 1) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                operador = 0; 
            }
            
            if (operador < 1 || operador > 4) {
                printf("Opcao invalida! Tente novamente.\n");
            }
        } while (operador < 1 || operador > 4);

        if (operador == 1) {
            printf("Digite o nome do item: ");
            scanf("%s", nome_item);
            printf("Digite a quantidade: ");
            scanf("%d", &quantidade);

            int encontrado = 0;
            for (int i = 0; i < total_itens; i++) {
                if (strcmp(nomes_estoque[i], nome_item) == 0) {
                    qtd_estoque[i] += quantidade;
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                strcpy(nomes_estoque[total_itens], nome_item);
                qtd_estoque[total_itens] = quantidade;
                total_itens++;
            }

            salvar_estoque(nomes_estoque, qtd_estoque, total_itens);
            printf("Item adicionado com sucesso!\n");

        } else if (operador == 2) {
            printf("Digite o nome do item: ");
            scanf("%s", nome_item);
            printf("Digite a quantidade a ser removida: ");
            scanf("%d", &quantidade_removida);
            
            int indice_encontrado = -1;
            for (int i = 0; i < total_itens; i++) {
                if (strcmp(nomes_estoque[i], nome_item) == 0) {
                    indice_encontrado = i;
                    break;
                }
            }

            if (indice_encontrado == -1) {
                printf("Item nao encontrado.\n");
            } else {
                if (qtd_estoque[indice_encontrado] < quantidade_removida) {
                    printf("Estoque insuficiente. Quantidade disponivel: %d\n", qtd_estoque[indice_encontrado]);
                } else {
                    qtd_estoque[indice_encontrado] -= quantidade_removida;
                    
                    if (qtd_estoque[indice_encontrado] == 0) {
                        for (int i = indice_encontrado; i < total_itens - 1; i++) {
                            strcpy(nomes_estoque[i], nomes_estoque[i + 1]);
                            qtd_estoque[i] = qtd_estoque[i + 1];
                        }
                        total_itens--;
                        printf("Item removido do estoque!\n");
                    } else {
                        printf("Quantidade atualizada com sucesso!\n");
                    }
                    salvar_estoque(nomes_estoque, qtd_estoque, total_itens);
                }
            }

        } else if (operador == 3) { 
            if (total_itens == 0) {
                printf("O estoque esta vazio.\n");
            } else {
                printf("=============================\n");
                printf("        Estoque Atual\n");
                printf("=============================\n");
                for (int i = 0; i < total_itens; i++) {
                    printf("Nome: %s\n", nomes_estoque[i]);
                    printf("Quantidade: %d\n\n", qtd_estoque[i]);
                }
            }
        }

        if (operador >= 1 && operador <= 3) {
            printf("Deseja realizar outra operacao? (s/n): ");
            char resposta;
            

            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            
            scanf("%c", &resposta); 
            if (resposta == 's' || resposta == 'S') {
                continue; 
            } else {
                printf("Obrigado por usar o Controle de Estoques! Ate a proxima.\n");
                break; 
            }
        } else if (operador == 4) { 
            printf("Obrigado por usar o Controle de Estoques! Ate a proxima.\n");
            break; 
        }

    } while (1);

    return 0;
}