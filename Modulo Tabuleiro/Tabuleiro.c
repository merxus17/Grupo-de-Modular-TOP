#include <stdio.h>
#include <malloc.h>
#include "tabuleiro.h"
#include "lista.h"
#include "lista_circular.h"
#include "pecas.h"

typedef struct 
{
	LIC_Lista Tab_principal;
	LIS_tppLista Reta_Final_Vermelha;
	LIS_tppLista Reta_Final_Amarela;
	LIS_tppLista Reta_Final_Azul;
	LIS_tppLista Reta_Final_Verde;
}Tabuleiro;

typedef struct {
	int pecas[4]; // cada entrada do vetor contem o numero de pe�as de cada cor, 0-vermelho, 1-azul, 2-amarelo, 3-verde //
	int num; // branca caso nao seja uma entrada, caso seja diz a cor //
} CasaNormal;

typedef struct {
	int pecas;
	int num;
} CasaEspecial;

typedef struct Head
{
	Tabuleiro* tab;
	Peca* pecasVermelhas[4];
	Peca* pecasAmarelas[4];
	Peca* pecasAzuis[4];
	Peca* pecasVerdes[4];

}Head;

// FUN��ES AUXILIARES DO M�DULO
void DestruirCasa(void * pValor);
TAB_tpCondRet TAB_MoverVermelha (TAB_Head* tabuleiro, int nPeca, int casas);
TAB_tpCondRet TAB_MoverAzul (TAB_Head* tabuleiro, int nPeca, int casas);
TAB_tpCondRet TAB_MoverAmarela (TAB_Head* tabuleiro, int nPeca, int casas);
TAB_tpCondRet TAB_MoverVerde (TAB_Head* tabuleiro, int nPeca, int casas);

TAB_Head* TAB_criaTabuleiro()
{
	int nCasa, CorCasa ,nCasaEspecial,PecaCor, CorReta;
	/* ncasa � o iterador de casas alocando e settando as 51 casas do tabuleiro externo
	   CorCasa s�o quantas cores pdoem estar numa casa 
	   nCasaEspecial iterador de casas especiais alocando e settando as 6 casas do tabuleiro interno de casa cor
	   PecaCor s�o quantas pecas cada cor tem 
	*/
	TAB_Head* tabuleiro = (TAB_Head*)malloc(sizeof(TAB_Head));
	if (tabuleiro == NULL){
		return NULL;
	}
	tabuleiro->tab = (Tabuleiro*)malloc(sizeof(Tabuleiro));
	if (tabuleiro->tab == NULL){
		return NULL;
	}
	tabuleiro->tab->Tab_principal = LIC_CriarLista(DestruirCasa);
	if (tabuleiro->tab->Tab_principal == NULL){
		return NULL;
	}
	for (nCasa = 1; nCasa <= 51; nCasa++){
		CasaNormal* casa = (CasaNormal*) malloc(sizeof(CasaNormal));
		if(casa == NULL){
			return NULL;
		}
		casa->num = nCasa;

		for (CorCasa = 0; CorCasa < 4; CorCasa++){
			casa->pecas[CorCasa] = 0;
		}

		LIC_InserirApos(tabuleiro->tab->Tab_principal, casa);
		
	}
	
	tabuleiro->tab->Reta_Final_Vermelha = LIS_CriarLista(DestruirCasa);
	if (tabuleiro->tab->Reta_Final_Vermelha == NULL){
		return NULL;
	}
	tabuleiro->tab->Reta_Final_Amarela = LIS_CriarLista(DestruirCasa);
	if (tabuleiro->tab->Reta_Final_Amarela == NULL){
		return NULL;
	}
	tabuleiro->tab->Reta_Final_Azul = LIS_CriarLista(DestruirCasa);
	if (tabuleiro->tab->Reta_Final_Azul == NULL){
		return NULL;
	}
	tabuleiro->tab->Reta_Final_Verde = LIS_CriarLista(DestruirCasa);
	if (tabuleiro->tab->Reta_Final_Verde == NULL){
		return NULL;
	}
	for( CorReta = 0 ; CorReta < 4; CorReta++)
	{
		for (nCasaEspecial = 0; nCasaEspecial < 6; nCasaEspecial++)
		{
			CasaEspecial* casaEspecial =  (CasaEspecial*) malloc(sizeof(CasaEspecial));
			if(casaEspecial == NULL)
			{
				return NULL;
			}
		
			casaEspecial->pecas=0;
			casaEspecial->num = nCasaEspecial;
			if( CorReta == 0)	
			 LIS_InserirElementoApos(tabuleiro->tab->Reta_Final_Vermelha,casaEspecial);
			else if ( CorReta == 1)
			LIS_InserirElementoApos(tabuleiro->tab->Reta_Final_Amarela, casaEspecial);
			else if ( CorReta == 2) 
			LIS_InserirElementoApos(tabuleiro->tab->Reta_Final_Azul, casaEspecial);
			else if ( CorReta == 3) 
			LIS_InserirElementoApos(tabuleiro->tab->Reta_Final_Verde, casaEspecial);		
		}
	}
	
	for (PecaCor = 0; PecaCor < 4; PecaCor++){
		tabuleiro->pecasAmarelas[PecaCor] = P_CriaPeca() ;
		tabuleiro->pecasAzuis[PecaCor] = P_CriaPeca();
		tabuleiro->pecasVermelhas[PecaCor] = P_CriaPeca();
		tabuleiro->pecasVerdes[PecaCor]= P_CriaPeca();
	}

	return tabuleiro;


}

