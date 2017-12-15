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

polozka* vytvorenie_zoznamu(){
	FILE *fr;
	int mnozstvo_zaznamov=0;
	char c;
	polozka *zaznam,*pom;
		if ((fr=fopen("auta.txt","r")) == NULL){
				printf("Zaznamy neboli nacitane\n");
				return NULL;//ak sa subor neda otvorit tak vypisem oznam a vratim hodnotu NULL.
		}

	zaznam=(polozka*) malloc (sizeof(polozka));//dynamicky si alokujem prvu strukturu
	c=fgetc(fr);
	if (c=='$')mnozstvo_zaznamov++;//pocitam si pocet zaznamov
	fgetc(fr);
	fgets (zaznam->kategoria,52,fr);
	fgets (zaznam->znacka,52,fr);
	fgets (zaznam->predajca,102,fr);
	fscanf (fr,"%d",&zaznam->cena);
	fscanf (fr,"%d\n",&zaznam->rok_vyroby);
	fgets (zaznam->stav_vozidla,202,fr); //nacitam do nej udaje zo suboru
	c=fgetc(fr);
	fgetc(fr);
   zaznam->dalsi=NULL;
   pom=zaznam;

   	   while (c=='$') //ak je v subore dalsi zaznam, tak vykonam nasledujuci cyklus
   	   {
   	   		mnozstvo_zaznamov++;
   		   pom->dalsi=(polozka*) malloc (sizeof(polozka));	//alokujem si strukturu na smernik v predchadzajucej strukture  
   		   pom=pom->dalsi;
   		   fgets (pom->kategoria,52,fr);
   		   fgets (pom->znacka,52,fr);
   		   fgets (pom->predajca,102,fr);
   		   fscanf (fr,"%d",&pom->cena);
   		   fscanf (fr,"%d\n",&pom->rok_vyroby);
   		   fgets (pom->stav_vozidla,202,fr);//nacitam si do struktury udaje zo suboru
   		   c=fgetc(fr);
   		   fgetc(fr);
   		   pom->dalsi=NULL;
   	   }

   fclose(fr);//zavrem subor
   printf("Nacitalo sa %d zaznamov \n",mnozstvo_zaznamov);//vypsiem oznam
 return zaznam; //vratim smernik ukazujuci na zaciatok spajaneho zoznamu struktur
}

void vypisanie_zoznamu(polozka *zaznam){
	polozka *pom=zaznam;
	int x=0;
	 while (pom!=NULL)
	    {
	    x++;
	      printf ("%d.\n",x);
	      printf("kategoria: %s",pom->kategoria);
	      printf("znacka: %s",pom->znacka);
	      printf("predajca: %s",pom->predajca);
	      printf("cena: %d\n",pom->cena);
	      printf("rok_vyroby: %d\n",pom->rok_vyroby);
	      printf("stav_vozidla: %s",pom->stav_vozidla);
	      pom=pom->dalsi; 
	    }//postupne vypisujem obsah struktur na standartny vystup
}

void pridanie_zaznamu(polozka **zaznam){
	polozka *pom,*novy;
	novy=(polozka*) malloc (sizeof(polozka));//alokujem si novy strukturu
	int pozicia=0;
	scanf("%d\n",&pozicia);
	gets(novy->kategoria);
	strcat (novy->kategoria,"\n");
	gets(novy->znacka);
	strcat (novy->znacka,"\n");
	gets(novy->predajca);
	strcat (novy->predajca,"\n");
	scanf("%d\n",&(novy->cena));
	scanf("%d\n",&(novy->rok_vyroby));
	gets(novy->stav_vozidla);
	strcat (novy->stav_vozidla,"\n");	//nacitam si do nej udaje z standartneho vstupu a za kazdy udaj doplnim znak \n
	if (*zaznam==NULL) {
	*zaznam=novy;
	novy->dalsi=NULL;					//ak spajany zaznam struktur neexistuje, tak tato struktura sa stane prvou strukturou v spajanom zozname struktur
	}
		else 
			if (pozicia==1){
				novy->dalsi=*zaznam;	//ak spajany zoznam struktur existuje a umiestnujem tuto strukturu na prvu poziciu
				*zaznam=novy;			// tak smernik z tejto strukury poslem na spajany zoznam a smernik zo zaciatku zoznamu poslem na tuto strukturu
			} 
			else{ 
			pom= *zaznam;
			int i;
			for (i=0;i<pozicia-2;i++)	//ak strukturu umiestujem na inu poziciu do existujuceho spajaneho zoznamu struktur
				if (pom->dalsi!=NULL) pom=pom->dalsi;//nastavim si pomocny smernik pom na strukturu za ktoru budem pridavat novu strukturu
			if (i>=pozicia-2){
				novy->dalsi=pom->dalsi;//na smernik z novej struktury umiestnim zvysok spajaneho zoznamu struktur
				pom->dalsi=novy;		//novu strukturu umiestnim za strukturu na ktoru ukazuje pomocny smernik
			}
			else pom->dalsi=novy;		//ak som prisiel na koniec zoznamu a zadana pozicia sa v zozname nenachadza tak strukturu umiestnim na koniec	
			}
}

