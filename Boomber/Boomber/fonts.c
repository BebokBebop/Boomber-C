#include"enumsStructsMacros.h"
#include"fonts.h"
#include<GLFW/glfw3.h>
#include "draw.h"
#include <stdio.h> 

void translateWord(sign **signs, char *word) {
	int wordSize = strlen(word);
	*signs = calloc(wordSize, sizeof(sign));
	for (int i = 0; i < wordSize; ++i) {
		switch (*word) { //literownik
		case '0': {
			int ncharacterArray[8][5] = {
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 1, 1 },
			{ 1, 0, 0, 1, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 1, 1, 0, 0, 1 },
			{ 1, 1, 0, 0, 1 },
			{ 0, 1, 1, 1, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case '1': {
			int ncharacterArray[8][5] = {
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 1, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 1, 1, 1, 1, 1 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case '2': {
			int ncharacterArray[8][5] = {
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 1, 1 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case '3': {
			int ncharacterArray[8][5] = {
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case '4': {
			int ncharacterArray[8][5] = {
			{ 0, 0, 0, 1, 1 },
			{ 0, 0, 1, 0, 1 },
			{ 0, 1, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 1 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case '5': {
			int ncharacterArray[8][5] = {
			{ 1, 1, 1, 1, 1},
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 1, 0 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case '6': {
			int ncharacterArray[8][5] = {
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case '7': {
			int ncharacterArray[8][5] = {
			{ 1, 1, 1, 1, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case '8': {
			int ncharacterArray[8][5] = {
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case '9': {
			int ncharacterArray[8][5] = {
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'S': {
			int ncharacterArray[8][5] = {
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'C': {
			int ncharacterArray[8][5] = {
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'O': {
			int ncharacterArray[8][5] = {
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'R': {
			int ncharacterArray[8][5] = {
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 1, 0, 0 },
			{ 1, 0, 0, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'E': {
			int ncharacterArray[8][5] = {
			{ 1, 1, 1, 1, 1 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 1, 1 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'T': {
			int ncharacterArray[8][5] = {
			{ 1, 1, 1, 1, 1 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'I': {
			int ncharacterArray[8][5] = {
			{ 0, 1, 1, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 1, 1, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'M': {
			int ncharacterArray[8][5] = {
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 0, 1, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case ' ': {
			int ncharacterArray[8][5] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'P': {
			int ncharacterArray[8][5] = {
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'A': {
			int ncharacterArray[8][5] = {
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 0, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'U': {
			int ncharacterArray[8][5] = {
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'D': {
			int ncharacterArray[8][5] = {
			{ 1, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'H': {
			int ncharacterArray[8][5] = {
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'L': {
			int ncharacterArray[8][5] = {
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 1, 1, 1, 1 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'G': {
			int ncharacterArray[8][5] = {
			{ 0, 1, 1, 1, 0 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0 },
			{ 1, 0, 1, 1, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 1, 1, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'V': {
			int ncharacterArray[8][5] = {
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case '!': {
			int ncharacterArray[8][5] = {
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'N': {
			int ncharacterArray[8][5] = {
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 0, 0, 1 },
			{ 1, 1, 0, 0, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 1, 0, 0, 1, 1 },
			{ 1, 0, 0, 1, 1 },
			{ 1, 0, 0, 0, 1 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case ':': {
			int ncharacterArray[8][5] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'W': {
			int ncharacterArray[8][5] = {
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 1, 1, 0, 1, 1 },
			{ 1, 0, 0, 0, 1 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		case 'Y': {
			int ncharacterArray[8][5] = {
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 0, 1, 0, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			};
			(*signs)[i] = calloc(8 * 5, sizeof(int));
			memcpy((*signs)[i], ncharacterArray, sizeof(ncharacterArray));
			break;
		}
		}
		word++;
	}
}

void writeStaticData() {
	double sizeX = (double)FONT_SIZE;
	double sizeY = (double)FONT_SIZE*1.5;

	sign* word;
	translateWord(&word, "SCORE");
	int length = 5;

	double X = SCORE_BOARD_L_X/2 + SCORE_BOARD_R_X/2  -  length * 6 * FONT_SIZE/2;
	double Y = 0.80;
	double x = X;
	double y = Y;
	
	for (int i = 0; i < length; ++i) { //narysuj dane slowo
		for (int bitX = 7; bitX >= 0; bitX--) {
			for (int bitY = 0; bitY < 5; bitY++) {
				if ((*(word[i]))[bitX][bitY]) {
					drawSquare(FONT_COLOR, x, y, sizeX, sizeY);
				}
				x += sizeX;
			}
			y += sizeY;
			x = X;
		}
		X = x += 6 * sizeX;
		y = Y;
	}
	for (int i = 0; i < length; i++) {
		free(word[i]);
	}
	free(word);


	translateWord(&word, "HIGHSCORE");
	length = 9;
	X = SCORE_BOARD_L_X / 2 + SCORE_BOARD_R_X / 2 - length * 6 * FONT_SIZE / 2;
	Y = 0.30;
	x = X;
	y = Y;
	for (int i = 0; i < length; ++i) { //narysuj dane slowo
		for (int bitX = 7; bitX >= 0; bitX--) {
			for (int bitY = 0; bitY < 5; bitY++) {
				if ((*(word[i]))[bitX][bitY]) {
					drawSquare(FONT_COLOR, x, y, sizeX, sizeY);
				}
				x += sizeX;
			}
			y += sizeY;
			x = X;
		}
		X = x += 6 * sizeX;
		y = Y;
	}
	for (int i = 0; i < length; i++) {
		free(word[i]);
	}
	free(word);

	translateWord(&word, "TIME");
	length = 4;
	X = SCORE_BOARD_L_X / 2 + SCORE_BOARD_R_X / 2 - length * 6 * FONT_SIZE / 2;
	Y = -0.20;
	x = X;
	y = Y;
	for (int i = 0; i < length; ++i) {
		for (int bitX = 7; bitX >= 0; bitX--) {
			for (int bitY = 0; bitY < 5; bitY++) {
				if ((*(word[i]))[bitX][bitY]) {
					drawSquare(FONT_COLOR, x, y, sizeX, sizeY);
				}
				x += sizeX;
			}
			y += sizeY;
			x = X;
		}
		X = x += 6 * sizeX;
		y = Y;
	}
}

void writeDynamicData(int highscore, int score, int timeLeft) {
	double sizeX = (double)FONT_SIZE;
	double sizeY = (double)FONT_SIZE*1.5;

	sign* word;
	char scoreChAr[5];
	if (score > 9999) {
		return;
	}
	sprintf(scoreChAr, "%d", score);

	translateWord(&word, scoreChAr);
	int length = strlen(scoreChAr);
	double X = SCORE_BOARD_L_X / 2 + SCORE_BOARD_R_X / 2 - length * 6 * FONT_SIZE / 2;
	double Y = 0.60;
	double x = X;
	double y = Y;
	for (int i = 0; i < length; ++i) {//narysuj dane slowo
		for (int bitX = 7; bitX >= 0; bitX--) {
			for (int bitY = 0; bitY < 5; bitY++) {
				if ((*(word[i]))[bitX][bitY]) {
					drawSquare(FONT_COLOR, x, y, sizeX, sizeY);
				}
				x += sizeX;
			}
			y += sizeY;
			x = X;
		}
		X = x += 6 * sizeX;
		y = Y;
	}

	for (int i = 0; i < 5; i++) {
		scoreChAr[i] = 0;
	}
	if (highscore > 9999) {
		return;
	}
	sprintf(scoreChAr, "%d", highscore);

	translateWord(&word, scoreChAr);
	length = strlen(scoreChAr);
	X = SCORE_BOARD_L_X / 2 + SCORE_BOARD_R_X / 2 - length * 6 * FONT_SIZE / 2;
	Y = 0.10;
	x = X;
	y = Y;
	for (int i = 0; i < length; ++i) {
		for (int bitX = 7; bitX >= 0; bitX--) {
			for (int bitY = 0; bitY < 5; bitY++) {
				if ((*(word[i]))[bitX][bitY]) {
					drawSquare(FONT_COLOR, x, y, sizeX, sizeY);
				}
				x += sizeX;
			}
			y += sizeY;
			x = X;
		}
		X = x += 6 * sizeX;
		y = Y;
	}

	char timeChAr[10];
	sprintf(timeChAr, "%d", timeLeft);
	translateWord(&word, timeChAr);
	length = strlen(timeChAr);
	X = SCORE_BOARD_L_X / 2 + SCORE_BOARD_R_X / 2 - length * 6 * FONT_SIZE / 2;
	Y = -0.40;
	x = X;
	y = Y;
	for (int i = 0; i < length; ++i) {
		for (int bitX = 7; bitX >= 0; bitX--) {
			for (int bitY = 0; bitY < 5; bitY++) {
				if ((*(word[i]))[bitX][bitY]) {
					drawSquare(FONT_COLOR, x, y, sizeX, sizeY);
				}
				x += sizeX;
			}
			y += sizeY;
			x = X;
		}
		X = x += 6 * sizeX;
		y = Y;
	}
}

void writePauseMessage(PauseScreenType pauseType) {
	sign* word;
	sign* word2;
	int length;
	int length2;
	switch (pauseType)
	{
	case none: return;
	case start: {
		translateWord(&word, "HELLO!");
		translateWord(&word2, "PRESS SPACE TO START");
		length = 6;
		length2 = 20;
		break;
	}
	case stop: {
		translateWord(&word, "GAME PAUSED");
		translateWord(&word2, "PRESS SPACE TO UNPAUSE");
		length = 11;
		length2 = 22;
		break;
	}
	case gameOver: {
		translateWord(&word, "GAME OVER!");
		translateWord(&word2, "PRESS SPACE TO RESTART");
		length = 10;
		length2 = 22;
		break;
	}
	case won: {
		translateWord(&word, "YOU WON!");
		translateWord(&word2, "PRESS SPACE TO GO ON");
		length = 8;
		length2 = 20;
		break;
	}
	default:
		return;
	}

	double X = -(length * 6 * FONT_SIZE) / 2;
	double Y = 0.6;
	double x = X;
	double y = Y;
	double sizeX = (double)FONT_SIZE;
	double sizeY = (double)FONT_SIZE*1.5;

	for (int i = 0; i < length; ++i) { //narysuj dany ciag znakow
		for (int bitX = 7; bitX >= 0; bitX--) {
			for (int bitY = 0; bitY < 5; bitY++) {
				if ((*(word[i]))[bitX][bitY]) {
					drawSquare(FONT_COLOR, x, y, sizeX, sizeY);
				}
				x += sizeX;
			}
			y += sizeY;
			x = X;
		}
		X = x += 6 * sizeX;
		y = Y;
	}
	for (int i = 0; i < length; i++) {
		free(word[i]);
	}
	free(word);

	X = -(length2 * 6 * FONT_SIZE / 2);
	Y = 0.3;
	x = X;
	y = Y;
	for (int i = 0; i < length2; ++i) {
		for (int bitX = 7; bitX >= 0; bitX--) {
			for (int bitY = 0; bitY < 5; bitY++) {
				if ((*(word2[i]))[bitX][bitY]) {
					drawSquare(FONT_COLOR, x, y, sizeX, sizeY);
				}
				x += sizeX;
			}
			y += sizeY;
			x = X;
		}
		X = x += 6 * sizeX;
		y = Y;
	}
	for (int i = 0; i < length2; i++) {
		free(word2[i]);
	}
	free(word2);
}

void writePauseMessageScore(int score) {
	sign* word;
	sign* word2;
	int length;
	int length2;
	translateWord(&word, "SCORE:");
	length = 6;
	double X = -(length * 6 * FONT_SIZE) / 2;
	double Y = 0.6;
	double x = X;
	double y = Y;
	double sizeX = (double)FONT_SIZE;
	double sizeY = (double)FONT_SIZE*1.5;

	
	char scoreChAr[5];
	if (score > 9999) {
		score = 9999;
		return;
	}
	sprintf(scoreChAr, "%d", score);
	translateWord(&word2, scoreChAr);
	length2 = strlen(scoreChAr);
	
	X = -((length2+length+1) * 6 * FONT_SIZE / 2);
	Y = 0.0;
	x = X;
	y = Y;
	for (int i = 0; i < length; ++i) {
		for (int bitX = 7; bitX >= 0; bitX--) {
			for (int bitY = 0; bitY < 5; bitY++) {
				if ((*(word[i]))[bitX][bitY]) {
					drawSquare(FONT_COLOR, x, y, sizeX, sizeY);
				}
				x += sizeX;
			}
			y += sizeY;
			x = X;
		}
		X = x += 6 * sizeX;
		y = Y;
	}
	for (int i = 0; i < length; i++) {
		free(word[i]);
	}
	free(word);

	x = X += sizeX;
	for (int i = 0; i < length2; ++i) {
		for (int bitX = 7; bitX >= 0; bitX--) {
			for (int bitY = 0; bitY < 5; bitY++) {
				if ((*(word2[i]))[bitX][bitY]) {
					drawSquare(FONT_COLOR, x, y, sizeX, sizeY);
				}
				x += sizeX;
			}
			y += sizeY;
			x = X;
		}
		X = x += 6 * sizeX;
		y = Y;
	}
	for (int i = 0; i < length2; i++) {
		free(word2[i]);
	}
	free(word2);

}