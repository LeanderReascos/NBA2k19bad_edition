#include <stdio.h>
#include <stdlib.h>
#include "libs/main.h"
#include "libs/partida.h"
#include "libs/novojogador.h"
#include <time.h>
#include "libs/instrucciones.h"

#define NUEVOJUEGO 1
#define EXIT 6
#define WEB 5
#define NEWPLAYER 2
#define INSTRUCCIONES 3
#define SETTINGS 4

/*Abre o reprodutor de musica feito em python*/
void openMusic(){
	FILE * file;
	file=fopen("libs/MUSICAS/.commands","w");
	if(file==NULL){
		printf("Commands didn't open'\n");
		exit(-1);
	}
	fprintf(file, "play");
	fclose(file);

	FILE *py;
    py = popen("py", "w");
    if (py == NULL) {
        printf("Error opening pipe to python.\n" 
            "This program needs python to function fully, please install it.\n");  
        exit(0);
    }
    fprintf(py, "exec(open('libs/game.py').read())");

    fclose(py);
}

/*Função main onde espera a seleção do utilizador para ingresar em alguma opção do menu*/
int main(int argc, char const *argv[])
{
	openMusic();

	int op,x;
	PARTIDA *partida = (PARTIDA*) malloc(sizeof(PARTIDA)); 
	if(partida == NULL) exit(-1);
	setsDefault(partida);

	do{
		op = mainSelect("main");
		switch(op){
			case WEB:
				system("start libs/Web/index.html");
				break;
			case SETTINGS:
				do{
					x = mainSelect("settings");
					segundoMenu(x,&partida->settings);
				}
				while(x != 0);
				break;
			case INSTRUCCIONES:
				instructions();
				break;
			case NUEVOJUEGO:

				x = valueSelect("planets");
				system("cls");
				printHeader();
				printf("\n\n\n");
				NEWGAME(partida,x);
				adicionarjugadores(partida);
				if(partida->njogadores > 1)
					x = valueSelect("mode");
				else
					x = 1;
				seleccionarModoDeJogo(partida,x);
				printPartida(partida);
				printf("\n");
				system("pause");
				playGame(partida);
				system("cls");
				
				break;

			case NEWPLAYER:
				system("cls");
				printHeader();
				novoJogador();
				break;
			case EXIT:
			case 0:
				Musica('s');
				if(partida == NULL)
					freeMemoryPartida(partida);
				break;
		}	
		
	}
	while(op != 0 && op!=EXIT ); //Nunca sai unicamente se carrega no ESC ou seleciona a função exit
	
	return 0;
}

