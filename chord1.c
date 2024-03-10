#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_LISTA 9
#define TAMANHO_MAXIMO 50

typedef struct NO {
    int numero;
    char recurso[TAMANHO_MAXIMO];
    int ativo;
    struct NO* proximo;
} NO;

int hash(const char* recurso) {
    int soma = 0;
    for (int i = 0; i < strlen(recurso); i++) {
        soma += recurso[i];
    }
    return soma % TAMANHO_LISTA;
}

NO* criar_NO(int numero, const char* recurso) {
    NO* novo_no = (NO*)malloc(sizeof(NO));
    if (novo_no == NULL) {
        printf("Erro: não foi possível alocar memória para o NOvo nó.\n");
    }
    novo_no->numero = numero;
    strcpy(novo_no->recurso, recurso);
    novo_no->ativo = 0;
    novo_no->proximo = novo_no;
    return novo_no;
}

void inserirRecurso(NO* lista[], const char* recurso) {
    int indice = hash(recurso);
    NO* novo_no = criar_NO(indice, recurso);

    if (lista[indice] == NULL) {
        lista[indice] = novo_no;
        novo_no->proximo = novo_no; // O NOvo nó aponta para si mesmo
    } else {
        novo_no->proximo = lista[indice]->proximo; // O NOvo nó aponta para o primeiro nó da lista
        lista[indice]->proximo = novo_no; // O último nó aponta para o NOvo nó
    }
}

void ativarNO(NO* lista[], int numero) {
    if (numero < 0 || numero >= TAMANHO_LISTA) {
        printf("Erro: número de nó inválido.\n");
        return;
    }

    if (lista[numero] != NULL) {
        lista[numero]->ativo = 1;
    } else {
        lista[numero] = criar_NO(numero, "sem recurso");
        lista[numero]->ativo = 1;
    }
}

void desativarNO(NO* lista[], int numero) {
    if (lista[numero] != NULL) {
        lista[numero]->ativo = 0;
        printf("O nó %d foi desativado.\n", numero);
    } else {
        printf("Erro: o nó %d não existe na lista.\n", numero);
    }
}

void liberarLista(NO* lista[]) {
    for (int i = 0; i < TAMANHO_LISTA; i++) {
        NO* atual = lista[i];
        while (atual != NULL) {
            NO* proximo = atual->proximo;
            free(atual);
            atual = proximo;
            if (atual == lista[i]) // Verifica se voltou ao início da lista
                break;
        }
        lista[i] = NULL; // Define o ponteiro da lista como NULL após liberar todos os nós
    }
}

void imprimirNOdosAtivos(NO* lista[]) {
    printf("Nós Ativos:\n");
    for (int i = 0; i < TAMANHO_LISTA; i++) {
        if (lista[i] != NULL && lista[i]->ativo == 1) {
            NO* atual = lista[i];
            printf(" %d -> ", atual->numero);
            NO* inicio = atual;
            do {
                printf("(%s) -> ", atual->recurso);
                atual = atual->proximo;
            } while (atual != inicio && atual != NULL); // Adicionando a verificação de atual != NULL
            printf("\n");
        }
    }
}

void imprimirLista(NO* lista[]) {
    printf("Lista Circular:\n");
    for (int i = 0; i < TAMANHO_LISTA; i++) {
        printf(" %d -> ", i);
        NO* atual = lista[i];
        if (atual != NULL) {
            NO* inicio = atual;
            do {
                printf("(%s) -> ", atual->recurso);
                atual = atual->proximo;
            } while (atual != inicio);
        }
        printf("NULL\n");
    }
}

void ligarNOsAtivados(NO* lista[]) {
    int primeiroAtivo = -1;
    for (int i = 0; i < TAMANHO_LISTA; i++) {
        if (lista[i] != NULL && lista[i]->ativo == 1) {
            primeiroAtivo = i;
            break;
        }
    }

    if (primeiroAtivo == -1) {
        return;
    }

    NO* atual = lista[primeiroAtivo];
    while (atual->proximo != lista[primeiroAtivo]) {
        atual = atual->proximo;
    }
    atual->proximo = lista[primeiroAtivo];
}

void imprimirNOsLigados(NO* lista[]) {
    for (int i = 0; i < TAMANHO_LISTA; i++) {
        NO* atual = lista[i];
        if (atual != NULL && atual->ativo == 1) {
            printf("Nó %d: ", i);
            NO* temp = atual;
            do {
                printf("%d ", temp->numero);
                temp = temp->proximo;
            } while (temp != atual);
            printf("\n");
        }
    }
}

int main() {
    NO* lista[TAMANHO_LISTA];
    for (int i = 0; i < TAMANHO_LISTA; i++) {
        lista[i] = NULL;
    }

    inserirRecurso(lista, "filme");
    inserirRecurso(lista, "musica");
    inserirRecurso(lista, "video");
    inserirRecurso(lista, "Mikenson");
    inserirRecurso(lista, "Shella");

    imprimirLista(lista);

    printf("-------------------------------\n");

    ativarNO(lista, 0);
    ativarNO(lista, 3);
    ativarNO(lista, 4);

    imprimirNOdosAtivos(lista);

    printf("-------------------------------\n");

    desativarNO(lista, 4);

    printf("-------------------------------\n");

    imprimirNOdosAtivos(lista);

    printf("------------------------------\n");

    //imprimirNOsLigados(lista);

    liberarLista(lista);

    return 0;
}
