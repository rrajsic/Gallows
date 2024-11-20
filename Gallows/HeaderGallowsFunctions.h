#ifndef HEADERGALLOWS_H
#define HEADERGALLOWS_H

char enterALetter();
char eneteringAGuess(char *guesses,int guessnum);
char* allocateGuesses(int numofguesses);

int randomNumber(int wordcount);					//this function extracts a random number using unsigned time
char* allocateHiddenWord(int maxletter);
char* initializeHiddenWord(char **words, int wordcount,int maxletter,int randomnumber);

char* switchLetter(char changedWord[], char guess, char **words,char *switchedword, int randomnumber,int *hits);

#endif