TAB_tpCondRet TAB_destroiTabuleiro(TAB_Head * tab)
{
	if( tab == NULL)
	{
		return TAB_CondRetTABNULL;
	}

	LIC_DestruirLista(tab->tab->Tab_principal);
	LIS_DestruirLista(tab->tab->Reta_Final_Vermelha);
	LIS_DestruirLista(tab->tab->Reta_Final_Verde);
	LIS_DestruirLista(tab->tab->Reta_Final_Amarela);
	LIS_DestruirLista(tab->tab->Reta_Final_Azul);
	free(tab->tab);
	free(tab);
	tab = NULL;
	
	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_verificaVitoria(TAB_Head* tabuleiro, Cor cor)
{
	// Respons�vel por determinar se um jogador venceu o jogo, ou seja, se colocou suas 4 pe�as na ultima casa
	CasaEspecial* Casa ;
	if( tabuleiro == NULL )
	{
		return TAB_CondRetTABNULL;
	}
	if (cor==Vermelho){
		IrFinalLista(tabuleiro->tab->Reta_Final_Vermelha);
		Casa = (CasaEspecial*)LIS_ObterValor(tabuleiro->tab->Reta_Final_Vermelha);
		if(Casa->num == 5 && Casa->pecas == 4){
			return TAB_CondRetVitoria;
		}
	}
	else if (cor==Azul){
		IrFinalLista(tabuleiro->tab->Reta_Final_Azul);
		Casa = (CasaEspecial*)LIS_ObterValor(tabuleiro->tab->Reta_Final_Azul);		
		if(Casa->num == 5 && Casa->pecas == 4){
			return TAB_CondRetVitoria;
		}
	}
	else if (cor==Amarelo){
		IrFinalLista(tabuleiro->tab->Reta_Final_Amarela);
		Casa = (CasaEspecial*)LIS_ObterValor(tabuleiro->tab->Reta_Final_Amarela);
		if(Casa->num == 5 && Casa->pecas == 4){
			return TAB_CondRetVitoria;
		}
	}
	else if (cor==Verde){
		IrFinalLista(tabuleiro->tab->Reta_Final_Verde);
		Casa = (CasaEspecial*)LIS_ObterValor(tabuleiro->tab->Reta_Final_Verde);
		if(Casa->num == 5 && Casa->pecas == 4){
			return TAB_CondRetVitoria;
		}
	}
	return TAB_CondRetNotThisTime;
}

TAB_tpCondRet TAB_moverPeca(TAB_Head* tabuleiro, Cor cor, int nPeca, int casas)
{
	//Respons�vel por testar se a pe�a a ser movida e o movimento s�o v�lidas e chama a fun��o de mover da resp�ctiva cor
	if(tabuleiro == NULL){
		return TAB_CondRetTABNULL;
	}
	if(cor == Branca){
		return TAB_CondRetPecaBranca;
	}
	if(nPeca < 0 || nPeca > 3){
		return TAB_CondRetNumDePecasInvalida;
	}
	if(casas <= 0){
		return TAB_CondRetMovimentoInvalido;
	}
	if(cor == Vermelho){
		return TAB_MoverVermelha(tabuleiro,nPeca,casas);
	}
	if(cor == Azul){
		return TAB_MoverAzul(tabuleiro,nPeca,casas);
	}
	if(cor == Amarelo){
		return TAB_MoverAmarela(tabuleiro,nPeca,casas);
	}
	if(cor == Verde){
		return TAB_MoverVerde(tabuleiro,nPeca,casas);
	}
	return TAB_CondRetNaoMoveu;
}

void TAB_showTab (TAB_Head * tabuleiro){
	int i,j,k,l;
	CasaNormal* casa;
	CasaEspecial* casaEspecial;
	if( tabuleiro == NULL)
	{
		return TAB_CondRetTABNULL;
	}
	printf("\n|");
	LIC_IrInicioLista(tabuleiro->tab->Tab_principal);
	for(i = 0; i < 51; i++){
		casa = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
		printf("%d: ", casa->num);
		if(casa->num == 1)
		{
			printf("Entrada Vermelha ");
		}
		if(casa->num == 40)
		{
			printf("Entrada Verde ");
		}
		if(casa->num == 14)
		{
			printf("Entrada Amarela ");
		}
		if(casa->num == 27)
		{
			printf("Entrada Azul ");
		}
		if(casa->pecas[0]){
			for(j = 0; j < casa->pecas[0]; j++){
				printf("R ");
			}
			printf("|");
		}
		if(casa->pecas[1]){
			for(j = 0; j < casa->pecas[1]; j++){
				printf("B ");
			}
			printf("|");
		}
		if(casa->pecas[2]){
			for(j = 0; j < casa->pecas[2]; j++){
				printf("Y ");
			}
			printf("|");
		}
		if(casa->pecas[3]){
			for(j = 0; j < casa->pecas[3]; j++){
				printf("G ");
			}
			printf("|");
		}
		if(casa->pecas[0] == 0 && casa->pecas[1] == 0 && casa->pecas[2] == 0 && casa->pecas[3] == 0){
			printf("_ |");
		}
		LIC_Avancar(tabuleiro->tab->Tab_principal, 1);
	}
	printf("\n\n|");
	IrInicioLista(tabuleiro->tab->Reta_Final_Vermelha);
	printf("Reta Vermelha: ");
	for(i = 0; i < 6; i++){
		casaEspecial = (CasaEspecial*) LIC_ObterValor(tabuleiro->tab->Reta_Final_Vermelha);
		printf("%d", casaEspecial->pecas);
		printf("|");
		LIS_AvancarElementoCorrente(tabuleiro->tab->Reta_Final_Vermelha, 1);
	}
	printf("           |");
	IrInicioLista(tabuleiro->tab->Reta_Final_Amarela);
	printf("Reta Amarela: ");
	for(i = 0; i < 6; i++){
		casaEspecial = (CasaEspecial*) LIC_ObterValor(tabuleiro->tab->Reta_Final_Amarela);
		printf("%d", casaEspecial->pecas);
		printf("|");
		LIS_AvancarElementoCorrente(tabuleiro->tab->Reta_Final_Amarela, 1);
	}
	printf("           |");
	IrInicioLista(tabuleiro->tab->Reta_Final_Azul);
	printf("Reta Azul: ");
	for(i = 0; i < 6; i++){
		casaEspecial = (CasaEspecial*) LIC_ObterValor(tabuleiro->tab->Reta_Final_Azul);
		printf("%d", casaEspecial->pecas);
		printf("|");
		LIS_AvancarElementoCorrente(tabuleiro->tab->Reta_Final_Azul, 1);
	}
	printf("           |");
	IrInicioLista(tabuleiro->tab->Reta_Final_Verde);
	printf("Reta Verde: ");
	for(i = 0; i < 6; i++){
		casaEspecial = (CasaEspecial*) LIC_ObterValor(tabuleiro->tab->Reta_Final_Verde);
		printf("%d", casaEspecial->pecas);
		printf("|");
		LIS_AvancarElementoCorrente(tabuleiro->tab->Reta_Final_Verde, 1);
	}
	printf("\n\n");
	printf("Pecas Amarelas: ");
	for (l=0 ; l<4 ; l++)
	{
		casa = (CasaNormal*) P_getCasa(tabuleiro->pecasAmarelas[l]);
		if ( casa != NULL)
			printf("%d ", casa->num );
		else
			printf("0 ");
	}
	printf("\n");
	printf("Pecas Vermelhas: ");
	for (l=0 ; l<4 ; l++)
	{
		casa = (CasaNormal*)P_getCasa(tabuleiro->pecasVermelhas[l]);
		if ( casa != NULL)
			printf("%d ", casa->num );
		else
			printf("0 ");
	}
	printf("\n");
	printf("Pecas Azul: ");
	for (l=0 ; l<4 ; l++)
	{
		casa = (CasaNormal*)P_getCasa(tabuleiro->pecasAzuis[l]);
		if ( casa != NULL)
			printf("%d ", casa->num );
		else
			printf("0 ");
	}
		printf("\n");
	printf("Pecas Verdes: ");
	for (l=0 ; l<4 ; l++)
	{
		casa = (CasaNormal*)P_getCasa(tabuleiro->pecasVerdes[l]);
		if ( casa != NULL)
			printf("%d ", casa->num );
		else
			printf("0 ");
	}
	printf("\n\n");
}

// FUN��ES AUXILIARES DO M�DULO

TAB_tpCondRet TAB_MoverVermelha (TAB_Head* tabuleiro, int nPeca, int casas)
{
	// Fun��o respons�vel pelo movimento das pe�as Vermelhas e por permitir que as mesmas comam uma �s outras(ou n�o)
	if (tabuleiro == NULL)
	{
		return TAB_CondRetTABNULL;
	}
	if(nPeca < 0 || nPeca > 4)
	{
	    return TAB_CondRetNumDePecasInvalida;
	}

	if((casas == 1 || casas ==6) && P_getCasa(tabuleiro->pecasVermelhas[nPeca]) == NULL){
		CasaNormal* Casa;
		LIC_IrInicioLista(tabuleiro->tab->Tab_principal);
		Casa = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
		P_setCasa(tabuleiro->pecasVermelhas[nPeca], Casa);
		Casa->pecas[0]++;
	}
	else if((casas != 1 && casas !=6) && P_getCasa(tabuleiro->pecasVermelhas[nPeca]) == NULL){
		return TAB_CondRetNaoEstaEmJogo;
	}
	else if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasVermelhas[nPeca])) == LIC_CondRetOK){ 
		// casa corrente � onde se encontra a pe�a (CASA NORMAL - a pe�a foi achada numa casa normal)
			int i=0;
			CasaNormal* Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
			Casa->pecas[0]--;
			while(i<casas && Casa->num!=50){
				LIC_Avancar(tabuleiro->tab->Tab_principal, 1);
				Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
				i++;
			}
			if(i == casas){ // andou tudo sem passar por entrada (ou parou bem sobre uma) (moviento branco a branco)
				int k=0;
				P_setCasa(tabuleiro->pecasVermelhas[nPeca], (void*)Casa);
				Casa->pecas[0]++;
			//==========Verifica se a pe�a vai comer a outra ou n�o===========//
				if(Casa->pecas[1] == 1 && Casa->num!=27){ // h� uma pe�a azul na casa
					Casa->pecas[1]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 pe�as azuis � a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasAzuis[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){
								P_setCasa(tabuleiro->pecasAzuis[k], NULL);
							}
						}
					}
				}
				if(Casa->pecas[2] == 1 && Casa->num!=14){// h� uma pe�a amarela na casa
					Casa->pecas[2]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 pe�as amarelas � a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasAmarelas[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){ 
								P_setCasa(tabuleiro->pecasAmarelas[k], NULL);
							}
						}
					}
				}
				if(Casa->pecas[3] == 1 && Casa->num!=40){ // h� uma pe�a verde na casa
					Casa->pecas[3]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 pe�as verdes � a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasVerdes[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){
								P_setCasa(tabuleiro->pecasVerdes[k], NULL);
							}
						}
					}
				}
				//==========FIM-COMER===========//
			}
			else{ // andou at� uma entrada antes de completar as casas (movimento branco a vermelho)
				CasaEspecial* Casa;
				IrInicioLista(tabuleiro->tab->Reta_Final_Vermelha);
				LIS_AvancarElementoCorrente(tabuleiro->tab->Reta_Final_Vermelha, casas-i-1); //mover o que faltou
				Casa = (CasaEspecial*)LIS_ObterValor(tabuleiro->tab->Reta_Final_Vermelha);
				P_setCasa(tabuleiro->pecasVermelhas[nPeca], Casa);
				Casa->pecas++;
			}

		}
		else if(LIS_ProcurarValor(tabuleiro->tab->Reta_Final_Vermelha, P_getCasa(tabuleiro->pecasVermelhas[nPeca])) == LIS_CondRetOK){
		// casa corrente � onde se encontra a pe�a (CASA ESPECIAL - a pe�a foi achada numa casa especial) (movimento vermelho a vermelho)
			CasaEspecial * Casa = (CasaEspecial*) LIS_ObterValor(tabuleiro->tab->Reta_Final_Vermelha);
			if(Casa->num==5){
				return TAB_CondRetJaTaNoFim;
			}
			else if(casas > (6-Casa->num)){
				return TAB_CondRetNotYet;
			}
			else{
				Casa->pecas--;
				LIS_AvancarElementoCorrente(tabuleiro->tab->Reta_Final_Vermelha, casas);
				Casa = (CasaEspecial*) LIS_ObterValor(tabuleiro->tab->Reta_Final_Vermelha);
				Casa->pecas++;
			}

		}
		else
			return TAB_CondRetMovimentoInvalido;
		
		return TAB_CondRetOK;
}

