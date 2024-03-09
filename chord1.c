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
    // Alocar memória para a string de recurso e copiar o conteúdo
    novoNo->recurso = (char*)malloc(strlen(recurso) + 1); // +1 para o caractere nulo
    if (novoNo->recurso == NULL) {
        printf("Erro: não foi possível alocar memória para o recurso.\n");
        free(novoNo); // Liberar a memória alocada para o novo nó
        exit(EXIT_FAILURE);
    }
    strcpy(novoNo->recurso, recurso);
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
    if (numero < 0 || numero >= TAMANHO_LISTA) {
        printf("Erro: número de nó inválido.\n");
        return;
    }

    if (lista[numero] != NULL) {
        lista[numero]->ativo = 1;
        //printf("O nó %d foi ativado.\n", numero);
    } else {
        // Se o nó não existe, criamos um novo nó vazio e o marcamos como ativo
        lista[numero] = criarNO(numero, "sem recurso");
        lista[numero]->ativo = 1;
        //printf("O nó %d foi ativado.\n", numero);
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

void imprimirNodosAtivos(NO* lista[]) {
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

void ligarNosAtivados(NO* lista[]) {
    // Encontrar o primeiro nó ativo
    int primeiroAtivo = -1;
    for (int i = 0; i < TAMANHO_LISTA; i++) {
        if (lista[i] != NULL && lista[i]->ativo == 1) {
            primeiroAtivo = i;
            break;
        }
    }

    // Se não há nenhum nó ativo, não há nada a fazer
    if (primeiroAtivo == -1) {
        return;
    }

    // Recriar a ligação entre os nós ativos
    NO* atual = lista[primeiroAtivo];
    while (atual->proximo != lista[primeiroAtivo]) {
        atual = atual->proximo;
    }
    atual->proximo = lista[primeiroAtivo];
}


void imprimirNosLigados(NO* lista[]) {
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
    // Inicializando a lista com NULL
    NO* lista[TAMANHO_LISTA];
    for (int i = 0; i < TAMANHO_LISTA; i++) {
        lista[i] = NULL;
    }

    // Exemplo de inserção de recursos
    inserirRecurso(lista, "filme");
    inserirRecurso(lista, "musica");
    inserirRecurso(lista, "video");
    inserirRecurso(lista, "Mikenson");
    inserirRecurso(lista, "Shella");

    // Exemplo de impressão da lista
    imprimirLista(lista);


    printf("-------------------------------\n");

    // Ativar um nó na lista
    ativarNo(lista, 0);
    ativarNo(lista, 3);
    ativarNo(lista, 4);
    // Imprimir os nós ativos e seus nós ligados
    imprimirNodosAtivos(lista);

     printf("-------------------------------\n");

    desativarNo(lista, 4);

     printf("-------------------------------\n");

    imprimirNodosAtivos(lista);

    printf("------------------------------\n");

    printf("Os nós ligados: \n");

    imprimirNosLigados(lista);

    // Liberar memória alocada
    liberarLista(lista);

    return 0;
}
