/*
    Marcello Alves
    Exercicio sobre strings e ordenação.
    Todos os direitos reservados.
*/
//Inclusão das bibliotecas.
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <time.h>
//Definição de variaveis globais.
#define TotalI 101
int I = 0, Cadastrados = 0;
//Definindo o contato.
struct Contato{

    char Nome[20];
    char Telefone[12];
    char Email[20];
    char Data[11];
    int ID;

} X[TotalI];
//Prototipo todas as funções do programa.
//Em ordem na qual aparece no codigo ;)
void Tela();
void Menu();
void Cadastro();
void ZeraID();
void Listagem();
void OrdenaNome();
void OrdenaTelefone();
void OrdenaEmail();
void OrdenaData();
void ProcuraContato();
void RemoveContato();
void Inicial();
void Info();

//Definindo Função que limpa a tela e apresenta o menu.
void Tela(){
    system ("cls");
    printf ("\n\n\t\t----------------------- AGENDA ELETRONICA -----------------------\n");
    printf ("\t\tDigite um dos comando para prosseguir:\n");
    printf ("\t\tC – Para cadastrar um contato na agenda.\n");
    printf ("\t\tL – Para listar todos os contatos já cadastrados na agenda.\n");
    printf ("\t\tP – Procurar um contato na agenda pelo nome.\n");
    printf ("\t\tR – Remover um contato da agenda pelo nome.\n");
    printf ("\t\tE – Exibir todos os contatos que começam com uma letra.\n");
    printf ("\t\tI – Tela com informações sobre a agenda.\n");
    printf ("\t\tS – Sair da agenda eletrônica.\n");
    printf ("\t\t–---------------------------------------------------------------- \n");
    printf ("\n\t\tComando: ");

}
//função na qual verifica qual o comando que o usuario
//inseriu e faz chamada as respectivas funcoes.
void Menu(){

    char Opcao;

    do {
            Tela();
            scanf(" %c", &Opcao);
            fflush(stdin);
            if (Opcao == 'C'){
                Cadastro();
            }
            if (Opcao == 'L'){
                Listagem();
            }
            if (Opcao == 'P'){
                ProcuraContato();
            }
            if (Opcao == 'R'){
                RemoveContato();
            }
            if (Opcao == 'E'){
                Inicial();
            }
            if (Opcao == 'I'){
                Info();
            }


    } while (Opcao != 'S');

}
//Função para cadastro
void Cadastro(){
        system ("cls");
        printf ("\n\n\t\t----------------------- AGENDA ELETRONICA -----------------------\n");
        printf ("\t\tCadastro:\n");
        printf ("\t\tInsira o nome: ");
        gets(X[I].Nome);
        fflush(stdin);
        printf ("\t\tInsira o telefone: ");
        gets (X[I].Telefone);
        fflush(stdin);
        printf ("\t\tInsira o email: ");
        gets (X[I].Email);
        fflush(stdin);
        printf ("\t\tInsira a data de nascimento: ");
        gets (X[I].Data);
        fflush(stdin);

        int i, Cont = 0;
        for (i = 0; i < TotalI; i++){
            if (strcmp(X[I].Nome, X[i].Nome) == 0 && I != i){
                Cont++;
            }
        }

        if (Cont == 0){
            printf("\n\n\t\tContato cadastrado com sucesso.\n");
            X[I].ID = 1;
            I++;
        } else {
            printf("\n\n\t\tContato já existe, não foi possivel inseri-lo.\n");
            strcpy(X[I].Nome, "");
            strcpy(X[I].Email, "");
            strcpy(X[I].Telefone, "");
            strcpy(X[I].Data, "");
            X[I].ID = 0;
        }
        getch();

}
//Função na qual zera os ID.
void ZeraID(){

    int i;
    for (i = 0; i < TotalI; i++){
        X[i].ID = 0;
    }

}
//Função que lista todos os contatos já cadastrados na agenda.
void Listagem(){
    int i;
    char Opcao;
        do {
        system ("cls");
        printf ("\n\n\t\t----------------------- AGENDA ELETRONICA -----------------------\n");
        printf ("\t\tListagem de contatos:\n");
        printf ("\t\tN - Nome.\n");
        printf ("\t\tT – Telefone.\n");
        printf ("\t\tE - Email.\n");
        printf ("\t\tD - Data de nascimento.\n");
        printf ("\t\tOpcao: ");
        scanf(" %c", &Opcao);
        fflush(stdin);
        } while (Opcao != 'N' && Opcao != 'T' && Opcao != 'E' && Opcao != 'D');

        if (Opcao == 'N'){
            OrdenaNome();
        }
        if (Opcao == 'T'){
            OrdenaTelefone();
        }
        if (Opcao == 'E'){
            OrdenaEmail();
        }
        if (Opcao == 'D'){
            OrdenaData();
        }

        for (i = 0; i < TotalI; i++){
            if (X[i].ID == 1){

                printf ("\n\n\t\tNome: %s", X[i].Nome);
                printf ("\n\t\tTelefone: %s", X[i].Telefone);
                printf ("\n\t\tEmail: %s", X[i].Email);
                printf ("\n\t\tData de nascimento: %s", X[i].Data);
            }
        }
        getch();
}
//Função ordena por nome
void OrdenaNome(){

    int i, k;
    char Aux[20];

    for (i = 0; i < TotalI; i++){

        for (k = i + 1; k < TotalI; k++){

            if (strcmp(X[i].Nome, X[k].Nome) > 0){

                X[101] = X[i];
                X[i] = X[k];
                X[k] = X[101];

            }
        }
    }
}
//Função ordena por telefone
void OrdenaTelefone(){

    int i, k;
    char Aux[20];

    for (i = 0; i < TotalI; i++){

        for (k = i + 1; k < TotalI; k++){

            if (strcmp(X[i].Telefone, X[k].Telefone) > 0){

                X[101] = X[i];
                X[i] = X[k];
                X[k] = X[101];

            }
        }
    }
}
//Função ordena por email
void OrdenaEmail(){

    int i, k;
    char Aux[20];

    for (i = 0; i < TotalI; i++){

        for (k = i + 1; k < TotalI; k++){

            if (strcmp(X[i].Email, X[k].Email) > 0){

                X[101] = X[i];
                X[i] = X[k];
                X[k] = X[101];

            }
        }
    }
}
//Função ordena por data de nascimento.
void OrdenaData(){

    int i, k;
    char Aux[20];

    for (i = 0; i < TotalI; i++){

        for (k = i + 1; k < TotalI; k++){

            if (strcmp(X[i].Data, X[k].Data) > 0){

                X[101] = X[i];
                X[i] = X[k];
                X[k] = X[101];

            }
        }
    }
}
//Função para procurar um contato a partir do nome fornecido.
void ProcuraContato(){

        char Pesq[20];
        int i, Aux = -1;
        system ("cls");
        printf ("\n\n\t\t----------------------- AGENDA ELETRONICA -----------------------\n");
        printf ("\t\tProcura de contatos:\n");
        printf ("\t\tInsira nome para pesquisa: ");
        scanf (" %s", &Pesq);
        for (i = 0; i < TotalI; i++){
            if (strcmp(Pesq, X[i].Nome) == 0){
                Aux = i;
            }
        }
        if (Aux == -1){
            printf ("\n\n\t\tNão foi possível encontrar este contato.");
        } else {
            printf ("\n\n\t\tNome: %s", X[Aux].Nome);
            printf ("\n\t\tTelefone: %s", X[Aux].Telefone);
            printf ("\n\t\tEmail: %s", X[Aux].Email);
            printf ("\n\t\tData: %s", X[Aux].Data);
        }
        getch();
}
//função na qual remove contato
void RemoveContato(){

        char RC[20];
        int i, Aux = -1;
        system ("cls");
        printf ("\n\n\t\t----------------------- AGENDA ELETRONICA -----------------------\n");
        printf ("\t\tRemoção de contatos:\n");
        printf ("\t\tInsira o nome para remoção: ");
        scanf (" %s", &RC);
        fflush(stdin);

        for (i = 0; i < TotalI; i++){

            if (strcmp(RC, X[i].Nome) == 0){
                    Aux = i;
            }
        }

        if (Aux == -1){
            printf ("\n\n\t\tNão foi possivel encontrar este contato.");
        } else{

            strcpy(X[Aux].Nome, "");
            strcpy(X[Aux].Email, "");
            strcpy(X[Aux].Telefone, "");
            strcpy(X[Aux].Data, "");
            X[Aux].ID = 0;
            OrdenaNome();
            I--;
            printf ("\n\n\t\tRemoção do contato com sucesso.");
        }
        getch();

}