TAB_tpCondRet TAB_MoverAzul (TAB_Head* tabuleiro, int nPeca, int casas){
	// Fun��o respons�vel pelo movimento das pe�as Azuis e por permitir que as mesmas comam uma �s outras(ou n�o)
	if (tabuleiro == NULL)
	{
		return TAB_CondRetTABNULL;
	}
	if(nPeca < 0 || nPeca > 4)
	{
	    return TAB_CondRetNumDePecasInvalida;
	}
	

	if((casas == 1 || casas ==6) && P_getCasa(tabuleiro->pecasAzuis[nPeca]) == NULL){
		CasaNormal* Casa;
		LIC_IrInicioLista(tabuleiro->tab->Tab_principal);
		LIC_Avancar(tabuleiro->tab->Tab_principal, 26);
		Casa = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
		P_setCasa(tabuleiro->pecasAzuis[nPeca], Casa);
		Casa->pecas[1]++;
	}
	else if((casas != 1 && casas !=6) && P_getCasa(tabuleiro->pecasAzuis[nPeca]) == NULL){
		return TAB_CondRetNaoEstaEmJogo;
	}
	else if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasAzuis[nPeca])) == LIC_CondRetOK){ 
		// casa corrente � onde se encontra a pe�a (CASA NORMAL - a pe�a foi achada numa casa normal)
			int i=0;
			CasaNormal* Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
			Casa->pecas[1]--;
			while(i<casas && Casa->num!=25){
				LIC_Avancar(tabuleiro->tab->Tab_principal, 1);
				Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
				i++;
			}
			if(i == casas){ // andou tudo sem passar por entrada (ou parou bem sobre uma) (moviento branco a branco)
				int k=0;

				P_setCasa(tabuleiro->pecasAzuis[nPeca], (void*)Casa);
				Casa->pecas[1]++;
			//==========Verifica se a pe�a vai comer a outra ou n�o===========//
				if(Casa->pecas[0] == 1 && Casa->num!=1){ // h� uma pe�a vermelha na casa
					Casa->pecas[0]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 pe�as azuis � a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasVermelhas[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){
								P_setCasa(tabuleiro->pecasVermelhas[k], NULL);
							}
						}
					}
				}
				if(Casa->pecas[2] == 1 && Casa->num!=14){// h� uma pe�a amarela na casa
					Casa->pecas[2]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 pe�as amarelas � a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasAmarelas[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){ 
								P_setCasa(tabuleiro->pecasAmarelas[k], NULL);
							}
						}
					}
				}
				if(Casa->pecas[3] == 1 && Casa->num != 40){ // h� uma pe�a verde na casa
					Casa->pecas[3]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 pe�as verdes � a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasVerdes[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){
								P_setCasa(tabuleiro->pecasVerdes[k], NULL);
							}
						}
					}
				}
				//==========FIM-COMER===========//
			}
			else{ // andou at� uma entrada antes de completar as casas (movimento branco a azul)
				CasaEspecial* Casa;
				IrInicioLista(tabuleiro->tab->Reta_Final_Azul);
				LIS_AvancarElementoCorrente(tabuleiro->tab->Reta_Final_Azul, casas-i-1); //mover o que faltou
				Casa = (CasaEspecial*)LIS_ObterValor(tabuleiro->tab->Reta_Final_Azul);
				P_setCasa(tabuleiro->pecasAzuis[nPeca], Casa);
				Casa->pecas++;
			}

		}
		else if(LIS_ProcurarValor(tabuleiro->tab->Reta_Final_Azul, P_getCasa(tabuleiro->pecasAzuis[nPeca])) == LIS_CondRetOK){
		// casa corrente � onde se encontra a pe�a (CASA ESPECIAL - a pe�a foi achada numa casa especial) (movimento azul a azul)
			CasaEspecial * Casa = (CasaEspecial*) LIS_ObterValor(tabuleiro->tab->Reta_Final_Azul);
			if(Casa->num==5){
				return TAB_CondRetMovimentoInvalido;
			}
			else if(casas > (6-Casa->num)){
				return TAB_CondRetNotYet;
			}
			else{
				Casa->pecas--;
				LIS_AvancarElementoCorrente(tabuleiro->tab->Reta_Final_Azul, casas);
				Casa = (CasaEspecial*) LIS_ObterValor(tabuleiro->tab->Reta_Final_Azul);
				Casa->pecas++;
			}
		}
		else
			return TAB_CondRetMovimentoInvalido;
		
		return TAB_CondRetOK;
}

