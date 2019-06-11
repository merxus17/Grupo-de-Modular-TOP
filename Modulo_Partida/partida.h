#include "tabuleiro.h"


typedef enum{
	PAR_CondRetOK

} PAR_tpCondRet;



PAR_tpCondRet PAR_Ready ();

PAR_tpCondRet  PAR_Set (int players, Cor cor[]);

int  PAR_Dice();

void PAR_Max(int d[], int same[]);

void PAR_Colors (Cor cor[], char **colors);