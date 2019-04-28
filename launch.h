#include <math.h>
#include <string.h>
#include <time.h>
#define GNUPLOT "gnuplot -persist"

#define GRAPH "parabola"
#define hCesto 3.05
#define carateresPorMetro 10
#define diametroCesto 0.45
#define pi 3.14

typedef struct Obstaculo{
		float xdist;
		float ymax;///altura do muro(1); altura inicial(2); amplitude do moviemtno*2(3)
		float vd; //velocidade do drone
		float ax; //aceleracao segundo x do drone
		float ay;//aceleracao segundo y do drone
		float teta; ////angulo que a velocidade inicial faz com a horizontal ou frequencia angular no movimento harmonico
		//POSIÇOES
		float x;
		float y;
}OBSTACULO;

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
	int cesto;
	int bonus;
	int before;
	//Obstaculo
	int aux;
	OBSTACULO obstaculo;
	//settings
	int animacion;
	int gnu;
	float vAni;
}BOLA;

void freeMatriz(char **m,int lin){
	int i;
	for(i=0; i<lin; i++){
		free(m[i]);
	}
	free(m);
}

float random(float min, float max){
	
	float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min ); 
}

void geraObstaculo(BOLA* bola){
	switch (bola->aux){
			case 0:                 //    sem obstaculo
			break;

			case 1:					//obstaculo estatico
				bola->obstaculo.x=random(1,bola->distCesto-1);
				bola->obstaculo.y=random(0,2)+hCesto;
				break;

			case 2:					//drone com movimento "aleatorio"
				bola->obstaculo.xdist=random(1,bola->distCesto-1);
			
				if(bola->obstaculo.xdist<(bola->distCesto/2)){
						bola->obstaculo.ax=random(0,7);
					
				}
				else{
						bola->obstaculo.ax=random(-7,0);
				}
				
			
				
				
				bola->obstaculo.ymax=random(0,1);                        
				bola->obstaculo.vd=random(3,10);
				bola->obstaculo.teta=random(0,pi/2);
				bola->obstaculo.ay=random(2,7);


				break;

			case 3:				//drone com movimento harmonnico
				bola->obstaculo.xdist=random(1,bola->distCesto-1);
				bola->obstaculo.ymax=random(0,2)+hCesto;                         ///altura maxima do drone que se move na vertical-AMPLITUDE DO MOVIMENTO HARMONICO*2
				bola->obstaculo.teta=random(2*pi, 6*pi);                                 //usamos o teta neste caso para definir a frequancia angular do movimento
			break;


	}
}


void verificaCesto(BOLA *bola){
	int enX = bola->x <= bola->distCesto+(diametroCesto/2) && bola->x >= bola->distCesto-(diametroCesto/2);
	int enY = bola->y <= hCesto+(diametroCesto/2) && bola->y >= hCesto-(diametroCesto/2);

	int beY =  bola->y > hCesto;
	//printf("X> %f EnX> %d EnY> %d BeY> %d Y> %f BEFORE> %d CESTO> %d\n",bola->x, enX,enY,beY,bola->y,enX && beY,enX && enY && bola->before);
	if(enX && beY){
		//printf("Ant\n");
		bola->before = 1;
	}
	if(enX && enY && bola->before){
		//printf("cesto\n");
		bola->cesto = 1;
	}
}

void launch_time(BOLA *bola, float t){
	bola->x = bola->v*cos(bola->ang)*t;
	bola->y = bola->h0 + bola->v*sin(bola->ang)*t -(float)(0.5*bola->g*pow(t,2));

	if(bola->aux > 1){
		float vdx;
		float vdy;
		switch(bola->aux){
			case 2:	
					vdx =(bola->obstaculo.vd)*cos(bola->obstaculo.teta);
					vdy =(bola->obstaculo.vd)*cos(bola->obstaculo.teta);
					bola->obstaculo.x= (bola->obstaculo.xdist)+vdx*t+0.5*(bola->obstaculo.ax)*pow(t,2);
					bola->obstaculo.y= (bola->obstaculo.ymax)+vdy*t+0.5*(bola->obstaculo.ay)*pow(t,2);
					break;
			case 3:
					bola->obstaculo.x= (bola->obstaculo.xdist);
					bola->obstaculo.y= (bola->obstaculo.ymax)/2*cos(bola->obstaculo.teta*t+pi/2)+(bola->obstaculo.ymax)/2;
					break;
		}
	}
	
	verificaCesto(bola);
}

void printMatriz(char **m,int sizeLinhas,int sizeColumna){
	int i,j;
	system("cls");
	for(i=0; i<sizeLinhas; i++){
	 	for(j=0; j<sizeColumna ;j++){
	 		printf("%c",m[i][j]);
	 	}
	 	printf("\n");
	 }
}