TAB_tpCondRet TAB_MoverAmarela (TAB_Head* tabuleiro, int nPeca, int casas){
	// Fun��o respons�vel pelo movimento das pe�as Amarelas e por permitir que as mesmas comam uma �s outras(ou n�o)
	if (tabuleiro == NULL)
	{
		return TAB_CondRetTABNULL;
	}
	if(nPeca < 0 || nPeca > 4)
	{
	    return TAB_CondRetNumDePecasInvalida;
	}
	
	
	
	if((casas == 1 || casas ==6) && P_getCasa(tabuleiro->pecasAmarelas[nPeca]) == NULL){
		CasaNormal* Casa;
		LIC_IrInicioLista(tabuleiro->tab->Tab_principal);
		LIC_Avancar(tabuleiro->tab->Tab_principal, 13);
		Casa = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
		P_setCasa(tabuleiro->pecasAmarelas[nPeca], Casa);
		Casa->pecas[2]++;
	}
	else if((casas != 1 && casas !=6) && P_getCasa(tabuleiro->pecasAmarelas[nPeca]) == NULL){
		return TAB_CondRetNaoEstaEmJogo;
	}
	else if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasAmarelas[nPeca])) == LIC_CondRetOK){ 
		// casa corrente � onde se encontra a pe�a (CASA NORMAL - a pe�a foi achada numa casa normal)
			int i=0;
			CasaNormal* Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
			Casa->pecas[2]--;
			while(i<casas && Casa->num!= 12){
				LIC_Avancar(tabuleiro->tab->Tab_principal, 1);
				Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
				i++;
			}
			if(i == casas){ // andou tudo sem passar por entrada (ou parou bem sobre uma) (moviento branco a branco)
				int k=0;

				P_setCasa(tabuleiro->pecasAmarelas[nPeca], (void*)Casa);
				Casa->pecas[2]++;
			//==========Verifica se a pe�a vai comer a outra ou n�o===========//
				if(Casa->pecas[1] == 1 && Casa->num!=27){ // h� uma pe�a azul na casa
					Casa->pecas[1]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 pe�as azuis � a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasAzuis[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){
								P_setCasa(tabuleiro->pecasAzuis[k], NULL);
							}
						}
					}
				}
				if(Casa->pecas[0] == 1 && Casa->num!=1){// h� uma pe�a vermelha na casa
					Casa->pecas[0]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 pe�as amarelas � a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasVermelhas[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){ 
								P_setCasa(tabuleiro->pecasVermelhas[k], NULL);
							}
						}
					}
				}
				if(Casa->pecas[3] == 1 && Casa->num!=40){ // h� uma pe�a verde na casa
					Casa->pecas[3]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 pe�as verdes � a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasVerdes[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){
								P_setCasa(tabuleiro->pecasVerdes[k], NULL);
							}
						}
					}
				}
				//==========FIM-COMER===========//
			}
			else{ // andou at� uma entrada antes de completar as casas (movimento branco a amarelo)
				CasaEspecial* Casa;
				IrInicioLista(tabuleiro->tab->Reta_Final_Amarela);
				LIS_AvancarElementoCorrente(tabuleiro->tab->Reta_Final_Amarela, casas-i-1); //mover o que faltou
				Casa = (CasaEspecial*)LIS_ObterValor(tabuleiro->tab->Reta_Final_Amarela);
				P_setCasa(tabuleiro->pecasAmarelas[nPeca], Casa);
				Casa->pecas++;
			}

		}
		else if(LIS_ProcurarValor(tabuleiro->tab->Reta_Final_Amarela, P_getCasa(tabuleiro->pecasAmarelas[nPeca])) == LIS_CondRetOK){
		// casa corrente � onde se encontra a pe�a (CASA ESPECIAL - a pe�a foi achada numa casa especial) (movimento amarelo a amarelo)
			CasaEspecial * Casa = (CasaEspecial*) LIS_ObterValor(tabuleiro->tab->Reta_Final_Amarela);
			if(Casa->num==5){
				return TAB_CondRetMovimentoInvalido;
			}
			else if(casas > (6-Casa->num)){
				return TAB_CondRetNotYet;
			}
			else{
				Casa->pecas--;
				LIS_AvancarElementoCorrente(tabuleiro->tab->Reta_Final_Amarela, casas);
				Casa = (CasaEspecial*) LIS_ObterValor(tabuleiro->tab->Reta_Final_Amarela);
				Casa->pecas++;
			}

		}
		else
			return TAB_CondRetMovimentoInvalido;
		
		
		return TAB_CondRetOK;
}

