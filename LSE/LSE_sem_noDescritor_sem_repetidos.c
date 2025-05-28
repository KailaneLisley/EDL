#include <stdio.h>           //Inclusão da biblioteca padrão de entrada e saída
#include <stdlib.h>          //Inclusão da biblioteca para uso de funções como malloc() e free()

typedef struct noLSE {       //Definindo a estrutura de NoLSE
    int info;                //Campo que armazena o valor (informação)
    struct noLSE* prox;      //Ponteiro para o próximo nó da lista
} NoLSE;

// P R O T Ó T I P O S   D A S   F U N Ç Õ E S
NoLSE* criarNo(int valor);                              //Função para criar novo Nó
int existeValor(NoLSE* inicio, int valor);              //Verifica se valor já existe na lista
void InserirInicio(NoLSE** inicio, int valor);          //Inserir Valor no INÍCIO da Lista
void InserirFinal(NoLSE** inicio, int valor);           //Inserir Valor no FIM da Lista
void exibirValores(NoLSE* inicio);                      //Exibir valores da Lista
void removerInicio(NoLSE** inicio);                     //Remover Primeiro Elemento da Lista
void removerFim(NoLSE** inicio);                        //Remover Último Elemento da Lista
void desalocarLista(NoLSE** inicio);                    //Desalocar Lista

int main() {
    NoLSE* minhaLista = NULL;                           //Inicializa lista vazia

    InserirInicio(&minhaLista, 10);                     //Insere valor 10 no início da lista
    InserirFinal(&minhaLista, 20);                      //Insere valor 20 no final da lista
    InserirInicio(&minhaLista, 5);                      //Insere valor 5 no início da lista

    printf("\nLista atual:\n");
    exibirValores(minhaLista);                          //Exibe os valores da lista

    printf("\nRemovendo o primeiro elemento...\n");
    removerInicio(&minhaLista);                         //Remove o primeiro elemento da lista

    printf("\nRemovendo o último elemento...\n");
    removerFim(&minhaLista);                            //Remove o último elemento da lista

    printf("\nLista após remoções:\n");
    exibirValores(minhaLista);                          //Exibe os valores da lista após remoções

    printf("\nDesalocando a lista...\n");
    desalocarLista(&minhaLista);                        //Desaloca toda a memória utilizada pela lista

    return 0;
}

NoLSE* criarNo(int valor) {                             //Cria um novo Nó com o valor informado
    NoLSE* aux = (NoLSE*) malloc(sizeof(NoLSE));         //Aloca memória para o novo nó
    if (aux == NULL) {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }
    aux->info = valor;                                  //Preenche o campo 'info' com o valor
    aux->prox = NULL;                                   //Inicializa o ponteiro para o próximo nó como NULL
    return aux;
}

int existeValor(NoLSE* inicio, int valor) {             //Verifica se o valor já está presente na lista
    NoLSE* aux = inicio;
    while (aux != NULL) {
        if (aux->info == valor)
            return 1;                                   //Valor já existe
        aux = aux->prox;
    }
    return 0;                                           //Valor não encontrado
}

void InserirInicio(NoLSE** inicio, int valor) {
    if (existeValor(*inicio, valor)) {
        printf("Valor %d já está na lista. Inserção ignorada.\n", valor);
        return;
    }

    NoLSE* novo = criarNo(valor);
    if (novo == NULL) return;

    novo->prox = *inicio;                               //Novo nó aponta para o antigo início
    *inicio = novo;                                     //Atualiza o início da lista
    printf("Inserção Efetuada!\n");
}

void InserirFinal(NoLSE** inicio, int valor) {
    if (existeValor(*inicio, valor)) {
        printf("Valor %d já está na lista. Inserção ignorada.\n", valor);
        return;
    }

    NoLSE* novo = criarNo(valor);
    if (novo == NULL) return;

    if (*inicio == NULL) {
        *inicio = novo;                                 //Lista estava vazia
    } else {
        NoLSE* aux = *inicio;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    printf("Inserção Efetuada!\n");
}

void exibirValores(NoLSE* inicio) {
    if (inicio == NULL) {
        printf("Lista Vazia!\n");
        return;
    }

    NoLSE* aux = inicio;
    while (aux != NULL) {
        printf("%d\n", aux->info);
        aux = aux->prox;
    }
}

void removerInicio(NoLSE** inicio) {
    if (*inicio == NULL) {
        printf("Lista vazia. Nada a remover.\n");
        return;
    }

    NoLSE* aux = *inicio;
    *inicio = aux->prox;
    free(aux);
    printf("Remoção do início realizada com sucesso.\n");
}

void removerFim(NoLSE** inicio) {
    if (*inicio == NULL) {
        printf("Lista vazia. Nada a remover.\n");
        return;
    }

    if ((*inicio)->prox == NULL) {                      //Apenas um elemento
        free(*inicio);
        *inicio = NULL;
    } else {
        NoLSE* aux = *inicio;
        while (aux->prox->prox != NULL) {
            aux = aux->prox;
        }
        free(aux->prox);
        aux->prox = NULL;
    }
    printf("Remoção do fim realizada com sucesso.\n");
}

void desalocarLista(NoLSE** inicio) {
    NoLSE* aux;
    while (*inicio != NULL) {
        aux = *inicio;
        *inicio = (*inicio)->prox;
        free(aux);
    }
    printf("Memória desalocada com sucesso.\n");
}