// Exemplo da aula
#include <stdio.h>
#include <stdlib.h>

typedef struct noLSE {
    int info;
    struct noLSE* prox;
} NoLSE;

void inserirOrdenado (NoLSE** ptr, int valor);
void removerInicio (NoLSE ** ptr);
void removerFinal (NoLSE ** ptr);
void exibirValores (NoLSE* ptr);
int contar (NoLSE* ptr); 
int buscar (NoLSE* ptr, int valor); 
void exibeOpcoes();

int main () {
    NoLSE* lista = NULL;
    int op, num, result;
    do {
        exibeOpcoes();
        scanf ("%d",&op);
        switch(op) {
            case 1: printf ("Informe o valor: ");
                    scanf ("%d",&num);
                    inserirOrdenado(&lista,num);
                    break;
            case 2: removerInicio (&lista);
                    break;
            case 3: removerFinal (&lista);
                    break;
            case 4: exibirValores (lista);
                    break;
            case 5: result = contar (lista);
                    printf ("A lista possui %d elementos \n", result);
                    break;
            case 6: printf ("Informe o valor: ");
                    scanf ("%d",&num);
                    result = buscar (lista, num);
                    printf ("O elemento %d aparece %d vez(es) na lista \n", num, result);
                    break;
            case 0: printf ("Bye bye \n");
                    break;
            default: printf ("Opcao invalida \n");
        }
    } while (op != 0);
    return 0;
}

void inserirOrdenado (NoLSE** ptr, int valor) {
    NoLSE* novo,* anterior,* atual;
    if(*ptr == NULL){//caso1 : inserção em lista vazia
        novo=(NoLSE*)malloc(sizeof(NoLSE));
        novo->info=valor;
        novo->prox=NULL;
        *ptr=novo;
        printf("Inserção efetuada!\n");
    }else{//Lista não vazia
        if(valor==(*ptr)->info){
            printf("Valor Repetido, inserção não efewtuada!\n");
        }else if(valor<(*ptr)->info){
            novo=(NoLSE*)malloc(sizeof(NoLSE));
            novo->info=valor;
            novo->prox=*ptr;
            *ptr=novo;
            printf("Inserção efetuada!\n");

        }else{
            anterior = *ptr;
            atual = anterior->prox;
            while(atual!=NULL){
                if(valor == atual->info){//conferindo se a valores repetidos
                    printf("Valor Repetido, inserção não efewtuada!\n");
                    return;
                }else if(valor<atual->info){//inserir no meio
                    novo=(NoLSE*)malloc(sizeof(NoLSE));
                    novo->info=valor;
                    novo->prox=*ptr;
                    *ptr=novo;
                    printf("Inserção efetuada!\n");
                    return;
                }else{//andando para o proximo nó
                    anterior=atual;
                    atual=atual->prox;
                }
            }
            novo=(NoLSE*)malloc(sizeof(NoLSE));
            novo->info=valor;
            novo->prox=NULL;
            anterior->prox=novo;
        }
    }
}

void removerInicio (NoLSE ** ptr) {
    NoLSE* aux;
    if (*ptr == NULL) {
        printf ("Lista vazia \n");
    }
    else {
        aux = *ptr;
        *ptr = (*ptr)->prox;
        free(aux);
        printf ("Remocao efetuada! \n");
    }
}

void removerFinal (NoLSE ** ptr) {
    NoLSE *anterior, *atual;
    if (*ptr == NULL) {
        printf ("Lista vazia \n");
    }
    else if ((*ptr)->prox == NULL) {
        free (*ptr);
        *ptr = NULL;
        printf ("Remocao efetuada! \n");
    }
    else {
        anterior = *ptr;
        atual = anterior->prox;
        while (atual->prox != NULL) {
            anterior = atual;
            atual = atual->prox;
        }
        free(atual);
        anterior->prox = NULL;
        printf ("Remocao efetuada! \n");
    }
}

void exibirValores (NoLSE* ptr) {
    NoLSE* aux;
    if (ptr == NULL) {
        printf ("A lista esta vazia! \n");
    }
    else {
        aux = ptr;
        while (aux != NULL) {
            printf ("%d ", aux->info);
            aux = aux->prox;
        }
        printf ("\n");
    }
}

int contar (NoLSE* ptr) {
    NoLSE* aux;
    int cont = 0;
    if (ptr == NULL) {
        return 0;
    }
    else {
        aux = ptr;
        while (aux != NULL) {
            cont++;
            aux = aux->prox;
        }
        return cont;
    }
}

int buscar (NoLSE* ptr, int valor) {
    NoLSE* aux;
    int cont = 0;
    if (ptr == NULL) {
        return 0;
    }
    else {
        aux = ptr;
        while (aux != NULL) {
            if (aux->info == valor) {
                cont++;
            }
            aux = aux->prox;
        }
        return cont;
    }
}

void exibeOpcoes () {
    printf ("Opcoes \n");
    printf ("1 - Inserir um novo valor no inicio da lista \n");
    printf ("2 - Remover o primeiro elemento da lista \n");
    printf ("3 - Remover o ultimo elemento da lista \n");
    printf ("4 - Exibir os elementos da lista \n");
    printf ("5 - Contar os elementos da lista \n");
    printf ("6 - Procurar um valor na lista \n");
    printf ("0 - Sair do programa \n");
    printf ("Informe a opcao desejada: ");
}