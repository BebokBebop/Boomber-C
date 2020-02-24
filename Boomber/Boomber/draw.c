/** @file */

#include "enumsStructsMacros.h"
#include "draw.h"
#include <GLFW\glfw3.h>
#include <stdlib.h>
#include "mapMemAndGen.h"

void initGrid(tile** bitmap, int gridSize, int howManyBoxes, int howManyUpgrades) {
	generateMap(bitmap, gridSize, howManyBoxes, howManyUpgrades);
}

void resetDrawStatics() {
	drawPortal(0, 0, 0, 0, 0, 0, 0, 1);
}

void setGlLists(int listArray[6], int gridSize) {
	listArray[0] = glGenLists(1);
	glNewList(listArray[0], GL_COMPILE);
	drawScoreboard();
	writeStaticData();
	glEndList();

	listArray[5] = glGenLists(1);
	glNewList(listArray[5], GL_COMPILE);
	drawGridBase(gridSize);
	glEndList();

	listArray[start] = glGenLists(1);
	glNewList(listArray[start], GL_COMPILE);
	drawPauseScreen();
	writePauseMessage(start);
	glEndList();

	listArray[stop] = glGenLists(1);
	glNewList(listArray[stop], GL_COMPILE);
	drawPauseScreen();
	writePauseMessage(stop);
	glEndList();

	listArray[gameOver] = glGenLists(1);
	glNewList(listArray[gameOver], GL_COMPILE);
	drawPauseScreen();
	writePauseMessage(gameOver);
	glEndList();

	listArray[won] = glGenLists(1);
	glNewList(listArray[won], GL_COMPILE);
	drawPauseScreen();
	writePauseMessage(won);
	glEndList();

}

void unSetGlList(int listArray[6]) {
	for (int i = 0; i < 5; i++) {
		glDeleteLists(listArray[i], 1);
		listArray[i] = 0;
	}
}

void drawGridBase(int gridSize) {

	glColor3f(BACKGROUND_COLOR); //tlo
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(-1, -1);
	glVertex2d(-1, 1);
	glVertex2d(1, 1);
	glVertex2d(1, -1);
	glEnd();


	double X = GRID_L_X; //polozenie mapy
	double Y = GRID_D_Y;

	double x = X;
	double y = Y;

	double stepX = 1.9 / gridSize * 2.0 / 3.0; //wielkosc X i Y kafelka 
	double stepY = 1.9 / gridSize;

	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			if (i % 2 && j % 2) {
				drawSquare(PILLAR_COLOR, x, y, stepX, stepY);
			}
			else {
				drawSquare(PATH_COLOR, x, y, stepX, stepY);
			}
			x += stepX;
		}
		y += stepY;
		x = X;
	}
	y = Y;
}

void drawGrid(tile** bitmap, int gridSize) {

	double X = GRID_L_X; //polozenie mapy
	double Y = GRID_D_Y;

	double x = X;
	double y = Y;

	// stosunek szerokosci do wysokosci jest forsowany na 3:2, wiec nie musze:
	//double stepX = size / gridSize / width; 
	//double stepY = size / gridSize / height;
	
	double stepX = 1.9 / gridSize * 2.0 / 3.0; //wielkosc X i Y kafelka 
	double stepY = 1.9 / gridSize;

	for (int j = 0; j < gridSize; j++) {
		for (int i = 0; i < gridSize; i++) {
			if (bitmap[i][j].type == pathTile || bitmap[i][j].type == bombTile || bitmap[i][j].type == enemyTile) {
				if (bitmap[i][j].upgrade) {
					switch (bitmap[i][j].upgrade) {
					case fireRange: {
						drawUpgrade(UPG_FIRE_RANGE_COLOR, x, y, stepX, stepY);
						break;
					}
					case bombsAvalible: {
						drawUpgrade(UPG_BOMBS_AVALIBLE, x, y, stepX, stepY);
						break;
					}
					case bombKick: {
						drawUpgrade(UPG_BOMB_KICK_COLOR, x, y, stepX, stepY);
						break;
					}
					case shield: {
						drawUpgrade(UPG_SHIELD_COLOR, x, y, stepX, stepY);
						break;
					}
					}
				}
			}
			else if (bitmap[i][j].type == boxTile) {
				drawSquare(BOX_COLOR, x, y, stepX, stepY);
			}
			else if (bitmap[i][j].type == fireTile) {
				bitmap[i][j].upgrade = 0;
				drawSquare(FIRE_COLOR, x, y, stepX, stepY);
			}
			else if (bitmap[i][j].type == firedBox) {
				drawSquare(FIRED_BOX_COLOR, x, y, stepX, stepY);
			}
			else if (bitmap[i][j].type == portalTile) {
				drawPortal(x, y, stepX, stepY, 0);
			}
			x += stepX;
		}
		y += stepY;
		x = X;
	}
	y = Y;
}

