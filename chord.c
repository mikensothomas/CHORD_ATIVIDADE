#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int dado;
    struct no* proximo;
} no;

// Função para criar um novo nó
no* criarno(int dado) {
    no* novono = (no*)malloc(sizeof(no));
    if (novono == NULL) {
        printf("Erro: Memória insuficiente!\n");
        exit(1);
    }
    novono->dado = dado;
    novono->proximo = NULL;
    return novono;
}

// Função para inserir um nó no final da lista
no* inserir_no_final(no* ultimo, int dado) {
    if (ultimo == NULL) {
        ultimo = criarno(dado);
        ultimo->proximo = ultimo; // Ponteiro proximo aponta para si mesmo
    } else {
        no* novono = criarno(dado);
        novono->proximo = ultimo->proximo;
        ultimo->proximo = novono;
        ultimo = novono;
    }
    return ultimo;
}

// Função para imprimir os elementos da lista circular
void imprimir_lista(no* ultimo) {
    if (ultimo == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    no* temp = ultimo->proximo;
    do {
        printf("%d ", temp->dado);
        temp = temp->proximo;
    } while (temp != ultimo->proximo);
    printf("\n");
}

// Função principal
int main() {
    no* ultimo = NULL;

    // Inserindo elementos na lista circular
    ultimo = inserir_no_final(ultimo, 1);
    ultimo = inserir_no_final(ultimo, 2);
    ultimo = inserir_no_final(ultimo, 3);
    ultimo = inserir_no_final(ultimo, 4);
    ultimo = inserir_no_final(ultimo, 5);
    ultimo = inserir_no_final(ultimo, 7);
    ultimo = inserir_no_final(ultimo, 8);
    ultimo = inserir_no_final(ultimo, 9);
    ultimo = inserir_no_final(ultimo, 10);
    ultimo = inserir_no_final(ultimo, 11);


    // Imprimindo a lista circular
    printf("Lista circular: ");
    imprimir_lista(ultimo);

    return 0;
}