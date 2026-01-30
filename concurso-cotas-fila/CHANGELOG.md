# Changelog

Todas as mudanças notáveis neste projeto serão documentadas neste arquivo.

O formato é baseado em [Keep a Changelog](https://keepachangelog.com/pt-BR/1.0.0/),
e este projeto adere ao [Versionamento Semântico](https://semver.org/lang/pt-BR/).

## [1.0.0] - 2026-01-30

### ✨ Adicionado
- Implementação inicial do sistema de convocação de candidatos
- Estrutura de dados Fila (FIFO) com alocação dinâmica
- Regras de cotas PPI (Pretos, Pardos e Indígenas)
- Regras de cotas PCD (Pessoas com Deficiência)
- Sistema de filas separadas por modalidade (AC, PPI, PCD)
- Programa principal com exemplo de uso
- Makefile para compilação automatizada
- Documentação completa em português
- README.md detalhado com exemplos
- Guia de contribuição (CONTRIBUTING.md)
- Documentação da arquitetura (ARCHITECTURE.md)
- Documentação da API (API.md)
- Licença MIT
- Exemplo de uso customizado com interface interativa
- Arquivo .gitignore para projetos C

### 📚 Documentação
- README.md: Documentação principal do projeto
- ARCHITECTURE.md: Arquitetura e design do sistema
- API.md: Referência completa das funções e estruturas
- CONTRIBUTING.md: Guia para contribuidores
- INSTALL.md: Guia rápido de instalação
- LICENSE: Licença MIT

### 🔧 Características Técnicas
- Complexidade O(1) para operações de fila
- Complexidade O(n) para processamento de n candidatos
- Gerenciamento adequado de memória (malloc/free)
- Código modular e bem estruturado
- Sem dependências externas (apenas stdlib C)
- Compatível com GCC 5.0+
- Suporte para Linux, macOS e Windows (via MinGW/WSL)

### 📊 Estatísticas
- Linhas de código: ~600 linhas (sem documentação)
- Módulos: 3 (fila, regras, main)
- Funções: 6 públicas
- Estruturas: 3 (Candidato, No, Fila)

## [Unreleased]

### 🎯 Planejado para Próximas Versões
- [ ] Leitura de candidatos de arquivo CSV
- [ ] Exportação de resultados para CSV/JSON
- [ ] Interface de linha de comando (CLI) com argumentos
- [ ] Validação robusta de dados de entrada
- [ ] Tratamento de erros com mensagens descritivas
- [ ] Testes unitários automatizados
- [ ] Integração contínua (CI/CD)
- [ ] Suporte a múltiplas configurações de cotas
- [ ] Geração de relatórios em PDF
- [ ] Modo verboso de execução
- [ ] Logs de auditoria
- [ ] Estatísticas avançadas
- [ ] Interface gráfica (GUI)
- [ ] Banco de dados SQLite

---

### Tipos de Mudanças
- **Adicionado** para novas funcionalidades
- **Alterado** para mudanças em funcionalidades existentes
- **Descontinuado** para funcionalidades que serão removidas
- **Removido** para funcionalidades removidas
- **Corrigido** para correções de bugs
- **Segurança** para vulnerabilidades corrigidas

### Links
- [1.0.0]: https://github.com/seu-usuario/concurso-cotas-fila/releases/tag/v1.0.0
