#include <stdio.h>
#include <stdlib.h>
#include "partida.h"
#include <math.h>
#include <time.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

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


