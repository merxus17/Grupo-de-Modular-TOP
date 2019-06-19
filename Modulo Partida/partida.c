#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include "partida.h"
#include "tabuleiro.h"


// CABECALHO DAS FUNCOES ENCAPSULADAS DO MODULO
PAR_tpCondRet  PAR_Set (int *players, Cor cor[4]);
PAR_tpCondRet  PAR_Go (int players, Cor cor[4], TAB_Head *Tabuleiro);
void PAR_Colors (Cor cor[], char **colors);
int  PAR_Dice();
void PAR_Max(int d[], int same[]);
void zera (int x[4]);
int PAR_First (int same[], int d[], int players, char **colors);
void PAR_Order (int first, Cor cor[4], char **colors, int players);
int PAR_Turn (int players, char ** colors, Cor cor[4], TAB_Head * Tabuleiro);
void PAR_Move(char ** colors, Cor cor[4], int i,  TAB_Head *Tabuleiro);
//============================================================================


// FUNCAO EXTERNADA PELO M�DULO
PAR_tpCondRet  PAR_Ready (){
	int players = 0;
	PAR_tpCondRet CondSet, CondGo;
	Cor cor[4];
	char *colors[4]; //o mesmo que o vetor de cores, mas em forma de string para facilitar os prints
	TAB_Head * Tabuleiro = TAB_criaTabuleiro();
	if (Tabuleiro == NULL){
		return PAR_CondRetFaltouMemoria;
	}

	CondSet = PAR_Set(&players, cor, colors);
	if (CondSet != PAR_CondRetOK){
		return CondSet;
	}

	CondGo  = PAR_Go(players, cor, Tabuleiro, colors);
	if (CondGo != PAR_CondRetOK){
		return CondGo;
	}

	TAB_destroiTabuleiro(Tabuleiro);

	return PAR_CondRetOK;
}


// CODIGO DAS FUNCOES ECAPSULADAS

/***************************************************************

$FC Fun��o: PAR &Set

$ED Descri��o da fun��o
	Recebe o n�mero de jogadores que participar�o da partida e armazena no ponteiro recebido;
	Pergunta a cada jogador que cor ele deseja e armazena esses dados num vetor do tipo Cor;
	Roda os dados inicias para verificar qual jogador ser� o primeiro, ent�o ordena os vetores 
									do tipo Cor e tipo char de acordo com a ordem determinada;
	Ou seja, a fun��o "seta" todas as informa��es necess�rias para que o jogo comece.


$EP Par�metros
	*players - ponteiro para a variavel que armazena o n�mero de jogadores
	cor      - vetor do tipo enumerado Cor onde s�o armazenados, em ordem, a cor de cada jogador
	colors   - vetor de strings correspondente ao vetor cor, serve para facilitar os prints

$FV Valor retornado
	CondRetOK			   - tudo funcionou como esperado
	CondRetErroDesconhecido- houve um erro onde valores foram verificados anteriormente, entao nao deveria haver

***************************************************************/
PAR_tpCondRet  PAR_Set (int *players, Cor cor[4], char ** colors){
	int i, c, n;
	int jafoi[4] ={0,0,0,0}; // onde tem 1 � uma cor que ja foi
	int d[4]; // valor do dado de cada jogador
	int same[4] = {0,0,0,0}; // onde tem 1 � o valor maior entre os dados
	int first; //numero q identifica o jogador que come�a

	//recebe o n� de jogadores
	printf("======LUDO=====\n======BEM VINDO\nDigite o numero de jogadores: ");
	scanf("%i", &n);

	//repete ate receber n� valido
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
		else{
			return PAR_CondRetErroDesconhecido;
		}
		
	}

	PAR_Colors(cor, colors);
	srand(time(NULL));

	printf("\n");

	for(i=0; i<*players; i++){
		d[i] = PAR_Dice();
		printf("\tDado inicial do %s: %i\n", colors[i] ,d[i]); 
	}
	 
	first = PAR_First(same, d, *players, colors);

	if(first > 4 || first <0){
		return PAR_CondRetErroDesconhecido;
	}

	PAR_Order(first, cor, colors, *players);


	return PAR_CondRetOK;
}


/***************************************************************

$FC Fun��o: PAR &Go

$ED Descri��o da fun��o
	Mostra o estado do tabuleiro a cada turno;
	Faz com que os turnos continuem acontecendo at� que um dos jogadores ven�a e diz quem ganhou no final;
	Ou seja, � quem da o "go" da partida.


$EP Par�metros
	*players - ponteiro para a variavel que armazena o n�mero de jogadores
	cor      - vetor do tipo enumerado Cor onde s�o armazenados, em ordem, a cor de cada jogador
	Tabuleiro- ponteiro para o tabuleiro da partida
	colors   - vetor de strings correspondente ao vetor cor, serve para facilitar os prints

$FV Valor retornado
	CondRetOK			   - tudo funcionou como esperado
	CondRetErroDesconhecido- houve um erro onde valores foram verificados anteriormente, entao nao deveria haver
	CondRetNinguemGanhou   - por algum erro interno, n�o houve retorno de condi��o de vit�ria

***************************************************************/

