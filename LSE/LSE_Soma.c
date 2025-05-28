#include <stdio.h>
#include <stdlib.h>

typedef struct noLSE {
    float info;
    struct noLSE* prox;
} NoLSE;

NoLSE* somar(NoLSE* l1, NoLSE* l2);

int main(){
    NoLSE* L1 = NULL;
    NoLSE* L2 = NULL;
    NoLSE* L3 = NULL;
    int num;

    printf("Preencher lista 1");
    printf("Informe um nº inteiro ou zero para encerrar: ");
    scanf("%d", &num);
    while(num!=0){
        inserirInicio(&L1, num);
        printf("Informe um nº inteiro ou zero para encerrar: ");
        scanf("%d", &num);
    }

    printf("Preencher lista 2");
    printf("Informe um nº inteiro ou zero para encerrar: ");
    scanf("%d", &num);
    while(num!=0){
        inserirInicio(&L2, num);
        printf("Informe um nº inteiro ou zero para encerrar: ");
        scanf("%d", &num);
    }

    L3 = somar(L1, L2);
    prinf("Soma das listas");
    exibir(L3);

    return 0;
}

void inserirFinal(NoLSE** lista, int valor){
    NoLSE* novo;
    NoLSE* aux; 
    novo = (NoLSE*) malloc(sizeof(NoLSE));
    novo->info = valor;
    novo->prox = NULL;
    if(*lista==NULL){
        *lista=novo;
    } else {
        aux = *lista;
        while(aux->prox!=NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
    }
    printf("Insercao concluida com sucesso!\n\n");
}

NoLSE* somar(NoLSE* l1, NoLSE* l2){
    NoLSE* aux1;
    NoLSE* aux2;
    NoLSE* ult;
    NoLSE* novo;
    NoLSE* l3 = NULL;
    int valor;
    aux1 = l1;
    aux2 = l2;
    while(aux1 != NULL && aux2 != NULL){
        valor = aux1->info + aux2->info;
        novo =(NoLSE*)malloc(sizeof(NoLSE));
        novo->info = valor;
        novo->prox = NULL;

        inserirFinal(&l3, valor);
        aux1 = aux1->prox;
        aux2 = aux2->prox;
    }
    if(aux1 == NULL && aux2 == NULL){
        return l3;
    } else if(aux1 != NULL){
        while(aux1 != NULL){
            valor = aux1->info;
            inserirFinal (&l3, valor);
            aux1 = aux1->prox;
        }
        return l3;
    } else {
        while(aux2 != NULL){
            valor = aux2->info;
            inserirFinal (&l3, valor);
            aux2 = aux2->prox;
        }
        return l3;
    }
}