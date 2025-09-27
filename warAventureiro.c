#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Biblioteca para controle de aleatoriedade

#define MAX_TERRITORIOS 5
#define TAM_NOME 50
#define TAM_COR 30

// Estrutura que representa um territorio
typedef struct Territorio {
    char nome[TAM_NOME];
    char corExercito[TAM_COR];
    int numeroTropas;
} Territorio;

// Funcao para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funcao que simula um ataque entre dois territorios
void simularAtaque(Territorio *atacante, Territorio *defensor) {
    // Sorteia dados de ataque e defesa (1 a 6)
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\nDados sorteados:\n");
    printf("Atacante rolou o dado e tirou : (%s): %d\n", atacante->nome, dadoAtaque);
    printf("Defensor rolou o dado e tirou : (%s): %d\n", defensor->nome, dadoDefesa);

    // Logica de batalha
    if (dadoAtaque >= dadoDefesa) {
        defensor->numeroTropas--;
        printf("O atacante venceu! O defensor perdeu 1 tropa.\n");

        // Verifica se o defensor perdeu todas as tropas
        if (defensor->numeroTropas <= 0) {
            defensor->numeroTropas = 1; // Ganha 1 tropa ao ser conquistado
            strcpy(defensor->corExercito, atacante->corExercito);
            printf("O territorio %s foi conquistado pelo exercito %s!\n", defensor->nome, defensor->corExercito);
        }
    } else {
        printf("O defensor resistiu ao ataque!\n");
    }
}

int main() {
    srand(time(NULL)); // Inicializa gerador de numeros aleatorios

    // Alocacao dinamica de memoria para os territorios
    Territorio *biblioteca = (Territorio *)calloc(MAX_TERRITORIOS, sizeof(Territorio));
    if (biblioteca == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    int totalTerritorio = 0;
    int opcao;

    do {
        printf("\n======================================================\n");
        printf("                     WAR\n");
        printf("======================================================\n");
        printf("1 - Cadastro dos Territorios\n");
        printf("2 - Listar todos os Territorios\n");
        printf("3 - Simular Ataque\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
        case 1:
            if (totalTerritorio < MAX_TERRITORIOS) {
                printf("\n--- Cadastro de Novo Territorio ---\n");

                printf("Digite o nome do Territorio: ");
                fgets(biblioteca[totalTerritorio].nome, TAM_NOME, stdin);
                biblioteca[totalTerritorio].nome[strcspn(biblioteca[totalTerritorio].nome, "\n")] = '\0';

                printf("Digite a cor do exercito: ");
                fgets(biblioteca[totalTerritorio].corExercito, TAM_COR, stdin);
                biblioteca[totalTerritorio].corExercito[strcspn(biblioteca[totalTerritorio].corExercito, "\n")] = '\0';

                printf("Digite o numero de tropas: ");
                scanf("%d", &biblioteca[totalTerritorio].numeroTropas);
                limparBufferEntrada();

                totalTerritorio++;
                printf("Territorio cadastrado com sucesso!\n");
            } else {
                printf("Limite de territorios atingido.\n");
            }
            break;

        case 2:
            printf("\n================ Listagem de Territorios ================\n");
            if (totalTerritorio == 0) {
                printf("Nenhum territorio cadastrado ainda.\n");
            } else {
                for (int i = 0; i < totalTerritorio; i++) {
                    printf("\nTerritorio %d\n", i + 1);
                    printf("Nome: %s\n", biblioteca[i].nome);
                    printf("Cor do Exercito: %s\n", biblioteca[i].corExercito);
                    printf("Numero de Tropas: %d\n", biblioteca[i].numeroTropas);
                }
            }
            break;

        case 3:
            if (totalTerritorio < 2) {
                printf("E necessario pelo menos dois territorios cadastrados para simular ataque.\n");
                break;
            }

            int atacante, defensor;
            printf("\n--- Fase de Ataque ---\n");
            printf("Escolha o numero do territorio atacante (1 a %d): ", totalTerritorio);
            scanf("%d", &atacante);
            printf("Escolha o numero do territorio defensor (1 a %d): ", totalTerritorio);
            scanf("%d", &defensor);
            limparBufferEntrada();

            // Validacao de entrada
            if (atacante < 1 || atacante > totalTerritorio || defensor < 1 || defensor > totalTerritorio || atacante == defensor) {
                printf("Territorios invalidos. Tente novamente.\n");
            } else {
                simularAtaque(&biblioteca[atacante - 1], &biblioteca[defensor - 1]);
            }
            break;

        case 0:
            printf("\nSaindo do sistema...\n");
            break;

        default:
            printf("\nOpcao invalida! Tente novamente.\n");
            break;
        }

    } while (opcao != 0);

    free(biblioteca); // Libera memoria alocada
    return 0;
}
