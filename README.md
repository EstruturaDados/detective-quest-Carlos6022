# Detective Quest - Nivel Novato

## Visao Geral

Este projeto implementa, em C, um mapa de uma mansao usando uma arvore binaria. O jogador inicia no Hall de Entrada e explora os comodos escolhendo caminhos para a esquerda ou direita ate encontrar um no-folha ou encerrar a exploracao.

## Objetivo

Aplicar conceitos basicos de estrutura de dados (arvore binaria) com alocacao dinamica e navegacao interativa controlada por entrada do usuario.

## Funcionalidades Principais

| Recurso                 | Descricao                                                     |
| ----------------------- | ------------------------------------------------------------- |
| Exploracao interativa   | Navegacao por escolhas do usuario (e, d, s).                  |
| Arvore fixa             | Mapa definido manualmente no codigo, sem insercoes dinamicas. |
| Encerramento automatico | Termina ao chegar em um no-folha.                             |
| Mensagens claras        | Saida orienta o usuario durante a exploracao.                 |

## Estrutura do Projeto

- `algoritmos_avancados.c`: implementacao do mapa, exploracao e liberacao de memoria.

## Arquitetura do Codigo

### Estrutura de Dados

```c
/**
 * @brief No da arvore que representa um comodo da mansao.
 */
typedef struct Sala {
	char nome[50];
	struct Sala *esquerda;
	struct Sala *direita;
} Sala;
```

### Funcoes Principais

- `criarSala(const char *nome)` - Cria dinamicamente um comodo.
- `explorarSalas(Sala *raiz)` - Permite a navegacao do jogador.
- `liberarSalas(Sala *raiz)` - Libera toda a memoria alocada.
- `main()` - Monta o mapa inicial e inicia a exploracao.

## Conceitos Aplicados

- Arvore binaria (nos com ate dois filhos).
- Alocacao dinamica com `malloc` e `free`.
- Controle de fluxo com `if`, `else` e `while`.
- Modularizacao com funcoes de responsabilidade unica.

## Como Usar

### Compilacao (GCC)

```bash
gcc -g algoritmos_avancados.c -o algoritmos_avancados.exe
```

### Execucao

```bash
./algoritmos_avancados.exe
```

### Exemplo de Interacao

```
Bem-vindo ao Detective Quest!
Explore a mansao a partir do Hall de Entrada.

Voce esta em: Hall de Entrada
Escolha um caminho: (e) esquerda, (d) direita, (s) sair: e
Voce esta em: Sala de Estar
Escolha um caminho: (e) esquerda, (d) direita, (s) sair: d
Voce esta em: Jardim
Fim do caminho. Nao ha mais salas.
```

## Requisitos Cumpridos

### Funcionais

- Arvore binaria criada dinamicamente.
- Exploracao interativa com entradas `e`, `d` e `s`.
- Mapa montado automaticamente na `main()`.
- Impressao do nome de cada sala visitada.

### Nao Funcionais

- Saida clara e orientada ao usuario.
- Codigo organizado com funcoes separadas.
- Comentarios em estilo Doxygen.

## Observacoes

- A arvore e montada manualmente no codigo e nao muda em tempo de execucao.
- Nao ha busca, insercao ou remocao dinamica durante o uso.

---

Status: OK
Ultima atualizacao: 07/02/2026
