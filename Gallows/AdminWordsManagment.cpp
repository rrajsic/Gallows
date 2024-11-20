#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "HeaderAdminWordsManagment.h"
#include "HeaderRandomWordsFunctions.h"

void adminWords()
{
	FILE *ranWords = NULL;
	ranWords = openFileRead();
	
	int wordcount = 0;
	wordcount = ranWordCount(ranWords);
	int maxletter = 0;
	maxletter = maxLetterCount(ranWords);
	
	fseek(ranWords, SEEK_SET, 0);				             	//need to return the pointer on top of the word file

	char **words = NULL;
	words = initializeWords(ranWords, wordcount, maxletter);

	int *sum = NULL;
	sum = initializeSum(ranWords, words, wordcount);

	doWordMgmt(ranWords,words,sum,wordcount,maxletter);

	closeAll(ranWords, words, sum, NULL, NULL, wordcount);
	return;
}

void optionWordMgmt()
{
	printf("\n1-View list of random words\n");
	printf("2-Sort words by alphabet\n");
	printf("3-Sort words by word size\n");
	printf("4-Add a word\n");
	printf("5-Find a word\n");
	printf("\n\nPress any key twice to return to previous menu or press (x) to exit.\n");
}

void doWordMgmt(FILE*ranWords,char **words,int *sum,int wordcount, int maxletter)
{
	char option = '\0';
	char choice = '\0';
	char **wordstemp = NULL;

	do {
		system("cls");
		optionWordMgmt();
		option = _getch();
		switch (option)
		{
		case '1':
			system("cls");
			printWordsFromFile(ranWords, wordcount,1);
			printf("\n");
			system("pause");
			break;

		case '2':
			system("cls");
			sortWordsby_Alphabet(&words, wordcount);
			printWouldYouLikeToPrintWords(words,wordcount,maxletter);
			break;

		case '3':
			system("cls");
			sum = NULL;
			wordstemp = NULL;
			wordstemp = printWordsFromFile(ranWords, wordcount, 0);
			sum = initializeSum(ranWords, wordstemp, wordcount);
			sortWordsBy_Size(&wordstemp,&sum,wordcount);										//bubblesort algorithm
			printWouldYouLikeToPrintWords(wordstemp,wordcount,maxletter);
			break;

		case '4':
			system("cls");
			addWordToFile(ranWords);
			system("pause");
			break;

			case'5':
				findWord(words,wordcount);
				system("pause");
				break;

		case 'x':
		case 'X':
			closeAll(ranWords, words, sum, NULL,NULL,wordcount);
			exit(EXIT_SUCCESS);

		default:
			return;
		}
	} while (1);
}

void printWouldYouLikeToPrintWords(char **words, int wordcount, int maxletter)
{
	char choice = '\0';
	printf("\nDo you want to print words? (y/n):  ");
	do {
		choice = _getch();
		if (choice == 'y' || choice == 'Y')
		{
			printWords(words, wordcount,maxletter);
			printf("\n");
			system("pause");
			break;
		}
		if (choice == 'n' || choice == 'N')break;
	} while (choice != 'y' || choice != 'n' || choice != 'Y' || choice != 'N');
}
