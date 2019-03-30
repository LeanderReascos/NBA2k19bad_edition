#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "campoDeJogo.h"

int main(int argc, char const *argv[])
{
	int op;
	op = mainSelect();
	switch(op){
		case 1:
			readCampo();
			addJugador(1,3,'1');
			printCampo();
			break;
		case 2:
			break;
		case 3:
			break;
		case 0:
			break;
	}
	freeCampo();
	return 0;
}
