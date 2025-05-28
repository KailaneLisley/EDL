//LDE com nó descritor e SEM valores repetidos 

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct noLDE{
    struct noLDE* ant;
    struct noLDE* prox;
    int info;
} NoLDE;

typedef struct descritor{
    NoLDE* inicio;
    NoLDE* fim;
    int qtd;
} Descritor;

Descritor* criarLista();
NoLDE* criarNo(int valor);
void exibirOpcoes();
int isEmpty(Descritor* lista);
NoLDE * buscar(Descritor* lista, int valor);
void inserir(Descritor* lista, int valor);
void remover(Descritor* lista, int valor);
void exibirValores(Descritor* lista);
void esvaziarLista(Descritor* lista);
void liberarLista(Descritor* lista);

int main(){
    Descritor* lista = criarLista();
    int op, valor, num;
    do{
        exibirOpcoes();
        scanf("%d", &op);
        switch(op){
            case 1:
                printf("\nDigite o valor: ");
                scanf("%d", &valor);
                inserir(lista, valor);
                break;
            case 2:
                printf("Qual valor deseja remover?");
                scanf("%d", &valor);
                remover(lista, valor);
                break;
            case 3:
                printf("\n= = L I S T A = =\n");
                exibirValores(lista);
                break;
            case 4:
                esvaziarLista(lista);
                printf("Lista esvaziada!\n");
                break;
            case 0:
                liberarLista(lista);
                printf("\nEncerrando programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (op!=0);
    return 0;
}

Descritor* criarLista(){
    Descritor* d = (Descritor*) malloc (sizeof(Descritor));
    d->inicio = NULL;
    d->fim = NULL;
    d->qtd = 0;
    return d;
}

NoLDE* criarNo(int valor){
    NoLDE* novo = (NoLDE*) malloc (sizeof(NoLDE));
    novo->ant = NULL;
    novo->prox = NULL;
    novo->info = valor;
    return novo;
}

void exibirOpcoes(){
    printf("\n=========== O P Ç Õ E S ===========\n");
    printf("\n1 - Inserir valor na lista\n");
    printf("2 - Remover valor da lista\n");
    printf("3 - Exibir valores\n");
    printf("4 - Esvaziar Lista\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

int isEmpty(Descritor* lista){
    if (lista->qtd == 0) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

NoLDE * buscar(Descritor* lista, int valor){ // busca sequencial melhorada
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

void inserir(Descritor* lista, int valor){ // inserção ordenada crescente
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

void remover(Descritor* lista, int valor){
     NoLDE *aux;

    if (isEmpty(lista) == TRUE) { // lista vazia
        printf ("Não há valores pra remover. Lista vazia! \n");
        return;
    }
    else if(lista->qtd == 1){
        free(lista->inicio);
        lista->inicio = NULL;
        lista->fim == NULL;
        lista->qtd == 0;
        printf("Valor Removido. Lista Vazia!");
        return;
    }
    else if (valor == lista->inicio->info) { //remover inicio
        aux = lista->inicio->prox; 
        lista->inicio = aux;
        free(aux->ant);
        aux->ant = NULL;
        lista->qtd--;
        printf ("Primeiro valor removido \n");
        return;
    }
    else if (valor == lista->fim->info) { //remover fim
        aux = lista->fim->ant;
        lista->fim = aux;
        free(aux->prox); 
        aux->prox = NULL;
        lista->qtd--;
        printf ("Último valor removido \n");
        return;
    }
    else { // remover no "meio"
        NoLDE* encontrou = buscar(lista, valor);
        NoLDE* anterior = encontrou->ant;
        NoLDE* proximo = encontrou->prox;
        anterior->prox = proximo;
        proximo->ant = anterior;
        free(encontrou);
        printf("Valor Removido da lista!");
        return;
    }
}

void exibirValores(Descritor* lista){
    NoLDE* aux;
    if(isEmpty(lista)==TRUE){
        printf("\nLista Vazia!\n");
    }
    else{
        aux = lista->inicio;
        while(aux!=NULL){
            printf("Valor: %d\n", aux->info);
            aux = aux->prox;
        }
    }
    printf("\n");
}

void esvaziarLista(Descritor* lista){
    if (isEmpty(lista)==TRUE) {
        printf("Lista Vazia!\n");
        return; 
    }
    NoLDE* atual = lista->inicio;
    NoLDE* proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

void liberarLista(Descritor* lista){
    if (lista == NULL){
        free(lista);
        return; 
    } else {
        printf("Esvaziando Lista...\n");
        esvaziarLista(lista); 
        free(lista);
        return; 
    }
}