void printParabola(BOLA *bola){
	FILE *gp;
    gp = popen(GNUPLOT, "w");
    if (gp == NULL) {
        printf("Erro ao abrir pipe para o GNU plot.\n"
            "Instale gnuplot, dependencia necesaria para o funcionamento completo do programa\n");
        exit(0);
    }
    fprintf(gp, "set yrange[0:%f]\n", bola->hMax);
    fprintf(gp, "set xrange[0:%f]\n", bola->distCesto);
    if(bola->aux > 0)
    	fprintf(gp, "plot 'obstaculo','%s','cesto'\n",GRAPH);
    else
    	fprintf(gp, "plot '%s','cesto'\n",GRAPH);

    fclose(gp);

}

void newBola(BOLA *bola){
	bola->cesto = 0;
	bola->before = 0;
}

void cestoDesign(float distCesto){
	FILE *cesto;
		cesto = fopen("cesto", "w");
		if(cesto == NULL) {
			printf("ERROR\n");
			exit(-1);
		}
	float aux = 0;
	while (aux <= diametroCesto/2){
		fprintf(cesto, "%.3f \t %.3f \n",distCesto-aux,hCesto);
		fprintf(cesto, "%.3f \t %.3f \n",distCesto+aux,hCesto);
		aux += 0.1;
	}
	fclose(cesto);
}

void parabola(BOLA *bola){
	newBola(bola);
	 bola->hMax = 1+(bola->h0+pow((bola->v*sin(bola->ang)),2)/(2*bola->g));
	 if(bola->hMax < hCesto+2) bola->hMax = hCesto+3;
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

	 cestoDesign(bola->distCesto);
	 for(i=0;i<(int)(diametroCesto*carateresPorMetro);i++){
	 	if(posYCesto < 0) break;
	 	 bola->parabola[posYCesto][posXCesto-i]='~'; 
	 	 bola->parabola[posYCesto][posXCesto+i]='~'; 
	 }
	 FILE *obs;
		obs = fopen("obstaculo", "w");
			if(obs == NULL) {
				printf("ERROR\n");
				exit(-1);
			}
	 if(bola->aux == 1){

	 	 int posYobs = sizeLinhas-(int)( bola->obstaculo.y*carateresPorMetro);
		 int posXobs = (int) bola->obstaculo.x*carateresPorMetro;
		 float ay = 0;
		 while(ay <= bola->obstaculo.y){
		 	fprintf(obs, "%.3f \t %.3f \n", bola->obstaculo.x,ay);	
		 	ay+=0.03;
		 }
		 	
		 
		 for(i=sizeLinhas-1; i>posYobs; i--){
		 	bola->parabola[i][posXobs]='|'; 
		 fclose(obs);
		 }
	 }
	 
		
	 FILE *fp;
	 fp = fopen(GRAPH, "w");
		if(fp == NULL) {
			printf("ERROR\n");
			exit(-1);
		}
	 float t = 0;
	 float dt = 0;
	 int pasoObstaculo = 1;
	 do{
	 	launch_time(bola,t);
	 	fprintf(fp, "%.3f \t %.3f \n", bola->x,bola->y);	
	 	
	 	int x,y;
	 	if(bola->aux > 1){
	 		y = (int)(sizeLinhas-bola->obstaculo.y*carateresPorMetro);
	 		x = (int)(bola->obstaculo.x*carateresPorMetro);
			fprintf(obs, "%.3f \t %.3f \n", bola->obstaculo.x,bola->obstaculo.y);
	 		if(bola->obstaculo.x>=0 && bola->obstaculo.y>0 && x<=sizeColumnas && y>=0)
	 			bola->parabola[y][x]='#'; 
	 		
	 	}
		
	 	y = (int)(sizeLinhas-bola->y*carateresPorMetro);
	 	x = (int)(bola->x*carateresPorMetro);
	 	//printf("%f        %d %d      %f  %f\n",t,x,y,bola->x, bola->y);
	 	if(bola->x>=0 &&bola->y>0 && x<=sizeColumnas && y>=0){
	 		bola->parabola[y][x]='@'; 
	 	}

	 	if(t-dt >= 0.01*bola->vAni && bola->x<=bola->distCesto && bola->animacion){
	 		printMatriz(bola->parabola,sizeLinhas,sizeColumnas);
	 		dt = t;
	 	}

		if(bola->aux > 0 && bola->x >= bola->obstaculo.x-0.3 && bola->x <= bola->obstaculo.x+0.3) {
			pasoObstaculo = bola->y > bola->obstaculo.y;
		}
	

	 	t += 0.01;	
	 }while(bola->y > 0 && pasoObstaculo);

	 if(bola->aux > 1 || obs != NULL){
	 	fclose(obs);
	 }

	 fclose(fp);
	 if(bola->gnu)
	 	printParabola(bola);	
	
	freeMatriz(bola->parabola,sizeLinhas);

}



