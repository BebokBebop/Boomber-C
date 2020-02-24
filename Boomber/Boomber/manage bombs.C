/** @file */

#include "enumsStructsMacros.h"
#include "manage bombs.h"
#include <stdlib.h>
#include <GLFW\glfw3.h>

int getBombID(Player *player, int x, int y) {
	int newestID = player->newestBomb;
	int oldestID = player->oldestBomb;
	for (int i = oldestID; i % MAX_BOMBS != newestID; i++) {
		if (player->bombList[i % MAX_BOMBS].coords.x == x ) {
			if (player->bombList[i % MAX_BOMBS].coords.y == y) {
				return i % MAX_BOMBS;
			}
		}
	}
	return NULL;
}

void moveTile(enum Direction dir, Bomb *currBomb, tile** bitmap, int gridSize) {
	int coordCheck;
	int vert;
	int horz;

	switch (dir) {
	case north: {
		vert = 1;
		horz = 0;
		coordCheck = currBomb->coords.y;
		break;
	}
	case east: {
		vert = 0;
		horz = 1;
		coordCheck = currBomb->coords.x;
		break;
	}
	case south: {
		vert = -1;
		horz = 0;
		coordCheck = currBomb->coords.y;
		break;
	}
	case west: {
		vert = 0;
		horz = -1;
		coordCheck = currBomb->coords.x;
		break;
	}
	}

	if (coordCheck + horz + vert < gridSize && coordCheck + horz + vert >= 0) {
		if (bitmap[currBomb->coords.x + horz][currBomb->coords.y + vert].type == pathTile) {
			bitmap[currBomb->coords.x + horz][currBomb->coords.y + vert].type = bombTile;
			bitmap[currBomb->coords.x][currBomb->coords.y].type = pathTile;
			currBomb->coords.x += horz;
			currBomb->coords.y += vert;
		}
		else if (bitmap[currBomb->coords.x + horz][currBomb->coords.y + vert].type == fireTile) {
			bitmap[currBomb->coords.x][currBomb->coords.y].type = pathTile;
			currBomb->coords.x += horz;
			currBomb->coords.y += vert;
			currBomb->kickDirection = 0;
		}
		else {
			currBomb->kickDirection = 0;
		}
	}
	else {
		currBomb->kickDirection = 0;
	}
}

void moveCheckExplodeAndCleanUpBombs(Player *player, tile** bitmap, int gridSize) {
	int newestID = player->newestBomb;
	int oldestID = player->oldestBomb;
	Bomb *currBomb = NULL;
	for (int i = oldestID; i % MAX_BOMBS != newestID; i++) {
		currBomb = &(player->bombList[i % MAX_BOMBS]);
		//move
		if (currBomb->statFlag == placed && currBomb->kickDirection) {
			if (glfwGetTime() - currBomb->kickTimer > 0.015) {
				currBomb->kickTimer = glfwGetTime();
				moveTile(currBomb->kickDirection, currBomb, bitmap, gridSize);
			}
		}
		//check
		if (player->bombList[i % MAX_BOMBS].statFlag == placed) {
			if (glfwGetTime() - player->bombList[i % MAX_BOMBS].explosionTimer > BOMB_EXPLODE_TIME) {
				player->bombList[i % MAX_BOMBS].statFlag = exploding;
			}
			if (bitmap[player->bombList[i % MAX_BOMBS].coords.x][player->bombList[i % MAX_BOMBS].coords.y].type == fireTile) {
				player->bombList[i % MAX_BOMBS].statFlag = exploding;
			}
		}
		if (player->bombList[i % MAX_BOMBS].statFlag == exploded) {
			if (glfwGetTime() - player->bombList[i % MAX_BOMBS].explosionTimer > FIRE_LINGERING_TIME) {
				player->bombList[i % MAX_BOMBS].statFlag = toBeCleaned;
			}
		}
		//explode
		if (player->bombList[i % MAX_BOMBS].statFlag == exploding) {
			explodeBombAddPoints(&player->bombList[i % MAX_BOMBS], player, bitmap, gridSize);
		}
		//clean
		if (player->bombList[i % MAX_BOMBS].statFlag == toBeCleaned) {
			cleanUp(i % MAX_BOMBS, player, bitmap);
		}
	}
}

void inline cleanTile(tile* currTile) {
	if (!--currTile->fireLayers) {
		currTile->type = pathTile;
	}
}

void inline moveBombData(Bomb* A, Bomb* B) {
	*B = *A;
}

