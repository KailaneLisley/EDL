/*
Lista Simplesmente Encadeada | Atividade de EDL
(Lista de inteiros, desordenada e com repetição)
Aluna: Kailane Lisley d Araujo Silva | RA: 851345
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct LSE{
    int info;
    struct LSE* prox;
}LSE;

void exibirOpcoes();
void inserirValorInicio(LSE** ptr, int valor);
void inserirValorUltimo(LSE** ptr, int valor);
void exibirValores(LSE* ptr);
void removerValorInicio(LSE** ptr);
void removerValorUltimo(LSE** ptr);
void exibirElementos(LSE* ptr);
int contarElementos(LSE* ptr);
int procurarValor(LSE* ptr, int valor);
void liberarLista(LSE** ptr);

int main (){
    LSE* lista = NULL;
    int op, num, n_;
    do{
        exibirOpcoes();
        scanf("%d", &op);
        switch(op){
            case 1:
                printf("\nInforme o valor para inserir no início da lista: ");
                scanf("%d", &num);
                inserirValorInicio(&lista, num);
                break;
            case 2:
                printf("Informe o valor para inserir no fim da lista: ");
                scanf("%d", &num);
                inserirValorUltimo(&lista, num);
                break;
            case 3:
                printf("Remover primeiro item da lista\n");
                removerValorInicio(&lista);
                break;
            case 4:
                printf("Remover ultimo item da lista\n");
                removerValorUltimo(&lista);
                break;
            case 5:
                printf("L I S T A\n");
                exibirElementos(lista);
                break;
            case 6:
                int contador = contarElementos(lista);
                if(contador == 0){
                        printf("Não ha nada na lista");
                } else {
                    printf("Total de elementos na lista e igual a %d\n\n", contador);
                }
                break;
            case 7:
                printf("Qual valor deseja procurar? ");
                scanf("%d", &n_);
                int encontrou = procurarValor(lista, n_);
                printf("O valor %d foi encontrado %d vezes\n\n", n_, encontrou);
                break;
            case 0:
                liberarLista(&lista);
                printf("Saindo...\n");
                return 0;
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while(op!=0);
    return 0;
}
void exibirOpcoes(){
    printf ("O P C O E S \n");
    printf ("1 - Inserir um novo valor no inicio da lista \n");
    printf ("2 - Inserir um novo valor no final da lista \n");
    printf ("3 - Remover o primeiro elemento da lista \n");
    printf ("4 - Remover o ultimo elemento da lista \n");
    printf ("5 - Exibir os elementos da lista \n");
    printf ("6 - Contar os elementos da lista \n");
    printf ("7 - Procurar um valor na lista \n");
    printf ("0 - Sair do programa \n");
    printf ("Informe a opcao desejada: ");
}
void inserirValorInicio(LSE** ptr, int valor){
    LSE* novo; 
    novo = (LSE*) malloc(sizeof(LSE));
    if(novo==NULL){
        printf("ERRO!");
        return;
    }
    novo->info = valor;
    novo->prox = NULL;
    if(*ptr==NULL){
        *ptr=novo;
    } else {
        novo->prox = *ptr;
        *ptr = novo;
    }
    printf("Insercao concluida com sucesso!\n\n");
}
void inserirValorUltimo(LSE** ptr, int valor){
    LSE* novo;
    LSE* aux; 
    novo = (LSE*) malloc(sizeof(LSE));
    if(novo==NULL){
        printf("ERRO!");
        return;
    }
    novo->info = valor;
    novo->prox = NULL;
    if(*ptr==NULL){
        *ptr=novo;
        return;
    } else {
        aux = *ptr;
        while(aux->prox!=NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
    }
    printf("Insercao concluida com sucesso!\n\n");
}
void removerValorInicio(LSE** ptr){
    LSE* aux; 
    if(*ptr==NULL){
        printf("Lista ja esta vazia\n");
    } else {
        aux = *ptr;
        *ptr = (*ptr)->prox;
        free(aux);
    }
    printf("Remocao concluida com sucesso!\n\n");
}
void removerValorUltimo(LSE** ptr){
    LSE* aux, *ant; 
    if (*ptr == NULL) {
        printf("Lista ja esta vazia\n");
    } else if ((*ptr)->prox == NULL){ 
        free(*ptr);
        *ptr = NULL;
    } else {
        aux = *ptr;
        while (aux->prox != NULL) {
            ant = aux;
            aux = aux->prox;
        }
        ant->prox = NULL;  
        free(aux); 
    }
    printf("Remocao concluida com sucesso!\n\n");
}
void exibirElementos(LSE* ptr){
    LSE* aux;
    if(ptr==NULL){
        printf("Lista Vazia!\n");
    } else {
        aux = ptr;
        while(aux!=NULL){
            printf("%d\n", aux->info);
            aux = aux->prox;
        }
    }
}
int contarElementos(LSE* ptr){
    LSE* aux;
    int cont=0;
    if(ptr==NULL){
        return 0; 
    } else {
        aux = ptr;
        while(aux!=NULL){
            cont++;
            aux = aux->prox;
        }
    }
    return cont;
}
int procurarValor(LSE* ptr, int valor){
    LSE* aux;
    int cont=0;
    if(ptr==NULL){
        return 0; 
    } else {
        aux = ptr;
        while(aux!=NULL){
            if(aux->info == valor){
                cont++;
            }
            aux = aux->prox;
        }
    }
    return cont;
}
void liberarLista(LSE** ptr) {
    LSE* aux;
    while (*ptr != NULL) {
        aux = *ptr;
        *ptr = (*ptr)->prox;
        free(aux);
    }
    printf("Memoria liberada!\n");
}
