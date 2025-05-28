#include <stdio.h>
#include <stdlib.h>

typedef struct noLSE{
    struct info;
    struct noLSE* prox;
} NoLSE;

void exibirOpcoes();
void inserirInicio(noLSE** ptr, int n);
void exibirValoresLista(noLSE* ptr);

int main(){
    noLSE* lista = NULL;
    int op, num;
    do{
        exibirOpcoes();
        scanf("%d", &op);
        switch(op){
        case 1:
            printf("Informe o valor: ");
            scanf("%d", &num);
            inserirInicio(&lista, num);
            break;
        case 2:
            printf("Valores da lista\n");
            exibirValoresLista(lista);
            break;
        case 0: 
            printf("Até logo!");
            break;
        
        default:
            printf("opcao invalida");
            break;
        }
    } while(op!=0);
    
    return 0;
}
void exibirOpcoes(){
    printf("O P C O E S\n");
    printf("1 - Inserir um novo valor no início da lista\n");
    printf("2 - Exibir os valores da lista \n");
    printf("0 - Encerrar o programa \n");
    printf("Seleione uma opcao: ");
}
void inserirInicio(noLSE** ptr, int valor){
    noLSE* novo;
    novo = (noLSE*) malloc(sizeof(noLSE));
    novo->info = valor;
    novo->prox = NULL;
    if(*ptr == NULL){ //lista vazia
        *ptr = novo;
    }
    else{ //lista não vazia
        novo->prox = *ptr;
        *ptr = novo;
    }
    printf("Insercao efetuada!\n");
}
void exibirValoresLista(noLSE* ptr){
    noLSE* aux;
    if(ptr == NULL){
        printf("A lista esta vazia");
    }
    else {
        aux = ptr;
        while(aux!=NULL){
            printf("%d", aux->info);
            aux = aux->prox;
        }
    }
}