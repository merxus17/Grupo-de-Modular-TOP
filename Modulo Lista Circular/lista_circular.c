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
         CNT_CONTAR( "LIC_CriarLista-Inicio" ) ;
      #endif

      Lista = ( LIC_tLista * ) malloc( sizeof( LIC_tLista )) ;
      if ( Lista == NULL )
      {
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_CriarLista- MEMORIA  , settar -2" ) ;
      #endif
         return NULL ;
      } /* if */
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_CriarLista-Antes-Limpa-Cabeça" ) ;
      #endif
      LimparCabeca( Lista ) ;
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_CriarLista-Depois-Limpa-Cabeça" ) ;
      #endif
      Lista->ExcluirValor = ExcluirValor ;
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_CriarLista-Return" ) ;
      #endif
      return Lista ;

   } /* Fim fun��o: LIC  &Criar lista */

/*==========================================================*/

/*  Fun��o: LIC  &Destruir lista*/

   LIC_CondRet LIC_DestruirLista( LIC_Lista Lista )
   {
      if (Lista==NULL)
      {
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_DestruirLista - Inicio" ) ;
      #endif
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	   }
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_DestruirLista - Antes EsvaziarLista " ) ;
      #endif
      free( Lista ) ;
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_DestruirLista - Depois EsvaziarLista" ) ;
      #endif
      return LIC_CondRetOK;
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

      if (Lista == NULL)
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIC_EsvaziarLista- if null" ) ;
         #endif
         printf("\nLista vazia\n");
         return LIC_CondRetListaVazia;
	   }
        #ifdef _DEBUG
         CNT_CONTAR( "LIC_EsvaziarLista - antes do if numElem" ) ;
         #endif
      if (Lista->numElem == 0)
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_EsvaziarLista - antes limpar cabeça" ) ;
         #endif
		    LimparCabeca(Lista);
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_EsvaziarLista - depois limpar cabeça " ) ;
         #endif
		   return LIC_CondRetListaVazia;
	  }
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_EsvaziarLista - elem = lista origem " ) ;
      #endif
      Elem = Lista->Origem ;
	  do
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_EsvaziarLista dentro do do  " ) ;
         #endif
         Prox = Elem->Prox ;
         LiberarElemento( Lista , Elem );
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_EsvaziarLista - LiberarElemento " ) ;
         #endif
		 if (Lista->numElem == 0)
       {
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_EsvaziarLista - antes de limpar cabeça 1 " ) ;
         #endif
			 LimparCabeca(Lista);
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_EsvaziarLista - depois do limpa cabeça 1 " ) ;
         #endif
			 return LIC_CondRetOK;
		 }
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_EsvaziarLista - elem = prox " ) ;
      #endif
         Elem = Prox ;
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_EsvaziarLista - while " ) ;
      #endif
      }while ( Elem->Prox != Lista->Origem );
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_EsvaziarLista - antes limpar cabeça 2 " ) ;
      #endif
      LimparCabeca( Lista ) ;
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_EsvaziarLista  - depois limpar cabeça 2 " ) ;
      #endif
	  return LIC_CondRetOK;;

   } /* Fim fun��o: LIS  &Esvaziar lista */

/*==========================================================*/

