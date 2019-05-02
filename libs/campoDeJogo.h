#include <string.h>
#include <stdlib.h>

/*Estrutura do campo de jogo Tem os valores nescesarios para o calculo dos lançamentos na partida*/
typedef struct campoDeJuego
{
	char nome[8];
	char file[100]; //nome do ficheiro
	//Matriz de carateres do campo de jogo
	char **campoDeJuego;
	int lin;
	//dimensiones em metros do campo
	float ancho; 
	float largo;
	//dimenções em carateres do campo (vem do ficheiro)
	int aChar;
	int lChar;
	//gravidade
	float g;
}CAMPO;

/*Adiciona o jogador na posição x y do campo de jogo para mostrar na ecra ao utilizador*/
void addJugador(float x, float y, char n, CAMPO *campo){
	int posX,posY;
	posX = (int) (x*campo->lChar/campo->largo);
	posY = (int) (y*campo->aChar/campo->ancho);
	campo->campoDeJuego[posY][posX]=n;
}
/*Libera memoria*/
void freeCampo(CAMPO *campo){
	int i,j;
	for(i=0; i<campo->lin; i++){
		free(campo->campoDeJuego[i]);
	}
	free(campo->campoDeJuego);
}
/*mostra o campo*/
void printCampo(CAMPO *campo){
	int i;
	for(i=0;i<campo->lin;i++){
		printf("%s",campo->campoDeJuego[i]);
	}
}
/*le a matriz do campo que se encontra no ficheiro campo de jogo*/
void readCampo(CAMPO *campo){
	FILE *fp;
	fp = fopen(campo->file,"r");
	if(fp==NULL){
		printf("Memory error 0\n");
		exit(-1);
	}
	int i=0;
	char buffer[219];
	if(campo->campoDeJuego != NULL && campo->lin >0) {
		freeCampo(campo);
	}
	campo->campoDeJuego = (char **) malloc(sizeof(char *));
	if(campo->campoDeJuego == NULL){
		printf("Memory error 1\n");
		exit(-1);
	}
	while(fgets(buffer,sizeof(buffer),fp)){
		if(i >  0){
			campo->campoDeJuego = (char **) realloc(campo->campoDeJuego,(i+1)*sizeof(char *));
			if(campo->campoDeJuego == NULL) {
				printf("Memory error 2\n");
				exit(-1);
			}
		}
		campo->campoDeJuego[i] = (char *) malloc(strlen(buffer)*sizeof(char));
		if(campo->campoDeJuego == NULL){
			printf("Memory error 3\n");
			exit(-1);
		}
		strcpy(campo->campoDeJuego[i],buffer);
		i++;
	}
	campo->lin=i;
	fclose(fp);
}
