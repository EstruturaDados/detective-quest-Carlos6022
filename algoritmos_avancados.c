#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file desafioNovato.c
 * @brief Mapa de mansao em arvore binaria com exploracao interativa.
 */

/**
 * @struct Sala
 * @brief No da arvore que representa um comodo da mansao.
 */
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

/**
 * @brief Cria dinamicamente uma sala com nome.
 * @param nome Nome do comodo.
 * @return Ponteiro para a nova sala alocada.
 */
Sala *criarSala(const char *nome) {
    Sala *nova = (Sala *)malloc(sizeof(Sala));
    if(nova == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

/**
 * @brief Permite a navegacao do jogador pela arvore.
 * @param raiz Sala inicial (Hall de Entrada).
 */
void explorarSalas(Sala *raiz) {
    Sala *atual = raiz;
    char opcao = ' ';

    while(atual != NULL) {
        printf("\nVoce esta em: %s\n", atual->nome);

        if(atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim do caminho. Nao ha mais salas.\n");
            break;
        }

        printf("Escolha um caminho: (e) esquerda, (d) direita, (s) sair: ");
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
 * @brief Libera recursivamente a memoria de todas as salas.
 * @param raiz Raiz da arvore.
 */
void liberarSalas(Sala *raiz) {
    if(raiz != NULL) {
        liberarSalas(raiz->esquerda);
        liberarSalas(raiz->direita);
        free(raiz);
    }
}

/**
 * @brief Monta o mapa inicial e inicia a exploracao.
 * @return Codigo de saida do programa.
 */
int main() {
    Sala *hall = criarSala("Hall de Entrada");
    Sala *salaEstar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *jardim = criarSala("Jardim");
    Sala *quarto = criarSala("Quarto");
    Sala *banheiro = criarSala("Banheiro");

    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    cozinha->esquerda = quarto;
    cozinha->direita = banheiro;

    printf("Bem-vindo ao Detective Quest!\n");
    printf("Explore a mansao a partir do Hall de Entrada.\n");

    explorarSalas(hall);
    liberarSalas(hall);

    return 0;
}
