#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int valor;
    struct NO* proximo;
} NO;

typedef struct Lista {
    NO* inicio;
    NO* fim;
} Lista;

void inicializa_lista(Lista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

void inserir_no_fim(Lista* lista, int valor) {
    NO* novo_no = (NO *)malloc(sizeof(NO));
    if (novo_no == NULL) {
        printf("Erro: Não foi possível alocar memória para o NOvo nó.\n");
        return;
    }

    novo_no->valor = valor;
    
    if (lista->inicio == NULL) {
        lista->inicio = novo_no;
    } else {
        lista->fim->proximo = novo_no;
    }

    lista->fim = novo_no;

    lista->fim->proximo = lista->inicio;
}

void imprimir_lista(Lista* lista) {
    if (lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    NO* atual = lista->inicio;

    do {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    } while (atual != lista->inicio);

    printf("\n");
}

int main() {
    Lista lista;
    inicializa_lista(&lista);

    inserir_no_fim(&lista, 10);
    inserir_no_fim(&lista, 20);
    inserir_no_fim(&lista, 30);
    inserir_no_fim(&lista, 40);
    inserir_no_fim(&lista, 50);
    inserir_no_fim(&lista, 60);
    inserir_no_fim(&lista, 70);
    inserir_no_fim(&lista, 80);

    printf("Lista: ");
    imprimir_lista(&lista);

    return 0;
}
