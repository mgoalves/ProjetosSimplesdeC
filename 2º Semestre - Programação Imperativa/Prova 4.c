#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

//Definindo a estrutura.
typedef struct Equipamento{
	
	long Cod;
	char Nome[20];
	char Tipo[20];
	char Local[20];
	int Ano;
	char Marca[20];
	char Modelo[20];
	
}Equipamento;

//Variaveis Globais
int TamVet = 0;
int i = 0;
int k = 0;

//Prototipação das funções
void ExibeMenu();
void Menu (Equipamento *X);
void Carregar(Equipamento *X);
void Sair (Equipamento *X);
void Buscar(Equipamento *X);
void Lista(Equipamento *X);
void Ordena (Equipamento *X);
void Cadastrar (Equipamento *X);
int  ContaLinhas (char NomeArq[]);
void Excluir (Equipamento *X);

void ExibeMenu(){
	
	system ("cls");
	
	printf ("\n\n\t\tDigite um comando para prosseguir:");
	printf ("\n\t\tA – Carregar um arquivo de dados.");
	printf ("\n\t\tC – Cadastrar um equipamento.");
	printf ("\n\t\tL – Listagem ordenada de equipamentos de um local.");
	printf ("\n\t\tB – Buscar um equipamento pelo código do patrimônio.");
	printf ("\n\t\tE – Excluir um equipamento cadastrado");
	printf ("\n\t\tS – Salvar dados e Sair.");
	
}

void Menu(Equipamento *X){

		
	char OP;

	do{
		ExibeMenu();
		scanf (" %c", &OP);
		fflush(stdin);
	
	if (OP == 'A'){
		Carregar(X);
		
	} else if (OP == 'C'){
		Cadastrar(X);
		
	} else if (OP == 'L'){
		Lista (X);
		
	} else if (OP == 'B'){
		Buscar(X);
		
	}else if (OP == 'E'){
		Excluir (X);
	
	}else if (OP == 'S'){
		Sair (X);
		
	}
	
	} while (OP != 'S');
		
}

void Carregar(Equipamento *X){
	
	system ("cls");
	char NomeArq[30];
	
	printf ("\n\n\t\tInforme o nome do arquivo para o carregamento: ");
	gets(NomeArq);
	fflush (stdin);
	
	int L = ContaLinhas(NomeArq);
	
	
	
	FILE *Arquivo;
	Arquivo = fopen(NomeArq, "r+");
	
	Equipamento Aux;
	char Linha[300];
	
	for (i = 0; i < L; i++){
		
		TamVet++;
		X = realloc (X, TamVet * sizeof(X));
		
		fscanf (Arquivo, "%s", Linha);
		
		Aux.Cod = atoi (strtok(Linha, ";"));
		strcpy(Aux.Nome, strtok(NULL, ";"));
		strcpy(Aux.Tipo, strtok(NULL, ";"));
		strcpy(Aux.Local, strtok(NULL, ";"));
		Aux.Ano = atoi (strtok(NULL, ";"));
		strcpy(Aux.Marca, strtok(NULL, ";"));
		strcpy(Aux.Modelo, strtok(NULL, ";"));
		
		X[TamVet] = Aux;
	}
	fclose (Arquivo);
	
}

void Sair (Equipamento *X){
	
	char NomeArq[30];
	system ("cls");
	printf ("\n\n\t\tPor favor insira o nome do arquivo para salvar: ");
	gets(NomeArq);	
	fflush(stdin);
	
	FILE *Arquivo;
	Arquivo = fopen (NomeArq, "w+");
	
	for (i = 0; i < TamVet; i++){
		
		fprintf (Arquivo, "%l;%s;%s;%s;%d;%s;%s\n", X[i].Cod, X[i].Nome, X[i].Tipo, X[i].Local, X[i].Ano, X[i].Marca, X[i].Modelo);
		
	}
	
	fclose (Arquivo);
	printf ("\n\n\t\tO Arquivo foi criado com sucesso.");
}

