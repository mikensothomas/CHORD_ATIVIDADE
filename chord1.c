#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_LISTA 9

// Estrutura do nó da lista
typedef struct NO {
    int numero;
    char* recurso;
    int ativo; // Indicador de ativação
    struct NO* proximo; // Próximo nó na lista
} NO;

// Função de hash simples
int hash(const char* recurso) {
    int soma = 0;
    for (int i = 0; i < strlen(recurso); i++) {
        soma += recurso[i];
    }
    return soma % TAMANHO_LISTA;
}

// Função para criar um novo nó
NO* criarNO(int numero, const char* recurso) {
    NO* novoNo = (NO*)malloc(sizeof(NO));
    if (novoNo == NULL) {
        printf("Erro: não foi possível alocar memória para o novo nó.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->numero = numero;
    novoNo->recurso = strdup(recurso);
    novoNo->ativo = 0; // Inicializa como não ativo
    novoNo->proximo = NULL;
    return novoNo;
}

void inserirRecurso(NO* lista[], const char* recurso) {
    int indice = hash(recurso);
    NO* novoNo = criarNO(indice, recurso);

    if (lista[indice] == NULL) {
        lista[indice] = novoNo;
        novoNo->proximo = novoNo;
    } else {
        NO* ultimo = lista[indice]->proximo;
        while (ultimo->proximo != lista[indice]->proximo) {
            ultimo = ultimo->proximo;
        }
        novoNo->proximo = lista[indice]->proximo;
        lista[indice]->proximo = novoNo;
        ultimo->proximo = novoNo;
    }
}

// Função para ativar um nó na lista circular
void ativarNo(NO* lista[], int numero) {
    if (lista[numero] != NULL) {
        lista[numero]->ativo = 1;
        printf("O nó %d foi ativado.\n", numero);
    } else {
        // Se o nó não existe, criamos um novo nó vazio e o marcamos como ativo
        lista[numero] = criarNO(numero, "sem recurso");
        lista[numero]->ativo = 1;
        printf("O nó %d foi ativado.\n", numero);
    }
}

// Função para desativar um nó na lista
void desativarNo(NO* lista[], int numero) {
    if (lista[numero] != NULL) {
        lista[numero]->ativo = 0;
        printf("O nó %d foi desativado.\n", numero);
    } else {
        printf("Erro: o nó %d não existe na lista.\n", numero);
    }
}


// Função para imprimir os nós ativos e com quem cada um deles está ligado
void imprimirNodosAtivos(NO* lista[]) {
    printf("Nós Ativos:\n");
    for (int i = 0; i < TAMANHO_LISTA; i++) {
        if (lista[i] != NULL && lista[i]->ativo == 1) {
            printf("Nó %d (Recurso: %s) -> ", i, lista[i]->recurso);
            NO* atual = lista[i]->proximo;
            while (atual != NULL && atual != lista[i]) {
                printf("Nó %d (Recurso: %s) -> ", atual->numero, atual->recurso);
                atual = atual->proximo;
            }
            printf("\n");
        }
    }
}


void liberarLista(NO* lista[]) {
    for (int i = 0; i < TAMANHO_LISTA; i++) {
        NO* atual = lista[i];
        while (atual != NULL) {
            NO* proximo = atual->proximo;
            free(atual->recurso);
            free(atual);
            atual = proximo;
            if (atual == lista[i]) // Verifica se voltou ao início da lista
                break;
        }
        lista[i] = NULL; // Define o ponteiro da lista como NULL após liberar todos os nós
    }
}


// Função para imprimir a lista
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

int main() {
    // Inicializando a lista com NULL
    NO* lista[TAMANHO_LISTA];
    for (int i = 0; i < TAMANHO_LISTA; i++) {
        lista[i] = NULL;
    }

    // Exemplo de inserção de recursos
    inserirRecurso(lista, "filme");
    inserirRecurso(lista, "musica");
    inserirRecurso(lista, "video");

    // Exemplo de impressão da lista
    imprimirLista(lista);

    // Ativar um nó na lista
    ativarNo(lista, 0);
    ativarNo(lista, 3);
    ativarNo(lista, 4);

    desativarNo(lista, 4);

    // Imprimir os nós ativos e seus nós ligados
    imprimirNodosAtivos(lista);

    // Liberar memória alocada
    liberarLista(lista);

    return 0;
}
