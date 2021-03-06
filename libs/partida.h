#include <string.h>
#include "campoDeJogo.h"
#include "launch.h"
#include "valoresLaunch.h"
#include <math.h>
#include <time.h>
#include "settings.h"

#define PI 3.14
#define POSINICIO 1

#define CASUAL 1
#define COMPETITIVE 2
#define SUDDEN_DEATH 3
#define MINIMO 1

/*Estruturas nescesarias*/

typedef struct jogador{
	//Base de datos
	char *name;
	float altura;
	//posi��o
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
	int *tentativas;
	int *cestos;
	int f;
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

/*Valores por default para o decorrer do jogo*/
void setsDefault(PARTIDA *partida){
	partida->settings.musica = true;
	partida->settings.videos  = true;
	partida->settings.animacion  = true;
	partida->settings.gnuplot  = true;
	partida->settings.velocidadeAnimacion = 1;
	partida->settings.nR[0] = 3; //ronda casual
	partida->settings.nR[1] = 3; //competitive
	partida->settings.nR[2] = 1; //muerte subita
	partida->settings.nT[0] = 5; //tentaitvas casual
	partida->settings.nT[1] = 5; //tentativas competitive
	partida->settings.nT[2] = 1; //muerteSubita
}
/***********************************************************FUN�OES PARA A CRIA��O DA PARTIDA************************************************************/
/*Cria��o da partida*/

void NEWGAME(PARTIDA *partidanova,int opcao){
	srand((unsigned int)time(NULL));
	partidanova->nPlaneta = opcao;
	PLANETA* planeta;
	planeta=(PLANETA*) malloc(sizeof(PLANETA));

	if(planeta == NULL){
		printf("Error memoria planeta\n");
		exit(-1);
	}
	int nJugadores = 1;
	int aux;
	do{
		system("cls");
		printHeader();	
		printtext(17,"libs/Ficheiros_de_texto/subHeaders",7);
		printtext(nJugadores+2,"libs/Ficheiros_de_texto/numberSelect",8);
		aux = selectNumber(&nJugadores);
	}
	while(aux != 0);
	
	partidanova->njogadores = nJugadores;

	partidanova->players = (PLAYER *) malloc(partidanova->njogadores*sizeof(PLAYER));

	FILE* fp;
	fp=fopen("libs/Base_de_datos/planets.data","r");
	if(fp==NULL){
		printf("ERROR\n");
		exit(-1);
	} 

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
	strcpy(partidanova->campo.file,"libs/Ficheiros_de_texto/campo");
}

/*Ler os jogadores da base de datos*/
void readPlayer(PLAYER *player,int n){
	int i = 0,j;
	FILE *fp;
	fp = fopen("libs/Base_de_datos/Jogadores.data","r");
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

/*Adicionar os jogadores a partida*/
void adicionarjugadores(PARTIDA *partida){
	int i,x;
	for(i=0; i<partida->njogadores; i++){
		x = valueSelect("Jogadores");
		if(x != 0){
			readPlayer(&partida->players[i],x);
		}
	}
}
/*Gera uma pisi��o aleartoria em fun�ao de um n[1,3] sendo as respetivas areas de jogo 
	n=1 Corresponde a area mais proxima do cesto (The Paint)
	n=2 A area que esta entre a area dos 3 pontos e a mais proxima
	n=3 A area dos 3 pontos*/
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
				if(((jogador->posX)>xmin2)&&((jogador->posX)<xmax2)){
					jogador->posY=random(ymin,campo->ancho);
				}

				else{
					jogador->posY=random((8.57/100)*(campo->ancho),campo->ancho);
				}
			}while((jogador->posY)<(8.57/100)*(campo->ancho));
			break;	
	}	
}


