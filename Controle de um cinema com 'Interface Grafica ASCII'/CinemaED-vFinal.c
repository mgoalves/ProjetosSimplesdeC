/*
	Trabalho de Estrutura de Dados - SI
	Profº Edmundo Spot - Monitora Amanda Cintra.

	Alunos:
	Marcello Gonçalves de Oliveira Alves - 201506640
	Reinaldo Albernaz de Oliveira - 201510705
	Hitallo Flavyo Lopes de Oliveira - 201517328
	Luiz Eduardo Borges Alves - 201510699

	Projeto para o controle e venda de ingressos.

	Todos os direitos reservados.
*/

//Importação de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <time.h>

#define MAX 30	  //Controla os dias.
#define SS	4	  //Controla a quantidade de sessões
#define Coluna 19 //Controla a matriz de dimensao 
#define Linha 7
#define TRUE 1
#define QMES 12 //maximo de meses que a ED suporta são 13
#define MAXF 10


//Está ED é para o controle de cada usuário, o quanto ele
//consumiu e para marcar sua poltrona.
typedef struct {

	short int meia;
	short int situacao;
	short int formaDePagamento;
	short int combo;
	float valor;

} poltrona;

//Objeivo desta ED é para o controle de cada sessão.
typedef struct {

	poltrona P[Linha][Coluna];

	short int quantInt;
	short int quantMeia;

	float valorBon;
	float valorBi;
	float valorTotalSessao;

	char filme[60];


} sessao;

//ED definida para um dia contendo 4 sessões
typedef struct {

	sessao S[SS];

	short int quantInt;
	short int quantMeia;

	float valorBon;
	float valorBi;

	float valorTotalDia;

	short int vfilme;

} dia;

//ED define um mês completo.
typedef struct {

	dia Elem[MAX];

	short int quantInt;
	short int quantMeia;

	float valorBon;
	float valorBi;

	float valorArrecado;

} mes;

//ED é uma Lista de dias, cada qual contentdo suas sessões.
typedef struct {

	mes M[QMES];
	int Prim, Ult;

} listaEST;

typedef struct {

	char f1[60];
	char f2[60];
	char f3[60];
	char f4[60];

} filmesINS;

typedef struct {

	char nome[60];

} filmeED;

typedef struct {

	filmeED Elem[MAXF];
	int Inicio, Fim, Total;

} filaEST;

//-------------------------------------------------------
//PROTOTIPO DAS FUNÇÕES
void criarLista(listaEST *L);
int verificarListaVazia (listaEST L);
int verificarListaCheia (listaEST L);
void inserirMes (listaEST *L, mes X);
void consultarVendasDiarias (listaEST L);
void exibirTela (listaEST *L, int mes, int sessao, int dia);
void exibirBomboniere (listaEST *L, int mes, int sessao, int dia, int l, int c);
void vendaIngresso(listaEST *L, int mes, int sessao, int dia);
void salvarArquivos (listaEST L);
void carregarArquivos (listaEST *L);
void consultarVendasMensais (listaEST L);
void consultarSessao(listaEST L);
void criarFila(filaEST *F);
int verificarFilaVazia(filaEST F);
int verificarFilaCheia(filaEST F);
void enfileirarAluno (filaEST *F, filmeED X);
void desenfileirarAluno(filaEST *F, filmeED *X);
void adicionarFilme(filaEST *F);
void instanciarFilme(filaEST *F, filmesINS *I);
void excluirFilme(filmesINS *I);
void lerED (filmesINS *I);
void salvarED (filmesINS I);
void exibirDias();
void consultaFilmes(filmesINS I);
void menu();
//-------------------------------------------------------

void criarLista(listaEST *L) {
	L -> Prim = 0;
	L -> Ult = L -> Prim;
}

int verificarListaVazia (listaEST L) {
	return(L.Prim == L.Ult); // Quando Prim for igual a Ult a lista está vazia
}

int verificarListaCheia (listaEST L) {
	return(L.Ult == MAX); // Quando Ult apontar para a posição Max a lista está cheia
}

void inserirMes (listaEST *L, mes X) {

	int A, P = L -> Prim;

	if (verificarListaCheia(*L)) {

		printf("\n\n\tA lista está cheia logo não foi possível adicionar um novo item.");

	} else {
		while ((P < L -> Ult))
			P++;

		if(P == L-> Ult) {

			L -> M[P] = X;
			L -> Ult ++;

		} else {

			for(A = L-> Ult; A > P; A--)
				L -> M[A] = L -> M[A-1];
			L -> M[P] = X;
			L -> Ult++;
		}
	}

}

