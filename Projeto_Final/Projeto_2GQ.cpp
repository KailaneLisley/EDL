#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define S_ATIVO 1 	  //Status Ativo
#define S_REMOVIDO 0  //Status removido
#define N 37
/* Foi decidido que o tamanho da tabela de Hashing será 37, pois esse foi o menor número possível encontrado que,
além de atender todos os crtérios de escolha do tamanho da tabela, reduz colisões e garante uma boa distribuição dos dados */

typedef struct produto {  	// Estrutura de um produto
	char chave[12];
	char descricao[50];
	float preco;
	int qtdEstoque;
	int status; 
} Produto;

typedef struct noLDE {		// Estrutura para uma representação do produto na tabela hashing
	char chave[12];
	int posicao;
	struct noLDE* prox;
	struct noLDE* ant;
} NoLDE;

// PROTÓTIPOS DAS FUNÇÕES E PROCEDIMENTOS
void exibirOpcoes();
NoLDE* criarNo(char chave[], int pos);
FILE* prepararArquivo(char nome[]);
void liberarArquivo(FILE* arq);
unsigned int funcaoHashing(char chave[]);
int buscar(NoLDE* tabelaHashing[], char chave[]);
void criarIndice(FILE* arq, NoLDE* tabelaHashing[]);
void desalocarIndice(NoLDE* tabelaHashing[]);
void inserirTabelaHash(NoLDE* tabelaHashing[], char chave[], int pos);
void cadastrar(FILE* arq, NoLDE* tabelaHashing[]);
void consultar(FILE* arq, NoLDE* tabelaHashing[]);
void alterar(FILE* arq, NoLDE* tabelaHashing[]);
void remover(FILE* arq, NoLDE* tabelaHashing[]);
void exibirCadastro(FILE* arq, NoLDE* tabelaHashing[]);

int main() {
	char nomeArq[] = "produtos.dat";
	int op;
	FILE* cadastro;
	NoLDE* tabelaHashing[N];  
	cadastro = prepararArquivo(nomeArq);
	if (cadastro == NULL)
		printf("Erro na abertura do arquivo. Programa encerrado \n");
	else {
		criarIndice(cadastro, tabelaHashing);
		do {
			exibirOpcoes();
			scanf("%d",&op); fflush(stdin);
			switch (op) {
			case 1:
				cadastrar(cadastro, tabelaHashing);
		        break;
			case 2:
				consultar(cadastro, tabelaHashing);
			    break;
			case 3:
				alterar(cadastro, tabelaHashing);
			    break;
			case 4: 
				remover(cadastro, tabelaHashing);
			    break;
			case 5: 
				exibirCadastro(cadastro);
			    break;
			case 0: 
				liberarArquivo(cadastro);
			    desalocarIndice(tabelaHashing);
			    break;
			default: printf("Opcao invalida \n");
			}
		} while (op != 0);
	}
	return 0;
}

void exibirOpcoes() {
	printf("\n= = = = = O P C O E S = = = = =\n");
	printf("1 - Cadastrar um novo produto \n");
	printf("2 - Consultar produto \n");
	printf("3 - Alterar dados do produto \n");
	printf("4 - Remover produto \n");
	printf("5 - Exibir produtos cadastrados \n");
	printf("0 - Encerrar programa \n");
	printf("Informe a opcao: ");
}

// FUNÇÃO PARA CRIAR NOVA REPRESENTAÇÃO DE UM PRODUTO (NÓ)
NoLDE* criarNo(char chave[], int pos){
	NoLDE* aux = (NoLDE*)malloc(sizeof(NoLDE)); // Cria novo nó
	if (aux == NULL) {
        return NULL;
    }
    strcpy(aux->chave, chave);  // Copia o código da chave para o novo nó
    aux->posicao = pos;          // Armazena a posição no arquivo
    aux->prox = NULL;
    aux->ant = NULL;
	return aux;
}

