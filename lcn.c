#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "partida.h"
#include "novojogador.h"

void adicionarjugadores(PARTIDA *partida){
	int i,x;
	for(i=0; i<partida->njogadores; i++){
		x = mainSelect("Base_de_datos/Jogadores.data");
		if(x != 0){
			readPlayer(&partida->players[i],x);
			printPlayer(&partida->players[i]);	
		}
	}
}

int main(int argc, char const *argv[])
{
	int op,x;
	PARTIDA *partida = (PARTIDA*) malloc(sizeof(PARTIDA)); 
	do{
		op = mainSelect("Ficheiros_de_texto/main");
		switch(op){
			case 1:
				break;
			case 2:
				x = mainSelect("Ficheiros_de_texto/planets");
				system("cls");
				printHeader();
				printf("\n\n\n");
				NEWGAME(partida,x);
				adicionarjugadores(partida);
				break;
			case 3:
				system("cls");
				printHeader();
				novoJogador();
				break;
			case 4:
			case 0:
				if(partida == NULL)
					freeMemoryPartida(partida);
				break;
		}	
		
	}
	while(op != 0 && op!=4 );
	
	return 0;
}

