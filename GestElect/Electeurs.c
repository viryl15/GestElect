#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Statistiques.h"
#include "Electeurs.h"
#include "Voter.h"
#include "main.h"


struct Electeur {
	char numCNI[32];
	char nom[50];
	char prenom[50];
	char sexe[1];
	int vote;
};

struct Electeur electeur;

struct Candidat {
	char numCNI[32];
	char nom[50];
	char prenom[50];
	char sexe[1];
};

struct Candidat candidat;

struct Vote {
	char electorCniNum[32];
	char CandidateCniNum[32];
};

struct Vote vote;

//#==========Launcher procedure============#
void goElecteur() {
	char choice[1];
	char anwser;
	//initElector();
	do
	{
		system("cls");
		printf("\n\t\t<<<<<<<@@@@@@@==== Gestion des electeurs ====@@@@@@>>>>>>\n\n");
		printf("\t 1- Afficher la liste des electeurs\n");
		printf("\t 2- Ajouter un electeur\n");
		printf("\t 3- Modifier les infos d'un electeur\n");
		printf("\t 4- Supprimer un electeur\n");
		printf("\t 5- Quitter ou appuyer sur 'q' pour quitter a tout moment\n\n");

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
			afficherElecteurs();
			break;
		case 2:
			ajouterElecteur();
			break;
		case 3:
			modifierElecteur();
			break;
		case 4:
			supprimerElecteur();
			break;
		case 5:
			main();
			break;
		default:
			break;
		}
		printf("\n\tVoulez-vous continuer ? o/n : ");
		scanf("%s", &anwser);//anwser = getch();
		while (getchar() != '\n');
		fflush(stdin);
	} while (anwser == 'o' || anwser == 'O');
	main();
}

//void initElector() {
//	FILE *F;
//	F = fopen("Electeur.txt", "r");
//	int i = 1;
//	do
//	{
//		fscanf(F, "%s ;%s ;%s ;%s ;%d \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe, &electeur.vote);
//		if (hasVote(i) == 1) {
//			electeur.vote, 1;
//		}
//		else {
//			electeur.vote, 0;
//		}
//		printf("electeur.vote = %d \n", electeur.vote);
//		fflush(stdin);
//		i++;
//		
//	} while (!feof(F));
//	fclose(F);
//	system("pause");
//}

/*==========Fonction de recherche============#
  cette fonction permet de verifier si un numero de CNI donne existe deja dans la base de donnee*/

