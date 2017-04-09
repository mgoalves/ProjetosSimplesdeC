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
	char login[10];
	char senha[10];

} pessoa;

typedef struct {

	char titulo[30];
	short editora;
	char autor[30];
	char areaC[30];
	short quantidade;
	short disponiveis;

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
	short sitMatr; // 1 - Ativa 2 - Bloqueada 3 - Debito
	char turma;
	endereco end;
	telefone tel;

} aluno;

typedef struct {

	short idAdm; // 1-funcionario 2-administrador
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

} funcEST;

typedef struct {

	aluno A[qAlunos];
	int Prim, Ult;

} alunoEST;

typedef struct {

	editora ED[qEditoras];
	int Prim, Ult;

} editEST;

typedef struct {

	emprestimo E[qEmprestimos];
	int Prim, Ult;

} empEST;

typedef struct {

	livro L[qLivros];
	int Prim, Ult;

} livroEST;


//Protopatipação de Funções na ordem em que esão dispostas no decorrer do codigo

void editarLivro(livroEST L);
void cadastrarLivro(livroEST *L, editEST ED);
void consultarLivro(livroEST L, editEST ED);
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

int verificarListaVaziaFunc (funcEST F) {
	return(F.Prim == F.Ult); // Quando Prim for igual a Ult a lista está vazia
}
int verificarListaVaziaAlun (alunoEST A) {
	return(A.Prim == A.Ult); // Quando Prim for igual a Ult a lista está vazia
}
int verificarListaVaziaEdit (editEST ED) {
	return(ED.Prim == ED.Ult); // Quando Prim for igual a Ult a lista está vazia
}
int verificarListaVaziaLivro (livroEST L) {
	return(L.Prim == L.Ult); // Quando Prim for igual a Ult a lista está vazia
}
int verificarListaVaziaEmp (empEST E) {
	return(E.Prim == E.Ult); // Quando Prim for igual a Ult a lista está vazia
}

int verificarListaCheiaFunc (funcEST F) {
	return(F.Ult == qFunc); // Quando Ult apontar para a posição Max a lista está cheia
}
int verificarListaCheiaAluno (alunoEST A) {
	return(A.Ult == qAlunos); // Quando Ult apontar para a posição Max a lista está cheia
}
int verificarListaCheiaEdit (editEST ED) {
	return(ED.Ult == qEditoras); // Quando Ult apontar para a posição Max a lista está cheia
}
int verificarListaCheiaLivro (livroEST L) {
	return(L.Ult == qLivros); // Quando Ult apontar para a posição Max a lista está cheia
}
int verificarListaCheiaEmp (empEST E) {
	return(E.Ult == qEmprestimos); // Quando Ult apontar para a posição Max a lista está cheia
}





void editarLivro(livroEST L){ //Criar excessão quando já houver um exemplar emprestado.
	
	int i; short aux = - 1; char saida = 'n'; livro X;
	char livro[30];

	
	do {
			
		system("cls");
		printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
		printf("\n\tSub Menu -> Livros -> Editar Livros");
		printf("\n\tInsira o titulo para buscar: ");
		scanf(" %[^\n]", &livro);
		fflush(stdin);
	
		for (i = 0; i < qLivros; i++) {
		
			if (strcmp(L.L[i].titulo,livro) == 0) {
				aux = i;
			
			}
		}
		
		if (aux == -1) {
		
			do{
		
				system("cls");
				printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
				printf("\n\tSub Menu -> Livros -> Editar Livros");
		
				printf("\n\n\tDesculpe, não foi possivel encontrar este livro em nossa base de dados.");
				printf("\n\n\tDeseja fazer uma nova busca?");
				printf("\n\tS - Sim, ótima ideia!");
				printf("\n\tN - Não, obrigado.");
				scanf(" %c", &saida);
			
			} while (saida != 'n' && saida != 'N' && saida != 's' && saida != 'S');
		
		} else {
		
			system("cls");
			printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
			printf("\n\tSub Menu -> Livros -> Editar Livros");		
			printf("\n\tLivro '%s'encotrado: ", livro);
			
			printf("\n\n\tNovo Titulo: ");
			gets(X.titulo);
			fflush(stdin);
			
			printf("\n\tNova area de conhecimento: ");
			gets(X.areaC);
			fflush(stdin);
			
			printf("\n\tNovo Autor: ");
			gets(X.autor);
			fflush(stdin);
			
			printf("\n\tNova Quantidade de exemplares: ");
			scanf(" %d", X.quantidade);
			X.disponiveis = X.quantidade;
			fflush(stdin);
		
			L.L[aux] = X;
		
			printf("\n\n\tDados salvos com sucesso.");
		
		}
		
		
	} while (saida != 'n' && saida != 'N');//Fim do cod
	
	getch();
	
}