PAR_tpCondRet  PAR_Go (int players, Cor cor[4], TAB_Head *Tabuleiro, char **colors){
	int i,j;
	int noWin = 1;
	
	TAB_showTab(Tabuleiro);

	while(noWin){
		noWin = PAR_Turn (players, colors, cor, Tabuleiro);
	}

	for (j = 0; j < players; j++){
		if (TAB_verificaVitoria(Tabuleiro, cor[j]) == TAB_CondRetVitoria){
			printf("\n\n VITORIA DO %s\n\n", colors[j]);
			return PAR_CondRetOK;
		}
	}
	if(j == players)
		return PAR_CondRetNinguemGanhou;
}


/***************************************************************

$FC Fun��o: PAR &Turn

$ED Descri��o da fun��o
	Realiza a organiza��o dos turnos da partida, chamando a fun��o que permite aos jogadores fazerem seus movimentos.


$EP Par�metros
	*players - ponteiro para a variavel que armazena o n�mero de jogadores
	cor      - vetor do tipo enumerado Cor onde s�o armazenados, em ordem, a cor de cada jogador
	Tabuleiro- ponteiro para o tabuleiro da partida
	colors   - vetor de strings correspondente ao vetor cor, serve para facilitar os prints

$FV Valor retornado
	1 - quando ningu�m venceu ainda
	0 - quando algu�m vence

***************************************************************/

int PAR_Turn (int players, char ** colors, Cor cor[4], TAB_Head * Tabuleiro){
	int i,j, noWin = 1;

	if(Tabuleiro == NULL){ // assertiva
		return NULL;
	}

	for (i = 0; i < players; i++){
		PAR_Move(colors, cor, i, Tabuleiro);

		for (j = 0; j < players; j++){
			if (TAB_verificaVitoria(Tabuleiro, cor[j]) == TAB_CondRetVitoria){
				noWin = 0;
				return noWin;
			}
		}
		
		printf("\nProximo jogador!");
		printf("\n=========================================");
		
	}
	return noWin;
}


/***************************************************************

$FC Fun��o: PAR &Move

$ED Descri��o da fun��o
	Pergunta ao jogador da vez que pe�a ele deseja mover;
	Chama a fun��o de mover pe�a do m�dulo tabuleiro, usando o valor retirado no dado;
	Faz o tratamento de cada caso de retorno dela:
		Se a pe�a escolhida est� fora de jogo e o dado n�o deu 1 ou 6 a fun��o termina;
		Se a pe�a escolhida j� est� na reta final e o valor no dado n�o � o exato necessario para o fim, a fun��o termina;
		Se a pe�a j� est� no fim o jogador deve escolher outra. A fun��o � chamada de novo, recursivamente;
		Se o jogador tirou 6 no dado ele tem direito a um turno extra. A fun��o � chamada de novo, recursivamente.


$EP Par�metros
	*players - ponteiro para a variavel que armazena o n�mero de jogadores
	cor      - vetor do tipo enumerado Cor onde s�o armazenados, em ordem, a cor de cada jogador
	Tabuleiro- ponteiro para o tabuleiro da partida
	colors   - vetor de strings correspondente ao vetor cor, serve para facilitar os prints
	i		 - inteiro que identifica de qual jogador � a vez

***************************************************************/
void PAR_Move(char ** colors, Cor cor[4], int i,  TAB_Head *Tabuleiro){
	int dice, nPeca;
	TAB_tpCondRet MovRet;


	printf("\n%s, que peca deseja mover? ", colors[i]);
	scanf("%i", &nPeca);

	while(nPeca < 1 || nPeca > 4){
		printf("\nPeca invalida.");
		printf("\n%s, que peca deseja mover? ", colors[i]);
		scanf("%i", &nPeca);
	}

	dice = PAR_Dice();
	printf("\n valor no dado: %i", dice);

	MovRet = TAB_moverPeca(Tabuleiro, cor[i], nPeca-1 , dice); //realiza o movimento
	TAB_showTab(Tabuleiro);

	if(MovRet == TAB_CondRetNaoEstaEmJogo){
		printf("\nEsse valor nao bota a peca em jogo :( \n");
	}
	else if(MovRet == TAB_CondRetNotYet){
		printf("\nEsse valor nao e exato para levar a peca ao centro :( ");
	}
	else if(MovRet == TAB_CondRetJaTaNoFim){
		printf("\nEssa peca ja esta no centro :)");
		printf("\n=========================================");
		PAR_Move(colors, cor, i, Tabuleiro);
	}
	else if (dice == 6){
		printf("\nTirou 6! Jogue novamente! :D");
		PAR_Move(colors, cor, i, Tabuleiro);
	}
		
}