/*	Fun��o: LIC  &Inserir elemento antes*/

   LIC_CondRet LIC_InserirAntes( LIC_Lista Lista, void * Valor )
   {
	  ElemLista * Elem ;

	    #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirAntes - inicio" ) ;
      #endif

      if (Lista==NULL){
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirAntes - lista == null " ) ;
         #endif
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	  }

      /* Criar elemento a inerir antes */
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirAntes - antes cria elemento  " ) ;
      #endif
         Elem = CriarElemento( Lista , Valor ) ;
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirAntes -  depois cria elemento" ) ;
      #endif
         if ( Elem == NULL )
         {
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirAntes - MEMORIA" ) ;
         #endif
            return LIC_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirAntes - lista-> elemcorr == null" ) ;
      #endif
         if ( Lista->ElemCorr == NULL )
         {
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirAntes - dentro lista-> elemcorr == null" ) ;
         #endif
			 Elem->Ant = Elem;
			 Elem->Prox = Elem;
			 Lista->Origem = Elem ;
             Lista->Fim = Elem ;
         } else
         {
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirAntes - dentro else" ) ;
         #endif
            Elem->Ant  = Lista->ElemCorr->Ant ;
            Lista->ElemCorr->Ant->Prox = Elem ;
            Elem->Prox = Lista->ElemCorr ;
            Lista->ElemCorr->Ant = Elem ;
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirAntes - antes elem->ant == Lista->fim" ) ;
         #endif
			if ( Elem->Ant == Lista->Fim )
			{
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirAntes - dentro elem->ant == Lista->fim" ) ;
         #endif
				Lista->Origem = Elem;
			} 
         }
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirAntes - antes lista->elemeCorr = elem" ) ;
         #endif
         Lista->ElemCorr = Elem ;
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirAntes - depois lista->elemeCorr = elem" ) ;
         #endif
         return LIC_CondRetOK ;

   } /* Fim fun��o: LIC  &Inserir elemento antes */

/*==========================================================*/

/*	Fun��o: LIC  &Inserir elemento ap�s */

   LIC_CondRet LIC_InserirApos( LIC_Lista Lista , void * Valor  )  
   {
	  ElemLista * Elem ;

	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirApos - inicio" ) ;
      #endif

      if (Lista==NULL)
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirApos - LISTA == NULL" ) ;
         #endif
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	   }

      /* Criar elemento a inerir ap�s */
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirApos - antes cria elemento" ) ;
      #endif
         Elem = CriarElemento( Lista , Valor ) ;
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirApos - depois cria elemento" ) ;
      #endif
         if ( Elem == NULL )
         {
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirApos - MEMORIA" ) ;
         #endif
            return LIC_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento ap�s o elemento */
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirApos - lista -> elemcorr == null" ) ;
         #endif
         if ( Lista->ElemCorr == NULL )
         {
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirApos - depois lista -> elemcorr == null" ) ;
         #endif
			 Elem->Ant = Elem;
			 Elem->Prox = Elem;
			 Lista->Origem = Elem ;
             Lista->Fim = Elem ;
         } else
         {
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirApos - dentro do else" ) ;
         #endif
            Elem->Prox  = Lista->ElemCorr->Prox ;
            Lista->ElemCorr->Prox->Ant = Elem ;
            Elem->Ant = Lista->ElemCorr ;
            Lista->ElemCorr->Prox = Elem ;
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirApos - antes Elem->Prox == Lista->Origem" ) ;
         #endif
			if ( Elem->Prox == Lista->Origem )
			{
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirApos - dentro Elem->Prox == Lista->Origem" ) ;
         #endif
				Lista->Fim = Elem;
			} /* if */
         } /* if */
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirApos - antes Lista->ElemCorr = Elem" ) ;
         #endif   
         Lista->ElemCorr = Elem ;
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_InserirApos - depois Lista->ElemCorr = Elem" ) ;
         #endif  
         return LIC_CondRetOK ;

   } /* Fim fun��o: LIC  &Inserir elemento ap�s */

/*==========================================================*/

/*  Fun��o: LIS  &Excluir elemento*/

   LIC_CondRet LIC_ExcluirElemento( LIC_Lista Lista )
   {
      ElemLista * Elem ;

	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_ExcluirElemento - Inicio" ) ;
      #endif

      if (Lista==NULL)
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_ExcluirElemento - Lista == NULL" ) ;
         #endif
		   printf("\nLista vazia\n");
		   return LIC_CondRetListaVazia;
	   }
      #ifdef _DEBUG
      CNT_CONTAR( "LIC_ExcluirElemento - antes Lista->ElemCorr == NULL" ) ;
      #endif
      if ( Lista->ElemCorr == NULL )
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_ExcluirElemento - dentro Lista->ElemCorr == NULL" ) ;
         #endif
         return LIC_CondRetListaVazia ;
      } /* if */
      #ifdef _DEBUG
      CNT_CONTAR( "LIC_ExcluirElemento - antes Elem = Lista->ElemCorr" ) ;
      #endif
      Elem = Lista->ElemCorr ;
      #ifdef _DEBUG
      CNT_CONTAR( "LIC_ExcluirElemento - depois Elem = Lista->ElemCorr" ) ;
      #endif
	  if ( Elem->Ant == Lista->Fim )
	  {
      #ifdef _DEBUG
      CNT_CONTAR( "LIC_ExcluirElemento - dentro Elem->Ant == Lista->Fim" ) ;
      #endif
		  Lista->Origem = Elem->Prox;
	  }
      #ifdef _DEBUG
      CNT_CONTAR( "LIC_ExcluirElemento - depois Elem->Prox == Lista->Origem" ) ;
      #endif
	  if ( Elem->Prox == Lista->Origem)
     {
      #ifdef _DEBUG
      CNT_CONTAR( "LIC_ExcluirElemento - dentro Elem->Prox == Lista->Origem" ) ;
      #endif
		  Lista->Fim = Elem->Ant;
	  }
      #ifdef _DEBUG
      CNT_CONTAR( "LIC_ExcluirElemento - antes Elem->Ant->Prox = Elem->Prox" ) ;
      #endif
	  Elem->Ant->Prox = Elem->Prox;
	  Elem->Prox->Ant = Elem->Ant;
	  
	  Lista->ElemCorr = Elem->Prox;
      #ifdef _DEBUG
      CNT_CONTAR( "LIC_ExcluirElemento - antes LiberarElemento" ) ;
      #endif
	  LiberarElemento( Lista , Elem );
      #ifdef _DEBUG
      CNT_CONTAR( "LIC_ExcluirElemento - depois LiberarElemento" ) ;
      #endif
	  if(Lista->numElem == 0)
     {
      #ifdef _DEBUG
      CNT_CONTAR( "LIC_ExcluirElemento - dentro Lista->numElem == 0" ) ;
      #endif
		  Lista->ElemCorr = NULL;
		  Lista->Origem = NULL;
		  Lista->Fim = NULL;
	  }
      #ifdef _DEBUG
      CNT_CONTAR( "LIC_ExcluirElemento - return" ) ;
      #endif
      return LIC_CondRetOK ;

   } /* Fim fun��o: LIC  &Excluir elemento */

