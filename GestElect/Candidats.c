#include <stdio.h>
#include <stdlib.h>

#include "Voter.h"
#include "Candidats.h"
#include "Electeurs.h"
#include "main.h"


struct Candidat {
	char numCNI[32];
	char nom[50];
	char prenom[50];
	char sexe[1];
};

struct Candidat candidat;

struct Electeur {
	char numCNI[32];
	char nom[50];
	char prenom[50];
	char sexe[1];
	int vote;
};

struct Electeur electeur;

//#==========Launcher procedure============#
void goCandidat() {
	char choice[1];
	char anwser;

	do
	{
		system("cls");
		printf("\n\t\t<<<<<<<@@@@@@@==== Gestion des candidats ====@@@@@@>>>>>>\n\n");
		printf("\t 1- Afficher la liste des candidats\n");
		printf("\t 2- Ajouter un candidat\n");
		printf("\t 3- Modifier les infos d'un candidat\n");
		printf("\t 4- Quitter ou appuyer sur 'q' pour quitter a tout moment\n\n");

		do {
			printf("\n\t=> Entrez votre choix : ");
			/*scanf("%d", &choice);
			while (getchar() != '\n');*/
			gets(choice);
			if (choice[0] == 'q' || choice[0] == 'Q') {
				main();
			}
		} while (strtol(choice, NULL, 10) < 1 || strtol(choice, NULL, 10) > 5);

		switch (strtol(choice, NULL, 10)) {
		case 1:
			afficherCandidats();
			break;
		case 2:
			ajouterCandidat();
			break;
		case 3:
			modifierCandidat();
			break;
		case 4:
			main();
			break;
		default:
			break;
		}
		printf("\n\tVoulez-vous continuer ? o/n : ");
		scanf("%c", &anwser);//anwser = getch();
		while (getchar() != '\n');
		fflush(stdin);
	} while (anwser == 'o' || anwser == 'O');
	main();
}

/*#==========Fonction de recherche============#
	cette fonction permet de verifier si un numero de CNI du candidat donne existe deja dans la base de donnee*/

//==========Procedure d'ajout==========#
void ajouterCandidat() {
	if (voteHasBeenApply()) {
		printf("\n\tLa liste definitive des Candidats a deja ete retenue [-> \n");
	}
	else
	{
		FILE *F;
		//int num;
		F = fopen("Candidat.txt", "a");
		printf("\n Entrez le numero du nouveau candidat : ");
		//scanf("%d", &num);
		char buf[32];
		//scanf("%31[0132456789]", &buf);

		gets(buf);
		if (strlen(buf) == 1 && (buf[0] == 'q' || buf[0] == 'Q')) {
			fclose(F);
			goCandidat();
		}
		//while (getchar() != '\n');
		//printf("%d", sizeof(num));num < 100000000 || num >= 1000000000 
		fflush(stdin);
		//printf("La taille du num cni est %d", strlen(buf));
		if (strlen(buf) != 9) {
			//printf("Le nombre de chiffre de votre nombre est : %d", nombre_chiffre3(num));
			printf("\n Entrez un numero de CNI a 9 caracteres \n");

			//printf("Le nombre de chiffre de votre nombre est : %d", strlen(buf));
			fclose(F);
			ajouterCandidat();
		}
		else {
			while (checkCni(buf) == 1) {
				//printf("Debut 2 !!!!\n");
				printf("\n Desole ce numero de CNI existe deja !!!");
				printf("\nEntrez un numero de CNI pour le nouveau candidat : ");
				//scanf("%d", &num);
				//scanf("%31[0132456789]", &buf);
				gets(buf);
				if (strlen(buf) == 1 && (buf[0] == 'q' || buf[0] == 'Q')) {
					goCandidat();
				}
				//while (getchar() != '\n');
			}
			strcpy(candidat.numCNI, buf);
			// strtol(buf, NULL, 10);
			printf("\n Entrez le nom : ");
			gets(candidat.nom);
			if (strlen(candidat.nom) == 1 && (candidat.nom[0] == 'q' || candidat.nom[0] == 'Q')) {
				goCandidat();
			}
			fflush(stdin);
			printf("\n Entrez le prenom : ");
			gets(candidat.prenom);
			if (strlen(candidat.nom) == 1 && (candidat.nom[0] == 'q' || candidat.nom[0] == 'Q')) {
				goCandidat();
			}
			fflush(stdin);
			char sexe[5];
			char sexe1;
			do
			{
				printf("\n Entrez le sexe 'M/F' : ");
				gets(sexe);
				fflush(stdin);
				if (strlen(sexe) > 1) {
					sexe1 = 'D';
					sexe[0] = '\0';
				}
				if (sexe[1] != NULL) {
					sexe1 = 'D';
					sexe[0] = '\0';
				}
				sexe1 = toupper(sexe[0]);
				if (strlen(sexe) == 1 && (sexe[0] == 'q' || sexe[0] == 'Q')) {
					//break;
					goCandidat();
					break;
				}
				/*if (strlen(sexe) == 1 && (sexe[0] == 'm' || sexe[0] == 'M' || sexe[0] == 'f' | sexe[0] == 'F')) {
					break;
				}*/
			} while (sexe1 != 'M' &&  sexe1 != 'F');
			sexe[0] = sexe1;
			strcpy(candidat.sexe, sexe);
			fflush(stdin);
			fprintf(F, "%s ;%s ;%s ;%s \n", candidat.numCNI, candidat.nom, candidat.prenom, candidat.sexe);
			FILE *F2;
			//int num;
			F2 = fopen("Electeur.txt", "a");
			fprintf(F2, "%s ;%s ;%s ;%s ;%d \n", candidat.numCNI, candidat.nom, candidat.prenom, candidat.sexe,0);
			fclose(F2);
			fclose(F);
		}
		fclose(F);
	}
}

