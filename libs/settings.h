#include <string.h>
#include <stdlib.h>

#define CASUAL 1
#define COMPETITIVE 2
#define SUDDEN_DEATH 3

#define MUSIC 1
#define VIDEO 2
#define ANIMATION 3
#define GNU 4
#define ROUND 5
#define TRY 6
#define INSTALL 7

typedef int BOOL;
#define true 1
#define false 0

typedef struct opciones{
	BOOL musica;
	BOOL videos;
	BOOL animacion;
	BOOL gnuplot;
	float velocidadeAnimacion;
	int nR[3];
	int nT[3];
}SETTINGS;

int select(){
	int op = -1;
    char cTecla;
    do{

	    cTecla = getch();
	    if(cTecla == 0)
	      cTecla = getch();
	    else
    	switch(cTecla)
	    {
	      case 9://TAB
	        break;
	                     
	      case 72://ARRIBA
	      	op =  72;
	      	break;
	      case 80://ABAJO
	      	op = 80;
	        break;
	                     
	      case 75://IZQUIERDA
	        break;
		  case 13://ENTER
	      case 27://ESC
	        op = 0;
	        break;
	      case 77://DERECHA
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
    while(op == -1); 
    return op;         
}

void boleanMenu(int n,BOOL *set){
	int ans;
	do{
		ans = -1;
		system("cls");
		printHeader();
		printTextTo(n);
		if((*set)){
			printTextTo(12);
			printTextTo(13);
		}
		else{
			printTextTo(14);
			printTextTo(15);
		}
		ans = select();
		if(ans == 72 || ans == 80){
			(*set) = !(*set);
		}
	}
	while(ans != 0);

	if(n == 6)
		Musica('s');
}

int selectNumber(int *n){
	int ans = select();
	if(ans == 72)
		if((*n)<9)
			(*n)++;
		else
			(*n) = 1;
	else if(ans == 80)
		if((*n)>1)
			(*n)--;
		else
			(*n)=9;
	return ans;
}
void selectMenu(int n,int v[]){
	int ans;
	system("cls");
	printHeader();
	printTextTo(n);
	int op = mainSelect("mode");
	do{
		int a;
		if(n == 10)
			a = 2;
		else
			a = 1;
		switch(op){
			case CASUAL:
				system("cls");
				printHeader();
				printtext(CASUAL,"Ficheiros_de_texto/modesVisual",7);
				printtext(a,"Ficheiros_de_texto/numberSelect",8);
				printtext(v[CASUAL-1]+2,"Ficheiros_de_texto/numberSelect",8);
				ans = selectNumber(&v[CASUAL-1]);
				break;
			case COMPETITIVE:
				system("cls");
				printHeader();
				printtext(COMPETITIVE,"Ficheiros_de_texto/modesVisual",7);
				printtext(a,"Ficheiros_de_texto/numberSelect",8);
				printtext(v[COMPETITIVE-1]+2,"Ficheiros_de_texto/numberSelect",8);
				ans = selectNumber(&v[COMPETITIVE-1]);
				break;
			default:
				system("cls");
				printHeader();
				printtext(SUDDEN_DEATH,"Ficheiros_de_texto/modesVisual",7);
				printtext(a,"Ficheiros_de_texto/numberSelect",8);
				printf("\n\tno can't be changed'\n");
				system("pause");
				break;
		}
	}
	while(ans != 0);
}

void segundoMenu(int op,SETTINGS *sets){
	FILE *cmd = NULL;
	switch(op){
		case INSTALL:
		    cmd = popen("cmd", "w");
		    if (cmd == NULL) 
		        exit(0);
		    fprintf(cmd, "cls\n");
		    fprintf(cmd, "cd dependencies\n");
		    fprintf(cmd, "dependencies.bat\n");
		    fclose(cmd);
			break;
		case MUSIC:
			boleanMenu(6,&sets->musica);
			break;
		case VIDEO:
			boleanMenu(7,&sets->videos);
			break;
		case ANIMATION:
			boleanMenu(8,&sets->animacion);
			break;
		case GNU:
			boleanMenu(9,&sets->gnuplot);
			break;
		case ROUND:
			selectMenu(10,sets->nR);
			break;
		case TRY:
			selectMenu(11,sets->nT);
			break;
	}
}
