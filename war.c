/*
 * Sistema Completo do Jogo War - Com Missões Estratégicas
 * 
 * Este programa implementa o jogo War completo com:
 * - Cadastro dinâmico de territórios
 * - Sistema de batalha com dados aleatórios
 * - Missões estratégicas para cada jogador
 * - Verificação de condições de vitória
 * 
 * Autor: Sistema War
 * Data: 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definições de constantes
#define MAX_MISSOES 5
#define TAM_MISSAO 150

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
 * Struct Jogador
 * 
 * Estrutura que representa um jogador no jogo War.
 * Contém informações sobre nome, cor e sua missão estratégica.
 */
typedef struct {
    char nome[30];        // Nome do jogador
    char cor[10];         // Cor do exército do jogador
    char* missao;         // Ponteiro para a missão alocada dinamicamente
} Jogador;

/*
 * Função: limparBuffer
 * 
 * Limpa o buffer de entrada para evitar problemas com leituras subsequentes.
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * Função: cadastrarTerritorios
 * 
 * Realiza o cadastro de todos os territórios, solicitando ao usuário
 * que informe nome, cor do exército e quantidade de tropas.
 * 
 * Parâmetros:
 *   territorios - ponteiro para o vetor de structs alocado dinamicamente
 *   quantidade - número de territórios a serem cadastrados
 */
void cadastrarTerritorios(Territorio* territorios, int quantidade) {
    printf("\n=== CADASTRO DE TERRITORIOS - JOGO WAR ===\n");
    printf("=========================================\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("--- Territorio %d de %d ---\n", i + 1, quantidade);
        
        printf("Digite o nome do territorio: ");
        scanf("%29s", (territorios + i)->nome);
        limparBuffer();
        
        printf("Digite a cor do exercito: ");
        scanf("%9s", (territorios + i)->cor);
        limparBuffer();
        
        printf("Digite o numero de tropas: ");
        scanf("%d", &(territorios + i)->tropas);
        limparBuffer();
        
        printf("\n");
    }
}

/*
 * Função: exibirTerritorios
 * 
 * Exibe todos os territórios cadastrados com suas informações.
 * 
 * Parâmetros:
 *   territorios - ponteiro para o vetor de structs
 *   quantidade - número de territórios a serem exibidos
 */
void exibirTerritorios(Territorio* territorios, int quantidade) {
    printf("\n=== MAPA DE TERRITORIOS ===\n");
    printf("===========================\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("[%d] %s\n", i + 1, (territorios + i)->nome);
        printf("    Cor.........: %s\n", (territorios + i)->cor);
        printf("    Tropas......: %d\n", (territorios + i)->tropas);
        printf("---------------------------\n");
    }
}

/*
 * Função: rolarDado
 * 
 * Simula a rolagem de um dado de 6 faces.
 * 
 * Retorno: número inteiro entre 1 e 6
 */
int rolarDado() {
    return (rand() % 6) + 1;
}

/*
 * Função: atacar
 * 
 * Simula um ataque entre dois territórios usando dados aleatórios.
 * Implementa as regras de batalha do jogo War.
 * 
 * Parâmetros:
 *   atacante - ponteiro para o território atacante (passagem por referência)
 *   defensor - ponteiro para o território defensor (passagem por referência)
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n=== SIMULACAO DE BATALHA ===\n");
    printf("Atacante: %s (%s) com %d tropas\n", 
           atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) com %d tropas\n", 
           defensor->nome, defensor->cor, defensor->tropas);
    printf("\n");
    
    // Valida se o atacante tem tropas suficientes
    if (atacante->tropas < 2) {
        printf("ATAQUE INVALIDO! O atacante precisa de pelo menos 2 tropas.\n");
        return;
    }
    
    // Rolagem de dados para batalha
    int dadoAtacante = rolarDado();
    int dadoDefensor = rolarDado();
    
    printf("Rolagem de dados:\n");
    printf("  Atacante rolou: %d\n", dadoAtacante);
    printf("  Defensor rolou: %d\n", dadoDefensor);
    printf("\n");
    
    // Determina o vencedor
    if (dadoAtacante > dadoDefensor) {
        printf(">>> VITORIA DO ATACANTE! <<<\n");
        printf("O territorio %s foi conquistado!\n", defensor->nome);
        
        // Conquista: muda a cor e transfere tropas
        strcpy(defensor->cor, atacante->cor);
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        
        printf("Tropas transferidas: %d\n", tropasTransferidas);
        printf("Tropas restantes no atacante: %d\n", atacante->tropas);
        
    } else {
        printf(">>> VITORIA DO DEFENSOR! <<<\n");
        printf("O ataque foi repelido!\n");
        
        // Atacante perde uma tropa
        atacante->tropas--;
        printf("O atacante perdeu 1 tropa. Tropas restantes: %d\n", 
               atacante->tropas);
    }
    
    printf("============================\n");
}

/*
 * Função: atribuirMissao
 * 
 * Sorteia uma missão aleatória do vetor de missões disponíveis
 * e a atribui ao jogador através de cópia de string.
 * 
 * Parâmetros:
 *   destino - ponteiro para onde a missão será copiada (passagem por referência)
 *   missoes - array de strings com as missões disponíveis (passagem por valor)
 *   totalMissoes - quantidade total de missões disponíveis
 */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    // Sorteia um índice aleatório
    int indiceSorteado = rand() % totalMissoes;
    
    // Copia a missão sorteada para o destino
    strcpy(destino, missoes[indiceSorteado]);
}

