#include <stdio.h>
#include <stdlib.h>

#include "Candidats.h"
#include "Electeurs.h"
#include "main.h"
#include "Voter.h"
#include "Statistiques.h"

void checkFiles() {
	FILE* fichier = NULL;
	fichier = fopen("Candidat.txt", "r");
	FILE* fichier2 = NULL;
	fichier = fopen("Electeur.txt", "r");
	FILE* fichier3 = NULL;
	fichier = fopen("Vote.txt", "r");
	if (fichier != NULL)
	{
		// On peut lire et écrire dans le fichier
		fclose(fichier);
		
	}else{
		// On affiche un message d'erreur si on veut
		//printf("Fichier Candidat.txt inexistant !\n");
		fichier = fopen("Candidat.txt", "a");
		fclose(fichier);
		//printf("Impossible d'ouvrir le fichier test.txt");
	}
	if (fichier2 != NULL) {
		// On peut lire et écrire dans le fichier
		fclose(fichier2);
		
	}
	else {
		// On affiche un message d'erreur si on veut
		//printf("Fichier Electeur.txt inexistant !\n");
		fichier2 = fopen("Electeur.txt", "a");
		fclose(fichier2);
		//printf("Impossible d'ouvrir le fichier test.txt");
	}
	if (fichier3 != NULL) {
		// On peut lire et écrire dans le fichier
		fclose(fichier3);
	}
	else {
		// On affiche un message d'erreur si on veut
		//printf("Fichier Vote.txt inexistant !\n");
		fichier3 = fopen("Vote.txt", "a");
		fclose(fichier3);
		//printf("Impossible d'ouvrir le fichier test.txt");
	}
	fclose(fichier);
	fclose(fichier2);
	fclose(fichier3);
	//system("pause");
}


int main()
{
	int choice;
	char anwser;
	checkFiles();
	do
	{

		system("cls");
		printf("\t\t _____   ____   _____  _______       _____  _      _____  _____  _____  _____  _____  _   _\n");
		printf("\t\t| ___ \\ | ___| /  ___|| _   _ |     |  ___|| |    |  ___|/  __ \\|_   _||_   _||  _  || \\ | |\n");
		printf("\t\t| |_/ / | |__  \\ `--.    | |        | |__  | |    | |__  | /  \\/  | |    | |  | | | ||  \\| |\n");
		printf("\t\t| ___ \\ | __ |  `--. \\   | |        |  __| | |    |  __| | |      | |    | |  | | | || . ` |\n");
		printf("\t\t| |_/ / | |___ /\\__/ /   | |        | |___ | |____| |___ | \\_ /\\  | |   _| |_ \\ \\_/ /| |\\  |\n");
		printf("\t\t\\____/  \\____/ \\____/    \\_/        \\____/ \\_____/\\____ /\\____ /  \\_/   \\___/  \\___/ \\_| \\_/\n\n");
		/*printf("\n\
			______  _____  ______  _______  _____  _      _____  _____  _____  _____  _____  _   _\n\
			| ___ \ | ___|/  ___ || _   _ ||  ___|| |    |  ___|/  __ \|_   _||_   _||  _  || \ | |\n\
			| |_/ / | |__  \ `- -.   | |   | |__  | |    | |__  | /  \/  | |    | |  | | | ||  \| |\n\
			| ___ \ | __ |  `- -. \  | |   |  __| | |    |  __| | |      | |    | |  | | | || . ` |\n\
			| |_/ / | |___ /\__/  /  | |   | |___ | |____| |___ | \__ /\ | |   _| |_ \ \_/ /| |\  |\n\
			\____/  \____/ \____ /   \_/   \____/ \_____/ \____ /\____ / \_/   \___/  \___/ \_| \_/\n\
			");*/
		printf("\n\t\t<<<<<<<@@@@@@@==== BIENVENUE SUR *BEST ELECTION* (^_^) ====@@@@@@>>>>>>\n\n");
		printf("\t 1- Gestion des candidats\n");
		printf("\t 2- Gestion des electeurs\n");
		printf("\t 3- Voter\n");
		printf("\t 4- Consulter les statistiques\n");
		printf("\t 5- Quitter\n\n");

		do {
			printf("\n\t=> Entrez votre choix : ");
			scanf("%d", &choice);
			while (getchar() != '\n');
		} while (choice < 1 || choice > 6);

		switch (choice) {
		case 1:
			goCandidat();
			break;
		case 2:
			goElecteur();
			break;
		case 3:
			goVoter();
			break;
		case 4:
			goStatistiques();
			break;
		default:
			break;
		}
		printf("\n\tVoulez-vous continuer ? o/n : ");
		scanf("%s", &anwser);//anwser = getch();
		fflush(stdin);
	} while (anwser == 'o' || anwser == 'O');
	
	system("exit");
	return EXIT_SUCCESS;
}