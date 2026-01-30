#include <stdlib.h>
#include "fila.h"

void inicializarFila(Fila *f) {
    f->inicio = f->fim = NULL;
}

int filaVazia(Fila *f) {
    return f->inicio == NULL;
}

void enfileirar(Fila *f, Candidato c) {
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = c;
    novo->prox = NULL;

    if (filaVazia(f)) {
        f->inicio = f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

Candidato desenfileirar(Fila *f) {
    No *aux = f->inicio;
    Candidato c = aux->dado;
    f->inicio = aux->prox;
    if (!f->inicio) f->fim = NULL;
    free(aux);
    return c;
}
