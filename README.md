# Detective Quest - Nivel Mestre

## Visao Geral

Este projeto implementa, em C, a versao mestre do Detective Quest. A mansao e representada por uma arvore binaria, as pistas coletadas sao armazenadas em uma BST, e cada pista e associada a um suspeito por uma tabela hash. Ao final, o jogador acusa um suspeito e o sistema verifica se existem pelo menos duas pistas que sustentam a acusacao.

## Objetivo

Aplicar conceitos de estrutura de dados (arvore binaria, BST e tabela hash) com navegacao interativa, associacao chave/valor e julgamento final baseado em evidencias.

## Funcionalidades Principais

| Recurso                      | Descricao                                                                 |
| --------------------------- | ------------------------------------------------------------------------- |
| Exploracao interativa        | Navegacao por escolhas do usuario (e, d, s).                              |
| Arvore fixa                  | Mapa definido manualmente no codigo, sem insercoes dinamicas de salas.    |
| Coleta de pistas             | Cada sala possui uma pista estatica associada ao comodo.                  |
| BST de pistas                | Pistas coletadas sao inseridas em ordem alfabetica.                       |
| Hash pista/suspeito           | Cada pista coletada e associada a um suspeito via tabela hash.            |
| Julgamento final             | Acusacao valida quando ha pelo menos duas pistas do suspeito.             |
| Mensagens claras             | Saida orienta a exploracao e o julgamento final.                          |

## Estrutura do Projeto

- `desafioMetre.c`: implementacao completa do nivel mestre.

## Arquitetura do Codigo

### Estruturas de Dados

```c
/**
 * @brief No da arvore que representa um comodo da mansao.
 */
typedef struct Sala {
    char nome[50];
    char pista[120];
    char suspeito[50];
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

/**
 * @brief Entrada da tabela hash que associa pista a suspeito.
 */
typedef struct HashEntry {
    char pista[120];
    char suspeito[50];
    struct HashEntry *proximo;
} HashEntry;
```

### Funcoes Principais

- `criarSala(const char *nome, const char *pista, const char *suspeito)` - Cria dinamicamente um comodo com pista e suspeito.
- `inserirPista(PistaNode *raiz, const char *pista)` - Insere uma pista na BST de pistas.
- `explorarSalas(Sala *atual, PistaNode **pistasRaiz, HashTable *tabela)` - Controla a navegacao e coleta de pistas.
- `inserirNaHash(HashTable *tabela, const char *pista, const char *suspeito)` - Insere associacao pista/suspeito na hash.
- `encontrarSuspeito(HashTable *tabela, const char *pista)` - Consulta o suspeito associado a uma pista.
- `verificarSuspeitoFinal(PistaNode *pistasRaiz, HashTable *tabela, const char *suspeitoAcusado)` - Realiza o julgamento final.

## Conceitos Aplicados

- Arvore binaria para o mapa da mansao.
- BST para ordenar pistas coletadas.
- Tabela hash para associar pista e suspeito.
- Recursividade na exploracao e contagem de pistas por suspeito.
- Alocacao dinamica com `malloc` e liberacao com `free`.

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
Bem-vindo ao Detective Quest - Nivel Mestre!
Explore a mansao e colete pistas.

Voce esta em: Hall de Entrada
Pista encontrada: Chave com simbolo estranho
Escolha um caminho: (e) esquerda, (d) direita, (s) sair: e
...

Pistas coletadas (ordem alfabetica):
- Chave com simbolo estranho
- Pegadas de barro fresco

Quem voce acusa? Digite o nome do suspeito: Helena
Acusacao aceita! Helena possui 2 pistas.
O caso foi resolvido com sucesso.
```

## Requisitos Cumpridos

### Funcionais

- Arvore binaria criada manualmente com comodos nomeados.
- Coleta de pistas por sala e armazenamento em BST.
- Tabela hash associando pista a suspeito.
- Exploracao interativa por e, d, s.
- Listagem final de pistas e julgamento com base em evidencias.

### Nao Funcionais

- Mensagens informativas durante exploracao e julgamento.
- Codigo modular e legivel.
- Comentarios explicativos nas funcoes exigidas.

## Observacoes

- A exploracao termina quando o jogador escolhe sair (s).
- A acusacao e aceita somente com pelo menos duas pistas para o suspeito.

---

Status: OK
Ultima atualizacao: 08/02/2026
