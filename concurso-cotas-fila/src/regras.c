#include "regras.h"

int ehVagaPPI(int posicao) {
    return (posicao - 3) % 5 == 0;
}

int ehVagaPCD(int posicao) {
    return posicao == 21 || (posicao > 21 && (posicao - 21) % 20 == 0);
}
