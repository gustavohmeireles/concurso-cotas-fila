# 📝 Exemplos de Uso

Esta pasta contém exemplos práticos de como utilizar e estender o sistema.

## Arquivos Disponíveis

### exemplo_custom.c
Exemplo de uso customizado com interface interativa que demonstra:
- Menu de opções para o usuário
- Cadastro interativo de candidatos
- Validação de entrada de dados
- Exibição formatada de resultados
- Estatísticas detalhadas de distribuição

#### Como Compilar
```bash
cd examples
gcc -Wall -I../include exemplo_custom.c ../src/fila.c ../src/regras.c -o exemplo_custom
```

#### Como Executar
```bash
./exemplo_custom
```

#### Funcionalidades
1. **Cadastrar candidato** - Adiciona novos candidatos ao sistema
2. **Processar convocações** - Executa o algoritmo de distribuição de cotas
3. **Exibir estatísticas** - Mostra análise detalhada da distribuição
4. **Sair** - Encerra o programa

### candidatos_exemplo.csv
Arquivo CSV de exemplo com dados de candidatos para testes.

**Formato:**
```csv
id,nome,modalidade
1,Ana Silva,AC
2,João Santos,PPI
3,Maria Costa,PCD
```

**Campos:**
- `id`: Identificador único (inteiro)
- `nome`: Nome completo do candidato (texto)
- `modalidade`: AC, PPI ou PCD

## Criando Seus Próprios Exemplos

### Exemplo Básico
```c
#include <stdio.h>
#include "../include/fila.h"
#include "../include/regras.h"

int main() {
    Fila fila;
    inicializarFila(&fila);
    
    Candidato c = {1, "Nome Exemplo", "AC"};
    enfileirar(&fila, c);
    
    if (!filaVazia(&fila)) {
        Candidato removido = desenfileirar(&fila);
        printf("Candidato: %s\n", removido.nome);
    }
    
    return 0;
}
```

### Compilação de Exemplos Personalizados
```bash
# Método 1: Usando GCC diretamente
gcc -Wall -I../include seu_exemplo.c ../src/fila.c ../src/regras.c -o seu_exemplo

# Método 2: Adicionando ao Makefile
# Edite o Makefile e adicione uma nova regra
```

## Ideias para Novos Exemplos

1. **Leitura de CSV** - Ler candidatos de arquivo CSV
2. **Exportação de Resultados** - Salvar convocações em arquivo
3. **Modo Batch** - Processar múltiplos concursos
4. **Relatório PDF** - Gerar relatório visual (requer biblioteca)
5. **API REST** - Expor funcionalidade via HTTP (requer biblioteca)
6. **Interface Web** - Frontend para o sistema (requer framework)
7. **Banco de Dados** - Persistência com SQLite (requer biblioteca)
8. **Logs Detalhados** - Sistema de logging avançado

## Contribuindo com Exemplos

Tem um exemplo interessante? Contribua!

1. Crie seu exemplo na pasta `examples/`
2. Adicione documentação clara no código
3. Atualize este README
4. Faça um Pull Request

Veja [CONTRIBUTING.md](../docs/CONTRIBUTING.md) para mais detalhes.

## Recursos Adicionais

- [API Documentation](../docs/API.md)
- [Architecture Guide](../docs/ARCHITECTURE.md)
- [Main README](../README.md)

## Suporte

Dúvidas sobre os exemplos? Abra uma Issue:
https://github.com/seu-usuario/concurso-cotas-fila/issues