// FUNÇÃO PARA PREPARAR O ARQUIVO PARA LEITURA E GRAVAÇÃO
FILE* prepararArquivo(char nome[]) {
	FILE* arq = fopen(nome, "r+b"); 	// Abrir arquivo para leitura e gravação
	if(arq==NULL){						// Se não for possível abrir o arquivo
		arq = fopen(nome, "w+b");			// Cria arquivo para leitura e gravação
	} 								
	return arq;							// Retorna o endereco do arquivo aberto ou criado.
}										// Retorna NULL se nao conseguir abrir nem criar o arquivo.

// PROCEDIMENTO PARA FECHAR E LIBERAR O ARQUIVO
void liberarArquivo(FILE* arq) {
    FILE* arq_aux = fopen("aux.dat", "w+b");   				// Criar arquivo auxiliar vazio
    if (arq_aux == NULL) {									// Se não for possível criar arquivo 
        printf("Erro ao criar arquivo auxiliar.\n");			// Retorna mensagem de erro
        return;
    }
    rewind(arq);  											// Volta para o início do arquivo original
	Produto produto;										// Cria uma estrutura para um produto
    while (fread(&produto, sizeof(Produto), 1, arq) == 1) {	// Enquanto a função conseguir ler apenas 1 produto por vez...
        if (produto.status == S_ATIVO) {						// Verifica se o produto está ativo (Status == 1)
            fwrite(&produto, sizeof(Produto), 1, arq_aux);		// Lê o registro e armazena as informações em 'produto'
        }
    }														// Ao terminar de ler todos os produtos cadastrados:
    fclose(arq);												// Fecha arquivo original
    fclose(arq_aux);											// Fecha arquivo auxiliar

    if (remove("produtos.dat") != 0) {						// Remove o arquivo original
        printf("Erro ao remover o arquivo original.\n");		// Se não conseguir remover, imprime uma mensagem de erro
        return;
    }
    if (rename("aux.dat", "produtos.dat") != 0) {			// Renomeia o arquivo auxiliar com o nome do arquivo original
        printf("Erro ao renomear o arquivo.\n");				// Se não conseguir renomear, imprime uma mensagem de erro
        return;
    }

    printf("Arquivo atualizado e liberado com sucesso.\n");
}

// FUNÇÃO DE HASHING - MÉTODO DA PERMUTAÇÃO PARA CHAVES ALFANUMERICAS
unsigned int funcaoHashing(const char chave[]) {
    unsigned int hash = 0;
    int tam = strlen(chave); 						// Calcula o tamanho da string usando strlen (termina no '\0')
    for (int i = 0; i < tam; i++) {					// Percorre todos os caracteres da string
        hash += (unsigned int)chave[i] * (i + 1);		// Multiplica o valor do caractere pelo seu índice + 1 
    }
    return hash % N;								// Retorna o índice onde a chave será inserida na tabela de hashing
}

// FUNÇÃO PARA LOCALIZAR UM NÓ  NA TABELA DE HASHING
NoLDE* localizarNo(NoLDE* tabela, char chave[], NoLDE** anterior) {
    *anterior = NULL;
    NoLDE* atual = tabela;
	while (atual != NULL && strcmp(chave, atual->chave) > 0){
		*anterior = atual;
        atual = atual->prox;
    }
    return atual;  // Pode ser NULL (fim) ou o nó que contém a chave ou maior que ela
}

// FUNÇÃO PARA PROCURAR UM CÓDIGO NA TABELA HASHING
int buscar(NoLDE* tabelaHashing[], char chave[]) {
    int indice = funcaoHashing(chave);
	NoLDE* anterior = NULL;
    NoLDE* atual = localizarNo(tabelaHashing[indice], chave, &anterior);
    if (atual == NULL){
		return -1;  // Não encontrou
	}
	else if(strcmp(chave, atual->chave) == 0) {
        return atual->posicao;  // Encontrou a chave
	}
	return -1;
}

