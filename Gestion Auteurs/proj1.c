#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TMAX 1000

typedef struct Date Date;
struct Date{
	int jour ;
	char mois[10];
	int annee;
};


typedef struct Auteur Auteur;
struct Auteur{
	char code[10] ;
	char nom [30];
	char prenom [20];
	Date Naissance;

};
	
void addAuteur();
void AfficherAuteur();
void ModifierAuteur();
void Rechercher(Auteur Perso);
void Supprimer();

int main(){
	Auteur P ;
	int rep=0 , menu=0;
	int choix;
	
	do{
	printf("\n \n \n \n \n \n \n ")  ;
	printf("\t \t \t  ********* MENU DE LA GESTION DES AUTEURS *******\n\n");
	printf("\t \t \t $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n");
	printf("\t \t \t $$  Pour ajouter <auteur> .................... 1 \n");
	printf("\t \t \t $$  Pour afficher la liste des auteurs ....... 2 \n");
	printf("\t \t \t $$  Pour modifier auteur ..................... 3 \n");
	printf("\t \t \t $$  Pour suprimer un auteur .................. 4 \n");
	printf("\t \t \t $$  Pour rechercher un auteur ................ 5 \n");
	printf("\t \t \t $$  Pour quitter le programme ................ 0 \n");
	printf("\t \t \t $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n");
	printf("\n");
	 
	
		printf("\n\t \t \t $$ BIENVENU DANS LE MENU DONNER VOTRE CHOIX s.v.p. : "); 
		scanf("%d",&choix);
	
		switch(choix){
		case 1 :do{
				printf("\t \t \t *** Vous souhaitez ajouter un auteur ****\n");
				addAuteur();
				printf("\t \t \t l ajout a ete effectue avec succes.\n");
				printf("\t \t \tVOULEZ VOUS AJOUTEZ UN AUTEUR (1/0) :");
				scanf("%d",&rep);
		}while(rep==1);
		break;
		
		case 2 :printf("\t \t \t *** Vous souhaitez afficher la liste des auteurs ****\n");
				AfficherAuteur();
				break;
	
		case 3 :do{
				printf("\t \t \t *** Vous souhaitez modifier un auteur ****\n");
				ModifierAuteur();
				printf("\t \t \t VOULEZ VOUS MODIFIER UN AUTRE AUTEUR (1/0) :");
				scanf("%d",&rep);
			}while(rep == 1);
			break;
		
		case 4 : do{
				printf("\t \t \t *** Vous souhaitez supprimer un auteur ****\n");	
				Supprimer();
				printf("\t \t \t VOULEZ VOUS SUPPRIMER UN AUTRE AUTEUR (1/0) :");
				scanf("%d",&rep);
		}while(rep == 1);
		break;
			
		case 5 :do{
				printf("\t \t \t *** Vous souhaitez rechercher un auteur ****\n");
				Rechercher(P);
				printf("\t \t \tVOULEZ VOUS RECHERCHEZ UN AUTRE AUTEUR (1/0) :");
				scanf("%d",&rep);
			}while(rep==1);
			break;
		
		case 0: printf("\t \t \t Vous avez quitte le programme A bientot ...");
				menu = 0;
				continue;
		}
		printf("\t \t \t VOULEZ VOUS RETOURNER AU MENU ou QUITTER LE PROGRAMME (1/0) : ");
		scanf("%d",&menu);
		system("cls");
	}while(menu == 1);

	
	
}

// **************  FONCTION POUR AJOUTER AUTEUR **************

void addAuteur(){
	
	FILE *fic = fopen("Auteurs.txt","a");
	Auteur Perso;
	fseek(fic,0,2); // on se place a la fin pour ne pas ecraser les autres
	printf("\t \t \t Entre le code de l auteur : ");
	scanf("%s",&Perso.code);

	printf("\t \t \t Entre le nom et le prenom de l auteur : ");
	scanf("%s%s",&Perso.nom,&Perso.prenom);

	printf("\t \t \t Entre la date de naissance de l auteur : ");
	scanf("%d%s%d",&Perso.Naissance.jour,&Perso.Naissance.mois,&Perso.Naissance.annee);
	
	fprintf(fic,"%s   ",Perso.code);
	fprintf(fic,"%s   %s",Perso.nom,Perso.prenom);	
	fprintf(fic,"   %d %s %d \n",Perso.Naissance.jour,Perso.Naissance.mois,Perso.Naissance.annee);
	fclose(fic);
} 

