#if ! defined( lista_circular_ )
#define lista_circular_
/***************************************************************************
*
*  $MCD Módulo de definição: LIC  Lista circular simplesmente encadeada
*
*  Arquivo gerado:              lista_circular.h
*  Letras identificadoras:      LIC
*
*  Projeto: INF 1301 / T2
*  Autores: Giulia Mahovlic
*
*  $ED Descrição do módulo
*     Implementa listas circulares genéricas duplamente encadeadas.
*     Podem existir n listas circulares em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista circular é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( listac_OWN )
   #define listac_EXT
#else
   #define listac_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIC_tagLista * LIC_Lista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         LIC_CondRetOK ,
               /* Concluiu corretamente */

         LIC_CondRetListaVazia ,
               /* A lista não contém elementos */

         LIC_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         LIC_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento de lista */

   } LIC_CondRet ;


/***********************************************************************
*
*  $FC Função: LIC  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista circular genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*
***********************************************************************/

   LIC_Lista LIC_CriarLista( void   ( * ExcluirValor ) ( void * Dado ) ) ;


/***********************************************************************
*
*  $FC Função: LIC  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*  
*  $EP Parâmetros
*	  Lista - ponteiro para a lista a ser destruída
*
*  $FV Valor retornado
*     LIC_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   void LIC_DestruirLista( LIC_Lista Lista ) ;


/***********************************************************************
*
*  $FC Função: LIC  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     Lista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

   void LIC_EsvaziarLista( LIC_Lista Lista ) ;


/***********************************************************************
*
*  $FC Função: LIC  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
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
*  $FC Função: LIC  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento após o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
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
*  $FC Função: LIC  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
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
*  $FC Função: LIC  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     Lista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     não NULL - se o elemento corrente existe ele é retornado
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

   void * LIC_ObterValor( LIC_Lista Lista ) ;


/***********************************************************************
*
*  $FC Função: LIC  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     Lista - ponteiro para a lista a manipular
*
***********************************************************************/

   void LIC_IrInicioLista( LIC_Lista Lista ) ;


/***********************************************************************
*
*  $FC Função: LIC  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     Lista - ponteiro para a lista a manipular
*
***********************************************************************/

   void LIC_IrFinalLista( LIC_Lista Lista ) ;


/***********************************************************************
*
*  $FC Função: LIC  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente x elementos na lista
*     Se x for positivo avança em sentido horário
*     Se x for negativo avança em sentido anti-horário
*     Se x for zero somente verifica se a lista está vazia
*     Faz nada se a lista possui apenas um elemento 
*				(avançar qualquer número em qualquer sentido 
*								sempre da no mesmo elemento)
*
*  $EP Parâmetros
*     Lista  - ponteiro para a lista a ser manipulada
*     x - o número de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se x elementos tiverem sido andados
*     CondRetListaVazia - se a lista está vazia
*
***********************************************************************/

   LIC_CondRet LIC_Avancar( LIC_Lista Lista , int x ) ;


/***********************************************************************
*
*  $FC Função: LIC  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*     A função compara ponteiro e não conteúdo apontado.
*
*  $EP Parâmetros
*     Lista  - ponteiro para a lista onde ocorre a procura
*     Valor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIC_CondRetOK  - se encontrou
*                      O elemento corrente passa a ser o que possui o valor procurado
*     LIC_CondRetNaoEncontrou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     LIC_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   LIC_CondRet LIC_ProcurarValor( LIC_Lista Lista, void * Valor) ;

#undef listac_EXT

/********** Fim do módulo de definição: LIC  Lista circular simplesmente encadeada **********/

#else
#endif