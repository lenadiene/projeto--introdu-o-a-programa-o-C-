#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTATOS 1000 

typedef enum {
	TELA_SAIR=-1,
	TELA_PRINCIPAL,
	TELA_CADASTRAR,
	TELA_DESCADASTRAR,
	TELA_LISTAR_TODOS,
} Telas;

typedef struct
{
	char nome[128];
	char telefone[64];
} Contato;

typedef struct
{
	Telas menu;
	int totalContatos;
	Contato contatos[MAX_CONTATOS];
} AgendaTelefonica;

int main (void)
{
    AgendaTelefonica agenda;
    
	memset(&agenda, 0x0, sizeof(agenda));
	
	
	agenda.menu = TELA_PRINCIPAL;
  
  FILE * memoria;
  if (memoria = fopen("contatos.bin", "r")){
        fclose(memoria);
	}
  
  else{
  	memoria = fopen("contatos.bin", "w");
	fclose(memoria);  
    }
	
  memoria = fopen("contatos.bin", "rb");	

  size_t lidos = fread(agenda.contatos, sizeof(Contato), 
  				MAX_CONTATOS, memoria);
  printf("lidos %zd contatos\n", lidos);
  agenda.totalContatos = (int)lidos;
  fclose(memoria);

	
	while (agenda.menu != TELA_SAIR)
	{
		switch (agenda.menu)
		{
		case TELA_PRINCIPAL:
		{
		  printf("-------------------------------------\n");
          printf("\tAGENDA TELEFONICA\n");
          printf("-------------------------------------\n");
          int opcao = -1;
          do
          {
            printf("EESCOLHA UMA OPCAO:\n");
            printf("\tDIGITE 1 PARA CADASTRAR UM CONTATO\n");
            printf("\tDIGITE 2 PARA REMOVER UM CONTATO\n");
            printf("\t DIGITE 3 PARA LISTAR TODOS OS CONTATOS\n");
            printf("\t DIGITE 0 PARA FECHAR O PROGRAMA\n");
            scanf("%d", &opcao);
            
          } while (opcao < 0 || opcao > 3);
          
          if (opcao == 0)
            agenda.menu = TELA_SAIR;
          
          if (opcao == 1)
          {
            agenda.menu = TELA_CADASTRAR;
            if (agenda.totalContatos >= MAX_CONTATOS)
            {
              printf("\tA AGENDA ESTA CHEIA, NAO E POSSIVEL ADICIONAR NOVOS CONTATOS\n");
              agenda.menu = TELA_PRINCIPAL;
            }
          }
          
          if (opcao == 2)
          {
            agenda.menu = TELA_DESCADASTRAR;
            if (agenda.totalContatos == 0)
            {
              printf("\tNAO TEM NENHUM CONTATO CADASTRADO PARA REMOVER\n");
              agenda.menu = TELA_PRINCIPAL;
            }
          }
          
          if (opcao == 3)
          {
            agenda.menu = TELA_LISTAR_TODOS;
            if (agenda.totalContatos == 0)
            {
              printf("\tA AGENDA NAO TEM NENHUM CONTATO PARA LISTAR\n");
              agenda.menu = TELA_PRINCIPAL;
            }
          }
        }
        break;
	
		case TELA_CADASTRAR:
		{
          printf("-------------------------------------\n");
          printf("\tTELA DE CADASTRO\n");
          printf("-------------------------------------\n");
          Contato novo;
          char opcao = 's';
          printf ("DESEJA INSERIR UM NOVO CONTATO? DIGITE ENTER PARA CONTINUAR\n");
		  int c = 0;
          while ((c = getchar()) != '\n' && c != EOF) { }
		  do
          {
            memset(&novo, 0x0, sizeof(novo));
            printf("DIGITE UM NOVO NOME PARA O CONTATO: \n");
            fgets(novo.nome, 128, stdin);
            int id = 0;
            while (novo.nome[id] != '\0' && novo.nome[id] != '\n')
              id++;
            novo.nome[id] = '\0';
            printf("DIGITE UM NOVO TELEFONE PARA O CONTATO:\n");
            fgets(novo.telefone, 64, stdin);
            id = 0;
            while (novo.telefone[id] != '\0' && novo.telefone[id] != '\n')
              id++;
            novo.telefone[id] = '\0';
            printf("DESEJA REALMENTE ADICIONAR ESSE CONTATO? [s/n]\n");
            opcao = getchar();
            c = 0;
            while ((c = getchar()) != '\n' && c != EOF) { }
          } while (opcao == 'n' || opcao == 'N');

		  agenda.contatos[agenda.totalContatos] = novo;
          agenda.totalContatos++;
		  memoria = fopen("contatos.bin", "w+b");
          if (memoria == NULL)
          {
            printf("ERRO ao abrir contatos.bin\n");
            return 0;
          }

          size_t salvos = fwrite(agenda.contatos, sizeof(Contato), 
		  agenda.totalContatos, memoria);
          if (salvos != (size_t)agenda.totalContatos)
          {
            printf("ERRO ao salvar contatos na memoria contatos.bin\n");
            return 1;
          }
          fclose(memoria);
					agenda.menu = TELA_PRINCIPAL;
		}
		break;
			
		case TELA_DESCADASTRAR:
		{
          printf("-------------------------------------\n");
          printf("\tTELA DE DESCADASTRO\n");
          printf("-------------------------------------\n");
          int i;

          for (i = 0; i < agenda.totalContatos; i++)
          {
            printf("CONTATO %d\n", i);
            printf("\tNOME: %s\n", agenda.contatos[i].nome);
            printf("\tTELEFONE: %s\n", agenda.contatos[i].telefone);
            printf("----------------------------------------------------\n");
          }
          int indice = -1;
          do
          {
            printf("DIGITE UM INDICE DE CONTATO PARA DESCADASTRAR: de 0 até %d\n", agenda.totalContatos-1);
            scanf("%d", &indice);
           
           
            int c = 0;
            while ((c = getchar()) != '\n' && c != EOF) { }
          } while (indice < 0 || indice >= agenda.totalContatos);
          
          for (i = indice; i < agenda.totalContatos - 1; i++)
            agenda.contatos[i] = agenda.contatos[i + 1];
         
          agenda.totalContatos--;

          memoria = fopen("contatos.bin", "w+b");
          if (memoria == NULL)
          {
            printf("ERRO ao abrir contatos.bin\n");
            return 0;
          }
          size_t salvos = fwrite(agenda.contatos, sizeof(Contato), agenda.totalContatos, memoria);
          if (salvos != (size_t)agenda.totalContatos)
          {
            printf("ERRO ao salvar contatos na memoria contatos.bin\n");
            return 1;
          }
          fclose(memoria);
					
  			agenda.menu = TELA_PRINCIPAL;
		}
		break;
			
			case TELA_LISTAR_TODOS:
				{
		          printf("-------------------------------------\n");
		          printf("\tLISTANDO CONTATOS\n");
        		  printf("-------------------------------------\n");
          		  int i;
		          for (i = 0; i < agenda.totalContatos; i++)
        		  {
            		printf("CONTATO %d\n", i);
            		printf("\tNOME: %s\n", agenda.contatos[i].nome);
            		printf("\tTELEFONE: %s\n", agenda.contatos[i].telefone);
            		printf("----------------------------------------------------\n");
          		  }
				agenda.menu = TELA_PRINCIPAL;
				}
				break;
			
			default:
				agenda.menu = TELA_PRINCIPAL;
				break;
		}
	}
	
	return 0;
}