/*
 * Função: exibirMissao
 * 
 * Exibe a missão de um jogador de forma formatada.
 * A missão é passada por valor (não há modificação).
 * 
 * Parâmetros:
 *   nomeJogador - nome do jogador
 *   missao - string contendo a missão (passagem por valor)
 */
void exibirMissao(char nomeJogador[], char* missao) {
    printf("\n+--------------------------------------------------+\n");
    printf("| MISSAO ESTRATEGICA - %s\n", nomeJogador);
    printf("+--------------------------------------------------+\n");
    printf("| %s\n", missao);
    printf("+--------------------------------------------------+\n");
}

/*
 * Função: contarTerritoriosPorCor
 * 
 * Conta quantos territórios pertencem a uma determinada cor.
 * 
 * Parâmetros:
 *   mapa - ponteiro para o vetor de territórios
 *   tamanho - quantidade de territórios
 *   cor - cor a ser contada
 * 
 * Retorno: número de territórios da cor especificada
 */
int contarTerritoriosPorCor(Territorio* mapa, int tamanho, char* cor) {
    int contador = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strcmp((mapa + i)->cor, cor) == 0) {
            contador++;
        }
    }
    return contador;
}

/*
 * Função: verificarTerritoriosConsecutivos
 * 
 * Verifica se uma cor possui territórios cadastrados em sequência.
 * (Simplificação: verifica se há N territórios da mesma cor em posições adjacentes)
 * 
 * Parâmetros:
 *   mapa - ponteiro para o vetor de territórios
 *   tamanho - quantidade de territórios
 *   cor - cor a ser verificada
 *   quantidade - quantidade mínima de territórios consecutivos
 * 
 * Retorno: 1 se encontrou a sequência, 0 caso contrário
 */
int verificarTerritoriosConsecutivos(Territorio* mapa, int tamanho, char* cor, int quantidade) {
    int consecutivos = 0;
    
    for (int i = 0; i < tamanho; i++) {
        if (strcmp((mapa + i)->cor, cor) == 0) {
            consecutivos++;
            if (consecutivos >= quantidade) {
                return 1;
            }
        } else {
            consecutivos = 0;
        }
    }
    return 0;
}

/*
 * Função: verificarMissao
 * 
 * Verifica se uma missão específica foi cumprida analisando o estado do mapa.
 * Implementa lógica simplificada para diferentes tipos de missões.
 * 
 * Parâmetros:
 *   missao - string contendo a missão a ser verificada (passagem por referência para leitura)
 *   mapa - ponteiro para o vetor de territórios
 *   tamanho - quantidade de territórios
 *   corJogador - cor do jogador que está sendo verificado
 * 
 * Retorno: 1 se a missão foi cumprida, 0 caso contrário
 */
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* corJogador) {
    // Verifica diferentes tipos de missões usando strstr para buscar palavras-chave
    
    // Missão: Conquistar 3 territórios consecutivos
    if (strstr(missao, "3 territorios consecutivos") != NULL) {
        return verificarTerritoriosConsecutivos(mapa, tamanho, corJogador, 3);
    }
    
    // Missão: Conquistar pelo menos 5 territórios
    if (strstr(missao, "5 territorios") != NULL) {
        int total = contarTerritoriosPorCor(mapa, tamanho, corJogador);
        return (total >= 5) ? 1 : 0;
    }
    
    // Missão: Dominar 50% do mapa
    if (strstr(missao, "50% do mapa") != NULL) {
        int total = contarTerritoriosPorCor(mapa, tamanho, corJogador);
        return (total >= tamanho / 2) ? 1 : 0;
    }
    
    // Missão: Eliminar todas as tropas de uma cor específica
    if (strstr(missao, "Eliminar") != NULL) {
        // Verifica se existe alguma cor completamente eliminada
        // (lógica simplificada: verifica se o jogador conquistou todos os territórios)
        int total = contarTerritoriosPorCor(mapa, tamanho, corJogador);
        return (total == tamanho) ? 1 : 0;
    }
    
    // Missão: Acumular 20 tropas em territórios controlados
    if (strstr(missao, "20 tropas") != NULL) {
        int totalTropas = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp((mapa + i)->cor, corJogador) == 0) {
                totalTropas += (mapa + i)->tropas;
            }
        }
        return (totalTropas >= 20) ? 1 : 0;
    }
    
    return 0; // Missão não cumprida por padrão
}

