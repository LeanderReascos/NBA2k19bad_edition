#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "novojogador.h"


void novaaltura(char nome[100],int numerodelinha ,FILE *ptr){
	printf("What's your height?");
	scanf ("%f",&altura);
	float altura;
	int temp=1;
	rewind(ptr);
    //open new file in write mode
    FILE ptr2;
    ptr2 = fopen("replica.c", "w");
    ch = 'A';
    while (ch != EOF)
    {
        ch = getc(ptr);
        //except the line to be deleted
        if (temp != numerodelinha)
        {
            //copy all lines in file replica.c
            putc(ch, ptr2);
        }
        if (ch == '\n')
        {
            temp++;
        }
    }
    fclose(ptr);
    fclose(ptr2);
   
    //rename the file replica.c to original name
    rename("replica.c", "Base_de_datos/Jogadores.data");
    //adicionar linha ao ficheiro
    
    FILE *fp;
 	fp=fopen("Base_de_datos/Jogadores.data","a");
	if (fp==NULL)
		exit(-1);
	fprintf(fp,"%s-%.2f\n", nome,altura);
    
    
    
    
  return; 	
}




void verificarNovoJogador () {
	
	int i,j,k,g,n;
	
	
	FILE *fp2;
	fp2=fopen("Base_de_datos/Jogadores.data","r");
	if (fp2==NULL)
		exit(-1);
	
	
	char line[200];
	while (fgets(line,200 , fp2) != NULL)  {
		char *ptrnomeficheiro;
		ptrnomeficheiro=strtok (line,"-");
		int linha=0;
		do{
		for (i=0;i<strlen(ptrnomeficheiro);i++){
			if(ptrnomeficheiro[i]=nome[i])
			k=0;
			else 
			k=1;
			}
			linha=linha+1;
		}while (k=0); 
		
		if(k=1){
			
			printf("That username is taken.");
			printf("Do you want to change your height?");
			char ans[3];
			gets(ans);
			char stringyes[3]="yes";
			
			do{
			for (j=0;j<strlen(ans);j++)
				if(ans[i]=stringyes[i])
				g=0;
				else
				g=1;
			}while (g=0);
			
			if (g=0)
			novaaltura(nome,linha,*fp2);
			else
			novoJogador();
			
		}
			
				
	}
	
	fclose(fp2);
	
}
