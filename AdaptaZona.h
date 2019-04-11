#include <stdio.h>
#include <stdlib.h>
#include "partida.h"


/* run this program using the console pauser or add your own getch, system("pause") or input loop */


void AdaptaZona(PLAYER* player,int zonaatual,CAMPO* campo, int n){
	switch(n){
		
		case 1:
			gerarPosicoes(player,campo,zonaatual+1);
		break;
		
		case 2:
			gerarPosicoes(player,campo,zonaatual-1);
		break;	
		
		case 3:
			gerarPosicoes(player,campo,zonaatual);
		break;	
	
		
	}
}
