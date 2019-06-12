#include <stdio.h>
#include <malloc.h>
#include "Pecas.h"


typedef struct P
{
	void* casa;
}P;


Peca* P_CriaPeca()
{
	Peca* pPeca = NULL;
	pPeca = (Peca*) malloc(sizeof(pPeca));
	if(pPeca == NULL)
	{
		return NULL;
	}
	pPeca->casa = NULL;
	return pPeca;
}

PEC_tpCondRet P_DestroiPeca(Peca* peca)
{
	if(peca==NULL){
		return PEC_CondRetPECNULL;
	}
	else if(peca != NULL)
	{
		free(peca);
		peca = NULL;
	}

	return PEC_CondRetOK;
}


void* P_getCasa (Peca* pPeca)
{
	if(pPeca == NULL)
	{
		return NULL;
	}
	return pPeca->casa;
}


PEC_tpCondRet P_setCasa(Peca* pPeca ,void* casa)
{
	if(pPeca == NULL)
	{
		return PEC_CondRetPECNULL;
	}
	pPeca->casa = casa;
	return PEC_CondRetOK;
}