//neste modulo mostra para o gestor do negocio como
//estão as vendas e todos os dados recolhidos
void consultarVendasDiarias (listaEST L) {

	int dia, mes;

	do {

		system ("cls");
		printf ("\n\t\t\tMÓDULO GESTOR\n\n\n");
		printf("\n\tQual Mês deseja ver os dados?");
		printf("\n\tOpcão: ");
		scanf("%d", &mes);
		fflush(stdin);

		mes--;

	} while (mes < 0 || mes >= QMES);


	do {

		system ("cls");
		printf ("\n\t\t\tMÓDULO GESTOR\n\n\n");
		printf("\n\tQual dia deseja ver os dados?");
		printf("\n\tOpcão: ");
		scanf("%d", &dia);
		fflush(stdin);

		dia--;

	} while (dia < 0 || dia >= MAX);

	system ("cls");
	printf ("\n\t\t\tMÓDULO GESTOR\n\n\n");

	printf("\n\n\t************ Total diário ***************\n");
	printf("\n\t      Valor arrecadado: %.2f", L.M[mes].Elem[dia].valorTotalDia);
	printf("\n\t      Valor Bomboniere: %.2f", L.M[mes].valorBon);
	printf("\n\t      Valor Bilheteria: %.2f", L.M[mes].valorBi);
	printf("\n\tQuantidade de inteiras: %d", L.M[mes].quantInt);
	printf("\n\t   Quantidade de meias: %d", L.M[mes].quantMeia);
	printf("\n\n\t***************************************");

	printf("\n\n\n\t*********** Sessão 16:30 ************\n");
	printf("\n\t      Valor arrecadado: %.2f", L.M[mes].Elem[dia].S[0].valorTotalSessao);
	printf("\n\t      Valor Bomboniere: %.2f", L.M[mes].Elem[dia].S[0].valorBon);
	printf("\n\t      Valor Bilheteria: %.2f", L.M[mes].Elem[dia].S[0].valorBi);
	printf("\n\tQuantidade de inteiras: %d", L.M[mes].Elem[dia].S[0].quantInt);
	printf("\n\t   Quantidade de meias: %d", L.M[mes].Elem[dia].S[0].quantMeia);
	printf("\n\n\t***************************************");

	printf("\n\n\n\t*********** Sessão 17:50 ************\n");
	printf("\n\t      Valor arrecadado: %.2f", L.M[mes].Elem[dia].S[1].valorTotalSessao);
	printf("\n\t      Valor Bomboniere: %.2f", L.M[mes].Elem[dia].S[1].valorBon);
	printf("\n\t      Valor Bilheteria: %.2f", L.M[mes].Elem[dia].S[1].valorBi);
	printf("\n\tQuantidade de inteiras: %d", L.M[mes].Elem[dia].S[1].quantInt);
	printf("\n\t   Quantidade de meias: %d", L.M[mes].Elem[dia].S[1].quantMeia);
	printf("\n\n\t***************************************");

	printf("\n\n\n\t*********** Sessão 19:20 ************\n");
	printf("\n\t      Valor arrecadado: %.2f", L.M[mes].Elem[dia].S[2].valorTotalSessao);
	printf("\n\t      Valor Bomboniere: %.2f", L.M[mes].Elem[dia].S[2].valorBon);
	printf("\n\t      Valor Bilheteria: %.2f", L.M[mes].Elem[dia].S[2].valorBi);
	printf("\n\tQuantidade de inteiras: %d", L.M[mes].Elem[dia].S[2].quantInt);
	printf("\n\t   Quantidade de meias: %d", L.M[mes].Elem[dia].S[2].quantMeia);
	printf("\n\n\t***************************************");

	printf("\n\n\n\t*********** Sessão 22:45 ************\n");
	printf("\n\t      Valor arrecadado: %.2f", L.M[mes].Elem[dia].S[3].valorTotalSessao);
	printf("\n\t      Valor Bomboniere: %.2f", L.M[mes].Elem[dia].S[3].valorBon);
	printf("\n\t      Valor Bilheteria: %.2f", L.M[mes].Elem[dia].S[3].valorBi);
	printf("\n\tQuantidade de inteiras: %d", L.M[mes].Elem[dia].S[3].quantInt);
	printf("\n\t   Quantidade de meias: %d", L.M[mes].Elem[dia].S[3].quantMeia);
	printf("\n\n\t***************************************");

	getch();

}