/*
 * Função: realizarAtaque
 * 
 * Coordena o processo de ataque, com validações e execução da batalha.
 * 
 * Parâmetros:
 *   territorios - ponteiro para o vetor de territórios
 *   quantidade - número total de territórios
 */
void realizarAtaque(Territorio* territorios, int quantidade) {
    int indiceAtacante, indiceDefensor;
    
    printf("\n=== INICIAR ATAQUE ===\n");
    exibirTerritorios(territorios, quantidade);
    
    printf("\nEscolha o numero do territorio ATACANTE: ");
    scanf("%d", &indiceAtacante);
    limparBuffer();
    
    if (indiceAtacante < 1 || indiceAtacante > quantidade) {
        printf("Territorio invalido!\n");
        return;
    }
    
    printf("Escolha o numero do territorio DEFENSOR: ");
    scanf("%d", &indiceDefensor);
    limparBuffer();
    
    if (indiceDefensor < 1 || indiceDefensor > quantidade) {
        printf("Territorio invalido!\n");
        return;
    }
    
    // Converte para índices do array
    indiceAtacante--;
    indiceDefensor--;
    
    // Validações
    if (indiceAtacante == indiceDefensor) {
        printf("ERRO: Nao e possivel atacar o proprio territorio!\n");
        return;
    }
    
    if (strcmp((territorios + indiceAtacante)->cor, 
               (territorios + indiceDefensor)->cor) == 0) {
        printf("ERRO: Nao e possivel atacar um territorio da mesma cor!\n");
        return;
    }
    
    // Executa o ataque
    atacar(territorios + indiceAtacante, territorios + indiceDefensor);
}

/*
 * Função: verificarVitoria
 * 
 * Verifica se algum jogador cumpriu sua missão e declara o vencedor.
 * 
 * Parâmetros:
 *   jogadores - array de jogadores
 *   numJogadores - quantidade de jogadores
 *   mapa - ponteiro para o vetor de territórios
 *   tamanhoMapa - quantidade de territórios
 * 
 * Retorno: 1 se algum jogador venceu, 0 caso contrário
 */
int verificarVitoria(Jogador* jogadores, int numJogadores, Territorio* mapa, int tamanhoMapa) {
    for (int i = 0; i < numJogadores; i++) {
        if (verificarMissao(jogadores[i].missao, mapa, tamanhoMapa, jogadores[i].cor)) {
            printf("\n");
            printf("*************************************************\n");
            printf("*                                               *\n");
            printf("*          >>> TEMOS UM VENCEDOR! <<<          *\n");
            printf("*                                               *\n");
            printf("*************************************************\n");
            printf("\n");
            printf("Jogador: %s (%s)\n", jogadores[i].nome, jogadores[i].cor);
            printf("Missao cumprida: %s\n", jogadores[i].missao);
            printf("\n");
            printf("*************************************************\n");
            return 1;
        }
    }
    return 0;
}

/*
 * Função: liberarMemoria
 * 
 * Libera toda a memória alocada dinamicamente no programa.
 * Essencial para evitar vazamento de memória.
 * 
 * Parâmetros:
 *   mapa - ponteiro para o vetor de territórios
 *   jogadores - array de jogadores
 *   numJogadores - quantidade de jogadores
 */
void liberarMemoria(Territorio* mapa, Jogador* jogadores, int numJogadores) {
    // Libera a memória das missões de cada jogador
    for (int i = 0; i < numJogadores; i++) {
        if (jogadores[i].missao != NULL) {
            free(jogadores[i].missao);
        }
    }
    
    // Libera o array de jogadores
    if (jogadores != NULL) {
        free(jogadores);
    }
    
    // Libera o mapa de territórios
    if (mapa != NULL) {
        free(mapa);
    }
    
    printf("\nMemoria liberada com sucesso!\n");
}

/*
 * Função: main
 * 
 * Função principal que coordena todo o fluxo do jogo War.
 * Implementa:
 * - Inicialização do sistema
 * - Cadastro de jogadores e territórios
 * - Atribuição de missões
 * - Loop principal do jogo
 * - Verificação de vitória
 * - Liberação de memória
 * 
 * Retorno: 0 indica execução bem-sucedida
 */
