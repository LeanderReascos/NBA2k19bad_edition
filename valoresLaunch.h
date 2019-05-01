#include <conio.h>
#include <math.h>
#include <string.h>
#define gBase  9.81
#define porcentajeY 0.08571
#define porcentajeX 0.5


int readTecla(){
	char cTecla;
	int var = -1;
	do{
		cTecla = getch();
	    if(cTecla == 0)
	      cTecla = getch();
	    else
	    switch(cTecla)
	    {
	      case 13://ENTER
	        var = 0;
	        break;
	      
	      case 9://TAB
	      	var = 9;
	        break;
	                    
	      case 72://ARRIBA
	        var = 72;
	        break;
	                     
	      case 80://ABAJO
	     	var = 80;
	        break;
	                     
	      case 75://IZQUIERDA
	      	var = 75;
	        break;
	                     
	      case 27://ESC
	        var = 27;
	        break;
	      case 77://DERECHA
	      	var = 77;
	        break;
	      case 'p'://Pause music
	        Musica('p');
	        break; 
	      case 'n':
	        Musica('n');
	        break;
	      case 'b':
	        Musica('b');
	        break;
	      case 's':
	        Musica('s');
	          break;
	      default:
	        break;
	    }
	}
	while(var == -1);
    return var;
}

void barraCarga(float valMax,float val,char text[100],char unidades[20]){
	int i;
	int n = (int)(val/valMax*10);
	printf("\r                                                                                  ");
	printf("\r\t%s %.2f %s   ",text,val,unidades);
	for(i=0;i<n;i++){
		printf("%c", 219);
	}
	printf(" %.2f %%",val/valMax*100);
}

float velocidadeSalto(float alturaJogador, float g1){
	int aux = alturaJogador >= 1.90;

	float vMax;
	float velocidadeSalto = 0;

	switch(aux){
		case 1:	vMax = 6*g1/gBase;	
				break;
		case 0:	vMax = 4*g1/gBase;	
				break;
	}

	int a;
	do{
		a = readTecla();
		if(a == 27)
			return -10;
		if((a == 72) && velocidadeSalto <= vMax){
			velocidadeSalto+=0.1;
			aux = 1;
		}

		else if((a == 80)  && velocidadeSalto >= 0){
			velocidadeSalto-=0.1;
			aux = 0;
		}
		else if(a == 75) velocidadeSalto = 0;
		else if(a == 77) velocidadeSalto = vMax;	
		else if(a == 9){
			switch(aux){
				case 1:	velocidadeSalto+=g1/gBase;	
						break;
				case 0:	velocidadeSalto-=g1/gBase;
						break;
			}
		}
		if(velocidadeSalto > vMax)		velocidadeSalto = vMax;
		if(velocidadeSalto < 0) velocidadeSalto = 0;
		//printf("\r\tJump Velocity: %.2f",velocidadeSalto);
		barraCarga(vMax,velocidadeSalto,"Jump Velocity:","m/s");
				
	}while(a != 0);

	

	return velocidadeSalto;
}


float velocidadeLanzamento( float g1){
	int a;
	float vMax = 20*g1/gBase;
	int aux;	
	float velocidadeLanzamento;
	do{
		a = readTecla();
		if(a == 27)
			return -10;
		if((a == 72) && velocidadeLanzamento <= vMax){
			velocidadeLanzamento+=0.1;
			aux = 1;
		}

		else if((a == 80)  && velocidadeLanzamento >= 1){
			velocidadeLanzamento-=0.1;
			aux = 0;
		}
		else if(a == 75) velocidadeLanzamento = 1;
		else if(a == 77) velocidadeLanzamento = vMax;	
		else if(a == 9){
			switch(aux){
				case 1:	velocidadeLanzamento+=g1/gBase;	
						break;
				case 0:	velocidadeLanzamento-=g1/gBase;
						break;
			}
		}
		if(velocidadeLanzamento > vMax)		velocidadeLanzamento = vMax;
		if(velocidadeLanzamento < 1) velocidadeLanzamento = 1;
		//printf("\r\tLaunch Velocity: %.2f",velocidadeLanzamento);
		barraCarga(vMax,velocidadeLanzamento,"Launch Velocity:","m/s");
				
	}while(a != 0);

	

	return velocidadeLanzamento;
}

float anguloLanzamento(){
	int a;
	float angMax = 85;
	float angMin = 1;
	int aux;	
	float anguloLanzamento;
	do{
		a = readTecla();
		if(a == 27)
			return -10;
		if((a == 72) && anguloLanzamento <= angMax){
			anguloLanzamento+=0.1;
			aux = 1;
		}

		else if((a == 80)  && anguloLanzamento >= 0){
			anguloLanzamento-=0.1;
			aux = 0;
		}
		else if(a == 75) anguloLanzamento = 1;
		else if(a == 77) anguloLanzamento = angMax;	
		else if(a == 9){
			switch(aux){
				case 1:	anguloLanzamento+=5;	
						break;
				case 0:	anguloLanzamento-=5;
						break;
			}
		}
		if(anguloLanzamento > angMax)		anguloLanzamento = angMax;
		if(anguloLanzamento < angMin) anguloLanzamento = angMin;
		//printf("\r\tLaunch Angle: %.2f",anguloLanzamento);
		barraCarga(angMax,anguloLanzamento,"Launch Angle:","degrees");
				
	}while(a != 0);

	

	return anguloLanzamento;
}

float distCesto(float Jx,float Jy,float dX, float dY){
	float posCestoX = dX*porcentajeX;
	float posCestoY = dY*porcentajeY;
	float x = pow((posCestoX-Jx),2);
	float y = pow((posCestoY-Jy),2);
	return sqrt(x+y);
}