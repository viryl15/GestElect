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

struct Electeur {
	char numCNI[32];
	char nom[50];
	char prenom[50];
	char sexe[1];
	int vote;
};
struct Electeur electeur;

struct Vote {
	char electorCniNum[32];
	char CandidateCniNum[32];
};

struct Vote vote;

void goStatistiques() {
	char choice[4];
	system("cls");
	printf("\n\t\t<<<<<<<<<<<<<<<<<@@@@@@@===== LES STATISTIQUES =====@@@@@@>>>>>>>>>>>>>>>>\n\n");
	
	int nbrVote = 0;
	FILE *V;
	V = fopen("Vote.txt", "r");
	//int nbrVoteCandidat = 0;
	while (!feof(V)) {
		fscanf(V, "%s ;%s \n", &vote.electorCniNum, &vote.CandidateCniNum);
		fflush(stdin);
		nbrVote++;
	}
	fclose(V);
	printf("\t\t\t<<<<<<<<<<<<@@@@@@@==============================@@@@@@>>>>>>>>>>>\n");
	printf("\t\t\t#                                                                #\n");
	printf("\t\t\t#                                                                #\n");
	printf("\t\t\t#                                                                #\n");
	printf("\t\t\t# Le nombre total d'electeurs incrit est : %d \n", nbrDelecteurs());
	printf("\t\t\t#                                                                #\n");
	printf("\t\t\t# Le nombre total d'electeurs ayant voter est : %d \n", nbrVote);
	printf("\t\t\t#                                                                #\n");
	printf("\t\t\t# Le taux de participation est de %.2f%% \n", ((double)nbrVote / (double)nbrDelecteurs()) * 100);
	printf("\t\t\t#                                                                #\n");
	printf("\t\t\t#                                                                #\n");
	printf("\t\t\t<<<<<<<<<<<<@@@@@@@==============================@@@@@@>>>>>>>>>>>\n\n");
	printf("\n\t\t<<<<<<<<<<<<@@@@@@@===== Resultats de chaque candidat =====@@@@@@>>>>>>>>>>>\n\n");
	int val = 0;
	FILE *F;
	F = fopen("Candidat.txt", "r");
	int nbrBulNul = 0;
	int i = 0;
	while (!feof(F)) {
		fscanf(F, "%s ;%s ;%s ;%s \n", &candidat.numCNI, &candidat.nom, &candidat.prenom, &candidat.sexe);
		fflush(stdin);
		FILE *V;
		V = fopen("Vote.txt", "r");
		int nbrVoteCandidat = 0;
		nbrBulNul = 0;
		while (!feof(V)) {
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
		if (strlen(candidat.nom)+strlen(candidat.prenom) > 12) {
			printf("\n\t\t\t<<<<<<<######====== Candidat %s %s ======######>>>>>>\n", candidat.nom, candidat.prenom);
			printf("\t\t\t#                                                  \t\t#\n");
			printf("\t\t\t#                                                  \t\t#\n");
			printf("\t\t\t#                                                  \t\t#\n");
			printf("\t\t\t# Nombre de vote : %d \n", nbrVoteCandidat);
			printf("\t\t\t#                                                  \t\t#\n");
			printf("\t\t\t#                                                  \t\t#\n");
			printf("\t\t\t# Pourcentage de reussite : %.2f%% \n", ((double)nbrVoteCandidat / (double)nbrVote) * 100);
			printf("\t\t\t#                                                  \t\t#\n");
			printf("\t\t\t#                                                  \t\t#\n");
			printf("\t\t\t#                                                  \t\t#\n");
			printf("\t\t\t<<<<<<<<<<<<<======================================>>>>>>>>>>>>>\n\n");
		}
		else {
			printf("\n\t\t\t<<<<<<<###==== Candidat %s %s ====###>>>>>>\n", candidat.nom, candidat.prenom);
			printf("\t\t\t#                                                 #\n");
			printf("\t\t\t#                                                 #\n");
			printf("\t\t\t#                                                 #\n");
			printf("\t\t\t# Nombre de vote : %d \n", nbrVoteCandidat);
			printf("\t\t\t#                                                 #\n");
			printf("\t\t\t#                                                 #\n");
			printf("\t\t\t# Pourcentage de reussite : %.2f%% \n", ((double)nbrVoteCandidat / (double)nbrVote) * 100);
			printf("\t\t\t#                                                 #\n");
			printf("\t\t\t#                                                 #\n");
			printf("\t\t\t#                                                 #\n");
			printf("\t\t\t<<<<<<<<<=================================>>>>>>>>>\n\n");
		}
		
		i++;

		fclose(V);
	}
	fclose(F);

	printf("\n\t\t\t<<<<<<<######==== Bulletins nuls ====######>>>>>>\n");
	printf("\t\t\t#                                               #\n");
	printf("\t\t\t#                                               #\n");
	printf("\t\t\t# Nombre de bulletins nuls : %d \n", nbrBulNul);
	printf("\t\t\t#                                               #\n");
	printf("\t\t\t#                                               #\n");
	printf("\t\t\t<<<<<<<<<================================>>>>>>>>\n\n");

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

int nbrDelecteurs() {
	FILE *F;
	F = fopen("Electeur.txt", "r");
	int nbrElecteur = 0;
	while (!feof(F)) {
		fscanf(F, "%s ;%s ;%s ;%s ;%d \n", &electeur.numCNI, &electeur.nom, &electeur.prenom, &electeur.sexe, &electeur.vote);
		fflush(stdin);
		nbrElecteur++;
	}
	fclose(F);
	return nbrElecteur;
}

//int nombreDeVote() {
//	int nbrVote = 0;
//	FILE *V;
//	V = fopen("Vote.txt", "r");
//	int nbrVoteCandidat = 0;
//	while (!feof(V)) {
//		fscanf(V, "%s ;%s \n", &vote.electorCniNum, &vote.CandidateCniNum);
//		fflush(stdin);
//		nbrVote++;
//	}
//	fclose(V);
//	return nbrVote;
//}
//
//int nbrCandidats() {
//	FILE *F;
//	F = fopen("Candidat.txt", "r");
//	int nbrCandidat = 0;
//	while (!feof(F)) {
//		fscanf(F, "%s ;%s ;%s ;%s \n", &candidat.numCNI, &candidat.nom, &candidat.prenom, &candidat.sexe);
//		fflush(stdin);
//		nbrCandidat++;
//	}
//	fclose(F);
//	return nbrCandidat;
//}
//
//void printCandidateWhitNum(int num) {
//	FILE *F;
//	F = fopen("Candidat.txt", "r");
//	int nbrBulNul = 0;
//	int i = 0;
//	while (!feof(F)) {
//		fscanf(F, "%s ;%s ;%s ;%s \n", &candidat.numCNI, &candidat.nom, &candidat.prenom, &candidat.sexe);
//		fflush(stdin);
//		FILE *V;
//		V = fopen("Vote.txt", "r");
//		int nbrVoteCandidat = 0;
//		nbrBulNul = 0;
//		while (!feof(V)) {
//			fscanf(V, "%s ;%s \n", &vote.electorCniNum, &vote.CandidateCniNum);
//			fflush(stdin);
//			//printf("vote.electorCniNum : %s \n", vote.electorCniNum);
//			if (strcmp(candidat.numCNI, vote.CandidateCniNum) == 0) {
//				nbrVoteCandidat++;
//			}
//			if (strcmp(vote.CandidateCniNum, "---------") == 0) {
//				nbrBulNul++;
//			}
//		}
//
//		if (num == i + 1) {
//			//====>>>> Met tous les noms en majuscule
//			for (int i = 0; candidat.nom[i] != '\0'; i++) {
//				// si les caractères sont en minuscules, converti-les en majuscules 
//				// en soustrayant 32 de leur valeur ASCII.
//				if (candidat.nom[i] >= 'a' && candidat.nom[i] <= 'z') {
//					candidat.nom[i] = candidat.nom[i] - 32;
//				}
//			}
//			for (int i = 0; candidat.prenom[i] != '\0'; i++) {
//				// si les caractères sont en minuscules, converti-les en majuscules 
//				// en soustrayant 32 de leur valeur ASCII.
//				if (candidat.prenom[i] >= 'a' && candidat.prenom[i] <= 'z') {
//					candidat.prenom[i] = candidat.prenom[i] - 32;
//				}
//			}
//
//			//=====>>>>>>> Affichage des statistiques de chaque Candidat¯\_(ツ)_/¯
//			printf("\n\t\t<<<<<<<######==== Candidat %s %s ====######>>>>>>\n\n", candidat.nom, candidat.prenom);
//			printf("\t\tNombre de vote : %d \n\n", nbrVoteCandidat);
//			printf("\t\tPourcentage de reussite : %.2f%% \n\n", ((double)nbrVoteCandidat / (double)nombreDeVote()) * 100);
//			printf("\t\t<<<<<<<<<<<<=================================>>>>>>>>>>>>\n\n");
//		}
//		i++;
//		fclose(V);
//	}
//	fclose(F);
//}
//
//int nbrVoteCandidat(int num) {
//	FILE *F;
//	F = fopen("Candidat.txt", "r");
//	int nbrBulNul = 0;
//	int i = 1;
//	int nbrVoteCandidat = 0;
//	while (!feof(F)) {
//		fscanf(F, "%s ;%s ;%s ;%s \n", &candidat.numCNI, &candidat.nom, &candidat.prenom, &candidat.sexe);
//		fflush(stdin);
//		FILE *V;
//		V = fopen("Vote.txt", "r");
//		if (num == i) {
//			while (!feof(V)) {
//				fscanf(V, "%s ;%s \n", &vote.electorCniNum, &vote.CandidateCniNum);
//				fflush(stdin);
//				//printf("vote.electorCniNum : %s \n", vote.electorCniNum);
//				if (strcmp(candidat.numCNI, vote.CandidateCniNum) == 0) {
//					nbrVoteCandidat++;
//				}
//				if (strcmp(vote.CandidateCniNum, "---------") == 0) {
//					nbrBulNul++;
//				}
//			}
//			break;
//		}
//		else {
//			i++;
//			continue;
//		}
//		fclose(V);
//		
//	}
//	fclose(F);
//	return nbrVoteCandidat;
//}
//
//void affichage(int* arr1, int* arr2) {
//
//	int* arr3 = malloc(nbrCandidats() * sizeof(int));
//	int* arr4 = malloc(nbrCandidats() * sizeof(int));
//	for (int i = 0; i < nbrCandidats(); i++) {
//		arr4[i] = arr2[i];
//	}
//
//	int d = 0, tmp = 0, i = 0;
//	for (d = 26; d != 0; d--){
//		for (i = 0; i < d; i++){
//			if (arr4[i] < arr4[i + 1]){
//				tmp = arr4[i];
//				arr4[i] = arr4[i + 1];
//				arr4[i + 1] = tmp;
//			}
//		}
//	}
//
//	int numPlusGrand = 0; int k = 0;
//	for (int i = 0; i < nbrCandidats(); i++){
//		for (int j = k; j < nbrCandidats(); j++) {
//			if (nbrVoteCandidat(arr1[j]) == arr4[i]) {
//				arr3[j] = arr1[j];
//			}
//		}
//		for (int l = 0; l < nbrCandidats(); l++) {
//			if (arr3[l]>=0) {
//				k++;
//			}
//		}
//	}
//	for (int k = 0; k < nbrCandidats(); k++) {
//		//printf("\nStats du premier :\n\n");
//		printCandidateWhitNum(arr3[k]);
//	}
//	free(arr3);
//	free(arr4);
//}

//void classementCandidatS() {
//	int* arr1 = malloc(nbrCandidats() * sizeof(int));
//	int* arr2 = malloc(nbrCandidats() * sizeof(int));
//	int val = 0;
//	FILE *F;
//	F = fopen("Candidat.txt", "r");
//	int nbrBulNul = 0;
//	int i = 0;
//	while (!feof(F)) {
//		fscanf(F, "%s ;%s ;%s ;%s \n", &candidat.numCNI, &candidat.nom, &candidat.prenom, &candidat.sexe);
//		fflush(stdin);
//		FILE *V;
//		V = fopen("Vote.txt", "r");
//		int nbrVoteCandidat = 0;
//		nbrBulNul = 0;
//		while (!feof(V)) {
//			fscanf(V, "%s ;%s \n", &vote.electorCniNum, &vote.CandidateCniNum);
//			fflush(stdin);
//			//printf("vote.electorCniNum : %s \n", vote.electorCniNum);
//			if (strcmp(candidat.numCNI, vote.CandidateCniNum) == 0) {
//				nbrVoteCandidat++;
//			}
//			if (strcmp(vote.CandidateCniNum, "---------") == 0) {
//				nbrBulNul++;
//			}
//		}
//		arr1[i] = i + 1;
//		arr2[i] = nbrVoteCandidat;
//		i++;
//		
//		fclose(V);
//	}
//	fclose(F);
//	affichage(arr1, arr2);
//	printf("\n\t\t<<<<<<<######==== Bulletins nuls ====######>>>>>>\n\n");
//	printf("\t\tNombre de bulletins nuls : %d \n\n", nbrBulNul);
//	printf("\t\t<<<<<<<<<<<<================================>>>>>>>>>>>>\n\n");
//	free(arr1);
//	free(arr2);
//}