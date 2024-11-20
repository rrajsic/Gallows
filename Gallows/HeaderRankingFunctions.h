#ifndef HEADERRANKINGFUNCTIONS_H
#define HEADERRANKINGFUNCTIONS_H
#include <time.h>
typedef struct Players
{
	char username[99];
	int score;
	struct tm tm;															//this is for time

	struct Players *next;
}PLAYER;

char* getUsername();
FILE* openFileUsernames();
FILE* openFileForbiddenNames();
PLAYER *allocatePlayer();
int logIn(char *username);
int countUsernames(FILE *file);
int checkUsernames(FILE *file, char *username,int printoption);				//if option == 1 this function prints usernames

char** allocateUsernames();
char **initializeUsernames(FILE *filenames, int namescount);

int writeScores_ToBin(char *username, PLAYER *p, int SCORE);
PLAYER* readScore_FromBin(PLAYER *p,char *username);
void checkSomeonesScore(FILE *usernamestxt);
int addAForbiddenUsername();

int closeAllRanking(FILE *usernamestxt, FILE *forbiddenusernamestxt, char **usernames,char **forbiddenusernames, int namescount,int forbidennamescount);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//LINKED LIST FUNCTIONS
void printRanksinLL(FILE *usernamestxt, char **usernames, int namecount);
PLAYER *MakeAList(PLAYER **head, PLAYER readP);
PLAYER* addToStart(PLAYER **head, PLAYER readP);
PLAYER *addToEnd(PLAYER **head, PLAYER readP);
int printList(PLAYER *head);
PLAYER* eraseList(PLAYER *head);



#endif