void cleanUp(int currentBombID, Player *player, tile** bitmap) {
	int reach;
	int i = player->bombList[currentBombID].coords.x;
	int j = player->bombList[currentBombID].coords.y;

	reach = player->bombList[currentBombID].fireCross[0];
	for (int k = 1; k <= reach; k++) {
		cleanTile(&bitmap[i][j + k]);
	}

	reach = player->bombList[currentBombID].fireCross[1];
	for (int k = 1; k <= reach; k++) {
		cleanTile(&bitmap[i + k][j]);
	}

	reach = player->bombList[currentBombID].fireCross[2];
	for (int k = 1; k <= reach; k++) {
		cleanTile(&bitmap[i][j - k]);
	}

	reach = player->bombList[currentBombID].fireCross[3];
	for (int k = 1; k <= reach; k++) {
		cleanTile(&bitmap[i - k][j]);
	}

	cleanTile(&bitmap[i][j]);

	player->bombList[currentBombID].statFlag = empty;
	bitmap[i][j].type = pathTile;
	if (player->oldestBomb != currentBombID) {
		moveBombData(&player->bombList[player->oldestBomb], &player->bombList[currentBombID]);
	}
	player->oldestBomb++;

	if (player->oldestBomb >= MAX_BOMBS) {
		player->oldestBomb -= MAX_BOMBS;
	}
}

void inline spreadFire(tile *currTile, int *breaker) {
	if (currTile->type == pathTile || currTile->type == enemyTile) {
		currTile->type = fireTile;
		currTile->fireLayers++;
	}
	else if (currTile->type == boxTile) {
		currTile->type = firedBox;
		currTile->fireLayers++;
		*breaker = 1;
	}
	else if (currTile->type == bombTile) {
		currTile->type = fireTile;
		currTile->fireLayers++;
	}
	else if (currTile->type == pillarTile || currTile->type == firedBox) {
		*breaker = 2;
	}
	else if (currTile->type == fireTile) {
		currTile->fireLayers++;
	}
}

void explodeBombAddPoints(Bomb* bomb, Player *player, tile** bitmap, int gridSize) {
	bomb->statFlag = exploded;
	bomb->explosionTimer = glfwGetTime();

	tile *currTile;
	Bomb *currBomb;
	int breaker;
	int i = 1;

	if (player->upgrades[bombsAvalible] < MAX_BOMBS) {
		player->upgrades[bombsAvalible]++;
	}

	bitmap[bomb->coords.x][bomb->coords.y].type = fireTile;
	bitmap[bomb->coords.x][bomb->coords.y].fireLayers++;
	for (i = 1; i < bomb->size; i++) {
		if (bomb->coords.y + i >= gridSize) {
			breaker = 1;
			break;
		}
		breaker = 0;
		spreadFire(&bitmap[bomb->coords.x][bomb->coords.y + i], &breaker);
		if (breaker == 1) { //napotkal box
			player->score += 10;
			i++;
			break;
		}
		else if (breaker == 2) { //napotkal pillar
			break;
		}
	}
	bomb->fireCross[0] = i-1;

	for (i = 1; i < bomb->size; i++) {
		if (bomb->coords.x + i >= gridSize) {
			breaker = 1;
			break;
		}
		breaker = 0;
		spreadFire(&bitmap[bomb->coords.x + i][bomb->coords.y], &breaker, player);
		if (breaker == 1) {//napotkal box
			player->score += 10;
			i++;
			break;
		}
		else if (breaker == 2) {
			break;
		}
	}
	bomb->fireCross[1] = i-1;

	for (i = 1; i < bomb->size; i++) {
		if (bomb->coords.y - i < 0) {
			breaker = 1;
			break;
		}
		breaker = 0;
		spreadFire(&bitmap[bomb->coords.x][bomb->coords.y - i], &breaker, player);
		if (breaker == 1) {//napotkal box
			player->score += 10;
			i++;
			break;
		}
		else if (breaker == 2) {
			break;
		}
	}
	bomb->fireCross[2] = i-1;

	for (i = 1; i < bomb->size; i++) {
		if (bomb->coords.x - i < 0) {
			breaker = 1;
			break;
		}
		breaker = 0;
		spreadFire(&bitmap[bomb->coords.x - i][bomb->coords.y], &breaker, player);
		if (breaker == 1) {
			player->score += 10; //napotkal box
			i++;
			break;
		}
		else if (breaker == 2) {
			break;
		}
	}
	bomb->fireCross[3] = i-1;

}

