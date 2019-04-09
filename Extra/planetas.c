#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct planeta
{
	char nome[8];
	float lcampo;
	float acampo;
	float g;
}PLANETA;

void crearPlaneta(){
	PLANETA planeta[9] = {{"Sun",75,70,274.13},{"Mercury",7.5,7,3.7},{"Venus",22.5,21,8.87},{"Earth",15,14,9.81},{"Mars",12,11.2,3.71},{"Jupiter",27,25.2,24.79},{"Saturn",30,28,10.44},{"Uranus",16.5,15.4,8.87},{"Neptune",19.5,18.2,11.15}};

	FILE *fp;
	fp = fopen("planets.data","wb");
	if(fp == NULL){
		printf("ERROR\n");
		exit(-1);
	}
	int i;
	for(i = 0; i < 9; i++)
		fwrite(&planeta[i],sizeof(PLANETA),9-i,fp);
	fclose(fp);
}

void printPlaneta(PLANETA *p){
	printf("%s\n%f %f %f\n",p->nome,p->lcampo,p->acampo,p->g );
}	

void leerPlaneta(){
	FILE *fp;
	fp = fopen("planets.data","r");
	if(fp == NULL){
		printf("ERROR\n");
		exit(-1);
	}

	PLANETA planeta;
	int i;
	while(i < 9 && fread(&planeta,sizeof(PLANETA),1,fp)){
		printPlaneta(&planeta);
		i++;
	}
	
	
	
	fclose(fp);
}

int main(int argc, char const *argv[])
{
	int op;
	scanf("%d",&op);

	if(op==1)
		leerPlaneta();
	if(op==2)
		crearPlaneta();
	

	return 0;
}