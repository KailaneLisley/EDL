#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct noLSEC {
    int info;
    struct noLSEC* prox;
} NoLSEC;

typedef struct descritor {
    NoLSEC* inicio;
    NoLSEC* fim;
    int qtd;
} Descritor;

Descritor* criarLista() {
    Descritor* aux = (Descritor*) malloc(sizeof(Descritor));
    aux->inicio = aux->fim = NULL;
    aux->qtd = 0;
    return aux;
}

NoLSEC* criarNo(int valor) {
    NoLSEC* aux = (NoLSEC*) malloc(sizeof(NoLSEC));
    aux->info = valor;
    aux->prox = NULL;
    return aux;
}

void inserirFinal(Descritor* l, int valor) {
    NoLSEC* novo = criarNo(valor);
    if (isEmpty(l) == TRUE) { // Caso 1: Lista Vazia
        l->inicio = novo;
        l->fim = novo;
        l->qtd = 1;
        l->fim->prox = l->inicio; //aplicar circularidade
    } else { // Caso 2: Lista Vazia
        l->fim->prox = novo;
        l->fim = novo;
        l->qtd++;
        l->fim->prox = l->inicio; //aplicar circularidade
    }
}

void exibirLista(Descritor* l) {
    if (isEmpty(l) == TRUE) {
        printf("Lista vazia!\n");
        return;
    }
    NoLSEC* aux = l->inicio;
    printf("Lista: ");
    do{
        printf("%d ", aux->info);
        aux = aux->prox;
    } while(aux != l->inicio);
    printf("\n");
}

void buscar(Descritor* l, int valor){
    NoLSEC* aux;
    if (isEmpty(l) == TRUE) {
        printf("Lista vazia!\n");
        return NULL;
    } else {
        aux = l->inicio;
        for(int i=1; i <= l->qtd; i++){
            if(aux->info == valor){
                return aux;
            } else {
                aux = aux->prox
            }
        }
        return NULL;
    }
}

int main() {
    Descritor* lista = criarLista();

    return 0;
}