int main() {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    int numTerritorios, numJogadores;
    Territorio* territorios = NULL;
    Jogador* jogadores = NULL;
    
    // Vetor de missões pré-definidas
    char* missoes[MAX_MISSOES] = {
        "Conquistar 3 territorios consecutivos no mapa",
        "Conquistar pelo menos 5 territorios de qualquer posicao",
        "Dominar 50% do mapa (metade dos territorios)",
        "Eliminar todas as tropas de pelo menos uma cor inimiga",
        "Acumular 20 tropas ou mais em seus territorios controlados"
    };
    
    printf("====================================\n");
    printf("   BEM-VINDO AO JOGO WAR - v3.0\n");
    printf("     EDICAO MISSOES ESTRATEGICAS\n");
    printf("====================================\n\n");
    
    // Cadastro de jogadores
    printf("Digite o numero de jogadores: ");
    scanf("%d", &numJogadores);
    limparBuffer();
    
    if (numJogadores <= 0) {
        printf("Numero de jogadores invalido!\n");
        return 1;
    }
    
    // Aloca memória para os jogadores
    jogadores = (Jogador*) malloc(numJogadores * sizeof(Jogador));
    if (jogadores == NULL) {
        printf("ERRO: Falha na alocacao de memoria para jogadores!\n");
        return 1;
    }
    
    // Cadastra cada jogador
    for (int i = 0; i < numJogadores; i++) {
        printf("\n--- Jogador %d ---\n", i + 1);
        printf("Nome: ");
        scanf("%29s", jogadores[i].nome);
        limparBuffer();
        
        printf("Cor do exercito: ");
        scanf("%9s", jogadores[i].cor);
        limparBuffer();
        
        // Aloca memória para a missão do jogador
        jogadores[i].missao = (char*) malloc(TAM_MISSAO * sizeof(char));
        if (jogadores[i].missao == NULL) {
            printf("ERRO: Falha na alocacao de memoria para missao!\n");
            liberarMemoria(NULL, jogadores, i);
            return 1;
        }
        
        // Atribui uma missão aleatória
        atribuirMissao(jogadores[i].missao, missoes, MAX_MISSOES);
        
        // Exibe a missão do jogador
        exibirMissao(jogadores[i].nome, jogadores[i].missao);
    }
    
    // Cadastro de territórios
    printf("\n\nDigite o numero de territorios: ");
    scanf("%d", &numTerritorios);
    limparBuffer();
    
    if (numTerritorios <= 0) {
        printf("Numero de territorios invalido!\n");
        liberarMemoria(NULL, jogadores, numJogadores);
        return 1;
    }
    
    // Aloca memória para os territórios
    territorios = (Territorio*) calloc(numTerritorios, sizeof(Territorio));
    if (territorios == NULL) {
        printf("ERRO: Falha na alocacao de memoria para territorios!\n");
        liberarMemoria(NULL, jogadores, numJogadores);
        return 1;
    }
    
    printf("Memoria alocada com sucesso!\n");
    
    // Cadastra os territórios
    cadastrarTerritorios(territorios, numTerritorios);
    
    // Menu principal do jogo
    int opcao;
    int jogoAtivo = 1;
    
    do {
        printf("\n====================================\n");
        printf("           MENU PRINCIPAL\n");
        printf("====================================\n");
        printf("1 - Exibir mapa de territorios\n");
        printf("2 - Exibir missoes dos jogadores\n");
        printf("3 - Realizar ataque\n");
        printf("4 - Verificar status das missoes\n");
        printf("0 - Sair do jogo\n");
        printf("====================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                exibirTerritorios(territorios, numTerritorios);
                break;
                
            case 2:
                printf("\n=== MISSOES DOS JOGADORES ===\n");
                for (int i = 0; i < numJogadores; i++) {
                    exibirMissao(jogadores[i].nome, jogadores[i].missao);
                }
                break;
                
            case 3:
                realizarAtaque(territorios, numTerritorios);
                // Verifica se algum jogador venceu após o ataque
                if (verificarVitoria(jogadores, numJogadores, territorios, numTerritorios)) {
                    jogoAtivo = 0;
                }
                break;
                
            case 4:
                printf("\n=== VERIFICACAO DE MISSOES ===\n");
                for (int i = 0; i < numJogadores; i++) {
                    printf("\nJogador: %s (%s)\n", jogadores[i].nome, jogadores[i].cor);
                    printf("Missao: %s\n", jogadores[i].missao);
                    
                    if (verificarMissao(jogadores[i].missao, territorios, 
                                       numTerritorios, jogadores[i].cor)) {
                        printf("Status: [CUMPRIDA!] \n");
                    } else {
                        printf("Status: [Em andamento]\n");
                    }
                }
                break;
                
            case 0:
                printf("\nEncerrando o jogo...\n");
                jogoAtivo = 0;
                break;
                
            default:
                printf("\nOpcao invalida!\n");
        }
        
    } while (jogoAtivo);
    
    // Libera toda a memória alocada
    liberarMemoria(territorios, jogadores, numJogadores);
    
    printf("\nObrigado por jogar WAR!\n");
    printf("====================================\n");
    
    return 0;
}