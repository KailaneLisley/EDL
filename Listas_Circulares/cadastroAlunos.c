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
void listar(Descritor* lista);
void alterarMedia(Descritor* lista, char nome[]);
void alterarFaltas(Descritor* lista, char nome[]);
void remover(Descritor* lista, char nome[]);
void limpar(Descritor* lista);

int main() {
    Descritor* turma = criarLista();
    int op;
    Aluno aluno;
    char nome[100];

    do {
        exibirOpcoes();
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1: // Cadastrar Aluno
                printf("Qual o nome do aluno? ");
                fgets(aluno.nome, 100, stdin);
                aluno.nome[strcspn(aluno.nome, "\n")] = 0;
                printf("Qual a média do aluno? ");
                scanf("%f", &aluno.media);
                printf("Qual a qtd. de faltas do aluno? ");
                scanf("%d", &aluno.faltas);
                cadastrar(turma, aluno);
                getchar();
                break;
            case 2: // Exibir todos os alunos da turma
                printf("\n==== ALUNOS CADASTRADOS ====\n");
                listar(turma);
                break;
            case 3: // Alterar média de um aluno
                printf("\nInforme o nome do aluno: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = 0;
                alterarMedia(turma, nome);
                break;
            case 4: // Alterar a quantidade de faltas de um aluno
                printf("\nInforme o nome do aluno: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = 0;
                alterarFaltas(turma, nome);
                break;
            case 5: // Exibir os dados de um aluno
                printf("\nInforme o nome do aluno: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = 0;
                exibirAluno(turma, nome);
                break;
            case 6: // Remover um aluno da turma
                printf("\nInforme o nome do aluno: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = 0;
                remover(turma, nome);
                break;
            case 0: // Encerrar programa
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

void exibirOpcoes() {
    printf("\n ==== S E C R E T A R I A ====\n");
    printf("1 | Cadastrar aluno \n");
    printf("2 | Exibir todos os alunos da turma \n");
    printf("3 | Alterar média de um aluno \n");
    printf("4 | Alterar a quantidade de faltas de um aluno \n");
    printf("5 | Exibir os dados de um aluno \n");
    printf("6 | Remover um aluno da turma \n");
    printf("0 | Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

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

NoLDEC* consultar(Descritor* lista, char nome[]) {      // Função para consultar se um aluno já está cadastrado na lista
    if (isEmpty(lista)){                                    // Se a lista estiver vazia... 
        return NULL;                                            // Retorna NULL
    } 
    NoLDEC* aux = lista->inicio;                            // Cria um ponteiro 'aux' para receber o 1º nó da lista
    do {                                                    // Loop para comparar o nome dos alunos cadastrados com o aluno atual
        if (strcmp(aux->info.nome, nome) == 0) {                // Se o nome do aluno atual for igual ao aluno cadastrado...
            return aux;                                             // Retorna 'aux' que aponta para o aluno encontrado no cadastro
        }
        aux = aux->prox;                                        // Se não encontrou, o 'aux' aponta para o próximo nó
    } while (aux != lista->inicio);                         // Enquanto não voltar ao início, repete
    return NULL;                                            // Se não encontrou o nome do aluno no cadastro, retorna NULL
}

void cadastrar(Descritor* lista, Aluno aluno) {         // Procedimento para cadastrar um novo aluno na lista
    if (consultar(lista, aluno.nome) != NULL) {             // Consulta se o aluno já está cadastrado
        printf("Aluno já cadastrado!\n");                       // Se estiver cadastrado, retorna mensagem informando ao usuário
        return;                                                 // Sai do procedimento
    }                                                       // Se não estiver cadastrado...

    NoLDEC* novo = (NoLDEC*) malloc(sizeof(NoLDEC));        // Cria e aloca memória para um novo nó
    novo->info = aluno;                                     // O campo de informação do novo nó recebe a estrutura 'aluno'

    if (isEmpty(lista)) {                                   // Se a lista estiver vazia...
        novo->prox = novo;                                      // O campo 'prox' do nó recebe o próprio nó (Aplica circularidade)
        novo->ant = novo;                                       // O campo 'ant' do nó recebe o próprio nó (Aplica circularidade)
        lista->inicio = novo;                                   // O campo 'inicio' da lista recebe o novo nó 
        lista->fim = novo;                                      // O campo 'inicio' da lista recebe o novo nó 
    } else {                                                // Se não estiver vazia faz a inserção ordenada do aluno na lista...
                                                            
        NoLDEC* aux = lista->inicio;                            // Cria um ponteiro 'aux' para receber nó do início da lista
        do {                                                    // Loop para percorrer a lista e encontrar a posição correta para a inserção  
            if (strcmp(aluno.nome, aux->info.nome) < 0){            // Verifica se o nome do aluno é alfabeticamente menor que o cadastrado
                break;                                                  // Se na posição atual o aluno pode ser inserido, quebra o loop e continua
            }
            aux = aux->prox;                                            // aux recebe o próximo nó da lista
        } while (aux != lista->inicio);                                 // Enquanto não voltar ao início, repete
        
          // INSERÇÃO NO INÍCIO
        if (aux == lista->inicio && strcmp(aluno.nome, aux->info.nome) < 0) {  // Se 'aux' for igual ao 1º nó da lista e o nome do aluno é alfabeticamente menor que o cadastrado
            novo->prox = lista->inicio;                                             
            novo->ant = lista->fim;
            lista->fim->prox = novo;
            lista->inicio->ant = novo;
            lista->inicio = novo;
        } // INSERÇÃO NO FINAL
        else if (aux == lista->inicio) {                                        // Senão se 'aux' for igual ao 1º nó da lista (Percorreu toda a lista circular)                       
            novo->prox = lista->inicio;
            novo->ant = lista->fim;
            lista->fim->prox = novo;
            lista->inicio->ant = novo;
            lista->fim = novo;
        } // INSERÇÃO NO MEIO                                                   // Senão (Caso não seja inserção no início nem no fim)
        else {                                                               
            novo->prox = aux;
            novo->ant = aux->ant;
            aux->ant->prox = novo;
            aux->ant = novo;
        }
    }
    lista->qtd++;                                                               // Quando inserir, icrementa +1 no campo 'qtd' da lista
    printf("%s cadastrado(a) com sucesso!\n", aluno.nome);                      // Retorna mensagem informando que a inserção ocorreu com sucesso
}

void listar(Descritor* lista) {                         // Procedimento para listar todos os alunos cadastrados na lista   
    int contador = 1;        
    if (isEmpty(lista)) {                                   // Se a lista estiver vazia
        return;                                                 // Retorna NULL
    }
    NoLDEC* aux = lista->inicio;                            // Cria um ponteiro 'aux' para receber o 1º nó da lista
    do {                                                    // Loop para exibir informações dos alunos
        printf("\n---- ALUNO %d ----\n", contador++);           // Informar qual a posição na lista do aluno está sendo exibido
        printf("Nome: %s\n", aux->info.nome);                     // Exibir nome do aluno
        printf("Média: %.2f\n", aux->info.media);               // Exibir média do aluno
        printf("Faltas: %d\n\n", aux->info.faltas);             // Exibir quantidade de faltas do aluno
        aux = aux->prox;                                        // O 'aux' passa a apontar par ao próximo aluno da lista
    } while (aux != lista->inicio);                         // Enquanto não voltar ao início, repete 
}

void alterarMedia(Descritor* lista, char nome[]) {      //Procedimento para alterar média de um aluno
    NoLDEC* aluno = consultar(lista, nome);                 // Cria um ponteiro 'aluno' para receber o nó correspondente ao aluno consultado
    if (aluno == NULL) {                                    // Se o aluno não for encontrado...
        printf("\nAluno não encontrado!\n");                      // Retorna mensagem informando ao usuário que o aluno não foi encontrado nos registros 
        return;                                                   // Sai do procedimento 
    }
    printf("\nInforme a nova média: ");                       // Pede ao usuário 
    scanf("%f", &aluno->info.media);
    fflush(stdin);
    printf("\nMédia alterada com sucesso!\n");
}

void alterarFaltas(Descritor* lista, char nome[]) {
    NoLDEC* aluno = consultar(lista, nome);
    if (aluno == NULL) {
        printf("Aluno não encontrado!\n");
        return;
    }
    int mudanca;
    printf("Informe a quantidade de faltas a ser acrescida (+) ou retirada (-): ");
    scanf("%d", &mudanca);
    fflush(stdin);
    aluno->info.faltas += mudanca;
    if (aluno->info.faltas < 0){
        aluno->info.faltas = 0;
    }
    printf("Faltas alteradas com sucesso!\n");
}

void exibirAluno(Descritor* lista, char nome[]) {
    NoLDEC* aluno = consultar(lista, nome);
    if (aluno == NULL) {
        printf("Aluno não encontrado!\n");
        return;
    }
    printf("\n--- DADOS DO ALUNO ---\n");
    printf("Nome: %s\n", aluno->info.nome);
    printf("Média: %.2f\n", aluno->info.media);
    printf("Faltas: %d\n", aluno->info.faltas);
}

void remover(Descritor* lista, char nome[]) {
    NoLDEC* aluno = consultar(lista, nome);
    if (aluno == NULL) {
        printf("Aluno não encontrado!\n");
        return;
    }

    if (aluno == lista->inicio && aluno == lista->fim) { // Único elemento
        lista->inicio = NULL;
        lista->fim = NULL;
    } else {
        aluno->ant->prox = aluno->prox;
        aluno->prox->ant = aluno->ant;
        if (aluno == lista->inicio) lista->inicio = aluno->prox;
        if (aluno == lista->fim) lista->fim = aluno->ant;
    }
    free(aluno);
    lista->qtd--;
    printf("Aluno removido com sucesso!\n");
}

void limpar(Descritor* lista) {
    if (lista->inicio == NULL) return;

    NoLDEC* aux = lista->inicio;
    NoLDEC* temp;

    do {
        temp = aux;
        aux = aux->prox;
        free(temp);
    } while (aux != lista->inicio);

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;

    printf("Cadastro limpo com sucesso!\n");
}
