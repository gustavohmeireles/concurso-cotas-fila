# 🚀 Guia de Instalação Rápida

## Para Usuários Linux/Mac

### 1. Verificar Dependências
```bash
gcc --version
make --version
```

Se não estiverem instalados:

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install build-essential
```

**Fedora/CentOS/RHEL:**
```bash
sudo dnf groupinstall "Development Tools"
```

**macOS:**
```bash
xcode-select --install
```

### 2. Clonar o Repositório
```bash
git clone https://github.com/seu-usuario/concurso-cotas-fila.git
cd concurso-cotas-fila
```

### 3. Compilar
```bash
make
```

### 4. Executar
```bash
./bin/concurso_cotas
```

## Para Usuários Windows

### Opção 1: WSL (Recomendado)
1. Instalar WSL: https://docs.microsoft.com/windows/wsl/install
2. Abrir terminal WSL
3. Seguir passos para Linux acima

### Opção 2: MinGW
1. Instalar MinGW: https://www.mingw-w64.org/
2. Adicionar ao PATH
3. Compilar:
```cmd
gcc -I./include src/*.c -o concurso_cotas.exe
```

## Verificação da Instalação

Se você vir uma saída similar a esta, a instalação foi bem-sucedida:

```
Pos Nome Modalidade ID
1 Ana Silva AC 1
2 Joao Santos AC 2
3 Pedro Costa PPI 3
...
```

## Problemas Comuns

**"gcc: command not found"**
- Instale o compilador GCC conforme instruções acima

**"make: command not found"**
- Instale o GNU Make conforme instruções acima

**Erro de permissão ao executar**
```bash
chmod +x bin/concurso_cotas
./bin/concurso_cotas
```

## Próximos Passos

- Leia o [README.md](README.md) completo
- Consulte a [Documentação da API](docs/API.md)
- Veja exemplos em [examples/](examples/)

## Suporte

Problemas? Abra uma Issue: https://github.com/seu-usuario/concurso-cotas-fila/issues
