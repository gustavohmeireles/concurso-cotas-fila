#ifndef FILA_H
#define FILA_H

#include "candidato.h"

typedef struct No {
    Candidato dado;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
    No *fim;
} Fila;

void inicializarFila(Fila *f);
int filaVazia(Fila *f);
void enfileirar(Fila *f, Candidato c);
Candidato desenfileirar(Fila *f);

#endif