// PROCEDIMENTO PARA INSERIR UM PRODUTO NA TABELA DE HASHING GARANTINDO A ORDENAÇÃO
void inserirTabelaHash(NoLDE* tabelaHashing[], char chave[], int pos) {
    int indice = funcaoHashing(chave);										// Aplicar a funcao de hashing na chave 
    NoLDE* anterior = NULL;													// Nó 'anterior inicializa com NULL'
    NoLDE* atual = localizarNo(tabelaHashing[indice], chave, &anterior);	// Nó 'atual' recebe: NULL se não encontrar a chave ou a possição da chave existente
	if (atual != NULL && strcmp(chave, atual->chave) == 0) {				// Se a chave já estiver cadastrada...
        printf("Aviso: chave '%s' já está presente na tabela.\n", chave);   	// Aborta a inserção e retorna mensagem informando a existencia da chave na tabela
        return;																	// Sai do procedimento
    }
	NoLDE* novo = criarNo(chave, pos);       								// Cria o novo nó com a chave e a posição
    if (novo == NULL) {														// Se der falha na alocação, aborta a inserção
        return; 														        // Sai do procedimento
    }																		// Aloca novo nó entre o 'anterior' e o 'atual'
    novo->prox = atual;														// Liga 'novo' ao 'atual'
    novo->ant = anterior;                                                   // Liga 'novo' ao 'anterior' 

    if (anterior == NULL) {                                                 // Se a inserção ocorreu no inicio...
        tabelaHashing[indice] = novo;                                           // Liga a tabela ao novo nó
    } else {                                                                // Se a inserção ocorreu no meio ou no final da LDE...
        anterior->prox = novo;                                                  // Liga o nó anterior ao nó novo
    }
    if (atual != NULL) {                                                    // Se a não inserção ocorreu no final...
        atual->ant = novo;                                                      // Liga o nó atual ao nó novo
	}
}

// PROCEDIMENTO PARA CRIAR UM ÍNDICE PARA CADA ITEM ATIVO DO ARQUIVO
void criarIndice(FILE* arq, NoLDE* tabelaHashing[]) {                  
    for (int i = 0; i < N; i++) {                                     
        tabelaHashing[i] = NULL;                                    // Inicializa toda a Tabela de Hash com NULL
    }
    Produto produto;                                                // Variável para armazenar temporariamente os dados de um produto lido do arquivo 
    int pos = 0;                                                    // Variável para armazenar a posição do produto no arquivo
    rewind(arq);                                                    // Posiciona o cursor no início do arquivo

    while (fread(&produto, sizeof(Produto), 1, arq) == 1) {         // Enquanto a função conseguir ler apenas 1 produto por vez... 
        if (produto.status == S_ATIVO) {                                // Verifica se o produto lido está com o status ativo
            inserirTabelaHash(tabelaHashing, produto.chave, pos);       // Se o produto está ativo, insere o produto na tabela de hashing
        }
        pos++;                                                          // Incrementa a posição do produto no arquivo
    }
}

// PROCEDIMENTO PARA DESLOCAR OS QUE COMPOEM AS LISTAS DA TABELA DE HASHING, DEIXANDO TODAS AS LISTAS VAZIAS
void desalocarIndice(NoLDE* tabelaHashing[]) {
    for (int i = 0; i < N; i++) {				// Começando do índice 0 até o último índice da tabela, faça...
        NoLDE* atual = tabelaHashing[i];			// Cria um ponteiro para receber o primeiro nó no índice i
        while(atual != NULL) {						// Enquanto não terminar de percorrer todos os nós da LDE...
            NoLDE* aux = atual;							// Cria um ponteiro auxiliar para receber o nó atual
            atual = atual->prox;						// O nó atual recebe o próximo nó
            free(aux);									// O nó apontado pelo ponteiro auxiliar é desalocado
        }											// Quando desalocar todos os nós da LDE do índice i...
        tabelaHashing[i] = NULL;					// O índece i da tabela de Hashing recebe NULL (Vazio)
    }											// Ao terminar o processo, todas as listas estão vazias
}												// Todos os índices foram desalocados, ou seja, a tabela está vazia

