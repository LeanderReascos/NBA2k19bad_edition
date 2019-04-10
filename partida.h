#include <string.h>
#include "campoDeJogo.h"
#include "launch.h"
#include "valoresLaunch.h"
#include <math.h>
#include <time.h>

#define PI 3.14

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
	int nRondas;
	PLAYER *players;
	CAMPO  campo;
	
}PARTIDA;


typedef struct planeta{
	char nome[8];
	float lcampo;
	float acampo;
	float g;
	
}PLANETA;



float random(float min, float max){
	
	float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min ); 
}


void gerarPosicoes(PLAYER* jogador,CAMPO* campo,int n){

	//LIMITES ZONA 1
	float xmin1=(5.05/15)*(campo->largo);
	float xmax1=(campo->largo)-xmin1;

	float rquadrado=pow((2.45/15)*(campo->largo),2);


	//LIMITES ZONA 2

	float xmin2=0.9/15*(campo->largo);
	float xmax2=(campo->largo)-xmin2;
	float a=-8.95/14*(campo->ancho)/pow((xmin2-(campo->largo)/2),2);





	switch (n){
		case 1:


			jogador->posX=random(xmin1,xmax1);
			float xcesto1=(campo->largo)/2-1;
			float xcesto2=(campo->largo)/2+1;


			float xlinha=fabs((campo->largo)/2-(jogador->posX));	                                        //temos que o ylinha da circunferencia  igual a sqrt de (rquadrado-xlinha^2)
			float ymax=(5.8/14*(campo->ancho))+sqrt(rquadrado-pow(xlinha,2)) ;


		if(((jogador->posX)>xcesto1 ) && ((jogador->posX)<xcesto2)){
			float ymin=(8.57/100)*(campo->ancho)+sqrt(1-pow(xlinha,2));
			jogador->posY=random(ymin,ymax);


		}

		else{

			jogador->posY=random(8.57/100*(campo->ancho),ymax);
		}
			break;


		case 2:

			jogador->posX=random(xmin2,xmax2);
			float xlinha2=fabs((campo->largo)/2-(jogador->posX));
			float ymin2=(5.8/14*(campo->ancho))+sqrt(rquadrado-pow(xlinha2,2)) ;                                          //zona 1 para os casos em que x "esta dentro desta"

			float ymax2=a*pow(((jogador->posX)-(campo->largo)/2),2)+8.95/14*(campo->ancho);


			if((jogador->posX)>xmin1 &&((jogador->posX)<xmax1)){
				jogador->posY=random(ymin2,ymax2);
			}
			else{
				jogador->posY=random(((8.57/100)*(campo->ancho)),ymax2);}
			break;

		case 3:
		    jogador->posX=random(0,campo->largo);


			float ymin=a*pow(((jogador->posX)-(campo->largo)/2),2)+8.95/14*(campo->ancho);               

			do{
			if(((jogador->posX)>xmin2)&&((jogador->posX)<xmax2))
			{
				jogador->posY=random(ymin,campo->ancho);
			}

			else{
				jogador->posY=random((8.57/100)*(campo->ancho),campo->ancho);
			}
			}while((jogador->posY)<(8.57/100)*(campo->ancho));

			break;	
	}	
}





void printPlayer(PLAYER *player){
	printf("\t%s\n\t%f\n",player->name,player->altura);
	int i;
	for(i=0; i<player->numeroRondas;i++){
		printf("\t\tROUND %d: %d",i+1,player->pontosRondas[i]);
	}
}

void printPartida(PARTIDA *partida){
	system("cls");
	printf("\n\n\t\t\t*** %s ***\n\n\n",partida->campo.nome);
	printCampo(&partida->campo);
	printf("\n\n>>> ");
	switch(partida->modoDeJogo){
		case 1:
				printf("CASUAL\n");
				break;
		case 2:
				printf("COMPETITIVE\n");
				break;
		case 3:
				printf("SUDDEN DEATH\n");
				break;
	}
	int i;
	for(i=0; i<partida->njogadores;i++){
		printf("\n%d. \n",i+1);;
		printPlayer(&partida->players[i]);
	}

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
	int i,j;
	partida->modoDeJogo=modoDeJogo;
	
	switch(modoDeJogo){
		case (1):
			for(i=0;i<partida->njogadores;i++){
				partida->players[i].numeroRondas=5;
				partida->nRondas = 5;
				partida->players[i].pontosRondas=(int*) malloc(5*sizeof(int));

				for(j=0; j<partida->players[i].numeroRondas;j++){
					partida->players[i].pontosRondas[j] = 0;
				}
			}
			break;
		case(2):
			for(i=0;i<partida->njogadores;i++){
				partida->players[i].numeroRondas=5;
				partida->nRondas = 5;
				partida->players[i].pontosRondas=(int*) malloc(5*sizeof(int));

				for(j=0; j<partida->players[i].numeroRondas;j++){
					partida->players[i].pontosRondas[j] = 0;
				}
			}
			break;
		case(3):
			for(i=0;i<partida->njogadores;i++){
				partida->players[i].numeroRondas=1;
				partida->nRondas = 1;
				partida->players[i].pontosRondas=(int*) malloc(sizeof(int));

				for(j=0; j<partida->players[i].numeroRondas;j++){
					partida->players[i].pontosRondas[j] = 0;
				}
			}
			break;
	}
	
	for(i=0; i<partida->njogadores; i++){
		gerarPosicoes(&partida->players[i],&partida->campo,1);
		printf("%f %f\n",partida->players[i].posX,partida->players[i].posY);
		system("pause");
		addJugador(partida->players[i].posX,partida->players[i].posY,'0'+i+1,&partida->campo);
	}

}

void freeMemoryPartida(PARTIDA *partida){
	free(partida->players);
	free(partida);
	freeCampo(&partida->campo);
}

void NEWGAME(PARTIDA *partidanova ,int opcao){
	srand((unsigned int)time(NULL));

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

void playGame(PARTIDA *partida){
	int i,j;
	for(i=0; i<partida->nRondas; i++){
		for(j=0; j<partida->njogadores;j++){
			system("cls");
			printPlayer(&partida->players[j]);
			printf("\n\nRONDA %d",i+1);
			printf("\n");
			system("pause");
			system("cls");
			partida->players[j].bola.distCesto = distCesto(partida->players[j].posX,partida->players[j].posY,partida->campo.largo,partida->campo.ancho);
			printf("Distance to the basket: %f\n", partida->players[j].bola.distCesto);
			printf("Jump Velocity: 0.00\n");
			float v = velocidadeSalto(partida->players[j].altura,partida->campo.g);
			partida->players[j].bola.h0 =  pow(v,2)/(2*partida->campo.g) + partida->players[j].altura;
			partida->players[j].bola.g = partida->campo.g;
			system("cls");
			printf("Launch Velocity: 0.00\n");
			partida->players[j].bola.v = velocidadeLanzamento(20,partida->campo.g);
			system("cls");
			printf("Launch Angle: 1.00\n");
			partida->players[j].bola.ang = anguloLanzamento()*PI/180;
			parabola(&partida->players[j].bola);
			system("pause");
			if(partida->players[j].bola.cesto)
				printf("CESTO\n");
			system("pause");

			
		}
	}
}