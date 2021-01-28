#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {
	char data[10];
	char autor[30];
	char dayRate[10];
} Info;

typedef struct {
	char tamanhoLinha[200];
	int tela;
	int diasEscritos;
	int procurar;
	int terminarEscrita;
	int diaRemover;
	int diaLer;
	int Sair;
} Diario;

int main(void) {

	Diario diario;
	diario.diasEscritos = 0;

	Info info;

	char nomeFile[] = "diario.dat";

	FILE * memoria;
	FILE * cache;

	while(1) {

		//Checa se o arquivo existe. Caso exista, procura quantos dias foram escritos//
		if (memoria = fopen(nomeFile, "r")) {
			diario.diasEscritos = 0;
			while(!feof(memoria)) {
				fgets(diario.tamanhoLinha, 5, memoria);
				if((diario.tamanhoLinha[0] == 'D') && (diario.tamanhoLinha[1] == 'i') && (diario.tamanhoLinha[2] == 'a') && (diario.tamanhoLinha[3] == ':')) {
					diario.diasEscritos++;
				}
			}

			fclose(memoria);
		}

		//Caso nao exista, cria o arquivo//
		else {
			memoria = fopen(nomeFile, "w");
			fclose(memoria);
		}

		system("COLOR 0B");

		printf("--------------------------------\n");
		printf("Voce possui %d dias escritos\n", diario.diasEscritos);
		printf("--------------------------------\n\n");
		printf("Ola, o que voce deseja fazer?\n\n");

		//Todas as opcoes so serao exibidas caso exista um ou mais dias escritos//
		if (diario.diasEscritos > 0) {
			printf("01- Adicionar um dia ao Diario;\n");
			printf("02- Ler um dia do Diario;\n");
			printf("03- Remover um dia do Diario;\n");
			printf("04- Resetar o Diario\n\n");
			printf("05- Fechar o programa\n\n");
			printf("Selecione: ");
			fflush(stdin);
			scanf(" %d", &diario.tela);
		}

		//Se nao houver nenhum, sera direcionado automaticamente para criar um novo//
		else {
			printf("~Voce nao possui nenhum dia adicionado, por favor \naperte Enter para continuar~\n");
			fflush(stdin);
			getchar();
			diario.tela = 1;
		}

		switch (diario.tela) {
			case 1:
				
				//Nesse case, apos a entrada das informacoes iniciais, ele entrara em um loop de leitura e escrita, onde
				//sera permitido ao usuario ver o que ja foi escrito enquanto cria uma nova linha
				system("cls");

				system("COLOR CF");

				memoria = fopen(nomeFile, "a");

				printf("--------------------------------\n");
				printf("Criacao de dia\n");
				printf("--------------------------------\n\n");

				//Entrada das informacoes iniciais//
				printf("Que dia e hoje? (d/m/a)\n");
				fflush(stdin);
				fgets(info.data, 10, stdin);
				fprintf(memoria, "\nDia: ");
				fprintf(memoria, info.data);

				printf("\nQuem esta escrevendo?\n");
				fflush(stdin);
				fgets(info.autor, 30, stdin);
				fprintf(memoria, "\nAutor: ");
				fprintf(memoria, info.autor);

				printf("\nQue nota voce daria ao seu dia?\n");
				fflush(stdin);
				fgets(info.dayRate, 10, stdin);
				fprintf(memoria, "DayRate: ");
				fprintf(memoria, info.dayRate);

				fclose(memoria);

				diario.terminarEscrita = 0;
				diario.diasEscritos++;

				//Comeco do loop//
				while(diario.terminarEscrita == 0) {
					system("cls");

					printf("--------------------------------\n");
					printf("Criacao de dia\n");
					printf("--------------------------------\n\n");

					diario.procurar = 0;

					//Responsavel pela exibicao do que ja foi escrito//
					memoria = fopen(nomeFile, "r");

					while(!feof(memoria)) {
						fgets(diario.tamanhoLinha, 5, memoria);
						if((diario.tamanhoLinha[0] == 'D') && (diario.tamanhoLinha[1] == 'i') && (diario.tamanhoLinha[2] == 'a') && (diario.tamanhoLinha[3] == ':')) {
							diario.procurar++;
							if(diario.procurar == diario.diasEscritos) {
								puts("Dia: ");
								while(!feof(memoria)) {
									fgets(diario.tamanhoLinha, 150, memoria);
									puts(diario.tamanhoLinha);
								}
							}
						}
					}

					fclose(memoria);

					//Responsavel pela insercao de novas linhas ou, a saida do programa//
					memoria = fopen(nomeFile, "a");

					printf("Dicas:\nQuando terminar um pensamento basta apertar Enter,\n");
					printf("a ultima frase escrita ficara em evidencia;\n\n");
					printf("Para sair basta escrever Sair\n\n");

					fflush(stdin);
					fgets(diario.tamanhoLinha, 200, stdin);

					if((diario.tamanhoLinha[0] == 'S') && (diario.tamanhoLinha[1] == 'a') && (diario.tamanhoLinha[2] == 'i') && (diario.tamanhoLinha[3] == 'r')) {
						diario.terminarEscrita = 1;
						system("cls");
					}

					else {
						fprintf(memoria, diario.tamanhoLinha);
					}

					fclose(memoria);

				}

				break;

			case 2:

				//Nesse case, será informado os dias que já foram escritos e o usuário
				//tera a opcao de selecionar que dia ele deseja ler
				system("cls");

				system("COLOR 90");

				printf("--------------------------------\n");
				printf("Leitura de dia\n");
				printf("Voce possui %d dias escritos\n", diario.diasEscritos);
				printf("--------------------------------\n\n");

				printf("Ola, qual desses dias voce gostaria de ler?\n\n");
				
				//Abre o arquivo e procura quais os dias ja foram escritos, informando sua data e posicao//
				memoria = fopen(nomeFile, "r");

				diario.procurar = 0;

				while(!feof(memoria)) {
					fgets(diario.tamanhoLinha, 5, memoria);
					if((diario.tamanhoLinha[0] == 'D') && (diario.tamanhoLinha[1] == 'i') && (diario.tamanhoLinha[2] == 'a') && (diario.tamanhoLinha[3] == ':')) {
						diario.procurar++;
						fgets(diario.tamanhoLinha, 150, memoria);
						printf("%d -", diario.procurar);
						puts(diario.tamanhoLinha);
					}
				}

				fclose(memoria);

				diario.Sair = 0;
				
				//O usuario podera informar qual data deseja ler, o programa informara
				//caso o numero inserido seja invalido
				while(diario.Sair == 0) {
					fflush(stdin);
					scanf(" %d", &diario.diaLer);
					if((diario.diaLer > 0) && (diario.diaLer <= diario.procurar)) {
						diario.Sair = 1;
						printf("\n\n");
					}

					else {
						printf("\nPor favor insira um numero valido\n\n");
					}
				}

				diario.procurar = 0;
				diario.Sair = 0;

				system("cls");
				
				//Apos o dia ser validado, ele sera apresentado ao usuario
				memoria = fopen(nomeFile, "r");

				while(!feof(memoria)) {
					fgets(diario.tamanhoLinha, 150, memoria);
					if((diario.tamanhoLinha[0] == 'D') && (diario.tamanhoLinha[1] == 'i') && (diario.tamanhoLinha[2] == 'a') && (diario.tamanhoLinha[3] == ':')) {
						diario.procurar++;
					}

					if(diario.procurar == diario.diaLer) {
						while(diario.Sair == 0) {
							fgets(diario.tamanhoLinha, 150, memoria);
							if((feof(memoria)) || (diario.tamanhoLinha[0] == 'D') && (diario.tamanhoLinha[1] == 'i') && (diario.tamanhoLinha[2] == 'a') && (diario.tamanhoLinha[3] == ':')) {

								diario.Sair = 1;
								printf("\n\nAperte Enter para continuar\n");
								fflush(stdin);
								getchar();
								system("cls");
							} else {
								puts(diario.tamanhoLinha);
							}
						}
					}
				}

				fclose(memoria);

				break;

			case 3:
				
				//Nesse case, será informado os dias que já foram escritos e o usuário
				//tera a opcao de selecionar que dia ele deseja remover do arquivo
				system("cls");

				system("COLOR ED");

				printf("--------------------------------\n");
				printf("Remocao de dia\n");
				printf("Voce possui %d dias escritos\n", diario.diasEscritos);
				printf("--------------------------------\n\n");

				printf("Ola, qual desses dias voce gostaria de remover?\n\n");

				memoria = fopen(nomeFile, "r");

				diario.procurar = 0;
				
				//Abre o arquivo e procura quais os dias ja foram escritos, informando sua data e posicao//
				while(!feof(memoria)) {
					fgets(diario.tamanhoLinha, 5, memoria);
					if((diario.tamanhoLinha[0] == 'D') && (diario.tamanhoLinha[1] == 'i') && (diario.tamanhoLinha[2] == 'a') && (diario.tamanhoLinha[3] == ':')) {
						diario.procurar++;
						fgets(diario.tamanhoLinha, 150, memoria);
						printf("%d -", diario.procurar);
						puts(diario.tamanhoLinha);
					}
				}

				fclose(memoria);

				diario.Sair = 0;
				
				//O usuario podera informar qual data deseja remover, o programa informara
				//caso o numero inserido seja invalido
				while(diario.Sair == 0) {
					fflush(stdin);
					scanf(" %d", &diario.diaRemover);
					if((diario.diaRemover > 0) && (diario.diaRemover <= diario.procurar)) {
						diario.Sair = 1;
					}

					else {
						printf("\nPor favor insira um numero valido\n\n");
					}
				}

				diario.procurar = 0;
				diario.Sair = 0;

				//Apos o dia ser validado, ele sera removido do arquivo
				memoria = fopen(nomeFile, "r");
				
				//Sera criado um arquivo temporario de nome "temp.dat"
				//Nesse arquivo serao inseridas todas as as data menos a que o usuario deseja remover
				cache = fopen("temp.dat", "w");

				while(!feof(memoria)) {
					fgets(diario.tamanhoLinha, 150, memoria);
					if((diario.tamanhoLinha[0] == 'D') && (diario.tamanhoLinha[1] == 'i') && (diario.tamanhoLinha[2] == 'a') && (diario.tamanhoLinha[3] == ':')) {
						diario.procurar++;
					}

					if(diario.procurar == diario.diaRemover) {
						while(diario.Sair == 0) {
							fgets(diario.tamanhoLinha, 150, memoria);
							if((feof(memoria)) || (diario.tamanhoLinha[0] == 'D') && (diario.tamanhoLinha[1] == 'i') && (diario.tamanhoLinha[2] == 'a') && (diario.tamanhoLinha[3] == ':')) {
								diario.Sair = 1;
								printf("\n\nAperte Enter para continuar\n");
								fflush(stdin);
								getchar();
								system("cls");
							}
						}
					}
					fprintf(cache, diario.tamanhoLinha);
				}

				fclose(memoria);
				fclose(cache);
				
				//Apos o procedimento, o arquivo original sera excluido e
				//o arquivo com os demais dias sera renomeado para o nome do arquivo original
				remove(nomeFile);
				rename("temp.dat", nomeFile);

				break;

			case 4:
				
				//Nesse case, o arquivo de texto sera sobrescrito 
				//por um arquivo em branco de mesmo nome
				memoria = fopen(nomeFile, "w");
				fclose(memoria);
				system("cls");
				break;

			case 5:
				exit(0);
				break;

			default:
				diario.tela	= 1;
		}
	}

	return 0;
}

