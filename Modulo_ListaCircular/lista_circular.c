/***************************************************************************
*  $MCI Módulo de implementação: LIC  Lista circular duplamente encadeada
*
*  Arquivo gerado:              lista_circular.c
*  Letras identificadoras:      LIC
*
*  Projeto: INF 1301 / T2
*  Autores: Giulia Mahovlic
*
***************************************************************************/

#include	<stdio.h>
#include	<string.h>
#include	<memory.h>
#include	<malloc.h>
#include	<assert.h>

#define listac_OWN
#include	"lista_circular.h"
#undef listac_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIC Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         void * Valor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * Prox ;
               /* Ponteiro para o elemento sucessor */
		 
         struct tagElemLista * Ant ;
               /* Ponteiro para o elemento antecessor */

   } ElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIC Descritor da cabeça de lista
*
*
***********************************************************************/

   typedef struct LIC_tagLista {

         ElemLista * Origem ;
               /* Ponteiro para a origem da lista */

         ElemLista * Fim ;
               /* Ponteiro para o final da lista */

         ElemLista * ElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Número de elementos da lista */

         void ( * ExcluirValor ) ( void * palor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } LIC_tLista ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( LIC_Lista   Lista, ElemLista * Elem ) ;

   static ElemLista * CriarElemento( LIC_Lista Lista, void * Valor ) ;

   static void LimparCabeca( LIC_Lista Lista ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/*==========================================================*/

/*  Função: LIC  &Criar lista*/

   LIC_Lista LIC_CriarLista( void   ( * ExcluirValor ) ( void * Dado ) )
   {

      LIC_tLista * Lista = NULL ;

      Lista = ( LIC_tLista * ) malloc( sizeof( LIC_tLista )) ;
      if ( Lista == NULL )
      {
         return NULL ;
      } /* if */

      LimparCabeca( Lista ) ;

      Lista->ExcluirValor = ExcluirValor ;

      return Lista ;

   } /* Fim função: LIC  &Criar lista */

/*==========================================================*/

/*  Função: LIC  &Destruir lista*/

   void LIC_DestruirLista( LIC_Lista Lista )
   {

      #ifdef _DEBUG
         assert( Lista != NULL ) ;
      #endif

      LIC_EsvaziarLista( Lista ) ;

      free( Lista ) ;

   } /* Fim função: LIC  &Destruir lista */

/*==========================================================*/

/*	Função: LIC  &Esvaziar lista*/

   void LIC_EsvaziarLista( LIC_Lista Lista )
   {

      ElemLista * Elem ;
      ElemLista * Prox ;

      #ifdef _DEBUG
         assert( Lista != NULL ) ;
      #endif

      Elem = Lista->Origem ;
	  while ( Elem->Prox != Lista->Origem )
      {
         Prox = Elem->Prox ;
         LiberarElemento( Lista , Elem ) ;
         Elem = Prox ;
      } /* while */

      LimparCabeca( Lista ) ;

   } /* Fim função: LIS  &Esvaziar lista */

/*==========================================================*/

/*	Função: LIC  &Inserir elemento antes*/

   LIC_CondRet LIC_InserirAntes( LIC_Lista Lista, void * Valor )
   {

      ElemLista * Elem ;

      #ifdef _DEBUG
         assert( Lista != NULL ) ;
      #endif

      /* Criar elemento a inerir antes */

         Elem = CriarElemento( Lista , Valor ) ;
         if ( Elem == NULL )
         {
            return LIC_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */

         if ( Lista->ElemCorr == NULL )
         {
			 Elem->Ant = Elem;
			 Elem->Prox = Elem;
			 Lista->Origem = Elem ;
             Lista->Fim = Elem ;
         } else
         {
            Elem->Ant  = Lista->ElemCorr->Ant ;
            Lista->ElemCorr->Ant->Prox = Elem ;
            Elem->Prox = Lista->ElemCorr ;
            Lista->ElemCorr->Ant = Elem ;

			if ( Elem->Ant == Lista->Fim )
			{
				Lista->Origem = Elem;
			} /* if */
         } /* if */

         Lista->ElemCorr = Elem ;

         return LIC_CondRetOK ;

   } /* Fim função: LIC  &Inserir elemento antes */

/*==========================================================*/

/*	Função: LIC  &Inserir elemento após */

   LIC_CondRet LIC_InserirApos( LIC_Lista Lista , void * Valor  )
      
   {

      ElemLista * Elem ;

      #ifdef _DEBUG
         assert( Lista != NULL ) ;
      #endif

      /* Criar elemento a inerir após */

         Elem = CriarElemento( Lista , Valor ) ;
         if ( Elem == NULL )
         {
            return LIC_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento após o elemento */

         if ( Lista->ElemCorr == NULL )
         {
			 Elem->Ant = Elem;
			 Elem->Prox = Elem;
			 Lista->Origem = Elem ;
             Lista->Fim = Elem ;
         } else
         {
            Elem->Prox  = Lista->ElemCorr->Prox ;
            Lista->ElemCorr->Prox->Ant = Elem ;
            Elem->Ant = Lista->ElemCorr ;
            Lista->ElemCorr->Prox = Elem ;
			
			if ( Elem->Prox == Lista->Origem )
			{
				Lista->Fim = Elem;
			} /* if */
         } /* if */
                  
         Lista->ElemCorr = Elem ;
                  
         return LIC_CondRetOK ;

   } /* Fim função: LIC  &Inserir elemento após */

/*==========================================================*/

/*  Função: LIS  &Excluir elemento*/

   LIC_CondRet LIC_ExcluirElemento( LIC_Lista Lista )
   {

      ElemLista * Elem ;

      #ifdef _DEBUG
         assert( Lista  != NULL ) ;
      #endif

      if ( Lista->ElemCorr == NULL )
      {
         return LIC_CondRetListaVazia ;
      } /* if */

      Elem = Lista->ElemCorr ;

      /* Desencadeia à esquerda */

	  if ( Elem->Ant == Lista->Fim )
	  {
		  Lista->Origem = Elem->Prox;
	  }
	  if ( Elem->Prox == Lista->Origem){
		  Lista->Fim == Elem->Ant;
	  }

	  Elem->Ant->Prox = Elem->Prox;
	  Elem->Prox->Ant = Elem->Ant;
	  
	  Lista->ElemCorr = Elem->Prox;

      LiberarElemento( Lista , Elem ) ;

      return LIC_CondRetOK ;

   } /* Fim função: LIC  &Excluir elemento */

/*==========================================================*/

/*  Função: LIC  &Obter referência para o valor contido no elemento*/

   void * LIC_ObterValor( LIC_Lista Lista )
   {

      #ifdef _DEBUG
         assert( Lista != NULL ) ;
      #endif

      if ( Lista->ElemCorr == NULL )
      {
        return NULL ;
      } /* if */

      return Lista->ElemCorr->Valor ;

   } /* Fim função: LIC  &Obter referência para o valor contido no elemento */

/*==========================================================*/

/*  Função: LIC  &Ir para o elemento inicial*/

   void LIC_IrInicioLista( LIC_Lista Lista )
   {

      #ifdef _DEBUG
         assert( Lista != NULL ) ;
      #endif

      Lista->ElemCorr = Lista->Origem ;

   } /* Fim função: LIC  &Ir para o elemento inicial */

/*==========================================================*/

/*  Função: LIC  &Ir para o elemento final*/

   void LIC_IrFinalLista( LIC_Lista Lista )
   {

      #ifdef _DEBUG
         assert( Lista != NULL ) ;
      #endif

      Lista->ElemCorr = Lista->Fim ;

   } /* Fim função: LIC  &Ir para o elemento final */

/*==========================================================*/

/*  Função: LIC  &Avançar elemento*/

   LIC_CondRet LIC_Avancar( LIC_Lista Lista, int x )
   {

      int i ;

      ElemLista * Elem ;

      #ifdef _DEBUG
         assert( Lista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( Lista->ElemCorr == NULL )
         {

            return LIC_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

	  /* Tratar elemento único */
		 
		 if(Lista->Fim == Lista->Origem){

			 return LIC_CondRetOK;

		 }/* fim ativa: Tratar elemento único */

      /* Tratar avançar para frente */

         if ( x > 0 )
         {

            Elem = Lista->ElemCorr ;
            for( i = x ; i > 0 ; i-- )
            {
               Elem = Elem->Prox ;
            } /* for */

            Lista->ElemCorr = Elem ;
            return LIC_CondRetOK ;


         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

         else if ( x < 0 )
         {

            Elem = Lista->ElemCorr ;
            for( i = x ; i < 0 ; i++ )
            {
               Elem = Elem->Ant ;
            } /* for */

            Lista->ElemCorr = Elem ;
            return LIC_CondRetOK ;

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar (x==0)*/

         return LIC_CondRetOK ;

   } /* Fim função: LIC  &Avançar elemento */

/*==========================================================*/

/*  Função: LIC  &Procurar elemento contendo valor*/

   LIC_CondRet LIC_ProcurarValor( LIC_Lista Lista , void * Valor )
   {

      ElemLista * Elem ;

      #ifdef _DEBUG
         assert( Lista  != NULL ) ;
      #endif

      if ( Lista->ElemCorr == NULL )
      {
         return LIC_CondRetListaVazia ;
      } /* if */

	  do
      {
         if ( Elem->Valor == Valor )
         {
            Lista->ElemCorr = Elem ;
            return LIC_CondRetOK ;
         } /* if */
		 Elem=Elem->Prox;
	  } while(Elem != Lista->ElemCorr->Ant);

      return LIC_CondRetNaoAchou ;

   } /* Fim função: LIC  &Procurar elemento contendo valor */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIC  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*  $EP Parâmetros
*	  Lista - ponteiro para a lista que contem o elemento a ser liberado
*     Elem  - ponteiro para o elemento a ser liberado
*
***********************************************************************/

   void LiberarElemento( LIC_Lista   Lista, ElemLista  * Elem   )
   {

      if ( ( Lista->ExcluirValor != NULL )  &&  ( Elem->Valor != NULL ) )
      {
         Lista->ExcluirValor( Elem->Valor ) ;
      } /* if */

      free( Elem ) ;

      Lista->numElem-- ;

   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIC  -Criar o elemento
*
***********************************************************************/

   ElemLista * CriarElemento( LIC_Lista Lista, void * Valor  )
   {

      ElemLista * Elem ;

      Elem = ( ElemLista * ) malloc( sizeof( ElemLista )) ;
      if ( Elem == NULL )
      {
         return NULL ;
      } /* if */

      Elem->Valor = Valor ;
      Elem->Ant   = NULL  ;
      Elem->Prox  = NULL  ;

      Lista->numElem ++ ;

      return Elem ;

   } /* Fim função: LIC  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIC  -Limpar a cabeça da lista
*
***********************************************************************/

   void LimparCabeca( LIC_Lista Lista )
   {

      Lista->Origem = NULL ;
      Lista->Fim = NULL ;
      Lista->ElemCorr = NULL ;
      Lista->numElem   = 0 ;

   } /* Fim função: LIC  -Limpar a cabeça da lista */

/********** Fim do módulo de implementação: LIC  Lista circular duplamente encadeada **********/

