/** @file */

#include "enumsStructsMacros.h"
#include "Enemies.h"
#include <stdlib.h>
#include <GLFW/glfw3.h>


void initEnemies(Enemy enemyArray[MAX_ENEMIES_PER_MAP], tile* bitmap, int howMany, int gridSize) {
	dropEnemies(enemyArray, bitmap, howMany, gridSize);
}

void resetEnemyStatics() {
	manageEnemiesAndScore(NULL, NULL, NULL, 0, 0, 1);
}

void addEnemy(Enemy enemyArray[MAX_ENEMIES_PER_MAP], int ID, EnemyType type, XY coords, Direction dir) {
	enemyArray[ID].coords = coords;
	enemyArray[ID].direction = dir;
	enemyArray[ID].status = calm;
	enemyArray[ID].type = type;
}

void moveBlind(Enemy *enemy, tile** bitmap, int gridSize) {
	static int iteration = 0;
	static time_t tt;
	static int seedOnce = 0;
	if (!seedOnce) {
		srand(time(&tt));
		seedOnce++;
	}

	int moveReturn = moveEnemy(enemy, 0, bitmap, gridSize);
	if (moveReturn == 1) { //udalo sie ruszyc, zresetuj iteracje i wroc
		iteration = 0;
		return;
	}
	else if (moveReturn == 2) {
		enemy->direction = rand()%4 + 1; //specjalny mechanizm reakcji na spotkanie innego przeciwnika - inaczej moga poruszac sie w logiczny, ale nieintuicyjny dla gracza sposob albo w bardzo rzadkich przypadkach moga utknac
		iteration = 0;
		return;
	}

	if (iteration == 0) {
		enemy->direction--;
		if (!enemy->direction) {
			enemy->direction = west;
		}
	}
	else if (iteration == 1) {
		enemy->direction--;
		if (!enemy->direction) {
			enemy->direction = west;
		}
		enemy->direction--;
		if (!enemy->direction) {
			enemy->direction = west;
		}
	}
	else if (iteration == 2) {
		enemy->direction++;
		if (enemy->direction == 5) {
			enemy->direction = north;
		}
	}
	else {
		iteration = 0;
		return;
	}
	iteration++;
	moveBlind(enemy, bitmap, gridSize);
}

void moveRandom(Enemy *enemy, tile** bitmap, int gridSize) {
	static time_t tt;
	static int seedOnce = 0;
	if (!seedOnce) {
		srand(time(&tt));
		seedOnce++;
	}
	for (int i = RANDOM_TRIALS; i >= 0; i--) {
		enemy->direction = rand() % 4 + 1;
		if (moveEnemy(enemy, 0, bitmap, gridSize) == 1) { 
			break;
		}
	}
}

int pointTowardsPlayerIfPossible(Enemy* enemy, Player *player) {
	if (player->brokenShieldTimer != -1 || player->status == dead) {
		return 0;
	}
	if (enemy->coords.x % 2 == 0) {
		if (enemy->coords.x == player->coords.x) {
			if (enemy->coords.y > player->coords.y) {
				enemy->direction = south;
			}
			else {
				enemy->direction = north;
			}
			return 1;
		}
	}
	if (enemy->coords.y % 2 == 0) {
		if (enemy->coords.y == player->coords.y) {
			if (enemy->coords.x > player->coords.x) {
				enemy->direction = west;
			}
			else {
				enemy->direction = east;
			}
			return 1;
		}
	}
	return 0;
}

void moveCharger(Enemy *enemy, Player *player, tile** bitmap, int gridSize) {
	pointTowardsPlayerIfPossible(enemy, player);
	if (moveEnemy(enemy, 1, bitmap, gridSize) == 0) {
		enemy->status = calm;
	}
}

