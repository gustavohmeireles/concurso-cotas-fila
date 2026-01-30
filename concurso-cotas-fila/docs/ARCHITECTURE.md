# 🏗️ Arquitetura do Sistema

## Visão Geral

O sistema de Convocação de Candidatos com Cotas é desenvolvido em C puro, utilizando estruturas de dados dinâmicas e seguindo os princípios de programação modular.

## Diagrama de Componentes

```
┌─────────────────────────────────────────────────────┐
│                    main.c                           │
│              (Programa Principal)                   │
│  - Inicialização das filas                         │
│  - Carregamento de candidatos                      │
│  - Controle do fluxo de convocação                │
│  - Exibição de resultados                          │
└──────────────┬──────────────────┬───────────────────┘
               │                  │
               ▼                  ▼
    ┌──────────────────┐  ┌──────────────────┐
    │    regras.c      │  │     fila.c       │
    │ (Lógica Cotas)   │  │  (Estrutura)     │
    │                  │  │                  │
    │ - ehVagaPPI()    │  │ - inicializar()  │
    │ - ehVagaPCD()    │  │ - enfileirar()   │
    │                  │  │ - desenfileirar()│
    └──────────────────┘  └──────────────────┘
               │                  │
               ▼                  ▼
        ┌──────────────────────────────┐
        │      candidato.h             │
        │   (Estrutura de Dados)       │
        │                              │
        │   typedef struct {           │
        │       int id;                │
        │       char nome[50];         │
        │       char modalidade[10];   │
        │   } Candidato;               │
        └──────────────────────────────┘
```

## Módulos do Sistema

### 1. candidato.h
**Responsabilidade**: Define a estrutura básica de dados do candidato

**Estrutura**:
```c
typedef struct {
    int id;                  // Identificador único (chave primária)
    char nome[50];          // Nome completo (máx 50 caracteres)
    char modalidade[10];    // "AC", "PPI" ou "PCD"
} Candidato;
```

**Uso de Memória**:
- int: 4 bytes
- char[50]: 50 bytes
- char[10]: 10 bytes
- **Total**: ~64 bytes por candidato (com padding)

---

### 2. fila.h / fila.c
**Responsabilidade**: Implementação da estrutura de dados Fila (FIFO)

**Estruturas**:

```c
// Nó da lista encadeada
typedef struct No {
    Candidato dado;     // Dados do candidato
    struct No *prox;    // Ponteiro para próximo nó
} No;

// Estrutura da Fila
typedef struct {
    No *inicio;         // Ponteiro para o primeiro elemento
    No *fim;           // Ponteiro para o último elemento
} Fila;
```

**Funções**:

| Função | Complexidade | Descrição |
|--------|-------------|-----------|
| `inicializarFila()` | O(1) | Define início e fim como NULL |
| `filaVazia()` | O(1) | Verifica se início é NULL |
| `enfileirar()` | O(1) | Adiciona elemento no fim |
| `desenfileirar()` | O(1) | Remove elemento do início |

**Fluxo de Enfileiramento**:
```
Estado inicial: NULL
                ↓
Adicionar A:    [A] → NULL
                ↓
Adicionar B:    [A] → [B] → NULL
                ↓
Adicionar C:    [A] → [B] → [C] → NULL
                ↑inicio        ↑fim
```

**Fluxo de Desenfileiramento**:
```
Estado:         [A] → [B] → [C] → NULL
                ↓
Remover A:      [B] → [C] → NULL
                ↑inicio   ↑fim
```

---

### 3. regras.h / regras.c
**Responsabilidade**: Implementação das regras de distribuição de cotas

**Funções**:

#### ehVagaPPI(int posicao)
```c
int ehVagaPPI(int posicao) {
    return (posicao - 3) % 5 == 0;
}
```

**Lógica**: 
- Primeira vaga PPI: posição 3
- Próximas vagas: a cada 5 posições
- Sequência: 3, 8, 13, 18, 23, 28...

**Explicação Matemática**:
```
Posição 3:  (3-3) % 5 = 0 % 5 = 0 ✓
Posição 4:  (4-3) % 5 = 1 % 5 = 1 ✗
Posição 5:  (5-3) % 5 = 2 % 5 = 2 ✗
Posição 8:  (8-3) % 5 = 5 % 5 = 0 ✓
Posição 13: (13-3) % 5 = 10 % 5 = 0 ✓
```

#### ehVagaPCD(int posicao)
```c
int ehVagaPCD(int posicao) {
    return posicao == 21 || (posicao > 21 && (posicao - 21) % 20 == 0);
}
```

**Lógica**:
- Primeira vaga PCD: posição 21
- Próximas vagas: a cada 20 posições
- Sequência: 21, 41, 61, 81...

**Explicação Matemática**:
```
Posição 21: 21 == 21 ✓
Posição 41: (41 > 21) && (41-21) % 20 = 20 % 20 = 0 ✓
Posição 61: (61 > 21) && (61-21) % 20 = 40 % 20 = 0 ✓
Posição 81: (81 > 21) && (81-21) % 20 = 60 % 20 = 0 ✓
```

---

### 4. main.c
**Responsabilidade**: Coordenação geral do sistema

**Fluxo de Execução**:

```
┌─────────────────────────────────────┐
│ 1. Inicialização                    │
│    - Criar 4 filas (AC, PPI, PCD, final) │
└────────────┬────────────────────────┘
             │
             ▼
┌─────────────────────────────────────┐
│ 2. Carregamento de Dados            │
│    - Array de candidatos            │
│    - Distribuir por modalidade      │
└────────────┬────────────────────────┘
             │
             ▼
┌─────────────────────────────────────┐
│ 3. Processamento                    │
│    Para cada posição (1 até n):     │
│    ├─ Verificar se é vaga PCD       │
│    ├─ Senão, verificar se é PPI     │
│    └─ Senão, usar AC                │
└────────────┬────────────────────────┘
             │
             ▼
┌─────────────────────────────────────┐
│ 4. Exibição de Resultados           │
│    - Mostrar posição final          │
│    - Mostrar nome, modalidade, ID   │
└─────────────────────────────────────┘
```

**Pseudocódigo do Algoritmo Principal**:
```
PARA posição DE 1 ATÉ total_candidatos:
    SE ehVagaPCD(posição) E fila_pcd_não_vazia:
        candidato ← desenfileirar(fila_pcd)
    SENÃO SE ehVagaPPI(posição) E fila_ppi_não_vazia:
        candidato ← desenfileirar(fila_ppi)
    SENÃO:
        candidato ← desenfileirar(fila_ac)
    FIM SE
    
    enfileirar(fila_final, candidato)
    IMPRIMIR(posição, candidato)
FIM PARA
```

## Padrões de Projeto Utilizados

### 1. Modularização
- Separação clara de responsabilidades
- Cada módulo tem um propósito específico
- Interface bem definida através de headers (.h)

### 2. Abstração de Dados
- A estrutura `Fila` encapsula a implementação interna
- O usuário não precisa conhecer os detalhes da lista encadeada
- Interface simples: inicializar, enfileirar, desenfileirar

### 3. Separação de Lógica de Negócio
- Regras de cotas isoladas em módulo próprio
- Facilita manutenção e testes
- Permite mudanças nas regras sem afetar outras partes

## Considerações de Performance

### Uso de Memória
**Por candidato na fila**:
- Candidato: 64 bytes
- Ponteiro (No*): 8 bytes (64-bit)
- **Total**: ~72 bytes por candidato enfileirado

**Para 1000 candidatos**:
- Memória estimada: 72KB x 4 filas = ~288KB
- Overhead do sistema: mínimo

### Complexidade de Tempo

| Operação | Complexidade | Justificativa |
|----------|-------------|---------------|
| Carregar n candidatos | O(n) | Loop único |
| Processar n candidatos | O(n) | Loop único |
| Cada convocação | O(1) | Operações de fila constantes |
| **Total** | **O(n)** | Linear no número de candidatos |

### Otimizações Implementadas

1. **Filas separadas por modalidade**
   - Evita varredura de arrays
   - Acesso direto aos candidatos corretos

2. **Lista encadeada**
   - Sem realocação de memória
   - Crescimento dinâmico

3. **Verificação de regras O(1)**
   - Cálculo matemático direto
   - Sem loops ou recursão

## Extensibilidade

### Como Adicionar Novas Modalidades

1. Adicionar nova modalidade em `candidato.h`
2. Criar nova fila em `main.c`
3. Implementar função `ehVaga[MODALIDADE]()` em `regras.c`
4. Adicionar lógica de verificação no loop principal

Exemplo para modalidade "Indígena" (IN):

```c
// Em regras.c
int ehVagaIN(int posicao) {
    return (posicao - 2) % 10 == 0;  // Posições 2, 12, 22...
}

// Em main.c
Fila indigena;
inicializarFila(&indigena);

// No loop de processamento
if(ehVagaIN(pos) && !filaVazia(&indigena)) {
    c = desenfileirar(&indigena);
}
```

## Testes e Validação

### Casos de Teste Recomendados

1. **Teste com fila vazia**
   - Todas as vagas AC

2. **Teste com apenas PPI**
   - Preenchimento correto nas posições 3, 8, 13...

3. **Teste com apenas PCD**
   - Preenchimento correto nas posições 21, 41, 61...

4. **Teste misto**
   - Prioridade correta: PCD > PPI > AC

5. **Teste de memória**
   - Verificar com Valgrind
   - Confirmar ausência de memory leaks

### Comando para Teste de Memória
```bash
valgrind --leak-check=full --show-leak-kinds=all ./bin/concurso_cotas
```

## Possíveis Melhorias Futuras

1. **Entrada de Dados**
   - Leitura de arquivo CSV
   - Interface de linha de comando
   - Banco de dados SQLite

2. **Saída de Dados**
   - Exportação para CSV/JSON
   - Geração de relatórios PDF
   - Logs detalhados

3. **Validações**
   - Verificar modalidade válida
   - Validar dados de entrada
   - Tratamento de erros robusto

4. **Interface**
   - Menu interativo
   - Cores no terminal (ANSI)
   - Barra de progresso

5. **Testes Automatizados**
   - Suite de testes unitários
   - Testes de integração
   - CI/CD no GitHub Actions

---

**Última atualização**: Janeiro 2026  
**Versão do documento**: 1.0