int checkCni(char cni[32]) {
	FILE *F;
	F = fopen("Electeur.txt", "r");

	do
	{
		fscanf(F, "%s ;%s ;%s ;%s ;%d \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe, &electeur.vote);
		//fflush(stdin);
		if (strcmp(electeur.numCNI, cni) == 0) {
			//printf("electeur.numCNI %s", electeur.numCNI);
			fclose(F);
			return 1;
		}
	} while (!feof(F));
	fclose(F);
	FILE *F2;
	F2 = fopen("Candidat.txt", "r");
	do
	{
		fscanf(F2, "%s ;%s ;%s ;%s \n", &candidat.numCNI, &candidat.nom, &candidat.prenom, &candidat.sexe);
		//fflush(stdin);
		if (strcmp(candidat.numCNI, cni) == 0) {
			//printf("electeur.numCNI %s", electeur.numCNI);
			fclose(F2);
			return 1;
		}
	} while (!feof(F));
	fclose(F2);
	return -1;
}

//==========Procedure d'ajout==========#
void ajouterElecteur() {
	FILE *F;
	//int num;
	F = fopen("Electeur.txt", "a");
	printf("\n Entrez le numero du nouvel electeur : ");
	//scanf("%d", &num);
	char buf[10];
	//scanf("%31[0132456789]", &buf);

	gets(buf);
	if (strlen(buf) == 1 && (buf[0] == 'q' || buf[0] == 'Q')) {
		goElecteur();
	}
	//while (getchar() != '\n');
	//printf("%d", sizeof(num));num < 100000000 || num >= 1000000000 
	fflush(stdin);
	//printf("La taille du num cni est %d", strlen(buf));
	if (strlen(buf) != 9) {
		//printf("Le nombre de chiffre de votre nombre est : %d", nombre_chiffre3(num));
		printf("\n Entrez un numero de CNI a 9 caracteres \n");
		
		//printf("Le nombre de chiffre de votre nombre est : %d", strlen(buf));
		ajouterElecteur();
	}
	else {
		while (checkCni(buf) == 1) {
			printf("\n Desole ce numero de CNI existe deja !!!");
			printf("\nEntrez un numero de CNI pour le nouvel electeur : ");
			//scanf("%d", &num);
			//scanf("%31[0132456789]", &buf);
			gets(buf);
			if (strlen(buf) == 1 && (buf[0] == 'q' || buf[0] == 'Q')) {
				goElecteur();
			}
			//while (getchar() != '\n');
		}

		strcpy(electeur.numCNI, buf);
		// strtol(buf, NULL, 10);
		printf("\n Entrez le nom : ");
		gets(electeur.nom);
		if (strlen(electeur.nom) == 1 && (electeur.nom[0] == 'q' || electeur.nom[0] == 'Q')) {
			goElecteur();
		}
		fflush(stdin);
		printf("\n Entrez le prenom : ");
		gets(electeur.prenom);
		if (strlen(electeur.prenom) == 1 && (electeur.prenom[0] == 'q' || electeur.prenom[0] == 'Q')) {
			goElecteur();
		}
		fflush(stdin);
		char sexe[5];
		char sexe1;
		do
		{
			printf("\n Entrez le sexe 'M/F' : ");
			gets(sexe);
			fflush(stdin);
			if (strlen(sexe) > 1){
				sexe1 = 'D';
				sexe[0] = '\0';
			}
			if (sexe[1] != NULL) {
				sexe1 = 'D';
				sexe[0] = '\0';
			}
			sexe1 = toupper(sexe[0]);
			if (strlen(sexe) == 1 && (sexe[0] == 'q' || sexe[0] == 'Q')) {
				goElecteur();
				break;
			}
		} while (sexe1 != 'M' &&  sexe1 != 'F' );
		sexe[0] = sexe1;
		strcpy(electeur.sexe, sexe);
		fprintf(F, "%s ;%s ;%s ;%s ;%d \n", electeur.numCNI, electeur.nom, electeur.prenom, electeur.sexe, electeur.vote);
		//fflush(stdin);
	}
	fclose(F);
}

void searchAndPrintElector() {
	//int searchNum;
	printf("Entrez le numero de l'electeur rechercher  ou tapez 'q' pour quitter : ");
	//scanf("%d", &searchNum);
	char buf[9];
	gets(buf);
	if (strlen(buf) == 1 && (buf[0] == 'q' || buf[0] == 'Q')) {
		goElecteur();
	}
	FILE *F;
	F = fopen("Electeur.txt", "r");

	do
	{
		fscanf(F, "%s ;%s ;%s ;%s ;%d \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe, &electeur.vote);
		if (strcmp(buf, electeur.numCNI) == 0) {
			printf("===== Informations sur l'electeur =====\n\n");
			printf("Numero de CNI :\t%s \n", electeur.numCNI);
			printf("Nom :\t %s \n", electeur.nom);
			printf("Prenom :\t %s \n", electeur.prenom);
			printf("Sexe :\t %s \n", electeur.sexe);
			printf("Vote :\t %d \n", electeur.vote);
		}
	} while (!feof(F));
	fclose(F);
}

//#=========Procedure de suppression=========#

void supprimerElecteur() {
	char answer;
	//int searchNum;
	printf("Entrez le numero de l'electeur a supprimer ou tapez 'q' pour quitter : ");
	//scanf("%d", &searchNum);
	char buf[32];
	gets(buf);
	if (strlen(buf) == 1 && (buf[0] == 'q' || buf[0] == 'Q')) {
		goElecteur();
	}
	FILE *F;
	F = fopen("Vote.txt", "r");
	int result = 0;
	while (!feof(F)) {
		fscanf(F, "%s ;%s \n", &vote.electorCniNum, &vote.CandidateCniNum);
		//printf("buf = %s; vote.electorCniNum = %s\n", buf, vote.electorCniNum);
		if (strcmp(buf, vote.electorCniNum) == 0) {
			result = 1;
		}
			//fflush(stdin);
	}
	fclose(F);
	//fflush(stdin);
	//printf("result = %d \n", result);
	if (result == 1) {
		printf("\n Impossible de supprimer cet electeur car il a deja voter. \n");
	}
	else {
		if (checkCni(buf) == 1) {
			printf("\n Voulez vous vraiment supprimer o/n ? ");
			scanf("%c", &answer);
			while (getchar() != '\n');
			fflush(stdin);
			if (answer == 'o' || answer == 'O') {
				FILE *tempF, *F;
				F = fopen("Electeur.txt", "r");
				tempF = fopen("TempElecteur.txt", "a");
				do {
					fscanf(F, "%s ;%s ;%s ;%s ;%d \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe, &electeur.vote);
					if (strtol(buf, NULL, 10) != strtol(electeur.numCNI, NULL, 10)) {
						fprintf(tempF, "%s ;%s ;%s ;%s ;%d \n", electeur.numCNI, electeur.nom, electeur.prenom, electeur.sexe, electeur.vote);
					}
				} while (!feof(F));
				fclose(tempF);
				fclose(F);
				remove("Electeur.txt");
				rename("TempElecteur.txt", "Electeur.txt");
				printf("\nSuppression effectuee avec succes\n");
			}

		}
		else {
			printf("\n Ce numero d'electeur n'est pas encore attribue\n");
		}
	}
}

//#==========Procedure de modification d'un electeur============#

void modifierElecteur() {
	//int searchNum;
	char answer1[2];
	printf("\n Entrez le numero de CNI de l'electeur a modifier : ");
	//scanf("%d", &searchNum);
	char buf[10];
	gets(buf);
	if (strlen(buf) == 1 && (buf[0] == 'q' || buf[0] == 'Q')) {
		goElecteur();
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
			F = fopen("Electeur.txt", "r");
			tempF = fopen("TempElecteur.txt", "a");
			do {
				fscanf(F, "%s ;%s ;%s ;%s ;%d \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe, &electeur.vote);
				if (strcmp(buf, electeur.numCNI) == 0) {
					strcpy(electeur.numCNI, buf);
					printf("\n Entrez le nom :");
					gets(electeur.nom);
					if (strlen(electeur.nom) == 1 && (electeur.nom[0] == 'q' || electeur.nom[0] == 'Q')) {
						goElecteur();
					}
					printf("\n Entrez le prenom :");
					gets(electeur.prenom);
					if (strlen(electeur.prenom) == 1 && (electeur.prenom[0] == 'q' || electeur.prenom[0] == 'Q')) {
						goElecteur();
					}
					char sexe[5];
					char sexe1;
					do
					{
						printf("\n Entrez le sexe 'M/F'  : ");
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
							goElecteur();
							break;
						}
						/*if (strlen(sexe) == 1 && (sexe[0] == 'm' || sexe[0] == 'M' || sexe[0] == 'f' | sexe[0] == 'F')) {
							break;
						}*/
					} while (sexe1 != 'M' &&  sexe1 != 'F');
					sexe[0] = sexe1;
					strcpy(electeur.sexe, sexe);
					fflush(stdin);
					if (hasVote(nbrDelecteurs() + 1) == 1) {
						electeur.vote, 1;
					}
					else {
						electeur.vote, 0;
					}
				}
				fprintf(tempF, "%s ;%s ;%s ;%s ;%d \n", electeur.numCNI, electeur.nom, electeur.prenom, electeur.sexe, electeur.vote);
			} while (!feof(F));
			fflush(stdin);
			fclose(tempF);
			fclose(F);
			remove("Electeur.txt");
			rename("TempElecteur.txt", "Electeur.txt");
			printf("\n Modification reussie !\n");
		}
		else {
			printf("\n Echec de la Modification !\n");
		}
	}
	else {
		printf("\n Ce numero d'electeur n'est pas encore attribue");
	}

}

//#==========Procedure d'affichage==========#

void afficherElecteurs() {
	FILE *F;
	F = fopen("Electeur.txt", "r");
	printf("\n\tLISTE DES ELECTEURS \n\n");
	printf("\t===================> \n\n");
	printf("\t ___________________________________________________________________________________________________________\n");
	printf("\t|NUMERO DE CNI\t||\t NOM \t||\t PRENOM \t||\t SEXE \t||\t VOTE \t\t\t    |\n");
	printf("\t|_______________||______________||______________________||______________||__________________________________|\n");
	do {
		fscanf(F, "%s ;%s ;%s ;%s ;%d \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe, &electeur.vote);
		fflush(stdin);
		printf("\t|%s\t||", electeur.numCNI);
		if (strlen(electeur.nom) > 7) {
			printf("%s||", electeur.nom);
		}
		else {
			printf("\t%s\t||", electeur.nom);
		}
		if (strlen(electeur.prenom) > 7) {
			printf("   %s   ||\t", electeur.prenom);
		}
		else {
			printf("\t%s\t\t||\t", electeur.prenom);
		}
		printf("%s\t||\t", electeur.sexe);
		printf("%d\t\t\t    |\n", electeur.vote);
		printf("\t|___________________________________________________________________________________________________________|\n");
	} while (!feof(F));
	fclose(F);
}