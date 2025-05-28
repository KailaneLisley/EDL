#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noLSE {
    char ra[15];
    char nome[100];
    float media;
    int faltas;
    struct noLSE* prox;
} NoLSE;

typedef struct descritor{
    NoLSE* prim;
    NoLSE* ult;
    int qtd;
} Descritor;

void inicializarLista(Descritor* lista);
NoLSE* buscar(Descritor* lista, char ra[]);
void inserirTurma(Descritor* lista);
void exibirLista(Descritor* lista, char* titulo);
void inserirOrdenado(Descritor* lista, NoLSE* aluno);
void classificarAlunos(Descritor* turma, Descritor* aprovados, Descritor* reprovadosPorMedia, Descritor* reprovadosPorFalta);

int main() {
    Descritor turma, aprovados, reprovadosPorMedia, reprovadosPorFalta;
    inicializarLista(&turma);
    
    int opcao;
    do {
        printf("\n1 - Inserir aluno\n2 - Classificar alunos\n3 - Exibir todas as listas\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar(); // Consumir \n
        switch (opcao) {
            case 1:
                inserirTurma(&turma);
                break;
            case 2:
                classificarAlunos(&turma, &aprovados, &reprovadosPorMedia, &reprovadosPorFalta);
                printf("Alunos classificados!\n");
                break;
            case 3:
                exibirLista(&turma, "Lista Turma");
                exibirLista(&aprovados, "Lista Aprovados");
                exibirLista(&reprovadosPorMedia, "Lista Reprovados por Média");
                exibirLista(&reprovadosPorFalta, "Lista Reprovados por Falta");
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    
    return 0;
}
void inicializarLista(Descritor* lista) {
    lista->prim = NULL;
    lista->ult = NULL;
    lista->qtd = 0;
}

NoLSE* buscar(Descritor* lista, char ra[]) {
    NoLSE* aux = lista->prim;
    while (aux != NULL) {
        if (strcmp(aux->ra, ra) == 0) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void inserirTurma(Descritor* lista) {
    char ra[15];
    char nome[100];
    float media;
    int faltas;
    
    printf("Informe o RA do aluno: ");
    scanf("%s", ra);
    getchar(); 
    
    if (buscar(lista, ra) != NULL) {
        printf("Aluno com RA %s já cadastrado.\n", ra);
        return;
    }
    
    NoLSE* novo = (NoLSE*)malloc(sizeof(NoLSE));
    strcpy(novo->ra, ra);
    
    printf("Informe o nome do aluno: ");
    fgets(novo->nome, 100, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = 0; 
    
    printf("Informe a média do aluno: ");
    scanf("%f", &novo->media);
    printf("Informe as faltas do aluno: ");
    scanf("%d", &novo->faltas);
    novo->prox = NULL;
    
    if (lista->qtd == 0) {
        lista->prim = novo;
        lista->ult = novo;
    } else {
        lista->ult->prox = novo;
        lista->ult = novo;
    }
    lista->qtd++;
}

void exibirLista(Descritor* lista, char* titulo) {
    printf("\n%s:\n", titulo);
    NoLSE* aux = lista->prim;
    while (aux != NULL) {
        printf("RA: %s, Nome: %s, Média: %.2f, Faltas: %d\n", aux->ra, aux->nome, aux->media, aux->faltas);
        aux = aux->prox;
    }
    if (lista->qtd == 0) {
        printf("Lista vazia.\n");
    }
}

void inserirOrdenado(Descritor* lista, NoLSE* aluno) {
    NoLSE* novo = (NoLSE*)malloc(sizeof(NoLSE));
    *novo = *aluno;
    novo->prox = NULL;
    
    if (lista->qtd == 0 || strcmp(novo->nome, lista->prim->nome) < 0) {
        novo->prox = lista->prim;
        lista->prim = novo;
        if (lista->qtd == 0) lista->ult = novo;
    } else {
        NoLSE* aux = lista->prim;
        while (aux->prox != NULL && strcmp(aux->prox->nome, novo->nome) < 0) {
            aux = aux->prox;
        }
        novo->prox = aux->prox;
        aux->prox = novo;
        if (novo->prox == NULL) lista->ult = novo;
    }
    lista->qtd++;
}

void classificarAlunos(Descritor* turma, Descritor* aprovados, Descritor* reprovadosPorMedia, Descritor* reprovadosPorFalta) {
    inicializarLista(aprovados);
    inicializarLista(reprovadosPorMedia);
    inicializarLista(reprovadosPorFalta);
    
    NoLSE* aux = turma->prim;
    while (aux != NULL) {
        if (aux->media >= 7.0 && aux->faltas <= 18) {
            inserirOrdenado(aprovados, aux);
        } else if (aux->faltas > 18) {
            inserirOrdenado(reprovadosPorFalta, aux);
        } else {
            inserirOrdenado(reprovadosPorMedia, aux);
        }
        aux = aux->prox;
    }
}