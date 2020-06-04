#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include "HeaderSourceFunctions.h"
#include "HeaderGallowsFunctions.h"
#include "HeaderRandomWordsFunctions.h"
#include "HeaderGallowsMain.h"
#include "HeaderAdminSpace.h"
#include "HeaderRankingFunctions.h"
#include "HeaderAdminRankingSystem.h"

int main()
{
	srand(time(unsigned(NULL)));
	
	printf("\n");

	char *username = NULL;
	username = loginfinish();
	system("cls");

	int SCORE = 0;
	PLAYER *p = NULL;
	p = checkLoginHit(username);
	SCORE = p->score;
									
	do {
		listOfGames();
		char option;
		option = _getch();						  //using _getch so user doesn't need to press enter

		switch (option)
		{
		case '1':
			GallowsMain(&SCORE);
			system("cls");
			break;

		case 'a':
		case 'A':
			AdminSpace();
			break;

		case 'x':
		case 'X':
			printf("\nThanks for playing!\n\n");
			Sleep(800);
			writeScores_ToBin(username, p, SCORE);
			free(username);
			free(p);
			return 0;

		default:
			printf("You have entered an invalid option.\n\n");
			Sleep(600);
			system("cls");
			continue;
		}

	} while (1);
}
