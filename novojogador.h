#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void novoJogador(){ ///CICLO VICIADO SÓ SAI CASO VALIDAR=0 QUE SE TORNA 1 QUANDO ENCONTRA UM NOME IGUAL NO FICHEIRO
	int numero=1;
	int ans;
	do{  	
		system("cls");
		printHeader();
  		prints("Ficheiros_de_texto/novojogador.txt");
		printtext(numero+2,"Ficheiros_de_texto/numberSelect",8);
		ans = selectNumber(&numero);
	}
	while(ans != 0);
	
	char nome[100];
 	float altura;
 	int n,i;
 	FILE *fp;
 	FILE *text;
 	fp=fopen("Base_de_datos/Jogadores.data","a");
 	text = fopen("Ficheiros_de_texto/Jogadores","a");
	if (fp==NULL || text==NULL)
		exit(-1);
	
//	printf("How many players do you want to add? \n 	");
//	scanf ("%d",&n);
	
	n=numero;
	int validar=0;
	for (i=1;i<=n;i++){
		while (1){
			validar=0;
			system("cls");
			printHeader();
			printf ("\n");
		    printf ("What's your player name? \n 	"); 
		    scanf (" %[^\n]%*c", nome);
		     
		     /////VERIFICACAO SE JÁ EXISTE JOGADOR
		     /////LER O FICHEIRO
		     
			FILE *fp2;
			fp2 = fopen("Base_de_datos/Jogadores.data","r");

		  	if(fp2==NULL) exit(-1);


		  	char* nficheiro=(char*) malloc(30*sizeof(char));
		  	char buffer[200];
		  	while(validar==0 && fgets(buffer,sizeof(buffer),fp2) ){
		       	nficheiro=strtok(buffer,"-");
		  	    if(strcmp(nficheiro,nome)==0)
			    	validar=1;	
				nficheiro=NULL;
		 	}

		 	free(nficheiro);
		  	fclose(fp2);
		  
		 	if (validar==0)
		  		break;
		  	
		  	system("cls");
		 	printHeader();
		 	printf("That player already exists.Please insert a different player name.\n");
		 	system("pause");
	     
		}
	    system("cls");
		printHeader();
	    printf("What's your heigh? \n 	");
	 	scanf ("%f",&altura);
	    fprintf(fp,"%s-%.2f\n", nome,altura); 
	    fprintf(text,"%s-%.2f\n", nome,altura);
    }

	fclose(fp);
	fclose(text);
	  
}



