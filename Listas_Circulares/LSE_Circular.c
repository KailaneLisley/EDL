// LSE CIRCULAR - Não Ordenada e SEM Repetidos

#define TRUE 1
#define FALSE 0
#include <stdlib.h>
#include <stdio.h>

typedef struct noLSECirc {
    int info;
    struct noLSECirc* prox;
} NoLSEC;

typedef struct descritor {
    NoLSEC* inicio;
    NoLSEC* fim;
    int qtd;
} Descritor;

Descritor* criarLista();
NoLSEC* criarNo(int valor);
NoLSEC* buscar (Descritor* l, int valor);
int isEmpty(Descritor* l);
void inserirInicio(Descritor* l, int valor);
void inserirFinal(Descritor* l, int valor);
void removerInicio(Descritor* l);
void removerFinal(Descritor* l);
void removerValor(Descritor* l, int valor);
void exibirValores(Descritor* l);
void removerTodos(Descritor* l);

void exibirOpcoes() {
    printf("\n = = = = = = O P C O E S = = = = = = : \n");
    printf("1 – Inserir valor no início da lista \n");
    printf("2 – Inserir valor no final da lista \n");
    printf("3 – Remover primeiro da lista \n");
    printf("4 – Remover último da lista \n");
    printf("5 – Remover um valor específico \n");
    printf("6 – Exibir todos os valores da lista \n");
    printf("7 – Remover todos os valores da lista \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main () {
    Descritor* listaInteiros = criarLista();
    int op, num;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        switch(op) {
            case 1:
                printf("Informe o valor a ser inserido: ");
                scanf("%d", &num);
                inserirInicio(listaInteiros, num);
                break;
            case 2:
                printf("Informe o valor a ser inserido: ");
                scanf("%d", &num);
                inserirFinal(listaInteiros, num);
                break;
            case 3:
                removerInicio(listaInteiros);
                break;
            case 4:
                removerFinal(listaInteiros);
                break;
            case 5:
                printf("Informe o valor a ser removido: ");
                scanf("%d", &num);
                removerValor(listaInteiros, num);
                break;
            case 6:
                printf("\n= = = = L I S T A = = = =\n");
                exibirValores(listaInteiros);
                break;
            case 7:
                removerTodos(listaInteiros);
                break;
            case 0:
                removerTodos(listaInteiros);
                printf("Fim de programa! \n");
                break;
            default: 
                printf("Opção inválida.\n");
        }
    } while (op != 0);
    return 0;
}

Descritor* criarLista(){
    Descritor* aux;
    aux = (Descritor*) malloc (sizeof(Descritor));
    aux->inicio = NULL;
    aux->fim = NULL;
    aux-> qtd = 0;
    return aux;
}

NoLSEC* criarNo (int valor) {
    NoLSEC* novo;
    novo = (NoLSEC*) malloc (sizeof(NoLSEC));
    novo->info = valor;
    novo->prox = NULL;
    return novo;
}

NoLSEC* buscar (Descritor* l, int valor) { 
    NoLSEC* aux;
    if (isEmpty(l) == TRUE) {
        return NULL;
    }
    else {
        aux = l->inicio;
        for (int i = 1; i <= l->qtd; i++) {
            if (aux->info == valor) {
                return aux;
            }
            aux = aux->prox;
        }
        return NULL;
    }
}

int isEmpty(Descritor* l) {
    if (l->qtd == 0) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

void inserirInicio(Descritor* l, int valor){
    NoLSEC* novo;
    novo = criarNo(valor);
    if (isEmpty(l) == TRUE) { 
        l->inicio = novo;
        l->fim = novo;
        l->qtd = 1;
        l->fim->prox = l->inicio;  
    }
    else { 
        if(buscar(l, valor) != NULL){
            printf("\nValor já existe na lista!\n");
            return;
        }
        novo->prox = l->inicio;
        l->inicio = novo;
        l->qtd++;
        l->fim->prox = l->inicio;  
    }
}

void inserirFinal (Descritor* l, int valor) {
    NoLSEC* novo;
    novo = criarNo(valor);
    if (isEmpty(l) == TRUE) { 
        l->inicio = novo;
        l->fim = novo;
        l->qtd = 1;
        l->fim->prox = l->inicio;  
    }
    else { 
        if(buscar(l, valor) != NULL){
            printf("\nValor já existe na lista!\n");
            return;
        }
        l->fim->prox = novo;
        l->fim = novo;
        l->qtd++;
        l->fim->prox = l->inicio;  
    }
}

void removerInicio(Descritor* l){
    if (isEmpty(l) == TRUE) {
        printf("\nLista já está vazia!\n");
        return;
    }

    NoLSEC* aux = l->inicio;
    if (l->qtd == 1) {
        l->inicio = NULL;
        l->fim = NULL;
    } else {
        l->inicio = l->inicio->prox;
        l->fim->prox = l->inicio;
    }
    free(aux);
    l->qtd--;
}

void removerFinal(Descritor* l){
    if (isEmpty(l) == TRUE) {
        printf("\nLista já está vazia!\n");
        return;
    }

    NoLSEC* ultimo = l->fim;
    if (l->qtd == 1) {
        l->inicio = NULL;
        l->fim = NULL;
    } else {
        NoLSEC* aux = l->inicio;
        while (aux->prox != l->fim) {
            aux = aux->prox;
        }
        aux->prox = l->inicio;
        l->fim = aux;
    }
    free(ultimo);
    l->qtd--;
}

void removerValor(Descritor* l, int valor){
    if (isEmpty(l) == TRUE) {
        printf("\nLista vazia!\n");
        return;
    }

    NoLSEC* atual = l->inicio;
    NoLSEC* anterior = NULL;
    for(int i=0; i<l->qtd; i++){
            if (atual->info == valor) {
                if (atual == l->inicio) {
                    removerInicio(l);
                } else if (atual == l->fim) {
                    removerFinal(l);
                } else {
                    anterior->prox = atual->prox;
                    free(atual);
                    l->qtd--;
                }
                printf("\nValor %d removido.\n", valor);
                return;
            }
        anterior = atual;
        atual = atual->prox;
    }
    printf("\nValor %d não encontrado.\n", valor);
}

void exibirValores(Descritor* l) { 
    NoLSEC* aux;
    if (isEmpty(l) == TRUE) {
        printf ("\nLista vazia \n");
    }
    else {
        aux = l->inicio;
        do {
            printf ("%d\n",aux->info);
            aux = aux->prox;
        } while (aux != l->inicio);
        printf ("\n");
    }
}

void removerTodos(Descritor* l){
    while (isEmpty(l) == FALSE) {
        removerInicio(l);
    }
    printf("Todos os elementos foram removidos.\n");
}