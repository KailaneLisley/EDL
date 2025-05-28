/*
Lista Simplesmente Encadeada | Atividade de EDL
(Lista de inteiros, desordenada e SEM repetição de números)
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
void removerValorEspecifico(LSE** ptr, int valor);
LSE* buscarValor(LSE* ptr, int valor);
void liberarLista(LSE** ptr);
int contarElementos(LSE* ptr);

int main (){
    LSE* lista = NULL;
    int op, num;
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
            printf("Informe o valor a ser removido: ");
                scanf("%d", &num);
                removerValorEspecifico(&lista, num);
                break;
            case 6:
                printf("\nL I S T A\n");
                exibirValores(lista);
                break;
            case 7:
                printf("Total de elementos na lista: %d\n\n", contarElementos(lista));
                break;
            case 8:
                printf("Informe o valor a ser buscado: ");
                scanf("%d", &num);
                if (buscarValor(lista, num) != NULL)
                    printf("Valor encontrado na lista!\n");
                else
                    printf("Valor não encontrado.\n");
                break;
            case 0:
                liberarLista(&lista);
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while(op!=0);
    return 0;
}

void exibirOpcoes(){
    printf("\nO P C O E S \n");
    printf("1 - Inserir um novo valor no inicio da lista \n");
    printf("2 - Inserir um novo valor no final da lista \n");
    printf("3 - Remover o primeiro elemento da lista \n");
    printf("4 - Remover o ultimo elemento da lista \n");
    printf("5 - Remover um valor específico \n");
    printf("6 - Exibir os elementos da lista \n");
    printf("7 - Contar os elementos da lista \n");
    printf("8 - Buscar um valor \n");
    printf("0 - Sair do programa \n");
    printf("Informe a opcao desejada: ");
}

void inserirValorInicio(LSE** ptr, int valor){
    if (buscarValor(*ptr, valor) != NULL) {
        printf("Erro: valor já existe na lista!\n");
        return;
    }
    LSE* novo = (LSE*) malloc(sizeof(LSE));
    if (novo == NULL) {
        printf("Erro: memória insuficiente!\n");
        return;
    }
    novo->info = valor;
    novo->prox = *ptr;
    *ptr = novo;
    printf("Inserção concluída com sucesso!\n\n");
}

void inserirValorUltimo(LSE** ptr, int valor){
    if (buscarValor(*ptr, valor) != NULL) {
        printf("Erro: valor já existe na lista!\n");
        return;
    }
    LSE* novo = (LSE*) malloc(sizeof(LSE));
    if (novo == NULL) {
        printf("Erro: memória insuficiente!\n");
        return;
    }
    novo->info = valor;
    novo->prox = NULL;
    if (*ptr == NULL) {
        *ptr = novo;
    } else {
        LSE* aux = *ptr;
        while(aux->prox != NULL) aux = aux->prox;
        aux->prox = novo;
    }
    printf("Inserção concluída com sucesso!\n\n");
}

void removerValorInicio(LSE** ptr){
    if(*ptr == NULL){
        printf("Lista já está vazia\n");
        return;
    }
    LSE* aux = *ptr;
    *ptr = (*ptr)->prox;
    free(aux);
    printf("Remoção concluída com sucesso!\n\n");
}

void removerValorUltimo(LSE** ptr){
    if (*ptr == NULL) return;
    if ((*ptr)->prox == NULL){ 
        free(*ptr);
        *ptr = NULL;
    } else {
        LSE *aux = *ptr, *ant = NULL;
        while (aux->prox != NULL) {
            ant = aux;
            aux = aux->prox;
        }
        ant->prox = NULL;
        free(aux);
    }
    printf("Remoção concluída com sucesso!\n\n");
}

void removerValorEspecifico(LSE** ptr, int valor){
    LSE* atual = *ptr, *anterior = NULL;
    while (atual != NULL && atual->info != valor) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL) {
        printf("Valor não encontrado na lista.\n");
        return;
    }
    if (anterior == NULL) {
        *ptr = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    free(atual);
    printf("Valor removido com sucesso!\n");
}

void exibirValores(LSE* ptr){
    while(ptr != NULL){
        printf("%d\n", ptr->info);
        ptr = ptr->prox;
    }
    printf("\n");
}

int contarElementos(LSE* ptr){
    int cont = 0;
    while(ptr != NULL){
        cont++;
        ptr = ptr->prox;
    }
    return cont;
}

LSE* buscarValor(LSE* ptr, int valor){
    while(ptr != NULL){
        if(ptr->info == valor)
            return ptr;
        ptr = ptr->prox;
    }
    return NULL;
}

void liberarLista(LSE** ptr) {
    while (*ptr != NULL) {
        LSE* aux = *ptr;
        *ptr = (*ptr)->prox;
        free(aux);
    }
    printf("Memória liberada!\n");
}