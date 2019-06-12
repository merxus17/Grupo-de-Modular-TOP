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
	int pecas[4]; // cada entrada do vetor contem o numero de peças de cada cor, 0-vermelho, 1-azul, 2-amarelo, 3-verde //
	Cor entrada; // branca caso nao seja uma entrada, caso seja diz a cor //
	int nCasa;
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

// FUNÇÕES AUXILIARES DO MÓDULO
void DestruirCasa(void * pValor);
TAB_tpCondRet TAB_MoverVermelha (TAB_Head* tabuleiro, int nPeca, int casas);
TAB_tpCondRet TAB_MoverAzul (TAB_Head* tabuleiro, int nPeca, int casas);
TAB_tpCondRet TAB_MoverAmarela (TAB_Head* tabuleiro, int nPeca, int casas);
TAB_tpCondRet TAB_MoverVerde (TAB_Head* tabuleiro, int nPeca, int casas);

TAB_Head* TAB_criaTabuleiro()
{
	int nCasa, CorCasa ,nCasaEspecial,PecaCor;
	/* ncasa é o iterador de casas alocando e settando as 51 casas do tabuleiro externo
	   CorCasa são quantas cores pdoem estar numa casa 
	   nCasaEspecial iterador de casas especiais alocando e settando as 6 casas do tabuleiro interno de casa cor
	   PecaCor são quantas pecas cada cor tem 
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
		if (nCasa == 1)
			casa->entrada = Vermelho;
		else if (nCasa == 13)
			casa->entrada = Amarelo;
		else if (nCasa == 26)
			casa->entrada = Azul;
		else if (nCasa == 39)
			casa->entrada = Verde;
		else
			casa->entrada = Branca;

		for (CorCasa = 0; CorCasa < 4; CorCasa++){
			casa->pecas[CorCasa] = 0;
		}
		casa->nCasa= nCasa;
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

	for (nCasaEspecial = 0; nCasaEspecial < 6; nCasaEspecial++){
		CasaEspecial* casaEspecial =  (CasaEspecial*) malloc(sizeof(CasaEspecial));
		if(casaEspecial == NULL){
			return NULL;
		}
		
		casaEspecial->pecas=0;
		casaEspecial->num = nCasaEspecial;
		
		 LIS_InserirElementoApos(tabuleiro->tab->Reta_Final_Vermelha,casaEspecial);
		 LIS_InserirElementoApos(tabuleiro->tab->Reta_Final_Amarela, casaEspecial);
		 LIS_InserirElementoApos(tabuleiro->tab->Reta_Final_Azul, casaEspecial);
		 LIS_InserirElementoApos(tabuleiro->tab->Reta_Final_Verde, casaEspecial);		
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
	if( !tab )
	{
		LIC_DestruirLista(tab->tab->Tab_principal);
		LIS_DestruirLista(tab->tab->Reta_Final_Vermelha);
		LIS_DestruirLista(tab->tab->Reta_Final_Verde);
		LIS_DestruirLista(tab->tab->Reta_Final_Amarela);
		LIS_DestruirLista(tab->tab->Reta_Final_Azul);
		free(tab->tab);
		free(tab);
		tab = NULL;
	}
	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_verificaVitoria(TAB_Head* tabuleiro, Cor cor)
{
	// Responsável por determinar se um jogador venceu o jogo, ou seja, se colocou suas 4 peças na ultima casa
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
	//Responsável por testar se a peça a ser movida e o movimento são válidas e chama a função de mover da respéctiva cor
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
	printf("\n|");
	LIC_IrInicioLista(tabuleiro->tab->Tab_principal);
	for(i = 0; i < 51; i++){
		casa = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
		printf("%d: ", casa->nCasa);
		if(casa->entrada == Vermelho)
		{
			printf("Entrada Vermelha ");
		}
		if(casa->entrada == Verde)
		{
			printf("Entrada Verde ");
		}
		if(casa->entrada == Amarelo)
		{
			printf("Entrada Amarela ");
		}
		if(casa->entrada == Azul)
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
			printf("%d ", casa->nCasa );
		else
			printf("0 ");
	}
	printf("\n");
	printf("Pecas Vermelhas: ");
	for (l=0 ; l<4 ; l++)
	{
		casa = (CasaNormal*)P_getCasa(tabuleiro->pecasVermelhas[l]);
		if ( casa != NULL)
			printf("%d ", casa->nCasa );
		else
			printf("0 ");
	}
	printf("\n");
	printf("Pecas Azul: ");
	for (l=0 ; l<4 ; l++)
	{
		casa = (CasaNormal*)P_getCasa(tabuleiro->pecasAzuis[l]);
		if ( casa != NULL)
			printf("%d ", casa->nCasa );
		else
			printf("0 ");
	}
		printf("\n");
	printf("Pecas Verdes: ");
	for (l=0 ; l<4 ; l++)
	{
		casa = (CasaNormal*)P_getCasa(tabuleiro->pecasVerdes[l]);
		if ( casa != NULL)
			printf("%d ", casa->nCasa );
		else
			printf("0 ");
	}
	printf("\n\n");
}

// FUNÇÕES AUXILIARES DO MÓDULO

TAB_tpCondRet TAB_MoverVermelha (TAB_Head* tabuleiro, int nPeca, int casas){
	// Função responsável pelo movimento das peças Vermelhas e por permitir que as mesmas comam uma às outras(ou não)
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
		// casa corrente é onde se encontra a peça (CASA NORMAL - a peça foi achada numa casa normal)
			int i=0;
			CasaNormal* Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
			Casa->pecas[0]--;
			LIC_Avancar(tabuleiro->tab->Tab_principal, 1);
			Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
			i++;
			while(i<casas && Casa->entrada!=Vermelho){
				LIC_Avancar(tabuleiro->tab->Tab_principal, 1);
				Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
				i++;
			}
			if(i==casas){ // andou tudo sem passar por entrada (ou parou bem sobre uma) (moviento branco a branco)
				int k=0;

				CasaNormal* iAzul;
				CasaNormal* iAmarelo;
				CasaNormal* iVerde;
				LIC_Avancar(tabuleiro->tab->Tab_principal, 12);
				iAzul = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
				LIC_Avancar(tabuleiro->tab->Tab_principal, 12);
				iAmarelo = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
				LIC_Avancar(tabuleiro->tab->Tab_principal, 12);
				iVerde = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);

				P_setCasa(tabuleiro->pecasVermelhas[nPeca], (void*)Casa);
				Casa->pecas[0]++;
			//==========Verifica se a peça vai comer a outra ou não===========//
				if(Casa->pecas[1] == 1 && Casa!=iAzul){ // há uma peça azul na casa
					Casa->pecas[1]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 peças azuis é a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasAzuis[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){
								P_setCasa(tabuleiro->pecasAzuis[k], NULL);
							}
						}
					}
				}
				if(Casa->pecas[2] == 1 && Casa!=iAmarelo){// há uma peça amarela na casa
					Casa->pecas[2]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 peças amarelas é a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasAmarelas[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){ 
								P_setCasa(tabuleiro->pecasAmarelas[k], NULL);
							}
						}
					}
				}
				if(Casa->pecas[3] == 1 && Casa!=iVerde){ // há uma peça verde na casa
					Casa->pecas[3]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 peças verdes é a que esta ali
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
			else{ // andou até uma entrada antes de completar as casas (movimento branco a vermelho)
				CasaEspecial* Casa;
				IrInicioLista(tabuleiro->tab->Reta_Final_Vermelha);
				LIS_AvancarElementoCorrente(tabuleiro->tab->Reta_Final_Vermelha, casas-i-2); //mover o que faltou
				Casa = (CasaEspecial*)LIS_ObterValor(tabuleiro->tab->Reta_Final_Vermelha);
				P_setCasa(tabuleiro->pecasVermelhas[nPeca], Casa);
				Casa->pecas++;
			}

		}
		else if(LIS_ProcurarValor(tabuleiro->tab->Reta_Final_Vermelha, P_getCasa(tabuleiro->pecasVermelhas[nPeca])) == LIS_CondRetOK){
		// casa corrente é onde se encontra a peça (CASA ESPECIAL - a peça foi achada numa casa especial) (movimento vermelho a vermelho)
			CasaEspecial * Casa = (CasaEspecial*) LIS_ObterValor(tabuleiro->tab->Reta_Final_Vermelha);
			if(Casa->num==5){
				return TAB_CondRetMovimentoInvalido;
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
	// Função responsável pelo movimento das peças Azuis e por permitir que as mesmas comam uma às outras(ou não)
	if((casas == 1 || casas ==6) && P_getCasa(tabuleiro->pecasAzuis[nPeca]) == NULL){
		CasaNormal* Casa;
		LIC_IrInicioLista(tabuleiro->tab->Tab_principal);
		LIC_Avancar(tabuleiro->tab->Tab_principal, 25);
		Casa = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
		P_setCasa(tabuleiro->pecasAzuis[nPeca], Casa);
		Casa->pecas[1]++;
	}
	else if((casas != 1 && casas !=6) && P_getCasa(tabuleiro->pecasAzuis[nPeca]) == NULL){
		return TAB_CondRetNaoEstaEmJogo;
	}
	else if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasAzuis[nPeca])) == LIC_CondRetOK){ 
		// casa corrente é onde se encontra a peça (CASA NORMAL - a peça foi achada numa casa normal)
			int i=0;
			CasaNormal* Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
			Casa->pecas[1]--;
			LIC_Avancar(tabuleiro->tab->Tab_principal, 1);
			Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
			i++;
			while(i<casas && Casa->entrada!=Azul){
				LIC_Avancar(tabuleiro->tab->Tab_principal, 1);
				Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
				i++;
			}
			if(i==casas){ // andou tudo sem passar por entrada (ou parou bem sobre uma) (moviento branco a branco) em direção a uma casa branca agora !!!
				int k=0;

				CasaNormal* iVermelho;
				CasaNormal* iAmarelo;
				CasaNormal* iVerde;
				LIC_IrInicioLista(tabuleiro->tab->Tab_principal);
				iVermelho = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
				LIC_Avancar(tabuleiro->tab->Tab_principal, 12);
				iAmarelo = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
				LIC_Avancar(tabuleiro->tab->Tab_principal, 12);
				iVerde = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);

				P_setCasa(tabuleiro->pecasAzuis[nPeca], (void*)Casa);
				Casa->pecas[1]++;
			//==========Verifica se a peça vai comer a outra ou não===========//
				if(Casa->pecas[0] == 1 && Casa!=iVermelho){ // há uma peça vermelha na casa
					Casa->pecas[0]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 peças azuis é a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasVermelhas[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){
								P_setCasa(tabuleiro->pecasVermelhas[k], NULL);
							}
						}
					}
				}
				if(Casa->pecas[2] == 1 && Casa!=iAmarelo){// há uma peça amarela na casa
					Casa->pecas[2]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 peças amarelas é a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasAmarelas[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){ 
								P_setCasa(tabuleiro->pecasAmarelas[k], NULL);
							}
						}
					}
				}
				if(Casa->pecas[3] == 1 && Casa!=iVerde){ // há uma peça verde na casa
					Casa->pecas[3]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 peças verdes é a que esta ali
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
			else{ // andou até uma entrada antes de completar as casas (movimento branco a azul)
				CasaEspecial* Casa;
				IrInicioLista(tabuleiro->tab->Reta_Final_Azul);
				LIS_AvancarElementoCorrente(tabuleiro->tab->Reta_Final_Azul, casas-i-2); //mover o que faltou
				Casa = (CasaEspecial*)LIS_ObterValor(tabuleiro->tab->Reta_Final_Azul);
				P_setCasa(tabuleiro->pecasAzuis[nPeca], Casa);
				Casa->pecas++;
			}

		}
		else if(LIS_ProcurarValor(tabuleiro->tab->Reta_Final_Azul, P_getCasa(tabuleiro->pecasAzuis[nPeca])) == LIS_CondRetOK){
		// casa corrente é onde se encontra a peça (CASA ESPECIAL - a peça foi achada numa casa especial) (movimento azul a azul)
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
	// Função responsável pelo movimento das peças Amarelas e por permitir que as mesmas comam uma às outras(ou não)
	if((casas == 1 || casas ==6) && P_getCasa(tabuleiro->pecasAmarelas[nPeca]) == NULL){
		CasaNormal* Casa;
		LIC_IrInicioLista(tabuleiro->tab->Tab_principal);
		LIC_Avancar(tabuleiro->tab->Tab_principal, 12);
		Casa = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
		P_setCasa(tabuleiro->pecasAmarelas[nPeca], Casa);
		Casa->pecas[2]++;
	}
	else if((casas != 1 && casas !=6) && P_getCasa(tabuleiro->pecasAmarelas[nPeca]) == NULL){
		return TAB_CondRetNaoEstaEmJogo;
	}
	else if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasAmarelas[nPeca])) == LIC_CondRetOK){ 
		// casa corrente é onde se encontra a peça (CASA NORMAL - a peça foi achada numa casa normal)
			int i=0;
			CasaNormal* Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
			Casa->pecas[2]--;
			LIC_Avancar(tabuleiro->tab->Tab_principal, 1);
			Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
			i++;
			while(i<casas && Casa->entrada!=Amarelo){
				LIC_Avancar(tabuleiro->tab->Tab_principal, 1);
				Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
				i++;
			}
			if(i==casas){ // andou tudo sem passar por entrada (ou parou bem sobre uma) (moviento branco a branco)
				int k=0;

				CasaNormal* iVermelho;
				CasaNormal* iAzul;
				CasaNormal* iVerde;
				LIC_IrInicioLista(tabuleiro->tab->Tab_principal);
				iVermelho = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
				LIC_Avancar(tabuleiro->tab->Tab_principal, 12);
				iAzul = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
				LIC_Avancar(tabuleiro->tab->Tab_principal, 12);
				iVerde = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);

				P_setCasa(tabuleiro->pecasAmarelas[nPeca], (void*)Casa);
				Casa->pecas[2]++;
			//==========Verifica se a peça vai comer a outra ou não===========//
				if(Casa->pecas[1] == 1 && Casa!=iAzul){ // há uma peça azul na casa
					Casa->pecas[1]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 peças azuis é a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasAzuis[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){
								P_setCasa(tabuleiro->pecasAzuis[k], NULL);
							}
						}
					}
				}
				if(Casa->pecas[0] == 1 && Casa!=iVermelho){// há uma peça vermelha na casa
					Casa->pecas[0]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 peças amarelas é a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasVermelhas[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){ 
								P_setCasa(tabuleiro->pecasVermelhas[k], NULL);
							}
						}
					}
				}
				if(Casa->pecas[3] == 1 && Casa!=iVerde){ // há uma peça verde na casa
					Casa->pecas[3]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 peças verdes é a que esta ali
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
			else{ // andou até uma entrada antes de completar as casas (movimento branco a amarelo)
				CasaEspecial* Casa;
				IrInicioLista(tabuleiro->tab->Reta_Final_Amarela);
				LIS_AvancarElementoCorrente(tabuleiro->tab->Reta_Final_Amarela, casas-i-2); //mover o que faltou
				Casa = (CasaEspecial*)LIS_ObterValor(tabuleiro->tab->Reta_Final_Amarela);
				P_setCasa(tabuleiro->pecasAmarelas[nPeca], Casa);
				Casa->pecas++;
			}

		}
		else if(LIS_ProcurarValor(tabuleiro->tab->Reta_Final_Amarela, P_getCasa(tabuleiro->pecasAmarelas[nPeca])) == LIS_CondRetOK){
		// casa corrente é onde se encontra a peça (CASA ESPECIAL - a peça foi achada numa casa especial) (movimento amarelo a amarelo)
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
	// Função responsável pelo movimento das peças Verdes e por permitir que as mesmas comam uma às outras(ou não)
	if((casas == 1 || casas ==6) && P_getCasa(tabuleiro->pecasVerdes[nPeca]) == NULL){
		CasaNormal* Casa;
		LIC_IrInicioLista(tabuleiro->tab->Tab_principal);
		LIC_Avancar(tabuleiro->tab->Tab_principal, 38);
		Casa = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
		P_setCasa(tabuleiro->pecasVerdes[nPeca], Casa);
		Casa->pecas[3]++;
	}
	else if((casas != 1 && casas !=6) && P_getCasa(tabuleiro->pecasVerdes[nPeca]) == NULL){
		return TAB_CondRetNaoEstaEmJogo;
	}
	else if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasVerdes[nPeca])) == LIC_CondRetOK){ 
		// casa corrente é onde se encontra a peça (CASA NORMAL - a peça foi achada numa casa normal)
			int i=0;
			CasaNormal* Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
			Casa->pecas[3]--;
			LIC_Avancar(tabuleiro->tab->Tab_principal, 1);
			Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
			i++;
			while(i<casas && Casa->entrada!=Verde){
				LIC_Avancar(tabuleiro->tab->Tab_principal, 1);
				Casa = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
				i++;
			}
			if(i==casas){ // andou tudo sem passar por entrada (ou parou bem sobre uma) (moviento branco a branco)
				int k=0;

				CasaNormal* iVermelho;
				CasaNormal* iAzul;
				CasaNormal* iAmarelo;
				LIC_IrInicioLista(tabuleiro->tab->Tab_principal);
				iVermelho = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
				LIC_Avancar(tabuleiro->tab->Tab_principal, 12);
				iAzul = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);
				LIC_Avancar(tabuleiro->tab->Tab_principal, 12);
				iAmarelo = (CasaNormal*)LIC_ObterValor(tabuleiro->tab->Tab_principal);

				P_setCasa(tabuleiro->pecasVerdes[nPeca], (void*)Casa);
				Casa->pecas[3]++;
			//==========Verifica se a peça vai comer a outra ou não===========//
				if(Casa->pecas[1] == 1 && Casa!=iAzul){ // há uma peça azul na casa
					Casa->pecas[1]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 peças azuis é a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasAzuis[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){
								P_setCasa(tabuleiro->pecasAzuis[k], NULL);
							}
						}
					}
				}
				if(Casa->pecas[2] == 1 && Casa!=iAmarelo){// há uma peça amarela na casa
					Casa->pecas[2]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 peças amarelas é a que esta ali
						if(LIC_ProcurarValor(tabuleiro->tab->Tab_principal, P_getCasa(tabuleiro->pecasAmarelas[k])) == LIC_CondRetOK){
							CasaNormal* aux = (CasaNormal*) LIC_ObterValor(tabuleiro->tab->Tab_principal);
							if(aux == Casa){ 
								P_setCasa(tabuleiro->pecasAmarelas[k], NULL);
							}
						}
					}
				}
				if(Casa->pecas[0] == 1 && Casa!=iVermelho){ // há uma peça vermelha na casa
					Casa->pecas[0]=0;
					for(k=0;k<4;k++){//descobrir qual das 4 peças verdes é a que esta ali
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
			else{ // andou até uma entrada antes de completar as casas (movimento branco a verde)
				CasaEspecial* Casa;
				IrInicioLista(tabuleiro->tab->Reta_Final_Verde);
				LIS_AvancarElementoCorrente(tabuleiro->tab->Reta_Final_Verde, casas-i-2); //mover o que faltou
				Casa = (CasaEspecial*)LIS_ObterValor(tabuleiro->tab->Reta_Final_Verde);
				P_setCasa(tabuleiro->pecasVerdes[nPeca], Casa);
				Casa->pecas++;
			}

		}
		else if(LIS_ProcurarValor(tabuleiro->tab->Reta_Final_Verde, P_getCasa(tabuleiro->pecasVerdes[nPeca])) == LIS_CondRetOK){
		// casa corrente é onde se encontra a peça (CASA ESPECIAL - a peça foi achada numa casa especial) (movimento verde a verde)
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
	// Libera o espaço de momória da casa
	if(pValor != NULL)
	{
		free(pValor);
	}
	return;
} 

