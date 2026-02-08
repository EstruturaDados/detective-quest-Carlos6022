# Detective Quest - Nivel Aventureiro

## Visao Geral

Este projeto implementa, em C, um mapa de uma mansao usando uma arvore binaria, com coleta de pistas. O jogador inicia no Hall de Entrada, explora os comodos e registra automaticamente as pistas em uma BST para exibicao alfabetica ao final.

## Objetivo

Aplicar conceitos de estrutura de dados (arvore binaria e BST) com alocacao dinamica, navegacao interativa e ordenacao alfabetica das pistas coletadas.

## Funcionalidades Principais

| Recurso               | Descricao                                                              |
| --------------------- | ---------------------------------------------------------------------- |
| Exploracao interativa | Navegacao por escolhas do usuario (e, d, s).                           |
| Arvore fixa           | Mapa definido manualmente no codigo, sem insercoes dinamicas de salas. |
| Coleta de pistas      | Cada sala pode ter uma pista associada.                                |
| BST de pistas         | Pistas coletadas sao inseridas em ordem alfabetica.                    |
| Exibicao ordenada     | Lista final de pistas em ordem alfabetica ao sair da exploracao.       |
| Mensagens claras      | Saida orienta o usuario durante toda a exploracao.                     |

## Estrutura do Projeto

- `desafioAventureiro.c`: implementacao do mapa, coleta de pistas e liberacao de memoria.

## Arquitetura do Codigo

### Estruturas de Dados

```c
/**
 * @brief No da arvore que representa um comodo da mansao.
 */
typedef struct Sala {
    char nome[50];
    char pista[120];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

/**
 * @brief No da BST que armazena pistas coletadas.
 */
typedef struct PistaNode {
    char pista[120];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;
```

### Funcoes Principais

- `criarSala(const char *nome, const char *pista)` - Cria dinamicamente um comodo com ou sem pista.
- `inserirPista(PistaNode *raiz, const char *pista)` - Insere uma pista na BST de pistas.
- `explorarSalasComPistas(Sala *raiz, PistaNode **pistasRaiz)` - Controla a navegacao e coleta.
- `exibirPistas(PistaNode *raiz)` - Imprime a BST em ordem alfabetica.
- `liberarSalas(Sala *raiz)` - Libera a memoria da arvore de salas.
- `liberarPistas(PistaNode *raiz)` - Libera a memoria da BST de pistas.
- `main()` - Monta o mapa inicial e inicia a exploracao.

## Conceitos Aplicados

- Arvore binaria (nos com ate dois filhos).
- Arvore binaria de busca (BST) para ordenacao.
- Alocacao dinamica com `malloc` e `free`.
- Recursividade para insercao e exibicao ordenada.
- Modularizacao com funcoes de responsabilidade unica.

## Como Usar

### Compilacao (GCC)

```bash
gcc -g desafioAventureiro.c -o desafioAventureiro.exe
```

### Execucao

```bash
./desafioAventureiro.exe
```

### Exemplo de Interacao

```
Bem-vindo ao Detective Quest!
Explore a mansao a partir do Hall de Entrada.

Voce esta em: Hall de Entrada
Pista encontrada: Chave com simbolo estranho
Escolha um caminho: (e) esquerda, (d) direita, (s) sair: e
Voce esta em: Sala de Estar
Pista encontrada: Pegadas de barro fresco
Escolha um caminho: (e) esquerda, (d) direita, (s) sair: s
Exploracao encerrada pelo jogador.

Pistas coletadas (ordem alfabetica):
- Chave com simbolo estranho
- Pegadas de barro fresco
```

## Requisitos Cumpridos

### Funcionais

- Arvore binaria criada dinamicamente.
- Exploracao interativa com entradas `e`, `d` e `s`.
- Mapa montado na `main()` com pistas por sala.
- Coleta automatica e armazenamento em BST.
- Impressao das pistas em ordem alfabetica ao final.

### Nao Funcionais

- Saida clara e orientada ao usuario.
- Codigo organizado com funcoes separadas.
- Comentarios em estilo Doxygen.

## Observacoes

- O usuario deve sair com `s` para ver a lista final de pistas.
- As arvores nao precisam ser balanceadas.

---

Status: OK
Ultima atualizacao: 08/02/2026