/*Gera a posi��o aleartoria inicial para todos os jogadores dependendo de um n[1,3]*/
void posRandomRonda(PARTIDA *partida, int n){
	int i;
	readCampo(&partida->campo);
	gerarPosicoes(&partida->players[0],&partida->campo,n);
	for(i=0; i<partida->njogadores; i++){
		partida->players[i].bola.bonus = 0;
		partida->players[i].zona = n;
		partida->players[i].posX = partida->players[0].posX;
		partida->players[i].posY = partida->players[0].posY;
		addJugador(partida->players[i].posX,partida->players[i].posY,'I',&partida->campo);
	}
}
/*Permite selecionar o modo de jogo entre Casual Competitive ou Sudden Death*/
void seleccionarModoDeJogo(PARTIDA *partida, int modoDeJogo){
	int i,j;
	partida->modoDeJogo=modoDeJogo;
	
	int n;
	switch(modoDeJogo){
		case (CASUAL):
			n = CASUAL-1;
			break;
		case(COMPETITIVE):
			n = COMPETITIVE -1;
			break;
		case(SUDDEN_DEATH):
			system("color 4f");
			n = SUDDEN_DEATH-1;
			break;
	}

	partida->tentativas = partida->settings.nT[n];
	for(i=0;i<partida->njogadores;i++){
		partida->players[i].numeroRondas=	partida->settings.nR[n];
		partida->nRondas = 	partida->settings.nR[n];
		partida->players[i].pontosRondas=(int*) malloc(	partida->settings.nR[n]*sizeof(int));
		partida->players[i].fallos=(int*) malloc(	partida->settings.nR[n]*sizeof(int));
		partida->players[i].cestos=(int*) malloc(	partida->settings.nR[n]*sizeof(int));
		partida->players[i].tentativas=(int*) malloc(	partida->settings.nR[n]*sizeof(int));
		for(j=0; j<partida->players[i].numeroRondas;j++){
			partida->players[i].pontosRondas[j] = 0;
			partida->players[i].fallos[j]= 0;
			partida->players[i].cestos[j]= 0;
			partida->players[i].tentativas[j]= 0;
		}
	}

	posRandomRonda(partida,POSINICIO);

}

/***********************************************************FUN�OES PARA A MOSTRAR OS VALORES DO JOGO************************************************************/

/*Fun��o que serve para imprimir os valores formatados do PLAYER */
void printPlayer(PLAYER *player){
	int i;
	int n = strlen(player->name);
	printf("|%s",player->name);
	for (i=n; i<24; i++){
		printf(" ");
	}
	printf("|   %.2f   ",player->altura);

	for(i=0; i<player->numeroRondas;i++){
		printf("|     %d     |    %d    ",player->pontosRondas[i],player->tentativas[i]);		
	}
	printf("|\n");
}

/*Mostra o cabe�alho dos valores de cada ronda desta maneira com n o numero de ronda:
| No |          NAME          |  HEIGHT  |  ROUND n  |  TRIES  |*/
void printEncabezado(int n){
	int i;
	printf("| No |          NAME          |  HEIGHT  |");
	for(i=0; i<n;i++){
		printf("  ROUND %d  |  TRIES  |",i+1);
	}
	printf("\n");
	for(i=0; i<42+21*n; i++){
		printf("-");
	}
	printf("\n");
}