void drawBombs(Player *player, int gridSize) {
	double X = GRID_L_X; //polozenie mapy
	double Y = GRID_D_Y;

	double x = X;
	double y = Y;

	double sizeX = 1.9 / gridSize * 2.0 / 3.0; //wielkosc X i Y kafelka 
	double sizeY = 1.9 / gridSize;

	int newestID = player->newestBomb;
	int oldestID = player->oldestBomb;
	for (int i = oldestID; i % MAX_BOMBS != newestID; i++) {
		if (player->bombList[i % MAX_BOMBS].statFlag == placed) {
			drawBomb(x + player->bombList[i % MAX_BOMBS].coords.x*sizeX, y + player->bombList[i % MAX_BOMBS].coords.y*sizeY, sizeX, sizeY, &player->bombList[i % MAX_BOMBS]);
		}
	}
}

void drawBomb(double x, double y, double sizeX, double sizeY, Bomb* bomb) {
	double sizer;
	float heatColor;
	double timeDiff = glfwGetTime() - bomb->explosionTimer;

	heatColor = 0.5 + 0.45 * timeDiff / BOMB_EXPLODE_TIME; //bomba rosnie liniowo
	sizer = 0.20 * timeDiff / BOMB_EXPLODE_TIME;

	glColor3f(heatColor, 0.1, 0.1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x + sizeX * (0.25 - sizer), y + sizeY * (0.25 - sizer));
	glVertex2d(x + sizeX * (0.75 + sizer), y + sizeY * (0.25 - sizer));
	glVertex2d(x + sizeX * (0.75 + sizer), y + sizeY * (0.75 + sizer));
	glVertex2d(x + sizeX * (0.25 - sizer), y + sizeY * (0.75 + sizer));
	glEnd();
}

void drawUpgrade(float R, float G, float B, double x, double y, double sizeX, double sizeY) {
	glColor3f(R, G, B);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x + sizeX / 2, y + sizeY *(1-UPGRADE_CRYSTAL_SIZE));
	glVertex2d(x + sizeX * (1 - UPGRADE_CRYSTAL_SIZE), y + sizeY / 2);
	glVertex2d(x + sizeX / 2, y + sizeY * UPGRADE_CRYSTAL_SIZE);
	glVertex2d(x + sizeX * UPGRADE_CRYSTAL_SIZE, y + sizeY / 2);
	glEnd();
}

void drawSquare(float R, float G, float B, double x, double y, double sizeX, double sizeY) {
	glColor3f(R, G, B);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x, y);
	glVertex2d(x + sizeX, y);
	glVertex2d(x + sizeX, y + sizeY);
	glVertex2d(x, y + sizeY);
	glEnd();
}

void drawPortal(double x, double y, double sizeX, double sizeY, int reset) {
	static double lastTime = 0;
	double timeNow = glfwGetTime();
	double timeDiff = timeNow - lastTime;
	if (reset) {
		lastTime = 0;
		return;
	}
	if (timeDiff > PORTAL_SUCKING_SPEED) {
		lastTime = timeNow;
		timeDiff = 0;
	}

	glColor3f(PORTAL_COLOR);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x, y);
	glVertex2d(x + sizeX, y);
	glVertex2d(x + sizeX, y + sizeY);
	glVertex2d(x, y + sizeY);
	glEnd();

	double resizer = 0.5 * (timeDiff) / PORTAL_SUCKING_SPEED;
	glColor3f(PORTAL_COLOR_2);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x + sizeX * (	resizer / 3), y + sizeY * (		resizer / 3));
	glVertex2d(x + sizeX * (1 - resizer / 3), y + sizeY * (		resizer / 3));
	glVertex2d(x + sizeX * (1 - resizer / 3), y + sizeY * (1 -	resizer / 3));
	glVertex2d(x + sizeX * (	resizer / 3), y + sizeY * (1 -	resizer / 3));
	glEnd();
	glColor3f(PORTAL_COLOR_3);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x + sizeX * (	resizer), y + sizeY * (		resizer));
	glVertex2d(x + sizeX * (1 - resizer), y + sizeY * (		resizer));
	glVertex2d(x + sizeX * (1 - resizer), y + sizeY * (1 -	resizer));
	glVertex2d(x + sizeX * (	resizer), y + sizeY * (1 -	resizer));
	glEnd();
}

