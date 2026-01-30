/**
 * Exemplo de Uso Customizado
 * 
 * Este exemplo demonstra como estender o sistema básico
 * para incluir funcionalidades adicionais como:
 * - Entrada de dados interativa
 * - Estatísticas de distribuição
 * - Validação de entrada
 * 
 * Para compilar este exemplo:
 * gcc -Wall -I../include exemplo_custom.c ../src/fila.c ../src/regras.c -o exemplo_custom
 * 
 * Para executar:
 * ./exemplo_custom
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/candidato.h"
#include "../include/fila.h"
#include "../include/regras.h"

// Estrutura para estatísticas
typedef struct {
    int total_ac;
    int total_ppi;
    int total_pcd;
    int vagas_ac;
    int vagas_ppi;
    int vagas_pcd;
} Estatisticas;

/**
 * Inicializa estrutura de estatísticas
 */
void inicializarEstatisticas(Estatisticas *stats) {
    stats->total_ac = 0;
    stats->total_ppi = 0;
    stats->total_pcd = 0;
    stats->vagas_ac = 0;
    stats->vagas_ppi = 0;
    stats->vagas_pcd = 0;
}

/**
 * Valida modalidade inserida
 * Retorna 1 se válida, 0 se inválida
 */
int validarModalidade(const char *modalidade) {
    return (strcmp(modalidade, "AC") == 0 ||
            strcmp(modalidade, "PPI") == 0 ||
            strcmp(modalidade, "PCD") == 0);
}

/**
 * Lê dados de um candidato via entrada padrão
 */
Candidato lerCandidato(int id) {
    Candidato c;
    c.id = id;
    
    printf("\n--- Cadastro de Candidato #%d ---\n", id);
    
    // Ler nome
    printf("Nome completo: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    // Remover newline
    c.nome[strcspn(c.nome, "\n")] = 0;
    
    // Ler modalidade
    do {
        printf("Modalidade (AC/PPI/PCD): ");
        fgets(c.modalidade, sizeof(c.modalidade), stdin);
        c.modalidade[strcspn(c.modalidade, "\n")] = 0;
        
        if (!validarModalidade(c.modalidade)) {
            printf("Erro: Modalidade inválida! Use AC, PPI ou PCD.\n");
        }
    } while (!validarModalidade(c.modalidade));
    
    return c;
}

/**
 * Exibe estatísticas finais
 */
void exibirEstatisticas(Estatisticas *stats, int total) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║            ESTATÍSTICAS DE CONVOCAÇÃO                  ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║ Total de Candidatos Inscritos: %3d                    ║\n", total);
    printf("║                                                        ║\n");
    printf("║ Por Modalidade de Inscrição:                          ║\n");
    printf("║   • Ampla Concorrência (AC):   %3d (%5.1f%%)         ║\n", 
           stats->total_ac, (stats->total_ac * 100.0) / total);
    printf("║   • Cotas Raciais (PPI):       %3d (%5.1f%%)         ║\n", 
           stats->total_ppi, (stats->total_ppi * 100.0) / total);
    printf("║   • Pessoas com Deficiência:   %3d (%5.1f%%)         ║\n", 
           stats->total_pcd, (stats->total_pcd * 100.0) / total);
    printf("║                                                        ║\n");
    printf("║ Vagas Ocupadas por Modalidade:                        ║\n");
    printf("║   • Ampla Concorrência (AC):   %3d (%5.1f%%)         ║\n", 
           stats->vagas_ac, (stats->vagas_ac * 100.0) / total);
    printf("║   • Cotas Raciais (PPI):       %3d (%5.1f%%)         ║\n", 
           stats->vagas_ppi, (stats->vagas_ppi * 100.0) / total);
    printf("║   • Pessoas com Deficiência:   %3d (%5.1f%%)         ║\n", 
           stats->vagas_pcd, (stats->vagas_pcd * 100.0) / total);
    printf("╚════════════════════════════════════════════════════════╝\n");
}

/**
 * Exibe menu principal
 */
void exibirMenu() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║   SISTEMA DE CONVOCAÇÃO DE CANDIDATOS COM COTAS        ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║  1. Cadastrar candidato                                ║\n");
    printf("║  2. Processar convocações                              ║\n");
    printf("║  3. Exibir estatísticas                                ║\n");
    printf("║  4. Sair                                               ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
}

