/***************************************************************************
*  $MCI M�dulo de implementa��o: LIC  Lista circular duplamente encadeada
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

#ifdef _DEBUG
   #include   "Generico.h"
   #include   "Conta.h"
#endif

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
*  $TC Tipo de dados: LIC Descritor da cabe�a de lista
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
               /* N�mero de elementos da lista */

         void ( * ExcluirValor ) ( void * palor ) ;
               /* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */

   } LIC_tLista ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void LiberarElemento( LIC_Lista   Lista, ElemLista * Elem ) ;

   static ElemLista * CriarElemento( LIC_Lista Lista, void * Valor ) ;

   static LIC_CondRet LimparCabeca( LIC_Lista Lista ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/*==========================================================*/

/*  Fun��o: LIC  &Criar lista*/

   LIC_Lista LIC_CriarLista( void   ( * ExcluirValor ) ( void * Dado ) )
   {
	  LIC_tLista * Lista = NULL ;

	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_CriarLista" ) ;
      #endif

      Lista = ( LIC_tLista * ) malloc( sizeof( LIC_tLista )) ;
      if ( Lista == NULL )
      {
         return NULL ;
      } /* if */

      LimparCabeca( Lista ) ;

      Lista->ExcluirValor = ExcluirValor ;

      return Lista ;

   } /* Fim fun��o: LIC  &Criar lista */

/*==========================================================*/

/*  Fun��o: LIC  &Destruir lista*/

   LIC_CondRet LIC_DestruirLista( LIC_Lista Lista )
   {
	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_DestruirLista" ) ;
      #endif

      if (Lista==NULL){
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	  }

      LIC_EsvaziarLista( Lista ) ;

      free( Lista ) ;

   } /* Fim fun��o: LIC  &Destruir lista */

/*==========================================================*/

/*	Fun��o: LIC  &Esvaziar lista*/

   LIC_CondRet LIC_EsvaziarLista( LIC_Lista Lista )
   {
	   

      ElemLista * Elem ;
      ElemLista * Prox ;

	  #ifdef _DEBUG
         CNT_CONTAR( "LIC_EsvaziarLista" ) ;
      #endif

      if (Lista==NULL){
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	  }

      if (Lista->numElem == 0){
		 LimparCabeca(Lista);
		 return;
	  }

      Elem = Lista->Origem ;
	  do
      {
         Prox = Elem->Prox ;
         LiberarElemento( Lista , Elem );
		 if (Lista->numElem == 0){
			 LimparCabeca(Lista);
			 return;
		 }
         Elem = Prox ;
      }while ( Elem->Prox != Lista->Origem );

      LimparCabeca( Lista ) ;
	  return;

   } /* Fim fun��o: LIS  &Esvaziar lista */

/*==========================================================*/

/*	Fun��o: LIC  &Inserir elemento antes*/

   LIC_CondRet LIC_InserirAntes( LIC_Lista Lista, void * Valor )
   {
	  ElemLista * Elem ;

	    #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirAntes" ) ;
      #endif

      if (Lista==NULL){
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	  }

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
			} 
         }

         Lista->ElemCorr = Elem ;

         return LIC_CondRetOK ;

   } /* Fim fun��o: LIC  &Inserir elemento antes */

/*==========================================================*/

