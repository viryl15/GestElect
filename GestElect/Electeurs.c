#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Electeurs.h"
#include "main.h"


struct Electeur {
	char numCNI[32];
	char nom[50];
	char prenom[50];
	char sexe[1];
};

struct Electeur electeur;

//#==========Launcher procedure============#
void goElecteur() {
	char choice[1];
	char anwser;

	do
	{
		system("cls");
		printf("\n\t\t<<<<<<<@@@@@@@==== Gestionn des electeurs ====@@@@@@>>>>>>\n\n");
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

/*==========Fonction de recherche============#
  cette fonction permet de verifier si un numero de CNI donne existe deja dans la base de donnee*/
int searchCniElecteur(char searchCNI[10]) {
	FILE *F;
	F = fopen("Electeur.txt", "r");
	do
	{
		fscanf(F, "%s ;%s ;%s ;%s \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe);
		fflush(stdin);
		
		if (strcmp(electeur.numCNI, searchCNI) == 0)
		{
			printf("electeur.numCNI %s", electeur.numCNI);
			fclose(F);
			return 1;
		}
	} while (!feof(F));
	fclose(F);
	return -1;
}

//==========Procedure d'ajout==========#
void ajouterElecteur() {
	FILE *F;
	//int num;
	F = fopen("Electeur.txt", "a");
	printf("\n Entrez le numero du nouveau electeur ou tapez 'q' pour quitter : ");
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
	printf("La taille du num cni est %d", strlen(buf));
	if (strlen(buf) != 9) {
		//printf("Le nombre de chiffre de votre nombre est : %d", nombre_chiffre3(num));
		printf("\n Entrez un numero a 9 chiffres ");
		
		//printf("Le nombre de chiffre de votre nombre est : %d", strlen(buf));
		ajouterElecteur();
	}
	else {
		while (searchCniElecteur(buf) == 1) {
			printf("\n Ce numero existe deja :");
			printf("\nEntrez un numero pour le nouveau electeur ou tapez 'q' pour quitter : ");
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
		printf("\n Entrez le nom ou tapez 'q' pour quitter : ");
		gets(electeur.nom);
		if (strlen(electeur.nom) == 1 && (electeur.nom[0] == 'q' || electeur.nom[0] == 'Q')) {
			goElecteur();
		}
		fflush(stdin);
		printf("\n Entrez le prenom ou tapez 'q' pour quitter : ");
		gets(electeur.prenom);
		if (strlen(electeur.nom) == 1 && (electeur.nom[0] == 'q' || electeur.nom[0] == 'Q')) {
			goElecteur();
		}
		fflush(stdin);
		char sexe[5];
		char sexe1;
		do
		{
			printf("\n Entrez le sexe 'M/F'  ou tapez 'q' pour quitter : ");
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
				//break;
				goElecteur();
				break;
			}
			/*if (strlen(sexe) == 1 && (sexe[0] == 'm' || sexe[0] == 'M' || sexe[0] == 'f' | sexe[0] == 'F')) {
				break;
			}*/
		} while (sexe1 != 'M' &&  sexe1 != 'F' );
		strcpy(electeur.sexe, sexe);
		fflush(stdin);
		fprintf(F, "%s ;%s ;%s ;%s \n", electeur.numCNI, electeur.nom, electeur.prenom, electeur.sexe);
		fclose(F);
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
		fscanf(F, "%s ;%s ;%s ;%s \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe);
		if (strcmp(buf, electeur.numCNI) == 0) {
			printf("===== Informations sur l'electeur =====\n\n");
			printf("Numero de CNI :\t%s \n", electeur.numCNI);
			printf("Nom :\t %s \n", electeur.nom);
			printf("Prenom :\t %s \n", electeur.prenom);
			printf("Sexe :\t %s \n", electeur.sexe);
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
	char buf[9];
	gets(buf);
	if (strlen(buf) == 1 && (buf[0] == 'q' || buf[0] == 'Q')) {
		goElecteur();
	}
	fflush(stdin);
	if (searchCniElecteur(buf) == 1) {
		printf("\n Voulez vous vraiment supprimer o/n ? ");
		scanf("%c", &answer);
		while (getchar() != '\n');
		fflush(stdin);
		if (answer == 'o' || answer == 'O') {
			FILE *tempF, *F;
			F = fopen("Electeur.txt", "r");
			tempF = fopen("TempElecteur.txt", "a");
			do {
				fscanf(F, "%s ;%s ;%s ;%s \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe);
				if (strtol(buf, NULL, 10) != strtol(electeur.numCNI, NULL, 10)) {
					fprintf(tempF, "%s ;%s ;%s ;%s \n", electeur.numCNI, electeur.nom, electeur.prenom, electeur.sexe);
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

//#==========Procedure de modification d'un electeur============#

void modifierElecteur() {
	//int searchNum;
	char answer1[2];
	printf("\n Entrez le numero de CNI de l'electeur a modifier ou tapez 'q' pour quitter : ");
	//scanf("%d", &searchNum);
	char buf[10];
	gets(buf);
	if (strlen(buf) == 1 && (buf[0] == 'q' || buf[0] == 'Q')) {
		goElecteur();
	}
	fflush(stdin);
	if (searchCniElecteur(buf) == 1) {
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
				fscanf(F, "%s ;%s ;%s ;%s \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe);
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
						printf("\n Entrez le sexe 'M/F'  ou tapez 'q' pour quitter : ");
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
					strcpy(electeur.sexe, sexe);
					fflush(stdin);
				}
				fprintf(tempF, "%s ;%s ;%s ;%s \n", electeur.numCNI, electeur.nom, electeur.prenom, electeur.sexe);
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
	printf("\tLa liste des electeurs est: \n\n");
	printf("\tNUMERO DE CNI\t||\t NOM \t||\t PRENOM \t||\t SEXE\n\n");
	do {
		fscanf(F, "%s ;%s ;%s ;%s \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe);
		fflush(stdin);
		printf("\t%s\t||\t", electeur.numCNI);
		printf("\t%s\t\t||\t", electeur.nom);
		printf("\t%s\t\t||\t", electeur.prenom);
		printf("\t%s\n", electeur.sexe);
	} while (!feof(F));
	fclose(F);
}