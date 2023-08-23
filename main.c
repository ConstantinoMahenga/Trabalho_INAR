#include <stdio.h>
#include <stdlib.h>
// [CONSTANTINO JOSE MAHENGA], o meu colega e [EDUARDO DA SILVA]


struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
};

// a função para alocar dinamicamente um novo nó
struct No* criarNo(int valor) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    if (novoNo == NULL) {
        perror("Erro ao alocar memória para um novo nó");
        exit(EXIT_FAILURE);
    }
    novoNo->valor = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Nossa função para inserir um nó na árvore
struct No* inserirNo(struct No* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }
    if (valor < raiz->valor) {
        raiz->esquerda = inserirNo(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserirNo(raiz->direita, valor);
    }
    return raiz;
}

// Nossa função para mostrar os nós por profundidade usando busca em profundidade
void mostrarCaminhoPorLinha(struct No* raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }
    if (nivel == 1) {
        printf("%d ", raiz->valor);
    } else {
        mostrarCaminhoPorLinha(raiz->esquerda, nivel - 1);
        mostrarCaminhoPorLinha(raiz->direita, nivel - 1);
    }
}

// Nossa função para encontrar o nível de um valor na árvore
int encontrarNivel(struct No* raiz, int valor, int nivel) {
    if (raiz == NULL) {
        return 0;
    }
    if (raiz->valor == valor) {
        return nivel;
    }
    int nivelEncontrado = encontrarNivel(raiz->esquerda, valor, nivel + 1);
    if (nivelEncontrado != 0) {
        return nivelEncontrado;
    }
    return encontrarNivel(raiz->direita, valor, nivel + 1);
}

// Nossa função para mostrar um caminho específico
void mostrarCaminho(struct No* pilha[], int topo) {
    for (int i = 0; i < topo; i++) {
        printf("%d ", pilha[i]->valor);
    }
    printf("\n");
}

// Nossa função para buscar um valor por profundidade e empilhar elementos do caminho
int buscarPorProfundidade(struct No* raiz, int valor, struct No* pilha[], int topo) {
    if (raiz == NULL) {
        return topo;
    }
    if (raiz->valor == valor) {
        pilha[topo++] = raiz;
        return topo;
    }

    pilha[topo++] = raiz;
    if (valor < raiz->valor) {
        topo = buscarPorProfundidade(raiz->esquerda, valor, pilha, topo);
    } else {
        topo = buscarPorProfundidade(raiz->direita, valor, pilha, topo);
    }
    return topo;
}

// Nossa função principal
int main() {
    struct No* raiz = NULL;
    raiz = inserirNo(raiz, 10);
    raiz = inserirNo(raiz, 5);
    raiz = inserirNo(raiz, 15);
    raiz = inserirNo(raiz, 3);
    raiz = inserirNo(raiz, 7);
    raiz = inserirNo(raiz, 12);
    raiz = inserirNo(raiz, 18);
    raiz = inserirNo(raiz, 2);
    raiz = inserirNo(raiz, 4);
    raiz = inserirNo(raiz, 6);
    raiz = inserirNo(raiz, 9);
    raiz = inserirNo(raiz, 11);
    raiz = inserirNo(raiz, 14);
    raiz = inserirNo(raiz, 17);
    raiz = inserirNo(raiz, 20);
    raiz = inserirNo(raiz, 1);
    raiz = inserirNo(raiz, 8);
    raiz = inserirNo(raiz, 13);
    raiz = inserirNo(raiz, 16);
    raiz = inserirNo(raiz, 19);

    int valorBusca = 20;
    int maxNivel = encontrarNivel(raiz, valorBusca, 1);

    for (int nivel = 1; nivel <= maxNivel; nivel++) {
        printf("Linha %d: ", nivel);
        mostrarCaminhoPorLinha(raiz, nivel);
        printf("\n");
    }

    struct No* pilhaCaminho[100];
    int topo = 0;
    topo = buscarPorProfundidade(raiz, valorBusca, pilhaCaminho, topo);

    printf("Caminho para %d encontrado por profundidade: ", valorBusca);
    mostrarCaminho(pilhaCaminho, topo);

    // Liberar memória alocada
    for (int i = 0; i < topo; i++) {
        free(pilhaCaminho[i]);
    }

    return 0;
}


/**
             A arvore contendo os 20 elementos , o algoritmo que nos seguimos
                                     10
                                   /    \
                                  5     15
                                 / \   /   \
                                3   7 12   18
                               / \    / \   / \
                              2   4  11 14 17 20
                             /        /
                            1        13
                                     /
                                    16
                                   /
                                  19
                             
*/
