#include <stdio.h>
#include <string.h>
#include "fila.h"
#include "regras.h"

int main() {
    Fila ac, ppi, pcd, final;
    inicializarFila(&ac);
    inicializarFila(&ppi);
    inicializarFila(&pcd);
    inicializarFila(&final);

    Candidato candidatos[] = {
        {1,"Ana Silva","AC"}, {2,"Joao Santos","AC"}, {3,"Pedro Costa","PPI"},
        {4,"Maria Oliveira","AC"}, {5,"Julia Lima","AC"}, {6,"Carlos Souza","AC"},
        {7,"Beatriz Alves","AC"}, {8,"Marcos Correia","PPI"}, {9,"Lucas Pereira","AC"},
        {10,"Fernanda Rocha","AC"}, {11,"Rafael Martins","AC"}, {12,"Juliana Ferreira","AC"},
        {13,"Bruno Cardoso","AC"}, {14,"Amanda Ribeiro","AC"}, {15,"Diego Nascimento","PCD"},
        {16,"Camila Azevedo","AC"}, {17,"Thiago Barbosa","AC"}, {18,"Patricia Dias","AC"},
        {19,"Rodrigo Monteiro","AC"}, {20,"Larissa Castro","AC"}, {21,"Wesley Gomes","PPI"},
        {22,"Fulano Teixeira","AC"}
    };

    int total = sizeof(candidatos)/sizeof(Candidato);

    for(int i=0;i<total;i++){
        enfileirar(&ac,candidatos[i]);
        if(strcmp(candidatos[i].modalidade,"PPI")==0) enfileirar(&ppi,candidatos[i]);
        if(strcmp(candidatos[i].modalidade,"PCD")==0) enfileirar(&pcd,candidatos[i]);
    }

    printf("Pos Nome Modalidade ID\n");

    for(int pos=1;pos<=total;pos++){
        Candidato c;
        if(ehVagaPCD(pos)&&!filaVazia(&pcd)) c=desenfileirar(&pcd);
        else if(ehVagaPPI(pos)&&!filaVazia(&ppi)) c=desenfileirar(&ppi);
        else c=desenfileirar(&ac);
        enfileirar(&final,c);
        printf("%d %s %s %d\n",pos,c.nome,c.modalidade,c.id);
    }
    return 0;
}
