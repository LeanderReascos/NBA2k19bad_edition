#define MANUAL "libs/Ficheiros_de_texto/instrucoes.txt"

void instructions(){
	system("cls");
	FILE *fp;
	fp = fopen(MANUAL,"r");
	if(fp == NULL) exit(-1);
	char buffer[100];
	while(fgets(buffer,sizeof(buffer),fp)){
		printf("%s",buffer);
	}
	system("pause");
}