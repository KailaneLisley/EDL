#include <stdio.h>
#include <stdlib.h>

typedef struct noLSE{
    int info;
    struct noLSE* prox;
} NoLSE;

typedef struct descritor {
    NoLSE* prim;
    NoLSE* ult;
    int qtd;
} Descritor;

Descritor* criarLista();
NoLSE* criarNo(int valor);
void exibirOpcao();
void inserirInicio(Descritor* d, int valor);
void inserirFinal(Descritor* d, int valor);
void exibirLista(Descritor* d);
void removerInicio(Descritor* d);
void removerFinal(Descritor* d);
int contarElementos(Descritor* d);
void liberarLista(Descritor* d);

int main(){
    Descritor* lista = criarLista();
    int opcao, valor;
    do {
        exibirOpcao();
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                printf("Digite o valor: ");
                scanf("%d", &valor);
                inserirInicio(lista, valor);
                break;
            case 2:
                printf("Digite o valor: ");
                scanf("%d", &valor);
                inserirFinal(lista, valor);
                break;
            case 3:
                printf("SUA LISTA\n");
                exibirLista(lista);
                break;
            case 4:
                removerInicio(lista);
                break;
            case 5:
                removerFinal(lista);
                break;
            case 6:
                printf("Quantidade de elementos: %d\n", contarElementos(lista));
                break;
            case 0:
                printf("Encerrando programa...\n");
                liberarLista(lista);
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);
    return 0;
}

Descritor* criarLista(){
    Descritor* aux = (Descritor*) malloc(sizeof(Descritor));
    if (aux == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    aux->prim = NULL;
    aux->ult = NULL;
    aux->qtd = 0;
    return aux;
}

NoLSE* criarNo(int valor){
    NoLSE* aux = (NoLSE*) malloc(sizeof(NoLSE));
    if (aux == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    aux->info = valor;
    aux->prox = NULL;
    return aux;
}

void exibirOpcao(){
    printf("\n1 - Inserir no início\n");
    printf("2 - Inserir no final\n");
    printf("3 - Exibir lista\n");
    printf("4 - Remover início\n");
    printf("5 - Remover final\n");
    printf("6 - Contar elementos\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

void inserirInicio(Descritor* d, int valor){
    NoLSE* novo = criarNo(valor);
    if (d->qtd == 0){
        d->prim = d->ult = novo;
    } else {
        novo->prox = d->prim;
        d->prim = novo;
    }
    d->qtd++;
    printf("Inserção Efetuada!\n");
}

void inserirFinal(Descritor* d, int valor){
    NoLSE* novo = criarNo(valor);
    if (d->qtd == 0){
        d->prim = d->ult = novo;
    } else {
        d->ult->prox = novo;
        d->ult = novo;
    }
    d->qtd++;
    printf("Inserção Efetuada!\n");
}

void exibirLista(Descritor* d){
    if (d->qtd == 0) {
        printf("Lista vazia!\n");
        return;
    }
    NoLSE* aux = d->prim;
    printf("Lista: ");
    while(aux != NULL){
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

void removerInicio(Descritor* d){
    if (d->qtd == 0) {
        printf("Lista vazia! Não há elementos para remover.\n");
        return;
    }
    NoLSE* aux = d->prim;
    d->prim = aux->prox;
    free(aux);
    d->qtd--;
    if (d->qtd == 0) {
        d->ult = NULL;
    }
    printf("Remoção Efetuada!\n");
}

void removerFinal(Descritor* d){
    if (d->qtd == 0) {
        printf("Lista vazia! Não há elementos para remover.\n");
        return;
    }
    if (d->qtd == 1) {
        free(d->prim);
        d->prim = d->ult = NULL;
    } else {
        NoLSE* aux = d->prim;
        while (aux->prox != d->ult) {
            aux = aux->prox;
        }
        free(d->ult);
        d->ult = aux;
        d->ult->prox = NULL;
    }
    d->qtd--;
    printf("Remoção Efetuada!\n");
}

int contarElementos(Descritor* d){
    return d->qtd;
}

void liberarLista(Descritor* d){
    NoLSE* aux = d->prim;
    while (aux != NULL) {
        NoLSE* temp = aux;
        aux = aux->prox;
        free(temp);
    }
    free(d);
}