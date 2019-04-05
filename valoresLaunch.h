#include <conio.h>

int readTecla(){
	 char cTecla;

    cTecla = getch();
    if(cTecla == 0)
      cTecla = getch();
    else
    switch(cTecla)
    {
      case 13://ENTER
        return 0;
        break;
      
      case 9://TAB
        break;
                    
      case 72://ARRIBA
        return 2;
        break;
                     
      case 80://ABAJO
     	return 1;
        break;
                     
      case 75://IZQUIERDA
        break;
                     
      case 27://ESC
        return 0;
        break;
      case 77://DERECHA
        break;
      default:
        break;
    }
}

float velocidadeSalto(float alturaJogador){
	int aux = alturaJogador >= 1.90;

	float vMax;
	float velocidadeSalto = 0;

	switch(aux){
		case 1:	vMax = 4;	
				break;
		case 0:	vMax = 6;	
				break;
	}

	int a;

	do{
		if((readTecla()-1) && velocidadeSalto != vMax){
			velocidadeSalto+=0.25;
		}

		else if((readTecla()-1) == 0 && velocidadeSalto >= 0){
			velocidadeSalto-=0.25;
		}
		printf("%f\n",velocidadeSalto );
		a = readTecla();
	}while(a != 0);

	
}