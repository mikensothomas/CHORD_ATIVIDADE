#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó
typedef struct No {
    int dado;
    struct No *proximo;
} No;

// Definição da estrutura da lista
typedef struct Lista {
    No *inicio;
    No *final;
} Lista;

// Função para inicializar a lista
void inicializarLista(Lista *lista) {
    lista->inicio = NULL;
    lista->final = NULL;
}

// Função para inserir um elemento no final da lista
void inserirFinal(Lista *lista, int dado) {
    // Criar um novo nó
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro: Não foi possível alocar memória para o novo nó.\n");
        return;
    }

    // Preencher os dados do novo nó
    novoNo->dado = dado;
    novoNo->proximo = NULL;

    // Verificar se a lista está vazia
    if (lista->inicio == NULL) {
        lista->inicio = novoNo;
    } else {
        lista->final->proximo = novoNo;
    }

    // Atualizar o ponteiro final para o novo nó
    lista->final = novoNo;

    // Tornar a lista circular
    lista->final->proximo = lista->inicio;
}

// Função para exibir os elementos da lista
void exibirLista(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    No *atual = lista->inicio;

    // Percorrer a lista até o final
    do {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    } while (atual != lista->inicio);

    printf("\n");
}

// Função principal
int main() {
    Lista lista;
    inicializarLista(&lista);

    // Inserir elementos na lista
    inserirFinal(&lista, 10);
    inserirFinal(&lista, 20);
    inserirFinal(&lista, 30);
    inserirFinal(&lista, 40);

    // Exibir a lista
    printf("Lista: ");
    exibirLista(&lista);

    return 0;
}