void cadastrarLivro(livroEST *L, editEST ED){
	
	int A, P = L -> Prim;
	livro X; short codED, i, aux = 1;
	char saida = 'n';
	
	do {
		
		aux = 1;
		printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
		printf("\n\tSub Menu -> Livros -> Cadastro de Livros");
		
		printf("\n\n\tInsira o codigo da editora: ");
		scanf(" %d", &codED);
		fflush(stdin);
		
		for (i = 0;i < qEditoras; i++) {
			
			if (ED.ED[i].id == codED) {
				
				printf("\n\tEditora '%s' foi encontrada!", ED.ED[i].nome);
				aux = 2;
				
			}
			
			
		}
		
		if (aux == 1){
			
			do {
				
				system("cls");
				printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
				printf("\n\tSub Menu -> Livros -> Cadastro de Livros");
		
				printf("\n\n\tDesculpe, não foi possivel encontrar esta editora");
				printf("\n\n\tDeseja fazer uma nova busca?");
				printf("\n\tS - Sim, ótima ideia!");
				printf("\n\tN - Não, obrigado.");
				scanf(" %c", &saida);
				
				
			} while (saida != 'n' && saida != 'N' && saida != 's' && saida != 'S');
			
			
		} else if (aux == 2) {
			
			printf("\n\n\tTitulo: ");
			gets(X.titulo);
			fflush(stdin);
			
			printf("\n\tArea de conhecimento: ");
			gets(X.areaC);
			fflush(stdin);
			
			printf("\n\tAutor: ");
			gets(X.autor);
			fflush(stdin);
			
			printf("\n\tQuantidade de exemplares: ");
			scanf(" %d", X.quantidade);
			X.disponiveis = X.quantidade;
			X.editora = codED;
			fflush(stdin);
			
			if (verificarListaCheiaLivro(*L)) {

				printf("\n\n\tA lista está cheia logo não foi possível adicionar um novo item.");

			} else {
				while ((P < L -> Ult))
					P++;
	
				if(P == L-> Ult) {
	
					L -> L[P] = X;
					L -> Ult ++;

				} else {

					for(A = L-> Ult; A > P; A--)
						L -> L[A] = L -> L[A-1];
					L -> L[P] = X;
					L -> Ult++;
				}
			}
			
		} // Fim do else if == 2
		
		
	} while (saida != 'n' && saida != 'N');

	
}

void consultarLivro(livroEST L, editEST ED) {
	
	char livro[20]; int i; short aux = -1; char saida = 'n';
	
	do {
	
	
	system("cls");
	printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
	printf("\n\tSub Menu -> Livros -> Consultar Livros");
	printf("\n\tInsira o nome para buscar: ");
	scanf(" %[^\n]", &livro);
	fflush(stdin);
	
	for (i = 0; i < qLivros; i++) {
		
		if (strcmp(L.L[i].titulo,livro) == 0) {
			
			aux = i;
			
		}
		
	}
	
		
		
		//Comparação de ID para exibir na tela.
		if (aux == -1) {
		
			do{
		
				system("cls");
				printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
				printf("\n\tSub Menu -> Livros -> Consultar Livros");
		
				printf("\n\n\tDesculpe, não foi possivel encontrar este livro em nossa base de dados.");
				printf("\n\n\tDeseja fazer uma nova busca?");
				printf("\n\tS - Sim, ótima ideia!");
				printf("\n\tN - Não, obrigado.");
				scanf(" %c", &saida);
			
			} while (saida != 'n' && saida != 'N' && saida != 's' && saida != 'S');
		
		} else {
		
					
			printf("\n\n\tLivro '%s'encotrado: ", livro);
		
		
			//Comparação de ID para exibir na tela.
			for (i = 0; i < qEditoras; i++) {
		
				if (ED.ED[i].id == L.L[aux].editora) {
					printf("\n\tEditora:              %s", ED.ED[i].nome);
			
				}
			}
		
			printf("\n\tNome do autor:         %s", L.L[aux].autor);
			printf("\n\tArea de conhecimento:  %s", L.L[aux].areaC);
			printf("\n\tQuantidade de livros:  %d", L.L[aux].quantidade);
			printf("\n\tQuantidade disponivel: %d", L.L[aux].disponiveis);
			getch();
				
		
		}
	
	
	
	} while (saida != 'n' && saida != 'N');	 
	
}


