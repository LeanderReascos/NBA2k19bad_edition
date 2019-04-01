	#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "campoDeJogo.h"
#include "launch.h"

int main(int argc, char const *argv[])
{
	int op;
	CAMPO campo;
	BOLA bola;
	bola.h0 = 1;  // Pos em y inicinal
	bola.v = 11.5; // Velocidade inicial
	bola.ang = 45*3.14/180; //angulo de lanzamiento
	bola.distCesto = 11;

	op = mainSelect();
	switch(op){
		case 1:
			/*strcpy(campo.file , "campo");
			campo.ancho = 11;
			campo.largo =15;
			campo.aChar =50;
			campo.lChar =128;
			readCampo(&campo);
			addJugador(7.5,6,'1',&campo);
			printCampo(&campo);*/
			parabola(&bola);
			break;
		case 2:
			break;
		case 3:
			break;
		case 0:
			break;
	}
	//freeCampo(&campo);
	return 0;
}