//Função que que exibe os contatos de acordo com a letra inicial.
void Inicial(){

        char CP;
        int i;
        system ("cls");
        printf ("\n\n\t\t----------------------- AGENDA ELETRONICA -----------------------\n");
        printf ("\t\tContatos com a inicial: \n");
        printf ("\t\tInsira a letra inicial: ");
        scanf (" %c", &CP);

        for (i = 0; i < TotalI; i++){

            if (X[i].Nome[0] == CP){

                    printf ("\n\n\t\tNome: %s", X[i].Nome);
                    printf ("\n\t\tTelefone: %s", X[i].Telefone);
                    printf ("\n\t\tEmail: %s", X[i].Email);
                    printf ("\n\t\tData: %s", X[i].Data);

            }
        }
        getch();
}
//função que verifica a quantidade de usuarios cadastrados
void Info(){

    int i;
    Cadastrados = 0;

    for (i = 0; i < TotalI; i++){

        if (X[i].ID == 1){
            Cadastrados++;
        }
    }
    system ("cls");
    printf ("\n\n\t\t----------------------- AGENDA ELETRONICA -----------------------\n");
    printf ("\t\tInformações:\n");
    printf ("\n\t\t-------------------------------------");
    printf ("\n\t\tTotal de Contatos Inseridos: %d", Cadastrados);
    printf ("\n\t\tTotal de Posições Restantes: %d", 100 - Cadastrados);
    printf ("\n\t\t-------------------------------------");

    getch();

}
int main (){

    setlocale(LC_ALL,"ptb");
    ZeraID();
    Menu();
    getch();
}
