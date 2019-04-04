#include <string.h>
#include "campoDeJogo.h"
#include "launch.h"

typedef struct jogador{
	//Base de datos
	char *name;
	float altura;
	//posição
	float posX;
	float posY;
	//Launch
	BOLA bola;
	//Rondas
	int numeroRondas;
	int *pontosRondas;
}PLAYER;

typedef struct partida{
	int modoDeJogo;
	int njogadores;
	PLAYER *players;
	CAMPO  campo;
	
}PARTIDA;


typedef struct planeta{
	char nome[8];
	float lcampo;
	float acampo;
	float g;
	
}PLANETA;

void printPlayer(PLAYER *player){
	printf("%s\n%f",player->name,player->altura );
}


void readPlayer(PLAYER *player,int n){
	int i = 0,j;
	FILE *fp;
	fp = fopen("Base_de_datos/Jogadores.data","r");
	if(fp == NULL){
		printf("Error ler jogador\n");
		exit(-1);
	}
	j = 0;
	char buffer[100];
	char *token;
	while(fgets(buffer,sizeof(buffer),fp) && i!=n){
		if(i==n-1){
			token = strtok(buffer,"-");
			while(token != NULL){
				if(j==0){
					player->name = (char *) malloc(strlen(token)*sizeof(char));
					strcpy(player->name,token);
				}
				else if(j==1)
					player->altura = atof(token);
				j++;
				token = strtok(NULL, "-");
			}
		}
		i++;
	}


}

void seleccionarModoDeJogo(PARTIDA *partida, int modoDeJogo){

}

void freeMemoryPartida(PARTIDA *partida){
	free(partida->players);
	free(partida);
	freeCampo(partida->campo);
}

void NEWGAME(PARTIDA *partidanova ,int opcao){

	PLANETA* planeta;
	planeta=(PLANETA*) malloc(sizeof(PLANETA));

	if(planeta == NULL){
		printf("Error memoria pleneta\n");
		exit(-1);
	}

	printf ("How many players will play this round?\n\t");
	int nJugadores;
	scanf("%d",&nJugadores);
	partidanova->njogadores = nJugadores;

	partidanova->players = (PLAYER *) malloc(partidanova->njogadores*sizeof(PLAYER));

	FILE* fp;
	fp=fopen("Base_de_datos/planets.data","r");
	if(fp==NULL){
		printf("ERROR\n");
		exit(-1);
	} 
	//fread(planeta,sizeof(PLANETA),opcao,fp);
	//ler o planeta-NOVA MANEIRA

	int i=0;
	do{
		i++;
		fread(planeta,sizeof(PLANETA),1,fp);
		
		
	}while(i!=opcao && i<=9);


	partidanova->campo.lChar=128;
	partidanova->campo.aChar=50;
	partidanova->campo.g=planeta->g;
	partidanova->campo.ancho=planeta->acampo;
	partidanova->campo.largo=planeta->lcampo;
	strcpy(partidanova->campo.nome,planeta->nome);
	strcpy(partidanova->campo.file,"Ficheiros_de_texto/campo");

	CAMPO *c = &partidanova->campo;
	readCampo(c);

}