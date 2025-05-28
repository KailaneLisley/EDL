//LDE com nó descritor e com valores repetidos 

#include <stdio.h>           
#include <stdlib.h> 

#define TRUE 1
#define FALSE 0

typedef struct noLDE { 
    struct noLDE* ant;    
    int info;              
    struct noLDE* prox;   
} NoLDE;

typedef struct descritor{   
    NoLDE* prim;                                         
    int qtd;  
    NoLDE* ult;                                           
} Descritor;

Descritor* criarLista ();
NoLDE* criarNo(int valor);
void exibirOpcao();
int isEmpty (Descritor* l);
void inserirInicio (Descritor* l, int valor);
void inserirFinal (Descritor* l, int valor);
void exibirCrescente (Descritor* l);
void exibirDecrescente (Descritor* l);
void removerInicio (Descritor* l);
void removerFinal (Descritor* l);
void removerValor(Descritor* l, int valor);
void esvaziarLista(Descritor* l);
void liberarLista(Descritor* l);

int main(){
    Descritor* lista;
    lista = criarLista();
    int op, valor, num;
    do {
        exibirOpcao();
        scanf("%d", &op);
        
        switch(op){
            case 1:
                printf("\nDigite o valor: ");
                scanf("%d", &valor);
                inserirInicio(lista, valor);
                break;
            case 2:
                removerInicio(lista);
                break;
            case 3:
                printf("\nDigite o valor: ");
                scanf("%d", &valor);
                inserirFinal(lista, valor);
                break;
            case 4:
                removerFinal(lista);
                break;
            case 5:
                printf("\nVALORES DE FORMA CRESCENTE\n");
                exibirCrescente(lista);
                break;
            case 6:
                printf("\nVALORES DE FORMA DECRESCENTE\n");
                exibirDecrescente(lista);
                break;
            case 7:
                printf("\nValor para ser removido: ");
                scanf("%d", &num);
                removerValor(lista, num);
                break;
            case 8:
                esvaziarLista(lista);
                printf("\nLista esvaziada.\n");
                break;
            case 0:
                printf("\nEncerrando programa...\n");
                liberarLista(lista);
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(op != 0);

    return 0;
}

Descritor* criarLista (){                              
    Descritor* l = (Descritor*)malloc(sizeof(Descritor));     
    if (l == NULL) {                               
        printf("Erro ao alocar memória!\n");      
        return NULL;
    }    
    l->prim = NULL; 
    l->qtd = 0;       
    l->ult = NULL;       
    return l;                                         
}

NoLDE* criarNo(int valor){                          
    NoLDE* novo = (NoLDE*)malloc(sizeof(NoLDE));            
    if (novo == NULL) {                               
        printf("Erro ao alocar memória!\n");           
        return NULL;
    } 
    novo->ant = NULL;
    novo->info = valor;                             
    novo->prox = NULL;                               
    return novo;                               
}

void exibirOpcao(){
    printf("\n=========== O P Ç Õ E S ===========\n");
    printf("\n1 - Inserir valor no início da lista\n");
    printf("2 - Remover o primeiro valor da lista\n");
    printf("3 - Inserir valor no fim da lista\n");
    printf("4 - Remover o último valor da lista\n");
    printf("5 - Exibir valores (Crescente)\n");
    printf("6 - Exibir valores (Decrescente)\n");
    printf("7 - Remover um valor específico (todos os repetidos)\n");
    printf("8 - Esvaziar Lista\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

//Verifica se a estrutura está vazia
int isEmpty (Descritor* l){
    if(l->qtd==0){
        return TRUE; //1 = true
    } 
    else {
        return FALSE; //0 = false
    }
}

void inserirInicio (Descritor* l, int valor){
    NoLDE* novo = criarNo(valor);
    if (novo == NULL) {                               
        printf("Erro ao alocar memória!\n");           
        return;
    } 
    if (isEmpty(l)==TRUE){ 
        l->prim = novo;
        l->ult = novo;
    }
    else {
        novo->prox = l->prim;
        l->prim->ant = novo;
        l->prim = novo;
    }
    l->qtd++;
}

void inserirFinal (Descritor* l, int valor){
    NoLDE* novo = criarNo(valor);
    if (novo == NULL) {                               
        printf("Erro ao alocar memória!\n");           
        return;
    } 
    if (isEmpty(l)==TRUE){
        l->prim = novo;
        l->ult = novo;
    } 
    else {
        novo->ant = l->ult;
        l->ult->prox = novo;
        l->ult = novo;
    }
    l->qtd++;
}

void exibirCrescente(Descritor* l){
    NoLDE* aux;
    if(isEmpty(l)==TRUE){
        printf("Lista Vazia!\n");
    }
    else{
        aux = l->prim;
        printf("Lista: \n");
        while(aux!=NULL){
            printf("Valor: %d\n", aux->info);
            aux = aux->prox;
        }
    }
    printf("\n");
}
void exibirDecrescente (Descritor* l){
    NoLDE* aux;
    if(isEmpty(l)==TRUE){
        printf("Lista Vazia!\n");
    }
    else{
        aux = l->ult;
        printf("Lista Inversa: \n");
        while(aux!=NULL){
            printf("Valor: %d\n", aux->info);
            aux = aux->ant;
        }
    }
    printf("\n");
}

void removerInicio (Descritor* l){
    NoLDE* aux;
    if (isEmpty(l)==TRUE){ 
        printf("A Lista já está vazia!\n");
        return;
    }
    else if (l->qtd == 1){
        free(l->prim); 
        l->prim = NULL;
        l->ult = NULL;
        l->qtd = 0;
    }
    else {
        aux = l->prim->prox; 
        l->prim = aux;
        free(aux->ant);
        aux->ant = NULL;
        l->qtd--;
    }
    printf("Primeiro elemento removido.\n");
}

void removerFinal (Descritor* l){
    NoLDE* aux;
    if (isEmpty(l)==TRUE){ 
        printf("A Lista já está vazia!\n");
        return;
    }
    else if (l->qtd == 1){
        free(l->ult);
        l->prim = NULL;
        l->ult = NULL;
        l->qtd = 0;
    }
    else {
        aux = l->ult->ant;
        l->ult = aux;
        free(aux->prox); 
        aux->prox = NULL;
        l->qtd--;
    }
    printf("Último elemento removido.\n");
}

void removerValor(Descritor* l, int valor){
    if (isEmpty(l) == TRUE){ 
        printf("A Lista já está vazia.\n");
        return;
    }

    NoLDE* atual = l->prim;
    int removidos = 0;

    while (atual != NULL) {
        NoLDE* proximo = atual->prox;

        if (atual->info == valor) {
            if (atual->ant != NULL) {
                atual->ant->prox = atual->prox;
            } else {
                l->prim = atual->prox; 
            }

            if (atual->prox != NULL) {
                atual->prox->ant = atual->ant;
            } else {
                l->ult = atual->ant; 
            }

            free(atual);
            l->qtd--;
            removidos++;
        }

        atual = proximo;
    }

    if (removidos > 0)
        printf("%d ocorrência(s) do valor %d removida(s).\n", removidos, valor);
    else
        printf("Valor %d não encontrado na lista.\n", valor);
}

void esvaziarLista(Descritor* l){
    if (isEmpty(l)==TRUE) {
        printf("Lista Vazia!\n");
        return; 
    }
    NoLDE* atual = l->prim;
    NoLDE* proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    l->prim = NULL;
    l->ult = NULL;
    l->qtd = 0;
}

void liberarLista(Descritor* l){
    if (l == NULL){
        return; 
    } 
        esvaziarLista(l); 
        free(l);
    
}