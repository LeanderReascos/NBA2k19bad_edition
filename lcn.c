#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "partida.h"
#include "novojogador.h"
#include <time.h>
#include "instrucciones.h"

#define NUEVOJUEGO 1
#define EXIT 4
#define NEWPLAYER 2
#define INSTRUCCIONES 3

void adicionarjugadores(PARTIDA *partida){
	int i,x;
	for(i=0; i<partida->njogadores; i++){
		x = mainSelect("Base_de_datos/Jogadores.data");
		if(x != 0){
			readPlayer(&partida->players[i],x);
		}
	}
}

void openMusic(){
	FILE * file;
	file=fopen("MUSICAS/.commands","w");
	if(file==NULL){
		printf("nao abriu commands\n");
		exit(-1);
	}
	fprintf(file, "play");
	fclose(file);

	FILE *py;
    py = popen("py", "w");
    if (py == NULL) {
        printf("Erro ao abrir pipe para o python.\n"
            "Instale python, dependencia necesaria para o funcionamento completo do programa\n");
        exit(0);
    }
    fprintf(py, "exec(open('MUSICAS/game.py').read())");

    fclose(py);
}

int main(int argc, char const *argv[])
{
	openMusic();

	int op,x;
	PARTIDA *partida = (PARTIDA*) malloc(sizeof(PARTIDA)); 
	do{
		op = mainSelect("Ficheiros_de_texto/main");
		switch(op){
			case INSTRUCCIONES:
				instructions();
				break;
			case NUEVOJUEGO:
				x = mainSelect("Ficheiros_de_texto/planets");
				system("cls");
				printHeader();
				printf("\n\n\n");
				NEWGAME(partida,x);
				adicionarjugadores(partida);
				if(partida->njogadores > 1)
					x = mainSelect("Ficheiros_de_texto/mode");
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
	while(op != 0 && op!=4 );
	
	return 0;
}

