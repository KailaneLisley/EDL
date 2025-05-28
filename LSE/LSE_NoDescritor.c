#include <stdio.h>                                      //Inclusão da biblioteca padrão de entrada e saída
#include <stdlib.h>                                     //Inclusão da biblioteca para uso de funções como malloc() e free()

typedef struct noLSE {                                  //Definindo a estrutura de NoLSE
    int info;                                               //Campo que armazena o valor (informação)
    struct noLSE* prox;                                     //Ponteiro para o próximo nó da lista
} NoLSE;

typedef struct descritor{                               //Definindo a estrutura do Descritor
    NoLSE* prim;                                            //Ponteiro para o primeiro elemento da lista
    NoLSE* ult;                                             //Ponteiro para o último elemento da lista
    int qtd;                                                //Quantidade de elementos na lista
} Descritor;

                                                    //P R O T Ó T I P O   D A S   F U N Ç Õ E S   E   P R O C E D I M E N T O S
Descritor* criarLista ();                               //Função para inicializar Lista (Construtor)
NoLSE* criarNo (int valor);                             //Função para criar novo Nó
void InserirInicio (Descritor* d, int valor);           //Procedimento para Inserir Valor no INÍCIO da Lista
void InserirFinal (Descritor* d, int valor);            //Procedimento para Inserir Valor no FIM da Lista
void exibirValores (Descritor* lista);                  //Procedimento para Exibir valores da Lista
void removerInicio (Descritor* lista);                  //Procedimento para Remover Primeiro Elemento da Lista
void removerFinal (Descritor* lista);                   //Procedimento para Remover Último Elemento da Lista
void desalocarLista (Descritor** lista);                //Procedimento para Desalocar Lista 

int main(){                                         //Função principal
    Descritor* minhaLista = criarLista();               //Cria e inicializa uma nova lista vazia

    InserirInicio(minhaLista, 10);                      //Insere valor 10 no início da lista
    InserirFinal(minhaLista, 20);                       //Insere valor 20 no final da lista
    InserirInicio(minhaLista, 5);                       //Insere valor 5 no início da lista

    printf("\nLista atual:\n");                         
    exibirValores(minhaLista);                          //Exibe os valores da lista

    printf("\nRemovendo o primeiro elemento...\n");
    removerInicio(minhaLista);                          //Remove o primeiro elemento da lista

    printf("\nRemovendo o último elemento...\n");
    removerFim(minhaLista);                             //Remove o último elemento da lista

    printf("\nLista após remoções:\n");
    exibirValores(minhaLista);                          //Exibe os valores da lista após remoções

    printf("\nDesalocando a lista...\n");
    desalocarLista(&minhaLista);                        //Desaloca toda a memória utilizada pela lista

    return 0;                                           //Fim do programa
}

Descritor* criarLista (){                           //Inicializando Lista (Construtor)
    Descritor* aux;                                     //Declarando ponteiro para Descritor
    aux = (Descritor*)malloc(sizeof(Descritor));        //Alocando memória para Descritor
    if (aux == NULL) {                                  //Verifica se a alocação foi feita com sucesso
        printf("Erro ao alocar memória!\n");            //Se aux(ponteiro do descritor) for NULL, printa erro e retorna
        return NULL;
    }    
    aux->prim = NULL;                                   //Inicializa ponteiro para o primeiro elemento como NULL
    aux->ult = NULL;                                    //Inicializa ponteiro para o último elemento como NULL
    aux->qtd = 0;                                       //Inicializa a quantidade de elementos como 0
    return aux;                                         //Retornando aux(ponteiro do descritor)
}

NoLSE* criarNo(int valor){                          //Criar um novo Nó (valor como parâmetro)
    NoLSE* aux;                                         //Declarando ponteiro para NoLSE
    aux = (NoLSE*)malloc(sizeof(NoLSE));                //Alocando Memória para o Nó
    if (aux == NULL) {                                  //Verifica se a alocação foi feita com sucesso
        printf("Erro ao alocar memória!\n");            //Se aux(ponteiro do nó) for NULL, printa erro e retorna
        return NULL;
    } 
    aux->info = valor;                                  //Preenchendo o campo 'info' com o valor
    aux->prox = NULL;                                   //Preenchendo o campo 'prox' com valor nulo
    return aux;                                         //Retornando aux(ponteiro do Nó)
}

