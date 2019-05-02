#include <string.h>
#include <conio.h>
#include "menuSongs.h"

#define PATH "libs/Ficheiros_de_texto/"

void prints(char nome[]){                       ///////////print da pergunta
  FILE *fp;
  fp = fopen(nome,"r");
  if(fp == NULL) exit(-1);
  char buffer[100];
  while(fgets(buffer,sizeof(buffer),fp)){
    printf("%s",buffer);
  }
  fclose(fp);
}

void freeMemoryMain(char **main, int n){
  int i;
  for(i=0; i<n;i++){
    free(main[i]);
  }
  free(main);
}
  
void printHeader(){
  FILE *fp;
  fp = fopen("libs/Ficheiros_de_texto/header","r");

  char buffer[200];
  while(fgets(buffer,sizeof(buffer),fp)){
    printf("%s",buffer);  
  }
  fclose(fp);
}

void printtext(int n,char file[],int a){
  FILE *fp;
  fp = fopen(file,"r");
  if(fp == NULL) exit(-1);

  int i=0;
  char buffer[200];
  while(fgets(buffer,sizeof(buffer),fp) && i < n*a ){
    if(i >= n*a-a)
      printf("%s",buffer);
    i++;
  }
}

void printTextTo(int line){
  char file[] = "libs/Ficheiros_de_texto/subHeaders";
  FILE *fp = fopen(file,"r");
  if(fp == NULL) 
    exit(-1);
  char buffer[200];
  int i=1;
  while(fgets(buffer,sizeof(buffer),fp) && i<=7*line){
    if(i>=7*(line-1))
      printf("%s",buffer);
    i++;
  }

}

void printMenu(char **m, int n, int pos,char fileMenu[]){
  int i;
  system("cls");
  printHeader();

  if(!strcmp(fileMenu,"main"))
    printTextTo(1);
  else if(!strcmp(fileMenu,"settings"))
    printTextTo(3);
  else if(!strcmp(fileMenu,"planets"))
    printTextTo(2);
  else if(!strcmp(fileMenu,"Jogadores"))
    printTextTo(4);
  else if(!strcmp(fileMenu,"leave"))
    printTextTo(5);
  else if(!strcmp(fileMenu,"mode"))
    printTextTo(16);
  else
    printf("%s>>\n", fileMenu);

  m[pos][0] = '*';
  for(i=0; i<n; i++){
    if(i!=pos){
      m[i][0] = ' ';
    }
    printf("\t\t\t\t\t%s\n",m[i]);
  }

}

int valueSelect(char file[]){
  int x;
  do{
    x = mainSelect(file);
  }
  while(x <= 0);
  return x;
}

int mainSelect(char fileMenu[]){
  
  FILE *fp;
  char file[100]="";
  strcat(file,PATH);
  strcat(file,fileMenu);

  fp = fopen(file,"r");

  if(fp==NULL) {
    printf("%s\n",file);
    system("pause");
    exit(-1);
  }

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
    
    printMenu(menu,i,opcion,fileMenu);
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

