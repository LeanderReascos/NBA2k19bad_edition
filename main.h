#include <string.h>
#include <conio.h>
#define nLines 26

void printMenu(char filename[], int n){
	system("cls");
	FILE *fp;
	fp = fopen(filename,"r");

	if(fp==NULL) exit(-1);

	int i=0;
	char buffer[200];
	while(fgets(buffer,sizeof(buffer),fp)&&i<n){
		if(i>=n-nLines)
			printf("%s",buffer);
		i++;
	}

	fclose(fp);
}

int mainSelect(){
	char cTecla;
	int ln = nLines;
	int aux = 1;
    while(1){
       	if(aux){
              	 aux = 0;
             	 printMenu("main.txt",ln);
              }
              	cTecla = getch();
       		if(cTecla == 0){
                  	cTecla = getch();
       		}
       
              else
                  switch(cTecla)
                  {
                   case 13://ENTER
                        return ln/nLines;
                   break;
                   
                   case 9://TAB
                        
                   break;
                   
                   case 72://ARRIBA
                        if(ln!=nLines){
                        	ln-=nLines;
                       	aux++;
                       }
                   break;
                   
                   case 80://ABAJO
                        if(ln!=nLines*4){
                        	ln+=nLines;
                       	aux++;
                       }
                   break;
                   
                   case 75://IZQUIERDA
                        
                   break;
                   
                   case 27://ESC
                       return 0;
                   break;
                   case 77://DERECHA
                        
                   break;
                   }
               }
}