// Atividade Extra – Lista Duplamente Encadeada Circular
// Aluna: Kailane Lisley de Araújo Silva
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct aluno {
    char nome[100];
    float media;
    int faltas;
} Aluno;

typedef struct noLDEC {
    struct noLDEC* ant;
    Aluno info;
    struct noLDEC* prox;
} NoLDEC;

typedef struct descritor {
    NoLDEC* inicio;
    NoLDEC* fim;
    int qtd;
} Descritor;

void exibirOpcoes();
Descritor* criarLista();
int isEmpty(Descritor* lista);
NoLDEC* consultar(Descritor* lista, char nome[]);
void cadastrar(Descritor* lista, Aluno aluno);

Descritor* criarLista() {
    Descritor* aux = (Descritor*) malloc(sizeof(Descritor));
    aux->inicio = NULL;
    aux->fim = NULL;
    aux->qtd = 0;
    return aux;
}

int isEmpty(Descritor* lista) {
    if (lista->qtd == 0) {
        return TRUE; 
    } else {
        return FALSE; 
    }
}

NoLDEC* consultar(Descritor* lista, char nome[]) {
    if (isEmpty(lista)==TRUE){
        return NULL;
    } 

    NoLDEC* aux = d->inicio;
    do {
        if (strcmp(aux->info.nome, nome) == 0) {
            return aux;
        }
        aux = aux->prox;
    } while (aux != d->inicio);

    return NULL;
}

void cadastrar(Descritor* lista, Aluno aluno) {
    if (consultar(lista, aluno.nome) != NULL) {
        printf("Aluno já cadastrado!\n");
        return;
    }

    NoLDEC* novo = (NoLDEC*) malloc(sizeof(NoLDEC));
    novo->info = aluno;

    if (isEmpty(lista)==TRUE) { 
        novo->prox = novo;
        novo->ant = novo;
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        // INSERIR ALUNO NA ORDEM ALFABÉTICA
        NoLDEC* aux = lista->inicio;                                    // Nó aux recebe nó do início da lista
        do {                                                            // Percorre a lista para encontrar a posição correta para a inserção  
            if (strcmp(aluno.nome, aux->info.nome) < 0){                // Verifica se o aluno já está cadastrado
                return;                                                 // Se já estiver, não insere
            }
            aux = aux->prox;                                            // aux recebe o próximo nó da lista
        } while (aux != lista->inicio);                                 // Enquanto não voltar ao início, repete
        
        if (aux == lista->inicio && strcmp(aluno.nome, aux->info.nome) < 0) {  //Inserção no início
            novo->prox = lista->inicio;
            novo->ant = lista->fim;
            lista->fim->prox = novo;
            lista->inicio->ant = novo;
            lista->inicio = novo;
        } else if (aux == lista->inicio) {                                     // Inserção no final
            novo->prox = lista->inicio;
            novo->ant = lista->fim;
            lista->fim->prox = novo;
            lista->inicio->ant = novo;
            lista->fim = novo;
        } else {                                                               // Inserção no meio
            novo->prox = aux;
            novo->ant = aux->ant;
            aux->ant->prox = novo;
            aux->ant = novo;
        }
    }

    lista->qtd++;
    printf("Aluno cadastrado com sucesso!\n");
}

// Listar todos os alunos
void listar(Descritor* d) {
    if (d->inicio == NULL) {
        printf("Cadastro vazio!\n");
        return;
    }

    NoLDEC* aux = d->inicio;
    do {
        printf("Nome: %s", aux->info.nome);
        printf("Média: %.2f\n", aux->info.media);
        printf("Faltas: %d\n\n", aux->info.faltas);
        aux = aux->prox;
    } while (aux != d->inicio);
}

// Alterar média
void alterarMedia(Descritor* d, char nome[]) {
    NoLDEC* aluno = consultar(d, nome);
    if (aluno == NULL) {
        printf("Aluno não encontrado!\n");
        return;
    }
    printf("Informe a nova média: ");
    scanf("%f", &aluno->info.media);
    fflush(stdin);
    printf("Média alterada com sucesso!\n");
}

