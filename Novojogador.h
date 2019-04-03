
void printheader(char nome_do_ficheiro[]){

FILE *fp;
fp=fopen (nome_do_ficheiro,"r");

if (fp==NULL)
	exit(-1);
	

char buffer[200];

while (fgets(buffer,sizeof(buffer),fp)){
	printf (buffer);
}
fclose (fp);
return;
}



 printheader("header trabalho");
 char nome[100];
 float altura;
 int n,i;
 FILE *fp;
 fp=fopen("Jogadores.data","a");
	if (fp==NULL)
	exit(-1);
	
	printf("How many players do you want to add? \n");
	scanf ("%d",&n);
	
	
	for (i=1;i<=n;i++){
	 printf ("\n");
     printf ("What's your player name? \n"); 
     scanf ("%s",&nome);
     printf("What's your heigh? \n");
 	 scanf ("%f",&altura);
     fprintf(fp,"%s;%f; \n", nome,altura); 
     }

	fclose(fp);
 
 
 
 
 
 
 

 


