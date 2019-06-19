#include "tabuleiro.h"


typedef enum{
	PAR_CondRetOK,
		//Jogo ocorreu como desejado
	PAR_CondRetFaltouMemoria,
		//Nao teve memoria para criar o tabuleiro
	PAR_CondRetErroDesconhecido,
		//Houve um erro onde valores foram verificados anteriormente, entao nao deveria haver
	PAR_CondRetNinguemGanhou
		//Nao foi retornada condicao de vitoria, mesmo que o loop tenha parado (so devia parar com condi��o de vitoria)
} PAR_tpCondRet;

/***************************************************************

$FC Fun��o: PAR &Ready

$ED Descri��o da fun��o
	Ela cria o tabuleiro, um vetor de cores do tipo Cor e um do tipo char e chama as fun��es que fazem o jogo funcionar;
	Ou seja, ela � uma prepara��o inical para a partida.

$FV Valor retornado
	CondRetOK			   - tudo funcionou como esperado
	CondRetFaltouMemoria   - falta de mem�ria ao criar o tabuleiro
	CondRetNinguemGanhou   - por algum erro interno, n�o houve retorno de condi��o de vit�ria
	CondRetErroDesconhecido- houve um erro onde valores foram verificados anteriormente, entao nao deveria haver

***************************************************************/
PAR_tpCondRet PAR_Ready ();
