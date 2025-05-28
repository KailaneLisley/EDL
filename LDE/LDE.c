//LDE com nó descritor e com valores repetidos 

#include <stdio.h>           
#include <stdlib.h> 

#define TRUE 1
#define FALSE 0

typedef struct noLDE { 
    struct noLSE* ant;    
    int info;              
    struct noLSE* prox;   
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
void exibirCecrescente (Descritor* l);
void exibirDecrescente (Descritor* l);
void removerInicio (Descritor* l);
void removerFinal (Descritor* l);
void removerValor(Descritor* lista, int valor);

int main(){
    Descritor* lista;
    lista = criarLista();
    int op, valor, num;
    do {
        exibirOpcao();
        scanf("%d", &op);
        
        switch(op){
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
                printf("VALORES DE FORMA CRESCENTE\n");
                exibirCrescente(lista);
                break;
            case 4:
                printf("VALORES DE FORMA DECRESCENTE\n");
                exibirDecrescente(lista);
                break;
            case 5:
                removerInicio(lista);
                break;
            case 6:
                removerFinal(lista);
                break;
            case 7:
                printf("Valor para ser removido: \n");
                scanf("%d", &num);
                removerValor(lista, num);
                break;
            case 0:
                printf("Encerrando programa...\n");
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
    printf("\n1 - Inserir no início\n");
    printf("2 - Inserir no final\n");
    printf("3 - Exibir lista (Crescente)\n");
    printf("4 - Exibir lista (Decrescente)\n");
    printf("5 - Remover início\n");
    printf("6 - Remover final\n");
    printf("7 - Remover um valor específico\n");
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
    if (isEmpty(l) == TRUE){ //Está vazia
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
    
}

void exibirCecrescente (Descritor* l){

}
void exibirDecrescente (Descritor* l){

}

void removerInicio (Descritor* l){

}

void removerFinal (Descritor* l){
    NoLDE* aux;
    //Caso 1: Lista Vazia
    if (isEmpty(l) == TRUE){ //Está vazia
        printf("A Lista já está vazia");
        return;
    }
    //Caso 2: Lista com apenas 1 nó
    else if (l->qtd == 1){
        free(l->prim); //Desalocar nó (seja pelo primeiro ou ultimo campo do nó descritor)
        l->prim = NULL;
        l->ult = NULL;
        l->qtd = 0;
    }
    //Caso 3: Lista com mais de 1 nó
    else {
        aux = l->ult->ant; //penultivo
        l->ult = aux;
        free(aux->prox);//Desalocar último nó 
        aux->prox = NULL;
        l->qtd--;
    }
}

void removerValor(Descritor* lista, int valor){
//Caso 1: Lista Vazia
//Caso 2: Lista apenas um nó
//Caso 3: Lista com mais de um nó
    //Caso 3.1: Remover no começo
    //Caso 3.2: Remover no final
    //Caso 3.3: Remover no meio
}