/*==========================================================*/

/*  Fun��o: LIC  &Obter refer�ncia para o valor contido no elemento*/

   void * LIC_ObterValor( LIC_Lista Lista )
   {
      if (Lista==NULL)
      {
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_ObterValor - Inicio" ) ;
      #endif
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	   }
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_ObterValor - antes Lista->ElemCorr == NULL " ) ;
      #endif
      if ( Lista->ElemCorr == NULL )
      {
               #ifdef _DEBUG
         CNT_CONTAR( "LIC_ObterValor - dentro Lista->ElemCorr == NULL " ) ;
      #endif
        return NULL ;
      } /* if */
            #ifdef _DEBUG
         CNT_CONTAR( "LIC_ObterValor - return " ) ;
      #endif
      return Lista->ElemCorr->Valor ;

   } /* Fim fun��o: LIC  &Obter refer�ncia para o valor contido no elemento */

/*==========================================================*/

/*  Fun��o: LIC  &Ir para o elemento inicial*/

   LIC_CondRet LIC_IrInicioLista( LIC_Lista Lista )
   {


      if (Lista==NULL)
      {
         	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_IrInicioLista - inicio" ) ;
      #endif
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	   }
	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_IrInicioLista - antes Lista->ElemCorr = Lista->Origem" ) ;
      #endif
      Lista->ElemCorr = Lista->Origem ;
	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_IrInicioLista - return" ) ;
      #endif
      return LIC_CondRetOK;

   } /* Fim fun��o: LIC  &Ir para o elemento inicial */

/*==========================================================*/