void drawPlayer(Player *player, int gridSize) {
	double color[3] = { PLAYER_COLOR };

	double sizeX = 1.9 / gridSize * 2.0 / 3.0; //wielkosc X i Y kafelka 
	double sizeY = 1.9 / gridSize;

	double x = GRID_L_X + player->coords.x*sizeX; 
	double y = GRID_D_Y + player->coords.y*sizeY;

	double timeNow = glfwGetTime();
	if (player->status == appearing) { //pojawia sie liniowo
		double resizer = (PLAYER_SIZE - 0.5) * (timeNow) / PLAYER_APPEAR_TIME;
		glColor3f(color[0] * (timeNow/PLAYER_APPEAR_TIME), color[1] * (timeNow / PLAYER_APPEAR_TIME), color[2] * (timeNow / PLAYER_APPEAR_TIME));
		glBegin(GL_TRIANGLE_FAN);
		glVertex2d(x + sizeX * (0.5 - resizer), y + sizeY * (0.5 - resizer));
		glVertex2d(x + sizeX * (0.5 + resizer), y + sizeY * (0.5 - resizer));
		glVertex2d(x + sizeX * (0.5 + resizer), y + sizeY * (0.5 + resizer));
		glVertex2d(x + sizeX * (0.5 - resizer), y + sizeY * (0.5 + resizer));
		glEnd();
		return;
	}

	//gracz juz jest na mapie - nie jest w trakcie pojawiania sie - model normalny

	double shieldFlash;
	if (player->upgrades[shield]) {
		drawSquare(SHIELD_COLOR, x, y, sizeX, sizeY);
	}
	else if ((shieldFlash = glfwGetTime() - player->brokenShieldTimer) < BROKEN_SHIELD_TIME) {
		int i;
		for (i = 0; shieldFlash > 0; i++) {
			shieldFlash -= i * 0.01;
		}
		if (i % 2) {
			drawSquare(SHIELD_COLOR, x, y, sizeX, sizeY);
		}
	}
	else {
		player->brokenShieldTimer = -1;
	}
	if (player->status != dead) {
		glColor3f(PLAYER_COLOR);
	}
	else {
		glColor3f(DEAD_PLAYER_COLOR);
	}

	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x + (1-	PLAYER_SIZE)*sizeX,	y + (1 - PLAYER_SIZE)*sizeY);
	glVertex2d(x +		PLAYER_SIZE *sizeX,	y + (1 - PLAYER_SIZE)*sizeY);
	glVertex2d(x +		PLAYER_SIZE *sizeX,	y +		 PLAYER_SIZE *sizeY);
	glVertex2d(x + (1 - PLAYER_SIZE)*sizeX,	y +		 PLAYER_SIZE *sizeY);
	glEnd();

	//switch (player->face) { //niezaimplementowane (rysowanie twarzy gracza
	//case happy: {
	//	break;
	//}
	//}
}

void drawScoreboard() {
	glColor3f(SCOREBOARD_BACKGROUND_COLOR);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(SCORE_BOARD_L_X, SCORE_BOARD_D_Y);
	glVertex2d(SCORE_BOARD_R_X, SCORE_BOARD_D_Y);
	glVertex2d(SCORE_BOARD_R_X, SCORE_BOARD_U_Y);
	glVertex2d(SCORE_BOARD_L_X, SCORE_BOARD_U_Y);
	glEnd();
}

