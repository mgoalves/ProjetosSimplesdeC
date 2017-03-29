#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>

typedef struct Aluno{
	
	char Nome[20];
	float N1;
	float N2;
	float N3;
	float N4;
	float Media;
	
}Aluno;

//Chamada de funções
int QuantidadeAlunos();
void CadastraAlunos(Aluno *X, int QC);
void Ordena(Aluno *X, int QC);
void Imprime (Aluno *X, int QC);


int QuantidadeAlunos (){
	
	int QAlunos;
	
	printf ("\n\n\t\t\tGerenciamento de Notas.");
	printf ("\n\n\n\t\tInforme a quantidade de alunos: ");
	scanf ("%d", &QAlunos);
	system ("cls");
	
	return QAlunos;
	
}

void CadastraAlunos(Aluno *X, int QC){
	
	int i;
	int MAX = QC;
	
	for (i = 0; i < MAX; i++){
		
			printf ("\n\n\t\t%dº Aluno: ", i + 1);	
			scanf (" %[^\n]s", X[i].Nome);
			fflush (stdin);
			printf ("\n\t\tNota 1: ");
			scanf (" %f", &X[i].N1);
			fflush (stdin);
			printf ("\n\t\tNota 2: ");
			scanf (" %f", &X[i].N2);
			fflush (stdin);
			printf ("\n\t\tNota 3: ");
			scanf (" %f", &X[i].N3);
			fflush (stdin);
			printf ("\n\t\tNota 4: ");
			scanf (" %f", &X[i].N4);
			fflush (stdin);
		
			X[i].Media = (X[i].N1 + X[i].N2 + X[i].N3 + X[i].N4) / 4;
	}
}

void Ordena(Aluno *X, int QC){
	
	int i, k; 
	int MAX = QC;
	Aluno Aux;
	
	
	
	for (i = 0; i < MAX; i++){
		
		for (k = (i + 1); k < MAX; k++){
			
			if (strcmp(X[k].Nome, X[i].Nome) < 0){
				
				Aux = X[k];
				X[k] = X[i];
				X[i] = Aux;				
			}
			
			
		}
	}
}

void Imprime (Aluno *X, int QC){
	
	int i;
	int MAX = QC;
	
	system ("cls");
	printf ("\n\n\t\t\tRelacao de alunos e suas respectivas notas.\n\n");
	
	for (i = 0; i < MAX; i++){

		printf ("\n\n\t\t%dº Aluno: %s", i + 1, X[i].Nome);
		printf ("\n\t\tMedia: %.2f", X[i].Media);

	}	

	printf ("\n\n\n\t\tObrigado por utilizar nosso programa.");
}

int main (){
	
	int QC = QuantidadeAlunos();
	
	Aluno *X;
	X = malloc (QC * sizeof (Aluno));
	
	CadastraAlunos (X, QC);
	Ordena(X, QC);
	Imprime (X, QC);
	
	free (X);

	
	getch();
}
