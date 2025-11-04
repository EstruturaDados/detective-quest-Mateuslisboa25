#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===============================================================
// Estrutura da árvore binária de cômodos da mansão
// ===============================================================
typedef struct Sala {
    char nome[50];
    char pista[100]; // pista opcional
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// ===============================================================
// Estrutura da árvore BST de pistas coletadas
// ===============================================================
typedef struct PistaNode {
    char pista[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

// ===============================================================
// Função: criarSala
// Cria dinamicamente uma sala com nome e pista opcional
// ===============================================================
Sala* criarSala(const char *nome, const char *pista) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memória para a sala!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    if (pista != NULL)
        strcpy(nova->pista, pista);
    else
        strcpy(nova->pista, "");
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// ===============================================================
// Função: criarPistaNode
// Cria um nó para armazenar uma nova pista na BST
// ===============================================================
PistaNode* criarPistaNode(const char *pista) {
    PistaNode *novo = (PistaNode*) malloc(sizeof(PistaNode));
    if (novo == NULL) {
        printf("Erro ao alocar memória para a pista!\n");
        exit(1);
    }
    strcpy(novo->pista, pista);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// ===============================================================
// Função: inserirPista
// Insere uma nova pista na árvore BST em ordem alfabética
// ===============================================================
PistaNode* inserirPista(PistaNode *raiz, const char *pista) {
    if (raiz == NULL)
        return criarPistaNode(pista);

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);

    return raiz;
}

// ===============================================================
// Função: exibirPistas
// Exibe as pistas da árvore BST em ordem alfabética (in-order)
// ===============================================================
void exibirPistas(PistaNode *raiz) {
    if (raiz == NULL) return;
    exibirPistas(raiz->esquerda);
    printf(" - %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

// ===============================================================
// Função: explorarSalasComPistas
// Controla a navegação entre salas e coleta de pistas
// ===============================================================
void explorarSalasComPistas(Sala *atual, PistaNode **arvorePistas) {
    char escolha;

    while (1) {
        printf("\nVocê está em: %s\n", atual->nome);

        // Se a sala tiver pista, coletar
        if (strlen(atual->pista) > 0) {
            printf("Você encontrou uma pista: \"%s\"!\n", atual->pista);
            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        } else {
            printf("Nenhuma pista encontrada aqui.\n");
        }

        // Mostrar caminhos disponíveis
        printf("\nEscolha o caminho:\n");
        if (atual->esquerda != NULL) printf(" (e) Esquerda -> %s\n", atual->esquerda->nome);
        if (atual->direita != NULL) printf(" (d) Direita -> %s\n", atual->direita->nome);
        printf(" (s) Sair da exploração\n");
        printf("Sua escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        } else if (escolha == 's') {
            printf("\nVocê decidiu encerrar a exploração.\n");
            break;
        } else {
            printf("Opção inválida! Escolha novamente.\n");
        }
    }
}

// ===============================================================
// Função: liberarArvoreSalas
// Libera memória da árvore da mansão
// ===============================================================
void liberarArvoreSalas(Sala *raiz) {
    if (raiz == NULL) return;
    liberarArvoreSalas(raiz->esquerda);
    liberarArvoreSalas(raiz->direita);
    free(raiz);
}

// ===============================================================
// Função: liberarArvorePistas
// Libera memória da árvore de pistas
// ===============================================================
void liberarArvorePistas(PistaNode *raiz) {
    if (raiz == NULL) return;
    liberarArvorePistas(raiz->esquerda);
    liberarArvorePistas(raiz->direita);
    free(raiz);
}

// ===============================================================
// Função principal: main
// Monta o mapa da mansão e inicia a exploração
// ===============================================================
int main() {
    // ===== Criação da árvore da mansão (fixa) =====
    Sala *hall = criarSala("Hall de Entrada", "Um bilhete rasgado com o nome 'Charles'");
    Sala *salaEstar = criarSala("Sala de Estar", "Uma luva suja de terra");
    Sala *cozinha = criarSala("Cozinha", "Um copo quebrado com marcas de batom");
    Sala *biblioteca = criarSala("Biblioteca", "Uma página arrancada de um diário");
    Sala *jardim = criarSala("Jardim", "Pegadas recentes na lama");
    Sala *porao = criarSala("Porão", "Uma chave antiga enferrujada");
    Sala *salaSegredos = criarSala("Sala dos Segredos", "Um retrato queimado parcialmente destruído");

    // Conectando as salas
    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    cozinha->esquerda = porao;
    cozinha->direita = salaSegredos;

    // ===== Início da exploração =====
    PistaNode *pistas = NULL;

    printf("=== Detective Quest: Coleta de Pistas ===\n");
    printf("Explore a mansão, colete pistas e descubra o culpado!\n");

    explorarSalasComPistas(hall, &pistas);

    // ===== Exibição das pistas coletadas =====
    printf("\n=== Pistas Coletadas (em ordem alfabética) ===\n");
    if (pistas == NULL)
        printf("Nenhuma pista foi coletada!\n");
    else
        exibirPistas(pistas);

    // ===== Liberação de memória =====
    liberarArvoreSalas(hall);
    liberarArvorePistas(pistas);

    printf("\nObrigado por jogar Detective Quest!\n");
    return 0;
}
