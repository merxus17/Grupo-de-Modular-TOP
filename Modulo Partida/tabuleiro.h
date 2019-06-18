#pragma once
//#include<stdbool.h>

typedef struct Head TAB_Head;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do tabuleiro
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
			/* Ainda não acabou o jogo */

		 TAB_CondRetPecaBranca,
			/* Peca branca nao é peca */

	     TAB_CondRetNumDePecasInvalida,
			/* Numero de pecas invalidas */

		 TAB_CondRetTABNULL,
            /* Ponteiro para tabuleiro NULL */
			
		 TAB_CondRetNaoEstaEmJogo,
		 /* A peca ainda não entrou em jogo*/

		 TAB_CondRetMovimentoInvalido,
            /* Tentativa de movimento invalido */

		 TAB_CondRetNotYet,
			/* Não tirou numero exato para por a peça no centro */

		 TAB_CondRetNaoMoveu,
			/* A peça nao foi movida */ 
		 TAB_CondRetJaTaNoFim
			/* Tentou mover uma peça que ja chegou no centro*/

   } TAB_tpCondRet ;

// enum da classe  peças 
typedef enum Cor {
	Vermelho,
	Azul,
	Amarelo,
	Verde,
	Branca
}Cor;

/***********************************************************************
*
*  $FC Função: TAB  &Criar tabuleiro
*
*  $ED Descrição da função
*     Inicia o tabuleiro e aloca todas as estruturas de dados.
*
*  $FV Valor retornado
*     NULL - Ocorreu problema durante a criação do tabuleiro. Não será dada mais informação quanto ao problema ocorrido.
*	  Ponteiro nao NULL - criou com sucesso.
*
***********************************************************************/
TAB_Head*  TAB_criaTabuleiro();


/***********************************************************************
*
*  $FC Função: TAB  &Destroi tabuleiro
*
*  $ED Descrição da função
*     Desaloca todas as estruturas.
*
*  $EP Parâmetros
*     Parâmetros
*        tab - um ponteiro para um TAB_Head.
*        
*  $FV Valor retornado
*     TAB_CondRetOK - Deletou o tabuleiro sem problemas ou o tabuleiro enviado ja era NULL.
*	  OBS. não existe previsão para possíveis falhas de execução.
*
***********************************************************************/
TAB_tpCondRet TAB_destroiTabuleiro(TAB_Head* tab);


/***********************************************************************
*
*  $FC Função: TAB  &Verifica vitoria
*
*  $ED Descrição da função
*     Verifica se a cor passada como parametro atingiu a condição de vitoria.
*
*  $EP Parâmetros
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
*  $FC Função: TAB  &Mover peca
*
*  $ED Descrição da função
*     Move a peça da cor e numero correpondente para a casa.
*
*  $EP Parâmetros
*     Parâmetros
*        cor - cor (ou jogador) em questao a ser movido.
*        nPeça - peca (do jogador) em questao a ser movido.
*		 casas - número e casas a mover (numero tirado no dado)
*        
*  $FV Valor retornado
*	  TAB_CondRetOK - Cor e peca enviada moveu e nao ganhou o jogo.
*	  TAB_CondRetPecaBranca - Cor enviada nao existe.
*	  TAB_CondRetNumDePecasInvalida - Peca enviada nao existe.
*	  TAB_CondRetTABNULL - Ponteiro para tabuleiro NULL.
*	  TAB_CondRetMovimentoInvalido - Tentativa de movimento invalido.
*	  TAB_CondRetNotYet - Nao tirou o numero exato para por a peça no centro
*	  TAB_CondRetNaoMoveu - A peça nao foi movida (nao diz porque) 
*
***********************************************************************/
TAB_tpCondRet TAB_moverPeca(TAB_Head* tabuleiro, Cor cor, int nPeça ,int casas);


/***************************************************************

$FC Função: TAB &showTab

$ED Descrição da função
	Mostra o estado atual do tabuleiro.

$EP Parâmetros
	tabuleiro - ponteiro para o tabuleiro

***************************************************************/
void TAB_showTab (TAB_Head * tabuleiro);