/*  Fun��o: LIC  &Ir para o elemento final*/

   LIC_CondRet LIC_IrFinalLista( LIC_Lista Lista )
   {


      if (Lista==NULL)
      {
 	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_IrFinalLista- Inicio" ) ;
      #endif        
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	   }
	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_IrFinalLista - antes Lista->ElemCorr = Lista->Fim " ) ;
      #endif
      Lista->ElemCorr = Lista->Fim ;
      	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_IrFinalLista - return " ) ;
      #endif
      return LIC_CondRetOK;
   } /* Fim fun��o: LIC  &Ir para o elemento final */

/*==========================================================*/

/*  Fun��o: LIC  &Avan�ar elemento*/

   LIC_CondRet LIC_Avancar( LIC_Lista Lista, int x )
   {
	  int i ;

      ElemLista * Elem ;

	   #ifdef _DEBUG
         CNT_CONTAR( "LIC_Avancar - Inicio" ) ;
      #endif

      if (Lista==NULL)
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_Avancar - Lista==NULL" ) ;
         #endif
		   printf("\nLista vazia\n");
		   return LIC_CondRetListaVazia;
	   }

      /* Tratar lista vazia */
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_Avancar - antes Lista->ElemCorr == NULL " ) ;
         #endif
         if ( Lista->ElemCorr == NULL )
         {
            #ifdef _DEBUG
            CNT_CONTAR( "LIC_Avancar - dentro Lista->ElemCorr == NULL " ) ;
            #endif
            return LIC_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

	  /* Tratar elemento �nico */
      #ifdef _DEBUG
      CNT_CONTAR( "LIC_Avancar - antes Lista->Fim == Lista->Origem " ) ;
      #endif
		 if(Lista->Fim == Lista->Origem)
       {
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_Avancar - dentro Lista->Fim == Lista->Origem " ) ;
         #endif
			return LIC_CondRetOK;

		 }/* fim ativa: Tratar elemento �nico */

      /* Tratar avan�ar para frente */
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_Avancar - antes x > 0 " ) ;
         #endif
         if ( x > 0 )
         {
            #ifdef _DEBUG
            CNT_CONTAR( "LIC_Avancar - dentro x > 0 " ) ;
            #endif
            Elem = Lista->ElemCorr ;
            for( i = x ; i > 0 ; i-- )
            {
               #ifdef _DEBUG
               CNT_CONTAR( "LIC_Avancar - dentro for( i = x ; i > 0 ; i-- )" ) ;
               #endif
               Elem = Elem->Prox ;
            } /* for */
            #ifdef _DEBUG
            CNT_CONTAR( "LIC_Avancar - depois for( i = x ; i > 0 ; i-- )" ) ;
            #endif
            Lista->ElemCorr = Elem ;
            #ifdef _DEBUG
               CNT_CONTAR( "LIC_Avancar - return if ( x > 0 )" ) ;
            #endif
            return LIC_CondRetOK ;


         } /* fim ativa: Tratar avan�ar para frente */

      /* Tratar avan�ar para tr�s */
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_Avancar - antes else if (x<0)" ) ;
         #endif
         else if ( x < 0 )
         {
            #ifdef _DEBUG
            CNT_CONTAR( "LIC_Avancar - dentro else if (x<0)" ) ;
            #endif
            Elem = Lista->ElemCorr ;
            for( i = x ; i < 0 ; i++ )
            {
               #ifdef _DEBUG
               CNT_CONTAR( "LIC_Avancar - dentro for( i = x ; i < 0 ; i++ )" ) ;
               #endif
               Elem = Elem->Ant ;
            } /* for */
            #ifdef _DEBUG
            CNT_CONTAR( "LIC_Avancar - depois for( i = x ; i < 0 ; i++ )" ) ;
            #endif
            Lista->ElemCorr = Elem ;
            #ifdef _DEBUG
            CNT_CONTAR( "LIC_Avancar - return dentro if ( x < 0)" ) ;
            #endif
            return LIC_CondRetOK ;

         } /* fim ativa: Tratar avan�ar para tr�s */

      /* Tratar n�o avan�ar (x==0)*/
         #ifdef _DEBUG
            CNT_CONTAR( "LIC_Avancar - return final" ) ;
         #endif
         return LIC_CondRetOK ;

   } /* Fim fun��o: LIC  &Avan�ar elemento */

