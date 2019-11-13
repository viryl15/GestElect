#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Electeurs.h"
#include "main.h"
#include "Voter.h"

struct Electeur {
	char numCNI[32];
	char nom[50];
	char prenom[50];
	char sexe[1];
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

void goVoter() {
	char choice[4];
	char anwser;

	do
	{
		system("cls");
		printf("\n\t\t<<<<<<<@@@@@@@==== Menu du Vote ====@@@@@@>>>>>>\n\n");
		printf("\t 0- Quitter ou appuyer sur 'q' pour annuler a tout moment\n\n");
		int a = 0;
		a = afficherListeElecteursV();
		do {
			printf("\n\t=> Entrez votre numero d'electeur : ");
			/*scanf("%d", &choice);
			while (getchar() != '\n');*/
			gets(choice);
			if (choice[0] == 'q' || choice[0] == 'Q') {
				main();
			}
		} while (strtol(choice, NULL, 10) < 0 || strtol(choice, NULL, 10) > a);

		if (strtol(choice, NULL, 10) == 0) {
			main();
		}
		if (hasVote(strtol(choice, NULL, 10)) == 1) {
			printf("Vous avez deja voter !!! \n");
		}
		else {
			makeElectorChoice(strtol(choice, NULL, 10));
		}
		printf("\n\tVoulez-vous continuer ? o/n : ");
		scanf("%s", &anwser);//anwser = getch();
		while (getchar() != '\n');
		fflush(stdin);
	} while (anwser == 'o' || anwser == 'O');
	main();
}

//#========> Fonction permettant de verifier si un electeur a deja voter <=========#
int hasVote(int electorChoice) {
	//printf("Votre choix %d \n", electorChoice);
	int val = 0;
	FILE *F;
	F = fopen("Electeur.txt", "r");
	int i = 1;
	do {
		fscanf(F, "%s ;%s ;%s ;%s \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe);
		fflush(stdin);
		if (electorChoice == i) {
			//printf("CNI de Votre choix %s \n", electeur.numCNI);
			FILE *V;
			V = fopen("Vote.txt", "r");
			do {
				fscanf(V, "%s ;%s \n", &vote.electorCniNum, &vote.CandidateCniNum);
				fflush(stdin);
				//printf("vote.electorCniNum : %s \n", vote.electorCniNum);
				if (strcmp(electeur.numCNI, vote.electorCniNum) == 0) {
					val = 1;
					//printf("Gooooooooooooooooood !!!!!!!! \n");
				}
			} while (!feof(V));
			fclose(V);
			break;
		}
		i++;
	} while (!feof(F));
	fclose(F);
	
	return val;
}

//#========> Fonction permettant de verifier si au moins vote a ete fait <=========#
int voteHasBeenApply() {
	FILE *V;
	V = fopen("Vote.txt", "r");
	fseek(V, 0, SEEK_END);
	printf("Positon curseur = %d \n", ftell(V));
	int val = 0;
	if (ftell(V) > 0) {
		val = 1;
	}
	fclose(V);
	return val;
}

//#========> Affichage de la liste des electeurs pour vote <=========#
int afficherListeElecteursV() {
	FILE *F;
	F = fopen("Electeur.txt", "r");
	printf("\tLa liste des electeurs est: \n\n");
	printf("\tNUMERO DE ELECTEUR||\t NOM \t||\t PRENOM \t||\t SEXE\n\n");
	int i = 1;
	do {
		fscanf(F, "%s ;%s ;%s ;%s \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe);
		fflush(stdin);
		printf("\t\t%d\t  ||", i);
		printf("\t%s\t||", electeur.nom);
		printf("\t%s\t\t||", electeur.prenom);
		printf("\t%s\n", electeur.sexe);
		i++;
	} while (!feof(F));
	fclose(F);
	return i - 1;
}

//#========> Choix de electeur <=========#
void makeElectorChoice(int num) {
	FILE *F;
	F = fopen("Electeur.txt", "r");
	/*printf("\tLa liste des electeurs est: \n\n");
	printf("\tNUMERO DE ELECTEUR\t||\t NOM \t||\t PRENOM \t||\t SEXE\n\n");*/
	int i = 1;
	do {
		fscanf(F, "%s ;%s ;%s ;%s \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe);
		fflush(stdin);
		if (num == i) {
			afficherListeCandidatsV(electeur.numCNI);
			break;
		}
		i++;
	} while (!feof(F));
	fclose(F);
}

//#========> Choix du candidat <=========#
void afficherListeCandidatsV(char ElectorCniNum[32]) {
	FILE *F;
	F = fopen("Candidat.txt", "r");
	system("cls");
	printf("\tLa liste des candidat est: \n\n");
	printf("\tNUMERO DU CANDIDAT||\t NOM \t||\t PRENOM \t||\t SEXE\n\n");
	int i = 1;
	do {
		fscanf(F, "%s ;%s ;%s ;%s \n", &candidat.numCNI, &candidat.nom, &candidat.prenom, &candidat.sexe);
		fflush(stdin);
		printf("\t%d\t||\t", i);
		printf("\t%s    ||", candidat.nom);
		printf("  %s    ||", candidat.prenom);
		printf("\t%s\n", candidat.sexe);
		i++;
	} while (!feof(F));
	fclose(F);

	char choice[4];
	do {
		printf("\n\t=> Entrez le numero du candidat choisit ou 0 pour un bulletin nul : ");
		/*scanf("%d", &choice);
		while (getchar() != '\n');*/
		gets(choice);
		if (choice[0] == 'q' || choice[0] == 'Q') {
			goVoter();
			break;
		}
	} while (strtol(choice, NULL, 10) < 0 || strtol(choice, NULL, 10) > i-1);
	makeCandidateChoice(strtol(choice, NULL, 10), ElectorCniNum);
}

void makeCandidateChoice(int candidateNum, char ElectorCniNum[32]) {
	FILE *F, *V;
	char nullCandidate[32];
	strcpy(nullCandidate, "---------");
	F = fopen("Candidat.txt", "r");
	V = fopen("Vote.txt", "a");
	/*printf("\tLa liste des candidat est: \n\n");
	printf("\tNUMERO DU CANDIDAT||\t NOM \t||\t PRENOM \t||\t SEXE\n\n");*/
	if (candidateNum == 0) {
		fprintf(V, "%s ;%s \n", ElectorCniNum, nullCandidate);
		printf("Vous avez voter ***bulletin nul*** \n");
	}
	else {
		int i = 1;
		do {
			fscanf(F, "%s ;%s ;%s ;%s \n", &candidat.numCNI, &candidat.nom, &candidat.prenom, &candidat.sexe);
			fflush(stdin);
			if (candidateNum == i) {
				fprintf(V, "%s ;%s \n", ElectorCniNum, candidat.numCNI);
				printf("Vous avez voter pour *** %s %s *** \n", candidat.nom, candidat.prenom);
				break;
			}
			i++;
		} while (!feof(F));
	}
	fclose(F);
	fclose(V);
}