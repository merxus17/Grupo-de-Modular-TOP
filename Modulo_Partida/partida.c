#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include "partida.h"
#include "tabuleiro.h"


PAR_tpCondRet  PAR_Ready (){
	int players = 0;
	Cor cor[4];
	TAB_Head * Tabuleiro = TAB_criaTabuleiro();;
	PAR_Set(&players, cor);
	PAR_Go(players, cor);
}

PAR_tpCondRet  PAR_Set (int *players, Cor cor[4]){
	int i, c, n;
	int jafoi[4] ={0,0,0,0}; // onde tem 1 é uma cor que ja foi

	//recebe o nº de jogadores
	printf("======LUDO=====\n======BEM VINDO\nDigite o numero de jogadores: ");
	scanf("%i", &n);

	//repete ate receber nº valido
	while(n < 2 || n > 4){
		printf("\nNumero de jogadores invalido.\nDigite o numero de jogadores: ");
		scanf("%i", &n);
	}
	*players = n;
	//definicao das cores
	printf("\nAzul     = 1\nVerde    = 2\nAmarelo  = 3\nVermelho = 4\n\n");
	
	for(i = 0; i < n; i++){
		printf("Jodador %i, escolha sua cor: ", i+1);
		scanf("%i", &c);
		
		while(c < 1 || c > 4){
			printf("\nNumero invalido.\nJodador %i, escolha sua cor: ", i+1);
			scanf("%i", &c);
		}
		while(jafoi[c-1] == 1){
			printf("\nEssa cor ja foi escolhida :( \nJodador %i, escolha sua cor: ", i+1);
			scanf("%i", &c);
		}
		
		jafoi[c-1] = 1;

		if(c==1){
			cor[i] = Azul;
		}
		else if(c==2){
			cor[i] = Verde;
		}
		else if(c==3){
			cor[i] = Amarelo;
		}
		else if(c==4){
			cor[i] = Vermelho;
		}
		
	}

	return PAR_CondRetOK;
}

PAR_tpCondRet  PAR_Go (int players, Cor cor[4]){
	int i,j;
	int d[4]; // valor do dado de cada jogador
	int same[4] = {0,0,0,0}; // onde tem 1 é o valor maior entre os dados
	char *colors[4];
	int first;

	PAR_Colors(cor, colors);
	srand(time(NULL));

	for(i=0; i<players; i++){
		for(j=0;j<=32767;j++){}
		d[i] = PAR_Dice();
		printf("\tDado inicial do %s: %i\n", colors[i] ,d[i]); 
	}
	 
	first = PAR_First(same, d, players, colors);
	
	printf("\n %i \n", first);

}

void PAR_Colors (Cor cor[], char **colors){
	int i;
	for (i=0; i<4; i++){
		if(cor[i]==Azul){
			colors[i] = "Azul";
		}
		if(cor[i]==Verde){
			colors[i] = "Verde";
		}
		if(cor[i]==Amarelo){
			colors[i] = "Amarelo";
		}
		if(cor[i]==Vermelho){
			colors[i] = "Vermelho";
		}
	}
}

int  PAR_Dice(){
	return 1 + rand() % 6;
}

void PAR_Max(int d[], int same[]){
	int i;
	int max = 0;
	for (i=0; i<4; i++){
		if(d[i] > max){
			max = d[i];
		}
	}
	for (i=0; i<4; i++){
		if(d[i]==max){
			same[i] = 1;
		}
	}
	return;
}

void zera (int x[4]){
	int i;
	for(i = 0; i < 4; i++){
		x[i] = 0;
	}
	return;
}

int PAR_First (int same[], int d[], int players, char **colors){
	int i;
	
	PAR_Max(d,same);
	if (same[0] == 1 && same[1] == 0 && same[2] == 0 && same[3] == 0){
		printf("\n%s comeca!", colors[0]);
		return 0;
	}
	else if (same[0] == 0 && same[1] == 1 && same[2] == 0 && same[3] == 0){
		printf("\n%s comeca!", colors[1]);
		return 1;
	}
	else if (same[0] == 0 && same[1] == 0 && same[2] == 1 && same[3] == 0 && players > 2){
		printf("\n%s comeca!", colors[2]);
		return 2;
	}
	else if (same[0] == 0 && same[1] == 0 && same[2] == 0 && same[3] == 1 && players > 3){
		printf("\n%s comeca!", colors[3]);
		return 3;
	}
	else{
		zera(d);
		printf("\nEmpataram: ");
		for (i = 0; i < 4; i++){
			if (same[i] == 1){
				printf("%s ", colors[i]);
				d[i] = PAR_Dice(); 
			}
		}
		printf("\n");
		for (i = 0; i < 4; i++){
			if (d[i] != 0){
				printf("\tNovo dado inicial do %s: %i\n", colors[i], d[i]);
			}
		}
		zera(same);
		PAR_Max(d,same);
		return PAR_First(same, d, players, colors);
	}
}


