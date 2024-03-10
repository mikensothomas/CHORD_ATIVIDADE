#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int dado;
    struct NO* proximo;
} NO;

// Função para criar um NOvo nó
NO* criar_no(int dado) {
    NO* novo_no = (NO*)malloc(sizeof(NO));
    if (novo_no == NULL) {
        printf("Erro: Memória insuficiente!\n");
        exit(1);
    }
    novo_no->dado = dado;
    novo_no->proximo = NULL;
    return novo_no;
}

// Função para inserir um nó NO final da lista
NO* inserir_NO_final(NO* ultimo, int dado) {
    if (ultimo == NULL) {
        ultimo = criar_no(dado);
        ultimo->proximo = ultimo; // Ponteiro proximo aponta para si mesmo
    } else {
        NO* novo_no = criar_no(dado);
        novo_no->proximo = ultimo->proximo;
        ultimo->proximo = novo_no;
        ultimo = novo_no;
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
    ultimo = inserir_NO_final(ultimo, 1);
    ultimo = inserir_NO_final(ultimo, 2);
    ultimo = inserir_NO_final(ultimo, 3);
    ultimo = inserir_NO_final(ultimo, 4);
    ultimo = inserir_NO_final(ultimo, 5);
    ultimo = inserir_NO_final(ultimo, 7);
    ultimo = inserir_NO_final(ultimo, 8);
    ultimo = inserir_NO_final(ultimo, 9);
    ultimo = inserir_NO_final(ultimo, 10);
    ultimo = inserir_NO_final(ultimo, 11);


    // Imprimindo a lista circular
    printf("Lista circular: ");
    imprimir_lista(ultimo);

    return 0;
}