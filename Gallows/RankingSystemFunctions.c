#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "HeaderRankingFunctions.h"

char* getUsername()																
{
	char *username = NULL;
	username = (char*)calloc(99, 1);
	if (username == NULL)
	{
		perror("Couldn't allocate memory for username\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	printf("Type in a username: ");
	int counter = 0;
	scanf("%s", username);
	while (counter < 30 && username[counter] != '\n')counter++;
	username[counter] = '\0';
	
	return username;
}

FILE* openFileUsernames()
{
	FILE *fileUsernames = NULL;

	fileUsernames = fopen("Ranking System\\Usernames.txt", "a+");
	if (fileUsernames == NULL)
	{
		perror("Couldn't open file \"Usernames.txt\"");
		system("pause");
		exit(EXIT_FAILURE);
	}
	return fileUsernames;
}

FILE* openFileForbiddenNames()
{
	FILE *forbidden = NULL;
	forbidden = fopen("Ranking System\\ForbiddenNames.txt", "a+");
	if (forbidden == NULL)
	{
		perror("Couldn't open file \"ForbiddenNames.txt\"");
		system("pause");
		exit(EXIT_FAILURE);
	}
	return forbidden;
}

PLAYER *allocatePlayer()
{
	PLAYER *p = NULL;
	p = (PLAYER*)calloc(1, sizeof(PLAYER));
	if (p == NULL)
	{
		perror("Couldn't allocate memory for player 'p'\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	return p;
}

int logIn(char *username)												//this function check if the typed login username has symbols or if its in forbidden usernames.txt
{
	int templetter = 0;

	for (int i = 0; i < strlen(username); i++)
	{
		templetter = (int)(*(username + i));

		if (!((templetter > 64 && templetter < 91) || (templetter > 96 && templetter < 123) || (templetter > 47 && templetter < 58)))		//if its a symbol
		{
			printf("Please avoid symbols and numbers! Try again.\n\n");
				return -1;
		}
	}

	FILE *forbiddenusernames = NULL;
	forbiddenusernames = openFileForbiddenNames();
	
	int temp = 0;
	temp = checkUsernames(forbiddenusernames, username, 0);

	if (temp == 0)return -2;
	else return 0;
}

int countUsernames(FILE *file)
{
	if (file == NULL)
	{
		perror("error file isn't open\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	int counter = 0;

	char **temp=NULL;
	temp = (char**)calloc(999, sizeof(char*));								
	for (int i = 0; i < 999; i++)	
		*(temp + i) = (char*)calloc(99, sizeof(char));

	if (temp == NULL)
	{
		perror("Couldn't allocate memory for forbidden names.\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	fseek(file, SEEK_SET, 0);
	while (fgets(*(temp + counter), 99, file) != NULL)counter++;

	for (int i = 0; i < 999; i++)
		free(*(temp + i));
	free(temp);

	return counter;
}
																					
int checkUsernames(FILE *file,char *username,int printoption)						//i will use this function for printing aswell for checking for matches
{																					//they are forbidden because windows doesn't let you create files with these names
	char **names = NULL;
	names = (char**)calloc(999, sizeof(char*));										
	for (int i = 0; i < 999; i++)
		*(names+i) = (char*)calloc(99, sizeof(char));
	
	if(names==NULL)
		{
			perror("Couldn't allocate memory for forbidden names.\n");
			system("pause");
			exit(EXIT_FAILURE);
		}
	
	int i = 0;
	while (fgets(*(names + i), 20, file) != NULL)
	{
		int counter = 0;
		while (counter < 50 && *(*(names+i) + counter) != '\n')counter++;				//this little function removes the \n sign of functions
		*(*(names + i) + counter) = '\0';
		if (printoption == 1) 
		{
			printf("%s\n", *(names + i));												//this is where the function prints
			Sleep(50);																	//using sleep for printing to seem more dynamical
		}
		i++;
	}
	
	if (username == NULL)return 0;														//if we want to use this function just for printing

	else
	{
		int temp = -2;
		for (int j = 0; j < i; j++)														//here we check for matches
		{
			if (strcmp(username, *(names + j)) == 0)
			{
				temp = 0;																//using temp so i can free memory
				break;
			}
			else temp = 1;
		}

		for (int i = 0; i < 22; i++)
			free(*(names + i));
		free(names);

		if (temp == 0)return 0;
		else return 1;
	}
}

char** allocateUsernames()
{
	char **usernames = NULL;
	usernames = (char**)calloc(999, sizeof(char*));								
	for (int i = 0; i < 999; i++)
		*(usernames + i) = (char*)calloc(99, sizeof(char));
	
	if (usernames == NULL)
	{
		perror("Couldn't allocate memory for forbidden names.\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	return usernames;
}

char **initializeUsernames(FILE *filenames, int namescount)
{
	char **usernames = NULL;
	usernames = allocateUsernames();

	fseek(filenames, SEEK_SET, 0);
	int i = 0;
	while (fgets(*(usernames + i), 20, filenames) != NULL)
	{
		int counter = 0;
		while (counter < 50 && *(*(usernames + i) + counter) != '\n')counter++;	//this little function removes the \n sign of functions
		*(*(usernames + i) + counter) = '\0';
		i++;
	}
	
	return usernames;
}

int writeScores_ToBin(char *username, PLAYER *p , int SCORE)		//with this function we will create bin file 
{																	//if the bin file already exists we will overwrite it with new score and time
	char usernamebin[99] = { "Ranking System\\bin\\" };
	strcat(usernamebin, username);
	strcat(usernamebin, ".bin");

	FILE *scores = NULL;
	scores = fopen(usernamebin, "wb");
	if (scores == NULL)
	{
		perror("Error in opening file 'scores' for writing\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	if (p == NULL)
		return -1;
	
	strcpy(p->username, username);
	p->score = SCORE;
	time_t t = time(NULL);											//this function saves time played
	p->tm = *localtime(&t);

	fwrite(p, sizeof(*p), 1, scores);

	fclose(scores);
	return 0;
}

PLAYER* readScore_FromBin(PLAYER *p, char *username)				//this function takes PLAYER p as an argument and returns PLAYER P 
{
	char usernamebin[99] = { "Ranking System\\bin\\" };
	strcat(usernamebin, username);
	strcat(usernamebin, ".bin");

	FILE *scores;
	scores = fopen(usernamebin, "rb");
	if (scores == NULL)
	{
		perror("Error in opening file 'scores' for reading\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	fread(p, sizeof(PLAYER), 1, scores);
	fclose(scores);
	return p;
}

void checkSomeonesScore(FILE *usernamestxt)
{
	char *username = NULL;
	username = getUsername();

	fseek(usernamestxt, SEEK_SET, 0);

	if (checkUsernames(usernamestxt, username, 0) == 0)
	{
		PLAYER *p = NULL;
		p = allocatePlayer();
		p = readScore_FromBin(p, username);

		printf("\nUsername: %s\n",p->username);
		printf("Score: %d\n", p->score);
		printf("Last played: ");
		printf("(%d.%d.%d) - %d:%d\n\n", p->tm.tm_mday, p->tm.tm_mon + 1, p->tm.tm_year + 1900, p->tm.tm_hour, p->tm.tm_min);

		free(p);
	}

	else printf("Player not found.\n");
}

int addAForbiddenUsername()
{
	char *name = NULL;
	name = getUsername();

	FILE *forbname=NULL;
	forbname = openFileForbiddenNames();

	fprintf(forbname, "\n%s", name);

	printf("\nForbidden username successfully added!");
	return EXIT_SUCCESS;
}

int closeAllRanking(FILE *usernamestxt, FILE *forbiddenusernamestxt, char **usernames, char **forbiddenusernames,int namescount,int forbiddennamescount)
{
	for (int i = 0; i < namescount; i++)
		free(*(usernames + i));
	free(usernames);

	for (int i = 0; i < forbiddennamescount; i++)
		free(*(forbiddenusernames+i));

	free(forbiddenusernames);
	fclose(usernamestxt);
	fclose(forbiddenusernamestxt);	
	
	return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//LINKED LIST FUNCTIONS

void printRanksinLL(FILE *usernamestxt,char **usernames,int namecount)
{
	PLAYER *head = NULL;
	PLAYER *newR = NULL;

	PLAYER *p = NULL;
	p = allocatePlayer();
	
	for (int i = 0; i < namecount-1; i++)
	{
		p = readScore_FromBin(p, *(usernames + i));
		head = MakeAList(&head, *p);
		newR = addToEnd(&head, *p);
	}
	printList(head);
	eraseList(head);
	
	free(p);
	fclose(usernamestxt);
}

PLAYER* MakeAList(PLAYER **head, PLAYER readP)								//readP is the structure of player currently read from memory
{
	PLAYER *temp = NULL;
	if (*head == NULL)
	{
		*head = (PLAYER*)calloc(1, sizeof(PLAYER));
		if (*head == NULL)
		{
			perror("Couldn't allocate memory for '*head'.\n");
			exit(EXIT_FAILURE);
		}
		strcpy((*head)->username, readP.username);
		(*head)->score = readP.score;
		(*head)->tm = readP.tm;
	}

	return *head;
}

PLAYER* addToStart(PLAYER **head, PLAYER readP)
{
	PLAYER *newR, *temp;
	newR = (PLAYER*)calloc(1, sizeof(PLAYER));
	if (newR == NULL)
	{
		perror("Couldn't allocate memory for '*newR'.\n");
		exit(EXIT_FAILURE);
	}
	strcpy(newR->username, readP.username);
	newR->score = readP.score;
	newR->tm = readP.tm;

	if (*head == NULL)
	{
		perror("List is empty.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		newR->next = *head;
		*head = newR;
	}
	return *head;
}

PLAYER* addToEnd(PLAYER **head, PLAYER readP)
{
	int counter = 0;
	PLAYER *newR, *temp = NULL;
	newR = (PLAYER*)calloc(1, sizeof(PLAYER));
	if (newR == NULL)
	{
		perror("Couldn't allocate memory for 'newR'.\n");
		exit(EXIT_FAILURE);

	}

	strcpy(newR->username, readP.username);
	newR->score = readP.score;
	newR->tm = readP.tm;

	if (*head == NULL)
	{
		perror("List is empty\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		for (temp = *head; temp->next != NULL; temp = temp->next)counter++;
		;																				//passing through list looking for the last element
		temp->next = newR;
	}
	return *head;
}


int printList(PLAYER *head)
{
	int counter = 0;
	PLAYER *temp = NULL;
	temp = head;

	if (head != NULL)
	{
		do
		{
			printf("Username: %s\n", temp->username);
			Sleep(50);
			printf("Score: %d\n", temp->score);
			Sleep(50);
			printf("Last played: ");
			Sleep(50);
			printf("(%d.%d.%d) - %d:%d\n\n", temp->tm.tm_mday, temp->tm.tm_mon + 1, temp->tm.tm_year + 1900, temp->tm.tm_hour, temp->tm.tm_min);
			Sleep(50);
			counter++;
			temp = temp->next;

		} while (temp != NULL);
		printf("\n");
		return counter;
	}
	else {
		printf("List is empty\n");
		return 0; 
	}
}

PLAYER* eraseList(PLAYER *head)
{
	PLAYER *temp = NULL;

	while (head)
	{
		temp = head;
		head = (head)->next;
		free(temp);
	}
	return NULL;
}
