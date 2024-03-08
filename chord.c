#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int dado;
    struct NO* proximo;
} NO;

// Função para criar um novo nó
NO* criarNo(int dado) {
    NO* novoNo = (NO*)malloc(sizeof(NO));
    if (novoNo == NULL) {
        printf("Erro: Memória insuficiente!\n");
        exit(1);
    }
    novoNo->dado = dado;
    novoNo->proximo = NULL;
    return novoNo;
}

// Função para inserir um nó no final da lista
NO* inserir_no_final(NO* ultimo, int dado) {
    if (ultimo == NULL) {
        ultimo = criarNo(dado);
        ultimo->proximo = ultimo; // Ponteiro proximo aponta para si mesmo
    } else {
        NO* novoNo = criarNo(dado);
        novoNo->proximo = ultimo->proximo;
        ultimo->proximo = novoNo;
        ultimo = novoNo;
    }
    return ultimo;
}

// Função para imprimir os elementos da lista circular
void imprimir_lista(NO* ultimo) {
    if (ultimo == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    NO* temp = ultimo->proximo;
    do {
        printf("%d ", temp->dado);
        temp = temp->proximo;
    } while (temp != ultimo->proximo);
    printf("\n");
}

// Função principal
int main() {
    NO* ultimo = NULL;

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