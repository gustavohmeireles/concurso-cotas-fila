# 🎯 Sistema de Convocação de Candidatos com Cotas

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

Sistema desenvolvido em C para gerenciamento de convocação de candidatos em concursos públicos brasileiros, com implementação automatizada das regras de cotas raciais (PPI) e cotas para pessoas com deficiência (PCD) conforme legislação vigente.

## 📋 Índice

- [Descrição](#-descrição)
- [Características](#-características)
- [Requisitos](#-requisitos)
- [Instalação](#-instalação)
- [Compilação](#-compilação)
- [Uso](#-uso)
- [Estrutura do Projeto](#-estrutura-do-projeto)
- [Regras de Cotas](#-regras-de-cotas)
- [Exemplos](#-exemplos)
- [Documentação Técnica](#-documentação-técnica)
- [Contribuindo](#-contribuindo)
- [Licença](#-licença)
- [Autor](#-autor)

## 🎓 Descrição

Este sistema implementa um algoritmo eficiente para convocação de candidatos respeitando as cotas estabelecidas pela legislação brasileira:

- **Ampla Concorrência (AC)**: Vagas gerais do concurso
- **Cotas Raciais (PPI)**: Pretos, Pardos e Indígenas
- **Cotas para PCD**: Pessoas com Deficiência

O sistema utiliza estruturas de dados do tipo **fila (FIFO)** para garantir a ordem cronológica de inscrição e aplica automaticamente as regras de distribuição de vagas por modalidade.

## ✨ Características

- ✅ Implementação de filas dinâmicas com alocação de memória otimizada
- ✅ Aplicação automática de regras de cotas conforme legislação
- ✅ Gestão independente de três categorias de candidatos
- ✅ Relatório detalhado de convocação com posição final
- ✅ Código modular e bem documentado
- ✅ Sem dependências externas (apenas biblioteca padrão C)
- ✅ Gerenciamento adequado de memória (sem memory leaks)

## 🔧 Requisitos

### Sistema Operacional
- Linux (Ubuntu, Debian, Fedora, CentOS, etc.)
- macOS
- Windows (com MinGW ou WSL)

### Software Necessário
```bash
gcc >= 5.0      # Compilador C
make >= 3.81    # Sistema de build
```

### Verificar Instalação
```bash
# Verificar versão do GCC
gcc --version

# Verificar versão do Make
make --version
```

### Instalar Dependências (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install build-essential
```

### Instalar Dependências (Fedora/CentOS/RHEL)
```bash
sudo dnf groupinstall "Development Tools"
# ou em versões antigas:
sudo yum groupinstall "Development Tools"
```

## 📦 Instalação

### Método 1: Clone do Repositório (Recomendado)
```bash
# Clonar o repositório
git clone https://github.com/seu-usuario/concurso-cotas-fila.git

# Entrar no diretório
cd concurso-cotas-fila
```

### Método 2: Download Direto
```bash
# Download do ZIP
wget https://github.com/seu-usuario/concurso-cotas-fila/archive/main.zip

# Extrair
unzip main.zip
cd concurso-cotas-fila-main
```

## 🔨 Compilação

### Compilação Simples
```bash
make
```

Este comando irá:
1. Criar o diretório `bin/` (se não existir)
2. Compilar todos os arquivos `.c` da pasta `src/`
3. Gerar o executável `bin/concurso_cotas`

### Compilação e Execução
```bash
make run
```

### Limpeza de Arquivos Compilados
```bash
# Remove arquivos .o e executável
make clean

# Remove também o diretório bin/
make distclean
```

### Outros Comandos Úteis
```bash
# Informações sobre o projeto
make info

# Criar pacote de distribuição
make dist

# Instalar no sistema (requer sudo)
make install

# Desinstalar do sistema
make uninstall

# Ver todos os comandos disponíveis
make help
```

## 🚀 Uso

### Execução Básica
```bash
./bin/concurso_cotas
```

### Saída Esperada
```
Pos Nome Modalidade ID
1 Ana Silva AC 1
2 Joao Santos AC 2
3 Pedro Costa PPI 3
4 Maria Oliveira AC 4
5 Julia Lima AC 5
6 Carlos Souza AC 6
7 Beatriz Alves AC 7
8 Marcos Correia PPI 8
...
21 Wesley Gomes PPI 21
22 Fulano Teixeira AC 22
```

### Modificando os Dados de Entrada

Edite o arquivo `src/main.c` e altere o array `candidatos[]`:

```c
Candidato candidatos[] = {
    {1, "Seu Nome", "AC"},
    {2, "Outro Nome", "PPI"},
    {3, "Mais Um", "PCD"},
    // Adicione mais candidatos aqui
};
```

Após modificar, recompile:
```bash
make clean
make
```

## 📁 Estrutura do Projeto

```
concurso-cotas-fila/
│
├── src/                    # Código fonte
│   ├── main.c             # Programa principal
│   ├── fila.c             # Implementação da estrutura de fila
│   └── regras.c           # Implementação das regras de cotas
│
├── include/               # Arquivos de cabeçalho
│   ├── candidato.h        # Definição da estrutura Candidato
│   ├── fila.h             # Interface da fila
│   └── regras.h           # Interface das regras
│
├── bin/                   # Executáveis (gerado automaticamente)
│   └── concurso_cotas     # Executável compilado
│
├── docs/                  # Documentação adicional
│   ├── ARCHITECTURE.md    # Arquitetura do sistema
│   ├── API.md             # Documentação das funções
│   └── CONTRIBUTING.md    # Guia de contribuição
│
├── examples/              # Exemplos de uso
│   └── exemplo_custom.c   # Exemplo de uso customizado
│
├── Makefile              # Script de compilação
├── README.md             # Este arquivo
├── LICENSE               # Licença do projeto
└── .gitignore           # Arquivos ignorados pelo Git
```

## 📐 Regras de Cotas

### Cotas PPI (Pretos, Pardos e Indígenas)
- **Frequência**: A cada 5 vagas
- **Posições**: 3, 8, 13, 18, 23, 28, ...
- **Cálculo**: `(posicao - 3) % 5 == 0`

### Cotas PCD (Pessoas com Deficiência)
- **Frequência**: A cada 20 vagas
- **Primeira vaga**: Posição 21
- **Posições**: 21, 41, 61, 81, ...
- **Cálculo**: `posicao == 21 || (posicao > 21 && (posicao - 21) % 20 == 0)`

### Ordem de Prioridade
1. **Primeiro**: Verifica se é vaga PCD
2. **Segundo**: Verifica se é vaga PPI
3. **Terceiro**: Ampla concorrência (AC)

### Exemplo de Distribuição (primeiras 25 vagas)
| Posição | Modalidade | Tipo       |
|---------|-----------|------------|
| 1       | AC        | Ampla      |
| 2       | AC        | Ampla      |
| 3       | **PPI**   | Cota Racial|
| 4       | AC        | Ampla      |
| 5       | AC        | Ampla      |
| ...     | ...       | ...        |
| 8       | **PPI**   | Cota Racial|
| ...     | ...       | ...        |
| 21      | **PCD**   | Deficiência|

## 💡 Exemplos

### Exemplo 1: Uso Básico

```bash
# Compilar
make

# Executar
./bin/concurso_cotas
```

### Exemplo 2: Adicionar Novos Candidatos

Edite `src/main.c`:

```c
Candidato candidatos[] = {
    {1, "João Silva", "AC"},
    {2, "Maria Santos", "PPI"},
    {3, "José Oliveira", "AC"},
    {4, "Ana Costa", "PCD"},
    {5, "Carlos Souza", "AC"},
    // Adicione mais aqui
};
```

### Exemplo 3: Integração com Arquivo CSV (Futuro)

Consulte `examples/exemplo_custom.c` para ver como ler dados de arquivos externos.

## 📚 Documentação Técnica

### Estruturas de Dados

#### Candidato
```c
typedef struct {
    int id;              // Identificador único
    char nome[50];       // Nome completo do candidato
    char modalidade[10]; // "AC", "PPI" ou "PCD"
} Candidato;
```

#### Fila (FIFO - First In, First Out)
```c
typedef struct No {
    Candidato dado;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
    No *fim;
} Fila;
```

### Funções Principais

#### Gerenciamento de Fila
- `void inicializarFila(Fila *f)` - Inicializa uma fila vazia
- `int filaVazia(Fila *f)` - Verifica se a fila está vazia
- `void enfileirar(Fila *f, Candidato c)` - Adiciona candidato ao fim da fila
- `Candidato desenfileirar(Fila *f)` - Remove e retorna candidato do início da fila

#### Regras de Cotas
- `int ehVagaPPI(int posicao)` - Verifica se a posição é destinada a cota PPI
- `int ehVagaPCD(int posicao)` - Verifica se a posição é destinada a cota PCD

### Complexidade Computacional

| Operação | Complexidade |
|----------|-------------|
| Enfileirar | O(1) |
| Desenfileirar | O(1) |
| Verificar vaga | O(1) |
| Processar n candidatos | O(n) |

### Gerenciamento de Memória

O sistema utiliza alocação dinâmica com `malloc()` e libera adequadamente com `free()`:

```c
// Alocação
No *novo = (No*) malloc(sizeof(No));

// Uso
novo->dado = c;
novo->prox = NULL;

// Liberação
free(aux);
```

## 🤝 Contribuindo

Contribuições são bem-vindas! Para contribuir:

1. Faça um Fork do projeto
2. Crie uma branch para sua feature (`git checkout -b feature/NovaFuncionalidade`)
3. Commit suas mudanças (`git commit -m 'Adiciona nova funcionalidade'`)
4. Push para a branch (`git push origin feature/NovaFuncionalidade`)
5. Abra um Pull Request

### Diretrizes de Código

- Siga o padrão de código existente
- Comente código complexo
- Atualize a documentação quando necessário
- Adicione testes quando aplicável

### Reportando Bugs

Use a aba [Issues](https://github.com/seu-usuario/concurso-cotas-fila/issues) para reportar bugs. Inclua:

- Descrição clara do problema
- Passos para reproduzir
- Comportamento esperado vs. observado
- Sistema operacional e versão do GCC

## 📄 Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para detalhes.

```
MIT License

Copyright (c) 2026 Gustavo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files...
```

## 👤 Autor

**Gustavo**
- DBA Oracle
- Especialista em Sistemas de Gestão

---

## 🔗 Links Úteis

- [Documentação do GCC](https://gcc.gnu.org/onlinedocs/)
- [Tutorial de Make](https://www.gnu.org/software/make/manual/)
- [Estruturas de Dados em C](https://www.ime.usp.br/~pf/algoritmos/)
- [Legislação sobre Cotas](http://www.planalto.gov.br/ccivil_03/_ato2011-2014/2012/lei/l12711.htm)

---

## 📊 Status do Projeto

![Status](https://img.shields.io/badge/Status-Stable-success)
![Version](https://img.shields.io/badge/Version-1.0.0-blue)
![Maintenance](https://img.shields.io/badge/Maintained-Yes-green)

---

⭐ Se este projeto foi útil para você, considere dar uma estrela no GitHub!

**Desenvolvido com ❤️ para processos seletivos mais justos e transparentes**
