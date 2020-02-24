/** @file */

#include "enumsStructsMacros.h"
#include "player.h"
#include <stdlib.h>
#include <GLFW\glfw3.h>


void moveInADirectionAndKickIfPossibleAndCollectAnUpgrade(Direction dir, tile** bitmap, Player* player, int gridSize) {
	if (player->status != alive) { //dead and teleporting players dont move
		return;
	}

	int coordCheck;
	int vert;
	int horz;

	switch (dir) {
	case north: {
		vert = 1;
		horz = 0;
		coordCheck = player->coords.y;
		break;
	}
	case east: {
		vert = 0;
		horz = 1;
		coordCheck = player->coords.x;
		break;
	}
	case south: {
		vert = -1;
		horz = 0;
		coordCheck = player->coords.y;
		break;
	}
	case west: {
		vert = 0;
		horz = -1;
		coordCheck = player->coords.x;
		break;
	}
	}

	if (coordCheck + vert + horz < gridSize && coordCheck + vert + horz >= 0) {

		if (bitmap[player->coords.x + horz][player->coords.y + vert].type == bombTile && player->upgrades[bombKick] && (coordCheck + 2 * vert + 2 * horz < gridSize && coordCheck + 2 * vert + 2 * horz >= 0)) {// sprawdz tez czy kafelka jeden dalej jest wolna, jesli chcesz kopnac bombe
			if (bitmap[player->coords.x + 2 * horz][player->coords.y + 2 * vert].type == pathTile) {
				int currBombID = getBombID(player, player->coords.x + horz, player->coords.y + vert);
				player->bombList[currBombID].kickDirection = dir;
				player->bombList[currBombID].kickTimer = glfwGetTime();
				bitmap[player->coords.x + horz][player->coords.y + vert].type = pathTile;
			}
		}

		if (bitmap[player->coords.x + horz][player->coords.y + vert].type != boxTile
			&& bitmap[player->coords.x + horz][player->coords.y + vert].type != pillarTile
			&& bitmap[player->coords.x + horz][player->coords.y + vert].type != bombTile) {
			switch (bitmap[player->coords.x + horz][player->coords.y + vert].upgrade) {
			case fireRange: {
				player->upgrades[fireRange]++;
				break;
			}
			case bombsAvalible: {
				player->upgrades[bombsAvalible]++;
				break;
			}
			case bombKick: {
				player->upgrades[bombKick] = 1;
				break;
			}
			case shield: {
				player->upgrades[shield] = 1;
				player->brokenShieldTimer = -1;
				break;
			}
			default: break;
			}
			bitmap[player->coords.x + horz][player->coords.y + vert].upgrade = 0;
			player->coords.x += horz;
			player->coords.y += vert;
		}
	}
}

void initPlayer(Player* player, int gameTime, int gridSize) {
	player->coords.x = 1;
	player->coords.y = gridSize - 2;
	player->status = appearing;
	player->score = 0;
	player->timeLeft = gameTime + PLAYER_APPEAR_TIME;
	player->upgrades[fireRange] = 2;
	player->upgrades[bombKick] = 0;
	player->upgrades[shield] = 0;
	player->upgrades[bombsAvalible] = 1;
	player->brokenShieldTimer = -1;
	for (int i = 0; i < 10; i++) {
		player->bombList[i].statFlag = empty;
	}
	player->newestBomb = 0;
	player->oldestBomb = 0;
}

void resetPlayerStatics() {
	checkPlayer(NULL, NULL, 0, 1);
}

void reInitPlayer(Player* player, int gameTime, int gridSize) {
	player->coords.x = 1;
	player->coords.y = gridSize - 2;
	player->timeLeft = gameTime + PLAYER_APPEAR_TIME;
	player->status = appearing; //previous = advancing
	for (int i = 0; i < 10; i++) {
		if (player->bombList[i].statFlag != empty) {
			player->bombList[i].statFlag = empty;
			player->upgrades[bombsAvalible]++;
		}
	}
	player->newestBomb = 0;
	player->oldestBomb = 0;
}

void openPortal(tile** bitmap, int gridSize) {
	bitmap[gridSize / 2][gridSize / 2].type = portalTile;
}

