#include <stdio.h>
#include <string.h>

typedef struct produto {
	char codigo[12];
	char descricao[50];
	float preco;
	int qtdEstoque;
	int status;  // 1 - ativo ou 0 - removido
} Produto;

typedef struct noLDE {
	char codigo[12];
	int posicao;
	struct noLDE* prox;
	struct noLDE* ant;
} NoLDE;

FILE* prepararArquivo(char nome[]);{

}
void fecharArquivo(FILE* arq);{
    fclose(arq);
}
void gravarRegistro(FILE* arq, Produto p){
    int status;
    fseek(arq, 0, SEEK_END);
    status = fwrite(&p, sizeof(Produto), 1, arq);
    if (status == 1){
        printf ("Registro gravado\n");
    }
    else {
        printf ("Erro de gravação\n");
    }
}
void exibirOpcoes(){
    printf("Opcoes \n");
	printf("1 - Cadastrar um novo produto \n");
	printf("0 - Encerrar programa \n");
	printf("Informe a opcao: ");
}

int main() {
	char nomeArq[] = "produtos.dat";
	int op;
	FILE* cadastro; 
	cadastro = prepararArquivo(nomeArq);
	if (cadastro == NULL)
		printf("Erro na abertura do arquivo. Programa encerrado \n");
	else {
		do {
			exibirOpcoes();
			scanf("%d",&op); fflush(stdin);
			switch (op) {
			case 1: 
                printf("Informe o codigo do produto");
                fgets(prod.codigo, 12, stdin); fflush(stdin);
                printf("Informe a descrição do produto");
                fgets(prod.descriao, 50, stdin); fflush(stdin);
                printf("Informe o preço do produto");
                scanf("%f", &prod.preco); fflush(stdin);
                printf("Informe oa qtd");
                scanf("%d", &prod.qtdEstoque); fflush(stdin);
                prod.status = 1;
                gravarRegistro(cadastro, prod)
		        break;
			case 0: liberarArquivo(cadastro);
			        break;
			default: printf("Opcao invalida \n");
			}
		} while (op != 0);
	}
	return 0;
}