// PROCEDIMENTO PARA REMOVER UM PRODUTO DA TABELA DE HASHING
void removerTabelaHash(NoLDE* tabelaHashing[], char chave[], int posTabela) {
    int indice = funcaoHashing(chave);                                      // Aplicar a funcao de hashing na chave 
    NoLDE* anterior = NULL;                                                 // Nó 'anterior inicializa com NULL'
    NoLDE* atual = localizarNo(tabelaHashing[indice], chave, &anterior);    // Nó 'atual' recebe: NULL se não encontrar a chave ou a possição da chave existente 

    if (atual != NULL && strcmp(chave, atual->chave) == 0) {                // Verifica se algum nó foi encontrado e se este nó é o que estamos procurando 
        if (anterior != NULL) {                                                 // Se o nó encontrado não for o primeiro nó...             
            anterior->prox = atual->prox;                                           // Liga o nó anterior ao próximo nó em relação ao atual        
        } else {                                                                // Senão (caso seja o primeiro nó...)
            tabelaHashing[indice] = atual->prox;                                    // A entrada da tabela para o indice específico recebe o próximo nó em relaçao ao nó atual
        }

        if (atual->prox != NULL) {                                              // Se o nó atual não for o último...
            atual->prox->ant = anterior;                                            // Liga o próximo nó ao nó anterior em relação ao atual
        }
        free(atual);                                                            // Remove nó atual
    } else {
        printf("Produto com chave %s não encontrado na tabela.\n", chave);
    }
}

// PROCEDIMENTO PARA CADASTRAR UM PRODUTO NOVO NO ARQUIVO
void cadastrar(FILE* arq, NoLDE* tabelaHashing[]) {
    Produto produto;                                                // Variável para armazenar temporariamente os dados de um produto lido do arquivo 
    printf("Informe a chave do produto: ");                         // Solicita o codigo do produto a ser cadastrado
    fgets(produto.chave, sizeof(produto.chave), stdin);
    produto.chave[strcspn(produto.chave, "\n")] = '\0';

    if (buscar(tabelaHashing, produto.chave) != -1) {               // Verifica se o produto já existe na tabela 
        printf("Produto já cadastrado.\n");                             // Se existir, não realiza o cadastro
        return;
    }
    printf("Informe a descricao: ");                                // Solicita descrição do produto
    fgets(produto.descricao, sizeof(produto.descricao), stdin);
    produto.descricao[strcspn(produto.descricao, "\n")] = '\0';

    printf("Informe o preco: ");                                    // Solicitar preço do produto
    scanf("%f", &produto.preco);
    printf("Informe a quantidade em estoque: ");                    // Solicitar a quantidade em estoque do produto
    scanf("%d", &produto.qtdEstoque);
    getchar(); // consumir o \n

    produto.status = S_ATIVO;                                       // Define o status do novo produto como ativo

    fseek(arq, 0, SEEK_END);                                        // Move o cursos para o final do arquivo
    fwrite(&produto, sizeof(Produto), 1, arq);                      // Cadastra produto no inal do arquivo

    fseek(arq, 0, SEEK_SET);                                        // Move o cursor para o comeo do arquivo 
    Produto p;                                                      // Variável para armazenar temporáriamente os dados de um produto lido do arquivo
    int pos = 0;                                                    // Variável para armazenar a prosição do produto cadastrado no arquivo
    while (fread(&p, sizeof(Produto), 1, arq) == 1) {               // Percorre todo o arquivo 
        pos++;                                                      // Icrementa a posição até chegar a última posição do arquivo
    }

    inserirTabelaHash(tabelaHashing, produto.chave, pos);           // Insere novo produto cadastrado na tabela de hash
    printf("Produto cadastrado com sucesso!\n");
}