void vymazanie_zaznamu(polozka **zaznam){
	int zhoda=0,pocet_vymazanych=0,i,j,k;
	char s[52],c[52];
	polozka *pom=(*zaznam)->dalsi;
	polozka *predosli=*zaznam;
		gets(s);
		gets(s);
		printf("%s.\n",s);
		for(i=0;i<strlen(s);i++){
			s[i]=tolower(s[i]);			//string z vstupu upravym na male pismena
		}
		
	while (predosli!=NULL){				//tento cyklus je prvu poziciu v spajanom zozname struktur
			strcpy(c,predosli->znacka);
			for(i=0;i<strlen(c);i++){
				c[i]=tolower(c[i]);		//string z struktury upravim na male pismena
			}
			i=0;
			while(c[i]!='\0'){			//robim cyklus po charoch do konca nacitaneho stringu
				if(c[i]==s[0]){
					j=0;k=0;
					for(j=i;j<=j+strlen(s);j++){
						if (c[j]!=s[k]){	//zistujem ci sa chary rovnaju, ak nie break-nem cyklus
							break;	
						}
						k++;
					}
					if (k==strlen(s)) {	//ak ma string zo vstupu dlzku k a mam zhodnych k charov po sebe tak je najdena zhoda
						zhoda=1;
						break;
					}
				}
			i++;
			}
			if(zhoda==1) {
				pocet_vymazanych++;	
				*zaznam=(*zaznam)->dalsi;
				free(predosli);
				predosli=*zaznam;
				zhoda=0;
			} else {
				pom=*zaznam;
				break;	//ak nemazem prvu poziciu break-nem tento cyklus a prejdem na dalsi	
				}					
}
				
if (predosli!=NULL)	//tento cyklus je pre zvysok spajaneho zoznamu struktur
	while (pom!=NULL){
		strcpy(c,pom->znacka);
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
					zhoda=1;
					break;
				}
			}
		i++;
		}
		if(zhoda==1) {			//ak mam zhodu, idem vymazat danu strukturu, poslem si smernik  na nasledujucu strukturu
			pocet_vymazanych++;	
			predosli->dalsi = pom->dalsi;
	  		free (pom); 		
	  		pom = predosli->dalsi;
	  		zhoda=0;
		}
		else{
			predosli = pom;
	  		pom = pom->dalsi;
		}
	}
		printf("Vymazalo sa %d zaznamov\n",pocet_vymazanych);		
}

void hladanie_zaznamov(polozka *zaznam){
polozka *pom=zaznam;
int y,x=0;
	scanf("%d",&y);
	while (pom!=NULL)				//prehladavam cely zoznam spajanych struktur
		{
			if ((pom->cena)<=y){	//ak plati podmienka tak danu strukturu vypisem na standartny vystup
			x++;
	      	printf ("%d.\n",x);
	     	printf("kategoria: %s",pom->kategoria);
	      	printf("znacka: %s",pom->znacka);
	      	printf("predajca: %s",pom->predajca);
	      	printf("cena: %d\n",pom->cena);
	      	printf("rok_vyroby: %d\n",pom->rok_vyroby);
	      	printf("stav_vozidla: %s",pom->stav_vozidla);	
			} 
	     	pom=pom->dalsi;
	    }
	if(x==0) printf("V ponuke su len auta s vyssou cenou\n"); 
}

void aktualizacia_zaznamu(polozka *zaznam){
polozka *pom=zaznam;
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
	strcat (stav_vozidla,"\n");		//nacitam si do lokalnych premennych udaje zo vstupu
	while (pom!=NULL)
		{ 
		strcpy(s,pom->znacka);
		for(i=0;i<=strlen(c);i++) if(c[i]!=s[i]) break;
			if ((i==(strlen(c)))&&(x==(pom->cena))){	//prehladavam spajany zoznam struktur, ak nejaka vyhovuje podmienkam
				y++;									// tak do nej nahram udaje z premennych 
				strcpy(pom->kategoria,kategoria);
				strcpy(pom->znacka,znacka);
				strcpy(pom->predajca,predajca);
				pom->cena=cena;
				pom->rok_vyroby=rok_vyroby;
				strcpy(pom->stav_vozidla,stav_vozidla);	
			}
	     	pom=pom->dalsi;	
	    }
	printf("Aktualizovalo sa %d zaznamov\n",y);
}

int main (){
char c;
polozka *zaznam=NULL;
while ((c=getchar())!='k'){
	if (c=='n') {
		if (zaznam!=NULL) //ak uz existuje spajany zoznam struktur tak ho odstranim z pamäte
			free(zaznam);
		zaznam=vytvorenie_zoznamu();
		continue;
	}
	if (c=='v') {
		vypisanie_zoznamu(zaznam);
		continue;
	}	
	if (c=='p') {
		pridanie_zaznamu(&zaznam); 
		continue;
	}	
	if (c=='z') {
		if ((zaznam)==NULL) printf("Vymazalo sa 0 zaznamov\n");
		 else vymazanie_zaznamu(&zaznam); 
		continue;
	}
	if (c=='h') {
		hladanie_zaznamov(zaznam); 
		continue;
	}	
	if (c=='a') {
		if ((zaznam)==NULL) printf("Aktualizovalo sa 0 zaznamov\n");
		 else aktualizacia_zaznamu(zaznam); 
		continue;
	}
}
if (c=='k')
	if (zaznam!=NULL) 
		free(zaznam);

return 0;
}
