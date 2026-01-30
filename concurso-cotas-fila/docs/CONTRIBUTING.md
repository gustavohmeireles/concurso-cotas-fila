# 🤝 Guia de Contribuição

Obrigado por considerar contribuir com o Sistema de Convocação de Candidatos com Cotas! Este documento fornece diretrizes para ajudá-lo a contribuir de forma efetiva.

## 📋 Índice

- [Código de Conduta](#código-de-conduta)
- [Como Posso Contribuir?](#como-posso-contribuir)
- [Configuração do Ambiente](#configuração-do-ambiente)
- [Processo de Desenvolvimento](#processo-de-desenvolvimento)
- [Padrões de Código](#padrões-de-código)
- [Processo de Pull Request](#processo-de-pull-request)
- [Reportando Bugs](#reportando-bugs)
- [Sugerindo Melhorias](#sugerindo-melhorias)

---

## Código de Conduta

Este projeto e todos os participantes devem aderir aos seguintes princípios:

- **Respeito**: Trate todos com respeito e consideração
- **Inclusão**: Seja acolhedor com contribuidores de todos os níveis
- **Profissionalismo**: Mantenha discussões técnicas e construtivas
- **Colaboração**: Trabalhe em conjunto para melhorar o projeto

---

## Como Posso Contribuir?

Existem várias formas de contribuir:

### 1. 🐛 Reportar Bugs
- Verifique se o bug já foi reportado
- Inclua detalhes sobre como reproduzir
- Forneça informações sobre seu ambiente

### 2. 💡 Sugerir Melhorias
- Descreva claramente a melhoria proposta
- Explique por que seria útil
- Considere impactos em funcionalidades existentes

### 3. 📝 Melhorar Documentação
- Corrigir erros de digitação
- Adicionar exemplos
- Melhorar clareza das explicações

### 4. 💻 Contribuir com Código
- Implementar novas funcionalidades
- Corrigir bugs
- Melhorar performance
- Adicionar testes

---

## Configuração do Ambiente

### Requisitos
```bash
# Ubuntu/Debian
sudo apt update
sudo apt install build-essential git

# Fedora/CentOS
sudo dnf groupinstall "Development Tools"
sudo dnf install git

# macOS
xcode-select --install
brew install gcc
```

### Clone e Configuração
```bash
# Fazer fork do repositório no GitHub
# Depois clonar seu fork:
git clone https://github.com/SEU-USUARIO/concurso-cotas-fila.git
cd concurso-cotas-fila

# Adicionar repositório original como upstream
git remote add upstream https://github.com/USUARIO-ORIGINAL/concurso-cotas-fila.git

# Verificar configuração
git remote -v
```

### Compilação Inicial
```bash
# Compilar o projeto
make

# Executar testes
make run

# Verificar por memory leaks (requer valgrind)
sudo apt install valgrind  # Ubuntu/Debian
valgrind --leak-check=full ./bin/concurso_cotas
```

---

## Processo de Desenvolvimento

### 1. Criar uma Branch

Sempre crie uma branch para suas mudanças:

```bash
# Atualizar main
git checkout main
git pull upstream main

# Criar branch descritiva
git checkout -b feature/nome-da-funcionalidade
# ou
git checkout -b bugfix/descricao-do-bug
# ou
git checkout -b docs/melhoria-documentacao
```

**Nomenclatura de Branches**:
- `feature/` - Novas funcionalidades
- `bugfix/` - Correções de bugs
- `hotfix/` - Correções urgentes
- `docs/` - Melhorias na documentação
- `refactor/` - Refatoração de código
- `test/` - Adição de testes

### 2. Fazer Mudanças

```bash
# Editar arquivos conforme necessário
nano src/fila.c

# Compilar e testar frequentemente
make clean && make run
```

### 3. Commit das Mudanças

Use mensagens de commit claras e descritivas:

```bash
git add src/fila.c
git commit -m "feat: adiciona verificação de memória em enfileirar"
```

**Formato de Mensagens de Commit**:
```
<tipo>: <descrição curta>

<descrição detalhada opcional>

<referências opcionais>
```

**Tipos de Commit**:
- `feat`: Nova funcionalidade
- `fix`: Correção de bug
- `docs`: Mudanças na documentação
- `style`: Formatação, ponto e vírgula, etc.
- `refactor`: Refatoração de código
- `test`: Adição de testes
- `chore`: Tarefas de manutenção

**Exemplos**:
```bash
git commit -m "feat: adiciona suporte para leitura de CSV"
git commit -m "fix: corrige memory leak em desenfileirar"
git commit -m "docs: atualiza README com novos exemplos"
git commit -m "refactor: melhora legibilidade de ehVagaPPI"
git commit -m "test: adiciona testes unitários para fila"
```

### 4. Push para seu Fork

```bash
git push origin feature/nome-da-funcionalidade
```

---

## Padrões de Código

### Estilo de Código C

#### Indentação
```c
// Use 4 espaços (não tabs)
void funcao() {
    if (condicao) {
        printf("4 espaços\n");
    }
}
```

#### Nomenclatura
```c
// Funções: camelCase ou snake_case
void inicializarFila(Fila *f);
void inicializar_fila(Fila *f);  // Também aceitável

// Estruturas: PascalCase
typedef struct {
    int campo;
} MinhaStruct;

// Constantes: UPPER_CASE
#define MAX_CANDIDATOS 1000
#define TAMANHO_NOME 50

// Variáveis: snake_case ou camelCase
int total_candidatos;
int totalCandidatos;  // Também aceitável
```

#### Comentários
```c
// Comentários de linha única para explicações curtas

/*
 * Comentários de bloco para explicações longas
 * ou documentação de funções complexas
 */

/**
 * Documentação estilo Doxygen para funções públicas
 * @param f Ponteiro para a fila
 * @return 1 se vazia, 0 caso contrário
 */
int filaVazia(Fila *f);
```

#### Espaçamento
```c
// Espaços ao redor de operadores
int resultado = a + b;
if (x == y) {
    // ...
}

// Espaço após vírgulas
funcao(a, b, c);

// Sem espaço entre nome da função e parênteses
funcao(parametro);
```

#### Chaves
```c
// Chave de abertura na mesma linha (estilo K&R)
void funcao() {
    if (condicao) {
        // código
    } else {
        // código
    }
}

// Chave de fechamento em linha própria
```

### Verificação de Erros

Sempre verifique retornos críticos:

```c
// ✓ CORRETO
No *novo = (No*) malloc(sizeof(No));
if (novo == NULL) {
    fprintf(stderr, "Erro: falha na alocação de memória\n");
    exit(EXIT_FAILURE);
}

// ✓ CORRETO
if (!filaVazia(&fila)) {
    Candidato c = desenfileirar(&fila);
}

// ✗ EVITAR - sem verificação
No *novo = (No*) malloc(sizeof(No));
novo->dado = c;  // Pode causar segfault se malloc falhou
```

### Documentação de Código

```c
/**
 * Adiciona um candidato ao final da fila
 * 
 * Aloca memória dinamicamente para um novo nó e adiciona
 * o candidato ao final da estrutura de fila.
 * 
 * @param f Ponteiro para a fila (não pode ser NULL)
 * @param c Candidato a ser adicionado (passado por valor)
 * 
 * @note O candidato é copiado, não é necessário manter
 *       a referência original após a chamada
 * 
 * @warning Se malloc falhar, o comportamento é indefinido
 * 
 * Complexidade: O(1)
 * 
 * Exemplo:
 * @code
 * Fila fila;
 * inicializarFila(&fila);
 * Candidato c = {1, "João", "AC"};
 * enfileirar(&fila, c);
 * @endcode
 */
void enfileirar(Fila *f, Candidato c);
```

---

## Processo de Pull Request

### Checklist Antes de Enviar

- [ ] Código compila sem erros ou warnings
- [ ] Código segue os padrões do projeto
- [ ] Adicionei/atualizei documentação relevante
- [ ] Adicionei/atualizei testes se aplicável
- [ ] Testei em múltiplos cenários
- [ ] Mensagens de commit são claras
- [ ] Branch está atualizada com upstream/main

### Criar Pull Request

1. Vá para seu fork no GitHub
2. Clique em "Pull Request"
3. Selecione sua branch e a branch `main` do repositório original
4. Preencha o template de PR:

```markdown
## Descrição
Descrição clara do que foi alterado e por quê.

## Tipo de Mudança
- [ ] Bug fix
- [ ] Nova funcionalidade
- [ ] Melhoria de performance
- [ ] Documentação
- [ ] Outro (especifique):

## Como Testar
1. Compile o projeto: `make`
2. Execute: `./bin/concurso_cotas`
3. Verifique que...

## Checklist
- [ ] Código compila sem warnings
- [ ] Testes passam
- [ ] Documentação atualizada
- [ ] Segue padrões do projeto

## Screenshots (se aplicável)
```

### Revisão de Código

- Responda aos comentários de forma construtiva
- Faça mudanças solicitadas em commits adicionais
- Marque comentários como resolvidos quando apropriado
- Seja paciente - revisões levam tempo

---

## Reportando Bugs

Use o template abaixo ao reportar bugs:

```markdown
**Descrição do Bug**
Descrição clara e concisa do que está acontecendo de errado.

**Como Reproduzir**
Passos para reproduzir o comportamento:
1. Compile com '...'
2. Execute com '...'
3. Faça '...'
4. Veja o erro

**Comportamento Esperado**
O que você esperava que acontecesse.

**Comportamento Observado**
O que realmente aconteceu.

**Screenshots**
Se aplicável, adicione screenshots.

**Ambiente:**
 - OS: [e.g. Ubuntu 22.04]
 - GCC Version: [e.g. 11.3.0]
 - Make Version: [e.g. 4.3]

**Contexto Adicional**
Qualquer outra informação relevante.

**Possível Solução (opcional)**
Se você tem ideia de como corrigir.
```

---

## Sugerindo Melhorias

Use o template abaixo para sugestões:

```markdown
**A sugestão está relacionada a um problema?**
Descrição clara do problema. Ex: "É frustrante quando..."

**Descreva a solução que você gostaria**
Descrição clara e concisa do que você quer que aconteça.

**Descreva alternativas consideradas**
Outras soluções ou funcionalidades que você considerou.

**Contexto Adicional**
Qualquer outro contexto, screenshots, ou exemplos.

**Benefícios Esperados**
Como isso melhoraria o projeto.
```

---

## Tipos de Contribuições Específicas

### Adicionando Nova Funcionalidade

1. Discuta a funcionalidade em uma Issue primeiro
2. Aguarde aprovação antes de implementar
3. Mantenha mudanças focadas e atômicas
4. Adicione testes
5. Atualize documentação

### Corrigindo Bugs

1. Referência a Issue do bug (se existir)
2. Adicione teste que falha antes da correção
3. Implemente a correção
4. Verifique que o teste agora passa
5. Verifique que não quebrou outros testes

### Melhorando Documentação

1. Verifique gramática e ortografia
2. Mantenha tom consistente
3. Adicione exemplos quando útil
4. Certifique-se que código de exemplo funciona
5. Atualize índices se necessário

---

## Recursos Úteis

- [Git Basics](https://git-scm.com/book/pt-br/v2)
- [C Programming Guide](https://www.ime.usp.br/~pf/algoritmos/)
- [Markdown Guide](https://www.markdownguide.org/)
- [Writing Good Commit Messages](https://chris.beams.io/posts/git-commit/)

---

## Dúvidas?

Se tiver dúvidas sobre como contribuir:

1. Verifique a documentação existente
2. Procure em Issues fechadas
3. Abra uma nova Issue com a tag `question`
4. Seja específico e forneça contexto

---

**Obrigado por contribuir! 🎉**

Sua contribuição ajuda a tornar processos seletivos mais justos e transparentes.