void searchAndPrintCandidat() {
	//int searchNum;
	printf("Entrez le numero de l'candidat rechercher  ou tapez 'q' pour quitter : ");
	//scanf("%d", &searchNum);
	char buf[32];
	gets(buf);
	if (strlen(buf) == 1 && (buf[0] == 'q' || buf[0] == 'Q')) {
		goCandidat();
	}
	FILE *F;
	F = fopen("Candidat.txt", "r");

	do
	{
		fscanf(F, "%s ;%s ;%s ;%s \n", &candidat.numCNI, &candidat.nom, &candidat.prenom, &candidat.sexe);
		if (strcmp(buf, candidat.numCNI) == 0) {
			printf("===== Informations sur l'electeur =====\n\n");
			printf("Numero de CNI :\t%s \n", candidat.numCNI);
			printf("Nom :\t %s \n", candidat.nom);
			printf("Prenom :\t %s \n", candidat.prenom);
			printf("Sexe :\t %s \n", candidat.sexe);
		}
	} while (!feof(F));
	fclose(F);
}

//#==========Procedure de modification d'un candidat============#

void modifierCandidat() {
	//int searchNum;
	char answer1[2];
	printf("\n Entrez le numero de CNI du candidat a modifier : ");
	//scanf("%d", &searchNum);
	char buf[32];
	gets(buf);
	if (strlen(buf) == 1 && (buf[0] == 'q' || buf[0] == 'Q')) {
		goCandidat();
	}
	fflush(stdin);
	if (checkCni(buf) == 1) {
		printf("\n Voulez vous vraiment modifier ? o/n : ");
		//scanf("%s", &answer1);
		gets(answer1);
		//while (getchar() != '\n');
		fflush(stdin);
		//printf("%s", answer);
		if (answer1[0] == 'o' || answer1[0] == 'O') {
			FILE *tempF, *F;
			F = fopen("Candidat.txt", "r");
			tempF = fopen("TempCandidat.txt", "a");
			do {
				fscanf(F, "%s ;%s ;%s ;%s \n", &candidat.numCNI, &candidat.nom, &candidat.prenom, &candidat.sexe);
				if (strcmp(buf, candidat.numCNI) == 0) {
					strcpy(candidat.numCNI, buf);
					printf("\n Entrez le nom :");
					gets(candidat.nom);
					if (strlen(candidat.nom) == 1 && (candidat.nom[0] == 'q' || candidat.nom[0] == 'Q')) {
						goCandidat();
					}
					printf("\n Entrez le prenom :");
					gets(candidat.prenom);
					if (strlen(candidat.prenom) == 1 && (candidat.prenom[0] == 'q' || candidat.prenom[0] == 'Q')) {
						goCandidat();
					}
					char sexe[5];
					char sexe1;
					do
					{
						printf("\n Entrez le sexe 'M/F' : ");
						gets(sexe);
						fflush(stdin);
						if (strlen(sexe) > 1) {
							sexe1 = 'D';
							sexe[0] = '\0';
						}
						if (sexe[1] != NULL) {
							sexe1 = 'D';
							sexe[0] = '\0';
						}
						sexe1 = toupper(sexe[0]);
						if (strlen(sexe) == 1 && (sexe[0] == 'q' || sexe[0] == 'Q')) {
							//break;
							goCandidat();
							break;
						}
						/*if (strlen(sexe) == 1 && (sexe[0] == 'm' || sexe[0] == 'M' || sexe[0] == 'f' | sexe[0] == 'F')) {
							break;
						}*/
					} while (sexe1 != 'M' &&  sexe1 != 'F');
					sexe[0] = sexe1;
					strcpy(candidat.sexe, sexe);
					fflush(stdin);
				}
				fprintf(tempF, "%s ;%s ;%s ;%s \n", candidat.numCNI, candidat.nom, candidat.prenom, candidat.sexe);
			} while (!feof(F));
			fflush(stdin);
			fclose(tempF);
			fclose(F);
			remove("Candidat.txt");
			rename("TempCandidat.txt", "Candidat.txt");
			printf("\n Modification reussie !\n");
		}
		else {
			printf("\n Echec de la Modification !\n");
		}
	}
	else {
		printf("\n Ce numero de candidat n'est pas encore attribue");
	}
}

//#==========Procedure d'affichage de la liste des candidats==========#

void afficherCandidats() {
	FILE *F;
	F = fopen("Candidat.txt", "r");
	printf("\n\tLISTE DES CANDIDATS \n");
	printf("\t===================> \n\n");
	printf("\t ___________________________________________________________________________________________\n");
	printf("\t|NUMERO DE CNI\t||\t NOM \t||\t PRENOM \t||\t SEXE \t\t\t    |\n");
	printf("\t|_______________||______________||______________________||__________________________________|\n");
	do {
		fscanf(F, "%s ;%s ;%s ;%s \n", &candidat.numCNI, &candidat.nom, &candidat.prenom, &candidat.sexe);
		fflush(stdin);
		printf("\t|%s\t||", candidat.numCNI);
		if (strlen(candidat.nom) > 7) {
			printf("%s||", candidat.nom);
		}
		else {
			printf("\t%s\t||", candidat.nom);
		}
		if (strlen(candidat.prenom) > 7) {
			printf("   %s   ||\t", candidat.prenom);
		}
		else {
			printf("\t%s\t\t||\t", candidat.prenom);
		}
		printf("\t%s\t\t    |\n", candidat.sexe);
		printf("\t|___________________________________________________________________________________________|\n");
	} while (!feof(F));
	fclose(F);
}