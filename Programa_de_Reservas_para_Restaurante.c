#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define RESERVA_MAX 100

typedef struct{  //STRUCT DE CADASTRO//
    char nome[50];
    char cpf[11];
    int quant_clientes, dia;
} cadastro;

int escolhaDia(){ //OPÇÃO DE DIAS//
    int dia;
    printf("Selecione o dia desejado: \n");
    printf("1 - Quinta-feira \n");
    printf("2 - Sexta-feira \n");
    printf("3 - Sabado \n");
    printf("4 - Domingo \n");
    fflush(stdin);
    scanf("%d", &dia);
    while(dia>4){
        printf("Dia errado! Selecione novamente! \n");
        printf("Escolha entre 1 e 4: \n");
        printf("1 - Quinta-feira \n");
        printf("2 - Sexta-feira \n");
        printf("3  - Sabado \n");
        printf("4 - Domingo \n");
        fflush(stdin);
        scanf("%d", &dia);
    }
    return dia;
}

int validaCPF(cadastro *cad, int i) { //VALIDAÇÃO DE CPF//
    if (strlen(cad[i].cpf) != 14) {
        printf("CPF deve ter exatamente 14 caracteres!\n");
        printf("Formato solicitado: formato XXX.XXX.XXX-XX\n");
        return 0;
    }
    int j = 0;
    for (j = 0; j < 14; j++) {
        if ((j == 3 || j == 7) && cad[i].cpf[j] != '.') 
            return 0;
        if (j == 11 && cad[i].cpf[j] != '-') 
            return 0;
        if ((j != 3 && j != 7 && j != 11) && (cad[i].cpf[j] < '0' || cad[i].cpf[j] > '9')) 
            return 0;
    }
    return 1;
}

int validaNome(cadastro *cad, int i) { //VALIDAÇÃO DE NOME//
    if (strlen(cad[i].nome) < 1) {
        printf("Nome não digitado!\n");
        return 0;
    }
    return 1;
}

void novoCadastro(cadastro *cad, int i){ //CADASTRO DE RESERVA//
    int valido=0;
    do { //VALIDAÇÃO DE DIGITAÇÃO DE NOME//
        printf("Digite o nome do responsável: \n");
        fflush(stdin);
        gets(cad[i].nome);
        valido = validaNome(cad,i);
        if (valido==0) {
            printf("Por favor, ");
        }
    } while (valido==0);
    do { //VALIDAÇÃO DE CARACTERES DE CPF//
        printf("Digite o CPF do responsavel: \n");
        fflush(stdin);
        scanf("%s", &cad[i].cpf);
        valido = validaCPF(cad, i);
        if (valido==0) {
            printf("CPF inválido. Tente novamente.\n\n");
       }
    } while (valido==0);
        cad[i].dia=escolhaDia();
        printf("Digite a quantidade de pessoas para esta reserva: \n");
        fflush(stdin);
        scanf("%d", &cad[i].quant_clientes);
}

void imprimaDia(int diaD){ //DESCRIÇÃO DE DIA//
    switch (diaD) {
        case 1:
             printf("Quinta-feira:\n\n"); break;
        case 2:
             printf("Sexta-feira:\n\n"); break;
        case 3:
             printf("Sábado:\n\n"); break;
        case 4:
             printf("Domingo:\n\n"); break;
    }
}

void imprimaCadastro(cadastro *cad, int i){ //IMPRESSÃO DE CADASTRO//
    printf("Reserva realizada com sucesso! \n");
    printf("Segue abaixo informações: \n \n");
    printf("===============================\n \n");
    printf("Responsavel: %s, CPF %s \n", cad[i].nome, cad[i].cpf);
    printf("Reserva realizada para: ");
    int diaD=cad[i].dia;
    imprimaDia(diaD);
    printf("Quantidade de pessoas: %d \n \n", cad[i].quant_clientes);
    printf("===============================\n \n");	
}

