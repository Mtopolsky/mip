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

void U(N **I){
	N *G,*P;
	P=(N*) malloc (sizeof(N));
	int R=0;
	scanf("%d\n",&R);
	gets(P->A);
	strcat (P->A,"\n");
	gets(P->B);
	strcat (P->B,"\n");
	gets(P->C);
	strcat (P->C,"\n");
	scanf("%d\n",&(P->D));
	scanf("%d\n",&(P->E));
	gets(P->F);
	strcat (P->F,"\n");	
	if (*I==NULL) {
	*I=P;
	P->H=NULL;					
	}
		else 
			if (R==1){
				P->H=*I;
				*I=P;			
			} 
			else{ 
			G= *I;
			int i;
			for (i=0;i<R-2;i++)	
				if (G->H!=NULL) G=G->H;
			if (i>=R-2){
				P->H=G->H;
				G->H=P;	
			}
			else G->H=P;	
			}
}

void V(N **I){
	int K=0,L=0,i,j,k;
	char s[52],c[52];
	N *G=(*I)->H;
	N *J=*I;
		gets(s);
		gets(s);
		printf("%s.\n",s);
		for(i=0;i<strlen(s);i++){
			s[i]=tolower(s[i]);	
		}
		
	while (J!=NULL){	
			strcpy(c,J->B);
			for(i=0;i<strlen(c);i++){
				c[i]=tolower(c[i]);	
			}
			i=0;
			while(c[i]!='\0'){
				if(c[i]==s[0]){
					j=0;k=0;
					for(j=i;j<=j+strlen(s);j++){
						if (c[j]!=s[k]){
							break;	
						}
						k++;
					}
					if (k==strlen(s)) {
						K=1;
						break;
					}
				}
			i++;
			}
			if(K==1) {
				L++;	
				*I=(*I)->H;
				free(J);
				J=*I;
				K=0;
			} else {
				G=*I;
				break;
				}					
}

if (J!=NULL)
	while (G!=NULL){
		strcpy(c,G->B);
		for(i=0;i<strlen(c);i++){
			c[i]=tolower(c[i]);	
		}
		i=0;
		while(c[i]!='\0'){
			if(c[i]==s[0]){
				j=0;k=0;
				for(j=i;j<=j+strlen(s);j++){
					if (c[j]!=s[k]){
						break;	
					}
					k++;
				}
				if (k==strlen(s)) {
					K=1;
					break;
				}
			}
		i++;
		}
		if(K==1) {	
			L++;	
			J->H = G->H;
	  		free (G); 		
	  		G = J->H;
	  		K=0;
		}
		else{
			J = G;
	  		G = G->H;
		}
	}
		printf("Vymazalo sa %d zaznamov\n",L);		
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
	if (c=='p') {
		U(&I); 
		continue;
	}
	if (c=='z') {
		if ((I)==NULL) printf("Vymazalo sa 0 zaznamov\n");
		 else V(&I); 
		continue;
	}
}	
  return 0;
}