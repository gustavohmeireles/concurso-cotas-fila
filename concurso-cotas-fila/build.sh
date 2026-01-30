#!/bin/bash

# Script de Build para Sistema de Convocação de Candidatos com Cotas
# Autor: Gustavo
# Descrição: Script auxiliar para compilação, testes e instalação

set -e  # Sair se qualquer comando falhar

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Função para exibir mensagens coloridas
print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_error() {
    echo -e "${RED}✗ $1${NC}"
}

print_info() {
    echo -e "${BLUE}ℹ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠ $1${NC}"
}

# Função para verificar dependências
check_dependencies() {
    print_info "Verificando dependências..."
    
    if ! command -v gcc &> /dev/null; then
        print_error "GCC não encontrado!"
        echo "Instale com:"
        echo "  Ubuntu/Debian: sudo apt install build-essential"
        echo "  Fedora/CentOS: sudo dnf groupinstall 'Development Tools'"
        exit 1
    fi
    
    if ! command -v make &> /dev/null; then
        print_error "Make não encontrado!"
        echo "Instale com:"
        echo "  Ubuntu/Debian: sudo apt install make"
        echo "  Fedora/CentOS: sudo dnf install make"
        exit 1
    fi
    
    print_success "Todas as dependências estão instaladas"
    echo "  GCC version: $(gcc --version | head -n1)"
    echo "  Make version: $(make --version | head -n1)"
}

# Função para compilar o projeto
build() {
    print_info "Compilando o projeto..."
    make clean
    make
    print_success "Compilação concluída!"
}

# Função para executar o programa
run() {
    print_info "Executando o programa..."
    echo ""
    ./bin/concurso_cotas
}

# Função para verificar memory leaks
check_memory() {
    if ! command -v valgrind &> /dev/null; then
        print_warning "Valgrind não está instalado"
        echo "Para verificar memory leaks, instale valgrind:"
        echo "  Ubuntu/Debian: sudo apt install valgrind"
        echo "  Fedora/CentOS: sudo dnf install valgrind"
        return
    fi
    
    print_info "Verificando memory leaks com Valgrind..."
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
             ./bin/concurso_cotas
}

# Função para criar pacote de distribuição
package() {
    print_info "Criando pacote de distribuição..."
    make dist
    print_success "Pacote criado: concurso-cotas-fila.tar.gz"
}

# Função para instalar no sistema
install_system() {
    print_info "Instalando no sistema..."
    make install
    print_success "Instalado em /usr/local/bin/concurso_cotas"
}

# Função para desinstalar do sistema
uninstall_system() {
    print_info "Desinstalando do sistema..."
    make uninstall
    print_success "Removido de /usr/local/bin/"
}

# Função para exibir ajuda
show_help() {
    echo "Script de Build - Sistema de Convocação de Candidatos com Cotas"
    echo ""
    echo "Uso: $0 [COMANDO]"
    echo ""
    echo "Comandos disponíveis:"
    echo "  deps        - Verificar dependências"
    echo "  build       - Compilar o projeto"
    echo "  run         - Compilar e executar"
    echo "  test        - Executar testes (compilar + executar)"
    echo "  memory      - Verificar memory leaks com Valgrind"
    echo "  clean       - Limpar arquivos compilados"
    echo "  package     - Criar pacote tar.gz"
    echo "  install     - Instalar no sistema (requer sudo)"
    echo "  uninstall   - Desinstalar do sistema (requer sudo)"
    echo "  all         - Verificar deps + compilar + executar"
    echo "  help        - Exibir esta ajuda"
    echo ""
    echo "Exemplos:"
    echo "  $0 build"
    echo "  $0 run"
    echo "  $0 all"
}

# Função principal
main() {
    case "${1:-}" in
        deps)
            check_dependencies
            ;;
        build)
            build
            ;;
        run)
            build
            run
            ;;
        test)
            build
            run
            ;;
        memory)
            build
            check_memory
            ;;
        clean)
            print_info "Limpando arquivos compilados..."
            make clean
            print_success "Limpeza concluída"
            ;;
        package)
            package
            ;;
        install)
            build
            install_system
            ;;
        uninstall)
            uninstall_system
            ;;
        all)
            check_dependencies
            build
            run
            ;;
        help|--help|-h)
            show_help
            ;;
        "")
            print_error "Nenhum comando especificado"
            echo ""
            show_help
            exit 1
            ;;
        *)
            print_error "Comando desconhecido: $1"
            echo ""
            show_help
            exit 1
            ;;
    esac
}

# Executar função principal
main "$@"
