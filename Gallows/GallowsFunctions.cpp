#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "HeaderGallowsFunctions.h"


char enterALetter()
{
	char letter = '\0';
	do {
		scanf(" %c",&letter);
		if ((int)letter < 97 || (int)letter>122)
		{
			printf("You need to enter a lowercase letter.\n");
			printf("Try again.\n");
		}
	} while ((int)letter < 97 || (int)letter>122);

	return letter;
}

char eneteringAGuess(char *guesses,int guessnum)												//this function is returning a guessed letter
{																								//but it also takes all guessed letters
	printf("Take a guess: ");

	int temp = 0;
		do
		{
			*(guesses +guessnum) = enterALetter();
	
			for (int i = 0; i < guessnum; i++)
			{
				if (*(guesses + guessnum) == *(guesses + i))
				{
					printf("You have already tried that letter.\n");
					printf("Try again.\n");
					temp = 1;
					break;
				}

				else temp = 0;
			}
		} while (temp);																			//while temp is 1 it will repeat
		
		printf("Your guesses: ");
		for (int i = 0; i < strlen(guesses); i++) 
			printf("%c, ", *(guesses + i));

		printf("\n");

		return *(guesses + guessnum);
}

char * allocateGuesses(int maxnumofguesses)
{
	char *guesses = NULL;
	guesses = (char*)calloc(maxnumofguesses, 1);
	if (guesses == NULL)
	{
		perror("Couldn't allocate memory for 'guesses'\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	return guesses;
}

int randomNumber(int wordcount)
{
	int randomnumber = 0;
	randomnumber = rand() % (wordcount + 1);

	return randomnumber;
}

char *allocateHiddenWord(int maxletter)
{
	char *hiddenword = NULL;
	hiddenword = (char*)calloc(maxletter, 1);

	if (hiddenword == NULL)
	{
		perror("Couldn't allocate memory for 'hiddenword'\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	return hiddenword;
}

char *initializeHiddenWord(char **words, int wordcount,int maxletter,int randomnumber)							//this function takes a random number and hides all the letters with ' _ '
{																												//then returns it
	char *hiddenword = allocateHiddenWord(maxletter);
	
	strcpy(hiddenword, *(words + randomnumber));

	for (int i = 0; i < strlen(hiddenword); i++)
		*(hiddenword + i) = '_';
	
	return hiddenword;
}

char *switchLetter(char changedWord[], char guess,char **words,char *switchedword,int randomnumber,int *hit)
{
	if (*switchedword =='\0')
	{
		for (int i = 0; i < strlen(*(words + randomnumber)); i++)
		{
			changedWord[i] = '_';
		}
	}

	else
		strcpy(changedWord, switchedword);

	int x = 0;
	int y = 0;													//needed to use x and y to simplify if statement
	for (int i = 0; i < strlen(*(words+randomnumber)); i++)
	{
		x = (int)guess;
		y = (int)(*(*(words + randomnumber)+i));

		if(x==y)
		{
			(*hit)++;
			changedWord[i] =guess;
		}
	}
	
	return changedWord;
}
