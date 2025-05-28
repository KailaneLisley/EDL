//LDE desordenada e sem valores repetidos
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
    NoLDE* inicio;                                         
    int qtd;  
    NoLDE* fim;                                           
} Descritor;

Descritor* criarLista ();
NoLDE* criarNo(int valor);
void exibirOpcao();
int isEmpty (Descritor* l);
void inserirFinal (Descritor* l, int valor);
void removerValor(Descritor* l, int valor);
void exibirValores(Descritor* l);
void intersecaoListas(Descritor* a, Descritor* b, Descritor* inter);
void uniaoListas(Descritor* a, Descritor* b, Descritor* uniao);
void esvaziarLista(Descritor* l);
void liberarListas(Descritor* a,Descritor* b, Descritor* inter, Descritor* uniao);

int main(){
    Descritor* A = criarLista();
    Descritor* B = criarLista();
    Descritor* Intersecao = criarLista();
    Descritor* Uniao = criarLista();

    int op, valor, num;
    char lista;
    do {
        exibirOpcao();
        scanf("%d", &op);
        
        switch(op){
            case 1:
                printf("\nEm qual lista deseja inserir o valor?(A|B): ");
                while ((getchar()) != '\n');
                scanf("%c", &lista);

                do{
                    printf("\nDigite o valor a ser inserido: ");
                    scanf("%d", &valor);
                    if(valor!=0){
                        if(lista == 'a' || lista =='A'){
                            inserirFinal(A, valor);
                        } else if(lista == 'b' || lista =='B'){
                            inserirFinal(B, valor);
                        }
                    }
                }while(valor!=0);
                break;
            case 2:
                printf("\nDigite o valor a ser removido: ");
                scanf("%d", &valor);
                printf("\nEm qual lista deseja?(A|B): ");
                while ((getchar()) != '\n');
                scanf("%c", &lista);

                if(lista == 'a' || lista =='A'){
                    removerValor(A, valor);
                } else if(lista == 'b' || lista =='B'){
                    removerValor(B, valor);
                }
            break;
            case 3:
                printf("\nQual lista deseja exibir?(A|B): ");
                while ((getchar()) != '\n');
                scanf("%c", &lista);
                printf("\nVALORES DA LISTA %s\n", lista);
                if(lista == 'a' || lista =='A'){
                    exibirValores(A);
                } else if(lista == 'b' || lista =='B'){
                    exibirValores(B);
                }
                break;
            case 4:
                intersecaoListas(A, B, Intersecao);
            break;
            case 5:
                uniaoListas(A, B, Uniao);
            break;
            case 6:
                printf("\nQual lista deseja esvaziar?(A|B): ");
                while ((getchar()) != '\n');
                scanf("%c", &lista);
                if(lista == 'a' || lista =='A'){
                    esvaziarLista(A);
                } else if(lista == 'b' || lista =='B'){
                    esvaziarLista(B);
                }
                printf("\nLista %c esvaziada.\n", lista);
                break;
            case 0:
                printf("\nEncerrando programa...\n");
                liberarListas(A, B, Intersecao, Uniao);
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
    l->inicio = NULL; 
    l->qtd = 0;       
    l->fim = NULL;       
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
    printf("\n1 - Inserir valor no fim da lista\n");
    printf("2 - Remover um valor da lista\n");
    printf("3 - Exibir valores\n");
    printf("4 - Interseção dos Valores)\n");
    printf("5 - União dos valores\n");
    printf("6 - Esvaziar uma lista\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

int isEmpty (Descritor* l){
    if(l->qtd==0){
        return TRUE; //1 = true
    } 
    else {
        return FALSE; //0 = false
    }
}

void inserirFinal (Descritor* l, int valor){
    NoLDE* novo = criarNo(valor);
    if (novo == NULL) {                               
        printf("Erro ao alocar memória!\n");           
        return;
    } 
    if (isEmpty(l)==TRUE){
        l->inicio = novo;
        l->fim = novo;
    } 
    else {
        novo->ant = l->fim;
        l->fim->prox = novo;
        l->fim = novo;
    }
    l->qtd++;
}

void exibirValores(Descritor* l){
    NoLDE* aux;
    if(isEmpty(l)==TRUE){
        printf("Lista Vazia!\n");
    }
    else{
        aux = l->inicio;
        printf("Lista: \n");
        while(aux!=NULL){
            printf("Valor: %d\n", aux->info);
            aux = aux->prox;
        }
    }
    printf("\n");
}

void removerValor(Descritor* l, int valor){
    if (isEmpty(l) == TRUE){ 
        printf("A Lista já está vazia.\n");
        return;
    }

    NoLDE* atual = l->inicio;
    int removidos = 0;

    while (atual != NULL) {
        NoLDE* proximo = atual->prox;

        if (atual->info == valor) {
            if (atual->ant != NULL) {
                atual->ant->prox = atual->prox;
            } else {
                l->inicio = atual->prox; 
            }

            if (atual->prox != NULL) {
                atual->prox->ant = atual->ant;
            } else {
                l->fim = atual->ant; 
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

NoLDE * buscar (Descritor* lista, int valor) { // busca sequencial melhorada
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

void inserir (Descritor* lista, int valor) { // inserção ordenada crescente
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

void intersecaoListas(Descritor* a,Descritor* b, Descritor* inter){
    NoLDE* aux_A = a->inicio;
    NoLDE* aux_B;
    while(aux_A != NULL){
        aux_B = b->inicio;
        if(buscar(b,aux_A->info) != NULL){
            inserir(inter, aux_A->info);
        }
        aux_A = aux_A->prox;
    }
}

void uniaoListas(Descritor* a,Descritor* b, Descritor* uniao){
    NoLDE* aux_A = a->inicio;
    NoLDE* aux_B = b->inicio;
    while(aux_A != NULL){
        inserir(uniao, aux_A->info);
        aux_A = aux_A->prox;
    }
    while(aux_B != NULL){
        inserir(uniao, aux_B->info);
        aux_B = aux_B->prox;
    }
}

void esvaziarLista(Descritor* l){
    if (isEmpty(l)==TRUE) {
        printf("Lista Vazia!\n");
        return; 
    }
    NoLDE* atual = l->inicio;
    NoLDE* proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    l->inicio = NULL;
    l->fim = NULL;
    l->qtd = 0;
}

void liberarListas(Descritor* a,Descritor* b, Descritor* inter, Descritor* uniao){
    if(a == NULL){
        return; 
    }
    if(b == NULL){
        return; 
    }
    if(inter == NULL){
        return; 
    }
    if(uniao == NULL){
        return; 
    } 
    esvaziarLista(a); 
    esvaziarLista(b);
    esvaziarLista(inter);
    esvaziarLista(uniao);
    free(a);
    free(b);
    free(inter);
    free(uniao);
}