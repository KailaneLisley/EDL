// Resolução da questão 3 da lista 1 de LDE 
// Código desenvolvido na aula do dia 06-05-2025

// Ordem crescente e sem repetidos
#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>

typedef struct noLDE {
    struct noLDE* ant;
    struct noLDE* prox;
    int info;
} NoLDE;

typedef struct descritor {
    NoLDE* inicio;
    NoLDE* fim;
    int qtd;
} Descritor;

Descritor* criarLista () {
    Descritor* d = (Descritor*) malloc (sizeof(Descritor));
    d->inicio = NULL;
    d->fim = NULL;
    d->qtd = 0;
    return d;
}

NoLDE* criarNo (int valor) {
    NoLDE* novo = (NoLDE*) malloc (sizeof(NoLDE));
    novo->ant = NULL;
    novo->prox = NULL;
    novo->info = valor;
    return novo;
}

int isEmpty (Descritor* lista) {
    if (lista->qtd == 0) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

NoLDE * buscar (Descritor* lista, int valor) { // busca sequencial melhorada
    NoLDE* aux = lista->inicio;
    while (aux != NULL) {
        if (aux->info == valor) {
            return aux;
        }
        else if (aux->info > valor) {
            return NULL;
        }
        else {
            aux = aux->prox;
        }
    }
    return NULL;
}

void inserir (Descritor* lista, int valor) { // inserção ordenada crescente
    NoLDE* novo, *atual, *anterior;

    if (isEmpty(lista) == TRUE) { // lista vazia
        novo = criarNo(valor);
        lista->inicio = novo;
        lista->fim = novo;
        lista->qtd++;
        printf ("Insercao efetuada! \n");
    }
    else if (valor == lista->inicio->info) {
        printf ("Valor repetido. Insercao não efetuada! \n");
    }
    else if (valor < lista->inicio->info) { // inserir no inicio
        novo = criarNo(valor);
        novo->prox = lista->inicio;
        lista->inicio->ant = novo;
        lista->inicio = novo;
        lista->qtd++;
        printf ("Insercao efetuada! \n");
    }
    else if (valor == lista->fim->info) {
        printf ("Valor repetido. Insercao não efetuada! \n");
    }
    else if (valor > lista->fim->info) { // inserir no final
        novo = criarNo(valor);
        novo->ant = lista->fim;
        lista->fim->prox = novo;
        lista->fim = novo;
        lista->qtd++;
        printf ("Insercao efetuada! \n");
    }
    else { // inserir no "meio"
        atual = lista->inicio;
        while (atual != NULL) {
            if (atual->info == valor) {
                printf ("Valor repetido. Insercao não efetuada! \n");
                return; // sair do procedimento
            }
            else if (atual->info > valor) {
                novo = criarNo(valor);
                anterior = atual->ant;
                anterior->prox = novo;
                novo->ant = anterior;
                novo->prox = atual;
                atual->ant = novo;
                lista->qtd++;
                printf ("Insercao efetuada! \n");
                return; // sair do procedimento
            }
            else {
                atual = atual->prox;
            }
        }
    }
}

// Falta implementar o exibir e o remover

int main () {
    Descritor* numeros;
    numeros = criarLista();

    // falta implementar o loop principal

   return 0;
}