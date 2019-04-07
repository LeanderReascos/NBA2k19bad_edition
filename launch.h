#include <math.h>
#include <string.h>
#include <time.h>

//#define g 9.81
#define hCesto 3.05
#define carateresPorMetro 5
#define radioCesto 0.45

typedef struct bola{
	float h0;  // Pos em y inicinal
	float v; // Velocidade inicial
	float ang; //angulo de lanzamiento
	// Pos actual no tempo
	float x; 
	float y;
	//Matriz de la parabola
	char **parabola;
	//datosExtra
	float hMax;
	float distCesto;
	float g;
}BOLA;

void launch_time(BOLA *bola, float t){
	bola->x = bola->v*cos(bola->ang)*t;
	bola->y = bola->h0 + bola->v*sin(bola->ang)*t -(float)( 0.5*bola->g*pow(t,2));
	//printf("%f %f %f\n",bola->x,bola->y,t);
}

void printParabola(BOLA *bola,int sizeLinhas,int sizeColumnas){
	system("cls");
	int i,j;
	for(i=0; i<sizeLinhas;i++){
	 	for(j=0; j<sizeColumnas;j++){
	 		printf("%c",bola->parabola[i][j]);	
	 	}
	 	printf("\n");
	 	
	 }
}


void parabola(BOLA *bola){
	 bola->hMax = bola->h0+pow((bola->v*sin(bola->ang)),2)/(2*bola->g);
	 int sizeLinhas = 5+(int)bola->hMax*carateresPorMetro;
	 int sizeColumnas = 2+(int)bola->distCesto*carateresPorMetro;


	 bola->parabola = (char **)malloc(sizeLinhas*sizeof(char *));
	 if(bola->parabola == NULL) exit(-1);

	 int i,j;
	 for(i=0; i<sizeLinhas;i++){
	 	bola->parabola[i] = (char *)malloc(sizeColumnas*sizeof(char));
	 	if(bola->parabola[i] == NULL) exit(-1);
	 	for(j=0; j<sizeColumnas; j++){
	 		bola->parabola[i][j]=' ';
	 		if(i==sizeLinhas-1)	bola->parabola[i][j] ='_';
	 		if(j==0) bola->parabola[i][j] ='|';
	 	}
	 }

	 int posXCesto = (int) bola->distCesto*carateresPorMetro;
	 int posYCesto = sizeLinhas-(int) hCesto*carateresPorMetro;

	 for(i=0;i<(int)(radioCesto*carateresPorMetro);i++){
	 	if(posYCesto < 0) break;
	 	 bola->parabola[posYCesto][posXCesto-i]='~'; 
	 	 bola->parabola[posYCesto][posXCesto+i]='~'; 
	 }

	 clock_t timeInicial = clock();
	 do{
	 	clock_t time = clock();
	 	float t = (float)(time-timeInicial)/CLOCKS_PER_SEC;
	 	launch_time(bola,t);
	 	int x,y;
	 	y = (int)(sizeLinhas-bola->y*carateresPorMetro);
	 	x = (int)(bola->x*carateresPorMetro);
	 	//printf("%f        %d %d      %f  %f\n",t,x,y,bola->x, bola->y);
	 	if(!(bola->x>=0 &&bola->y>=0 && x<=sizeColumnas))	
	 		break;
	 	bola->parabola[y][x]='@'; 
	 	printParabola(bola,sizeLinhas,sizeColumnas);
	 }while(bola->y > 0);

	 free(bola->parabola);

}