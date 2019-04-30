#include <string.h>
#include "campoDeJogo.h"
#include "launch.h"
#include "valoresLaunch.h"
#include <math.h>
#include <time.h>
#include "settings.h"

#define PI 3.14
#define POSINICIO 3

#define CASUAL 1
#define COMPETITIVE 2
#define SUDDEN_DEATH 3


typedef struct jogador{
	//Base de datos
	char *name;
	float altura;
	//posição
	float posX;
	float posY;
	int zona;
	//Launch
	BOLA bola;
	//Rondas
	int numeroRondas;
	int *pontosRondas;
	int total;
	int *fallos;
}PLAYER;

typedef struct partida{
	int modoDeJogo;
	int njogadores;
	int nRondas;
	int nPlaneta;
	PLAYER *players;
	CAMPO  campo;
	int tentativas;

	//settings
	SETTINGS settings;
	
}PARTIDA;


typedef struct planeta{
	char nome[8];
	float lcampo;
	float acampo;
	float g;

	
}PLANETA;

void setsDefault(PARTIDA *partida){
	partida->settings.musica = true;
	partida->settings.videos  = false;
	partida->settings.animacion  = false;
	partida->settings.gnuplot  = false;
	partida->settings.velocidadeAnimacion = 3;
	partida->settings.nR[0] = 3; //ronda casual
	partida->settings.nR[1] = 1; //competitive
	partida->settings.nT[0] = 1; //tentaitvas casual
	partida->settings.nT[1] = 1; //tentativas competitive
}

void resultado(PLAYER *player){
	int i;
	int soma = 0;
	for(i=0; i<player->numeroRondas; i++){
		soma += player->pontosRondas[i];
	}
	player->total = soma;
}


void SomaRondas (PARTIDA* partida,int* n){
	int soma,i,j;
	
	for(i=0;i<partida->njogadores;i++){
		resultado(&partida->players[i]);
		n[i]=partida->players[i].total;
	
	}
	
	
}

