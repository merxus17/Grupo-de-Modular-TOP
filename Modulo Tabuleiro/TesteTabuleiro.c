#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.h"

#include    "Generico.h"
#include    "LERPARM.h"

#include    "Tabuleiro.h"

static const char RESET_TAB_CMD         [ ] = "=resetteste"     ;
static const char CRIA_TAB_CMD         [ ] = "=TAB_criaTabuleiro";
static const char VITORIA_TAB_CMD      [ ] = "=TAB_verificaVitoria"  ;
static const char MOVER_PECA_CMD      [ ] = "=TAB_moverPeca"  ;
static const char DESTRUIR_TAB_CMD      [ ] = "=TAB_destroiTabuleiro"   ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_TAB   10


TAB_Head*   vtTAB[ DIM_VT_TAB ] ;



/***********************************************************************
*
*  $FC Fun��o: TLIS &Testar lista
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 listas, identificadas pelos �ndices 0 a 10
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
	Cor traduzCor ( int n);
   
	
	TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
	  

      int inxLista  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TAB_tpCondRet CondRet = TAB_CondRetOK ;

      int i ;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_TAB_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_TAB ; i++ )
            {
               vtTAB[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarLista */

         else if ( strcmp( ComandoTeste , CRIA_TAB_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "i" ,
                       &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtTAB[ inxLista ] = TAB_criaTabuleiro() ;

            return TST_CompararPonteiroNulo( 1 , vtTAB[ inxLista ] ,
               "Erro em ponteiro de nova Tabuleiro."  ) ;

         } /* fim ativa: Testar CriarLista */

      /* Testar Destruir peça lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_TAB_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "ii" ,
                               &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = TAB_destroiTabuleiro( vtTAB[ inxLista ] ) ;
            vtTAB[ inxLista ] = NULL ;

            return TST_CompararInt( CondRetEsp , CondRet ,
               "Condicao de retorno errada ao destruir."  ) ;

         } /* fim ativa: Testar Destruir Peça */

      

      /* Testar inserir elemento antes */

         else if ( strcmp( ComandoTeste , VITORIA_TAB_CMD ) == 0 )
         {
			 int corRecebida;
			 Cor cor;
            numLidos = LER_LerParametros( "iii" ,
                       &inxLista , &corRecebida ,&CondRetEsp ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

			cor = traduzCor ( corRecebida);

            CondRet = TAB_verificaVitoria( vtTAB[ inxLista ] , cor ) ;
			
            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao retornar vitoria.") ;

         } /* fim ativa: Testar inserir elemento antes */

      /* Testar inserir elemento apos */

         else if ( strcmp( ComandoTeste , MOVER_PECA_CMD ) == 0 )
         {
			 Cor cor ;
			 int corRecebida;
			 int Numero ,Casas;
            numLidos = LER_LerParametros( "iiiii" ,
                       &inxLista , &corRecebida , &Numero ,&Casas ,&CondRetEsp ) ;
			
            if ( ( numLidos != 5 ))
            {
               return TST_CondRetParm ;
            } /* if */
			
			cor = traduzCor ( corRecebida );
			
            CondRet = TAB_moverPeca ( vtTAB[ inxLista ] , cor , Numero , Casas  ) ;
			
			

            return TST_CompararInt( CondRetEsp , CondRet ,
                    "Condicao de retorno errada ao mover peca."                   ) ;
			

         } /* fim ativa: Testar inserir elemento apos */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TLIS &Testar lista */





   Cor traduzCor ( int n)
   {
	   if( n == 0 )
		   return Vermelho;
	   else if( n == 1 )
		   return Azul;
	   else if( n == 2 )
		   return Amarelo;
	   else if( n== 3 )
		   return Verde;
	   else 
		   return Branca;

   }



   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_TAB ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtTAB[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
	  } else
      {
         if ( vtTAB[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim fun��o: TLIS -Validar indice de lista */