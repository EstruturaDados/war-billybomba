#include <stdio.h>  // Biblioteca padrão para entrada e saída
#include <stdlib.h> // Biblioteca para funções utilitárias (como alocação de memória)
#include <string.h> // Biblioteca para manipulação de strings

// Definindo constantes para o tamanho máximo de territórios e campos de text
#define MAX_TERRITORIOS 5
#define TAM_NOME 50
#define TAM_COR 30

// Estrutura que representa um território no jogo
struct Territorio
{
    char nome[TAM_NOME];       // Nome do território
    char corExercito[TAM_COR]; // Cor do exército que ocupa o território
    int numeroTropas;          // Número de tropas presentes no território
};

// Função para limpar o buffer de entrada (evita problemas com fgets após scanf)
void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; // Consome caracteres até nova linha ou fim de arquivo
}

int main()
{
    struct Territorio biblioteca[MAX_TERRITORIOS]; // Vetor que armazena os territórios cadastrados
    int totalTerritorio = 0;                       // Contador de territórios cadastrados
    int opcao;                                     // Variável para armazenar a opção do menu

    // Loop principal do programa
    do
    {
        // Exibe o menu principal

        printf("======================================================\n");
        printf("                     WAR\n");
        printf("======================================================\n");
        printf("1 - Cadastro dos Territorios:\n");
        printf("2 - Listar todos os Territorios\n");
        printf("0 - Sair\n");

        // Lê a opção do usuário
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o buffer após leitura numérica

        // Executa a ação correspondente à opção escolhida
        switch (opcao)
        {
        case 1:
            // Cadastro de novo território
            printf("--- Cadastro de Novo Territorios ---\n\n");

            // Verifica se ainda há espaço para cadastrar
            if ((totalTerritorio < MAX_TERRITORIOS) && (opcao == 1))
            {

                // Lê o nome do território
                printf("Digite o nome do Territorio:");
                fgets(biblioteca[totalTerritorio].nome, TAM_NOME, stdin);

                // Lê a cor do exército
                printf("Digite a Cor do exercito:");
                fgets(biblioteca[totalTerritorio].corExercito, TAM_COR, stdin);

                // Remove o caractere de nova linha das strings
                biblioteca[totalTerritorio].nome[strcspn(biblioteca[totalTerritorio].nome, "\n")] = '\0';
                biblioteca[totalTerritorio].corExercito[strcspn(biblioteca[totalTerritorio].corExercito, "\n")] = '\0';

                // Lê o número de tropas
                printf("Digite Numero de tropas:");
                scanf("%d", &biblioteca[totalTerritorio].numeroTropas);
                limparBufferEntrada();

                // Incrementa o contador de territórios
                totalTerritorio++;

                printf("\nTerritorios cadastrado com sucesso! \n");
            }
            else
            {

                // Caso o limite de territórios tenha sido atingido
                printf("Numeros de Territorios cheio! Nao e possivel cadastra novos Territorios\n");
            }

            break;

        case 2:

            // Listagem dos territórios cadastrados
            printf("======================================================\n");
            printf("================Listagem de Territorios===============\n");

            if (totalTerritorio == 0)
            {

                // Nenhum território cadastrado
                printf("Nenhum Territorios cadastrado ainda.\n");
            }
            else
            {
                for (int i = 0; i < totalTerritorio; i++)
                {
                    // Exibe os dados de cada território
                    printf("\n------------------------------------------------\n");
                    printf("Territorios %d\n", i + 1);
                    printf("Nome: %s\n", biblioteca[i].nome);
                    printf("Cor: %s\n", biblioteca[i].corExercito);

                    printf("Numero de tropas: %d\n", biblioteca[i].numeroTropas);
                }

                printf("\n------------------------------------------------\n");
            }
            break;

        case 0:

            // Encerra o programa
            printf("\nSaindo do sistema ....\n");

            break;

        default:
            // Caso o usuário digite uma opção inválida
            printf("\nOpcao invalida! Tente novamente.\n");
            printf("\nPressione Enter para continuar...");
            getchar();
            break;
        }

    } while (opcao != 0); // Continua o loop até o usuário escolher sair
    return 0; // Fim do programa
}