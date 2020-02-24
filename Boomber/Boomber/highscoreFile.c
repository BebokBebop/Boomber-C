/** @file */

#include<stdio.h>

int getHighscore(FILE *in) {
	char buffer[16]; // HIGHSCORE:_XXXX\0
	fread(buffer, 15, sizeof(char), in);

	int highscore = atoi(buffer+11);
	return highscore;
}

void setHighscore(int score, FILE*out) {
	char buffer[16] = "HIGHSCORE: ";
	buffer[15] = '\0';
	sprintf(buffer + 11,"%d", score); // HIGHSCORE:_XXXX\0
	fwrite(buffer, sizeof(char), strlen(buffer), out);
}