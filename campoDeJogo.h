#include <string.h>
#define campo "campo"
#define ancho  11
#define largo 15
#define aChar 50
#define lChar 128


char **campoDeJuego = NULL;
int lin;

void addJugador(float x, float y, char n){
	int posX,posY;
	posX = (int) (x*lChar/largo);
	posY = (int) (y*aChar/ancho);
	campoDeJuego[posY][posX]=n;
}

void freeCampo(){
	free(campoDeJuego);
}

void printCampo(){
	int i;
	system("cls");
	for(i=0;i<lin;i++){
		printf("%s",campoDeJuego[i]);
	}
}

void readCampo(){
	FILE *fp;
	fp = fopen(campo,"r");

	if(fp==NULL) exit(-1);
	int i=0;
	char buffer[219];
	campoDeJuego = (char **) malloc(sizeof(char *));
	if(campoDeJuego == NULL)
		exit(-1);
	while(fgets(buffer,sizeof(buffer),fp)){
		if(i >  0){
			campoDeJuego = (char **) realloc(campoDeJuego,(i+1)*sizeof(char *));
			if(campoDeJuego == NULL) 
				exit(-1);
		}
		campoDeJuego[i] = (char *) malloc(strlen(buffer)*sizeof(char));
		if(campoDeJuego == NULL)
			exit(-1);
		strcpy(campoDeJuego[i],buffer);
		i++;
	}
	lin=i;
	fclose(fp);
}
