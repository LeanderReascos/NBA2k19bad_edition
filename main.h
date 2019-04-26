#include <string.h>
#include <conio.h>
#include "menuSongs.h"
void freeMemoryMain(char **main, int n){
  int i;
  for(i=0; i<n;i++){
    free(main[i]);
  }
  free(main);
}

void printHeader(){
  FILE *fp;
  fp = fopen("Ficheiros_de_texto/header","r");

  char buffer[200];
  while(fgets(buffer,sizeof(buffer),fp)){
    printf("%s",buffer);  
  }
  fclose(fp);
}

void printMenu(char **m, int n, int pos){
  int i;
  system("cls");
  printHeader();
  printf("\n\n");
  m[pos][0] = '*';
  for(i=0; i<n; i++){
    if(i!=pos){
      m[i][0] = ' ';
    }
    printf("\t\t\t\t\t%s\n",m[i]);
  }

}

int mainSelect(char fileMenu[]){
  
  FILE *fp;
  fp = fopen(fileMenu,"r");

  if(fp==NULL) exit(-1);

  char **menu;
  menu = (char **) malloc(sizeof(char *));

  if(menu == NULL)  exit(-1);

  int i=0;
  char buffer[200];
  while(fgets(buffer,sizeof(buffer),fp)){
    if(i > 0) {
      menu = (char **) realloc(menu, (i+1)*sizeof(char *));
      if(menu == NULL) exit(-1);
    }
    menu[i] = (char *)malloc((2+strlen(buffer))*sizeof(char));
    menu[i][0] = ' ';
    menu[i][1] = ' ';
    strcpy((menu[i]+2),buffer);
    i++;
  }

  fclose(fp);
  int opcion = 0;

  while(1){
    
    printMenu(menu,i,opcion);
    char cTecla;

    cTecla = getch();
    if(cTecla == 0)
      cTecla = getch();
    else
    switch(cTecla)
    {
      case 13://ENTER
        freeMemoryMain(menu,i);
        return opcion+1;
        break;
      
      case 9://TAB
        break;
                     
      case 72://ARRIBA
        if(opcion != 0)
          opcion--;
        
        break;
                     
      case 80://ABAJO
        if(opcion != i-1)
          opcion++;
        break;
                     
      case 75://IZQUIERDA
        break;
                     
      case 27://ESC
        return 0;
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
             
}

