#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <locale.h>

//Variaveis Globais
#define TRUE 1 
#define FALSE 0

//Estruturas 
typedef struct {
	
	char titulo[30];
	char editora[30];
	short edicao;
	short quantPag;
	short quantidade;

} livro;

typedef struct {
	
	char titulo[30];
	char revista[30];
	short mes; //12 Meses 1 - Janeiro | 2 - Fevereiro ...
	short ano;
	short quantidade;
	
} revista;

typedef struct {
	
	char artista[30];
	char gravadora[30];
	short quantFaixas;
	short quantidade;
	
} cd;

typedef struct {
	
	char titulo[30];
	char produtor[30];
	short minutos;
	short quantidade;
	
} dvd;

typedef struct {
	
	char nome[30];
	char desenvolvedora[30];
	short quantidade;
	
	
} jogos;

typedef struct {
	
	char nome[30];
	int matricula;
	short emprestimo;
	
} aluno;



//Protopatipação de Funções



//função Primaria
int main () {
	
	setlocale(LC_ALL, "ptb");
	menu();
	getch();
	
}
