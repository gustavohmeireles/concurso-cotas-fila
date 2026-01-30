#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "regras.h"

// Função para imprimir linha divisória
void imprimirLinha(int tamanho) {
    for(int i = 0; i < tamanho; i++) printf("-");
    printf("\n");
}

int main() {
    Fila ac, ppi, pcd, final;
    inicializarFila(&ac);
    inicializarFila(&ppi);
    inicializarFila(&pcd);
    inicializarFila(&final);

    Candidato candidatos[] = {
        // Posições 1-10
        {1,"Ana Silva","AC"}, {2,"Joao Santos","AC"}, {3,"Maria Oliveira","PPI"},
        {4,"Pedro Costa","AC"}, {5,"Julia Lima","AC"}, {6,"Carlos Souza","AC"},
        {7,"Beatriz Alves","AC"}, {8,"Marcos Correia","PPI"}, {9,"Lucas Pereira","AC"},
        {10,"Fernanda Rocha","AC"},
        
        // Posições 11-20
        {11,"Rafael Martins","AC"}, {12,"Juliana Ferreira","AC"}, {13,"Bruno Cardoso","PPI"},
        {14,"Amanda Ribeiro","AC"}, {15,"Diego Nascimento","AC"}, {16,"Camila Azevedo","AC"},
        {17,"Thiago Barbosa","AC"}, {18,"Patricia Dias","PPI"}, {19,"Larissa Castro","AC"},
        {20,"Rodrigo Monteiro","AC"},
        
        // Posições 21-30 (21=PCD)
        {21,"Fulano Teixeira","AC"}, {22,"Wesley Gomes","PCD"}, {23,"Fernando Santos","PPI"},
        {24,"Mariana Lima","AC"}, {25,"Ricardo Silva","AC"}, {26,"Isabela Rocha","AC"},
        {27,"Gabriel Costa","AC"}, {28,"Leticia Dias","PPI"}, {29,"Felipe Almeida","AC"},
        {30,"Daniela Costa","AC"},
        
        // Posições 31-40
        {31,"Andre Santos","AC"}, {32,"Carolina Lima","AC"}, {33,"Henrique Costa","PPI"},
        {34,"Vanessa Santos","AC"}, {35,"Gustavo Lima","AC"}, {36,"Bianca Silva","AC"},
        {37,"Leonardo Rocha","AC"}, {38,"Natalia Costa","PPI"}, {39,"Vitor Lima","AC"},
        {40,"Renata Santos","AC"},
        
        // Posições 41-50 (41=PCD)
        {41,"Paulo Costa","PCD"}, {42,"Aline Lima","AC"}, {43,"Marcelo Silva","PPI"},
        {44,"Cristina Costa","AC"}, {45,"Rodrigo Santos","AC"}, {46,"Tatiana Silva","AC"},
        {47,"Eduardo Lima","AC"}, {48,"Priscila Costa","PPI"}, {49,"Fabio Santos","AC"},
        {50,"Silvia Lima","AC"},
        
        // Posições 51-60
        {51,"Roberto Souza","AC"}, {52,"Monica Pereira","AC"}, {53,"Alexandre Costa","PPI"},
        {54,"Claudia Silva","AC"}, {55,"Sergio Lima","AC"}, {56,"Luciana Santos","AC"},
        {57,"Marcio Oliveira","AC"}, {58,"Adriana Costa","PPI"}, {59,"Raul Silva","AC"},
        {60,"Simone Lima","AC"},
        
        // Posições 61-70 (61=PCD)
        {61,"Antonio Santos","PCD"}, {62,"Regina Lima","AC"}, {63,"Claudio Silva","PPI"},
        {64,"Marcia Santos","AC"}, {65,"Jorge Silva","AC"}, {66,"Eliane Lima","AC"},
        {67,"Luiz Costa","AC"}, {68,"Patricia Silva","PPI"}, {69,"Mauro Costa","AC"},
        {70,"Rosana Lima","AC"},
        
        // Posições 71-80
        {71,"Francisco Silva","AC"}, {72,"Maria Costa","AC"}, {73,"Jose Lima","PPI"},
        {74,"Ana Santos","AC"}, {75,"Ronaldo Costa","AC"}, {76,"Fernanda Santos","AC"},
        {77,"Paulo Costa","AC"}, {78,"Cristiane Lima","PPI"}, {79,"Marcos Santos","AC"},
        {80,"Luciane Silva","AC"},
        
        // Posições 81-90 (81=PCD)
        {81,"Joao Oliveira","PCD"}, {82,"Sandra Costa","AC"}, {83,"Ricardo Silva","PPI"},
        {84,"Vera Costa","AC"}, {85,"Paulo Lima","AC"}, {86,"Marisa Silva","AC"},
        {87,"Alberto Lima","AC"}, {88,"Helena Santos","PPI"}, {89,"Nelson Silva","AC"},
        {90,"Lucia Santos","AC"},
        
        // Posições 91-100
        {91,"Miguel Costa","AC"}, {92,"Teresa Silva","AC"}, {93,"Sergio Santos","PPI"},
        {94,"Alice Lima","AC"}, {95,"Hugo Costa","AC"}, {96,"Sofia Silva","AC"},
        {97,"Arthur Santos","AC"}, {98,"Laura Lima","PPI"}, {99,"Davi Costa","AC"},
        {100,"Livia Silva","AC"}
    };

    int total = sizeof(candidatos)/sizeof(Candidato);

    // Separar candidatos por modalidade
    for(int i=0; i<total; i++){
        if(strcmp(candidatos[i].modalidade,"AC")==0) {
            enfileirar(&ac, candidatos[i]);
        }
        if(strcmp(candidatos[i].modalidade,"PPI")==0) {
            enfileirar(&ppi, candidatos[i]);
        }
        if(strcmp(candidatos[i].modalidade,"PCD")==0) {
            enfileirar(&pcd, candidatos[i]);
        }
    }

    printf("Exemplo de saida:\n\n");

    // ========== LISTA AMPLA CONCORRÊNCIA ==========
    printf("========== LISTA AMPLA CONCORRENCIA ==========\n");
    printf("%-4s%-24s%-16s%-16s%-16s\n", "ID", "Nome", "Classif.Geral", "Classif.Negro", "Classif.PCD");
    imprimirLinha(76);
    
    // Criar cópia temporária da fila AC
    Fila temp_ac;
    inicializarFila(&temp_ac);
    Candidato lista_ac[100];
    int count_ac = 0;
    
    while(!filaVazia(&ac)) {
        Candidato c = desenfileirar(&ac);
        lista_ac[count_ac++] = c;
        enfileirar(&temp_ac, c);
    }
    
    for(int i=0; i<count_ac; i++) {
        printf("%-4d%-24s%-16d%-16d%-16d\n", i+1, lista_ac[i].nome, lista_ac[i].id, 0, 0);
    }
    ac = temp_ac;
    printf("\n");

    // ========== LISTA COTAS RACIAIS ==========
    printf("========== LISTA COTAS RACIAIS ==========\n");
    printf("%-4s%-24s%-16s%-16s%-16s\n", "ID", "Nome", "Classif.Geral", "Classif.Negro", "Classif.PCD");
    imprimirLinha(76);
    
    // Criar cópia temporária da fila PPI
    Fila temp_ppi;
    inicializarFila(&temp_ppi);
    Candidato lista_ppi[100];
    int count_ppi = 0;
    
    while(!filaVazia(&ppi)) {
        Candidato c = desenfileirar(&ppi);
        lista_ppi[count_ppi++] = c;
        enfileirar(&temp_ppi, c);
    }
    
    for(int i=0; i<count_ppi; i++) {
        printf("%-4d%-24s%-16d%-16d%-16d\n", i+1, lista_ppi[i].nome, lista_ppi[i].id, i+1, 0);
    }
    ppi = temp_ppi;
    printf("\n");

    // ========== LISTA PCD ==========
    printf("========== LISTA PCD ==========\n");
    printf("%-4s%-24s%-16s%-16s%-16s\n", "ID", "Nome", "Classif.Geral", "Classif.Negro", "Classif.PCD");
    imprimirLinha(76);
    
    // Criar cópia temporária da fila PCD
    Fila temp_pcd;
    inicializarFila(&temp_pcd);
    Candidato lista_pcd[100];
    int count_pcd = 0;
    
    while(!filaVazia(&pcd)) {
        Candidato c = desenfileirar(&pcd);
        lista_pcd[count_pcd++] = c;
        enfileirar(&temp_pcd, c);
    }
    
    for(int i=0; i<count_pcd; i++) {
        printf("%-4d%-24s%-16d%-16d%-16d\n", i+1, lista_pcd[i].nome, lista_pcd[i].id, 0, i+1);
    }
    pcd = temp_pcd;
    printf("\n");

    // ========== RESULTADO FINAL DA CONVOCAÇÃO ==========
    imprimirLinha(76);
    printf("%-40s%s\n", "", "RESULTADO FINAL DA CONVOCACAO");
    imprimirLinha(76);
    printf("%-4s%-30s%-26s%-16s\n", "Pos", "Nome", "Modalidade", "ID");
    imprimirLinha(76);

    for(int pos=1; pos<=total; pos++){
        Candidato c;
        char modalidade_final[30];
        
        if(ehVagaPCD(pos) && !filaVazia(&pcd)) {
            c = desenfileirar(&pcd);
            sprintf(modalidade_final, "Cota PCD");
        } 
        else if(ehVagaPPI(pos) && !filaVazia(&ppi)) {
            c = desenfileirar(&ppi);
            sprintf(modalidade_final, "Cota Racial");
        } 
        else {
            c = desenfileirar(&ac);
            sprintf(modalidade_final, "Ampla Concorrencia");
        }
        
        enfileirar(&final, c);
        printf("%-4d%-30s%-26s%-16d\n", pos, c.nome, modalidade_final, c.id);
    }
    
    return 0;
}
