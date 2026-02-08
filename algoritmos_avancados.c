#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file desafioAventureiro.c
 * @brief Mapa de mansao em arvore binaria com coleta de pistas.
 */

#define NOME_TAM 50
#define PISTA_TAM 120

/**
 * @struct Sala
 * @brief No da arvore que representa um comodo da mansao.
 */
typedef struct Sala {
    char nome[NOME_TAM];
    char pista[PISTA_TAM];
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
 * @brief Cria dinamicamente um comodo com ou sem pista.
 * @param nome Nome do comodo.
 * @param pista Pista encontrada no comodo (pode ser NULL ou vazia).
 * @return Ponteiro para a nova sala alocada.
 */
Sala *criarSala(const char *nome, const char *pista) {
    Sala *nova = (Sala *)malloc(sizeof(Sala));
    if(nova == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    snprintf(nova->nome, sizeof(nova->nome), "%s", nome);
    if(pista != NULL && pista[0] != '\0') {
        snprintf(nova->pista, sizeof(nova->pista), "%s", pista);
    } else {
        nova->pista[0] = '\0';
    }

    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

/**
 * @brief Cria dinamicamente um no de pista.
 * @param pista Texto da pista.
 * @return Ponteiro para o novo no de pista.
 */
PistaNode *criarPistaNode(const char *pista) {
    PistaNode *novo = (PistaNode *)malloc(sizeof(PistaNode));
    if(novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    snprintf(novo->pista, sizeof(novo->pista), "%s", pista);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

/**
 * @brief Insere uma nova pista na arvore de pistas.
 * @param raiz Raiz da BST de pistas.
 * @param pista Texto da pista a inserir.
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
 * @brief Controla a navegacao entre salas e coleta de pistas.
 * @param raiz Sala inicial (Hall de Entrada).
 * @param pistasRaiz Ponteiro para a raiz da BST de pistas.
 */
void explorarSalasComPistas(Sala *raiz, PistaNode **pistasRaiz) {
    Sala *atual = raiz;
    char opcao = ' ';

    while(atual != NULL) {
        printf("\nVoce esta em: %s\n", atual->nome);

        if(atual->pista[0] != '\0') {
            printf("Pista encontrada: %s\n", atual->pista);
            *pistasRaiz = inserirPista(*pistasRaiz, atual->pista);
            atual->pista[0] = '\0';
        } else {
            printf("Nenhuma pista neste comodo.\n");
        }

        {
            int temEsq = atual->esquerda != NULL;
            int temDir = atual->direita != NULL;

            if(!temEsq && !temDir) {
                printf("Nao ha caminhos disponiveis. Use s para sair.\n");
            }

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
        if(scanf(" %c", &opcao) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }

        if(opcao == 's') {
            printf("Exploracao encerrada pelo jogador.\n");
            break;
        } else if(opcao == 'e') {
            if(atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Nao ha sala a esquerda.\n");
            }
        } else if(opcao == 'd') {
            if(atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Nao ha sala a direita.\n");
            }
        } else {
            printf("Opcao invalida. Use e, d ou s.\n");
        }
    }
}

/**
 * @brief Imprime a arvore de pistas em ordem alfabetica.
 * @param raiz Raiz da BST de pistas.
 */
void exibirPistas(PistaNode *raiz) {
    if(raiz == NULL) {
        return;
    }

    exibirPistas(raiz->esquerda);
    printf("- %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

/**
 * @brief Libera recursivamente a memoria de todas as salas.
 * @param raiz Raiz da arvore de salas.
 */
void liberarSalas(Sala *raiz) {
    if(raiz != NULL) {
        liberarSalas(raiz->esquerda);
        liberarSalas(raiz->direita);
        free(raiz);
    }
}

/**
 * @brief Libera recursivamente a memoria da BST de pistas.
 * @param raiz Raiz da BST de pistas.
 */
void liberarPistas(PistaNode *raiz) {
    if(raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

int main() {
    Sala *hall = criarSala("Hall de Entrada", "Chave com simbolo estranho");
    Sala *salaEstar = criarSala("Sala de Estar", "Pegadas de barro fresco");
    Sala *cozinha = criarSala("Cozinha", "Faca com iniciais gravadas");
    Sala *biblioteca = criarSala("Biblioteca", "Livro com pagina marcada");
    Sala *jardim = criarSala("Jardim", "Pegadas levam ao portao");
    Sala *quarto = criarSala("Quarto", "Carta rasgada no criado-mudo");
    Sala *banheiro = criarSala("Banheiro", "Frasco de perfume vazio");

    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    cozinha->esquerda = quarto;
    cozinha->direita = banheiro;

    PistaNode *pistasRaiz = NULL;

    printf("Bem-vindo ao Detective Quest!\n");
    printf("Explore a mansao a partir do Hall de Entrada.\n");

    explorarSalasComPistas(hall, &pistasRaiz);

    printf("\nPistas coletadas (ordem alfabetica):\n");
    if(pistasRaiz == NULL) {
        printf("Nenhuma pista foi coletada.\n");
    } else {
        exibirPistas(pistasRaiz);
    }

    liberarSalas(hall);
    liberarPistas(pistasRaiz);

    return 0;
}
