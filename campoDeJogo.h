#include <string.h>


typedef struct campoDeJuego
{
	char file[5]; //nome do ficheiro
	//Matriz de carateres do campo de jogo
	char **campoDeJuego;
	int lin;
	//dimensiones em metros do campo
	float ancho; 
	float largo;
	//dimenções em carateres do campo (vem do ficheiro)
	int aChar;
	int lChar;
}CAMPO;

void addJugador(float x, float y, char n, CAMPO *campo){
	int posX,posY;
	posX = (int) (x*campo->lChar/campo->largo);
	posY = (int) (y*campo->aChar/campo->ancho);
	campo->campoDeJuego[posY][posX]=n;
}

void freeCampo(CAMPO *campo){
	free(campo->campoDeJuego);
}

void printCampo(CAMPO *campo){
	system("cls");
	int i;
	printf("%d\n", campo->lin);
	for(i=0;i<campo->lin;i++){
		printf("%s",campo->campoDeJuego[i]);
	}
}

void readCampo(CAMPO *campo){
	FILE *fp;
	fp = fopen(campo->file,"r");
	if(fp==NULL) exit(-1);
	int i=0;
	char buffer[219];
	campo->campoDeJuego = (char **) malloc(sizeof(char *));
	if(campo->campoDeJuego == NULL)
		exit(-1);
	while(fgets(buffer,sizeof(buffer),fp)){
		if(i >  0){
			campo->campoDeJuego = (char **) realloc(campo->campoDeJuego,(i+1)*sizeof(char *));
			if(campo->campoDeJuego == NULL) 
				exit(-1);
		}
		campo->campoDeJuego[i] = (char *) malloc(strlen(buffer)*sizeof(char));
		if(campo->campoDeJuego == NULL)
			exit(-1);
		strcpy(campo->campoDeJuego[i],buffer);
		i++;
	}
	campo->lin=i;
	fclose(fp);
}
