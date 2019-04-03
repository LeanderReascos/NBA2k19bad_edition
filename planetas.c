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
	PLANETA planeta[9] = {{"Sun",30,22,274.13},{"Mercury",10,6,3.7},{"Venus",20,17,8.87},{"Earth",15,11,9.81},{"Mars",12,8,3.71},{"Jupiter",22,18,24.79},{"Saturn",25,21,10.44},{"Uranus",16,12,8.87},{"Neptune",17,13,11.15}};

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