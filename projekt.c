#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct polozkaa{
char kategoria [52];
char znacka [52];
char predajca [102];
int cena;
int rok_vyroby;
char stav_vozidla [202];
struct polozkaa *dalsi;
};

typedef struct polozkaa polozka ;

polozka* S(){
	FILE *fr;
	int O=0;
	char c;
	polozka *I,*G;
		if ((fr=fopen("auta.txt","r")) == NULL){
				printf("Zaznamy neboli nacitane\n");
				return NULL;
		}

	I=(polozka*) malloc (sizeof(polozka));
	c=fgetc(fr);
	if (c=='$')O++;
	fgetc(fr);
	fgets (I->kategoria,52,fr);
	fgets (I->znacka,52,fr);
	fgets (I->predajca,102,fr);
	fscanf (fr,"%d",&I->cena);
	fscanf (fr,"%d\n",&I->rok_vyroby);
	fgets (I->stav_vozidla,202,fr);
	c=fgetc(fr);
	fgetc(fr);
   I->dalsi=NULL;
   G=I;

   	   while (c=='$') 
   	   {
   	   		O++;
   		   G->dalsi=(polozka*) malloc (sizeof(polozka));	
   		   G=G->dalsi;
   		   fgets (G->kategoria,52,fr);
   		   fgets (G->znacka,52,fr);
   		   fgets (G->predajca,102,fr);
   		   fscanf (fr,"%d",&G->cena);
   		   fscanf (fr,"%d\n",&G->rok_vyroby);
   		   fgets (G->stav_vozidla,202,fr);
   		   c=fgetc(fr);
   		   fgetc(fr);
   		   G->dalsi=NULL;
   	   }

   fclose(fr);
   printf("Nacitalo sa %d zaznamov \n",O);
 return I; 
}

void T(polozka *I){
	polozka *G=I;
	int x=0;
	 while (G!=NULL)
	    {
	    x++;
	      printf ("%d.\n",x);
	      printf("kategoria: %s",G->kategoria);
	      printf("znacka: %s",G->znacka);
	      printf("predajca: %s",G->predajca);
	      printf("cena: %d\n",G->cena);
	      printf("rok_vyroby: %d\n",G->rok_vyroby);
	      printf("stav_vozidla: %s",G->stav_vozidla);
	      G=G->dalsi; 
	    }
}

void U(polozka **I){
	polozka *G,*P;
	P=(polozka*) malloc (sizeof(polozka));
	int R=0;
	scanf("%d\n",&R);
	gets(P->kategoria);
	strcat (P->kategoria,"\n");
	gets(P->znacka);
	strcat (P->znacka,"\n");
	gets(P->predajca);
	strcat (P->predajca,"\n");
	scanf("%d\n",&(P->cena));
	scanf("%d\n",&(P->rok_vyroby));
	gets(P->stav_vozidla);
	strcat (P->stav_vozidla,"\n");	
	if (*I==NULL) {
	*I=P;
	P->dalsi=NULL;					
	}
		else 
			if (R==1){
				P->dalsi=*I;
				*I=P;			
			} 
			else{ 
			G= *I;
			int i;
			for (i=0;i<R-2;i++)	
				if (G->dalsi!=NULL) G=G->dalsi;
			if (i>=R-2){
				P->dalsi=G->dalsi;
				G->dalsi=P;	
			}
			else G->dalsi=P;	
			}
}

void V(polozka **I){
	int K=0,L=0,i,j,k;
	char s[52],c[52];
	polozka *G=(*I)->dalsi;
	polozka *J=*I;
		gets(s);
		gets(s);
		printf("%s.\n",s);
		for(i=0;i<strlen(s);i++){
			s[i]=tolower(s[i]);	
		}
		
	while (J!=NULL){	
			strcpy(c,J->znacka);
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
				*I=(*I)->dalsi;
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
		strcpy(c,G->znacka);
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
			J->dalsi = G->dalsi;
	  		free (G); 		
	  		G = J->dalsi;
	  		K=0;
		}
		else{
			J = G;
	  		G = G->dalsi;
		}
	}
		printf("Vymazalo sa %d zaznamov\n",L);		
}

void W(polozka *I){
polozka *G=I;
int y,x=0;
	scanf("%d",&y);
	while (G!=NULL)		
		{
			if ((G->cena)<=y){
			x++;
	      	printf ("%d.\n",x);
	     	printf("kategoria: %s",G->kategoria);
	      	printf("znacka: %s",G->znacka);
	      	printf("predajca: %s",G->predajca);
	      	printf("cena: %d\n",G->cena);
	      	printf("rok_vyroby: %d\n",G->rok_vyroby);
	      	printf("stav_vozidla: %s",G->stav_vozidla);	
			} 
	     	G=G->dalsi;
	    }
	if(x==0) printf("V ponuke su len auta s vyssou cenou\n"); 
}

void X(polozka *I){
polozka *G=I;
char s[52],c[52];
int x=0,y=0,i;
char kategoria [52];
char znacka [52];
char predajca [102];
int cena;
int rok_vyroby;
char stav_vozidla [202];
	for (i=0;i<52;i++){
		s[i]='\0';
		c[i]='\0';
	}
	gets(c);
	gets(c);
	printf("%s.\n",c);
	scanf("%d\n",&x);	
	gets(kategoria);
	strcat (kategoria,"\n");
	gets(znacka);
	strcat (znacka,"\n");
	gets(predajca);
	strcat (predajca,"\n");
	scanf("%d\n",&cena);
	scanf("%d\n",&rok_vyroby);
	gets(stav_vozidla);
	strcat (stav_vozidla,"\n");	
	while (G!=NULL)
		{ 
		strcpy(s,G->znacka);
		for(i=0;i<=strlen(c);i++) if(c[i]!=s[i]) break;
			if ((i==(strlen(c)))&&(x==(G->cena))){
				y++;
				strcpy(G->kategoria,kategoria);
				strcpy(G->znacka,znacka);
				strcpy(G->predajca,predajca);
				G->cena=cena;
				G->rok_vyroby=rok_vyroby;
				strcpy(G->stav_vozidla,stav_vozidla);	
			}
	     	G=G->dalsi;	
	    }
	printf("Aktualizovalo sa %d zaznamov\n",y);
}

int main (){
char c;
polozka *I=NULL;
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
	if (c=='h') {
		W(I); 
		continue;
	}	
	if (c=='kategoria') {
		if ((I)==NULL) printf("Aktualizovalo sa 0 zaznamov\n");
		 else X(I); 
		continue;
	}
}
if (c=='k')
	if (I!=NULL) 
		free(I);

return 0;
}
