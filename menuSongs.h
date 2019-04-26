#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int leCommand(FILE * file){

	char buffer [20];
	if(file==NULL){
		printf("nao abriu commands\n");
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
	file2=fopen("MUSICAS/.commands","r");
	if(file2==NULL){
		printf("nao abriu commands\n");
		//exit(-1);
	}
	switch (letra){
		case 'p':
				if(leCommand(file2)){
					file2=fopen("MUSICAS/.commands","w");
				    fprintf(file2,"%s","pause");
				}
				else if(leCommand(file2)==0){
					file2=fopen("MUSICAS/.commands","w");
				    fprintf(file2,"%s","play");
				}
				break;	
		case 'n':
				file2=fopen("MUSICAS/.commands","w");
                fprintf(file2,"%s","next");
				break;
		case 'b':
				file2=fopen("MUSICAS/.commands","w");
	    		fprintf(file2,"%s","before");
				break;
		case 's':
    	       file2=fopen("MUSICAS/.commands","w");
               fprintf(file2,"%s","stop");
			break;
}
fclose(file2);
}















