#pragma once
#ifndef DEF_ELECTEURS
#define DEF_ELECTEURS
void goElecteur();
int checkCni(char searchCNI[32]);
//int searchCniElecteur(char searchCNI[32]);
void ajouterElecteur();
void searchAndPrintElector();
void supprimerElecteur();
void modifierElecteur();
void afficherElecteurs();
#endif