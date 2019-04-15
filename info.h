#include <stdlib.h>
#include <stdio.h>
#include "partida.h"


void informacao(PARTIDA *partida){
	char name[100];
	FILE *header;
	header= fopen ("Ficheiros_de_texto/header","r");
	if (header==NULL)
		exit(-1);
	printf("What do you want to name the file containing game information? \n");
	gets(name);
	char *ptrname;
	ptrname=name;
	char *ptrtxt;
	ptrtxt=".txt";
	ptrname=strcat(ptrname,ptrtxt);
	FILE *info;
	info=fopen(name,"w");
	if (info==NULL)
		exit(-1);
	char buffer[200];
	while (fgets(buffer,sizeof(buffer),header)){
		fprintf(info,buffer);
	}
	
	//Print CABECALHO
	int i;
	int n=partida->nRondas;
	fprintf(info,"| No |          NAME          |  HEIGHT  |");
	for(i=0; i<n;i++){
		fprintf(info,"  RONDA %d  |",i+1);
	}
	
	
	fprintf(info,"\n");
	for(i=0; i<42+12*n; i++){
		fprintf(info,"-");
	}
	fprintf(info,"\n");
	
	
	for(i=0; i<partida->njogadores;i++){
		if(i<9)
			fprintf(info,"| %d  ",i+1);
		else 
			fprintf(info,"| %d ",i+1);
		infoprintPlayer(&partida->players[i],info);
	}

	fprintf(info,"\n");
	
}


void infoprintPlayer(PLAYER *player,FILE *info){
	int i;
	int n = strlen(player->name);
	fprintf(info,"|%s",player->name);
	for (i=n; i<24; i++){
		fprintf(info," ");
	}
	fprintf(info,"|   %.2f   ",player->altura);

	for(i=0; i<player->numeroRondas;i++){
		fprintf(info,"|     %d     ",player->pontosRondas[i]);
	}
	fprintf(info,"|\n");
}