// PROCEDIMENTO PARA CONSULTAR UM PRODUTO
void consultar(FILE* arq, NoLDE* tabelaHashing[]) {
    char chave[12];
    printf("Informe a chave do produto: ");                             // Solicita o codigo do produto a ser cadastrado
    fgets(chave, sizeof(chave), stdin);
    chave[strcspn(chave, "\n")] = '\0';

    int pos = buscar(tabelaHashing, chave);                             // Procura produto na tabela de hash
    if (pos == -1) {                                                    // Se a buscar retornar -1...
        printf("Produto não encontrado.\n");                                // O produto não foi encontrado
        return;                                                             // Sai do procedimento'1
    }
    Produto produto;
    fseek(arq, pos * sizeof(Produto), SEEK_SET);
    fread(&produto, sizeof(Produto), 1, arq);

    if (produto.status == S_ATIVO) {
        printf("Chave: %s\nDescricao: %s\nPreco: %.2f\nEstoque: %d\n",
            produto.chave, produto.descricao, produto.preco, produto.qtdEstoque);
    } else {
        printf("Produto removido.\n");
    }
}
/* Consultar o registro do produto no arquivo
    * 1 - Solicita o codigo do produto a ser consultado.
    * 2 - Procura pelo codigo na tabela de hashing.
    * 3 - Caso nao encontre, informa que o produto nao esta no cadastro.
    * 4 - Caso encontre, vai ao arquivo, na posicao indicada, 
	*     le o registro do produto e exibe seus dados.*/

// PROCEDIMENTO PARA ALTERAR UM PRODUTO
void alterar(FILE* arq, NoLDE* tabelaHashing[]) {
    char chave[12];
    printf("Informe a chave do produto a alterar: ");
    fgets(chave, sizeof(chave), stdin);
    chave[strcspn(chave, "\n")] = '\0';

    int pos = buscar(tabelaHashing, chave);

    if (pos == -1) {
        printf("Produto não encontrado.\n");
        return;
    }

    Produto produto;
    fseek(arq, pos * sizeof(Produto), SEEK_SET);
    fread(&produto, sizeof(Produto), 1, arq);

    printf("Informe a nova descricao: ");
    fgets(produto.descricao, sizeof(produto.descricao), stdin);
    produto.descricao[strcspn(produto.descricao, "\n")] = '\0';

    printf("Informe o novo preco: ");
    scanf("%f", &produto.preco);
    printf("Informe a nova quantidade em estoque: ");
    scanf("%d", &produto.qtdEstoque);
    getchar(); // consumir o \n

    fseek(arq, pos * sizeof(Produto), SEEK_SET);
    fwrite(&produto, sizeof(Produto), 1, arq);

    printf("Produto alterado com sucesso!\n");
}
/* Alterar o registro do carro no arquivo.
	 * 1 - Solicita o codigo do produto a ser alterado.
	 * 2 - Procura pelo codigo na tabela de hashing.
	 * 3 - Caso nao encontre, informa que o produto nao esta no cadastro.
	 * 4 - Caso encontre, vai ao arquivo, na posicao indicada, le o registro do produto e 
     *     exibe seus dados.
	 * 5 - Pergunta ao usuario quais dados deseja alterar. Efetiva a alteracao dos dados no arquivo. */

// PROCEDIMENTO PARA ALTERAR STATUS DO PRODUTO E REMOVE-LO DA TABELA DE HASHING
void remover(FILE* arq, NoLDE* tabelaHashing[]) {
    char chave[12];
    printf("Informe a chave do produto a remover: ");
    fgets(chave, sizeof(chave), stdin);
    chave[strcspn(chave, "\n")] = '\0';

    int pos = buscar(tabelaHashing, chave);

    if (pos == -1) {
        printf("Produto não encontrado.\n");
        return;
    }

    Produto produto;
    fseek(arq, pos * sizeof(Produto), SEEK_SET);
    fread(&produto, sizeof(Produto), 1, arq);

    produto.status = S_REMOVIDO;

    fseek(arq, pos * sizeof(Produto), SEEK_SET);
    fwrite(&produto, sizeof(Produto), 1, arq);

    removerTabelaHash(tabelaHashing, chave, pos);

    printf("Produto removido com sucesso!\n");
}
/* Remover o registro do produto do arquivo
	 * 1 - Solicita o codigo do produto a ser removido.
	 * 2 - Procura pelo codigo na tabela de hashing.
	 * 3 - Caso nao encontre, informa que o produto nao esta no cadastro.
	 * 4 - Caso encontre, vai ao arquivo, na posicao indicada, le o registro do produto e exibe seus dados.
	 * 5 - Pergunta ao usuario se deseja realmente remover e efetiva a remocao.
	 *     A remocao consiste em alterar, no arquivo, o STATUS do registro do produto para 0 (removido).
	 * 5 - Remove o no que contem a chave da tabela de hashing. 
	 *     Utilize para isso o procedimento "removerTabelaHash". */

