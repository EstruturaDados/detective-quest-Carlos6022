#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file desafioMetre.c
 * @brief Detective Quest - Nivel mestre com BST de pistas e hash de suspeitos.
 */

#define NOME_TAM 50
#define PISTA_TAM 120
#define SUSPEITO_TAM 50
#define HASH_TAM 23

/**
 * @struct Sala
 * @brief No da arvore que representa um comodo da mansao.
 */
typedef struct Sala {
    char nome[NOME_TAM];
    char pista[PISTA_TAM];
    char suspeito[SUSPEITO_TAM];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

/**
 * @struct PistaNode
 * @brief No da BST que armazena pistas coletadas.
 */
typedef struct PistaNode {
    char pista[PISTA_TAM];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

/**
 * @struct HashEntry
 * @brief Entrada da tabela hash que associa pista a suspeito.
 */
typedef struct HashEntry {
    char pista[PISTA_TAM];
    char suspeito[SUSPEITO_TAM];
    struct HashEntry *proximo;
} HashEntry;

typedef struct HashTable {
    HashEntry *buckets[HASH_TAM];
} HashTable;

static unsigned int hash_string(const char *texto) {
    unsigned int hash = 5381;
    int c = 0;
    while((c = (unsigned char)*texto++) != 0) {
        hash = ((hash << 5) + hash) + (unsigned int)c;
    }
    return hash % HASH_TAM;
}

static int comparar_ignore_case(const char *a, const char *b) {
    while(*a != '\0' && *b != '\0') {
        int ca = tolower((unsigned char)*a);
        int cb = tolower((unsigned char)*b);
        if(ca != cb) {
            return ca - cb;
        }
        a++;
        b++;
    }
    return (unsigned char)*a - (unsigned char)*b;
}

/**
 * @brief Cria dinamicamente um comodo com pista e suspeito associados.
 * @param nome Nome do comodo.
 * @param pista Pista encontrada no comodo (pode ser vazia).
 * @param suspeito Suspeito relacionado a pista (pode ser vazio).
 * @return Ponteiro para a nova sala alocada.
 */
Sala *criarSala(const char *nome, const char *pista, const char *suspeito) {
    Sala *nova = (Sala *)malloc(sizeof(Sala));
    if(nova == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    snprintf(nova->nome, sizeof(nova->nome), "%s", nome);
    snprintf(nova->pista, sizeof(nova->pista), "%s", pista ? pista : "");
    snprintf(nova->suspeito, sizeof(nova->suspeito), "%s", suspeito ? suspeito : "");
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

static PistaNode *criarPistaNode(const char *pista) {
    PistaNode *novo = (PistaNode *)malloc(sizeof(PistaNode));
    if(novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    snprintf(novo->pista, sizeof(novo->pista), "%s", pista);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

/**
 * @brief Insere a pista coletada na BST de pistas.
 * @param raiz Raiz da BST.
 * @param pista Texto da pista.
 * @return Nova raiz da BST.
 */
PistaNode *inserirPista(PistaNode *raiz, const char *pista) {
    if(raiz == NULL) {
        return criarPistaNode(pista);
    }

    if(strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if(strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }

    return raiz;
}

/**
 * @brief Insere associacao pista/suspeito na tabela hash.
 * @param tabela Tabela hash.
 * @param pista Chave da pista.
 * @param suspeito Valor do suspeito.
 */
void inserirNaHash(HashTable *tabela, const char *pista, const char *suspeito) {
    unsigned int idx = hash_string(pista);
    HashEntry *atual = tabela->buckets[idx];
    while(atual != NULL) {
        if(strcmp(atual->pista, pista) == 0) {
            snprintf(atual->suspeito, sizeof(atual->suspeito), "%s", suspeito);
            return;
        }
        atual = atual->proximo;
    }

    HashEntry *novo = (HashEntry *)malloc(sizeof(HashEntry));
    if(novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    snprintf(novo->pista, sizeof(novo->pista), "%s", pista);
    snprintf(novo->suspeito, sizeof(novo->suspeito), "%s", suspeito);
    novo->proximo = tabela->buckets[idx];
    tabela->buckets[idx] = novo;
}

/**
 * @brief Consulta o suspeito correspondente a uma pista.
 * @param tabela Tabela hash.
 * @param pista Pista a consultar.
 * @return Suspeito associado ou NULL.
 */
const char *encontrarSuspeito(HashTable *tabela, const char *pista) {
    unsigned int idx = hash_string(pista);
    HashEntry *atual = tabela->buckets[idx];
    while(atual != NULL) {
        if(strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }
    return NULL;
}

/**
 * @brief Navega pela arvore e ativa o sistema de pistas.
 * @param atual Sala atual da exploracao.
 * @param pistasRaiz Raiz da BST de pistas coletadas.
 * @param tabela Hash com pistas e suspeitos.
 */
void explorarSalas(Sala *atual, PistaNode **pistasRaiz, HashTable *tabela) {
    if(atual == NULL) {
        return;
    }

    printf("\nVoce esta em: %s\n", atual->nome);
    if(atual->pista[0] != '\0') {
        printf("Pista encontrada: %s\n", atual->pista);
        *pistasRaiz = inserirPista(*pistasRaiz, atual->pista);
        inserirNaHash(tabela, atual->pista, atual->suspeito);
        atual->pista[0] = '\0';
        atual->suspeito[0] = '\0';
    } else {
        printf("Nenhuma pista neste comodo.\n");
    }

    {
        int temEsq = atual->esquerda != NULL;
        int temDir = atual->direita != NULL;

        printf("Escolha um caminho: ");
        if(temEsq && temDir) {
            printf("(e) esquerda, (d) direita, (s) sair: ");
        } else if(temEsq) {
            printf("(e) esquerda, (s) sair: ");
        } else if(temDir) {
            printf("(d) direita, (s) sair: ");
        } else {
            printf("(s) sair: ");
        }
    }

    char opcao = ' ';
    if(scanf(" %c", &opcao) != 1) {
        printf("Entrada invalida.\n");
        explorarSalas(atual, pistasRaiz, tabela);
        return;
    }

    if(opcao == 's') {
        printf("Exploracao encerrada pelo jogador.\n");
        return;
    }
    if(opcao == 'e') {
        if(atual->esquerda != NULL) {
            explorarSalas(atual->esquerda, pistasRaiz, tabela);
        } else {
            printf("Nao ha sala a esquerda.\n");
            explorarSalas(atual, pistasRaiz, tabela);
        }
        return;
    }
    if(opcao == 'd') {
        if(atual->direita != NULL) {
            explorarSalas(atual->direita, pistasRaiz, tabela);
        } else {
            printf("Nao ha sala a direita.\n");
            explorarSalas(atual, pistasRaiz, tabela);
        }
        return;
    }

    printf("Opcao invalida. Use e, d ou s.\n");
    explorarSalas(atual, pistasRaiz, tabela);
}

static void exibirPistas(PistaNode *raiz) {
    if(raiz == NULL) {
        return;
    }
    exibirPistas(raiz->esquerda);
    printf("- %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

static int contarPistasSuspeito(PistaNode *raiz, HashTable *tabela, const char *suspeito) {
    if(raiz == NULL) {
        return 0;
    }

    int total = 0;
    total += contarPistasSuspeito(raiz->esquerda, tabela, suspeito);

    {
        const char *associado = encontrarSuspeito(tabela, raiz->pista);
        if(associado != NULL && comparar_ignore_case(associado, suspeito) == 0) {
            total += 1;
        }
    }

    total += contarPistasSuspeito(raiz->direita, tabela, suspeito);
    return total;
}

/**
 * @brief Conduz a fase de julgamento final.
 * @param pistasRaiz Raiz da BST de pistas coletadas.
 * @param tabela Tabela hash com suspeitos.
 * @param suspeitoAcusado Nome do suspeito acusado.
 */
void verificarSuspeitoFinal(PistaNode *pistasRaiz, HashTable *tabela, const char *suspeitoAcusado) {
    int total = contarPistasSuspeito(pistasRaiz, tabela, suspeitoAcusado);
    if(total >= 2) {
        printf("\nAcusacao aceita! %s possui %d pistas.\n", suspeitoAcusado, total);
        printf("O caso foi resolvido com sucesso.\n");
    } else {
        printf("\nAcusacao fraca! %s possui apenas %d pista(s).\n", suspeitoAcusado, total);
        printf("O misterio permanece sem solucao.\n");
    }
}

static void liberarSalas(Sala *raiz) {
    if(raiz != NULL) {
        liberarSalas(raiz->esquerda);
        liberarSalas(raiz->direita);
        free(raiz);
    }
}

static void liberarPistas(PistaNode *raiz) {
    if(raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

static void liberarHash(HashTable *tabela) {
    for(int i = 0; i < HASH_TAM; i++) {
        HashEntry *atual = tabela->buckets[i];
        while(atual != NULL) {
            HashEntry *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
        tabela->buckets[i] = NULL;
    }
}

static void limpar_entrada(void) {
    int c = 0;
    do {
        c = getchar();
    } while(c != '\n' && c != EOF);
}

int main(void) {
    Sala *hall = criarSala("Hall de Entrada", "Chave com simbolo estranho", "Helena");
    Sala *salaEstar = criarSala("Sala de Estar", "Pegadas de barro fresco", "Otavio");
    Sala *cozinha = criarSala("Cozinha", "Faca com iniciais gravadas", "Lucia");
    Sala *biblioteca = criarSala("Biblioteca", "Livro com pagina marcada", "Helena");
    Sala *jardim = criarSala("Jardim", "Pegadas levam ao portao", "Otavio");
    Sala *quarto = criarSala("Quarto", "Carta rasgada no criado-mudo", "Lucia");
    Sala *banheiro = criarSala("Banheiro", "Frasco de perfume vazio", "Helena");

    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->esquerda = quarto;
    cozinha->direita = banheiro;

    PistaNode *pistasRaiz = NULL;
    HashTable tabela = {0};

    printf("Bem-vindo ao Detective Quest - Nivel Mestre!\n");
    printf("Explore a mansao e colete pistas.\n");

    explorarSalas(hall, &pistasRaiz, &tabela);

    printf("\nPistas coletadas (ordem alfabetica):\n");
    if(pistasRaiz == NULL) {
        printf("Nenhuma pista foi coletada.\n");
    } else {
        exibirPistas(pistasRaiz);
    }

    limpar_entrada();
    char suspeitoAcusado[SUSPEITO_TAM] = {0};
    printf("\nQuem voce acusa? Digite o nome do suspeito: ");
    if(fgets(suspeitoAcusado, sizeof(suspeitoAcusado), stdin) == NULL) {
        printf("Entrada invalida.\n");
    } else {
        size_t len = strlen(suspeitoAcusado);
        if(len > 0 && suspeitoAcusado[len - 1] == '\n') {
            suspeitoAcusado[len - 1] = '\0';
        }
        if(suspeitoAcusado[0] != '\0') {
            verificarSuspeitoFinal(pistasRaiz, &tabela, suspeitoAcusado);
        } else {
            printf("Nome vazio. Julgamento encerrado.\n");
        }
    }

    liberarSalas(hall);
    liberarPistas(pistasRaiz);
    liberarHash(&tabela);

    return 0;
}
