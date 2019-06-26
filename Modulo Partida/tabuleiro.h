#pragma once
//#include<stdbool.h>

typedef struct Head TAB_Head;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do tabuleiro
*
***********************************************************************/

   typedef enum {

         TAB_CondRetOK ,
            /* Concluiu corretamente */

         TAB_CondRetDestruirFalhou,
            /* Falha ao destruir */

		 TAB_CondRetVitoria,
			/* O jogo tem um vencedor */

		 TAB_CondRetNotThisTime,
			/* Ainda n�o acabou o jogo */

		 TAB_CondRetPecaBranca,
			/* Peca branca nao � peca */

	     TAB_CondRetNumDePecasInvalida,
			/* Numero de pecas invalidas */

		 TAB_CondRetTABNULL,
            /* Ponteiro para tabuleiro NULL */
			
		 TAB_CondRetNaoEstaEmJogo,
		 /* A peca ainda n�o entrou em jogo*/

		 TAB_CondRetMovimentoInvalido,
            /* Tentativa de movimento invalido */

		 TAB_CondRetNotYet,
			/* N�o tirou numero exato para por a pe�a no centro */

		 TAB_CondRetNaoMoveu,
			/* A pe�a nao foi movida */ 
		 TAB_CondRetJaTaNoFim
			/* Tentou mover uma pe�a que ja chegou no centro*/

   } TAB_tpCondRet ;

// enum da classe  pe�as 
typedef enum Cor {
	Vermelho,
	Azul,
	Amarelo,
	Verde,
	Branca
}Cor;

/***********************************************************************
*
*  $FC Fun��o: TAB  &Criar tabuleiro
*
*  $ED Descri��o da fun��o
*     Inicia o tabuleiro e aloca todas as estruturas de dados.
*
*  $FV Valor retornado
*     NULL - Ocorreu problema durante a cria��o do tabuleiro. N�o ser� dada mais informa��o quanto ao problema ocorrido.
*	  Ponteiro nao NULL - criou com sucesso.
*
***********************************************************************/
TAB_Head*  TAB_criaTabuleiro();


/***********************************************************************
*
*  $FC Fun��o: TAB  &Destroi tabuleiro
*
*  $ED Descri��o da fun��o
*     Desaloca todas as estruturas.
*
*  $EP Par�metros
*     Par�metros
*        tab - um ponteiro para um TAB_Head.
*        
*  $FV Valor retornado
*     TAB_CondRetOK - Deletou o tabuleiro sem problemas ou o tabuleiro enviado ja era NULL.
*	  OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
***********************************************************************/
TAB_tpCondRet TAB_destroiTabuleiro(TAB_Head* tab);


/***********************************************************************
*
*  $FC Fun��o: TAB  &Verifica vitoria
*
*  $ED Descri��o da fun��o
*     Verifica se a cor passada como parametro atingiu a condi��o de vitoria.
*
*  $EP Par�metros
*        tabuleiro - um ponteiro para um TAB_Head.
*        cor - cor (ou jogador) em questao a ser testado condicao de vitoria.
*        
*  $FV Valor retornado
*     TAB_CondRetVitoria - Cor enviada ganhou o jogo.
*	  TAB_CondRetNotThisTime - Cor enviada nao ganhou o jogo.
*
***********************************************************************/
TAB_tpCondRet TAB_verificaVitoria(TAB_Head* tabuleiro, Cor cor);


/***********************************************************************
*
*  $FC Fun��o: TAB  &Mover peca
*
*  $ED Descri��o da fun��o
*     Move a pe�a da cor e numero correpondente para a casa.
*
*  $EP Par�metros
*     Par�metros
*        cor - cor (ou jogador) em questao a ser movido.
*        nPe�a - peca (do jogador) em questao a ser movido.
*		 casas - n�mero e casas a mover (numero tirado no dado)
*        
*  $FV Valor retornado
*	  TAB_CondRetOK - Cor e peca enviada moveu e nao ganhou o jogo.
*	  TAB_CondRetPecaBranca - Cor enviada nao existe.
*	  TAB_CondRetNumDePecasInvalida - Peca enviada nao existe.
*	  TAB_CondRetTABNULL - Ponteiro para tabuleiro NULL.
*	  TAB_CondRetMovimentoInvalido - Tentativa de movimento invalido.
*	  TAB_CondRetNotYet - Nao tirou o numero exato para por a pe�a no centro
*	  TAB_CondRetNaoMoveu - A pe�a nao foi movida (nao diz porque) 
*
***********************************************************************/
TAB_tpCondRet TAB_moverPeca(TAB_Head* tabuleiro, Cor cor, int nPe�a ,int casas);


/***************************************************************

$FC Fun��o: TAB &showTab

$ED Descri��o da fun��o
	Mostra o estado atual do tabuleiro.

$EP Par�metros
	tabuleiro - ponteiro para o tabuleiro

$FV Valor retornado
	TAB_CondRetTABNULL - recebeu um tabuleiro nulo
	TAB_CondRetOK      - tudo certo

***************************************************************/
TAB_tpCondRet TAB_showTab (TAB_Head * tabuleiro);