int VeRondas(PARTIDA* partida,int *lastronda)
{
	int res = 0;

	int i,j=1,m;
	int* n=(int*) malloc(sizeof(int)*(partida->njogadores));            				/////array das somas dos pontos dos jogadores por ordem de como os proprios estao organizados
	int* jogadoresprimeiro=(int*) malloc(sizeof(int));                 					 /////array que guarda os indices dos jogadores com maior pontuaÃ§ao
	jogadoresprimeiro[0]=0;

	SomaRondas(partida,n);
	int maior=n[0];
	for(i=1;i<partida->njogadores;i++){
		if(n[i]>maior){
			maior=n[i];
			j=1;
			jogadoresprimeiro=(int*) realloc(jogadoresprimeiro,sizeof(int)*j);
			jogadoresprimeiro[0]=i;
		}
		else if(n[i]==maior){
			j++;
			jogadoresprimeiro=(int*) realloc(jogadoresprimeiro,sizeof(int)*j);
			jogadoresprimeiro[j-1]=i;
		}
	
	}	
	if(partida->modoDeJogo==2 && j>1){                                        				/////caso seja modo 2-adicionar rondas e temos varios jogadores com a maior pontuaÃ§ao
	
	for(m=0;m<j;m++){
		int aux = partida->players[jogadoresprimeiro[m]].numeroRondas;
		(*lastronda) = aux;
		partida->players[jogadoresprimeiro[m]].numeroRondas+=2;             			//////aumento do numero de rondas usando o vetor jogadoresprimeiro porque guarda os indices dos jogadores que estejam nesta situacao
		partida->players[jogadoresprimeiro[m]].pontosRondas=(int*) realloc(partida->players[jogadoresprimeiro[m]].pontosRondas,sizeof(int)*(partida->players[jogadoresprimeiro[m]].numeroRondas)); 
		partida->players[jogadoresprimeiro[m]].fallos=(int*) realloc(partida->players[jogadoresprimeiro[m]].fallos,sizeof(int)*(partida->players[jogadoresprimeiro[m]].numeroRondas)); 
		res = 1;
		if(partida->players[jogadoresprimeiro[m]].pontosRondas == NULL || partida->players[jogadoresprimeiro[m]].fallos == NULL)
				exit(-1);
		int k;
		for(k=0; k<2; k++){
			partida->players[jogadoresprimeiro[m]].pontosRondas[aux+k] = 0;
			partida->players[jogadoresprimeiro[m]].fallos[aux+k] = 0;
		}
	}

	}
	
	free(n);
	free(jogadoresprimeiro);
	if(res)			partida->nRondas+=2;  
	return res;
	
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




void readPlayer(PLAYER *player,int n){
	int i = 0,j;
	FILE *fp;
	fp = fopen("Base_de_datos/Jogadores.data","r");
	if(fp == NULL){
		printf("Error in reading player.\n");
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
		case (CASUAL):
			partida->tentativas = partida->settings.nT[CASUAL-1];
			for(i=0;i<partida->njogadores;i++){
				partida->players[i].numeroRondas=	partida->settings.nR[CASUAL-1];
				partida->nRondas = 	partida->settings.nR[CASUAL-1];
				partida->players[i].pontosRondas=(int*) malloc(	partida->settings.nR[CASUAL-1]*sizeof(int));
				partida->players[i].fallos=(int*) malloc(	partida->settings.nR[CASUAL-1]*sizeof(int));

				for(j=0; j<partida->players[i].numeroRondas;j++){
					partida->players[i].pontosRondas[j] = 0;
					partida->players[i].fallos[j]= 0;
				}
			}
			break;
		case(COMPETITIVE):
			partida->tentativas = partida->settings.nT[COMPETITIVE-1];
			for(i=0;i<partida->njogadores;i++){
				partida->players[i].numeroRondas=	partida->settings.nR[COMPETITIVE-1];
				partida->nRondas = 	partida->settings.nR[COMPETITIVE-1];
				partida->players[i].pontosRondas=(int*) malloc(	partida->settings.nR[COMPETITIVE-1]*sizeof(int));
				partida->players[i].fallos=(int*) malloc(	partida->settings.nR[COMPETITIVE-1]*sizeof(int));
				for(j=0; j<partida->players[i].numeroRondas;j++){
					partida->players[i].pontosRondas[j] = 0;
					partida->players[i].fallos[j]= 0;
				}
			}
			break;
		case(SUDDEN_DEATH):
			partida->tentativas = 1;
			for(i=0;i<partida->njogadores;i++){
				system("color 4f");
				partida->players[i].numeroRondas=1;
				partida->nRondas = 1;
				partida->players[i].pontosRondas=(int*) malloc(sizeof(int));
				partida->players[i].fallos=(int*) malloc(sizeof(int));
				for(j=0; j<partida->players[i].numeroRondas;j++){
					partida->players[i].pontosRondas[j] = 0;
					partida->players[i].fallos[j]= 0;
				}
			}
			break;
	}
	gerarPosicoes(&partida->players[0],&partida->campo,POSINICIO);
	for(i=0; i<partida->njogadores; i++){
		partida->players[i].bola.bonus = 0;
		partida->players[i].zona = POSINICIO;
		partida->players[i].posX = partida->players[0].posX;
		partida->players[i].posY = partida->players[0].posY;
		addJugador(partida->players[i].posX,partida->players[i].posY,'I',&partida->campo);
	}

}


void freeMemoryPartida(PARTIDA *partida){
	int i;
	for(i=0; i < partida->njogadores; i++){
		free(partida->players[i].name);
		free(partida->players[i].pontosRondas);
		free(partida->players[i].fallos);
	}

	free(partida->players);
	freeCampo(&partida->campo);
	free(partida);
}

void NEWGAME(PARTIDA *partidanova,int opcao){
	srand((unsigned int)time(NULL));
	partidanova->nPlaneta = opcao;
	PLANETA* planeta;
	planeta=(PLANETA*) malloc(sizeof(PLANETA));

	if(planeta == NULL){
		printf("Error in planet memory.\n");
		exit(-1);
	}
	//printf ("How many players will play this round?\n\t");
	int nJugadores = 1;
	//scanf("%d",&nJugadores);
	int aux;
	do{
		system("cls");
		printHeader();	
		printtext(17,"Ficheiros_de_texto/subHeaders",7);
		printtext(nJugadores+2,"Ficheiros_de_texto/numberSelect",8);
		aux = selectNumber(&nJugadores);
	}
	while(aux != 0);
	
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

	switch(opcao){
		case 1:
				system("color 06");
				break;
		case 2:
				system("color 0e");
				break;
		case 3:
				system("color 08");
				break;
		case 4:
				system("color 02");
				break;
		case 5:
				system("color 84");
				break;
		case 6:
				system("color e0");
				break;
		case 7:
				system("color 03");
				break;
		case 8:
				system("color 02");
				break;
		case 9:
				system("color 09");
				break;
	}
	partidanova->campo.lChar=128;
	partidanova->campo.aChar=50;
	partidanova->campo.g=planeta->g;
	partidanova->campo.ancho=planeta->acampo;
	partidanova->campo.largo=planeta->lcampo;
	partidanova->campo.lin=0;
	strcpy(partidanova->campo.nome,planeta->nome);
	strcpy(partidanova->campo.file,"Ficheiros_de_texto/campo");

	CAMPO *c = &partidanova->campo;
	readCampo(c);

}

void somaPontos(PLAYER * player,int n,int aux){	
	switch(player->zona){
		case 1:
			if(aux==0)
				player->pontosRondas[n]++;
			
			else if(aux==1)
				player->pontosRondas[n]+=2;
			
			break;

		case 2:
			if(aux==0)
				player->pontosRondas[n]+=2;
			
			else if(aux==1)
				player->pontosRondas[n]+=3;
			
			break;	
		case 3:
			if(aux==0)
				player->pontosRondas[n]+=3;
				
			else if(aux==1)
				player->pontosRondas[n]+=4;
		break;
	}
}

void adaptaZona(PLAYER* player,CAMPO* campo, int n){
	switch(n){

		case 1:
			gerarPosicoes(player,campo,player->zona+1);
			player->zona++;
		break;

		case 2:
			gerarPosicoes(player,campo,player->zona-1);
			player->zona--;
		break;	

		case 3:
			gerarPosicoes(player,campo,player->zona);
		break;	


	}
}

void printPlayer(PLAYER *player){
	int i;
	int n = strlen(player->name);
	printf("|%s",player->name);
	for (i=n; i<24; i++){
		printf(" ");
	}
	printf("|   %.2f   ",player->altura);

	for(i=0; i<player->numeroRondas;i++){
		if(player->pontosRondas[i]>0)
			printf("|     %d     |   %d   ",player->pontosRondas[i],player->fallos[i]+1);
		else
			printf("|     %d     |   %d   ",player->pontosRondas[i],player->fallos[i]);
	}
	printf("|\n");
}


void printEncabezado(int n){
	int i;
	printf("| No |          NAME          |  HEIGHT  |");
	for(i=0; i<n;i++){
		printf("  ROUND %d  |  TRY  |",i+1);
	}
	printf("\n");
	for(i=0; i<42+21*n; i++){
		printf("-");
	}
	printf("\n");
}


void printPartida(PARTIDA *partida){
	system("cls");
	printtext(partida->nPlaneta,"Ficheiros_de_texto/planetsVisual",16);
	printf("\n");
	printtext(partida->modoDeJogo,"Ficheiros_de_texto/modesVisual",7);
	printf("\n\n\n");
	int i;

	printEncabezado(partida->nRondas);

	for(i=0; i<partida->njogadores;i++){
		if(i<9)
			printf("| %d  ",i+1);
		else 
			printf("| %d ",i+1);
		printPlayer(&partida->players[i]);
	}

	printf("\n");
	printCampo(&partida->campo);

}



void ordenar(PARTIDA *partida){
	int i,j;
	int mayor;
	PLAYER player;
	for(i=0; i<partida->njogadores; i++){
		resultado(&partida->players[i]);
	}

	for(i=0; i<partida->njogadores; i++){
		mayor = i;
		for(j=i; j<partida->njogadores; j++){
			if(partida->players[j].total>partida->players[i].total)
				mayor = j;
		}
		player = partida->players[i];
		partida->players[i] = partida->players[mayor];
		partida->players[mayor] = player;
	}
}


void infoprintPlayer(PLAYER *player,FILE *info,int nT,FILE *json){
	int i;
	int n = strlen(player->name);
	fprintf(info,"|%s",player->name);
	for (i=n; i<24; i++){
		fprintf(info," ");
	}
	fprintf(info,"|   %.2f   ",player->altura);

	int intentos=0;
	int fallos=0;
	fprintf(json, "{\"name\":\"%s\", \"height\": %.2f,\"NumberOfRounds\": %d,\"Rounds\":[", player->name,player->altura,player->numeroRondas);
	for(i=0; i<player->numeroRondas;i++){

		if(player->pontosRondas[i]>0){
			fprintf(info,"|     %d     |   %d   ",player->pontosRondas[i],player->fallos[i]+1);
			intentos+=player->fallos[i]+1;
		}
		else{
			fprintf(info,"|     %d     |   %d   ",player->pontosRondas[i],player->fallos[i]);
			intentos+=player->fallos[i];
		}	
		fprintf(json, "{\"points\":%d,\"tries\":%d}",player->pontosRondas[i],player->fallos[i]);
		
		if(i<player->numeroRondas-1)
			fprintf(json, "," );
		fallos+=player->fallos[i];
	}
	fprintf(json, "]}");
	fprintf(info,"|   %.1f   |\n",((intentos-fallos)/intentos)*100);
}


void fprintText(int n,char file[100],int a, FILE *info){
	FILE *fp;
	fp = fopen(file,"r");
	if(fp == NULL) exit(-1);

	int i=0;
	char buffer[160];
	while(fgets(buffer,sizeof(buffer),fp) && i < n*a ){
		if(i >= n*a-a)
			fprintf(info,"%s",buffer);
		i++;
	}
	fclose(fp);
}

void informacao(PARTIDA *partida){
	char name[100];
	printf("What do you want to name the file containing game information? \n");
	scanf (" %[^\n]%*c", name);
	strcat(name,".txt");

	FILE *json;
	json = fopen("Web/database.json","w");

	FILE *information;
	information = fopen(name,"w");

	if(json == NULL || information == NULL)
		exit(-1);

	fprintText(1,"Ficheiros_de_texto/header",16,information);
	fprintf(information,"\n\n\n");

	int i;
	int n=partida->nRondas;
	fprintf(information,"| No |          NAME          |  HEIGHT  |");
	for(i=0; i<n;i++){
		fprintf(information,"  ROUND %d  |  TRY  |",i+1);
	}
	fprintf(information,"  PTS%%  |");
	fprintf(information,"\n");
	for(i=0; i<42+21*n; i++){
		fprintf(information,"-");
	}
	fprintf(information,"---------\n");
	fprintf(json, "GameValues = '{\"nr\":%d,\"nj\":%d,\"t\":%d}'\n",partida->nRondas,partida->njogadores,partida->tentativas);
	fprintf(json, "data = '[");
	for(i=0; i<partida->njogadores;i++){
		if(i<9)
			fprintf(information,"| %d  ",i+1);
		else 
			fprintf(information,"| %d ",i+1);


		infoprintPlayer(&partida->players[i],information,partida->tentativas,json);
		if(i<partida->njogadores-1)
			fprintf(json, "," );
	}
	fprintf(json, "]'");
	fprintf(information,"\n");

	fclose(json);
	fclose(information);
}

void cesto(){
	FILE *py;
    py = popen("py", "w");
    if (py == NULL) {
        printf("Error opening pipe to python.\n"
            "This program needs python to function fully, please install it.\n"); 
        exit(0);
    }
    fprintf(py, "exec(open('video.py').read())");

    fclose(py);
}

void exitGame(int v,PARTIDA *partida){
	if(v == -10){
		int x = mainSelect("leave");
		if(x == 1){
			informacao(partida);
			exit(0);
		}
		else
			system("cls");
	}	
}

void runRonda(PARTIDA *partida, int j,int i, int k){
	system("cls");
	printtext(partida->nPlaneta,"Ficheiros_de_texto/planetsVisual",16);
	printf("\n");
	printtext(partida->modoDeJogo,"Ficheiros_de_texto/modesVisual",7);
	printf("\n\n\n");
	printPartida(partida);
	printf("\n\n");
	printEncabezado(partida->nRondas);
	if(j<9)
		printf("| %d  ",j+1);
	else 
		printf("| %d ",j+1);
	printPlayer(&partida->players[j]);
	partida->players[j].bola.distCesto = distCesto(partida->players[j].posX,partida->players[j].posY,partida->campo.largo,partida->campo.ancho);
	printf("\nVALUES: \n");
	printf("\tROUND %d \\ Try number %d\n",i+1,k+1);
	printf("\tDistance to the basket: %f\n", partida->players[j].bola.distCesto);
	printf("\tJump Velocity: 0.00");
	float v = velocidadeSalto(partida->players[j].altura,partida->campo.g);
	exitGame(v,partida);
	partida->players[j].bola.h0 =  pow(v,2)/(2*partida->campo.g) + partida->players[j].altura;
	partida->players[j].bola.g = partida->campo.g;
	printf("\n");
	printf("\tLaunch Velocity: 1.00");
	partida->players[j].bola.v = velocidadeLanzamento(partida->campo.g);
	exitGame(partida->players[j].bola.v,partida);
	printf("\n");
	printf("\tLaunch Angle: 1.00");
	float ang = anguloLanzamento();
	partida->players[j].bola.ang = ang*PI/180;
	exitGame(ang,partida);
	if(k == 0 || partida->players[j].fallos[i]%2 == 0){
		switch(partida->players[j].zona){
			case 1:
					partida->players[j].bola.aux = 0;				
					break;
			case 2:
					partida->players[j].bola.aux = 1;	
					break;
			case 3:
					partida->players[j].bola.aux = (rand() % 3)+1;	
					break;
		}
		geraObstaculo(&partida->players[j].bola);
	}
	//setting
	partida->players[j].bola.gnu = partida->settings.gnuplot;
	partida->players[j].bola.animacion = partida->settings.animacion;
	partida->players[j].bola.vAni = partida->settings.velocidadeAnimacion;

	parabola(&partida->players[j].bola);
	system("pause");		
			
}

void cestoAux(PLAYER *player, int n){
	FILE * file2;
	file2=fopen("VIDEOS/.videos","w");
	if(file2==NULL){
		printf("Commands didn't open'\n");
		//exit(-1);
	}
	if(n == 1)
		fprintf(file2, "%s", player->name);
	else
		fprintf(file2, "haha");
	fclose(file2);
}

int confirmRonda(PARTIDA *partida, int j,int i){
	int aux;
	if(partida->players[j].bola.cesto){
		cestoAux(&partida->players[j], 1);
		somaPontos(&partida->players[j],i,partida->players[j].bola.bonus);
		partida->players[j].bola.bonus = 1;
		if(partida->players[j].zona < 3)
			adaptaZona(&partida->players[j],&partida->campo,1);
		else
			adaptaZona(&partida->players[j],&partida->campo,3);

		aux = 0;
	}
	else{
		cestoAux(&partida->players[j], 2);
		partida->players[j].fallos[i]++;

		if(partida->players[j].fallos[i] == partida->tentativas || partida->players[j].fallos[i]%2 == 0){
			partida->players[j].bola.bonus = 0;
			if(partida->players[j].zona > 1)
				adaptaZona(&partida->players[j],&partida->campo,2);
			else
				adaptaZona(&partida->players[j],&partida->campo,3);
			aux = 1;
		}
		else {
			partida->players[j].bola.bonus = 0;
			aux = 1;
		}
		
	}
	if(partida->settings.videos){
		cesto();
		system("pause");
		system("cls");
	}

	readCampo(&partida->campo);
	int a;

	for(a=0; a<partida->njogadores; a++){
		addJugador(partida->players[a].posX,partida->players[a].posY,'0'+a+1,&partida->campo);	
	}
	

	
	return aux;
}

void playGame(PARTIDA *partida){
	int i,j,k;
	int aux;
	for(i=0; i<partida->nRondas ; i++){
		for(j=0; j<partida->njogadores;j++){
			aux = 1;
			for(k=0; k<partida->tentativas  && aux; k++){
				runRonda(partida,j,i,k);
				aux = confirmRonda(partida,j,i);
				system("del obstaculo");
				system("del parabola");
				system("del cesto");
			}
		}
	}
	int last;
	if(VeRondas(partida,&last)){
		printf("TIE\n");
		printf("%d\n",partida->nRondas );
		for(i=last; i<partida->nRondas; i++){
			for(j=0; j<partida->njogadores;j++){
				for(k=0; k<partida->tentativas  && aux; k++){
					runRonda(partida,j,i,k);
					aux = confirmRonda(partida,j,i);
					system("del obstaculo");
					system("del parabola");
					system("del cesto");
				}	
			}
		}
	}
	ordenar(partida);
	system("pause");
	informacao(partida);
}
