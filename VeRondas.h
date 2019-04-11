#include <stdio.h>
#include <stdlib.h>
#include "partida.h"


/* run this program using the console pauser or add your own getch, system("pause") or input loop */


void VeRondas(PARTIDA* partida)
{
	int i,j=1,m;
	int* n=(int*) malloc(sizeof(int)*(partida->njogadores));            				/////array das somas dos pontos dos jogadores por ordem de como os proprios estao organizados
	int* jogadoresprimeiro=(int*) malloc(sizeof(int));                 					 /////array que guarda os indices dos jogadores com maior pontuaçao
	jogadoresprimeiro[0]=0;
	int maior=n[0];
	SomaRondas(partida,n);
	for(i=1;i<partida->njogadores;i++){
		if(n[i]>maior){
			maior=n[i];
			//free(jogadoresprimeiro);
			//apagar array e colocar apenas o novo vencedor
			j=1;
			jogadoresprimeiro=(int*) realloc(sizeof(int)*j);
			jogadoresprimeiro[0]=i;
		}
		else if(n[i]=maior){
			j++;
			jogadoresprimeiro=(int*) realloc(sizeof(int)*j);
			jogadoresprimeiro[j-1]=i;
		}
		
	}	
	if(partida->modoDeJogo==2 && j>1){                                        				/////caso seja modo 2-adicionar rondas e temos varios jogadores com a maior pontuaçao
	
	for(m=0;m<j;m++){
		partida->players[jogadoresprimeiro[m]].numeroRondas++;                				//////aumento do numero de rondas usando o vetor jogadoresprimeiro porque guarda os indices dos jogadores que estejam nesta situacao
	}

	}
	
	free(n);
	free(jogadoresprimeiro);
	
	
}


void SomaRondas (PARTIDA* partida,int* n){
	int soma,i;
	
	for(i=0;i<partida->njogadores;i++){
		soma=0;
		for(j=0;j<partida->players[i].numeroRondas;j++)
		{
			soma+=partida->players[i].pontosRondas[j];
		}
		n[i]=soma;
	
	}
	
}