void menu () {

	do { //Responsável por terminar o programa

		funcEST F;
		alunoEST A;
		editEST ED;
		livroEST L;
		empEST E;

		criarListaFunc(&F);
		criarListaAluno(&A);
		criarListaEditora(&ED);
		criarListaLivro(&L);
		criarListaEmp(&E);

		
		
		strcpy(F.F[5].func.login,"adm");
		strcpy(F.F[5].func.senha,"123");
		F.F[5].idAdm = 2;
		
		//carregarArquivosFunc(&F);
		//carregarArquivosAluno(&A);
		//carregarArquivosEdit(&ED);
		//carregarArquivosLivro(&L);
		//carregarArquivosEmp(&E);

		printf ("\n\n\tRecomendamos que use a tela em tamanho máximo para mais conforto.");
		sleep(3);

		short loginS = 0;
		int i; //Usado para os laços de repetição sem comprometimento e necessidade posterior de
		//uma posição qualquer da contagem
		do {
			
			system ("cls");
			printf ("\n\t\t\tLOGIN\n\n\n");
			printf("\n\t1 - Funcionário");
			printf("\n\t2 - Aluno");
			printf("\n\t3 - Sair");
			printf("\n\tOpcão: ");
			scanf("%d", &loginS);
			fflush(stdin);

			short saidaLogin = 0;
			char loginErro = 0;
			short menuP = 0;
			short menuS = 0;
			char login[10], senha[10];
			short aux = 0;

			if (loginS == 1) {

				do { //Checar Login de funcionario e gerente
					saidaLogin = 0;

					system("cls");
					printf ("\n\t\t\tLOGIN\n\n\n");
					printf ("\n\tUser: ");
					scanf ("%s", &login);
					fflush(stdin);
					printf("\n\tSenha: ");
					scanf ("%s", &senha);
					fflush(stdin);

					for (i = 0; i < 50; i++) {

						if (strcmp(F.F[i].func.login,login) == 0 && strcmp(F.F[i].func.senha,senha) == 0 &&
						        F.F[i].idAdm == 1) {

							printf ("\n\n\tLogin realizado com sucesso!");
							saidaLogin = 1;

						}

						if (strcmp(F.F[i].func.login,login) == 0 && strcmp(F.F[i].func.senha,senha) == 0 &&
						        F.F[i].idAdm == 2) {

							printf ("\n\n\tLogin realizado com sucesso!");
							saidaLogin = 3;

						}

					}

					if (saidaLogin == 0) {

						aux = 0;
						do {

							system ("cls");
							printf ("\n\t\t\tLOGIN\n\n\n");
							printf ("\n\n\tSenha e/ou usuário está(ão) errado(s).");
							printf("\n\tDeseja tentar novamente?");
							printf("\n\tS - Sim, parece ótimo.");
							printf("\n\tN - Não, sair.");
							printf("\n\tOpção: ");
							scanf ("%c", &loginErro);

							if (loginErro == 's' || loginErro =='S') {

								aux = 1;

							} else if (loginErro == 'n' || loginErro =='N') {

								aux = 2;
								saidaLogin = 2;

							}


						} while(aux != 1 && aux != 2);

					}


				} while (saidaLogin != 1 && saidaLogin != 2 && saidaLogin != 3);


				if (saidaLogin == 1) { //Menu para Funcionario comum ----------------------------------------------


					do {

						system("cls");
						printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");

						printf("\n\tSub Menus: ");
						printf("\n\t1 - Livros");
						printf("\n\t2 - Editoras");
						printf("\n\t3 - Alunos");
						printf("\n\t4 - Emprestimos e Devoluções");
						printf("\n\t5 - Relatórios");
						printf("\n\t6 - Sair");
						printf("\n\tOpcão: ");
						scanf("%d", &menuP);
						fflush(stdin);
						menuS = 0;

						if (menuP == 1) {
							menuS = 0;
							do {

								system("cls");
								printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
								printf("\n\tSub Menu -> Livros");

								printf("\n\t1 - Consultar Livro");
								printf("\n\t2 - Cadastrar Livro");
								printf("\n\t3 - Editar Livro");
								printf("\n\t4 - Excluir Livro");
								printf("\n\t5 - Livros com maior procura");
								printf("\n\t6 - Livros com menor procura");
								printf("\n\t7 - Sair");
								printf("\n\tOpcão: ");
								scanf("%d", &menuS);
								fflush(stdin);

								if(menuS == 1) {
									
									consultarLivro(L, ED);

								} else if (menuS == 2) {
									
									cadastrarLivro(&L, ED);

								} else if (menuS == 3) {
									
									editarLivro(L);

								} else if (menuS == 4) {

								} else if (menuS == 5) {

								} else if (menuS == 6) {

								}


							} while (menuS != 7);

						} else if (menuP == 2) { 
							menuS = 0;
							do {

								system("cls");
								printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
								printf("\n\tSub Menu -> Editoras");

								printf("\n\t1 - Consultar Editora");
								printf("\n\t2 - Cadastrar Editora");
								printf("\n\t3 - Editar Editora");
								printf("\n\t4 - Excluir Editora");
								printf("\n\t5 - Sair");
								printf("\n\tOpcão: ");
								scanf("%d", &menuS);
								fflush(stdin);

								if(menuS == 1) {

								} else if (menuS == 2) {

								} else if (menuS == 3) {

								} else if (menuS == 4) {

								}

							} while (menuS != 5);

						} else if (menuP == 3) {
							menuS = 0;
							do {

								system("cls");
								printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
								printf("\n\tSub Menu -> Alunos");


								printf("\n\t1 - Consultar Aluno");
								printf("\n\t2 - Editar Aluno");
								printf("\n\t3 - Cadastrar Aluno");
								printf("\n\t4 - Bloquear Aluno");
								printf("\n\t5 - Desbloquear Aluno");
								printf("\n\t6 - Sair");
								printf("\n\tOpcão: ");
								scanf("%d", &menuS);
								fflush(stdin);

								if(menuS == 1) {

								} else if (menuS == 2) {

								} else if (menuS == 3) {

								} else if (menuS == 4) {

								} else if (menuS == 5) {

								}

							} while (menuS != 6);

						} else if (menuP == 4) {
							menuS = 0;
							do {

								system("cls");
								printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
								printf("\n\tSub Menu -> Emprestimos");

								printf("\n\t1 - Consultar Emprestimo");
								printf("\n\t2 - Realizar Emprestimo");
								printf("\n\t3 - Prorrogar Emprestimo");
								printf("\n\t4 - Efetuar Devolução");
								printf("\n\t5 - Baixa de alunos com debito");
								printf("\n\t6 - Sair");
								printf("\n\tOpcão: ");
								scanf("%d", &menuS);
								fflush(stdin);

								if(menuS == 1) {

								} else if (menuS == 2) {

								} else if (menuS == 3) {

								} else if (menuS == 4) {

								} else if (menuS == 5) {

								}

							} while (menuS != 6);

						} else if (menuP == 5) {
							menuS = 0;
							do {

								system("cls");
								printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
								printf("\n\tSub Menu -> Relatórios");

								printf("\n\t1 - Alunos ativos");
								printf("\n\t2 - Alunos bloquados");
								printf("\n\t5 - Alunos com debito.");
								printf("\n\t3 - Livros Diponíveis");
								printf("\n\t4 - Livros Indisponíveis");
								printf("\n\t5 - Editoras cadastradas");
							    printf("\n\t6 - Sair");
      					        printf("\n\tOpcão: ");
								scanf("%d", &menuS);
						        fflush(stdin);

								   if(menuS == 1) {

							       } else if (menuS == 2){

							       } else if (menuS == 3) {

							       } else if (menuS == 4) {

							       } else if (menuS == 5) {

							       }

							} while (menuS != 6);

						}

					} while (menuP != 6);

			    } else if (saidaLogin == 3) { //Menu Para Gerente -------------------------------------------------

					do {

						system("cls");
						printf ("\n\t\t\tMENU GERENTE\n\n\n");

      					printf("\n\tSub Menus: ");
						printf("\n\t1 - Livros");
						printf("\n\t2 - Editoras");
						printf("\n\t3 - Alunos");
						printf("\n\t4 - Emprestimos e Devoluções");
						printf("\n\t5 - Relatórios");
						printf("\n\t6 - Funcionarios");
						printf("\n\t7 - Sair");
     					printf("\n\tOpcão: ");
						scanf("%d", &menuP);
						fflush(stdin);
						menuS = 0;

						if (menuP == 1) {
							
							menuS = 0;
							do {

							    system("cls");
							    printf ("\n\t\t\tMENU GERENTE\n\n\n");
							    printf("\n\tSub Menu -> Livros");

							    printf("\n\t1 - Consultar Livro");
							    printf("\n\t2 - Cadastrar Livro");
							    printf("\n\t3 - Editar Livro");
							    printf("\n\t4 - Excluir Livro");
							    printf("\n\t5 - Livros com maior procura");
							    printf("\n\t6 - Livros com menor procura");
							    printf("\n\t7 - Sair");
       							printf("\n\tOpcão: ");
								scanf("%d", &menuS);
								fflush(stdin);

								if(menuS == 1) {

							    } else if (menuS == 2){

							    } else if (menuS == 3) {

							    } else if (menuS == 4) {

							    } else if (menuS == 5) {

							    } else if (menuS == 6) {

							    }

						 } while (menuS != 7);


					} else if (menuP == 2) {
						
							menuS = 0;
							do {

							    system("cls");
							    printf ("\n\t\t\tMENU GERENTE\n\n\n");
							    printf("\n\tSub Menu -> Editoras");

							    printf("\n\t1 - Consultar Editora");
							    printf("\n\t2 - Cadastrar Editora");
							    printf("\n\t3 - Editar Editora");
							    printf("\n\t4 - Excluir Editora");
							    printf("\n\t5 - Sair");
       							printf("\n\tOpcão: ");
								scanf("%d", &menuS);
								fflush(stdin);

								if(menuS == 1) {

							    } else if (menuS == 2){

							    } else if (menuS == 3) {

							    } else if (menuS == 4) {

							    }

							    } while (menuS != 5);

					} else if (menuP == 3) {
						menuS = 0;	
						do {

						    system("cls");
						    printf ("\n\t\t\tMENU GERENTE\n\n\n");
						    printf("\n\tSub Menu -> Alunos");

						    printf("\n\t1 - Consultar Aluno");
						    printf("\n\t2 - Editar Aluno");
						    printf("\n\t3 - Bloquear Aluno");
						    printf("\n\t4 - Desbloquear Aluno");
						    printf("\n\t5 - Sair");
       						printf("\n\tOpcão: ");
							scanf("%d", &menuS);
							fflush(stdin);

							if(menuS == 1) {

							} else if (menuS == 2){

							} else if (menuS == 3) {

							} else if (menuS == 4) {

							}

			      		} while (menuS != 5);

					} else if (menuP == 4) {
						menuS = 0;
						do {

							system("cls");
							printf ("\n\t\t\tMENU GERENTE\n\n\n");
							printf("\n\tSub Menu -> Emprestimos");
	
		    			    printf("\n\t1 - Consultar Emprestimo");
							printf("\n\t2 - Realizar Emprestimo");
							printf("\n\t3 - Prorrogar Emprestimo");
							printf("\n\t4 - Efetuar Devolução");
							printf("\n\t5 - Baixa de alunos com debito");
							printf("\n\t6 - Sair");
     						printf("\n\tOpcão: ");
							scanf("%d", &menuS);
							fflush(stdin);

							if(menuS == 1) {

							} else if (menuS == 2){

							} else if (menuS == 3) {

							} else if (menuS == 4) {

							} else if (menuS == 5) {

							}

						} while (menuS != 6);

					} else if (menuP == 5) {
					    menuS = 0;
					    do {

					        system("cls");
					        printf ("\n\t\t\tMENU GERENTE\n\n\n");
					        printf("\n\tSub Menu -> Relatórios");

					        printf("\n\t1 - Alunos ativos");
					        printf("\n\t2 - Alunos bloquados");
					        printf("\n\t5 - Alunos com debito.");
					        printf("\n\t3 - Livros Diponíveis");
					        printf("\n\t4 - Livros Indisponíveis");
					        printf("\n\t5 - Editoras cadastradas");
					     	printf("\n\t6 - Sair");
							printf("\n\tOpcão: ");
							scanf("%d", &menuS);
							fflush(stdin);

							if(menuS == 1) {

							} else if (menuS == 2) {

							} else if (menuS == 3) {

							} else if (menuS == 4) {

							} else if (menuS == 5) {

							}

						} while (menuS != 6);


				   } else if (menuP == 6) {
				     	menuS = 0;
						do {

							system("cls");
							printf ("\n\t\t\tMENU GERENTE\n\n\n");
							printf("\n\tSub Menu -> Funcionários");

							printf("\n\t1 - Consultar Funcionario");
							printf("\n\t2 - Editar Funcionario");
							printf("\n\t3 - Demitir Funcionario");
							printf("\n\t4 - Promover Funcionario");
							printf("\n\t5 - Sair");
							printf("\n\tOpcão: ");
							scanf("%d", &menuS);
							fflush(stdin);
							
							if(menuS == 1) {

							} else if (menuS == 2) {

							} else if (menuS == 3) {

							} else if (menuS == 4) {

							}

						} while (menuS != 5);

					}

				} while (menuP != 7);

			}   

			} else if (loginS == 2){ //Menu para o aluno -----------------------------------------------
			
				
				do { //Checar Login de aluno
					saidaLogin = 0;

					system("cls");
					printf ("\n\t\t\tLOGIN\n\n\n");
					printf ("\n\tUser: ");
					scanf ("%s", &login);
					fflush(stdin);
					printf("\n\tSenha: ");
					scanf ("%s", &senha);
					fflush(stdin);

					for (i = 0; i < 50; i++) {

						if (strcmp(A.A[i].estudante.login,login) == 0 && strcmp(A.A[i].estudante.senha,senha)) {

							printf ("\n\n\tLogin realizado com sucesso!");
							saidaLogin = 1;

						}

					}

					if (saidaLogin == 0) {

						aux = 0;
						do {

							system ("cls");
							printf ("\n\t\t\tLOGIN\n\n\n");
							printf ("\n\n\tSenha e/ou usuário está(ão) errado(s).");
							printf("\n\tDeseja tentar novamente?");
							printf("\n\tS - Sim, parece ótimo.");
							printf("\n\tN - Não, sair.");
							printf("\n\tOpção: ");
							scanf ("%c", &loginErro);

							if (loginErro == 's' || loginErro =='S') {

								aux = 1;

							} else if (loginErro == 'n' || loginErro =='N') {

								aux = 2;
								saidaLogin = 2;

							}


						} while(aux != 1 && aux != 2);

					}


				} while (saidaLogin != 1 && saidaLogin != 2);
				
				if(saidaLogin == 1) {
					
					//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
					menuS = 0;
					do{
					
					
					system("cls");
					printf ("\n\t\t\tMENU ALUNO\n\n\n");

					printf("\n\t1 - Consultar Livros");
					printf("\n\t2 - Reservar Livro");
					printf("\n\t3 - Verificar dados cadastrais");
					printf("\n\t4 - Acompanhar emprestimo");
					printf("\n\t5 - Sair");
					printf("\n\tOpcão: ");
					scanf("%d", &menuS);
					fflush(stdin);
						
						if (menuS == 1) {
							
						} else if (menuS == 2) {
							
						} else if (menuS == 3) {
							
						} else if (menuS == 4) {
							
						}
					
					} while (menuS != 5);
				}
			
			
			}

			//salvarArquivosFunc(F);
			//salvarArquivosAluno(A);
			//salvarArquivosEdit(ED);
			//salvarArquivosLivro(L);
			//salvarArquivosEmp(E);

			printf("\n\n\n\tObrigado por utilizar nosso sistema.");
			

		} while (loginS != 3);

	} while (0);
}	

//função Primaria --------------------------------------------------------------------------
int main () {

	setlocale(LC_ALL, "ptb");
	menu();
	getch();

}
