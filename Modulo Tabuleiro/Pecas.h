/***********************************************************************
*
*  $TC Tipo de dados: PEC Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da peca
*
***********************************************************************/

typedef enum {

         PEC_CondRetOK ,
               /* Concluiu corretamente */

         PEC_CondRetPECNULL ,
               /* A Peca enviada é NULL */

         PEC_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         PEC_CondRetFaltouMemoria ,
               /* Faltou memória ao tentar criar um elemento de PECta */

		 PEC_CondFalhouDelecao
			  /* Faltou memória ao tentar criar um elemento de PECta */

   } PEC_tpCondRet ;

typedef struct P Peca;

/***********************************************************************
*
*  $FC Função: PEC  &Criar peca
*
*  $ED Descrição da função
*     Inicia peca e aloca espaco.
*
*  $FV Valor retornado
*     NULL - Ocorreu problema durante a criação da peca. Não será dada mais informação quanto ao problema ocorrido.
*	  Ponteiro nao NULL - Criou com sucesso.
*
***********************************************************************/
Peca* P_CriaPeca();


/***********************************************************************
*
*  $FC Função: PEC  &Destroi peca
*
*  $ED Descrição da função
*     Desaloca peca enviada.
*
*  $EP Parâmetros
*     Parâmetros
*        peca - um ponteiro para uma peca.
*        
*  $FV Valor retornado
*     PEC_CondRetOK - Deletou a peca sem problemas ou a peca enviado ja era NULL.
*	  OBS. não existe previsão para possíveis falhas de execução.
*
***********************************************************************/
PEC_tpCondRet P_DestroiPeca(Peca* peca);


/***********************************************************************
*
*  $FC Função: PEC  &Get casa
*
*  $ED Descrição da função
*     Pega o ponteiro para a casa.
*
*  $EP Parâmetros
*     Parâmetros
*        peca - um ponteiro para uma peca.
*        
*  $FV Valor retornado
*     Ponteiro para a casa - Ponteiro para a cassa da peca enviada, pode retornar NULL se o valor da casa for NULL.
*	  NULL - Retorna NULL se o ponteiro para peca for NULL.
*
***********************************************************************/
void* P_getCasa (Peca* p);

/***********************************************************************
*
*  $FC Função: PEC  &Set casa
*
*  $ED Descrição da função
*     Seta o ponteiro para a casa.
*
*  $EP Parâmetros
*     Parâmetros
*        peca - um ponteiro para uma peca.
*		 casa - um ponteiro para uma casa
*        
*  $FV Valor retornado
*     PEC_CondRetOK - Se o valor foi setado corretamentee.
*	  PEC_CondRetPECNULL - Se o ponteiro para peca for NULL.
*
***********************************************************************/
PEC_tpCondRet P_setCasa(Peca* p ,void* casa);