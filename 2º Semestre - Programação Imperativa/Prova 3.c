#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char nome[60];
	char email[100];
	char telefone[13];
} pessoa;

pessoa cadastrarPessoa();
char mostrarMenu();
int buscarContatoPorNome(char nome[], pessoa *contatos, int quantidade);
void imprimirContato(pessoa p);
void ordenarContatos(pessoa *contatos, int quantidade);
void listarContatos(pessoa *contatos, int quantidade);
void informarDados(int quantidade, int total);
void procurarPorContato(pessoa *contatos, int qtdContatos);

void salvarArquivo(char nomeArquivo[], pessoa *contatos, int qtdContatos) {
	FILE *arquivo = fopen(nomeArquivo, "w");
	int i;
	for(i = 0; i < qtdContatos; i++) {
		fprintf(arquivo, "%s;%s;%s\n", 
			contatos[i].nome, 
			contatos[i].email, 
			contatos[i].telefone);
	}
	fclose(arquivo);
}

void carregarArquivo(char nomeArquivo[], pessoa *contatos, int qtdLinhas) {
	FILE *arquivo = fopen(nomeArquivo, "r+");
	int i;
	pessoa contato;
	char linha[200];
	for(i = 0; i < qtdLinhas; i++) {
		fscanf(arquivo, " %[^\n]s", linha);
		
		strcpy(contato.nome, strtok(linha, ";"));
		strcpy(contato.email, strtok(NULL, ";"));
		strcpy(contato.telefone, strtok(NULL, ";"));
		
		contatos[i] = contato;
	}
	fclose(arquivo);
}

int contarLinhas(char nomeArquivo[]) {
	FILE *arquivo = fopen(nomeArquivo, "r+");
	int linhas = 0;
	while(!feof(arquivo)) {
		char c = fgetc(arquivo);
		if(c == '\n') {
			linhas++;
		}
	}	
	fclose(arquivo);
	return linhas;
}

int main() {
	char nomeArquivo[] = "contatos.txt";
	
	int qtdLinhas = contarLinhas(nomeArquivo);
		
	pessoa *contatos;
	int tamanhoAgenda = (qtdLinhas < 2) ? 2 : qtdLinhas;
	int qtdContatos = qtdLinhas;
	contatos = malloc(tamanhoAgenda * sizeof(pessoa));
	
	carregarArquivo(nomeArquivo, contatos, qtdLinhas);
	
	char opcao;
	do {
		opcao = mostrarMenu();
		switch(opcao) {
			case 'C': case 'c':
				if(qtdContatos == tamanhoAgenda-1) {
					tamanhoAgenda *= 2;
					contatos = realloc(contatos, tamanhoAgenda * sizeof(pessoa)); 
				}
				contatos[qtdContatos] = cadastrarPessoa();
				qtdContatos++;
			break;
			case 'B': case 'b':
				procurarPorContato(contatos, qtdContatos);
			break;
			case 'L': case 'l':
				listarContatos(contatos, qtdContatos);
			break;
			case 'I': case 'i':
				informarDados(qtdContatos, tamanhoAgenda);
			break;
			case 'S': case 's':
				salvarArquivo(nomeArquivo, contatos, qtdContatos);
				printf("Muito obrigado por utilizar a agenda. Tenha um bom dia!\n");
			break;
			default:
				printf("A opção informada é inválida");
			break;
		}
	} while(opcao != 'S');
	
	return 0;
}

pessoa cadastrarPessoa() {
	pessoa p;
	
	printf("Informe o nome da pessoa: ");
	scanf(" %[^\n]s", p.nome);
	printf("Informe o e-mail da pessoa: ");
	scanf(" %[^\n]s", p.email);
	printf("Informe o telefone da pessoa: ");
	scanf(" %[^\n]s", p.telefone);

	return p;
}

char mostrarMenu() {
	printf("Digite um comando para prosseguir:\n");
	printf("C – Cadastrar uma pessoa na agenda.\n");
	printf("B – Buscar uma pessoa cadastrada na agenda.\n");
	printf("L – Listar todos os contatos cadastrados.\n");
	printf("I – Informações Gerenciais.\n");
	printf("S – Sair.\n");
	char opcao;
	scanf(" %c", &opcao);
	return opcao;
}

int buscarContatoPorNome(char nome[], pessoa *contatos, int quantidade) {
	int i;
	for(i = 0; i < quantidade; i++) {
		if(strcmp(contatos[i].nome, nome) == 0) {
			return i;
		}
	}
	return -1;
}

void imprimirContato(pessoa p) {
	printf("Nome: %s\n", p.nome);
	printf("E-mail: %s\n", p.email);
	printf("Telefone: %s\n", p.telefone);
}

void ordenarContatos(pessoa *contatos, int quantidade) {
	int i, j;
	for(i = 0; i < quantidade; i++) {
		int min = i;
		for(j = i+1; j < quantidade; j++) {
			if(strcmp(contatos[min].nome, contatos[j].nome) > 0) {
				min = j;
			}
		}
		if(i != min) {
			pessoa temp = contatos[i];
			contatos[i] = contatos[min];
			contatos[min] = temp;
		}
	}
}

void listarContatos(pessoa *contatos, int quantidade) {
	ordenarContatos(contatos, quantidade);
	int i;
	for(i = 0; i < quantidade; i++) {
		printf("------- Contato %i --------\n", i+1);
		imprimirContato(contatos[i]);
		printf("---------------------------\n");
	}	
}

void informarDados(int quantidade, int total) {
	printf("\n----------------------------------------\n");
	printf("Quantidade de contatos cadastrados: %d\n", quantidade);
	printf("Posições disponíveis na agenda: %d\n", total-quantidade);
	printf("----------------------------------------\n");
}

void procurarPorContato(pessoa *contatos, int qtdContatos) {
	char nome[60];
	printf("Informe um nome para buscar: ");
	scanf(" %[^\n]s", nome);
	int posicao = buscarContatoPorNome(nome, contatos, qtdContatos);
	if(posicao == -1) {
		printf("O nome informado não foi encontrado.");
	} else {
		printf("\n----------------------------------------\n");
		imprimirContato(contatos[posicao]);
		printf("----------------------------------------\n");
	}
}