// PROCEDIMENTO PARA EXIBIR TODOS OS PRODUTOS ATIVOS 
void exibirCadastro(FILE* arq, NoLDE* tabelaHashing[]) {
    Produto produto;
    int pos = 0;
    rewind(arq);
    printf("\n= = = PRODUTOS CADASTRADOS = = =\n");
    while (fread(&produto, sizeof(Produto), 1, arq) == 1) {
        if (produto.status == S_ATIVO) {
            printf("Posição: %d\n", pos);
            printf("Chave: %s\nDescricao: %s\nPreco: %.2f\nEstoque: %d\n\n",
                produto.chave, produto.descricao, produto.preco, produto.qtdEstoque);
        }
        pos++;
    }
	/* Exibe todos os registros de produtos ATIVOS constantes no arquivo. */
    if (buscar(tabelaHashing, produto.chave) != -1) {
        printf("Produto já cadastrado.\n");
        return;
    }

    printf("Informe a descricao: ");
    fgets(produto.descricao, sizeof(produto.descricao), stdin);
    produto.descricao[strcspn(produto.descricao, "\n")] = '\0';

    printf("Informe o preco: ");
    scanf("%f", &produto.preco);
    printf("Informe a quantidade em estoque: ");
    scanf("%d", &produto.qtdEstoque);
    getchar(); // consumir o \n

    produto.status = S_ATIVO;

    fseek(arq, 0, SEEK_END);
    int pos = ftell(arq) / sizeof(Produto);
    fwrite(&produto, sizeof(Produto), 1, arq);

    inserirTabelaHash(tabelaHashing, produto.chave, pos);

    printf("Produto cadastrado com sucesso!\n");
}

/* Cadastrar o registro do produtp no arquivo e inserir a chave (codigo do produto) na tabela de hashing.
	* 1 - Solicita o codigo do produto a ser cadastrado.
	* 2 - Procura pelo codigo na tabela de hashing.
	* 3 - Caso encontre, informa que o produto ja esta no cadastro.
	* 4 - Caso nao encontre, solicita os demais dados do produto, o insere no final do arquivo.
	* 5 - Insere a chave, juntamente com sua posicao no arquivo, na tabela de hashing.
	*     Utilize para isso o procedimento "inserirTabelaHash". */

// PROCEDIMENTO PARA CONSULTAR UM PRODUTO
void consultar(FILE* arq, NoLDE* tabelaHashing[]) {
    char chave[12];
    printf("Informe a chave do produto: ");
    fgets(chave, sizeof(chave), stdin);
    chave[strcspn(chave, "\n")] = '\0';

    int pos = buscar(tabelaHashing, chave);

    if (pos == -1) {
        printf("Produto não encontrado.\n");
        return;
    }

    Produto produto;
    fseek(arq, pos * sizeof(Produto), SEEK_SET);
    fread(&produto, sizeof(Produto), 1, arq);

    if (produto.status == S_ATIVO) {
        printf("Chave: %s\nDescricao: %s\nPreco: %.2f\nEstoque: %d\n",
            produto.chave, produto.descricao, produto.preco, produto.qtdEstoque);
    } else {
        printf("Produto removido.\n");
    }
}
/* Consultar o registro do produto no arquivo
    * 1 - Solicita o codigo do produto a ser consultado.
    * 2 - Procura pelo codigo na tabela de hashing.
    * 3 - Caso nao encontre, informa que o produto nao esta no cadastro.
    * 4 - Caso encontre, vai ao arquivo, na posicao indicada, 
	*     le o registro do produto e exibe seus dados.*/

