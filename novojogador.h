#include <string.h>
#include <stdio.h>


void novoJogador(){
    char nome[100];
 	float altura;
 	int n,i;
 	FILE *fp;
 	fp=fopen("Base_de_datos/Jogadores.data","a");
	if (fp==NULL)
		exit(-1);
	
	printf("How many players do you want to add? \n 	");
	scanf ("%d",&n);
	
	
	for (i=1;i<=n;i++){
	 printf ("\n");
     printf ("What's your player name? \n 	"); 
     scanf (" %[^\n]%*c", nome);
     //verificarNovoJogador(nome);
     printf("What's your heigh? \n 	");
 	 scanf ("%f",&altura);
     fprintf(fp,"%s-%.2f\n", nome,altura); 
    }

	fclose(fp);
}