int main() {
    Fila ac, ppi, pcd, final;
    Estatisticas stats;
    Candidato *candidatos = NULL;
    int total = 0;
    int capacidade = 10;
    int opcao;
    int processado = 0;
    
    // Inicializar estruturas
    inicializarFila(&ac);
    inicializarFila(&ppi);
    inicializarFila(&pcd);
    inicializarFila(&final);
    inicializarEstatisticas(&stats);
    
    // Alocar array inicial
    candidatos = (Candidato*) malloc(capacidade * sizeof(Candidato));
    if (candidatos == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória\n");
        return 1;
    }
    
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║   BEM-VINDO AO SISTEMA DE GESTÃO DE CONCURSOS         ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    while (1) {
        exibirMenu();
        
        if (scanf("%d", &opcao) != 1) {
            printf("Erro: Entrada inválida!\n");
            while (getchar() != '\n');  // Limpar buffer
            continue;
        }
        getchar();  // Consumir newline
        
        switch (opcao) {
            case 1:  // Cadastrar candidato
                if (processado) {
                    printf("\nErro: Não é possível cadastrar após processar convocações!\n");
                    break;
                }
                
                // Expandir array se necessário
                if (total >= capacidade) {
                    capacidade *= 2;
                    Candidato *temp = (Candidato*) realloc(candidatos, 
                                                           capacidade * sizeof(Candidato));
                    if (temp == NULL) {
                        fprintf(stderr, "Erro: Falha ao expandir memória\n");
                        free(candidatos);
                        return 1;
                    }
                    candidatos = temp;
                }
                
                // Ler candidato
                candidatos[total] = lerCandidato(total + 1);
                total++;
                
                printf("\n✓ Candidato cadastrado com sucesso!\n");
                break;
                
            case 2:  // Processar convocações
                if (total == 0) {
                    printf("\nErro: Nenhum candidato cadastrado!\n");
                    break;
                }
                
                if (processado) {
                    printf("\nErro: Convocações já foram processadas!\n");
                    break;
                }
                
                // Distribuir candidatos nas filas
                for (int i = 0; i < total; i++) {
                    enfileirar(&ac, candidatos[i]);
                    
                    if (strcmp(candidatos[i].modalidade, "PPI") == 0) {
                        enfileirar(&ppi, candidatos[i]);
                        stats.total_ppi++;
                    } else if (strcmp(candidatos[i].modalidade, "PCD") == 0) {
                        enfileirar(&pcd, candidatos[i]);
                        stats.total_pcd++;
                    } else {
                        stats.total_ac++;
                    }
                }
                
                // Processar convocações
                printf("\n");
                printf("╔════════════════════════════════════════════════════════════════════╗\n");
                printf("║                    LISTA DE CONVOCAÇÃO                             ║\n");
                printf("╠════╦═══════════════════════════════╦═════════════╦═════════════════╣\n");
                printf("║ Nº ║ Nome                          ║ Modalidade  ║ ID              ║\n");
                printf("╠════╬═══════════════════════════════╬═════════════╬═════════════════╣\n");
                
                for (int pos = 1; pos <= total; pos++) {
                    Candidato c;
                    
                    if (ehVagaPCD(pos) && !filaVazia(&pcd)) {
                        c = desenfileirar(&pcd);
                        stats.vagas_pcd++;
                    } else if (ehVagaPPI(pos) && !filaVazia(&ppi)) {
                        c = desenfileirar(&ppi);
                        stats.vagas_ppi++;
                    } else {
                        c = desenfileirar(&ac);
                        stats.vagas_ac++;
                    }
                    
                    enfileirar(&final, c);
                    printf("║ %2d ║ %-29s ║ %-11s ║ %15d ║\n", 
                           pos, c.nome, c.modalidade, c.id);
                }
                
                printf("╚════╩═══════════════════════════════╩═════════════╩═════════════════╝\n");
                
                processado = 1;
                printf("\n✓ Convocações processadas com sucesso!\n");
                break;
                
            case 3:  // Exibir estatísticas
                if (!processado) {
                    printf("\nErro: Processe as convocações primeiro!\n");
                    break;
                }
                
                exibirEstatisticas(&stats, total);
                break;
                
            case 4:  // Sair
                printf("\nEncerrando sistema...\n");
                free(candidatos);
                return 0;
                
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    }
    
    return 0;
}
