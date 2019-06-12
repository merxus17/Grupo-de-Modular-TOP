#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.h"

#include    "Generico.h"
#include    "LERPARM.h"

#include    "Pecas.h"

static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char CRIA_PEÇA_CMD         [ ] = "=criaPeca";
static const char DESTRUIR_PEÇA_CMD      [ ] = "=destruirPeca"  ;
static const char GET_CASA_CMD      [ ] = "=getCasa"  ;
static const char SET_CASA_CMD      [ ] = "=setCasa"   ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_PEÇAS   10

Peca*   vtPeças[ DIM_VT_PEÇAS ] ;



/***********************************************************************
*
*  $FC Fun��o: TLIS &Testar lista
*
*  $ED Descri��o da fun��o
*     Podem ser criadas até 10 pecas, identificadas pelos índices 0 a 10
*
*     Comandos dispon�veis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de mem�ria
*     =criarlista                   inxLista
*     =destruirlista                inxLista
*     =esvaziarlista                inxLista
*     =inselemantes                 inxLista  string  CondRetEsp
*     =inselemapos                  inxLista  string  CondRetEsp
*     =obtervalorelem               inxLista  string  CondretPonteiro
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =avancarelem                  inxLista  numElem CondRetEsp
*
***********************************************************************/
	int ValidarInxLista( int inxLista , int Modo );

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
	  

      int inxLista  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      PEC_tpCondRet CondRet = PEC_CondRetOK ;

      int i ;


      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_PEÇAS ; i++ )
            {
               vtPeças[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarLista */

         else if ( strcmp( ComandoTeste , CRIA_PEÇA_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "i" ,
                       &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtPeças[ inxLista ] = P_CriaPeca() ;

            return TST_CompararPonteiroNulo( 1 , vtPeças[ inxLista ] ,
               "Erro em ponteiro de nova peça."  ) ;

         } /* fim ativa: Testar CriarLista */

      /* Testar Destruir peça lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_PEÇA_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            P_DestroiPeca( vtPeças[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir Peça */

      

      /* Testar inserir elemento antes */

         else if ( strcmp( ComandoTeste , GET_CASA_CMD ) == 0 )
         {
			 long ValorObtido = 0 ;
			 int* n = 0;
			 void* casaObtida = NULL ;
            numLidos = LER_LerParametros( "ii" ,
                       &inxLista , &CondRetEsp ) ;

             //|| ( ! ValidarInxLista( inxLista , NAO_VAZIO ))
            if ( ( numLidos != 2 )
              )
            {
               return TST_CondRetParm ;
            } /* if */

            casaObtida = P_getCasa( vtPeças[ inxLista ] ) ;
			
			if( casaObtida == NULL)
			{
				return TST_CondRetErro;
			}
			
			n = (int*) casaObtida;
			
			
			
			ValorObtido = (long)*n;
			
			
            return TST_CompararInt( CondRetEsp , ValorObtido ,
                     "Condicao de retorno errada ao receber casa.") ;

         } /* fim ativa: Testar inserir elemento antes */

      /* Testar inserir elemento apos */

         else if ( strcmp( ComandoTeste , SET_CASA_CMD ) == 0 )
         {
			 void* InteiroDado = NULL;
			 int* Inteiro = (int*) malloc(sizeof(int));
            numLidos = LER_LerParametros( "iii" ,
                       &inxLista , Inteiro , &CondRetEsp ) ;
			 
			
			
			
            if ( ( numLidos != 3 ))
            {
               return TST_CondRetParm ;
            } /* if */
			
			InteiroDado = (void*)Inteiro;
			
            CondRet = P_setCasa ( vtPeças[ inxLista ] , InteiroDado ) ;
			
			

            return TST_CompararInt( CondRetEsp , CondRet ,
                    "Condicao de retorno errada ao settar casa."                   ) ;
			

         } /* fim ativa: Testar inserir elemento apos */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TLIS &Testar lista */









   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_PEÇAS ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtPeças[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
	  } else
      {
         if ( vtPeças[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim fun��o: TLIS -Validar indice de lista */