void InserirInicio (Descritor* d, int valor){       // I N S E R I R   V A L O R   N O   I N I C I O   D A   L I S T A
    NoLSE* novo;                                        //Declarar Ponteiro para o Nó
    novo = criarNo(valor);                              //Criar/Alocar o Nó (Usando função de criar nó)
    if (d->qtd == 0){                                   //Verifica se a lista está vazia
        d->prim = novo;                                 //Campo 'prim' do descritor aponta para novo nó
        d->ult = novo;                                  //Campo 'ult' do descritor aponta para novo nó
    } else {                                            //Caso a lista NÃO esteja vazia
        novo->prox = d->prim;                           //Novo nó aponta para o primeiro nó atual
        d->prim = novo;                                 //Novo nó se torna o primeiro da lista
    }
    d->qtd++;                                           //Incrementa quantidade de elementos
    printf("Inserção Efetuada!\n");                     //Exibe mensagem de aceitação
}

void InserirFinal (Descritor* d, int valor){        // I N S E R I R   V A L O R   N O   F I M   D A   L I S T A
    NoLSE* novo;                                        //Declarar Ponteiro para o Nó
    novo = criarNo(valor);                              //Criar/Alocar o Nó (Usando função de criar nó)
    if (d->qtd == 0){                                   //Verifica se a lista está vazia
        d->prim = novo;
        d->ult = novo;
    } else {                                            //Caso a lista NÃO esteja vazia
        d->ult->prox = novo;                            //Último elemento atual aponta para o novo nó
        d->ult = novo;                                  //Atualiza o ponteiro 'ult' para o novo nó
    }
    d->qtd++;                                           //Incrementa quantidade de elementos
    printf("Inserção Efetuada!\n");                     //Exibe mensagem de aceitação
}

void exibirValores (Descritor* lista){              // E X I B I R   V A L O R E S   D A   L I S T A
    NoLSE* aux;                                         //Declarar Ponteiro aux para descritor
    if (lista->qtd == 0){                               //Verifica se a lista está vazia
        printf("Lista Vazia!\n");
    } else {
        aux = lista->prim;                              //Ponteiro 'aux' recebe o primeiro nó
        while (aux != NULL){                            //Percorre a lista até o fim
            printf("%d\n", aux->info);                  //Imprime valor do nó
            aux = aux->prox;                            //Avança para o próximo nó
        }
    }
}

void removerInicio(Descritor* lista) {              // R E M O V E R   P R I M E I R O   E L E M E N T O   D A   L I S T A
    if (lista->qtd == 0) {                              //Se a lista estiver vazia, nada a remover
        printf("Lista vazia. Nada a remover.\n");
        return;
    }

    NoLSE* aux = lista->prim;                           //Salva o ponteiro do primeiro nó
    lista->prim = aux->prox;                            //Atualiza o ponteiro 'prim' para o próximo nó
    free(aux);                                          //Libera a memória do nó removido
    lista->qtd--;                                       //Decrementa a quantidade de elementos

    if (lista->qtd == 0) {                              //Se a lista ficou vazia após remoção
        lista->ult = NULL;                              //Atualiza o ponteiro do último também
    }
    printf("Remoção do início realizada com sucesso.\n");
}

void removerFim(Descritor* lista) {                 // R E M O V E R   Ú L T I M O   E L E M E N T O   D A   L I S T A
    if (lista->qtd == 0) {                              //Se a lista estiver vazia, nada a remover
        printf("Lista vazia. Nada a remover.\n");
        return;
    }

    NoLSE* aux;

    if (lista->qtd == 1) {                              //Caso só exista um elemento na lista
        aux = lista->ult;                               //Salva ponteiro para o único nó
        lista->prim = NULL;                             //Atualiza 'prim' para NULL
        lista->ult = NULL;                              //Atualiza 'ult' para NULL
        free(aux);                                      //Libera memória do nó
    } else {
        aux = lista->prim;                              //Começa pelo primeiro elemento
        while (aux->prox != lista->ult) {               //Percorre até o penúltimo nó
            aux = aux->prox;
        }
        free(lista->ult);                               //Libera memória do último nó
        lista->ult = aux;                               //Atualiza 'ult' para o penúltimo nó
        lista->ult->prox = NULL;                        //Garante que seja o último (prox = NULL)
    }

    lista->qtd--;                                       //Decrementa quantidade de elementos
    printf("Remoção do fim realizada com sucesso.\n");
}

void desalocarLista(Descritor** lista) {            // D E S A L O C A R   T O D A   A   L I S T A
    while ((*lista)->qtd > 0) {                         //Enquanto houver elementos na lista
        removerInicio(*lista);                          //Remove o primeiro elemento
    }
    free(*lista);                                       //Libera a memória do descritor
    *lista = NULL;                                      //Define o ponteiro para NULL (evita uso indevido)
    printf("Lista desalocada com sucesso.\n");
}