// **************  FONCTION POUR AFFICHER AUTEUR  **************

void AfficherAuteur(){
	
	FILE *fic = fopen("Auteurs.txt","r");
	Auteur Perso;
	int caractereActuel;
	char chaine[TMAX];
	fseek(fic,0,2);// on place le curseur a la fin 
	if(ftell(fic)==0){
		printf("\t \t \t le fichier est vide,il ya rien a affiche !\n");
		return; 
	}
	rewind(fic); // on place le ptr au debut
		printf("\t \t \t-----------------------------------------------\n");
		printf("\t \t \tCode    Nom    Prenom    Date de naissance \n"); 
		printf("\t \t \t-----------------------------------------------\n");
		
		while(fgets(chaine,TMAX,fic) != NULL){
			printf("\t \t \t %s ",chaine);
		}
	
	fclose(fic);
}

// **************  FONCTION POUR RECHERCHER AUTEUR **************

void ModifierAuteur(){
	
	FILE *fic = fopen("Auteurs.txt","r");
	FILE *tmp = fopen("tmp.txt","w");
	// Declaration des variables 
	Auteur Perso;
	char codesEntre[10];
	char chaine [TMAX];
	int trouve ;
	char nvNom[20],nvPrenom[20];
	Date nvNaissance;
	
	if(fic == NULL || tmp == NULL){
		printf("Erreur d ouverture");
		exit(1);
	}
	
	printf("\t \t \t Entre le code de l auteur que vous souhaitez modifiez :");
	scanf("%s",&codesEntre);
	
	do{
		fscanf(fic,"%s %s %s %d %s %d \n",&Perso.code,&Perso.nom,&Perso.prenom,&Perso.Naissance.jour,&Perso.Naissance.mois,&Perso.Naissance.annee);//lit le fichier
		if(strcmp(codesEntre,Perso.code) == 0){
				trouve = 1;
				break;
		}
	}while(!feof(fic)); // rechercher si le code entre existe 
	
		if(trouve == 1){  // si on trouve le code entre on affiche les infos de l'auteur
			printf("\t \t \t Les infos de l auteur que vous souhaitez modifiez sont : \n");
				printf("\t \t \t Code\tNom\tPrenom\tDate de Naissance \n");
				printf("\t \t \t-------------------------------------------------\n");
				printf("\t \t \t %s\t%s\t%s\t%d %s %d\n",Perso.code,Perso.nom,Perso.prenom,Perso.Naissance.jour,Perso.Naissance.mois,Perso.Naissance.annee);
		}
		else{
			printf("\t \t \t le code entre existe pas dans le fichier \n");
		}
		fclose(fic);
		
		fic = fopen("Auteurs.txt","r");
		
		printf("\n\t \t \t Entre les nouvelles Donnees \n");
		printf("\t \t \t Entre le nouveau nom et prenom de l auteur : ");scanf("%s%s",&nvNom,&nvPrenom);
		
		printf("\t \t \t Entre la nouvelle date de naissance de l auteur : ");
		scanf("%d%s%d",&nvNaissance.jour,&nvNaissance.mois,&nvNaissance.annee);
		
		do{
			fscanf(fic,"%s %s %s %d %s %d \n",&Perso.code,&Perso.nom,&Perso.prenom,&Perso.Naissance.jour,&Perso.Naissance.mois,&Perso.Naissance.annee);
			if(strcmp(codesEntre,Perso.code)==0){
				fprintf(tmp,"%s   ",codesEntre);
				fprintf(tmp,"%s   %s",nvNom,nvPrenom);
				fprintf(tmp,"   %d %s %d \n",nvNaissance.jour,nvNaissance.mois,nvNaissance.annee);
				
			}else{
				fprintf(tmp,"%s %s %s %d %s %d \n",Perso.code,Perso.nom,Perso.prenom,Perso.Naissance.jour,Perso.Naissance.mois,Perso.Naissance.annee);
			}
			
		}while(!feof(fic));
		
		fclose(tmp);
		fclose(fic);
		
		remove("Auteurs.txt");
		rename("tmp.txt","Auteurs.txt");
		getch();
}

// ************  FONCTION POUR RECHERCHER AUTEUR **************

