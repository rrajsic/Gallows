#ifndef HEADERRANDOMWORDSFUNCTIONS_H
#define HEADERRANDOMWORDSFUNCTIONS_H

FILE * openFileRead();
FILE * openFileAppend();
int checkifFileOpen(FILE *ranWords);

char** allocateWords(FILE *ranWords, int wordcount, int maxlettercount);
char** initializeWords(FILE *ranWords, int wordcount, int maxletter);
int* allocateSum(FILE *ranWords, int wordcount);
int* initializeSum(FILE *ranWords, char **words, int wordcount);

int ranWordCount(FILE *ranWords);
int maxLetterCount(FILE *ranWords);

void sortWordsby_Alphabet(char***words, int wordcount);							//Basic strcmp comparing
void sortWordsBy_Size(char***words, int **sum, int wordcount);					//Bubblesort algorithm
void swapWords(char *word_1, char *word_2);

char* getWord();
void addWordToFile(FILE *ranWords);
void findWord(char**words, int wordcount);

void printWords(char **words, int wordcount,int maxletter);
char** printWordsFromFile(FILE *ranWords,int wordcount,int printoption);

int closeAll(FILE *ranWords,char **words,int *sum,char *hiddenword,char *guesses, int wordcount);

#endif