void resumoReserva(cadastro *cad, int diaD){ //LISTA DE RESERVAS//
    int d=0;
    int reservadia = 0;
    for (d=0; d < RESERVA_MAX; d++) {
        if (cad[d].dia == diaD) {
             printf("===============================\n");
             printf("Reserva #%d \n", d + 1);
             printf("Nome: %s \n", cad[d].nome);
             printf("CPF: %s \n", cad[d].cpf);
             printf("Dia: %d \n", cad[d].dia);
             printf("Quantidade de pessoas: %d \n", cad[d].quant_clientes);
             printf("===============================\n\n");
             fflush(stdin);
             reservadia = 1;
        }
    }
    if (reservadia == 0) {
        printf("===============================\n");
        printf("Nenhuma reserva encontrada para este dia.\n");
        printf("===============================\n\n");
    }
}

void calculoReserva(cadastro *cad, int diaD){ // QUANTIDADE DE CLIENTES//
   int t=0;
   int somareservas = 0;
   int quantreservas=0;
   for (t=0; t < RESERVA_MAX; t++){
        if (cad[t].dia == diaD) {
             somareservas += cad[t].quant_clientes;
             quantreservas++;
        }
    }
   printf("Resumo de reservas para ");
   imprimaDia(diaD);
   printf("\n===============================\n");
   printf("Quantidade de Reservas: %d\n", quantreservas);
   printf("Quantidade de clientes, com base nas reservas: %d", somareservas);
   printf("\n===============================\n");
}

int main() {
   setlocale(LC_ALL,"");
   cadastro cad[RESERVA_MAX];
   int menu;
   char opcao2;
   int i=0;
   memset(cad, 0, sizeof(cad));
   do { //MENU//
        printf("Seja Bem-vindo ao sistema de Reservas! \n");
        printf("Selecione uma ação: \n\n");
        printf("1 - Fazer uma reserva \n");
        printf("2 - Listar Reservas \n");
        printf("3 - Total de Pessoas Por Dia.\n");
        printf("4 - Sair\n\n");
        fflush(stdin);
        scanf("%d", &menu);
        system("cls");

        switch(menu) {
             case 1:
                   printf("BEM VINDO AO CADASTRO DE RESERVA!\n\n");
	        do{
		   if (i >= RESERVA_MAX) {
                              printf("Número máximo de reservas atingido!\n");
                              break;
		   }
		   novoCadastro(cad, i); 	//FUNÇÃO CADASTRO DE RESERVA//
		   system("cls");
		   imprimaCadastro(cad, i); //FUNÇÃO IMPRIMA CADASTRO// 
		   i++;	    
		   printf("Você deseja realizar mais um cadastro? \n");
		   printf("s - Sim \n");
		   printf("n - Não \n");
		   fflush(stdin);
		   scanf("%c", &opcao2);
		    	    
		   system("pause");
		   system("cls");
	        } while(opcao2 != 'n');
	        break;
             case 2:
                   printf("BEM VINDO A ÁREA DE LISTAGEM!\n\n");
                   do{
		   int diaD=escolhaDia(); //OPÇÃO DE DIAS//
		   system("cls");
		   printf("Confira o resumo de reservas para ");
		   imprimaDia(diaD);  //IMPRESSÃO DE DIAS//
		   resumoReserva(cad, diaD);
		   printf("Você deseja analisar outra listagem? \n");
		   printf("s - Sim \n");
		   printf("n - Não \n");
		   printf("\n");
		   scanf("%c", &opcao2);
		   fflush(stdin);		    	    
		   system("pause");
		   system("cls");
                   } while(opcao2 != 'n');
                   break;
             case 3:
                   printf("BEM VINDO AO RESUMO DE RESERVAS!\n");
                   printf("Abaixo será listado o total de clientes para o dia selecionado.\n\n");
                   do{
		   int diaD=escolhaDia(); //OPÇÃO DE DIAS//
		   system("cls");
		   calculoReserva(cad, diaD); //RESUMO DE RESERVAS//
		   printf("Você deseja verificar o resumo de reservas de outro dia? \n");
		   printf("s - Sim \n");
		   printf("n - Não \n");
		   fflush(stdin);
		   scanf("%c", &opcao2);
		   system("pause");
		   system("cls");
                   } while(opcao2 != 'n');
                   break;
             case 4:
                   printf("Saindo...\n");
                   break;
        }
   }
   while(menu != 4);
   return 0;
}



