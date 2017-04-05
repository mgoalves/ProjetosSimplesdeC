/*

	Trabalho para a disciplina projeto de software
	05/04/2017
	
	Aluno:
	Marcello Gonçalves de Oliveira Alves
	
	Projeto para gestão de uma biblioteca
	
	Todos os direitos reservados.

*/

//Inclusão de Bibliotecas
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

#define qFunc 50 //Quantidade máxima de funcionarios permitido na biblioteca
#define qAlunos 5000 //  || de alunos ||
#define qLivros 15000 //  || de livros ||
#define qEditoras 500 // || de editoras ||
#define qEmprestimos 5000 // || de emprestimos ||

//Estruturas ----------------------------------------------------------------------
typedef struct {
	
	int cpf;
	char email[15];
	char nome[15];
	short sexo; // 0-mulher 1-homem
	char dataNasc[10];
	
} pessoa;

typedef struct {
	
	char titulo[30];
	short editora;
	pessoa autor;
	char areaC[30];
	short quantidade;

} livro;

typedef struct {
	
	short tipo;
	char numero[12];
	short operadora; //Tim-0  Vivo-1  Oi-2 Claro-3 Nextel-4 Correios-5
	
} telefone;

typedef struct {
	
	char logradouro[30];
	int num;
	char complemento[15];
	char bairro[15];
	int cep;
	char estado[3]; //Usar UF 
	char cidade[15];
	
} endereco;

typedef struct {
	
	char dataEmp[10];
	char dataEst[10];
	char dataCon[10];
	int idAluno;
	int idFunc;

	
 } emprestimo;

typedef struct {
	
	pessoa estudante;
	int matricula;
	short sitMatr; // 0-trancada 1-ativa 2-jubilada
	char turma;
	endereco end;
	telefone tel;
	
} aluno;

typedef struct {
	
	short idAdm; // 0-funcionario 1-administrador
	char login[10];
	char senha[10];
	endereco end;
	telefone tel;
	pessoa func;
	
} funcionario;

typedef struct {
	
	short id;
	char nome[30];
	char cnpj[15];
	
} editora;

//Ddefinindo estrutura de lista para aluno, funcionario, editora, emprestimo e livos  -----
typedef struct {
	
	funcionario F[qFunc];
	int Prim, Ult;
	
}funcEST;

typedef struct {
	
	aluno A[qAlunos];
	int Prim, Ult;
	
}alunoEST;

typedef struct {
	
	editora ED[qEditoras];
	int Prim, Ult;
	
}editEST;

typedef struct {
	
	emprestimo E[qEmprestimos];
	int Prim, Ult;
	
}empEST;

typedef struct {
	
	livro L[qLivros];
	int Prim, Ult;
	
}livroEST;


//Protopatipação de Funções ---------------------------------------------------------------
void menu();


//Funções para instaciar as listas criadas  ------------------------------------------------
void criarListaFunc(funcEST *F) {
	F -> Prim = 0;
	F -> Ult = F -> Prim;
}
void criarListaAluno(alunoEST *A) {
	A -> Prim = 0;
	A -> Ult = A -> Prim;
}
void criarListaEditora(editEST *ED) {
	ED -> Prim = 0;
	ED -> Ult = ED -> Prim;
}
void criarListaLivro(livroEST *L) {
	L -> Prim = 0;
	L -> Ult = L -> Prim;
}
void criarListaEmp(empEST *E) {
	E -> Prim = 0;
	E -> Ult = E -> Prim;
}







void menu () {
	
	//Criar listas estáticas

	
	
	//Funções para carregar arquivos para a memoria.
	//carregarArquivos();
	
	do {
		
		
		
		
	} while (1);
	
}

//função Primaria --------------------------------------------------------------------------
int main () {
	
	setlocale(LC_ALL, "ptb");
	menu();
	getch();
	
}
