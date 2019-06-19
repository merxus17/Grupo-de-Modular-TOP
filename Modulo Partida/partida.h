#include "tabuleiro.h"


typedef enum{
	PAR_CondRetOK,
		//Jogo ocorreu como desejado
	PAR_CondRetFaltouMemoria,
		//Nao teve memoria para criar o tabuleiro
	PAR_CondRetErroDesconhecido,
		//Houve um erro onde valores foram verificados anteriormente, entao nao deveria haver
	PAR_CondRetNinguemGanhou
		//Nao foi retornada condicao de vitoria, mesmo que o loop tenha parado (so devia parar com condição de vitoria)
} PAR_tpCondRet;

/***************************************************************

$FC Função: PAR &Ready

$ED Descrição da função
	Ela cria o tabuleiro, um vetor de cores do tipo Cor e um do tipo char e chama as funções que fazem o jogo funcionar;
	Ou seja, ela é uma preparação inical para a partida.

$FV Valor retornado
	CondRetOK			   - tudo funcionou como esperado
	CondRetFaltouMemoria   - falta de memória ao criar o tabuleiro
	CondRetNinguemGanhou   - por algum erro interno, não houve retorno de condição de vitória
	CondRetErroDesconhecido- houve um erro onde valores foram verificados anteriormente, entao nao deveria haver

***************************************************************/
PAR_tpCondRet PAR_Ready ();
