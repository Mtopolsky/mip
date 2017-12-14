#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct M{
char A [52];
char B [52];
char C [102];
int D;
int E;
char F [202];
struct M *H;
};

typedef struct M N ;

N* S(){
	FILE *fr;
	int O=0;
	char c;
	N *I,*G;
		if ((fr=fopen("auta.txt","r")) == NULL){
				printf("Zaznamy neboli nacitane\n");
				return NULL;
		}

	I=(N*) malloc (sizeof(N));
	c=fgetc(fr);
	if (c=='$')O++;
	fgetc(fr);
	fgets (I->A,52,fr);
	fgets (I->B,52,fr);
	fgets (I->C,102,fr);
	fscanf (fr,"%d",&I->D);
	fscanf (fr,"%d\n",&I->E);
	fgets (I->F,202,fr);
	c=fgetc(fr);
	fgetc(fr);
   I->H=NULL;
   G=I;

   	   while (c=='$') 
   	   {
   	   		O++;
   		   G->H=(N*) malloc (sizeof(N));	
   		   G=G->H;
   		   fgets (G->A,52,fr);
   		   fgets (G->B,52,fr);
   		   fgets (G->C,102,fr);
   		   fscanf (fr,"%d",&G->D);
   		   fscanf (fr,"%d\n",&G->E);
   		   fgets (G->F,202,fr);
   		   c=fgetc(fr);
   		   fgetc(fr);
   		   G->H=NULL;
   	   }

   fclose(fr);
   printf("Nacitalo sa %d zaznamov \n",O);
 return I; 
}

void T(N *I){
	N *G=I;
	int x=0;
	 while (G!=NULL)
	    {
	    x++;
	      printf ("%d.\n",x);
	      printf("A: %s",G->A);
	      printf("B: %s",G->B);
	      printf("C: %s",G->C);
	      printf("D: %d\n",G->D);
	      printf("E: %d\n",G->E);
	      printf("F: %s",G->F);
	      G=G->H; 
	    }
}
int main (){
char c;
N *I=NULL;
while ((c=getchar())!='k'){
	if (c=='n') {
		if (I!=NULL) 
			free(I);
		I=S();
		continue;
	}
	if (c=='v') {
		T(I);
		continue;
  }
  return 0;
}