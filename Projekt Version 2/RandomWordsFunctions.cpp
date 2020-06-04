#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include "HeaderRandomWordsFunctions.h"

FILE * openFileRead()
{
	FILE *ranWords = NULL;
	ranWords = fopen("Random Words\\randomWords.txt", "r");
	if (checkifFileOpen(ranWords) == -1)exit(EXIT_FAILURE);
	return ranWords;
}

FILE * openFileAppend()
{
	FILE *ranWords = NULL;
	ranWords = fopen("Random Words\\randomWords.txt", "a+");
	if (checkifFileOpen(ranWords) == -1)exit(EXIT_FAILURE);
	return ranWords;
}

int checkifFileOpen(FILE *ranWords)
{
	if (ranWords == NULL)
	{
		perror("Error: ranWords isn't open\n");
		system("pause");

		return -1;
	}
	else return 1;
}

char **allocateWords(FILE *ranWords, int wordcount, int maxlettercount)
{
	if (checkifFileOpen(ranWords) == -1)exit(EXIT_FAILURE);

	char **wordsfield = NULL;
	wordsfield = (char**)calloc(wordcount, sizeof(char*));
	for (int i = 0; i < wordcount; i++)
		*(wordsfield + i) = (char*)calloc(maxlettercount, sizeof(char));
	
	if (wordsfield == NULL)
	{
		perror("Couldn't allocate memory\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < wordcount; i++)
		if (*(wordsfield+i) == NULL)
		{
			perror("Couldn't allocate memory\n");
			system("pause");
			exit(EXIT_FAILURE);
		}

	return wordsfield;
}

char **initializeWords(FILE *ranWords, int wordcount, int maxletter)										
{
	char **words = NULL;
	words = allocateWords(ranWords, wordcount, maxletter);
	for (int i = 0; i < wordcount; i++)
	{
		fgets(*(words + i), maxletter, ranWords);
		for (int j = 0; j < strlen(*(words + i)); j++)
			if(*(*(words+i)+j)=='\n')*(*(words + i) + (strlen(*(words + i)) - 1)) = '\0';					//this replaces the \n with \0 as a last character
		
		//printf("%d->%s\n", i, *(words + i));																//prints out the words respectively
	}
	return words;
}

int *allocateSum(FILE *ranWords, int wordcount)
{
	checkifFileOpen(ranWords);

	int *sum = NULL;
	sum = (int *)calloc(wordcount, sizeof(int));
	if (sum == NULL)
	{
		perror("Couldn't allocate memory for sum.\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	else return sum;
}

int *initializeSum(FILE *ranWords,char **words, int wordcount)												//this function sums ASCII values of letters
{
	int *sum=NULL;
	sum = allocateSum(ranWords, wordcount);

	for (int i = 0; i < wordcount; i++)
		for (int j = 0; j < strlen(*(words + i)-1); j++)
			*(sum + i) = *(sum + i) + *(*(words + i) + j);

	return sum;
}

int ranWordCount(FILE *ranWords)
{
	if (checkifFileOpen(ranWords) == -1)exit(EXIT_FAILURE);

	int counter = 0;
	char field[9999][99] = { '\0' };
	while (fgets(field[counter], 99, ranWords) != NULL)counter++;

	return counter;
}

int maxLetterCount(FILE *ranWords)
{
	if (checkifFileOpen(ranWords) == -1)exit(EXIT_FAILURE);

	int counter = 0;
	int lettercounter = 0;
	char field[9999][99] = { '\0' };

	fseek(ranWords, SEEK_SET, 0);
	while (fgets(field[counter], 99, ranWords) != NULL)counter++;

	//printf("counter %d\n", counter);											prints how many words there are
	int maxletter = 0;
	for (int i = 0; i < counter; i++)
	{
		lettercounter = (strlen(field[i])+2);									//i put +2 just to be sure because if +2 is missing it wont count all the letters (idk why)
		if (lettercounter > maxletter)
			maxletter = lettercounter;
	}

	return maxletter;
}

void sortWordsby_Alphabet(char***words,int wordcount)
{
	for (int i = 0; i < wordcount; i++)
		for (int j = 0; j < wordcount; j++)
			if (strcmp(*(*words + i), (*(*words + j))) < 0)
				swapWords(*(*words + i), *(*words + j));
			
}

void sortWordsBy_Size(char***words,int **sum,int wordcount)										//bubble sort algorithm
{
	for (int i = 0; i < wordcount; i++)
		for (int j = (i + 1); j < wordcount; j++)
		{
			if (*(*sum+i) > *(*sum + j))
			{
				swapWords(*(*words + i), *(*words + j));
				int temp;
				temp = *(*sum + i);
				*(*sum + i) = *(*sum + j);
				*(*sum + j) = temp;
			}
		}
}

void swapWords(char *word_1, char *word_2)
{
	char temp[999] = { '\0' };
	strcpy(temp, word_1);
	strcpy(word_1,word_2);
	strcpy(word_2, temp);
}

char* getWord()
{
	char *word = NULL;
	word = (char*)calloc(99, 1);
	if (word == NULL)
	{
		perror("Couldn't allocate memory for 'word'.\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}								//this little function clears buffer
	
	printf("Type in a word: ");
	scanf("%s", word);

	int counter = 0;
	while (counter <50 && *(word+counter) != '\n')counter++;
	*(word + counter) = '\0';
	
	return word;
}

void addWordToFile(FILE *ranWords)
{
	ranWords = openFileAppend();
	char *word = NULL;
	word = getWord();
	fprintf(ranWords, "\n%s", word);

	fclose(ranWords);
	printf("Changes will take effect when program restarts.\n");
}

void findWord(char**words,int wordcount)
{
	char *word = NULL;
	word = getWord();

	int temp = -2;														//initialized so that it isn't garbage
	int i = 0;
	for ( i = 0; i < wordcount; i++)
	{
		temp = strcmp(*(words+i), word);
		if (temp == 0)break;
	}

	if (temp == 0) {
		printf("Word \"%s\"has been found.\n",word);
		printf("And it's on index: [%d]\n", i);
	}
	else printf("Word \"%s\"has not been found.\n",word);

	free(word);
	return;
}

void printWords(char **words, int wordcount,int maxletter)
{
	for (int i = 0; i < wordcount; i++)
	{
		printf("%s\n", *(words + i));
		if (wordcount < 500)Sleep(50);													//if there isn't a huge ammount of data, make it a bit slower so it will seem
	}																					//more dynamical
	printf("\n");
}

char** printWordsFromFile(FILE *ranWords,int wordcount,int printoption)
{
	fseek(ranWords, SEEK_SET, 0);
	char **words = NULL;
	words = allocateWords(ranWords, wordcount, 99);
	int i = 0;
	while (fgets(*(words + i), 99, ranWords) != NULL)
	{
		for (int j = 0; j < strlen(*(words + i)); j++)
			if (*(*(words + i) + j) == '\n')*(*(words + i) + (strlen(*(words + i)) - 1)) = '\0';

		if(printoption!=0)printf("%s\n", *(words + i));					
		i++;
	}

	return words;
}

int closeAll(FILE *ranWords,char **words,int *sum,char *hiddenword,char *guesses,int wordcount)
{
	for (int i = 0; i < wordcount; i++)
		free(*(words + i));

	free(words);
	free(hiddenword);
	free(guesses);
	fclose(ranWords);

	return 1;
}