/*Mostra na ecra os valores de toda a partida, Campo de jogo com as posi��es dos jogadores e os valores de cada jogador
Utilizando as fun��es anteriores para isso*/
void printPartida(PARTIDA *partida){
	system("cls");
	printtext(partida->nPlaneta,"libs/Ficheiros_de_texto/planetsVisual",16);
	printf("\n");
	printtext(partida->modoDeJogo,"libs/Ficheiros_de_texto/modesVisual",7);
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

/***********************************************************FUN�OES PARA EXPORTAR OS RESULTADOS DO JOGO************************************************************/

/*Exporta a informa��o de cada jogador aos dos ficheiros correspondentes*/
void infoprintPlayer(PLAYER *player,FILE *info,int nT,FILE *json){
	int i;
	int n = strlen(player->name);
	fprintf(info,"|%s",player->name);
	for (i=n; i<24; i++){
		fprintf(info," ");
	}
	fprintf(info,"|   %.2f   ",player->altura);

	int intentos=0;
	int cestos=0;
	fprintf(json, "{\"name\":\"%s\", \"height\": %.2f,\"NumeroRondas\": %d,\"rondas\":[", player->name,player->altura,player->numeroRondas);
	for(i=0; i<player->numeroRondas;i++){
		fprintf(info,"|     %d     |    %d    ",player->pontosRondas[i],player->tentativas[i]);
		fprintf(json, "{\"pontos\":%d,\"tentativas\":%d,\"cestos\":%d}",player->pontosRondas[i],player->tentativas[i],player->cestos[i]);
		
		if(i<player->numeroRondas-1)
			fprintf(json, "," );
		intentos+=player->tentativas[i];
		cestos+=player->cestos[i];
	}
	float per = (float)cestos/(float)intentos;
	fprintf(json, "]}");
	fprintf(info,"|   %.1f   |\n",per*100);
}

/*Mostrar ficheiros de texto no programa para ter uma melhor apresenta��o*/
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

/*Exporta a informa��o da partida para dois ficheiros um .txt(mostrar em texto plano os resultados) 
e um .json(cria uma base de datos para ser usada na pagina web)*/
void informacao(PARTIDA *partida){
	char name[100];
	printf("What do you want to name the file containing game information? \n");
	scanf (" %[^\n]%*c", name);
	strcat(name,".txt");

	FILE *json;
	json = fopen("libs/Web/database.json","w");

	FILE *information;
	information = fopen(name,"w");

	if(json == NULL || information == NULL)
		exit(-1);

	fprintText(1,"libs/Ficheiros_de_texto/header",16,information);
	fprintf(information,"\n\n\n");

	int i;
	int n=partida->nRondas;
	fprintf(information,"| No |          NAME          |  HEIGHT  |");
	for(i=0; i<n;i++){
		fprintf(information,"  ROUND %d  |  TRIES  |",i+1);
	}
	fprintf(information,"  PTS%%  |");
	fprintf(information,"\n");
	for(i=0; i<42+21*n; i++){
		fprintf(information,"-");
	}
	fprintf(information,"---------\n");
	fprintf(json, "partidaValues = '{\"nr\":%d,\"nj\":%d,\"t\":%d}'\n",partida->nRondas,partida->njogadores,partida->tentativas);
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


/*Permite abandonar o jogo no meio da partida*/
void exitGame(int v,PARTIDA *partida){
	if(v == -10){
		int x = mainSelect("leave");
		if(x == 1){
			informacao(partida);
			printf("\n\tTanks for play.\n");
			exit(0);
		}
		else
			system("cls");
	}	
}


/***********************************************************FUN�OES QUE DECORREM O JOGO DA PARTIDA************************************************************/

/*Nesta fun��o sao utilizadas fun��es do ficheiro valoreslaunch.h (para inserir os valores respetivos a cada lan�amento)
e a fun�ao launch.h (para fazer o lan�amento de cada bola)*/
void runRonda(PARTIDA *partida, int j,int i, int k){
	system("cls");
	printtext(partida->nPlaneta,"libs/Ficheiros_de_texto/planetsVisual",16);
	printf("\n");
	printtext(partida->modoDeJogo,"libs/Ficheiros_de_texto/modesVisual",7);
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
	printf("\tROUND %d \\ Try number %d\\N Cestos: %d\\Bonus: %d\n",i+1,k+1,partida->players[j].cestos[i],partida->players[j].bola.bonus);
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

/***********************************************************FUN�OES PYTHON************************************************************/

/*Variavel auxiliar para controlo dos ficheiros de video de acordo a validade do cesto*/
void cestoAux(PLAYER *player, int n){
	FILE * file2;
	file2=fopen("libs/VIDEOS/.videos","w");
	if(file2==NULL){
		printf("nao abriu commands\n");
		exit(-1);
	}
	if(n == 1)
		fprintf(file2, "%s", player->name);
	else
		fprintf(file2, "haha");
	fclose(file2);
}
/*Abre e reproduz em segundo plano as fun��es de python que mostram os videos*/
void cesto(){
	FILE *py;
    py = popen("py", "w");
    if (py == NULL) {
        printf("Erro ao abrir pipe para o python.\n"
            "Instale python, dependencia necesaria para o funcionamento completo do programa\n");
        exit(0);
    }
    fprintf(py, "exec(open('libs/video.py').read())");

    fclose(py);
}

/***********************************************************FUN�OES QUE VERIFICAM O ESTADO DA PARTIDA************************************************************/

/*Soma os ontos ao jogador de acordo a ronda e se apresenta o bonus, tudo isto em fun��o da zona*/
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

/* Muda de posi��o do jogador em fun��o ao modo de jogo, posi��o atual e se foi ou nao cesto o lan�amento 
SE DISTORIGINAL PARA O CASE 3 JA FOR MAXIMO(DIAGONAL DO CAMPO) DEVE MANTER ESSA POSICAO      MAXIMO=SQRT(L/2^2+C^2)
SE DISTORIGINAL PARA O CASE 4 JA FOR MINIMO(A 1 METRO DO CESTO) DEVE MANTER ESSA POSICAO      MINIMO=1*/
void adaptaZona(PLAYER* player,CAMPO* campo, int n,int modo){                                                           ///////////////////////////////////////////////DIFERENCA
	float distatual2=campo->ancho;
	float distatual1=0.0;
	float distoriginal=distCesto(player->posX,player->posY,campo->largo,campo->ancho);
	float MAXIMO =sqrt(pow(campo->ancho,2)+pow(campo->largo/2,2));
	
	if(modo != SUDDEN_DEATH){
		switch(n){

			case 1:                                                        ///////////////////////ZONA MAIS LONGE- USADA PARA A QUANDO MARCA PONTO
				gerarPosicoes(player,campo,player->zona+1);
				player->zona++;
			break;

			case 2:                                            ///////////////////////ZONA MAIS PERTO- USADA PARA A QUANDO PERDE DUAS VEZES SEGUIDAS
				gerarPosicoes(player,campo,player->zona-1);
				player->zona--;
			break;	

			case 3: 
			    gerarPosicoes(player,campo,player->zona);
			    distatual1=distCesto(player->posX,player->posY,campo->largo,campo->ancho);                                  ///////////////////////MESMA ZONA MAS MAIS LONGE- USADA PARA QUANDO ESTA  NA ZONA 3 E ACERTA
				if(!(distoriginal>=MAXIMO-MAXIMO*0.002)){
					while (distatual1<=distoriginal ){           
					gerarPosicoes(player,campo,player->zona); 
					distatual1=distCesto(player->posX,player->posY,campo->largo,campo->ancho);
					}
				}   
				break;	
			
			case 4:  
				gerarPosicoes(player,campo,player->zona);  
				distatual2=distCesto(player->posX,player->posY,campo->largo,campo->ancho);                                    ///////////////////////MESMA ZONA MAS MAIS PERTO- USADA PARA A ZONA 1
				if(!(distoriginal<=MINIMO+0.1)){
					while (distatual2>=distoriginal  && distatual2!=MINIMO){
						gerarPosicoes(player,campo,player->zona);      
						distatual2=distCesto(player->posX,player->posY,campo->largo,campo->ancho);
					}
				}
				break;
		}
	}
}

/*Depois de ser executado o lan�amento verifica se este foi cesto ou nao, para isto utiliza os valores antes ja calculados
no lan�amento (fun�oes de launch.h)*/
int confirmRonda(PARTIDA *partida, int j,int i){
	int aux = 1;

	if(partida->players[j].bola.cesto){
		partida->players[j].cestos[i]++;
		cestoAux(&partida->players[j], 1);
		somaPontos(&partida->players[j],i,partida->players[j].bola.bonus);
		partida->players[j].bola.bonus = 1;
		if(partida->players[j].zona < 3)
			adaptaZona(&partida->players[j],&partida->campo,1,partida->modoDeJogo);
		else
			adaptaZona(&partida->players[j],&partida->campo,3,partida->modoDeJogo);
		if(partida->modoDeJogo == SUDDEN_DEATH)
			aux = 0;
		partida->players[j].f = 0;
	}
	else{
		cestoAux(&partida->players[j], 2);
		partida->players[j].fallos[i]++;

		if(partida->players[j].f/*partida->players[j].fallos[i] == partida->tentativas || partida->players[j].fallos[i]%2 == 0*/){
			partida->players[j].bola.bonus = 0;
			if(partida->players[j].zona > 1)
				adaptaZona(&partida->players[j],&partida->campo,2,partida->modoDeJogo);
			else
				adaptaZona(&partida->players[j],&partida->campo,4,partida->modoDeJogo);
			partida->players[j].f = 0;
		}
		else {
			partida->players[j].bola.bonus = 0;
			partida->players[j].f++;
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

/***********************************************************FUN�OES AUXILIARES************************************************************/
/*Conta os pontos totais de um PLAYER*/
void resultado(PLAYER *player){
	int i;
	int soma = 0;
	for(i=0; i<player->numeroRondas; i++){
		soma += player->pontosRondas[i];
	}
	player->total = soma;
}

/*Ordena aos jogadores do melhor ao menor em fun��o dos seus pontos*/
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


/*Inicializar a 0 a variavel auxiliar para detetar o numero de falhas para cada jogador*/
void poeZeros(PARTIDA* partida){                                         
	int i;
	for(i=0;i<partida->njogadores;i++){
		partida->players[i].f=0;
		
	}
}

/*Guarda os resultados de cada jogador num array dinamico para depois verificar se existe empate*/
void SomaRondas (PARTIDA* partida,int* n){
	int soma,i,j;
	for(i=0;i<partida->njogadores;i++){
		resultado(&partida->players[i]);
		n[i]=partida->players[i].total;
	}
}

/*Verifica se existem dois ou mais jogadores na primeira posi��o, sendo verdade realoca memoria para continuar o jogo
adicionando EXTREAS rondas e devolvendo um valor int[1,0]
	1 = EMPATE
	0 = NAO HA EMPATE
alem disso guarda em dois pointers int
	lastronda = o valor da ultima ronda para continuar apartir dai
	np = o numero de jogadores empatados*/
int VeRondas(PARTIDA* partida,int *lastronda, int *np,int extras)
{
	int res = 0;
	(*np) = 0;
	int i,j=1,m;
	int* n=(int*) malloc(sizeof(int)*(partida->njogadores));            				/////array das somas dos pontos dos jogadores por ordem de como os proprios estao organizados
	int* jogadoresprimeiro=(int*) malloc(sizeof(int));                 					 /////array que guarda os indices dos jogadores com maior pontuaçao
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
	if(partida->modoDeJogo==COMPETITIVE && j>1){                                        				/////caso seja modo 2-adicionar rondas e temos varios jogadores com a maior pontuaçao
	
		for(m=0;m<partida->njogadores;m++){
			int aux = partida->players[m].numeroRondas;
			(*lastronda) = aux;

			partida->players[m].numeroRondas+=extras;             			//////aumento do numero de rondas usando o vetor jogadoresprimeiro porque guarda os indices dos jogadores que estejam nesta situacao
			partida->players[m].pontosRondas=(int*) realloc(partida->players[m].pontosRondas,sizeof(int)*(partida->players[m].numeroRondas)); 
			partida->players[m].fallos=(int*) realloc(partida->players[m].fallos,sizeof(int)*(partida->players[m].numeroRondas)); 
			partida->players[m].cestos=(int*) realloc(partida->players[m].cestos,sizeof(int)*(partida->players[m].numeroRondas)); 
			partida->players[m].tentativas=(int*) realloc(partida->players[m].tentativas,sizeof(int)*(partida->players[m].numeroRondas)); 
			res = 1;
			if(partida->players[m].pontosRondas == NULL || partida->players[m].fallos == NULL)
					exit(-1);
			int k;
			for(k=0; k<extras; k++){
				partida->players[m].pontosRondas[aux+k] = 0;
				partida->players[m].fallos[aux+k] = 0;
				partida->players[m].cestos[aux+k] = 0;
				partida->players[m].tentativas[aux+k] = 0;
			}
		}
	}
	(*np) = j;
	free(n);
	free(jogadoresprimeiro);
	if(res)			partida->nRondas+=extras;  
	return res;
}


void freeMemoryPartida(PARTIDA *partida){
	int i;
	for(i=0; i < partida->njogadores; i++){
		free(partida->players[i].name);
		free(partida->players[i].pontosRondas);
		free(partida->players[i].fallos);
		free(partida->players[i].tentativas);
		free(partida->players[i].cestos);
	}

	free(partida->players);
	freeCampo(&partida->campo);
	free(partida);
}

/*ESTRUTURA para saber guardar a informa��o do vencedor*/
typedef struct VENCEDOR{
	char nome[30];
	int pontuacao;
}VENCEDOR;

/*Como extra se os jogadores envolvidos tiverem uma pontua��o > 0 verifica se bateu um recorde sendo assim guarda a informa��o
em dois ficheiros HIGHSCORES.data (base de datos) e higscores.json(para mostrar no site)*/
void listaMelhores(PARTIDA* partida){
	VENCEDOR * lista=NULL;
	int contador;
	int conseguiu=0,m,j,j2,i2;

	FILE * fp2=fopen("libs/Base_de_datos/HIGHSCORES.data","r");
	if (fp2==NULL) exit(-1);
		
	int i;
	contador=0;
	
	char buffer[40];
	char* partes;

	lista=(VENCEDOR*) malloc(sizeof(VENCEDOR));              
	while(fgets(buffer,sizeof(buffer),fp2)){
		(contador)++;
		lista=(VENCEDOR*) realloc(lista,(contador)*sizeof(VENCEDOR));
		partes=strtok(buffer,";");
		i=1;
		while (partes!=NULL){
			switch(i){
				case 1:
					strcpy(lista[(contador)-1].nome,partes);
					break;
				case 2:
					lista[(contador)-1].pontuacao=atoi(partes);
					break;
			}
			partes=strtok(NULL,";");
			i++;
		}
	}
	fclose(fp2);
		
	int* n=(int*) malloc(partida->njogadores*sizeof(int));    
	int tamanho=contador,conseguiu2;          
	SomaRondas(partida,n);

	for(i2=0;i2<partida->njogadores;i2++){
		conseguiu2=0;
		for(j=0;j<(contador) && conseguiu2==0;j++){
			if(n[i2]>=lista[j].pontuacao && n[i2]!=0 ){
				conseguiu2=1;
				conseguiu=1;
				for(j2=(contador)-1;j2>j;j2--){                              ////////////repreencher lista dos vencedores- eliminando o ultimo .E indo passando o "ultimo" atual para a posicao seguinte
					strcpy(lista[j2].nome,lista[j2-1].nome);
					lista[j2].pontuacao=lista[j2-1].pontuacao;	
				}
				strcpy(lista[j].nome,partida->players[i2].name);
				lista[j].pontuacao=n[i2];
				tamanho=5;
			}	
		}
	}
	free(n);	
	
	FILE * fp=fopen("libs/Base_de_datos/HIGHSCORES.data","r+");
	if (fp==NULL) {
		printf("ERROR\n");
		exit(-1);	
	}
	if (conseguiu==1){            ///////CASO HAJA ALTERACOES, D�-SE A NOTICIA MOSTRANDO A "TABELA"               
		system("cls");          
		printHeader();
		prints("libs/Ficheiros_de_texto/CONGRATULATIONS.txt");
		FILE *json = fopen("libs/Web/highscores.json","w");    
		fprintf(json, "highscores= '[" );
		for	(m=0;m<(tamanho);m++){
			fprintf(fp,"%s;%d;\n",lista[m].nome,lista[m].pontuacao);
			fprintf(json, "{\"name\":\"%s\", \"pontos\": %d}", lista[m].nome,lista[m].pontuacao);
			printf("\n\n\t\t\t\t\t\t\t\t%d. %s->%d\n",m+1,lista[m].nome,lista[m].pontuacao);
			if(m != tamanho-1)
				fprintf(json, ",");
		}
		fprintf(json, "]'");
		fclose(json);
	}
	
	
	free(lista);
	fclose(fp);
	system("pause");
}

/***********************************************************FUN�AO PRINCIPAL ONDE DECORRE TODAS AS RONDAS************************************************************/
void playGame(PARTIDA *partida){
	int i,j,k;
	int aux;
	int last = 0,nP,zona;
	if(partida->modoDeJogo != SUDDEN_DEATH){

		for(i=0; i<partida->nRondas ; i++){
			poeZeros(partida);
			if(i>2){
				zona=1+rand()%2; 
				posRandomRonda(partida,zona);
			}
			else if(i>0)
				posRandomRonda(partida,i+1);
			for(j=0; j<partida->njogadores;j++){
				aux = 1;
				for(k=0; k<partida->tentativas && aux; k++){
					runRonda(partida,j,i,k);
					aux = confirmRonda(partida,j,i);
					partida->players[j].tentativas[i]++;
					system("del obstaculo");
					system("del parabola");
					system("del cesto");
				}
			}
		}
		ordenar(partida);
		if(VeRondas(partida,&last,&nP,2)){
			printf("EMPATE\n");
			printf("%d\n",partida->nRondas );
			for(i=last; i<partida->nRondas; i++){
				if(i>2){
				zona=1+rand()%2; 
				posRandomRonda(partida,zona);
				}
				else if(i>0)
					posRandomRonda(partida,i+1);
				poeZeros(partida);
				for(j=0; j<nP;j++){
					for(k=0; k<partida->tentativas  && aux; k++){
						runRonda(partida,j,i,k);
						aux = confirmRonda(partida,j,i);
						partida->players[j].tentativas[i]++;
						system("del obstaculo");
						system("del parabola");
						system("del cesto");
					}	
				}
			}
		}
		ordenar(partida);
		if(VeRondas(partida,&last,&nP,1))
			partida->modoDeJogo = SUDDEN_DEATH;
	}
	if(partida->modoDeJogo == SUDDEN_DEATH){
		aux = 1;
		k = 0;
		poeZeros(partida);
		while(aux){
			i = last;
			if(k>0 && k%2 == 0){
				zona=1+rand()%2; 
				posRandomRonda(partida,zona);
			}
			for(j=0; j<partida->njogadores && aux;j++){
				runRonda(partida,j,i,k);
				aux = confirmRonda(partida,j,i);
				partida->players[j].tentativas[i]++;
				system("del obstaculo");
				system("del parabola");
				system("del cesto");
			}
			k++;
		}
	}
	
	ordenar(partida);
	system("pause");
	informacao(partida);
	listaMelhores(partida);
}