/*	Fun��o: LIC  &Inserir elemento ap�s */

   LIC_CondRet LIC_InserirApos( LIC_Lista Lista , void * Valor  )
      
   {
	  ElemLista * Elem ;

	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirApos" ) ;
      #endif

      if (Lista==NULL){
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	  }

      /* Criar elemento a inerir ap�s */

         Elem = CriarElemento( Lista , Valor ) ;
         if ( Elem == NULL )
         {
            return LIC_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento ap�s o elemento */

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

   } /* Fim fun��o: LIC  &Inserir elemento ap�s */

/*==========================================================*/

/*  Fun��o: LIS  &Excluir elemento*/

   LIC_CondRet LIC_ExcluirElemento( LIC_Lista Lista )
   {
      ElemLista * Elem ;

	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_ExcluirElemento" ) ;
      #endif

      if (Lista==NULL){
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	  }

      if ( Lista->ElemCorr == NULL )
      {
         return LIC_CondRetListaVazia ;
      } /* if */

      Elem = Lista->ElemCorr ;

	  if ( Elem->Ant == Lista->Fim )
	  {
		  Lista->Origem = Elem->Prox;
	  }
	  if ( Elem->Prox == Lista->Origem){
		  Lista->Fim = Elem->Ant;
	  }

	  Elem->Ant->Prox = Elem->Prox;
	  Elem->Prox->Ant = Elem->Ant;
	  
	  Lista->ElemCorr = Elem->Prox;

	  LiberarElemento( Lista , Elem );

	  if(Lista->numElem == 0){
		  Lista->ElemCorr = NULL;
		  Lista->Origem = NULL;
		  Lista->Fim = NULL;
	  }
      return LIC_CondRetOK ;

   } /* Fim fun��o: LIC  &Excluir elemento */

/*==========================================================*/

/*  Fun��o: LIC  &Obter refer�ncia para o valor contido no elemento*/

   void * LIC_ObterValor( LIC_Lista Lista )
   {
	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_ObterValor" ) ;
      #endif

      if (Lista==NULL){
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	  }

      if ( Lista->ElemCorr == NULL )
      {
        return NULL ;
      } /* if */

      return Lista->ElemCorr->Valor ;

   } /* Fim fun��o: LIC  &Obter refer�ncia para o valor contido no elemento */

/*==========================================================*/

/*  Fun��o: LIC  &Ir para o elemento inicial*/

   LIC_CondRet LIC_IrInicioLista( LIC_Lista Lista )
   {
	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_IrInicioLista" ) ;
      #endif

      if (Lista==NULL){
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	  }

      Lista->ElemCorr = Lista->Origem ;

   } /* Fim fun��o: LIC  &Ir para o elemento inicial */

/*==========================================================*/

/*  Fun��o: LIC  &Ir para o elemento final*/

   LIC_CondRet LIC_IrFinalLista( LIC_Lista Lista )
   {
	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_IrFinalLista" ) ;
      #endif

      if (Lista==NULL){
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	  }

      Lista->ElemCorr = Lista->Fim ;

   } /* Fim fun��o: LIC  &Ir para o elemento final */

/*==========================================================*/

/*  Fun��o: LIC  &Avan�ar elemento*/

   LIC_CondRet LIC_Avancar( LIC_Lista Lista, int x )
   {
	  int i ;

      ElemLista * Elem ;

	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_Avancar" ) ;
      #endif

      if (Lista==NULL){
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	  }

      /* Tratar lista vazia */

         if ( Lista->ElemCorr == NULL )
         {

            return LIC_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

	  /* Tratar elemento �nico */
		 
		 if(Lista->Fim == Lista->Origem){

			 return LIC_CondRetOK;

		 }/* fim ativa: Tratar elemento �nico */

      /* Tratar avan�ar para frente */

         if ( x > 0 )
         {

            Elem = Lista->ElemCorr ;
            for( i = x ; i > 0 ; i-- )
            {
               Elem = Elem->Prox ;
            } /* for */

            Lista->ElemCorr = Elem ;
            return LIC_CondRetOK ;


         } /* fim ativa: Tratar avan�ar para frente */

      /* Tratar avan�ar para tr�s */

         else if ( x < 0 )
         {

            Elem = Lista->ElemCorr ;
            for( i = x ; i < 0 ; i++ )
            {
               Elem = Elem->Ant ;
            } /* for */

            Lista->ElemCorr = Elem ;
            return LIC_CondRetOK ;

         } /* fim ativa: Tratar avan�ar para tr�s */

      /* Tratar n�o avan�ar (x==0)*/

         return LIC_CondRetOK ;

   } /* Fim fun��o: LIC  &Avan�ar elemento */

/*==========================================================*/

/*  Fun��o: LIC  &Procurar elemento contendo valor*/

   LIC_CondRet LIC_ProcurarValor( LIC_Lista Lista , void * Valor )
   {
	  ElemLista * Elem ;
	  int n =0;

	     #ifdef _DEBUG
         CNT_CONTAR( "LIC_ProcurarValor" ) ;
      #endif

      if (Lista==NULL){
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	  }

      if ( Lista->ElemCorr == NULL )
      {
         return LIC_CondRetListaVazia ;
      } /* if */
	  Elem = Lista->ElemCorr;
	  
	  while(n!=Lista->numElem){
		 if ( Elem->Valor == Valor )
		 {
			 Lista->ElemCorr = Elem ;
			 return LIC_CondRetOK ;
		 } 
		 Elem=Elem->Prox;
		 n++;		  
	  }

      return LIC_CondRetNaoAchou ;

   } /* Fim fun��o: LIC  &Procurar elemento contendo valor */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: LIC  -Liberar elemento da lista
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*  $EP Par�metros
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

   } /* Fim fun��o: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Fun��o: LIC  -Criar o elemento
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

   } /* Fim fun��o: LIC  -Criar o elemento */


/***********************************************************************
*
*  $FC Fun��o: LIC  -Limpar a cabe�a da lista
*
***********************************************************************/

   LIC_CondRet LimparCabeca( LIC_Lista Lista )
   {
       if ( Lista == NULL )
      {
         return LIC_CondRetListaVazia ;
      } 
      Lista->Origem = NULL ;
      Lista->Fim = NULL ;
      Lista->ElemCorr = NULL ;
      Lista->numElem   = 0 ;

   } /* Fim fun��o: LIC  -Limpar a cabe�a da lista */

/********** Fim do m�dulo de implementa��o: LIC  Lista circular duplamente encadeada **********/