/***************************************************************

$FC Fun��o: PAR &Order

$ED Descri��o da fun��o
	Modifica a ordem dos vetores cor e colors de acordo com a ordem determinada por quem tirou o maior valor no dado inicial;
	O jogador que vai primeiro � identificado pelo inteiro first e resto � organizado levando em conta o sentido hor�rio.


$EP Par�metros
	players  - inteiro que armazena o n�mero de jogadores
	cor      - vetor do tipo enumerado Cor onde s�o armazenados, em ordem, a cor de cada jogador
	colors   - vetor de strings correspondente ao vetor cor, serve para facilitar os prints
	first    - inteiro que identifica qual jogador � o primeiro

***************************************************************/

void PAR_Order (int first, Cor cor[4], char **colors, int players){
	int i;
	Cor aux[4];
	for (i = 0; i < players; i++){
		aux[i] = cor[first];
		if(first < players-1){
			first++;
		}
		else if(first == players-1){
			first = 0;
		}
	}
	for (i = 0; i < players; i++){
		cor[i] = aux[i];
	}
	
	PAR_Colors(cor, colors);
	for (i=0;i<players;i++){
		printf("\t %s", colors[i]);
	}

}

/***************************************************************

$FC Fun��o: PAR &Colors

$ED Descri��o da fun��o
	Faz a equivalencia entre o vetor do tipo Cor e do tipo char, de forma que cada entrada de cor corresponda � entrada de mesmo indice em colors;
	Essa equivalencia serve para facilitar os prints.

$EP Par�metros
	cor      - vetor do tipo enumerado Cor onde s�o armazenados, em ordem, a cor de cada jogador
	colors   - vetor de strings correspondente ao vetor cor, serve para facilitar os prints

***************************************************************/

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

/***************************************************************

$FC Fun��o: PAR &Dice

$ED Descri��o da fun��o
	Usa uma fun��o da biblioteca de C para gerar um n�mero aleatorio entre 1 e 6, simulando um dado;

***************************************************************/

int  PAR_Dice(){
	return 1 + rand() % 6;
}

/***************************************************************

$FC Fun��o: PAR &Max

$ED Descri��o da fun��o
	Encontra o maior n�mero entre os fornecidos pelo vetor d, que contem o valor dos dados inicias;
	O vetor same � recebido com todas as entradas iguais a 0, quando � verificado que um jogador tirou o valor maximo encontrado no dado, 
				a entrada no vetor same referente a ele vira 1, assim o programa sabe quais jogadores empataram para realizar o desempate,
				e ao fim dos desempates sabe-se quem come�a.

$EP Par�metros
	d	 - vetor de inteiros que armazena, em ordem, o valor retirado no dado incial de cada jogador
	same - vetor de inteiros que indica quais jogadores tiraram o mesmo maior valor

***************************************************************/

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

/***************************************************************

$FC Fun��o: PAR &zera

$ED Descri��o da fun��o
	Todo o programa faz uso de muitos vetores de inteiros com 4 elementos, por isso essa fun��o serve apenas para
	auxiliar quando um desses vetores precisa ser zerado.

$EP Par�metros
	x - vetor de inteiros a ser zerado

***************************************************************/
void zera (int x[4]){
	int i;
	for(i = 0; i < 4; i++){
		x[i] = 0;
	}
	return;
}

/***************************************************************

$FC Fun��o: PAR &First

$ED Descri��o da fun��o
	Primeiro  chama a fun��o PAR_Max e verifica se apenas uma das entradas do vetor same � 1, se sim retorna o �ndice da entrada vencedora;
	Se n�o, informa quais os jogadores que empataram e roda novos dados iniciais apenas para eles;
	Zera o vetor same, chama novamente a fun��o PAR_Max para atualizar o vetor same e chama a fun��o de novo, recursivamente, at� que
	apenas um jogador tenha o maior valor. 

$EP Par�metros
	same	 - vetor de inteiros que diz qual/quais jogadores tiraram o valor maior no dado inicial
	d		 - vetor de inteiros que tem os valores tirados nos dados
	players  - inteiro que diz o n�mero de jogadores na partida
	colors   - vetor de strings correspondente ao vetor cor, serve para facilitar os prints

$EV Valor Retornado

	Retorna o �ndice correspondente ao jogador que come�a

***************************************************************/

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




