#include <stdio.h>
#include <stdlib.h>

#define TAM 10 // Tamanho da tabela hash

// Estrutura para o nó da lista circular
typedef struct no {
    int chave;
    struct no* proximo;
} no;

// Estrutura para a lista
typedef struct {
    no* inicio;
    int tam;
} Lista;

// Função hash (resto da divisão)
int funcaoHash(int chave) {
    return chave % TAM;
}

// Inicializa uma lista vazia
void inicializarLista(Lista* l) {
    l->inicio = NULL;
    l->tam = 0;
}

// Insere um elemento no início da lista
void inserirNaLista(Lista* l, int valor) {
    no* novo = (no*)malloc(sizeof(no));
    if (novo) {
        novo->chave = valor;
        novo->proximo = l->inicio;
        l->inicio = novo;
        l->tam++;
    } else {
        printf("\nErro ao alocar memória!\n");
    }
}

// Busca um elemento na lista
int buscarNaLista(Lista* l, int valor) {
    no* aux = l->inicio;
    while (aux && aux->chave != valor) {
        aux = aux->proximo;
    }
    if (aux) {
        return aux->chave;
    }
    return 0;
}

// Imprime a lista
void imprimirLista(Lista* l) {
    no* aux = l->inicio;
    printf("Tam: %d: ", l->tam);
    while (aux) {
        printf("%d ", aux->chave);
        aux = aux->proximo;
    }
    printf("\n");
}

// Inicializa toda a tabela com listas vazias
void inicializarTabela(Lista t[]) {
    for (int i = 0; i < TAM; i++) {
        inicializarLista(&t[i]);
    }
}

// Insere um elemento na tabela hash
void inserir(Lista t[], int valor) {
    int id = funcaoHash(valor);
    inserirNaLista(&t[id], valor);
}

int main() {
    Lista tabela[TAM];
    inicializarTabela(tabela);

    // Exemplo de inserção
    inserir(tabela, 42);
    inserir(tabela, 17);

    // Exemplo de busca
    int resultado = buscarNaLista(&tabela[funcaoHash(42)], 42);
    if (resultado) {
        printf("Elemento encontrado: %d\n", resultado);
    } else {
        printf("Elemento não encontrado.\n");
    }

    // Exemplo de impressão
    for (int i = 0; i < TAM; i++) {
        printf("Lista %d: ", i);
        imprimirLista(&tabela[i]);
    }

    return 0;
}