TAB_tpCondRet TAB_MoverVerde (TAB_Head* tabuleiro, int nPeca, int casas){
	// Fun��o respons�vel pelo movimento das pe�as Verdes e por permitir que as mesmas comam uma �s outras(ou n�o)
	if (tabuleiro == NULL)
	{
		return TAB_CondRetTABNULL;
	}
	if(nPeca < 0 || nPeca > 4)
	{
	    return TAB_CondRetNumDePecasInvalida;
	}
	
	
	if((casas == 1 || casas ==6) && P_getCasa(tabuleiro->pecasVerdes[nPeca]) == NULL){
		CasaNormal* Casa;
		LIC_IrInicioLista(tabuleiro->tab->Tab_principal);
		LIC_Avancar(tabuleiro->tab->Tab_principal, 39);
		Casa = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
		P_setCasa(tabuleiro->pecasVerdes[nPeca], Casa);
		Casa->pecas[3]++;
	}
	else if((casas != 1 && casas !=6) && P_getCasa(tabuleiro->pecasVerdes[nPeca]) == NULL){
		return TAB_CondRetNaoEstaEmJogo;
	}
	else if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasVerdes[nPeca])) == LIC_CondRetOK){ 
		// casa corrente � onde se encontra a pe�a (CASA NORMAL - a pe�a foi achada numa casa normal)
			int i=0;
			CasaNormal* Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
			Casa->pecas[3]--;
			while(i<casas && Casa->num!=38){
				LIC_Avancar(tabuleiro->tab->Tab_principal, 1);
				Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
				i++;
			}
			if(i == casas){ // andou tudo sem passar por entrada (ou parou bem sobre uma) (moviento branco a branco)
				int k=0;

				P_setCasa(tabuleiro->pecasVerdes[nPeca], (void*)Casa);
				Casa->pecas[3]++;
			//==========Verifica se a pe�a vai comer a outra ou n�o===========//
				if(Casa->pecas[1] == 1 && Casa->num!=27){ // h� uma pe�a azul na casa
					Casa->pecas[1]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 pe�as azuis � a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasAzuis[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){
								P_setCasa(tabuleiro->pecasAzuis[k], NULL);
							}
						}
					}
				}
				if(Casa->pecas[2] == 1 && Casa->num!=14){// h� uma pe�a amarela na casa
					Casa->pecas[2]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 pe�as amarelas � a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasAmarelas[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){ 
								P_setCasa(tabuleiro->pecasAmarelas[k], NULL);
							}
						}
					}
				}
				if(Casa->pecas[0] == 1 && Casa->num!= 1){ // h� uma pe�a vermelha na casa
					Casa->pecas[0]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 pe�as verdes � a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasVermelhas[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){
								P_setCasa(tabuleiro->pecasVermelhas[k], NULL);
							}
						}
					}
				}
				//==========FIM-COMER===========//
			}
			else{ // andou at� uma entrada antes de completar as casas (movimento branco a verde)
				CasaEspecial* Casa;
				IrInicioLista(tabuleiro->tab->Reta_Final_Verde);
				LIS_AvancarElementoCorrente(tabuleiro->tab->Reta_Final_Verde, casas-i-1); //mover o que faltou
				Casa = (CasaEspecial*)LIS_ObterValor(tabuleiro->tab->Reta_Final_Verde);
				P_setCasa(tabuleiro->pecasVerdes[nPeca], Casa);
				Casa->pecas++;
			}

		}
		else if(LIS_ProcurarValor(tabuleiro->tab->Reta_Final_Verde, P_getCasa(tabuleiro->pecasVerdes[nPeca])) == LIS_CondRetOK){
		// casa corrente � onde se encontra a pe�a (CASA ESPECIAL - a pe�a foi achada numa casa especial) (movimento verde a verde)
			CasaEspecial * Casa = (CasaEspecial*) LIS_ObterValor(tabuleiro->tab->Reta_Final_Verde);
			if(Casa->num==5){
				return TAB_CondRetMovimentoInvalido;
			}
			else if(casas > (6-Casa->num)){
				return TAB_CondRetNotYet;
			}
			else{
				Casa->pecas--;
				LIS_AvancarElementoCorrente(tabuleiro->tab->Reta_Final_Verde, casas);
				Casa = (CasaEspecial*) LIS_ObterValor(tabuleiro->tab->Reta_Final_Verde);
				Casa->pecas++;
			}

		}
		else
			return TAB_CondRetMovimentoInvalido;
		
		return TAB_CondRetOK;
}

void DestruirCasa(void * pValor)
{
	// Libera o espa�o de mom�ria da casa
	if(pValor != NULL)
	{
		free(pValor);
	}
	return;
} 

