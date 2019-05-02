#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int leCommand(FILE * file){

	char buffer [20];
	if(file==NULL){
		printf("Commands didn't open'\n");
		exit(-1);
	  }
	fgets(buffer,sizeof(buffer),file);
	fclose(file);
	if(strcmp(buffer,"play")==0){
	    return 1;
	}
	else if(strcmp(buffer,"pause")==0){
	    return 0;
	}
}


void Musica(char letra){
	FILE * file2;
	file2=fopen("libs/MUSICAS/.commands","r");
	if(file2==NULL){
		printf("Commands didn't open'\n");
		//exit(-1);
	}
	char c[10];
	strcpy(c,strupr(&letra));
	switch (c[0]){
		case 'P':
				if(leCommand(file2)){
					file2=fopen("libs/MUSICAS/.commands","w");
				    fprintf(file2,"%s","pause");
				}
				else if(leCommand(file2)==0){
					file2=fopen("libs/MUSICAS/.commands","w");
				    fprintf(file2,"%s","play");
				}
				break;	
		case 'N':
				file2=fopen("libs/MUSICAS/.commands","w");
                fprintf(file2,"%s","next");
				break;
		case 'B':
				file2=fopen("libs/MUSICAS/.commands","w");
	    		fprintf(file2,"%s","before");
				break;
		case 'S':
    	       file2=fopen("libs/MUSICAS/.commands","w");
               fprintf(file2,"%s","stop");
			break;
}
fclose(file2);
}















