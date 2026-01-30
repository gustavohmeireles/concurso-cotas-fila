# 📚 Documentação da API

Esta documentação detalha todas as funções, estruturas e tipos de dados disponíveis no sistema.

## Índice

- [Estruturas de Dados](#estruturas-de-dados)
- [Módulo: fila.h](#módulo-filah)
- [Módulo: regras.h](#módulo-egrash)
- [Exemplos de Uso](#exemplos-de-uso)

---

## Estruturas de Dados

### Candidato

```c
typedef struct {
    int id;
    char nome[50];
    char modalidade[10];
} Candidato;
```

**Descrição**: Representa um candidato inscrito no concurso.

**Campos**:
- `id` (int): Identificador único do candidato. Deve ser um número positivo único.
- `nome` (char[50]): Nome completo do candidato. Máximo de 49 caracteres + '\0'.
- `modalidade` (char[10]): Modalidade de inscrição. Valores válidos: "AC", "PPI", "PCD".

**Exemplo de Uso**:
```c
Candidato c1 = {1, "João Silva", "AC"};
Candidato c2 = {2, "Maria Santos", "PPI"};
Candidato c3 = {3, "José Oliveira", "PCD"};
```

**Notas**:
- O campo `modalidade` deve ser preenchido exatamente como "AC", "PPI" ou "PCD"
- Espaços em branco no final podem causar problemas na comparação
- Recomenda-se sempre usar string literals ou `strncpy` seguro

---

### No

```c
typedef struct No {
    Candidato dado;
    struct No *prox;
} No;
```

**Descrição**: Nó de uma lista encadeada simples. Uso interno da fila.

**Campos**:
- `dado` (Candidato): Dados do candidato armazenado neste nó.
- `prox` (struct No*): Ponteiro para o próximo nó da lista, ou NULL se for o último.

**Notas**:
- Esta estrutura é de uso interno. Aplicações não devem manipulá-la diretamente.
- A alocação e liberação são gerenciadas pelas funções da fila.

---

### Fila

```c
typedef struct {
    No *inicio;
    No *fim;
} Fila;
```

**Descrição**: Estrutura de dados Fila (FIFO - First In, First Out).

**Campos**:
- `inicio` (No*): Ponteiro para o primeiro nó da fila (próximo a ser removido).
- `fim` (No*): Ponteiro para o último nó da fila (último adicionado).

**Invariantes**:
- Se `inicio == NULL`, então `fim == NULL` (fila vazia)
- Se `inicio != NULL`, então `fim != NULL` (fila não vazia)
- Em fila com 1 elemento: `inicio == fim`

**Exemplo de Declaração**:
```c
Fila minhaFila;
inicializarFila(&minhaFila);
```

---

## Módulo: fila.h

### inicializarFila

```c
void inicializarFila(Fila *f);
```

**Descrição**: Inicializa uma fila vazia.

**Parâmetros**:
- `f` (Fila*): Ponteiro para a estrutura Fila a ser inicializada.

**Comportamento**:
- Define `f->inicio` como NULL
- Define `f->fim` como NULL

**Pré-condições**:
- `f` não deve ser NULL

**Pós-condições**:
- A fila está vazia
- `filaVazia(f)` retorna verdadeiro (1)

**Exemplo**:
```c
Fila fila_ac;
inicializarFila(&fila_ac);

if (filaVazia(&fila_ac)) {
    printf("Fila inicializada corretamente!\n");
}
```

**Notas**:
- Deve ser chamada antes de qualquer outra operação na fila
- Não aloca memória dinamicamente (apenas inicializa ponteiros)
- É seguro chamar múltiplas vezes (reinicializa a fila)

---

### filaVazia

```c
int filaVazia(Fila *f);
```

**Descrição**: Verifica se a fila está vazia.

**Parâmetros**:
- `f` (Fila*): Ponteiro para a fila a ser verificada.

**Retorno**:
- `1` (verdadeiro) se a fila está vazia
- `0` (falso) se a fila contém elementos

**Complexidade**: O(1) - tempo constante

**Exemplo**:
```c
Fila fila;
inicializarFila(&fila);

if (filaVazia(&fila)) {
    printf("A fila está vazia.\n");
} else {
    printf("A fila contém elementos.\n");
}
```

**Notas**:
- Verifica apenas se `f->inicio == NULL`
- Não modifica a fila
- É seguro chamar a qualquer momento

---

### enfileirar

```c
void enfileirar(Fila *f, Candidato c);
```

**Descrição**: Adiciona um candidato ao final da fila.

**Parâmetros**:
- `f` (Fila*): Ponteiro para a fila onde o candidato será adicionado.
- `c` (Candidato): Candidato a ser adicionado (passado por valor).

**Comportamento**:
1. Aloca memória para um novo nó
2. Copia os dados do candidato para o nó
3. Adiciona o nó ao final da fila
4. Atualiza o ponteiro `fim`

**Complexidade**: O(1) - tempo constante

**Pré-condições**:
- `f` não deve ser NULL
- Deve haver memória disponível para alocação

**Pós-condições**:
- O candidato está na fila
- `filaVazia(f)` retorna falso (0)
- O candidato está na última posição

**Exemplo**:
```c
Fila fila_ppi;
inicializarFila(&fila_ppi);

Candidato c1 = {1, "Ana Costa", "PPI"};
Candidato c2 = {2, "Bruno Silva", "PPI"};

enfileirar(&fila_ppi, c1);
enfileirar(&fila_ppi, c2);

// Ordem na fila: c1 -> c2
```

**Tratamento de Erros**:
- Se `malloc` falhar, o programa pode ter comportamento indefinido
- Em produção, recomenda-se verificar se `malloc` retornou NULL

**Melhorias Sugeridas**:
```c
void enfileirar(Fila *f, Candidato c) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        fprintf(stderr, "Erro: memória insuficiente\n");
        exit(EXIT_FAILURE);
    }
    // ... resto do código
}
```

---

### desenfileirar

```c
Candidato desenfileirar(Fila *f);
```

**Descrição**: Remove e retorna o candidato do início da fila.

**Parâmetros**:
- `f` (Fila*): Ponteiro para a fila de onde o candidato será removido.

**Retorno**:
- (Candidato): O candidato que estava no início da fila.

**Comportamento**:
1. Salva referência ao primeiro nó
2. Copia os dados do candidato
3. Atualiza o ponteiro `inicio` para o próximo nó
4. Se a fila ficou vazia, atualiza `fim` para NULL
5. Libera a memória do nó removido
6. Retorna o candidato

**Complexidade**: O(1) - tempo constante

**Pré-condições**:
- `f` não deve ser NULL
- A fila NÃO deve estar vazia (comportamento indefinido caso contrário)

**Pós-condições**:
- O primeiro candidato foi removido
- A memória do nó foi liberada
- Se a fila tinha 1 elemento, agora está vazia

**Exemplo**:
```c
Fila fila;
inicializarFila(&fila);

Candidato c1 = {1, "João", "AC"};
Candidato c2 = {2, "Maria", "AC"};

enfileirar(&fila, c1);
enfileirar(&fila, c2);

if (!filaVazia(&fila)) {
    Candidato removido = desenfileirar(&fila);
    printf("Removido: %s (ID: %d)\n", removido.nome, removido.id);
    // Saída: Removido: João (ID: 1)
}
```

**⚠️ IMPORTANTE - Verificação de Fila Vazia**:
```c
// SEMPRE verifique antes de desenfileirar!
if (!filaVazia(&fila)) {
    Candidato c = desenfileirar(&fila);
    // usar c...
} else {
    printf("Erro: tentativa de desenfileirar fila vazia!\n");
}
```

**Comportamento Indefinido**:
- Chamar `desenfileirar` em fila vazia causa segmentation fault
- Não há verificação interna na implementação atual

---

## Módulo: regras.h

### ehVagaPPI

```c
int ehVagaPPI(int posicao);
```

**Descrição**: Verifica se uma posição é destinada à cota PPI (Pretos, Pardos e Indígenas).

**Parâmetros**:
- `posicao` (int): Número da posição a ser verificada (deve ser ≥ 1).

**Retorno**:
- `1` (verdadeiro) se a posição é destinada a cota PPI
- `0` (falso) caso contrário

**Regra Implementada**:
- Primeira vaga PPI: posição 3
- Vagas subsequentes: a cada 5 posições (3, 8, 13, 18, 23...)

**Fórmula**: `(posicao - 3) % 5 == 0`

**Complexidade**: O(1) - tempo constante

**Exemplos**:
```c
ehVagaPPI(1);   // Retorna 0 (falso)
ehVagaPPI(3);   // Retorna 1 (verdadeiro)
ehVagaPPI(8);   // Retorna 1 (verdadeiro)
ehVagaPPI(13);  // Retorna 1 (verdadeiro)
ehVagaPPI(14);  // Retorna 0 (falso)
```

**Tabela de Verdade (primeiras 20 posições)**:
```
Posição | ehVagaPPI | Cálculo
--------|-----------|------------------
1       | 0         | (1-3)%5 = -2%5 ≠ 0
2       | 0         | (2-3)%5 = -1%5 ≠ 0
3       | 1         | (3-3)%5 = 0%5 = 0 ✓
4       | 0         | (4-3)%5 = 1%5 ≠ 0
5       | 0         | (5-3)%5 = 2%5 ≠ 0
6       | 0         | (6-3)%5 = 3%5 ≠ 0
7       | 0         | (7-3)%5 = 4%5 ≠ 0
8       | 1         | (8-3)%5 = 5%5 = 0 ✓
13      | 1         | (13-3)%5 = 10%5 = 0 ✓
18      | 1         | (18-3)%5 = 15%5 = 0 ✓
```

**Base Legal**:
- Lei 12.990/2014: reserva 20% das vagas para negros
- A cada 5 vagas, 1 é reservada (20%)

---

### ehVagaPCD

```c
int ehVagaPCD(int posicao);
```

**Descrição**: Verifica se uma posição é destinada à cota PCD (Pessoas com Deficiência).

**Parâmetros**:
- `posicao` (int): Número da posição a ser verificada (deve ser ≥ 1).

**Retorno**:
- `1` (verdadeiro) se a posição é destinada a cota PCD
- `0` (falso) caso contrário

**Regra Implementada**:
- Primeira vaga PCD: posição 21
- Vagas subsequentes: a cada 20 posições (21, 41, 61, 81...)

**Fórmula**: `posicao == 21 || (posicao > 21 && (posicao - 21) % 20 == 0)`

**Complexidade**: O(1) - tempo constante

**Exemplos**:
```c
ehVagaPCD(20);  // Retorna 0 (falso)
ehVagaPCD(21);  // Retorna 1 (verdadeiro)
ehVagaPCD(22);  // Retorna 0 (falso)
ehVagaPCD(41);  // Retorna 1 (verdadeiro)
ehVagaPCD(61);  // Retorna 1 (verdadeiro)
ehVagaPCD(81);  // Retorna 1 (verdadeiro)
```

**Tabela de Verdade**:
```
Posição | ehVagaPCD | Cálculo
--------|-----------|-------------------------
1-20    | 0         | Não atende nenhuma condição
21      | 1         | posicao == 21 ✓
22-40   | 0         | (22-21)%20 = 1%20 ≠ 0
41      | 1         | (41-21)%20 = 20%20 = 0 ✓
42-60   | 0         | Não múltiplo de 20
61      | 1         | (61-21)%20 = 40%20 = 0 ✓
81      | 1         | (81-21)%20 = 60%20 = 0 ✓
```

**Base Legal**:
- Lei 8.112/1990, Art. 5º, § 2º: reserva até 20% das vagas para PCD
- Lei 13.146/2015 (Estatuto da Pessoa com Deficiência)
- Mínimo de 5% em concursos com mais de 20 vagas

---

## Exemplos de Uso

### Exemplo 1: Criação e Uso Básico de Fila

```c
#include <stdio.h>
#include "fila.h"

int main() {
    // Criar e inicializar fila
    Fila fila_ac;
    inicializarFila(&fila_ac);
    
    // Criar candidatos
    Candidato c1 = {1, "Ana Silva", "AC"};
    Candidato c2 = {2, "Bruno Costa", "AC"};
    Candidato c3 = {3, "Carlos Lima", "AC"};
    
    // Adicionar candidatos
    enfileirar(&fila_ac, c1);
    enfileirar(&fila_ac, c2);
    enfileirar(&fila_ac, c3);
    
    // Processar fila
    while (!filaVazia(&fila_ac)) {
        Candidato c = desenfileirar(&fila_ac);
        printf("ID: %d, Nome: %s, Modalidade: %s\n", 
               c.id, c.nome, c.modalidade);
    }
    
    return 0;
}
```

**Saída esperada**:
```
ID: 1, Nome: Ana Silva, Modalidade: AC
ID: 2, Nome: Bruno Costa, Modalidade: AC
ID: 3, Nome: Carlos Lima, Modalidade: AC
```

---

### Exemplo 2: Verificação de Regras de Cotas

```c
#include <stdio.h>
#include "regras.h"

void mostrarDistribuicao(int total) {
    printf("Posição | Tipo de Vaga\n");
    printf("--------|-------------\n");
    
    for (int i = 1; i <= total; i++) {
        if (ehVagaPCD(i)) {
            printf("%7d | PCD\n", i);
        } else if (ehVagaPPI(i)) {
            printf("%7d | PPI\n", i);
        } else {
            printf("%7d | AC\n", i);
        }
    }
}

int main() {
    mostrarDistribuicao(25);
    return 0;
}
```

---

### Exemplo 3: Sistema Completo de Convocação

```c
#include <stdio.h>
#include <string.h>
#include "fila.h"
#include "regras.h"

int main() {
    // Inicializar filas
    Fila ac, ppi, pcd, final;
    inicializarFila(&ac);
    inicializarFila(&ppi);
    inicializarFila(&pcd);
    inicializarFila(&final);
    
    // Array de candidatos
    Candidato candidatos[] = {
        {1, "Ana Silva", "AC"},
        {2, "Bruno Costa", "PPI"},
        {3, "Carlos Lima", "AC"},
        {4, "Diana Santos", "PCD"},
        {5, "Eduardo Souza", "AC"}
    };
    
    int total = sizeof(candidatos) / sizeof(Candidato);
    
    // Distribuir candidatos nas filas apropriadas
    for (int i = 0; i < total; i++) {
        enfileirar(&ac, candidatos[i]);
        
        if (strcmp(candidatos[i].modalidade, "PPI") == 0) {
            enfileirar(&ppi, candidatos[i]);
        }
        
        if (strcmp(candidatos[i].modalidade, "PCD") == 0) {
            enfileirar(&pcd, candidatos[i]);
        }
    }
    
    // Processar convocações
    printf("Posição | Nome           | Modalidade | ID\n");
    printf("--------|----------------|------------|----\n");
    
    for (int pos = 1; pos <= total; pos++) {
        Candidato c;
        
        // Aplicar regras de cotas
        if (ehVagaPCD(pos) && !filaVazia(&pcd)) {
            c = desenfileirar(&pcd);
        } else if (ehVagaPPI(pos) && !filaVazia(&ppi)) {
            c = desenfileirar(&ppi);
        } else {
            c = desenfileirar(&ac);
        }
        
        enfileirar(&final, c);
        printf("%7d | %-14s | %-10s | %d\n", 
               pos, c.nome, c.modalidade, c.id);
    }
    
    return 0;
}
```

---

## Boas Práticas

### 1. Sempre Inicialize Filas
```c
// ✓ CORRETO
Fila f;
inicializarFila(&f);

// ✗ ERRADO (fila não inicializada)
Fila f;
enfileirar(&f, candidato);
```

### 2. Verifique Fila Vazia Antes de Desenfileirar
```c
// ✓ CORRETO
if (!filaVazia(&fila)) {
    Candidato c = desenfileirar(&fila);
}

// ✗ ERRADO (pode causar segmentation fault)
Candidato c = desenfileirar(&fila);
```

### 3. Use strcmp para Comparar Strings
```c
// ✓ CORRETO
if (strcmp(c.modalidade, "PPI") == 0) {
    // ...
}

// ✗ ERRADO (compara endereços, não conteúdo)
if (c.modalidade == "PPI") {
    // ...
}
```

### 4. Libere Memória (se aplicável)
```c
// Após usar todas as filas, libere a memória
while (!filaVazia(&fila)) {
    desenfileirar(&fila);  // Já libera automaticamente
}
```

---

## Referências

- [Documentação de Estruturas de Dados](ARCHITECTURE.md)
- [Lei 12.990/2014 - Cotas Raciais](http://www.planalto.gov.br/ccivil_03/_ato2011-2014/2014/lei/l12990.htm)
- [Lei 8.112/1990 - Regime Jurídico dos Servidores Públicos](http://www.planalto.gov.br/ccivil_03/leis/l8112cons.htm)

---

**Última atualização**: Janeiro 2026  
**Versão**: 1.0.0
