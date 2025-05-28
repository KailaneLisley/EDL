// Atividade 2 – Lista Duplamente Encadeada Circular
// Aluna: Kailane Lisley de Araújo Silva
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct noLDE { 
    struct noLDE* ant;    
    int info;              
    struct noLDE* prox;   
} NoLDEC;

typedef struct descritor {   
    NoLDEC* inicio;                                          
    int qtd;  
    NoLDEC* fim;                                           
} Descritor;

void exibirOpcoes();
Descritor* criarLista ();
NoLDEC* criarNo(int valor);
int isEmpty(Descritor* lista);
void inserirFinal(Descritor* lista, int valor);
int ehIgual(Descritor* lista1, Descritor* lista2);
Descritor* copiaInversa(Descritor* lista);
void concatenar(Descritor* lista1, Descritor* lista2);
void imprimir(Descritor* lista);
void liberarLista(Descritor* lista);

int main() {
    Descritor* lista1 = criarLista();
    Descritor* lista2 = criarLista();
    int op, l, num, opcao, opc, igual;
    do{
        exibirOpcoes();
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("\nInforme o valor a ser inserido na lista: ");
                scanf("%d", &num);
                printf("Deseja inserir valor na lista 1 ou 2?: ");
                scanf("%d", &l);
                if (l == 1) {
                    inserirFinal(lista1, num);
                    printf("Valor %d inserido na Lista 1.\n", num);
                } else if(l == 2){
                    inserirFinal(lista2, num);
                    printf("Valor %d inserido na Lista 2.\n", num);
                } else {
                    printf("Opção inválida! Insira 1 ou 2.\n");
                    break;
                }
                break;
            case 2: 
                printf("\nComparando listas...\n");
                igual = ehIgual(lista1, lista2);
                if (igual == 1) {
                    printf("As listas são iguais.\n");
                } else if (igual == 0) {
                    printf("As listas são diferentes.\n");
                }
                break;
            case 3:
                printf("Deseja Copiar a inversa da:\n");
                printf("1 - Lista 1\n");
                printf("2 - Lista 2\n");
                printf("Opcao: ");
                scanf("%d", &opcao);
                if (opcao == 1) {
                    printf("Copia inversa da Lista 1\n");
                    Descritor* copia = copiaInversa(lista1);
                    imprimir(copia);
                    free(copia);
                } else if (opcao == 2) {
                    printf("Copia inversa da Lista 2\n");
                    Descritor* copia = copiaInversa(lista2);
                    imprimir(copia);
                    free(copia);
                } else {
                    printf("Opção inválida! Insira 1 ou 2.\n");
                    break;
                }
                break;
            case 4:
                printf("\nDeseja concatenar:\n");
                printf("1 - Lista 1 com Lista 2\n");
                printf("2 - Lista 2 com Lista 1\n");
                printf("Opcao: ");
                scanf("%d", &opc);
                if (opc == 1) {
                    printf("\nConcatenando Lista 1 com Lista 2...\n");
                    concatenar(lista1, lista2);
                } else if (opc == 2) {
                    printf("\nConcatenando Lista 2 com Lista 1...\n");
                    concatenar(lista2, lista1);
                } else {
                    printf("\nOpção inválida! Insira 1 ou 2.\n");
                    break;
                }
                break;
            case 5:
                printf("\n==== Lista 1 ====\n");
                imprimir(lista1);
                printf("==== Lista 2 ====\n");
                imprimir(lista2);
                break;
            case 0:
                printf("Fim do programa!\n");
                printf("Saindo...\n");
                liberarLista(lista1);
                liberarLista(lista2);
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (op != 0);

    return 0;
}

void exibirOpcoes() {
    printf("\n===== M E N U =====\n");
    printf("1 - Inserir valor em uma lista\n");
    printf("2 - Comparar listas\n");
    printf("3 - Copiar inversamente uma lista\n");
    printf("4 - Concatenar listas\n");
    printf("5 - Imprimir listas\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
}

Descritor* criarLista () {                             
    Descritor* l = (Descritor*)malloc(sizeof(Descritor));     
    if (l == NULL) {                               
        printf("Erro ao alocar memória!\n");      
        return NULL;
    }    
    l->inicio = NULL; 
    l->qtd = 0;       
    l->fim = NULL;       
    return l;                                         
}

NoLDEC* criarNo(int valor) {                          
    NoLDEC* novo = (NoLDEC*)malloc(sizeof(NoLDEC));            
    if (novo == NULL) {                               
        printf("Erro ao alocar memória!\n");           
        return NULL;
    } 
    novo->ant = NULL;
    novo->info = valor;                             
    novo->prox = NULL;                               
    return novo;                               
}

int isEmpty(Descritor* lista) {
    if (lista->qtd == 0) {
        return TRUE; 
    } else {
        return FALSE; 
    }
}

void inserirFinal(Descritor* lista, int valor) {
    NoLDEC* novo = criarNo(valor);
    if (isEmpty(lista)) { 
        lista->inicio = novo;
        lista->fim = novo;
        novo->prox = novo; 
        novo->ant = novo;
    } else { 
        novo->ant = lista->fim;
        novo->prox = lista->inicio;
        lista->fim->prox = novo;
        lista->inicio->ant = novo;
        lista->fim = novo;
    }
    lista->qtd++;
}

int ehIgual(Descritor* lista1, Descritor* lista2) {
    if (lista1->qtd != lista2->qtd) {
        return 0; // Diferentes: Quantidade de elementos diferente
    }
    if (isEmpty(lista1) && isEmpty(lista2)) {
        return 1; // Iguais: Ambas estão vazias
    }

    NoLDEC* aux1 = lista1->inicio;
    NoLDEC* aux2 = lista2->inicio;

    for (int i = 0; i < lista1->qtd; i++) {
        if (aux1->info != aux2->info) {
            return 0; // Diferentes: Elementos diferentes
        }
        aux1 = aux1->prox;
        aux2 = aux2->prox;
    }
    printf("As listas são iguais.\n");
    return 1;
}

Descritor* copiaInversa(Descritor* lista) {
    Descritor* nova = criarLista();
    if (isEmpty(lista)) return nova;

    NoLDEC* aux = lista->fim;
    int i;
    for (i = 0; i < lista->qtd; i++) {
        inserirFinal(nova, aux->info);
        aux = aux->ant;
    }
    return nova;
}

void concatenar(Descritor* lista1, Descritor* lista2) {
    if (isEmpty(lista2)) return;

    if (isEmpty(lista1)) {
        lista1->inicio = lista2->inicio;
        lista1->fim = lista2->fim;
        lista1->qtd = lista2->qtd;
        lista2->inicio = NULL;
        lista2->fim = NULL;
        lista2->qtd = 0;
        return;
    }

    lista1->fim->prox = lista2->inicio;
    lista2->inicio->ant = lista1->fim;

    lista2->fim->prox = lista1->inicio;
    lista1->inicio->ant = lista2->fim;

    lista1->fim = lista2->fim;
    lista1->qtd += lista2->qtd;

    lista2->inicio = NULL;
    lista2->fim = NULL;
    lista2->qtd = 0;
}

void imprimir(Descritor* lista) {
    if (isEmpty(lista)) {
        printf("Lista vazia\n");
        return;
    }
    NoLDEC* aux = lista->inicio;
    int i;
    for (i = 0; i < lista->qtd; i++) {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

void liberarLista(Descritor* lista) {
    if (isEmpty(lista)) {
        free(lista);
        return;
    }
    NoLDEC* atual = lista->inicio;
    NoLDEC* prox;
    int i;
    for (i = 0; i < lista->qtd; i++) {
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(lista);
}