void Rechercher(Auteur Perso){
	
	FILE * fic = fopen("Auteurs.txt","r");
	
	int search , found = 0;
	char nomEnter[10] , prenomEnter[20];
	char codeEntre[10];Date birth;
	
	if(fic == NULL) {
		printf("erreur d ouverture ");
		exit(1);
	}
	
	printf("\t\t\t Vous souhaitez recherchez l auteur a partir du : \n"); 
	printf("\t\t\t 1-code \n");
	printf("\t\t\t 2-Nom \n");
	printf("\t\t\t 3-Date de naissance \n");
	printf("\t\t\t choix : ");
	scanf("%d",&search);
	
	switch(search){
		
	case 1 : printf("\t\t\t Entre le code de l auteur : ");scanf("%s",codeEntre);
				do{
					fscanf(fic,"%s %s %s %d %s %d ",&Perso.code,&Perso.nom,&Perso.prenom,&Perso.Naissance.jour,&Perso.Naissance.mois,&Perso.Naissance.annee);
					if(strcmp(codeEntre,Perso.code)==0){
						found = 1;
						break;
					}
				}while(!feof(fic));
		break;
	case 2 : 	printf("\t \t \t Entre le nom de l'auteur : ");
				scanf("%s",&nomEnter); //nom qu'on rechercher
				printf("\t \t \tEntre le prenom de l auteur :");
				scanf("%s",&prenomEnter); // prenom qu'on rechercher
				do{
					fscanf(fic,"%s %s %s %d %s %d \n",&Perso.code,&Perso.nom,&Perso.prenom,&Perso.Naissance.jour,&Perso.Naissance.mois,&Perso.Naissance.annee);//lit le fichier
					if(strcmpi(nomEnter,Perso.nom)==0 && strcmpi(prenomEnter,Perso.prenom)==0 ){
						found = 1;
						break;
					}
			}while(!feof(fic));
		break;
	case 3 : printf("\t \t \tEntre la date de naissance de l auteur : ");
			scanf("%d%s%d",&birth.jour,&birth.mois,&birth.annee);
			do{
				fscanf(fic,"%s %s %s %d %s %d \n",&Perso.code,&Perso.nom,&Perso.prenom,&Perso.Naissance.jour,&Perso.Naissance.mois,&Perso.Naissance.annee );
				if((birth.jour==Perso.Naissance.jour) && (strcmp(birth.mois,Perso.Naissance.mois)==0) && (birth.annee==Perso.Naissance.annee)){
					found = 1;
					break;
				}
			}while(!feof(fic));
		break;
		
	default : printf(" \t \t \tVotre choix n est pas disponible \n");
			break;
	}
	
	if(found == 1){
				printf("\t \t \t Voici les informations de l auteur que vous cherchez \n");
				printf("\t \t \t Code\tNom\tPrenom\tDate de Naissance \n");
				printf("\t \t \t-------------------------------------------------\n");
				printf("\t \t \t %s\t%s\t%s\t%d %s %d\n",Perso.code,Perso.nom,Perso.prenom,Perso.Naissance.jour,Perso.Naissance.mois,Perso.Naissance.annee);
			}else{
					printf("\t\t\t Auteur introuvable !\n");
				}
	fclose(fic);
}

 // ************  FONCTION POUR SUPRIMER AUTEUR ************

void Supprimer(){
	FILE *fic = fopen("Auteurs.txt","r");
	FILE *tmp = fopen("Tempo.txt","w");
	
	Auteur Perso;int trouve=0;
	char codeEntre[5];
	printf("\t\t\t Entre le code de l'auteur que vous souhaitez supprimer : ");scanf("%s",codeEntre);
	
	do{
		fscanf(fic,"%s %s %s %d %s %d ",&Perso.code,&Perso.nom,&Perso.prenom,&Perso.Naissance.jour,&Perso.Naissance.mois,&Perso.Naissance.annee);
		if(strcmp(codeEntre,Perso.code)==0){
			trouve = 1;
		}
		else{
			fprintf(tmp,"%s\t%s\t%s\t%d\t%s\t%d\n",Perso.code,Perso.nom,Perso.prenom,Perso.Naissance.jour,Perso.Naissance.mois,Perso.Naissance.annee);
		}
	}while(!feof(fic));
	
	if(trouve == 1){
		printf("\t\t\t L auteur a bien ete surprime \n");
	}
	else{
		printf("\t\t\t le code Entre existe pas dans le fichier \n");
	}
	fclose(fic);
	fclose(tmp);
	remove("Auteurs.txt");
	rename("Tempo.txt","Auteurs.txt");
	
}
	
		
		
		
	






