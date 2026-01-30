# Makefile para Sistema de Convocação de Candidatos com Cotas
# Autor: Gustavo
# Descrição: Compila o sistema de gestão de filas para concursos públicos

# Configurações do compilador
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./include
LDFLAGS = 
TARGET = bin/concurso_cotas
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

# Lista de arquivos fonte e objetos
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Cores para output (opcional)
COLOR_RESET = \033[0m
COLOR_GREEN = \033[32m
COLOR_YELLOW = \033[33m

# Regra principal: compila o executável
all: $(BIN_DIR) $(TARGET)
	@echo "$(COLOR_GREEN)✓ Compilação concluída com sucesso!$(COLOR_RESET)"
	@echo "$(COLOR_YELLOW)Execute com: ./$(TARGET)$(COLOR_RESET)"

# Cria o diretório bin se não existir
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Regra para criar o executável final
$(TARGET): $(OBJECTS)
	@echo "$(COLOR_YELLOW)Linkando executável...$(COLOR_RESET)"
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Regra para compilar arquivos .c em arquivos .o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compilando $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa arquivos compilados
clean:
	@echo "Limpando arquivos compilados..."
	rm -f $(BIN_DIR)/*.o $(TARGET)
	@echo "$(COLOR_GREEN)✓ Limpeza concluída!$(COLOR_RESET)"

# Remove também o diretório bin
distclean: clean
	rm -rf $(BIN_DIR)

# Compila e executa
run: all
	@echo "\n$(COLOR_GREEN)=== Executando o programa ===$(COLOR_RESET)\n"
	./$(TARGET)

# Instalação do executável no sistema (requer sudo)
install: all
	@echo "Instalando em /usr/local/bin..."
	sudo cp $(TARGET) /usr/local/bin/concurso_cotas
	@echo "$(COLOR_GREEN)✓ Instalação concluída!$(COLOR_RESET)"

# Desinstalação
uninstall:
	@echo "Removendo de /usr/local/bin..."
	sudo rm -f /usr/local/bin/concurso_cotas
	@echo "$(COLOR_GREEN)✓ Desinstalação concluída!$(COLOR_RESET)"

# Mostra informações sobre o projeto
info:
	@echo "=== Informações do Projeto ==="
	@echo "Compilador: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo "Arquivos fonte: $(SOURCES)"
	@echo "Executável: $(TARGET)"

# Cria um pacote tar.gz para distribuição
dist: clean
	@echo "Criando pacote de distribuição..."
	tar -czf concurso-cotas-fila.tar.gz \
		Makefile README.md LICENSE \
		src/ include/ docs/ examples/
	@echo "$(COLOR_GREEN)✓ Pacote concurso-cotas-fila.tar.gz criado!$(COLOR_RESET)"

# Ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make         - Compila o projeto"
	@echo "  make run     - Compila e executa"
	@echo "  make clean   - Remove arquivos compilados"
	@echo "  make install - Instala no sistema (requer sudo)"
	@echo "  make uninstall - Remove do sistema"
	@echo "  make dist    - Cria pacote tar.gz"
	@echo "  make info    - Mostra informações do projeto"
	@echo "  make help    - Mostra esta ajuda"

.PHONY: all clean distclean run install uninstall info dist help
