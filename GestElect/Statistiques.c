#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "Voter.h"
#include "Statistiques.h"

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

void goStatistiques() {
	char choice[4];
	system("cls");
	printf("\n\t\t<<<<<<<@@@@@@@==== Les Statistiques ====@@@@@@>>>>>>\n\n");

	int nbrVote = 0;
	FILE *V;
	V = fopen("Vote.txt", "r");
	int nbrVoteCandidat = 0;
	while (!feof(V)) {
		fscanf(V, "%s ;%s \n", &vote.electorCniNum, &vote.CandidateCniNum);
		fflush(stdin);
		nbrVote++;
	}
	printf("\t\tLe nombre total de vote est : %d \n\n", nbrVote);
	fclose(V);

	int val = 0;
	FILE *F;
	F = fopen("Candidat.txt", "r");
	int nbrBulNul = 0;
	while (!feof(F)) {
		fscanf(F, "%s ;%s ;%s ;%s \n", &candidat.numCNI, &candidat.nom, &candidat.prenom, &candidat.sexe);
		fflush(stdin);
		FILE *V;
		V = fopen("Vote.txt", "r");
		int nbrVoteCandidat = 0;
		nbrBulNul = 0;
		while (!feof(V)){
			fscanf(V, "%s ;%s \n", &vote.electorCniNum, &vote.CandidateCniNum);
			fflush(stdin);
			//printf("vote.electorCniNum : %s \n", vote.electorCniNum);
			if (strcmp(candidat.numCNI, vote.CandidateCniNum) == 0) {
				nbrVoteCandidat++;
			}
			if (strcmp(vote.CandidateCniNum, "---------") == 0) {
				nbrBulNul++;
			}
		}
		//====>>>> Met tous les noms en majuscule
		for (int i = 0; candidat.nom[i] != '\0'; i++) {
			// si les caractères sont en minuscules, converti-les en majuscules 
			// en soustrayant 32 de leur valeur ASCII.
			if (candidat.nom[i] >= 'a' && candidat.nom[i] <= 'z') {
				candidat.nom[i] = candidat.nom[i] - 32;
			}
		}
		for (int i = 0; candidat.prenom[i] != '\0'; i++) {
			// si les caractères sont en minuscules, converti-les en majuscules 
			// en soustrayant 32 de leur valeur ASCII.
			if (candidat.prenom[i] >= 'a' && candidat.prenom[i] <= 'z') {
				candidat.prenom[i] = candidat.prenom[i] - 32;
			}
		}

		//=====>>>>>>> Affichage des statistiques de chaque Candidat¯\_(ツ)_/¯
		printf("\n\t\t<<<<<<<######==== Candidat %s %s ====######>>>>>>\n\n", candidat.nom, candidat.prenom);
		printf("\t\tNombre de vote : %d \n\n", nbrVoteCandidat);
		printf("\t\tPourcentage de reussite : %.2f%% \n\n", ((double)nbrVoteCandidat/ (double)nbrVote)*100);
		printf("\t\t<<<<<<<<<<<<=================================>>>>>>>>>>>>\n\n");
		fclose(V);
	}
	fclose(F);

	printf("\n\t\t<<<<<<<######==== Bulletins nuls ====######>>>>>>\n\n");
	printf("\t\tNombre de bulletins nuls : %d \n\n", nbrBulNul);
	printf("\t\t<<<<<<<<<<<<================================>>>>>>>>>>>>\n\n");

	do {
		printf("\n\t=> Tapez q pour quitter : ");
		gets(choice);
		
		if (choice[0] == 'q' || choice[0] == 'Q') {
			if (strlen(choice)>1) {
				choice[0] = '\0';
			}
			else {
				main();
			}
		}
	} while (toupper(choice[0]) != 'Q');
}