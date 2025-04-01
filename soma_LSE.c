#include <stdio.h>
#include <stdlib.h>

typedef struct noLSE {
    float info;
    struct noLSE* prox;
} NoLSE;

void exibirOpcoes();
void inserirValor(NoLSE** list, float valor);
void exibirValores(NoLSE* list);
NoLSE* soma(NoLSE* l1, NoLSE* l2);
void liberarLista(NoLSE** list);

int main(){
    printf("Criando lista 1\n");
    NoLSE* L1 = NULL;
    printf("Criando lista 2\n");
    NoLSE* L2 = NULL;
    NoLSE* L3 = NULL;
    
    int op, lista;
    float num;
    do{
        exibirOpcoes();
        scanf("%d", &op);
        switch(op){
            case 1:
                printf("\nInforme o valor para inserir na lista: ");
                scanf("%f", &num);
                do{
                    printf("Deseja inserir %.2f em qual lista? (1 ou 2): ", num);
                    scanf("%d", &lista);
                    if(lista == 1){
                        inserirValor(&L1, num);
                        break;
                    } else if(lista == 2){
                        inserirValor(&L2, num);
                        break;
                    } else {
                        printf("Essa lista não existe. Tente novamente\n");
                    }
                } while(lista != 1 && lista != 2);
                break;
            case 2:
                do{
                    printf("Deseja exibir valores de qual lista? (1, 2 ou 3 para soma): ");
                    scanf("%d", &lista);
                    if(lista == 1){
                        exibirValores(L1);
                        break;
                    } else if(lista == 2){
                        exibirValores(L2);
                        break;
                    } else if(lista == 3){
                        L3 = soma(L1, L2);
                        exibirValores(L3);
                        break;
                    } else {
                        printf("Essa lista não existe. Tente novamente\n");
                    }
                } while(lista != 1 && lista != 2 && lista != 3);
                break;
            case 0:
                liberarLista(&L1);
                liberarLista(&L2);
                liberarLista(&L3);
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while(op != 0);
    return 0;
}

void exibirOpcoes(){
    printf("\nO P C O E S \n");
    printf("1 - Inserir um novo valor em uma lista \n");
    printf("2 - Exibir valores \n");
    printf("0 - Sair do programa \n");
    printf("Informe a opcao desejada: ");
}

void inserirValor(NoLSE** list, float valor){
    NoLSE* novo = (NoLSE*)malloc(sizeof(NoLSE));
    novo->info = valor;
    novo->prox = *list;
    *list = novo;
    printf("Inserção Efetivada\n");
}

void exibirValores(NoLSE* list){
    NoLSE* aux = list;
    if(aux == NULL){
        printf("Lista Vazia!\n");
    } else {
        while(aux != NULL){
            printf("%.2f ", aux->info);
            aux = aux->prox;
        }
        printf("\n");
    }
}

NoLSE* soma(NoLSE* l1, NoLSE* l2){
    NoLSE* l_soma = NULL;
    NoLSE **ptr = &l_soma;
    
    while(l1 != NULL || l2 != NULL){
        *ptr = (NoLSE*)malloc(sizeof(NoLSE));
        (*ptr)->prox = NULL;
        
        if(l1 != NULL){
            (*ptr)->info = l1->info;
            l1 = l1->prox;
        } else {
            (*ptr)->info = 0;
        }
        if(l2 != NULL){
            (*ptr)->info += l2->info;
            l2 = l2->prox;
        }
        ptr = &((*ptr)->prox);
    }
    return l_soma;
}

void liberarLista(NoLSE** list){
    NoLSE* aux;
    while(*list != NULL){
        aux = *list;
        *list = (*list)->prox;
        free(aux);
    }
}
