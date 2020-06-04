#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "HeaderAdminRankingSystem.h"
#include "HeaderRankingFunctions.h"
#include "HeaderRandomWordsFunctions.h"

void RankingSystem()
{
	
	FILE *usernamestxt = NULL;
	usernamestxt = openFileUsernames();
	
	FILE *forbusernamestxt = NULL;
	forbusernamestxt = openFileForbiddenNames();
	
	int usernamecount = 0;
	int forbiddenusernamecount = 0;
	usernamecount = countUsernames(usernamestxt);
	forbiddenusernamecount = countUsernames(forbusernamestxt);
	

	char **usernames = NULL;
	usernames = initializeUsernames(usernamestxt, usernamecount);
	
	
	char **fusernames = NULL;
	fusernames = initializeUsernames(forbusernamestxt, forbiddenusernamecount);

	
	doRankingMngmt(usernamestxt, forbusernamestxt, usernames, fusernames, usernamecount, forbiddenusernamecount);

	closeAllRanking(usernamestxt, forbusernamestxt, usernames, fusernames,usernamecount,forbiddenusernamecount);

	return;
}

void optionRankingMgmt()
{
	printf("\n1 - View list of usernames.");
	printf("\n2 - View list of forbidden usernames.");
	printf("\n3 - Sort usernames by alphabet.");
	printf("\n4 - Check out someone's score.");
	printf("\n5 - Add a forbidden username.");
	printf("\n6 - View all users and scores (Linked list)\n");
	printf("\n\nPress any key twice to return to previous menu or press (x) to exit.\n");
}

void doRankingMngmt(FILE *usernamestxt, FILE *forbiddenusernamestxt, char **usernames, char **forbiddenusernames, int namescount, int forbiddennamescount)
{
	char option = '\0';
	char choice = '\0';

	do
	{
		system("cls");
		optionRankingMgmt();
		option = _getch();

		switch (option)
		{
		case '1':
			system("cls");
			fclose(usernamestxt);
			usernamestxt = openFileUsernames();
			printf("\n");
			checkUsernames(usernamestxt, NULL, 1);					//1 is for printing, NULL pointer is used for other function
			printf("\n");
			system("pause");
			break;

		case '2':
			system("cls");
			fclose(forbiddenusernamestxt);
			forbiddenusernamestxt = openFileForbiddenNames();
			printf("\n");
			checkUsernames(forbiddenusernamestxt, NULL, 1);
			printf("\n");
			system("pause");
			break;

		case '3':
			system("cls");
			printf("\n");
			sortWordsby_Alphabet(&usernames, namescount);
			printWords(usernames, namescount, 30);
			printf("\n");
			system("pause");
			break;

		case '4':
			system("cls");
			checkSomeonesScore(usernamestxt);
			printf("\n");
			system("pause");
			break;

		case '5':
			addAForbiddenUsername();
			printf("\n");
			system("pause");
			break;

		case '6': 
			system("cls");
			printRanksinLL(usernamestxt, usernames, namescount);
			printf("\n");
			system("pause");
			break;

		case 'x':
		case 'X':
			closeAllRanking(usernamestxt, forbiddenusernamestxt, usernames, forbiddenusernames, namescount, forbiddennamescount);
			exit(EXIT_SUCCESS);
			
		default:
			return;
		}
	} while (1);
}