int moveEnemy(Enemy* enemy, int charge, tile** bitmap, int gridSize) {
	int vert;
	int horz;
	int coordCheck;
	switch (enemy->direction) {
	case north: {
		vert = 1;
		horz = 0;
		coordCheck = enemy->coords.y;
		break;
	}
	case east: {
		vert = 0;
		horz = 1;
		coordCheck = enemy->coords.x;
		break;
	}
	case south: {
		vert = -1;
		horz = 0;
		coordCheck = enemy->coords.y;
		break;
	}
	case west: {
		vert = 0;
		horz = -1;
		coordCheck = enemy->coords.x;
		break;
	}
	}

	if (coordCheck + vert + horz < gridSize && coordCheck + vert + horz >= 0) {
		if (bitmap[enemy->coords.x + horz][enemy->coords.y + vert].type == pathTile
			|| (charge && bitmap[enemy->coords.x + horz][enemy->coords.y + vert].type == boxTile))
		{
			bitmap[enemy->coords.x + horz][enemy->coords.y + vert].upgrade = 0;
			bitmap[enemy->coords.x + horz][enemy->coords.y + vert].type = enemyTile;

			bitmap[enemy->coords.x][enemy->coords.y].type = pathTile;
			enemy->coords.x += horz;
			enemy->coords.y += vert;
			bitmap[enemy->coords.x][enemy->coords.y].type = enemyTile;

			return 1;
		}
		else if (bitmap[enemy->coords.x + horz][enemy->coords.y + vert].type == fireTile
			|| (charge && bitmap[enemy->coords.x + horz][enemy->coords.y + vert].type == firedBox)) {
			bitmap[enemy->coords.x][enemy->coords.y].type = pathTile;
			enemy->coords.x += horz;
			enemy->coords.y += vert;
			return 1;
		}
		else if (bitmap[enemy->coords.x + horz][enemy->coords.y + vert].type == enemyTile) {
			return 2;
		}
	}
	return 0;
}

int manageEnemiesAndScore(Enemy enemyArray[MAX_ENEMIES_PER_MAP], Player* player, tile** bitmap, int howMany, int gridSize, int reset) {
	static double lastMoveTime1 = 0;
	static double lastMoveTime2 = 0;
	static double lastMoveTime3 = 0;
	if (reset) {
		lastMoveTime1 = lastMoveTime2 = lastMoveTime3 = 0;
		return;
	}

	int alldead = 1;
	int blindMove = 0; //czy mozna poruszyc przeciwnika typu blind
	int randomMove = 0; //czy mozna poruszyc przeciwnika typu random
	int chargerMove = 0; //czy mozna poruszyc przeciwnika typu charger
	double timeNow = glfwGetTime();

	if (timeNow - lastMoveTime1 > ENEMY1_SPEED) {
		blindMove = 1;
	}
	if (timeNow - lastMoveTime2 > ENEMY2_SPEED) {
		randomMove = 1;
	}
	if (timeNow - lastMoveTime3 > ENEMY3_SPEED) {
		chargerMove = 1;
	}

	for (int i = 0; i < howMany; i++) {
		if (enemyArray[i].status != dead && enemyArray[i].status != dying) {
			if (bitmap[enemyArray[i].coords.x][enemyArray[i].coords.y].type == fireTile) {
				enemyArray[i].rottingTime = ENEMY_ROT_TIME + glfwGetTime();
				enemyArray[i].status = dying;
				player->score += 100;
			}
			else {
				alldead = 0;
				switch (enemyArray[i].type) {
				case blind: {
					if (blindMove) {
						moveBlind(&enemyArray[i], bitmap, gridSize);
						lastMoveTime1 = timeNow;
					}
					break;
				}
				case random: {
					if (randomMove) {
						moveRandom(&enemyArray[i], bitmap, gridSize);
						lastMoveTime2 = timeNow;
					}
					break;
				}
				case charger: {
					if (pointTowardsPlayerIfPossible(&enemyArray[i], player)) {
						enemyArray[i].status = rushing;
					}
					if (enemyArray[i].status == rushing) {
						if (chargerMove) {
							moveCharger(&enemyArray[i], player, bitmap, gridSize);
							lastMoveTime3 = timeNow;
						}
					}
					else if (blindMove) {
						moveBlind(&enemyArray[i], bitmap, gridSize);
						lastMoveTime1 = timeNow;
					}
					break;
				}
				}
			}

		} 

		if (enemyArray[i].status == dying) {
			if (enemyArray[i].rottingTime - glfwGetTime() < 0) {
				enemyArray[i].status = dead;
			}
		}
	}
	return alldead;
}

void dropEnemies(Enemy enemyArray[MAX_ENEMIES_PER_MAP], tile** bitmap, int howMany, int gridSize) {
	time_t tt;
	srand(time(&tt));
	int x, y;
	for (int i = 0; i < howMany; i++) {
		x = rand() % gridSize;
		y = rand() % gridSize;
		if ((x < 1) || (y > gridSize - 2)) { //miejsce dla gracza
			i--;
			continue;
		}
		if (x % 2 && y % 2) { //kolumna 
			i--;
			continue;
		}
		if (bitmap[x][y].type == boxTile || bitmap[x][y].type == enemyTile) { //juz zajete
			i--;
			continue;
		}
		bitmap[x][y].type = enemyTile;
		XY coords = { x,y };
		addEnemy(enemyArray, i, rand() % 3, coords, rand() % 4 + 1);
	}
}
