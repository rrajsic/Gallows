#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "HeaderSourceFunctions.h"
#include "HeaderRankingFunctions.h"
#include "HeaderRandomWordsFunctions.h"



void listOfGames()
{
	//printf("\nPress a number beside which action you would like.\n\n");
	printIntroduction();														//thats the long typing function
	Sleep(200);
	printf("->1-Play Gallows\n");
	Sleep(100);
	printf("\n");
	printf("->A-Access Admin settings\n");
	Sleep(100);
	printf("~~~~~~~~~~~~~~~~~~~~~~~\n");
	Sleep(100);
	printf("Press (x) to exit.\n");
}

void printIntroduction()
{
	printf("\nP");
	Sleep(50);
	printf("r");
	Sleep(50);
	printf("e");
	Sleep(50);
	printf("s");
	Sleep(50);
	printf("s");
	Sleep(50);
	printf(" ");
	Sleep(50);
	printf("a");
	Sleep(50);
	printf(" ");
	Sleep(50);
	printf("n");
	Sleep(50);
	printf("u");
	Sleep(50);
	printf("m");
	Sleep(50);
	printf("b");
	Sleep(50);
	printf("e");
	Sleep(50);
	printf("r");
	Sleep(50);
	printf(" ");
	Sleep(50);
	printf("b");
	Sleep(50);
	printf("e");
	Sleep(50);
	printf("s");
	Sleep(50);
	printf("i");
	Sleep(50);
	printf("d");
	Sleep(50);
	printf("e");
	Sleep(50);
	printf(" ");
	Sleep(50);
	printf("w");
	Sleep(50);
	printf("h");
	Sleep(50);
	printf("i");
	Sleep(50);
	printf("c");
	Sleep(50);
	printf("h");
	Sleep(50);
	printf(" ");
	Sleep(50);
	printf("a");
	Sleep(50);
	printf("c");
	Sleep(50);
	printf("t");
	Sleep(50);
	printf("i");
	Sleep(50);
	printf("o");
	Sleep(50);
	printf("n");
	Sleep(50);
	printf(" ");
	Sleep(50);
	printf("y");
	Sleep(50);
	printf("o");
	Sleep(50);
	printf("u");
	Sleep(50);
	printf(" ");
	Sleep(50);
	printf("w");
	Sleep(50);
	printf("o");
	Sleep(50);
	printf("u");
	Sleep(50);
	printf("l");
	Sleep(50);
	printf("d");
	Sleep(50);
	printf(" ");
	Sleep(50);
	printf("l");
	Sleep(50);
	printf("i");
	Sleep(50);
	printf("k");
	Sleep(50);
	printf("e\n");
}

char* loginfinish()
{
	char *username = NULL;
	int loginsucces = -2;
	do {
		username = getUsername();
		loginsucces = logIn(username);
		if (loginsucces == -2)printf("Seems like you've entered one of the forbidden usernames, try again.\n\n");

	} while (loginsucces < 0);										//here we just check if a person typed a forbidden username or set of symbols like : ! , . ; .. 

	return username;
}

PLAYER* checkLoginHit(char *username)								//this function checks for repeating usernames
{
	FILE *usernamestxt = NULL;
	usernamestxt = openFileUsernames();

	PLAYER *p = NULL;
	p = allocatePlayer();
	int temp = -1;													//random defintion just that it's no longer garbage
	temp = checkUsernames(usernamestxt, username, 0);

	if (temp == 0)
	{
		printf("\nWelcome back %s!\n", username);
		Sleep(400);
		p = readScore_FromBin(p,username);
	
		printf("\nYour stats are:\n");
		Sleep(150);
		printf("Score: %d\n", p->score);
		Sleep(150);
		printf("Last played: ");
		Sleep(150);
		printf("(%d.%d.%d) - %d:%d\n\n", p->tm.tm_mday, p->tm.tm_mon + 1, p->tm.tm_year + 1900, p->tm.tm_hour, p->tm.tm_min);
		Sleep(150);
	}
	else
	{
		fputs(username, usernamestxt);
		fputs("\n", usernamestxt);
		writeScores_ToBin(username, p, 0);
		printf("\nWelcome, %s!\n", username);
		Sleep(400);
	}

	fclose(usernamestxt);
	return p;
}
