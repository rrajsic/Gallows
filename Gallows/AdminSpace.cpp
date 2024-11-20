#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include "HeaderAdminSpace.h"
#include "HeaderAdminWordsManagment.h"
#include "HeaderAdminRankingSystem.h"

void AdminSpace()
{
	const char password[7] = { "kundak" };
	int x = 0;
	x = checkPassword(password);
	if (x == 0)exit(1);

	char option='\0';

	do {

		system("cls");
		printf("\nYou have enter super mega private secret sector. Choose your option:\n");

		printAdminSpaceOptions();
		option = _getch();

		switch (option)
		{

		case '1':
			adminWords();
			break;

		case '2':
			RankingSystem();
			break;

		case 'x':
		case 'X':
			exit(1);

		default:
			system("cls");
			return;
		}
		_getch();
	} while (1);
}

int checkPassword(const char password[])
{
	int temp = 0;
	do {
		printf("\nEnter password: ");
		char entry[99];
		scanf("%s", entry);

		if (strcmp(password, entry) == 0)
		{
			printf("\nAccess Granted!");
			Sleep(500);
			return 1;
		}

		char x;
		printf("Wrong password. Do you want to try again? (y/n): ");

		do {
			x = _getch();
			switch (x)
			{
			case 'y':
			case 'Y':
				break;

			case 'n':
			case 'N':
				temp = 1;
				break;

			default:
				break;
			}
		} while (x != 'y' && x != 'Y' && x != 'n' && x != 'N');

	} while (temp == 0);

	printf("\n");
	system("pause");
	return 0;
}

void printAdminSpaceOptions()
{
	printf("\n1 - Random Words Managment.");
	printf("\n2 - Ranking System Managment");

	printf("\n\n\nPress any key to return to previous menu or press (x) to exit.\n");
}