void placeBomb(tile** bitmap, Player* player, int gridSize) {
	if (player->status != alive) {
		return;
	}

	if (player->upgrades[bombsAvalible]
		&& bitmap[player->coords.x][player->coords.y].type != bombTile
		&& bitmap[player->coords.x][player->coords.y].type != fireTile
		&& bitmap[player->coords.x][player->coords.y].type != enemyTile
		&& bitmap[player->coords.x][player->coords.y].type != pillarTile)
	{
		bitmap[player->coords.x][player->coords.y].type = bombTile;
		player->bombList[player->newestBomb].size = player->upgrades[fireRange];
		player->bombList[player->newestBomb].explosionTimer = glfwGetTime();
		player->bombList[player->newestBomb].coords.x = player->coords.x;
		player->bombList[player->newestBomb].coords.y = player->coords.y;
		player->bombList[player->newestBomb].statFlag = placed;
		player->bombList[player->newestBomb].kickDirection = 0;

		player->upgrades[bombsAvalible]--;
		player->newestBomb++;
		if (player->newestBomb >= MAX_BOMBS) {
			player->newestBomb -= MAX_BOMBS;
		}
	}
}

void placeBox(tile** bitmap, Player* player, int gridSize) {
	if (bitmap[player->coords.x][player->coords.y].type != bombTile && bitmap[player->coords.x][player->coords.y].type != fireTile) {
		bitmap[player->coords.x][player->coords.y].type = boxTile;
	}
}

void damagePlayer(Player* player) {
	if (player->upgrades[shield]) {
		player->upgrades[shield] = 0;
		player->brokenShieldTimer = glfwGetTime();
	}
	else if (glfwGetTime() - player->brokenShieldTimer > BROKEN_SHIELD_TIME) {
		player->status = dead;
	}
}

void checkPlayer(tile** bitmap, Player* player, int gameTime, int reset) {
	static double lastTime = -1;
	double timeNow = glfwGetTime();
	if (reset) {
		lastTime = -1;
		return;
	}

	if (player->status == appearing) {
		if (lastTime == -1) {
			lastTime = timeNow + PLAYER_APPEAR_TIME;
		}
		else {
			if (lastTime - timeNow <= 0) { //animacja pojawiania sie skonczyla
				player->status = alive;
				lastTime = -1;
			}
		}
	}
	else if (player->status != alive) { //nie nalezy sprawdzac gracza, ktory sie pojawia, jest martwy lub wszedl do portalu
		return;
	}

	if (bitmap[player->coords.x][player->coords.y].type == fireTile 
		|| bitmap[player->coords.x][player->coords.y].type == enemyTile
		|| bitmap[player->coords.x][player->coords.y].type == firedBox) {
		damagePlayer(player);
	}
	else if (bitmap[player->coords.x][player->coords.y].type == portalTile) {
		player->status = winning;
		player->score += 1000;
	}
	else if (player->timeLeft > 0) {
		player->timeLeft = gameTime - timeNow;
		if (player->timeLeft <= 0) {
			player->timeLeft = 0;
			lastTime = timeNow;
		}
	}
	else if (player->score >= 10) {
		if (timeNow  - lastTime > SCORE_DROP_FREQUENCY) {
			lastTime = timeNow;
			player->score *= (double)8.5/10;
		}
	}
	else if (timeNow - lastTime > SCORE_DROP_FREQUENCY) {
		player->score = 0;
		player->status = dead;
	}
}

int waitForGame_over() {
	static double wait = -1;
	if (wait == -1) {
		wait = glfwGetTime() + 2; //+GAME_OVER_TIME
	}
	if (wait - glfwGetTime() <= 0) {
		wait = -1;
		return 1;
	}
	return 0;
}

int waitForNextStageAndSumScore(Player* player) {
	static double wait = -1;

	if (player->timeLeft > 0) {
		if (wait == -1) {
			wait = glfwGetTime() + TIME_COUNT_SPEED;
		}
		else if (wait - glfwGetTime() <= 0) {
			player->score += 1;
			player->timeLeft -= 1;
			wait = -1;
		}
		return 0;
	}

	if (wait == -1) {
		wait = glfwGetTime() + 3;
	}
	else if (wait - glfwGetTime() <= 0) {
		wait = -1;
		return 1;
	}
	return 0;
}

void increaseBombFireRange(Player* player) {
	player->upgrades[fireRange]++;
}

void decreaseBombFireRange(Player* player) {
	if (player->upgrades[fireRange] > 2) {
		player->upgrades[fireRange]--;
	}
}

void increaseBombsAvalible(Player* player) {
	player->upgrades[bombsAvalible]++;
}

void decreaseBombsAvalible(Player* player) {
	if (player->upgrades[bombsAvalible] > 1) {
		player->upgrades[bombsAvalible]--;
	}
}

void shieldSwitch(Player* player) {
	if (player->upgrades[shield]) {
		player->upgrades[shield] = 0;
	}
	else {
		player->upgrades[shield] = 1;
		player->brokenShieldTimer = -1;
	}
}

void kickSwitch(Player* player) {
	if (player->upgrades[bombKick])
		player->upgrades[bombKick] = 0;
	else
		player->upgrades[bombKick] = 1;
}

