#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define TAM_NOME 50
#define TAM_COR 30

typedef struct {
    char nome[TAM_NOME];
    char corExercito[TAM_COR];
    int numeroTropas;
} Territorio;

typedef enum {
    MISSAO_CONQUISTAR_3,
    MISSAO_DESTRUIR_VERDE
} TipoMissao;

// Inicializa os territorios com dados fixos
void inicializarTerritorios(Territorio *territorios) {
    const char *nomes[] = {"Alfa", "Bravo", "Charlie", "Delta", "Echo"};
    const char *cores[] = {"Vermelho", "Verde", "Azul", "Amarelo", "Preto"};
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        strcpy(territorios[i].nome, nomes[i]);
        strcpy(territorios[i].corExercito, cores[i]);
        territorios[i].numeroTropas = rand() % 5 + 1;
    }
}

// Exibe o estado atual dos territorios
void exibirMapa(const Territorio *territorios) {
    printf("\n=== Mapa Atual ===\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Territorio %d: %s | Cor: %s | Tropas: %d\n",
               i + 1, territorios[i].nome, territorios[i].corExercito, territorios[i].numeroTropas);
    }
}

// Simula um ataque entre dois territorios
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\nAtaque de %s contra %s\n", atacante->nome, defensor->nome);
    printf("Dado do atacante: %d\n", dadoAtaque);
    printf("Dado do defensor: %d\n", dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        defensor->numeroTropas--;
        printf("O defensor perdeu 1 tropa.\n");
        if (defensor->numeroTropas <= 0) {
            strcpy(defensor->corExercito, atacante->corExercito);
            defensor->numeroTropas = 1;
            printf("Territorio conquistado!\n");
        }
    } else {
        printf("O defensor resistiu ao ataque.\n");
    }
}

// Verifica se a missao foi cumprida
int verificarMissao(const Territorio *territorios, const char *corJogador, TipoMissao missao) {
    int conquistados = 0;
    switch (missao) {
        case MISSAO_CONQUISTAR_3:
            for (int i = 0; i < MAX_TERRITORIOS; i++) {
                if (strcmp(territorios[i].corExercito, corJogador) == 0) {
                    conquistados++;
                }
            }
            return conquistados >= 3;
        case MISSAO_DESTRUIR_VERDE:
            for (int i = 0; i < MAX_TERRITORIOS; i++) {
                if (strcmp(territorios[i].corExercito, "Verde") == 0) {
                    return 0;
                }
            }
            return 1;
        default:
            return 0;
    }
}

// Exibe a descricao da missao
void exibirMissao(TipoMissao missao) {
    printf("\n=== Missao Atual ===\n");
    if (missao == MISSAO_CONQUISTAR_3) {
        printf("Conquistar 3 territorios\n");
    } else {
        printf("Destruir o exercito Verde\n");
    }
}

// Menu principal
void menuJogo(Territorio *territorios, const char *corJogador, TipoMissao missao) {
    int opcao;
    do {
        printf("\n=== Menu Principal ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int a, d;
            exibirMapa(territorios);
            printf("Escolha o numero do territorio atacante (1 a %d): ", MAX_TERRITORIOS);
            scanf("%d", &a);
            printf("Escolha o numero do territorio defensor (1 a %d): ", MAX_TERRITORIOS);
            scanf("%d", &d);
            if (a < 1 || a > MAX_TERRITORIOS || d < 1 || d > MAX_TERRITORIOS || a == d) {
                printf("Escolhas invalidas.\n");
            } else if (strcmp(territorios[a - 1].corExercito, corJogador) != 0) {
                printf("Voce so pode atacar com seus proprios territorios.\n");
            } else {
                atacar(&territorios[a - 1], &territorios[d - 1]);
                if (verificarMissao(territorios, corJogador, missao)) {
                    printf("\n*** Missao Cumprida! Voce venceu! ***\n");
                    break;
                }
            }
        } else if (opcao == 2) {
            exibirMissao(missao);
            if (verificarMissao(territorios, corJogador, missao)) {
                printf("Missao cumprida!\n");
            } else {
                printf("Missao ainda nao cumprida.\n");
            }
        } else if (opcao == 0) {
            printf("Saindo do jogo...\n");
        } else {
            printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

int main() {
    srand(time(NULL));

    Territorio territorios[MAX_TERRITORIOS];
    const char *corJogador = "Vermelho";
    TipoMissao missao = rand() % 2;

    inicializarTerritorios(territorios);
    menuJogo(territorios, corJogador, missao);

    return 0;
}