// PROCEDIMENTO PARA ALTERAR UM PRODUTO
void alterar(FILE* arq, NoLDE* tabelaHashing[]) {
    char chave[12];
    printf("Informe a chave do produto a alterar: ");
    fgets(chave, sizeof(chave), stdin);
    chave[strcspn(chave, "\n")] = '\0';

    int pos = buscar(tabelaHashing, chave);

    if (pos == -1) {
        printf("Produto não encontrado.\n");
        return;
    }

    Produto produto;
    fseek(arq, pos * sizeof(Produto), SEEK_SET);
    fread(&produto, sizeof(Produto), 1, arq);

    printf("Informe a nova descricao: ");
    fgets(produto.descricao, sizeof(produto.descricao), stdin);
    produto.descricao[strcspn(produto.descricao, "\n")] = '\0';

    printf("Informe o novo preco: ");
    scanf("%f", &produto.preco);
    printf("Informe a nova quantidade em estoque: ");
    scanf("%d", &produto.qtdEstoque);
    getchar(); // consumir o \n

    fseek(arq, pos * sizeof(Produto), SEEK_SET);
    fwrite(&produto, sizeof(Produto), 1, arq);

    printf("Produto alterado com sucesso!\n");
}
/* Alterar o registro do carro no arquivo.
	 * 1 - Solicita o codigo do produto a ser alterado.
	 * 2 - Procura pelo codigo na tabela de hashing.
	 * 3 - Caso nao encontre, informa que o produto nao esta no cadastro.
	 * 4 - Caso encontre, vai ao arquivo, na posicao indicada, le o registro do produto e 
     *     exibe seus dados.
	 * 5 - Pergunta ao usuario quais dados deseja alterar. Efetiva a alteracao dos dados no arquivo. */

// PROCEDIMENTO PARA ALTERAR STATUS DO PRODUTO E REMOVE-LO DA TABELA DE HASHING
void remover(FILE* arq, NoLDE* tabelaHashing[]) {
    char chave[12];
    printf("Informe a chave do produto a remover: ");
    fgets(chave, sizeof(chave), stdin);
    chave[strcspn(chave, "\n")] = '\0';

    int pos = buscar(tabelaHashing, chave);

    if (pos == -1) {
        printf("Produto não encontrado.\n");
        return;
    }

    Produto produto;
    fseek(arq, pos * sizeof(Produto), SEEK_SET);
    fread(&produto, sizeof(Produto), 1, arq);

    produto.status = S_REMOVIDO;

    fseek(arq, pos * sizeof(Produto), SEEK_SET);
    fwrite(&produto, sizeof(Produto), 1, arq);

    removerTabelaHash(tabelaHashing, chave, pos);

    printf("Produto removido com sucesso!\n");
}
/* Remover o registro do produto do arquivo
	 * 1 - Solicita o codigo do produto a ser removido.
	 * 2 - Procura pelo codigo na tabela de hashing.
	 * 3 - Caso nao encontre, informa que o produto nao esta no cadastro.
	 * 4 - Caso encontre, vai ao arquivo, na posicao indicada, le o registro do produto e exibe seus dados.
	 * 5 - Pergunta ao usuario se deseja realmente remover e efetiva a remocao.
	 *     A remocao consiste em alterar, no arquivo, o STATUS do registro do produto para 0 (removido).
	 * 5 - Remove o no que contem a chave da tabela de hashing. 
	 *     Utilize para isso o procedimento "removerTabelaHash". */

// PROCEDIMENTO PARA EXIBIR TODOS OS PRODUTOS ATIVOS 
void exibirCadastro(FILE* arq) {
    Produto produto;
    int pos = 0;
    rewind(arq);
    printf("\n= = = PRODUTOS CADASTRADOS = = =\n");
    while (fread(&produto, sizeof(Produto), 1, arq) == 1) {
        if (produto.status == S_ATIVO) {
            printf("Posição: %d\n", pos);
            printf("Chave: %s\nDescricao: %s\nPreco: %.2f\nEstoque: %d\n\n",
                produto.chave, produto.descricao, produto.preco, produto.qtdEstoque);
        }
        pos++;
    }
}
	/* Exibe todos os registros de produtos ATIVOS constantes no arquivo. */
