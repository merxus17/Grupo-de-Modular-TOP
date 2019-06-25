#if ! defined( lista_circular_ )
#define lista_circular_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: LIC  Lista circular duplamente encadeada
*
*  Arquivo gerado:              lista_circular.h
*  Letras identificadoras:      LIC
*
*  Projeto: INF 1301 / T2
*  Autores: Giulia Mahovlic
*
*  $ED Descri��o do m�dulo
*     Implementa listas circulares gen�ricas duplamente encadeadas.
*     Podem existir n listas circulares em opera��o simultaneamente.
*     As listas possuem uma cabe�a encapsulando o seu estado.
*
*     Cada lista circular � homog�nea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da lista.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada lista referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( listac_OWN )
   #define listac_EXT
#else
   #define listac_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LIC_tagLista * LIC_Lista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

   typedef enum {

         LIC_CondRetOK ,
               /* Concluiu corretamente */

         LIC_CondRetListaVazia ,
               /* A lista n�o cont�m elementos */

         LIC_CondRetNaoAchou ,
               /* N�o encontrou o valor procurado */

         LIC_CondRetFaltouMemoria
               /* Faltou mem�ria ao tentar criar um elemento de lista */

   } LIC_CondRet ;


/***********************************************************************
*
*  $FC Fun��o: LIC  &Criar lista
*
*  $ED Descri��o da fun��o
*     Cria uma lista circular gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*
***********************************************************************/

   LIC_Lista LIC_CriarLista( void   ( * ExcluirValor ) ( void * Dado ) ) ;


/***********************************************************************
*
*  $FC Fun��o: LIC  &Destruir lista
*
*  $ED Descri��o da fun��o
*     Destr�i a lista fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*  
*  $EP Par�metros
*	  Lista - ponteiro para a lista a ser destru�da
*
*  $FV Valor retornado
*     LIC_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   LIC_CondRet LIC_DestruirLista( LIC_Lista Lista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIC  &Esvaziar lista
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Par�metros
*     Lista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

   LIC_CondRet LIC_EsvaziarLista( LIC_Lista Lista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIC  &Inserir elemento antes
*
*  $ED Descri��o da fun��o
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     Lista - ponteiro para a lista onde deve ser inserido o elemento
*     Valor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIC_CondRetOK
*     LIC_CondRetFaltouMemoria
*
***********************************************************************/

   LIC_CondRet LIC_InserirAntes( LIC_Lista Lista ,  void * Valor  ) ;


/***********************************************************************
*
*  $FC Fun��o: LIC  &Inserir elemento ap�s
*
*  $ED Descri��o da fun��o
*     Insere novo elemento ap�s o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*        Lista - ponteiro para a lista onde deve ser inserido o elemento
*        Valor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIC_CondRetOK
*        LIC_CondRetFaltouMemoria
*
***********************************************************************/

   LIC_CondRet LIC_InserirApos( LIC_Lista Lista ,  void * Valor );


/***********************************************************************
*
*  $FC Fun��o: LIC  &Excluir elemento
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a lista tornou-se vazia.
*
*  $EP Par�metros
*     Lista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIC_CondRetOK
*     LIC_CondRetListaVazia
*
***********************************************************************/

   LIC_CondRet LIC_ExcluirElemento( LIC_Lista Lista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIC  &Obter refer�ncia para o valor contido no elemento
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no elemento corrente da lista
*
*  $EP Par�metros
*     Lista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     n�o NULL - se o elemento corrente existe ele � retornado
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

   void * LIC_ObterValor( LIC_Lista Lista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIC  &Ir para o elemento inicial
*
*  $ED Descri��o da fun��o
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     Lista - ponteiro para a lista a manipular
*
***********************************************************************/

   LIC_CondRet LIC_IrInicioLista( LIC_Lista Lista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIC  &Ir para o elemento final
*
*  $ED Descri��o da fun��o
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     Lista - ponteiro para a lista a manipular
*
***********************************************************************/

   LIC_CondRet LIC_IrFinalLista( LIC_Lista Lista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIC  &Avan�ar elemento
*
*  $ED Descri��o da fun��o
*     Avan�a o elemento corrente x elementos na lista
*     Se x for positivo avan�a em sentido hor�rio
*     Se x for negativo avan�a em sentido anti-hor�rio
*     Se x for zero somente verifica se a lista est� vazia
*     Faz nada se a lista possui apenas um elemento 
*				(avan�ar qualquer n�mero em qualquer sentido 
*								sempre da no mesmo elemento)
*
*  $EP Par�metros
*     Lista  - ponteiro para a lista a ser manipulada
*     x - o n�mero de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se x elementos tiverem sido andados
*     CondRetListaVazia - se a lista est� vazia
*
***********************************************************************/

   LIC_CondRet LIC_Avancar( LIC_Lista Lista , int x ) ;


/***********************************************************************
*
*  $FC Fun��o: LIC  &Procurar elemento contendo valor
*
*  $ED Descri��o da fun��o
*     Procura o elemento que referencia o valor dado.
*     A fun��o compara ponteiro e n�o conte�do apontado.
*
*  $EP Par�metros
*     Lista  - ponteiro para a lista onde ocorre a procura
*     Valor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIC_CondRetOK  - se encontrou
*                      O elemento corrente passa a ser o que possui o valor procurado
*     LIC_CondRetNaoEncontrou - se o ponteiro n�o foi encontrado
*                      O elemento corrente continua o mesmo
*     LIC_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   LIC_CondRet LIC_ProcurarValor( LIC_Lista Lista, void * Valor) ;

#undef listac_EXT

/********** Fim do m�dulo de defini��o: LIC  Lista circular duplamente encadeada **********/

#else
#endif