void Buscar(Equipamento *X){
	
	Ordena(X);
	
	long CodT;
	system ("cls");
	printf ("\n\n\t\tPor favor insira o codigo para busca: ");
	scanf (" %l", CodT);
	
	for (i = 0; i < TamVet; i++){
		
		if (CodT == X[i].Cod){
			printf ("\n\n\t\tCod: %l", X[i].Cod);
			printf ("\n\t\tNome: %s", X[i].Nome);
			printf ("\n\t\tTipo: %s", X[i].Tipo);
			printf ("\n\t\tLocal: %s", X[i].Local);
			printf ("\n\t\tAno: %d", X[i].Ano);
			printf ("\n\t\tMarca: %s", X[i].Marca);
			printf ("\n\t\tModelo: %s", X[i].Modelo);
		}
	}
	
	getch();
	
}

void Lista(Equipamento *X){
	
	Ordena(X);
	
	char LT[30];
	system ("cls");
	printf ("\n\n\t\tInforme o local para listagem: ");
	gets(LT);
	fflush(stdin);
	
	for (i = 0; i < TamVet; i++){
		
		if (strcmp(LT, X[i].Local) == 0){
			
			printf ("\n\n\t\tCod: %l", X[i].Cod);
			printf ("\n\t\tNome: %s", X[i].Nome);
			printf ("\n\t\tTipo: %s", X[i].Tipo);
			printf ("\n\t\tLocal: %s", X[i].Local);
			printf ("\n\t\tAno: %d", X[i].Ano);
			printf ("\n\t\tMarca: %s", X[i].Marca);
			printf ("\n\t\tModelo: %s", X[i].Modelo);
			
		}
	}
	
	printf ("\n\n\t\tTodos os equipamentos encotrados neste local.");
	getch();
}


void Ordena (Equipamento *X){
	
	Equipamento Aux;
	
	for (i = 0; i < TamVet; i++){
		
		for (k = i + 1; k < TamVet; k++){
			
			if (strcmp(X[i].Nome, X[k].Nome) < 0){
				
				Aux = X[k];
				X[k] = X[i];
				X[i] = Aux;
				
			}
		}	
	}
}

void Cadastrar (Equipamento *X){
	
	system ("cls");
	
	TamVet++;
	X = realloc (X,   TamVet * sizeof (X));	
	
	printf ("\n\n\t\tInsira o codigo: ");
	scanf (" %l", X[TamVet].Cod);
	fflush (stdin);
	
	printf ("\n\t\tInsira o nome: ");
	gets(X[TamVet].Nome);
	fflush(stdin);
	
	printf ("\n\t\tInsira o tipo: ");
	gets(X[TamVet].Tipo);
	fflush(stdin);
	
	printf ("\n\t\tInsira o Local: ");
	gets(X[TamVet].Local);
	fflush(stdin);
	
	printf ("\n\n\t\tInsira o ano: ");
	scanf (" %d", X[TamVet].Ano);
	fflush (stdin);
	
	printf ("\n\t\tInsira o marca: ");
	gets(X[TamVet].Marca);
	fflush(stdin);
	
	printf ("\n\t\tInsira o modelo: ");
	gets(X[TamVet].Modelo);
	fflush(stdin);
	
	printf ("\n\n\t\tEquipamento cadastrado com sucesso.");
	getch();
	
}

int  ContaLinhas (char NomeArq[]){
	
	int Linhas;
	char C;
	
	FILE *Arquivo;
	Arquivo = fopen(NomeArq, "r+");
	
	while (!feof(Arquivo)){
		
		C = fgetc(Arquivo);
		if (C == '\n'){
			Linhas++;
		}
	}
	
	fclose (Arquivo);
	return Linhas;	
}

void Excluir (Equipamento *X){
	
	
	int Cod;
	
	system ("cls");
	printf ("\n\n\t\tInsira o codigo para a exclusão: ");
	scanf ("%d", &Cod);
	
	
	printf ("\n\n\t\tEquipamento excluido com sucesso.");
	getch();
	
}

int main (){
	
	setlocale (LC_ALL, "ptb");
	
	Equipamento *X = malloc (sizeof (Equipamento));
		
	Menu(X);
	
	getch();
}
