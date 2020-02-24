/** @file */
#include "enumsStructsMacros.h"
#include "mapMemAndGen.h"
#include <stdio.h>

void dealocateMap(tile **(*bitmap), int gridSize) {
	for (int i = 0; i < gridSize; i++) {
		free((*bitmap)[i]);
	}
	free(*bitmap);
}


void allocateMap(tile **(*bitmap), int gridSize) {
	(*bitmap) = malloc(gridSize * sizeof(tile*));
	for (int i = 0; i < gridSize; i++) {
		(*bitmap)[i] = malloc(gridSize * sizeof(tile));
	}
}


void generateMap(tile** bitmap, int gridSize, int howManyBoxes, int howManyUpgrades) {
	static time_t tt;
	static int seedOnce = 0;
	if (!seedOnce) {
		srand(time(&tt));
		seedOnce++;
	}

	int upg = howManyUpgrades;
	int upgType;
	int x, y;
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			if (i % 2 && j % 2) {
				bitmap[i][j].type = pillarTile;
			}
			else {
				bitmap[i][j].type = pathTile;
			}
			bitmap[i][j].fireLayers = bitmap[i][j].upgrade = 0;
		}
	}
	for (int i = 0; i < howManyBoxes; i++) {
		x = rand() % gridSize;
		y = rand() % gridSize;
		if ((x < 2) && (y > gridSize - 3)) { //miejsce dla gracza
			i--;
			continue;
		}
		if (x % 2 && y % 2) { //kolumna 
			i--;
			continue;
		}
		if (bitmap[x][y].type == boxTile) { //juz zajete
			i--;
			continue;
		}
		if (upg) {
			upg--;
			upgType = rand() % 100;
			if (upgType < 40) {
				bitmap[x][y].upgrade = fireRange;
			}
			else if (upgType < 80) {
				bitmap[x][y].upgrade = bombsAvalible;
			}
			else if (upgType < 90) {
				bitmap[x][y].upgrade = bombKick;
			}
			else {
				bitmap[x][y].upgrade = shield;
			}
		}

		bitmap[x][y].type = boxTile;
	}
}