// Alterar faltas
void alterarFaltas(Descritor* d, char nome[]) {
    NoLDEC* aluno = consultar(d, nome);
    if (aluno == NULL) {
        printf("Aluno não encontrado!\n");
        return;
    }
    int mudanca;
    printf("Informe a quantidade de faltas a ser acrescida (+) ou retirada (-): ");
    scanf("%d", &mudanca);
    fflush(stdin);
    aluno->info.faltas += mudanca;
    if (aluno->info.faltas < 0) aluno->info.faltas = 0;
    printf("Faltas alteradas com sucesso!\n");
}

// Exibir dados de um aluno
void exibirAluno(Descritor* d, char nome[]) {
    NoLDEC* aluno = consultar(d, nome);
    if (aluno == NULL) {
        printf("Aluno não encontrado!\n");
        return;
    }
    printf("Nome: %s", aluno->info.nome);
    printf("Média: %.2f\n", aluno->info.media);
    printf("Faltas: %d\n", aluno->info.faltas);
}

// Remover aluno
void remover(Descritor* d, char nome[]) {
    NoLDEC* aluno = consultar(d, nome);
    if (aluno == NULL) {
        printf("Aluno não encontrado!\n");
        return;
    }

    if (aluno == d->inicio && aluno == d->fim) { // Único elemento
        d->inicio = NULL;
        d->fim = NULL;
    } else {
        aluno->ant->prox = aluno->prox;
        aluno->prox->ant = aluno->ant;
        if (aluno == d->inicio) d->inicio = aluno->prox;
        if (aluno == d->fim) d->fim = aluno->ant;
    }
    free(aluno);
    d->qtd--;
    printf("Aluno removido com sucesso!\n");
}

// Limpar cadastro
void limpar(Descritor* d) {
    if (d->inicio == NULL) return;

    NoLDEC* aux = d->inicio;
    NoLDEC* temp;

    do {
        temp = aux;
        aux = aux->prox;
        free(temp);
    } while (aux != d->inicio);

    d->inicio = NULL;
    d->fim = NULL;
    d->qtd = 0;

    printf("Cadastro limpo com sucesso!\n");
}

void exibirOpcoes() {
    printf("\nOpções \n");
    printf("1 - Cadastrar aluno \n");
    printf("2 - Exibir todos os alunos da turma \n");
    printf("3 - Alterar média de um aluno \n");
    printf("4 - Alterar a quantidade de faltas de um aluno \n");
    printf("5 - Exibir os dados de um aluno \n");
    printf("6 - Remover um aluno da turma \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main() {
    Descritor* turma = criarDescritor();
    int op;
    Aluno al;
    char nome[100];

    do {
        exibirOpcoes();
        scanf("%d", &op);
        fflush(stdin);

        switch (op) {
            case 1:
                printf("Qual o nome do aluno? ");
                fgets(al.nome, 100, stdin);
                fflush(stdin);
                printf("Qual a média do aluno? ");
                scanf("%f", &al.media);
                fflush(stdin);
                printf("Qual a qtd. de faltas do aluno? ");
                scanf("%d", &al.faltas);
                fflush(stdin);
                cadastrar(turma, al);
                break;
            case 2:
                listar(turma);
                break;
            case 3:
                printf("Informe o nome do aluno: ");
                fgets(nome, 100, stdin);
                fflush(stdin);
                alterarMedia(turma, nome);
                break;
            case 4:
                printf("Informe o nome do aluno: ");
                fgets(nome, 100, stdin);
                fflush(stdin);
                alterarFaltas(turma, nome);
                break;
            case 5:
                printf("Informe o nome do aluno: ");
                fgets(nome, 100, stdin);
                fflush(stdin);
                exibirAluno(turma, nome);
                break;
            case 6:
                printf("Informe o nome do aluno: ");
                fgets(nome, 100, stdin);
                fflush(stdin);
                remover(turma, nome);
                break;
            case 0:
                limpar(turma);
                free(turma);
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opção inválida\n");
        }
    } while (op != 0);

    return 0;
}