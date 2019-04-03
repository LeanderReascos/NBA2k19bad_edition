#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "partida.h"
#include "launch.h"
#include "novojogador.h"

int main(int argc, char const *argv[])
{
	int op,x;
	PARTIDA *partida;
	do{
		op = mainSelect("Ficheiros_de_texto/main");
		switch(op){
			case 1:
				break;
			case 2:
				x = mainSelect("Ficheiros_de_texto/planets");
				NEWGAME(partida,x);

				break;
			case 3:
				system("cls");
				printHeader();
				novoJogador();
				break;
			case 4:
			case 0:
				break;
		}	
		
	}
	while(op != 0 && op!=4 );
	
	return 0;
}

