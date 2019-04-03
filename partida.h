#include "campoDeJogo.h"

typedef struct partida{
	int njogadores;
	CAMPO  campo;
	
}PARTIDA;


typedef struct planeta{
	char nome[8];
	float lcampo;
	float acampo;
	float g;
	
}PLANETA;

void NEWGAME(PARTIDA* partidanova ,int opcao){


PLANETA* planeta;
planeta=(PLANETA*) malloc(sizeof(PLANETA));


partidanova->campo.lChar=128;
partidanova->campo.aChar=50;
strcpy(partidanova->campo.file,"campo");

	
printf ("How many players will play this round? ");
scanf("%d",&(partidanova->njogadores));

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


partidanova->campo.g=planeta->g;
partidanova->campo.ancho=planeta->acampo;
partidanova->campo.largo=planeta->lcampo;
strcpy(partidanova->campo.nome,planeta->nome);
strcpy(partidanova->campo.file,"campo");


//AQUI NAO ACABOU DE CORRER
readCampo( &(partidanova->campo));

}