/*
	Aluno: Marcello Alves.
	Programção imperativa.
	Prova 2.

*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define Z 100

//Fução que limpa a tela e printa o sistema.
void LimpaTela (){
	system ("cls");
	printf ("\n\n\t\t\tSistema para cadastro de usuario\n\n");
}
//Criação dos tipos estruturas.
typedef struct{

    int Gestante;
    int M45;
    int TDS;
    int PDDCNT;
    int C6;
    int Indio;
    int NaoRisco;

} Enumeracao;

typedef struct {

    char Nome[40];
    char CPF[12];
    int Idade;
    char Genero;
    char Cidade[15];
    char Estado[3];
    char Vacinada;
    Enumeracao GrupoDeRisco;

} Pessoa;

typedef struct {

    int A;
    int B;
    int C;
    int D;
    int E;
    int F;
    int H;

} Vacinadas;

//função prencher dados
Pessoa LerDados(Pessoa X){

    Pessoa C = X;
    LimpaTela();
    int OP;

    printf ("\n\tInsira o nome: ");
    scanf (" %s", &C.Nome);
    printf ("\n\tInsira o CPF: ");
    scanf (" %s", &C.CPF);
    printf ("\n\tInsira a idade: ");
    scanf (" %d", &C.Idade);
    printf ("\n\tInsira o genero(F/M): ");
    scanf (" %c", &C.Genero);
    printf ("\n\tInsira a cidade: ");
    scanf (" %s", &C.Cidade);
    printf ("\n\tInsira o UF do estado: ");
    scanf (" %s", &C.Estado);
    printf ("\n\tEsta vacinada (S/N): ");
    scanf (" %c", &C.Vacinada);

    LimpaTela();
    printf ("\n\tEm qual dos grupos a seguir o paciente esta: \n");
    printf ("\n\t1. Gestante\n");
    printf ("\n\t2. Maes  com ate 45 dias apos o parto\n");
    printf ("\n\t3. Trabalhadores de Saude\n");
    printf ("\n\t4. Portadoras de doencas cronicas nao transmissiveis\n");
    printf ("\n\t5. Criancas de 6 meses ate 5 anos\n");
    printf ("\n\t6. Indigenas\n");
    printf ("\n\t7. Nenhum grupo de risco\n");
    printf ("\n\tOpcao: ");
    scanf (" %d", &OP);

        if (OP == 1){
            C.GrupoDeRisco.Gestante++;
        }
        if (OP == 2){
            C.GrupoDeRisco.M45++;
        }
        if (OP == 3){
            C.GrupoDeRisco.TDS++;
        }
        if (OP == 4){
            C.GrupoDeRisco.PDDCNT++;
        }
        if (OP == 5){
            C.GrupoDeRisco.C6++;
        }
        if (OP == 6){
            C.GrupoDeRisco.Indio++;
        }
        if (OP == 7){
            C.GrupoDeRisco.NaoRisco++;
        }

        return C;
}

// Função Zera Contador
Pessoa ZeraContador (Pessoa X){

    Pessoa C = X;
    LimpaTela();
    C.GrupoDeRisco.Gestante = C.GrupoDeRisco.M45 = C.GrupoDeRisco.TDS = 0;
    C.GrupoDeRisco.PDDCNT = C.GrupoDeRisco.C6 = C.GrupoDeRisco.Indio = 0;
    C.GrupoDeRisco.NaoRisco = 0;

    return C;
}
//Zera o contadodor total de pessoas vacinadas ou nao
Vacinadas Zera(Vacinadas Y){

    Vacinadas C = Y;

    C.A = C.B = C.C = C.D = C.E = C.F = C.H = 0;

    return C;

}

//Função que conta o total de pessoas vacinadas.
Vacinadas ContadorV (Vacinadas Y, Pessoa X){

    Vacinadas C = Y;

    if (X.Vacinada == 'S' && X.GrupoDeRisco.Gestante != 0){
        C.A++;
    }
    if (X.Vacinada == 'S' && X.GrupoDeRisco.M45 != 0){
        C.B++;
    }
    if (X.Vacinada == 'S' && X.GrupoDeRisco.TDS != 0){
        C.C++;
    }
    if (X.Vacinada == 'S' && X.GrupoDeRisco.PDDCNT != 0){
        C.D++;
    }
    if (X.Vacinada == 'S' && X.GrupoDeRisco.C6 != 0){
        C.E++;
    }
    if (X.Vacinada == 'S' && X.GrupoDeRisco.Indio != 0){
        C.F++;
    }
    if (X.Vacinada == 'S' && X.GrupoDeRisco.NaoRisco != 0){
        C.H++;
    }
    return C;
}
//Função que conta o total de  NAO pessoas vacinadas.

Vacinadas ContadorNV(Vacinadas N, Pessoa P){

    Vacinadas C = N;
    Pessoa X = P;


    if (X.Vacinada == 'N' && X.GrupoDeRisco.Gestante != 0){
        C.A++;
    }
    if (X.Vacinada == 'N' && X.GrupoDeRisco.M45 != 0){
        C.B++;
    }
    if (X.Vacinada == 'N' && X.GrupoDeRisco.TDS != 0){
        C.C++;
    }
    if (X.Vacinada == 'N' && X.GrupoDeRisco.PDDCNT != 0){
        C.D++;
    }
    if (X.Vacinada == 'N' && X.GrupoDeRisco.C6 != 0){
        C.E++;
    }
    if (X.Vacinada == 'N' && X.GrupoDeRisco.Indio != 0){
        C.F++;
    }
    if (X.Vacinada == 'N' && X.GrupoDeRisco.NaoRisco != 0){
        C.H++;
    }
    return C;
}
//Função que imprime o Resultado Final de pessoas Vacinadas por grupo

void ImprimeFim(Vacinadas J, Vacinadas K){

    Vacinadas Y = J;
    Vacinadas N = K;

    LimpaTela();
    printf ("\n\tGestantes vacinadas: %d\n", Y.A);
    printf ("\n\tGestantes nao vacinadas: %d\n", N.A);
    printf ("\n\tMaes com ate 45 dias vacinadas: %d\n", Y.B);
    printf ("\n\tMaes com ate 45 dias nao vacinadas: %d\n", N.B);
    printf ("\n\tTrabalhadores da saude vacinados: %d\n", Y.C);
    printf ("\n\tTrabalhadores da saude nao vacinados: %d\n", N.C);
    printf ("\n\tPortadodes de doencas cronicas vacinados: %d\n", Y.D);
    printf ("\n\tPortadodes de doencas cronicas nao vacinados: %d\n", N.D);
    printf ("\n\tCriancas vacinados: %d\n", Y.E);
    printf ("\n\tCriancas nao vacinados: %d\n", N.E);
    printf ("\n\tIndigenas vacinados: %d\n", Y.F);
    printf ("\n\tIndigenas nao vacinados: %d\n", N.F);
    printf ("\n\tNenhum grupo de risco vacinados: %d\n", Y.H);
    printf ("\n\tNenhum grupo de risco nao vacinados: %d\n", N.H);

    getch();

    system ("cls");

}

//Função Recursiva
int DiasR (int I, int N){

    if (I < N){
        return DiasR;
    } else {

        return DiasR(I*(I + 3), N - I);
    }
}


// função principal
int main (){

    Pessoa X;
    Vacinadas Y, N;
    int i, A, B, Dias;
    LimpaTela();
    Y = Zera(Y);
    N = Zera(N);

    for (i = 0; i < Z; i++){
        X = ZeraContador(X);
        X = LerDados(X);
        Y = ContadorV (Y, X);
        N = ContadorNV (N, X);

    }
    ImprimeFim(Y, N);
    printf ("\n\n\n\tFuncao pela qual calcula os dias.\n\n");
    printf ("\n\tInsira a quantidade de pessoas infectadas: ");
    scanf(" %d", &A);
    printf ("\n\tInsira a quantidade de nao pessoas infectadas: ");
    scanf(" %d", &B);
    Dias = DiasR(A, B);
    printf ("\n\tDias ate a contaminacao completa: %d\n", Dias);
    getch();

}
