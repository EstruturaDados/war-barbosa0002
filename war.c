/*
 * Sistema de Cadastro de Territórios - Jogo War
 * 
 * Este programa implementa o cadastro básico de territórios para o jogo War,
 * permitindo armazenar informações sobre nome, cor do exército e quantidade de tropas.
 * 
 * Autor: Sistema War
 * Data: 2025
 */

#include <stdio.h>
#include <string.h>

// Definição da quantidade de territórios a serem cadastrados
#define MAX_TERRITORIOS 5

/*
 * Struct Territorio
 * 
 * Estrutura de dados que representa um território no jogo War.
 * Contém as informações essenciais de cada território:
 * - nome: identificação do território (até 29 caracteres + '\0')
 * - cor: cor do exército que ocupa o território (até 9 caracteres + '\0')
 * - tropas: quantidade de tropas posicionadas no território
 */
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
} Territorio;

/*
 * Função: limparBuffer
 * 
 * Limpa o buffer de entrada para evitar problemas com leituras subsequentes.
 * Útil após usar scanf com especificadores que não consomem o '\n'.
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * Função: cadastrarTerritorios
 * 
 * Realiza o cadastro de todos os territórios, solicitando ao usuário
 * que informe nome, cor do exército e quantidade de tropas para cada um.
 * 
 * Parâmetros:
 *   territorios[] - vetor de structs onde os dados serão armazenados
 *   quantidade - número de territórios a serem cadastrados
 */
void cadastrarTerritorios(Territorio territorios[], int quantidade) {
    printf("\n=== CADASTRO DE TERRITORIOS - JOGO WAR ===\n");
    printf("=========================================\n\n");
    
    // Laço para cadastrar cada território
    for (int i = 0; i < quantidade; i++) {
        printf("--- Territorio %d de %d ---\n", i + 1, quantidade);
        
        // Leitura do nome do território
        printf("Digite o nome do territorio: ");
        scanf("%29s", territorios[i].nome);
        limparBuffer();
        
        // Leitura da cor do exército
        printf("Digite a cor do exercito: ");
        scanf("%9s", territorios[i].cor);
        limparBuffer();
        
        // Leitura da quantidade de tropas
        printf("Digite o numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBuffer();
        
        printf("\n");
    }
}

/*
 * Função: exibirTerritorios
 * 
 * Exibe na tela todos os territórios cadastrados com suas respectivas
 * informações (nome, cor do exército e quantidade de tropas).
 * 
 * Parâmetros:
 *   territorios[] - vetor de structs contendo os dados dos territórios
 *   quantidade - número de territórios a serem exibidos
 */
void exibirTerritorios(Territorio territorios[], int quantidade) {
    printf("\n=== TERRITORIOS CADASTRADOS ===\n");
    printf("================================\n\n");
    
    // Laço para percorrer e exibir cada território
    for (int i = 0; i < quantidade; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome........: %s\n", territorios[i].nome);
        printf("  Cor.........: %s\n", territorios[i].cor);
        printf("  Tropas......: %d\n", territorios[i].tropas);
        printf("--------------------------------\n");
    }
}

/*
 * Função: main
 * 
 * Função principal do programa. Coordena o fluxo de execução:
 * 1. Declara o vetor de structs para armazenar os territórios
 * 2. Chama a função de cadastro
 * 3. Chama a função de exibição dos dados
 * 
 * Retorno: 0 indica execução bem-sucedida
 */
int main() {
    // Declaração do vetor de structs para armazenar os territórios
    Territorio territorios[MAX_TERRITORIOS];
    
    // Cadastro dos territórios
    cadastrarTerritorios(territorios, MAX_TERRITORIOS);
    
    // Exibição dos territórios cadastrados
    exibirTerritorios(territorios, MAX_TERRITORIOS);
    
    printf("\nCadastro concluido com sucesso!\n");
    
    return 0;
}