// Função que monstra as poltronas disponiveis
void exibirTela (listaEST *L, int mes, int sessao, int dia) {

	char X[133]; // vetor que guarda o caracter que indica se a poltrona esta livre ou ocupada

	int i, l, c;
	// Deixa livre todas as poltronas
	for(i = 0; i < 133; i++) {
		X[i] = ' ';
	};

	i = 0;
	for(l = 0; l < Linha; l++) {
		for(c = 0; c < Coluna; c++, i++) {

			if (L->M[mes].Elem[dia].S[sessao].P[l][c].situacao == 1) {
				X[i] = '@';
			}

		}
	}

	setlocale(LC_ALL, "C"); // Volta para o padrão do C *** Sempre use antes de imprimir o Cinema ***** ou então ele vai estragar tudo

	printf("\t");
	for(i = 0; i < 80; i++) {
		printf("%c", 178);
	}	// Cria as paredes do Cinema


	// Fileira G
	printf("\n\t%c  %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,178);
	printf("\t%cG %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,179,X[114],179,179,X[115],179,179,X[116],179,179,X[117],179,179,X[118],179,179,X[119],179,179,X[120],179,179,X[121],179,179,X[122],179,179,X[123],179,179,X[124],179,179,X[125],179,179,X[126],179,179,X[127],179,179,X[128],179,179,X[129],179,179,X[130],179,179,X[131],179,179,X[132],179,178);
	printf("\t%c  %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,178);
	// Fileira F
	printf("\t%c  %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,178);
	printf("\t%cF %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,179,X[95],179,179,X[96],179,179,X[97],179,179,X[98],179,179,X[99],179,179,X[100],179,179,X[101],179,179,X[102],179,179,X[103],179,179,X[104],179,179,X[105],179,179,X[106],179,179,X[107],179,179,X[108],179,179,X[109],179,179,X[110],179,179,X[111],179,179,X[112],179,179,X[113],179,178);
	printf("\t%c  %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,178);
	// Fileira E
	printf("\t%c  %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,178);
	printf("\t%cE %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,179,X[76],179,179,X[77],179,179,X[78],179,179,X[79],179,179,X[80],179,179,X[81],179,179,X[82],179,179,X[83],179,179,X[84],179,179,X[85],179,179,X[86],179,179,X[87],179,179,X[88],179,179,X[89],179,179,X[90],179,179,X[91],179,179,X[92],179,179,X[93],179,179,X[94],179,178);
	printf("\t%c  %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,178);
	// Fileira D
	printf("\t%c  %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,178);
	printf("\t%cD %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,179,X[57],179,179,X[58],179,179,X[59],179,179,X[60],179,179,X[61],179,179,X[62],179,179,X[63],179,179,X[64],179,179,X[65],179,179,X[66],179,179,X[67],179,179,X[68],179,179,X[69],179,179,X[70],179,179,X[71],179,179,X[72],179,179,X[73],179,179,X[74],179,179,X[75],179,178);
	printf("\t%c  %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,178);
	// Fileira C
	printf("\t%c  %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,178);
	printf("\t%cC %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,179,X[38],179,179,X[39],179,179,X[40],179,179,X[41],179,179,X[42],179,179,X[43],179,179,X[44],179,179,X[45],179,179,X[46],179,179,X[47],179,179,X[48],179,179,X[49],179,179,X[50],179,179,X[51],179,179,X[52],179,179,X[53],179,179,X[54],179,179,X[55],179,179,X[56],179,178);
	printf("\t%c  %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,178);
	// Fileira B
	printf("\t%c  %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,178);
	printf("\t%cB %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,179,X[19],179,179,X[20],179,179,X[21],179,179,X[22],179,179,X[23],179,179,X[24],179,179,X[25],179,179,X[26],179,179,X[27],179,179,X[28],179,179,X[29],179,179,X[30],179,179,X[31],179,179,X[32],179,179,X[33],179,179,X[34],179,179,X[35],179,179,X[36],179,179,X[37],179,178);
	printf("\t%c  %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,178);
	// Fileira A
	printf("\t%c  %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,218,196,191,178);
	printf("\t%cA %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,179,X[0],179,179,X[1],179,179,X[2],179,179,X[3],179,179,X[4],179,179,X[5],179,179,X[6],179,179,X[7],179,179,X[8],179,179,X[9],179,179,X[10],179,179,X[11],179,179,X[12],179,179,X[13],179,179,X[14],179,179,X[15],179,179,X[16],179,179,X[17],179,179,X[18],179,178);
	printf("\t%c  %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c%c%c %c\n",178,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,192,196,217,178);

	printf("\t%c   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19 %c\n",178,178); // Numeração das colunas

	printf("\t");
	for(i = 0; i < 80; i++) {
		printf("%c", 178);   // Cria as paredes do Cinema
	}
	
	setlocale(LC_ALL, "ptb"); // Volta a acentuação para português
	printf("\n\n\t\t\t\tFILME - %s", L->M[mes].Elem[dia].S[sessao].filme);
}

void exibirBomboniere (listaEST *L, int mes, int sessao, int dia, int l, int c) {

	int auxBon;

	do {

		system("cls");
		printf ("\n\t\t\tBOMBONIERE\n\n\n");
		printf("\n\n\tPipoca:");
		printf("\n\t1 - R$  5,00 - Pipoca média");
		printf("\n\t2 - R$  7.50 - Pipoca Grande");
		printf("\n\t3 - R$ 10.00 - Pipoca Mega");
		printf("\n\n\tRefrigerante:");
		printf("\n\t4 - R$ 10.00 - Refrigerante Médio");
		printf("\n\t5 - R$ 12.50 - Refrigerante Grande");
		printf("\n\n\tCombos:");
		printf("\n\t6 - R$ 20.50 - Pipoca Mega + Refri Grande");
		printf("\n\t7 - R$ 31.00 - Pipoca Mega + 2 Refri Grande");
		printf("\n\n\t8 - Continuar sem bomboniere");
		printf("\n\tOpcão: ");
		scanf (" %d", &auxBon);
		fflush(stdin);

		auxBon--;

	} while(auxBon != 0 && auxBon != 1 && auxBon != 2 && auxBon != 3  && auxBon != 4
	        && auxBon != 5  && auxBon != 6  && auxBon != 7);


	if (auxBon == 0) {

		L->M[mes].Elem[dia].S[sessao].P[l][c].combo = 0;
		L->M[mes].Elem[dia].S[sessao].P[l][c].valor += 5.00;
		L->M[mes].valorBon += 5.00;
		L->M[mes].valorArrecado += 5.00;
		L->M[mes].Elem[dia].valorTotalDia += 5.00;
		L->M[mes].Elem[dia].valorBon += 5.00;
		L->M[mes].Elem[dia].S[sessao].valorTotalSessao += 5.00;
		L->M[mes].Elem[dia].S[sessao].valorBon += 5.00;

	} else if (auxBon == 1) {

		L->M[mes].Elem[dia].S[sessao].P[l][c].combo = 1;
		L->M[mes].Elem[dia].S[sessao].P[l][c].valor += 7.50;
		L->M[mes].valorBon += 7.50;
		L->M[mes].valorArrecado += 7.50;
		L->M[mes].Elem[dia].valorTotalDia += 7.50;
		L->M[mes].Elem[dia].valorBon += 7.50;
		L->M[mes].Elem[dia].S[sessao].valorTotalSessao += 7.50;
		L->M[mes].Elem[dia].S[sessao].valorBon += 7.50;


	} else if (auxBon == 2) {

		L->M[mes].Elem[dia].S[sessao].P[l][c].combo = 2;
		L->M[mes].Elem[dia].S[sessao].P[l][c].valor += 10.00;
		L->M[mes].valorBon += 10.00;
		L->M[mes].valorArrecado += 10.00;
		L->M[mes].Elem[dia].valorTotalDia += 10.00;
		L->M[mes].Elem[dia].valorBon += 10.00;
		L->M[mes].Elem[dia].S[sessao].valorTotalSessao += 10.00;
		L->M[mes].Elem[dia].S[sessao].valorBon += 10.00;


	}  else if (auxBon == 3) {

		L->M[mes].Elem[dia].S[sessao].P[l][c].combo = 3;
		L->M[mes].Elem[dia].S[sessao].P[l][c].valor += 10.00;
		L->M[mes].valorBon += 10.00;
		L->M[mes].valorArrecado += 10.00;
		L->M[mes].Elem[dia].valorTotalDia += 10.00;
		L->M[mes].Elem[dia].valorBon += 10.00;
		L->M[mes].Elem[dia].S[sessao].valorTotalSessao += 10.00;
		L->M[mes].Elem[dia].S[sessao].valorBon += 10.00;


	}  else if (auxBon == 4) {

		L->M[mes].Elem[dia].S[sessao].P[l][c].combo = 4;
		L->M[mes].Elem[dia].S[sessao].P[l][c].valor += 12.50;
		L->M[mes].valorBon += 12.50;
		L->M[mes].valorArrecado += 12.50;
		L->M[mes].Elem[dia].valorTotalDia += 12.50;
		L->M[mes].Elem[dia].valorBon += 12.50;
		L->M[mes].Elem[dia].S[sessao].valorTotalSessao += 12.50;
		L->M[mes].Elem[dia].S[sessao].valorBon += 12.50;


	}  else if (auxBon == 5) {

		L->M[mes].Elem[dia].S[sessao].P[l][c].combo = 5;
		L->M[mes].Elem[dia].S[sessao].P[l][c].valor += 20.50;
		L->M[mes].valorBon += 20.50;
		L->M[mes].valorArrecado += 20.50;
		L->M[mes].Elem[dia].valorTotalDia += 20.50;
		L->M[mes].Elem[dia].valorBon += 20.50;
		L->M[mes].Elem[dia].S[sessao].valorTotalSessao += 20.50;
		L->M[mes].Elem[dia].S[sessao].valorBon += 20.50;

	}  else if (auxBon == 6) {

		L->M[mes].Elem[dia].S[sessao].P[l][c].combo = 6;
		L->M[mes].Elem[dia].S[sessao].P[l][c].valor += 31.00;
		L->M[mes].valorBon += 31.00;
		L->M[mes].valorArrecado += 31.00;
		L->M[mes].Elem[dia].valorTotalDia += 31.00;
		L->M[mes].Elem[dia].valorBon += 31.00;
		L->M[mes].Elem[dia].S[sessao].valorTotalSessao += 31.00;
		L->M[mes].Elem[dia].S[sessao].valorBon += 31.00;

	}

	do {


		system("cls");
		printf ("\n\n\t\t\tFormas de Pagamento\n\n\n");
		printf("\n\t1 - Dinheiro");
		printf("\n\t2 - MasterCard");
		printf("\n\t3 - MasterCard Maestro");;
		printf("\n\t4 - Visa");
		printf("\n\t5 - Visa Eletron");
		printf("\n\t6 - ELO");

		printf("\n\n\tTotal: %.2f", L->M[mes].Elem[dia].S[sessao].P[l][c].valor);
		printf("\n\tOpcão: ");

		scanf (" %d", &auxBon);
		fflush(stdin);

		auxBon--;



	} while (auxBon != 0 && auxBon != 1 && auxBon != 2 && auxBon != 3  && auxBon != 4
	         && auxBon != 5);


	L->M[mes].Elem[dia].S[sessao].P[l][c].formaDePagamento = auxBon;

}



// Este será responsável pela venda do ingresso,
// ou seja, irá validar se a poltrona está disponivel;
void vendaIngresso(listaEST *L, int mes, int sessao, int dia) {

	int c, l, i = 0;
	for(l = 0; l < Linha; l++) {
		for(c = 0; c < Coluna; c++, i++) {

			if (L->M[mes].Elem[dia].S[sessao].P[l][c].situacao == 1) {
				i++;
			}

		}
	}

	if (i == 136) {

		printf ("\n\n\tTodas as poltronas desta sessão já estão ocupadas.");
		getch();

	} else {

		char meiaAux;
		int  op = 0, sair = 1;



		do {

			op = 0;

			system ("cls");
			printf ("\n\t\t\tVENDA DE INGRESSOS\n\n\n");
			printf ("\n\tMês: %d", ((mes) + 1));
			printf ("\n\tDia: %d", ((dia) + 1));
			printf("\n\tFilme: %s\n",L->M[mes].Elem[dia].S[sessao].filme);

			exibirTela(L, mes, sessao, dia);

			char auxL;

			printf ("\n\n\tSelecione a linha: ");
			scanf (" %c", &auxL);
			fflush(stdin);
			printf ("\n\n\tSelecione a coluna: ");
			scanf (" %d", &c);
			fflush(stdin);

			if (auxL == 'a' || auxL == 'A') {
				l = 0;
			} else if (auxL == 'b' || auxL == 'B') {
				l = 1;
			} else if (auxL == 'c' || auxL == 'C') {
				l = 2;
			} else if (auxL == 'd' || auxL == 'D') {
				l = 3;
			} else if (auxL == 'e' || auxL == 'E') {
				l = 4;
			} else if (auxL == 'f' || auxL == 'F') {
				l = 5;
			} else if (auxL == 'g' || auxL == 'G') {
				l = 6;
			}

			c--;

			if (c != 0 && c != 1 && c != 2 && c != 3  && c != 4 && c != 5 && c != 6 
			&& c != 7 && c != 8  && c != 9 && c != 10 && c != 11 && c != 12 
			&& c != 13 && c != 14  && c != 15 && c != 16 && c != 17  && c != 18) {

				do {
					
					system("cls");
					printf ("\n\n\tPoltrona Inválida.");

					printf ("\n\n\tDeseja selecionar outra poltrona? [S][N]: ");
					scanf (" %c", &meiaAux);
					fflush(stdin);

					if (meiaAux == 's' || meiaAux == 'S') {

						op = 1;
						sair = 0;

					} else if (meiaAux == 'n' || meiaAux == 'N') {

						sair = 0;

					}

				} while (sair);

				sair = 1;

			} else if (l != 0 && l != 1 && l != 2 && l != 3  && l != 4 && l != 5 && l != 6) {

				do {
					printf ("\n\n\tPoltrona Inválida.");

					printf ("\n\n\tDeseja selecionar outra? [S][N]: ");
					scanf (" %c", &meiaAux);
					fflush(stdin);

					if (meiaAux == 's' || meiaAux == 'S') {

						op = 1;
						sair = 0;

					} else if (meiaAux == 'n' || meiaAux == 'N') {

						sair = 0;

					}

				} while (sair);

				sair = 1;


			} else if (L->M[mes].Elem[dia].S[sessao].P[l][c].situacao == 0) {

				do {

					system ("cls");
					printf ("\n\t\t\tVENDA DE INGRESSOS\n\n\n");
					printf ("\n\tInteira - R$ 17,00");
					printf ("\n\tMeia    - R$  8,50");
					printf ("\n\tApresentou a carteirinha? [S][N]: ");
					scanf (" %c", &meiaAux);
					fflush(stdin);

				} while (meiaAux != 's' && meiaAux != 'S' && meiaAux != 'n' && meiaAux != 'N');

				if (meiaAux == 's' || meiaAux == 'S') {

					L->M[mes].Elem[dia].S[sessao].P[l][c].meia = 1;
					L->M[mes].Elem[dia].S[sessao].P[l][c].valor += 8.50;

					L->M[mes].Elem[dia].quantMeia++;
					L->M[mes].Elem[dia].valorTotalDia += 8.50;
					L->M[mes].Elem[dia].valorBi += 8.50;

					L->M[mes].Elem[dia].S[sessao].valorTotalSessao += 8.50;
					L->M[mes].Elem[dia].S[sessao].quantMeia++;
					L->M[mes].Elem[dia].S[sessao].valorBi += 8.50;

					L->M[mes].quantMeia++;
					L->M[mes].valorBi += 8.50;
					L->M[mes].valorArrecado += 8.50;

				} else {

					L->M[mes].Elem[dia].S[sessao].P[l][c].meia = 0;
					L->M[mes].Elem[dia].S[sessao].P[l][c].valor += 17.00;

					L->M[mes].Elem[dia].quantInt++;
					L->M[mes].Elem[dia].valorTotalDia += 17.00;
					L->M[mes].Elem[dia].valorBi += 17.00;

					L->M[mes].Elem[dia].S[sessao].valorTotalSessao += 17.00;
					L->M[mes].Elem[dia].S[sessao].quantInt++;
					L->M[mes].Elem[dia].S[sessao].valorBi += 17.00;

					L->M[mes].quantInt++;
					L->M[mes].valorBi += 17.00;
					L->M[mes].valorArrecado += 17.00;
				}


				L->M[mes].Elem[dia].S[sessao].P[l][c].situacao = 1;


				exibirBomboniere(L, mes, sessao, dia, l, c);

				printf ("\n\tVenda realizada com sucesso!!");


				char aux;
				do {
					system("cls");
					printf ("\n\tVenda realizada com sucesso!!");
					printf ("\n\n\tDeseja comprar mais um ingresso para esta sessão? [S][N]: ");
					scanf(" %c", &aux);
					fflush(stdin);

					if (aux == 'S' || aux == 's') {

						vendaIngresso(L, mes, sessao, dia);
						sair = 0;

					} else if (aux == 'N' || aux == 'n') {

						sair = 0;
					}

				} while (sair);



			} else {

				printf ("\n\n\tPoltrona Inválida ou Já Está Ocupada.");

				printf ("\n\n\tDeseja selecionar outra? [S][N]: ");
				scanf (" %c", &meiaAux);
				fflush(stdin);

				if (meiaAux == 's' || meiaAux == 'S') {

					op = 1;
				}

			}

		} while (op);
	}
}

//responsável por salvar nos arquivos os dados
void salvarArquivos (listaEST L) {


	int i, k, l, c, m;
	char nomeArq[6] = "00.txt";

	system ("cls");
	printf ("\n\n\tSalvando os dados, por favor aguarde...");

	FILE *arquivo;

	for(m = 0; m < QMES; m++) {

		char aux = (char) m;

		if (m < 10) {

			nomeArq[0] = '0';
			nomeArq[1] = aux + 48;

		} else if (m >= 10 && m < 20) {

			aux = m % 10;

			nomeArq[0] = '1';
			nomeArq[1] = aux + 48;

		}


		arquivo = fopen (nomeArq, "w+");


		i = 0;
		for (i = 0; i < MAX; i++) { //Controla o dia

			k = 0;
			for(k = 0; k < SS; k++) { //Controla as sessões

				l = c = 0;
				for(l = 0; l < Linha; l++) { //Controla a matriz (poltonas) - Linhas

					c = 0;
					for(c = 0; c < Coluna; c++) { //Colunas

						fprintf (arquivo,"%d;%d;%.2f;%.2f;%.2f;%d;%d;%.2f;%.2f;%.2f;%d;%d;%.2f;%.2f;%.2f;%d;%d;%d;%d;%.2f\n",

						         L.M[m].quantMeia,
						         L.M[m].quantInt,
						         L.M[m].valorBon,
						         L.M[m].valorBi,
						         L.M[m].valorArrecado,
						         L.M[m].Elem[i].quantMeia,
						         L.M[m].Elem[i].quantInt,
						         L.M[m].Elem[i].valorBon,
						         L.M[m].Elem[i].valorBi,
						         L.M[m].Elem[i].valorTotalDia,
						         L.M[m].Elem[i].S[k].quantMeia,
						         L.M[m].Elem[i].S[k].quantInt,
						         L.M[m].Elem[i].S[k].valorBon,
						         L.M[m].Elem[i].S[k].valorBi,
						         L.M[m].Elem[i].S[k].valorTotalSessao,
						         L.M[m].Elem[i].S[k].P[l][c].meia,
						         L.M[m].Elem[i].S[k].P[l][c].situacao,
						         L.M[m].Elem[i].S[k].P[l][c].combo,
						         L.M[m].Elem[i].S[k].P[l][c].formaDePagamento,
						         L.M[m].Elem[i].S[k].P[l][c].valor

						        );
					}
				}

			}
		}
	}


	fclose (arquivo);

	printf ("\n\n\tOs dados foram salvos com sucesso.");

}

//Assim que o programa executar,
//este irá carregar os dados
//já salvos em arquivos
void carregarArquivos (listaEST *L) {

	system ("cls");
	printf ("\n\n\tInicializando.");

	FILE *arquivo;

	int i, k, l, c, m;
	mes Aux;
	char nomeArq[6] = "00.txt";
	char linha[100];


	for (m = 0; m < QMES; m++) {

		char aux = (char) m;

		if (m < 10) {

			nomeArq[0] = '0';
			nomeArq[1] = aux + 48;

		} else if (m >= 10 && m < 20) {

			aux = m % 10;

			nomeArq[0] = '1';
			nomeArq[1] = aux + 48;

		}


		arquivo = fopen (nomeArq, "r+");

		i = 0;
		for (i = 0; i < MAX; i++) { //Controla o dia


			k = 0;
			for(k = 0; k < SS; k++) { //Controla as sessões

				l = c = 0;
				for(l = 0; l < Linha; l++) { //Controla a matriz (poltonas) - Linhas

					c = 0;
					for(c = 0; c < Coluna; c++) { //Colunas

						fscanf (arquivo, "%s", linha);

						Aux.quantMeia = atoi (strtok(linha, ";"));
						Aux.quantInt = atoi (strtok(NULL, ";"));
						Aux.valorBon =  atof (strtok(NULL, ";"));
						Aux.valorBi =  atof (strtok(NULL, ";"));
						Aux.valorArrecado =  atof (strtok(NULL, ";"));
						Aux.Elem[i].quantMeia = atoi (strtok(NULL, ";"));
						Aux.Elem[i].quantInt = atoi (strtok(NULL, ";"));
						Aux.Elem[i].valorBon = atof (strtok(NULL, ";"));
						Aux.Elem[i].valorBi = atof (strtok(NULL, ";"));
						Aux.Elem[i].valorTotalDia = atof (strtok(NULL, ";"));
						Aux.Elem[i].S[k].quantMeia = atoi (strtok(NULL, ";"));
						Aux.Elem[i].S[k].quantInt = atoi (strtok(NULL, ";"));
						Aux.Elem[i].S[k].valorBon = atof (strtok(NULL, ";"));
						Aux.Elem[i].S[k].valorBi = atof (strtok(NULL, ";"));
						Aux.Elem[i].S[k].valorTotalSessao = atof (strtok(NULL, ";"));
						Aux.Elem[i].S[k].P[l][c].meia = atoi (strtok(NULL, ";"));
						Aux.Elem[i].S[k].P[l][c].situacao = atoi (strtok(NULL, ";"));
						Aux.Elem[i].S[k].P[l][c].combo = atoi (strtok(NULL, ";"));
						Aux.Elem[i].S[k].P[l][c].formaDePagamento = atoi (strtok(NULL, ";"));
						Aux.Elem[i].S[k].P[l][c].valor = atof (strtok(NULL, "\n"));
						

					}
				}

			}
		}

		//Insere o dia na lista
		inserirMes(L, Aux);

	}

	fclose(arquivo);

	printf ("\n\n\n\tArquivos carregados com sucesso.");
}

void consultarVendasMensais (listaEST L) {

	int mes;


	do {
		system ("cls");
		printf ("\n\t\t\tMÓDULO GESTOR\n");
		printf ("\n\t\t\tCINEMA ED\n\n\n");
		printf("\n\tQual mês deseja?");
		printf("\n\t(Meses válidos: 1 - 12)");
		printf("\n\tMês: ");
		scanf("%d", &mes);
		fflush(stdin);

		mes--;

	} while (mes < 0 || mes >= QMES);

	double v01 = 0.0, v02 = 0.0, v03 = 0.0, v04 = 0.0;
	double i01 = 0.0, i02 = 0.0, i03 = 0.0, i04 = 0.0;
	double b01 = 0.0, b02 = 0.0, b03 = 0.0, b04 = 0.0;
	int int01 = 0, int02 = 0, int03 = 0, int04 = 0.0;
	int m01 = 0, m02 = 0, m03 = 0, m04 = 0;

	int dia = 0;
	for (dia = 0; dia < MAX; dia++) {

		v01 += 		L.M[mes].Elem[dia].S[0].valorTotalSessao;
		b01 +=		L.M[mes].Elem[dia].S[0].valorBon;
		i01 +=		L.M[mes].Elem[dia].S[0].valorBi;
		int01 += 	L.M[mes].Elem[dia].S[0].quantInt;
		m01 +=		L.M[mes].Elem[dia].S[0].quantMeia;

		v02 += 		L.M[mes].Elem[dia].S[1].valorTotalSessao;
		b02 +=		L.M[mes].Elem[dia].S[1].valorBon;
		i02 +=		L.M[mes].Elem[dia].S[1].valorBi;
		int02 += 	L.M[mes].Elem[dia].S[1].quantInt;
		m01 +=		L.M[mes].Elem[dia].S[1].quantMeia;

		v03 += 		L.M[mes].Elem[dia].S[2].valorTotalSessao;
		b03 +=		L.M[mes].Elem[dia].S[2].valorBon;
		i03 +=		L.M[mes].Elem[dia].S[2].valorBi;
		int03 += 	L.M[mes].Elem[dia].S[2].quantInt;
		m03 +=		L.M[mes].Elem[dia].S[2].quantMeia;

		v04 += 		L.M[mes].Elem[dia].S[3].valorTotalSessao;
		b04 +=		L.M[mes].Elem[dia].S[3].valorBon;
		i04 +=		L.M[mes].Elem[dia].S[3].valorBi;
		int04 += 	L.M[mes].Elem[dia].S[3].quantInt;
		m04 +=		L.M[mes].Elem[dia].S[3].quantMeia;

	}

	printf("\n\n\t************ Total Mensal *************\n");
	printf("\n\t      Valor arrecadado: %.2f", L.M[mes].valorArrecado);
	printf("\n\t      Valor Bomboniere: %.2f", L.M[mes].valorBon);
	printf("\n\t      Valor Bilheteria: %.2f", L.M[mes].valorBi);
	printf("\n\tQuantidade de inteiras: %d", L.M[mes].quantInt);
	printf("\n\t   Quantidade de meias: %d", L.M[mes].quantMeia);
	printf("\n\n\t***************************************");

	printf("\n\n\n\t*********** Sessão 16:30 ************\n");
	printf("\n\t      Valor arrecadado: %.2f", v01);
	printf("\n\t      Valor Bomboniere: %.2f", b01);
	printf("\n\t      Valor Bilheteria: %.2f", i01);
	printf("\n\tQuantidade de inteiras: %d", int01);
	printf("\n\t   Quantidade de meias: %d", m01);
	printf("\n\n\t***************************************");

	printf("\n\n\n\t*********** Sessão 17:50 ************\n");
	printf("\n\t      Valor arrecadado: %.2f", v02);
	printf("\n\t      Valor Bomboniere: %.2f", b02);
	printf("\n\t      Valor Bilheteria: %.2f", i02);
	printf("\n\tQuantidade de inteiras: %d", int02);
	printf("\n\t   Quantidade de meias: %d", m02);
	printf("\n\n\t***************************************");

	printf("\n\n\n\t*********** Sessão 19:20 ************\n");
	printf("\n\t      Valor arrecadado: %.2f", v03);
	printf("\n\t      Valor Bomboniere: %.2f", b03);
	printf("\n\t      Valor Bilheteria: %.2f", i03);
	printf("\n\tQuantidade de inteiras: %d", int03);
	printf("\n\t   Quantidade de meias: %d", m03);
	printf("\n\n\t***************************************");

	printf("\n\n\n\t*********** Sessão 22:45 ************\n");
	printf("\n\t      Valor arrecadado: %.2f", v04);
	printf("\n\t      Valor Bomboniere: %.2f", b04);
	printf("\n\t      Valor Bilheteria: %.2f", i04);
	printf("\n\tQuantidade de inteiras: %d", int04);
	printf("\n\t   Quantidade de meias: %d", m04);
	printf("\n\n\t***************************************");

	getch();

}

void consultarSessao(listaEST L) {

	int dia, sessao, mes;

	do {

		system ("cls");
		printf ("\n\t\t\tMÓDULO GESTOR\n\n\n");
		printf("\n\tQual mês deseja ver os dados?");
		printf("\n\t(Meses válidos: 1 - 12)");
		printf("\n\tOpcão: ");
		scanf("%d", &mes);
		fflush(stdin);

		mes--;

	} while (mes < 0 || mes >= QMES);

	do {

		system ("cls");
		printf ("\n\t\t\tMÓDULO GESTOR\n\n\n");
		printf("\n\tQual dia deseja ver os dados?");
		printf("\n\t(Dias válidos: 1 - 30)");
		printf("\n\tOpcão: ");
		scanf("%d", &dia);
		fflush(stdin);

		dia--;

	} while (dia < 0 || dia >= MAX);

	do {

		system ("cls");
		printf ("\n\t\t\tMÓDULO GESTOR\n\n\n");
		printf("\n\tQual sessão?");
		printf("\n\tSessões válidas: ");
		printf("\n\t1 - 16:30 - %s", L.M[mes].Elem[dia].S[0].filme);
		printf("\n\t2 - 17:50 - %s", L.M[mes].Elem[dia].S[1].filme);
		printf("\n\t3 - 19:20 - %s", L.M[mes].Elem[dia].S[2].filme);
		printf("\n\t4 - 22:45 - %s", L.M[mes].Elem[dia].S[3].filme);
		printf("\n\tOpcão: ");
		scanf("%d", &sessao);
		fflush(stdin);

		sessao--;

	} while (sessao < 0 || sessao >= SS);

	system("cls");
	printf ("\n\t\t\tMÓDULO GESTOR\n");
	printf("\n\t************** TOTAL ************\n");
	printf ("\n\tValor arrecado nesta sessão: %.2f", L.M[mes].Elem[dia].S[sessao].valorTotalSessao);
	printf ("\n\t        Valor da Bomboniere: %.2f\n", L.M[mes].Elem[dia].S[sessao].valorBon);
	printf ("\n\t         Valor de Ingressos: %.2f\n", L.M[mes].Elem[dia].S[sessao].valorBi);
	printf ("\n\t         Total de ingressos: %d", L.M[mes].Elem[dia].S[sessao].quantInt
	        + L.M[mes].Elem[dia].S[sessao].quantMeia);
	printf ("\n\t          Total de inteiras: %d", L.M[mes].Elem[dia].S[sessao].quantInt);
	printf ("\n\t             Total de meias: %d\n", L.M[mes].Elem[dia].S[sessao].quantMeia);
	printf("\n\t*********************************\n\n");

	exibirTela(&L, mes, sessao, dia);

	getch();
}

void criarFila(filaEST *F) {

	F-> Inicio = 0;
	F-> Fim = 0;
	F-> Total = 0;
}

int verificarFilaVazia(filaEST F) {

	return(F.Inicio == F.Fim);
}

int verificarFilaCheia(filaEST F) {

	return((F.Fim + 1) % MAXF == F.Fim);
}

void enfileirarAluno (filaEST *F, filmeED X) {

	F->Elem[F->Fim] = X;
	F->Fim = (F->Fim + 1) % MAXF;
	F->Total++;

	printf("\n\n\tFilme adicionado com sucesso a fila de espera.");

}

void desenfileirarAluno(filaEST *F, filmeED *X) {

	*X = F->Elem[F->Inicio];
	F -> Inicio = (F->Inicio + 1) % MAXF;
	F -> Total--;

}

void adicionarFilme(filaEST *F) {

	if(verificarFilaCheia(*F)) {

		printf("\n\n\tA fila de filmes no momento está cheia, instancie um filme primeiro.");

	} else {

		filmeED X;


		system("cls");
		printf("\n\n\tInsira o nome do filme:");
		printf("\n\tNome: ");
		gets(X.nome);
		fflush(stdin);

		enfileirarAluno(F, X);


	}
}


void instanciarFilme(filaEST *F, filmesINS *I) {

	if(verificarFilaVazia(*F)) {

		printf("\n\n\tNão há filmes na fila de espera.");


	} else if (strcmp(I->f1,"") == 0) {

		filmeED *X;
		desenfileirarAluno(F, X);
		strcpy(I->f1, X->nome);
		printf("\n\n\tElemento removido da fila e adicionado aos filmes disponiveis ");

	} else if (strcmp(I->f2,"") == 0) {

		filmeED *X;
		desenfileirarAluno(F, X);
		strcpy(I->f2, X->nome);
		printf("\n\n\tElemento removido da fila e adicionado aos filmes disponiveis ");

	} else if (strcmp(I->f3,"") == 0) {

		filmeED *X;
		desenfileirarAluno(F, X);
		strcpy(I->f3, X->nome);
		printf("\n\n\tElemento removido da fila e adicionado aos filmes disponiveis ");

	} else if (strcmp(I->f4,"") == 0) {

		filmeED *X;
		desenfileirarAluno(F, X);
		strcpy(I->f4, X->nome);
		printf("\n\n\tElemento removido da fila e adicionado aos filmes disponiveis ");

	} else {

		printf("\n\n\tNão há espaço, exclua filmes primeiro.");

	}
	getch();
}


void excluirFilme(filmesINS *I) {

	int op;

	do {

		system("cls");
		printf("\n\n\n\tEXCLUSÃO DE FILMES\n");
		printf("\n\tQual filme deseja excluir?\n\n");
		printf("\n\t1 - %s", I->f1);
		printf("\n\t2 - %s", I->f2);
		printf("\n\t3 - %s", I->f3);
		printf("\n\t4 - %s", I->f4);
		printf("\n\tOpção: ");
		scanf(" %d", &op);
		fflush(stdin);

	} while (op != 1 && op != 2 && op != 3 && op != 4);

	if (op == 1) {

		strcpy(I->f1, "");

	} else if (op == 2) {

		strcpy(I->f2, "");

	} else if (op == 3) {

		strcpy(I->f3, "");

	} else if (op == 4) {

		strcpy(I->f4, "");

	}

	printf("\n\n\tExcluido com sucesso. ");
	getch();

}

void lerED (filmesINS *I) {


	char nomeArq[] = "EDFilmes.txt";
	char linha[60];
	filmesINS Aux[4];

	FILE *arquivo;

	arquivo = fopen (nomeArq, "r+");

	int i;
	for (i = 0; i < 4; i++) {

		fgets(linha, sizeof(linha), arquivo);
		strcpy(Aux[i].f1,linha);

	}

	strcpy(I->f1,Aux[0].f1);
	strcpy(I->f2,Aux[1].f1);
	strcpy(I->f3,Aux[2].f1);
	strcpy(I->f4,Aux[3].f1);


	fclose (arquivo);
}

void salvarED (filmesINS I) {



	char nomeArq[] = "EDFilmes.txt";
	char linha[60];

	FILE *arquivo;

	arquivo = fopen (nomeArq, "w+");

	int i;
	for (i = 0; i < 4; i++) {

		if (i == 0) {

			fprintf (arquivo,"%s", I.f1);

		} else if (i == 1) {

			fprintf (arquivo,"%s", I.f2);

		} else if (i == 2) {

			fprintf (arquivo,"%s", I.f3);

		} else if (i == 3) {

			fprintf (arquivo,"%s", I.f4);

		}

	}

	fclose (arquivo);

}

void exibirDias() {

	setlocale(LC_ALL, "C"); // Volta para o padrão do C *** Sempre use antes de imprimir o Cinema ***** ou então ele vai estragar tudo

	int D[30];
	int i, k;
	for(i = 0; i < 31; i++) {
		D[i] = i+1;
	}

	printf("\n\t");
	for(i = 0; i < 38; i++) {
		printf("%c", 178);
	}	// Cria as bordas do calendario


	printf("\n");
	printf("\t%c DOM  SEG  TER  QUA  QUI  SEX  SAB  %c\n",178,178);
	//Primeira semana
	printf("\t%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c\n",178,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,178);
	printf("\t%c %c%2d%c %c%2d%c %c%2d%c %c%2d%c %c%2d%c %c%2d%c %c%2d%c %c\n",178,179,D[0],179,179,D[1],179,179,D[2],179,179,D[3],179,179,D[4],179,179,D[5],179,179,D[6],179,178);
	printf("\t%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c\n",178,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,178);
	//Segunda semana
	printf("\t%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c\n",178,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,178);
	printf("\t%c %c%2d%c %c%2d%c %c%2d%c %c%2d%c %c%2d%c %c%2d%c %c%2d%c %c\n",178,179,D[7],179,179,D[8],179,179,D[9],179,179,D[10],179,179,D[11],179,179,D[12],179,179,D[13],179,178);
	printf("\t%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c\n",178,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,178);
	//Terceira semana
	printf("\t%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c\n",178,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,178);
	printf("\t%c %c%2d%c %c%2d%c %c%2d%c %c%2d%c %c%2d%c %c%2d%c %c%2d%c %c\n",178,179,D[14],179,179,D[15],179,179,D[16],179,179,D[17],179,179,D[18],179,179,D[19],179,179,D[20],179,178);
	printf("\t%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c\n",178,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,178);
	//Quarta semana
	printf("\t%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c\n",178,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,178);
	printf("\t%c %c%2d%c %c%2d%c %c%2d%c %c%2d%c %c%2d%c %c%2d%c %c%2d%c %c\n",178,179,D[21],179,179,D[22],179,179,D[23],179,179,D[24],179,179,D[25],179,179,D[26],179,179,D[27],179,178);
	printf("\t%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c\n",178,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,178);
	//Quinta semana
	printf("\t%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c\n",178,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,218,196,196,191,178);
	printf("\t%c %c%2d%c %c%2d%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c\n",178,179,D[28],179,179,D[29],179,179,255,255,179,179,255,255,179,179,255,255,179,179,255,255,179,179,255,255,179,178);
	printf("\t%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c\n",178,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,192,196,196,217,178);

	printf("\t");
	for(i = 0; i < 38; i++) {
		printf("%c", 178);   // Cria as bordas do calendario
	}

	setlocale(LC_ALL, "ptb"); // Volta a acentuação para português
}

void consultaFilmes(filmesINS I){
	
	system("cls");
	printf ("\n\t\t\tFILMES EM CARTAZ\n\n\n");
	printf("\n\n\t1 - %s",I.f1);
	printf("\n\n\t2 - %s",I.f2);
	printf("\n\n\t3 - %s",I.f3);
	printf("\n\n\t4 - %s",I.f4);
	
}


void menu() {


	//Resposável por terminar o programa.
	do {

		filaEST F;
		filmesINS I;
		listaEST L;

		criarFila(&F);
		lerED(&I);
		criarLista(&L);
		carregarArquivos(&L);

		printf ("\n\n\tRecomendamos que use a tela em tamanho máximo para mais conforto.");
		getch();

		int opcao;

		//Responsável por uma venda.
		do {


			system ("cls");
			printf ("\n\t\t\tCINEMA ED\n\n\n");
			printf("\n\t1 - Vender assentos");
			printf("\n\t2 - Módulo Gestor");
			printf("\n\t3 - Sair");
			printf("\n\tOpcão: ");
			scanf("%d", &opcao);
			fflush(stdin);

			int dia;
			int sessao;
			int mes;

			if (opcao == 1) {

				do {

					system ("cls");
					printf ("\n\t\t\tCINEMA ED\n\n\n");
					printf("\n\tPara qual mês deseja realizar a venda?");
					printf("\n\t(Meses válidos: 1 - 12)");
					printf("\n\tMês: ");
					scanf("%d", &mes);
					fflush(stdin);

					mes--; //mesmo principio acima

				} while (mes < 0 || mes >= QMES);

				do {

					system ("cls");
					printf ("\n\t\t\tCINEMA ED\n\n\n");
					printf("\n\tPara qual dia deseja realizar a venda?");
					printf("\n\t(Dias válidos: 1 - 30)");

					printf("\n\tDia: ");
					scanf("%d", &dia);
					fflush(stdin);

					dia--; //mesmo principio acima

				} while (dia < 0 || dia >= MAX);

				if (L.M[mes].Elem[dia].vfilme == 0) {

					int k, ran;
					L.M[mes].Elem[dia].vfilme == 1;

					for (k = 0; k < 4; k++) {
						
						ran = 1 + (rand() % 4);

						if (ran == 1) {
							
							strcpy(L.M[mes].Elem[dia].S[k].filme, I.f1);

						} else if (ran == 2) {
							
							strcpy(L.M[mes].Elem[dia].S[k].filme, I.f2);

						} else if (ran == 3) {
							
							strcpy(L.M[mes].Elem[dia].S[k].filme, I.f3);

						} else if (ran == 4) {
							
							strcpy(L.M[mes].Elem[dia].S[k].filme, I.f4);

						}

					}
					
				}

				do {

					system ("cls");
					printf ("\n\t\t\tFILMES EM CARTAZ\n\n\n");
					printf("\n\t1 - 16:30 - %s", L.M[mes].Elem[dia].S[0].filme);
					printf("\n\t2 - 17:50 - %s", L.M[mes].Elem[dia].S[1].filme);
					printf("\n\t3 - 19:20 - %s", L.M[mes].Elem[dia].S[2].filme);
					printf("\n\t4 - 22:45 - %s", L.M[mes].Elem[dia].S[3].filme);
					printf("\n\tOpcão: ");
					scanf("%d", &sessao);
					fflush(stdin);

					sessao--; //sessao sempre comeca com zero por isso diminuir 1;

				} while (sessao != 0 && sessao != 1 && sessao != 2 && sessao != 3);

				vendaIngresso(&L, mes, sessao, dia);

			} else if (opcao == 2) {

				int auxMG;

				do {


					do {

						system ("cls");
						printf ("\n\t\t\tMODULO GESTOR\n\n\n");
						printf("\n\t1 - Dados mensais");
						printf("\n\t2 - Dados diários");
						printf("\n\t3 - Dados por sessões");
						printf("\n\t4 - Adicionar Filme");
						printf("\n\t5 - Instaciar Filme");
						printf("\n\t6 - Excluir Filme");
						printf("\n\t7 - Consultar Filmes em Cartaz");
						printf("\n\t8 - Sair");
						printf("\n\tOpcão: ");
						scanf("%d", &auxMG);
						fflush(stdin);

						auxMG--;

					} while (auxMG != 0 && auxMG != 1 && auxMG != 2 && auxMG != 3
					         && auxMG != 4 && auxMG != 5 && auxMG != 6  && auxMG != 7);

					if (auxMG == 0) {

						consultarVendasMensais(L);

					} else if (auxMG == 1) {

						consultarVendasDiarias(L);

					} else if (auxMG == 2) {

						consultarSessao(L);

					} else if (auxMG == 3) {

						adicionarFilme(&F);
						getch();

					} else if (auxMG == 4) {

						instanciarFilme(&F , &I);
						getch();

					} else if (auxMG == 5) {

						excluirFilme(&I);
						getch();

					} else if (auxMG == 6) {

						consultaFilmes(I);
						getch();

					}


				} while (auxMG != 7);
			}

		} while (opcao != 3);


		salvarED(I);
		salvarArquivos(L);
		
	} while (0);

}

int main() {

	setlocale(LC_ALL, "ptb");
	menu();
	getch();

}