/*==========================================================*/

/*  Fun��o: LIC  &Procurar elemento contendo valor*/

   LIC_CondRet LIC_ProcurarValor( LIC_Lista Lista , void * Valor )
   {
	  ElemLista * Elem ;
	  int n =0;

	     #ifdef _DEBUG
         CNT_CONTAR( "LIC_ProcurarValor - Inicio" ) ;
      #endif

      if (Lista==NULL){
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_ProcurarValor - dentro LISTA == NULL" ) ;
      #endif
		  printf("\nLista vazia\n");
		  return LIC_CondRetListaVazia;
	  }
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_ProcurarValor - antes Lista->ElemCorr == NULL" ) ;
      #endif
      if ( Lista->ElemCorr == NULL )
      {
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_ProcurarValor - dentro Lista->ElemCorr == NULL" ) ;
      #endif         
         return LIC_CondRetListaVazia ;
      } /* if */
            #ifdef _DEBUG
         CNT_CONTAR( "LIC_ProcurarValor - antes Elem = Lista->ElemCorr" ) ;
      #endif
	  Elem = Lista->ElemCorr;
	              #ifdef _DEBUG
         CNT_CONTAR( "LIC_ProcurarValor - depois Elem = Lista->ElemCorr" ) ;
      #endif
	  while(n!=Lista->numElem)
     {
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_ProcurarValor - antes Elem->Valor == Valor" ) ;
      #endif
		 if ( Elem->Valor == Valor )
		 {
         #ifdef _DEBUG
         CNT_CONTAR( "LIC_ProcurarValor - dentro Elem->Valor == Valor" ) ;
         #endif
			 Lista->ElemCorr = Elem ;
			 return LIC_CondRetOK ;
		 } 
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_ProcurarValor - depois Elem->Valor == Valor" ) ;
      #endif
		 Elem=Elem->Prox;
		 n++;		  
	  }
      #ifdef _DEBUG
         CNT_CONTAR( "LIC_ProcurarValor - return" ) ;
      #endif
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
         #ifdef _DEBUG
         CNT_CONTAR( "LiberarElemento - Inicio" ) ;
         #endif
         Lista->ExcluirValor( Elem->Valor ) ;
      } /* if */
            #ifdef _DEBUG
         CNT_CONTAR( "LiberarElemento - bloco" ) ;
         #endif
      free( Elem ) ;

      Lista->numElem-- ;
            #ifdef _DEBUG
         CNT_CONTAR( "LiberarElemento - return" ) ;
         #endif
      return;

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
         #ifdef _DEBUG
         CNT_CONTAR( "CriarElemento - Inicio" ) ;
         #endif
      if ( Elem == NULL )
      {
         #ifdef _DEBUG
         CNT_CONTAR( "CriarElemento - dentro Elem == NULL " ) ;
         #endif
         return NULL ;
      } /* if */
      #ifdef _DEBUG
      CNT_CONTAR( "CriarElemento - fora Elem == NULL " ) ;
      #endif
      Elem->Valor = Valor ;
      Elem->Ant   = NULL  ;
      Elem->Prox  = NULL  ;

      Lista->numElem ++ ;
      #ifdef _DEBUG
      CNT_CONTAR( "CriarElemento - return " ) ;
      #endif
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
         #ifdef _DEBUG
         CNT_CONTAR( "LimparCabeca - Inicio " ) ;
         #endif
         return LIC_CondRetListaVazia ;
      } 
      #ifdef _DEBUG
      CNT_CONTAR( "LimparCabeca - bloco " ) ;
      #endif
      Lista->Origem = NULL ;
      Lista->Fim = NULL ;
      Lista->ElemCorr = NULL ;
      Lista->numElem   = 0 ;
      #ifdef _DEBUG
      CNT_CONTAR( "LimparCabeca - return " ) ;
      #endif
      return LIC_CondRetOK;
   } /* Fim fun��o: LIC  -Limpar a cabe�a da lista */

/********** Fim do m�dulo de implementa��o: LIC  Lista circular duplamente encadeada **********/

