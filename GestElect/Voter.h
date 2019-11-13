#pragma once
#ifndef DEF_VOTER
#define DEF_VOTER
void goVoter();
int afficherListeElecteursV();
int hasVote(int electorChoice);
int voteHasBeenApply();
void makeElectorChoice(int num);
void afficherListeCandidatsV(char ElectorCniNum[32]);
void makeCandidateChoice(int candidateNum, char ElectorCniNum[32]);
#endif