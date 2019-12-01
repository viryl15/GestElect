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
		fscanf(F, "%s ;%s ;%s ;%s ;%d \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe, &electeur.vote);
		fflush(stdin);
		if (electorChoice == i) {
			//printf("CNI de Votre choix %s \n", electeur.numCNI);
			FILE *V;
			V = fopen("Vote.txt", "r");
			do {
				fscanf(V, "%s ;%s \n", &vote.electorCniNum, &vote.CandidateCniNum);
				fflush(stdin);
				//verifier si le numero de CNI de l'electeur en question est dans la liste des votes deja effectuer
				if (strcmp(electeur.numCNI, vote.electorCniNum) == 0) {
					//l'electeur en question a deja voter
					val = 1;
					break;
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

//#========> Fonction permettant de verifier si au moins 1 vote a ete fait <=========#
int voteHasBeenApply() {
	FILE *V;
	V = fopen("Vote.txt", "r");
	//positionnement a la fin du fichier
	fseek(V, 0, SEEK_END);
	//printf("Positon curseur = %d \n", ftell(V));
	int val = 0;
	//recuperation de la position du curseur dans le fichier avec ftell(V)
	if (ftell(V) > 0) {
		val = 1;
	}
	fclose(V);
	return val;
}

//#========> Affichage de la liste des electeurs pour vote <=========#
int afficherListeElecteursV() {
	modifierElecteurApresElection();
	FILE *F;
	F = fopen("Electeur.txt", "r");
	printf("\tLISTE DES ELECTEURS \n");
	printf("\t===================> \n\n");
	printf("\t ___________________________________________________________________________________________________________\n");
	printf("\t|NUMERO    ELECTEUR||\t NOM \t||\t PRENOM \t||\t SEXE \t||\t VOTE \t\t\t    |\n");
	printf("\t|__________________||___________||______________________||______________||__________________________________|\n");
	int i = 1;
	do {
		fscanf(F, "%s ;%s ;%s ;%s ;%d \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe, &electeur.vote);
		fflush(stdin);
		printf("\t|\t%d\t   ||", i);
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
		/*printf("\t%s\t||", electeur.nom);
		printf("\t%s\t\t||", electeur.prenom);*/
		printf("%s\t||\t", electeur.sexe);
		printf("%d\t\t\t    |\n", electeur.vote);
		printf("\t|___________________________________________________________________________________________________________|\n");
		i++;
	} while (!feof(F));
	fclose(F);
	
	return i - 1;
}

//#========> Choix de electeur <=========#
void makeElectorChoice(int num) {
	FILE *F;
	F = fopen("Electeur.txt", "r");
	int i = 1;
	do {
		fscanf(F, "%s ;%s ;%s ;%s ;%d \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe, &electeur.vote);
		fflush(stdin);
		if (num == i) {
			//fclose(F);
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
	printf("\n\tLISTE DES CANDIDATS \n");
	printf("\t===================> \n\n");
	printf("\t ___________________________________________________________________________________________\n");
	printf("\t|NUMERO DU CANDIDAT||\t NOM \t||\t PRENOM \t||\t SEXE \t\t\t    |\n");
	printf("\t|__________________||___________||______________________||__________________________________|\n");
	int i = 1;
	do {
		fscanf(F, "%s ;%s ;%s ;%s \n", &candidat.numCNI, &candidat.nom, &candidat.prenom, &candidat.sexe);
		fflush(stdin);
		printf("\t|%d\t\t   ||", i);
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
				//modifierElecteurApresElection();
				break;
			}
			i++;
		} while (!feof(F));
	}
	fclose(F);
	fclose(V);
	
}

int nbrVote() {
	FILE *F;
	F = fopen("Vote.txt", "r");
	int nbrDeVote = 0;
	while (!feof(F)) {
		fscanf(F, "%s ;%s \n", &vote.electorCniNum, &vote.CandidateCniNum);
		fflush(stdin);
		nbrDeVote++;
	}
	fclose(F);
	return nbrDeVote;
}

void modifierElecteurApresElection() {
	int g = 1;
	FILE *file;
	file = fopen("Vote.txt", "r");
	printf("Debut !!!!!!!!!!!\n");
	system("pause");
	while (g <= nbrVote()) {
		fscanf(file, "%s ;%s \n", &vote.electorCniNum, &vote.CandidateCniNum);
		char ElectorCniNum[32];
		
		if (g == nbrVote()) {
			strcpy(ElectorCniNum, vote.electorCniNum);
			printf("nbrVote() = %d\n", nbrVote());
			printf("ElectorCniNum = %s\n", ElectorCniNum);
			system("pause");
			FILE *tempF, *F;
			F = fopen("Electeur.txt", "r");
			tempF = fopen("TempElecteur.txt", "w");
			do {
				fscanf(F, "%s ;%s ;%s ;%s ;%d \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe, &electeur.vote);
				if (strcmp(ElectorCniNum, electeur.numCNI) == 0) {
					strcpy(electeur.numCNI, ElectorCniNum);
					strcpy(electeur.nom, electeur.nom);
					strcpy(electeur.prenom, electeur.prenom);
					strcpy(electeur.sexe, electeur.sexe);
					electeur.vote = 1;
					
					//fflush(stdin);
				}
				//printf("ElectorCniNum = %s electeur.numCNI = %s\n", ElectorCniNum, electeur.numCNI);
				//printf("electeur.vote = %d\n", electeur.vote);
				fprintf(tempF, "%s ;%s ;%s ;%s ;%d \n", electeur.numCNI, electeur.nom, electeur.prenom, electeur.sexe, electeur.vote);
			} while (!feof(F));
			//fflush(stdin);
			fclose(tempF);
			fclose(F);
			fclose(F);
			fclose(F);
			fclose(F);
			/*FILE *K;
			K = fopen("Test.txt", "w");
			
			printf("REMOVE = %d\n", fclose(F));
			fclose(K);
			remove("Electeur.txt");*/
			remove("Electeur.txt");
			system("pause");
			rename("TempElecteur.txt", "Electeur.txt");
			//printf("\n Modification reussie !\n");
		}
		g++;
	}
	fclose(file);

}