void drawEnemyBlind(float R, float G, float B, double x, double y, double sizeX, double sizeY) {
	glColor3f(R, G, B);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x + 0.09*sizeX, y + 0.09*sizeY);
	glVertex2d(x + 0.91*sizeX, y + 0.09*sizeY);
	glVertex2d(x + 0.91*sizeX, y + 0.91*sizeY);
	glVertex2d(x + 0.09*sizeX, y + 0.91*sizeY);
	glEnd();
}

void drawEnemyRandom(float R, float G, float B, double x, double y, double sizeX, double sizeY) {
	glColor3f(R, G, B);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x + 0.09*sizeX, y + 0.09*sizeY);
	glVertex2d(x + 0.91*sizeX, y + 0.09*sizeY);
	glVertex2d(x + 0.91*sizeX, y + 0.91*sizeY);
	glVertex2d(x + 0.09*sizeX, y + 0.91*sizeY);
	glEnd();
}

void drawEnemychargerCalm(float R, float G, float B, double x, double y, double sizeX, double sizeY) {
	glColor3f(R, G, B);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x + 0.09*sizeX, y + 0.09*sizeY);
	glVertex2d(x + 0.91*sizeX, y + 0.09*sizeY);
	glVertex2d(x + 0.91*sizeX, y + 0.91*sizeY);
	glVertex2d(x + 0.09*sizeX, y + 0.91*sizeY);
	glEnd();
}

void drawEnemychargerUpset(float R, float G, float B, double x, double y, double sizeX, double sizeY) {
	glColor3f(R, G, B);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x + 0.09*sizeX, y + 0.09*sizeY);
	glVertex2d(x + 0.91*sizeX, y + 0.09*sizeY);
	glVertex2d(x + 0.91*sizeX, y + 0.91*sizeY);
	glVertex2d(x + 0.09*sizeX, y + 0.91*sizeY);
	glEnd();
}

void drawEnemy(double x, double y, double sizeX, double sizeY, Enemy* enemy) {
	switch (enemy->type) {
	case blind: {
		if (enemy->status == dying) {
			drawEnemyBlind(ENEMY1_DEAD_COLOR, x, y, sizeX, sizeY);
		}
		else {
			drawEnemyBlind(ENEMY1_COLOR, x, y, sizeX, sizeY);
		}
		break;
	}
	case random: {
		if (enemy->status == dying) {
			drawEnemyRandom(ENEMY2_DEAD_COLOR, x, y, sizeX, sizeY);
		}
		else {
			drawEnemyRandom(ENEMY2_COLOR, x, y, sizeX, sizeY);
		}
		break;
	}
	case charger: {
		if (enemy->status == rushing) {
			if (enemy->status == dying) {
				drawEnemychargerUpset(ENEMY3_DEAD_COLOR, x, y, sizeX, sizeY);
			}
			else {
				drawEnemychargerUpset(ENEMY3_2ND_PHASE_COLOR, x, y, sizeX, sizeY);
			}
			break;
		}
		else {
			if (enemy->status == dying) {
				drawEnemychargerCalm(ENEMY3_DEAD_COLOR, x, y, sizeX, sizeY);
			}
			else {
				drawEnemychargerCalm(ENEMY3_1ST_PHASE_COLOR, x, y, sizeX, sizeY);
			}
			break;
		}
		break;
	}
	}
}

void drawAllEnemies(Enemy enemyArray[MAX_ENEMIES_PER_MAP], int gridSize, int howMany) {
	double X = GRID_L_X; //polozenie mapy
	double Y = GRID_D_Y;

	double x = X;
	double y = Y;

	double sizeX = 1.9 / gridSize * 2.0 / 3.0; //wielkosc X i Y kafelka 
	double sizeY = 1.9 / gridSize;

	for (int i = 0; i < howMany; i++) {
		if (enemyArray[i].status != dead) {
			drawEnemy(x + enemyArray[i].coords.x*sizeX, y + enemyArray[i].coords.y*sizeY, sizeX, sizeY, &enemyArray[i]);
		}
	}
}

void drawPauseScreen() {
	glColor3f(PAUSE_SCREEN_COLOR);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(-1, -1);
	glVertex2d(-1, 1);
	glVertex2d(1, 1);
	glVertex2d(1, -1);
	glEnd();
}