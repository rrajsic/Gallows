#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include "HeaderGallowsMain.h"
#include "HeaderGallowsFunctions.h"
#include "HeaderRandomWordsFunctions.h"

void GallowsMain(int *SCORE)
{	
	//Here are admin variables that can be changed

	int NUMBER_OF_LIVES = 10;										//also needs to be changed in the end of this function
	//////////////////////////////
	char choice = '\0';
	do {
		system("cls");												//Clears the screen

		FILE *ranWords = NULL;
		ranWords = openFileRead();

		int wordcount = 0;
		wordcount = ranWordCount(ranWords);
		int maxletter = 0;
		maxletter = maxLetterCount(ranWords);

		fseek(ranWords, SEEK_SET, 0);				             	//need to return the pointer on top of the word file

		char **words = NULL;
		words = initializeWords(ranWords, wordcount, maxletter);

		char *guesses = NULL;
		guesses = allocateGuesses(26);								//there are 26 letters in the alphabet

		char *hiddenword = NULL;
		int randomnumber = randomNumber(wordcount);
		hiddenword = initializeHiddenWord(words, wordcount, maxletter, randomnumber);


		//printf("%s\n", *(words + randomnumber));					//prints out the randomized word
		//printf("And now its hidden -> %s\n", hiddenword);

		printRules(NUMBER_OF_LIVES);
		thinkingGallows();

		int guessnum = 0;
		char switchedword[999] = { '\0' };										//switched word is a temporary variable where we will change and save the word
		int hits = 0;															//hits is the number of successful guessses
		do {
			int temp = hits;													//we will save the last number of hits so when we guess we can sheck if the number is bigger										

			*(guesses + guessnum) = eneteringAGuess(guesses, guessnum);
			strcpy(switchedword, switchLetter(*(guesses + guessnum), words, switchedword, randomnumber, &hits));	//switch letter is a function in 'GallowsFunctions.cpp'															

			strcpy(hiddenword, switchedword);
			printf("{ %s }\n", hiddenword);
			guessnum++;

			if (hits == strlen(switchedword))
			{
				printf("\nCongratulations, you've guessed the word.\a\n");
				printf("You get 100 points!\n");
				*SCORE += 50;																						//if the user guesses the word he gets 50 points
				break;
			}

			else if (hits > temp)
			{
				printf("\n->You have guessed correctly!");
				printf(" (+5 pts)\n");
				*SCORE += 5;
			}

			else {
				NUMBER_OF_LIVES--;
				printf("\n->Miss. Number of lives left: [%d]\n", NUMBER_OF_LIVES);
			}

		} while (NUMBER_OF_LIVES > 0);

		if (NUMBER_OF_LIVES == 0)
		{
			printf("\nSorry, you lost!\a\n");
			printf("The word was ->%s\n", *(words + randomnumber));
		}

		closeAll(ranWords, words, NULL, hiddenword, guesses, wordcount);

		printf("\n\nPress (y) to play again or any key to return to previous menu.\n");
		choice = _getch();
		if (choice == 'y' || choice == 'Y') NUMBER_OF_LIVES = 10;
	} while (choice == 'y' || choice == 'Y');
	
	return;
}

void printRules(int lives)
{
	printf("\nWelcome to my Gallows game\n");
	printf("Rules:\n");
	printf("- Try to guess the randomized word.\n");
	printf("- You have %d lives.\n", lives);
	printf("- For each letter guessed you get +5 pts.\n");
	printf("- For each word guessed you get +50 pts.\n");
	printf("Good luck!\n\n");
}

void thinkingGallows()
{
	printf("I'm thinking of a word\n\n");
	Sleep(1000);
	printf("H");
	Sleep(250);
	printf("m");
	Sleep(250);
	printf("m");
	Sleep(250);
	printf(".");
	Sleep(250);
	printf(" .");
	Sleep(250);
	printf(" .\n");
	printf("Got it.\n");
	Sleep(250);
	printf("Give it a try!\n\n");
	Sleep(250);
}
