/** @file */

#include <GLFW\glfw3.h>
#include <stdio.h>
#include "enumsStructsMacros.h"
#include "draw.h"
#include "player.h"
#include "manage bombs.h"
#include "Enemies.h"
#include "fonts.h"
#include "highscoreFile.h"
#include "TestArg.h"
#include "mapMemAndGen.h"

/** Pauzuje gre i zapisuje aktualny czas
* @param pauseSetter Wskaznik na typ pauzy. Sluzy do ustawienia zmiennej statycznej wewnatrz funkcji.
* @param dTimeSetter Wskaznik na zmienna pamietajaca czas gry sprzed pauzy. Sluzy do ustawienia zmiennej statycznej wewnatrz funkcji.
*/
void pauseGame(PauseScreenType *pauseSetter, double* dTimeSetter) {
	static PauseScreenType *pause = NULL;
	static double *dTime = NULL;
	if (dTime == NULL) { //przypadek sprzed inicjalizacji
		dTime = dTimeSetter;
		pause = pauseSetter;
		return;
	}
	if (*pause != none) {
		return;
	}
	*pause = stop;
	*dTime = glfwGetTime();
}

/** Wylacza pauze gry i ustawia aktualny czas na czas sprzed pauzy
* @param pauseSetter Wskaznik na typ pauzy. Sluzy do ustawienia zmiennej statycznej wewnatrz funkcji.
* @param dTimeSetter Wskaznik na zmienna pamietajaca czas gry sprzed pauzy. Sluzy do ustawienia zmiennej statycznej wewnatrz funkcji.
* @return 1 jesli udalo sie wylaczyc pauze lub 0 jesli pauzy nie bylo
*/
int unPauseGame(PauseScreenType *pauseSetter, double* dTimeSetter) {
	static PauseScreenType *pause = NULL;
	static double *dTime = NULL;
	if (dTime == NULL) {
		dTime = dTimeSetter;
		pause = pauseSetter;
		return 0;
	}
	if (*pause == none) {
		return 0;
	}
	*pause = none;
	glfwSetTime(*dTime);
	return 1;
}

/** Wywoluje odpowiednie funkcje odpowiadajace wcisnieciu odpowiednich klawiszy
* @param window wskaznik na strukture okna glfw.
* @param key Jaki klawisz.
* @param scancode
* @param action Akcja klawisza (nacisniety czy puszczony).
* @param mods 
* @param bitmap wskaznik na wskaznik na mape gry. Sluzy do ustawienia zmiennych statycznych wewnatrz funkcji)
* @param playerSetter wskaznik gracza. Sluzy do ustawienia zmiennych statycznych wewnatrz funkcji)
* @param debugModeSetter wskaznik zmienna ustawiajaca debugMode gry. Sluzy do ustawienia zmiennych statycznych wewnatrz funkcji)
* @param gridSizeSetter wskaznik zmienna przechowujaca wielkosc mapy. Sluzy do ustawienia zmiennych statycznych wewnatrz funkcji)
*/
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods,
	tile*** bitmapSetter, Player* playerSetter, int *debugModeSetter, int *gridSizeSetter)
{
	static int bitmapPointerSet = 0;
	static Player *player;
	static tile**(*bitmap);
	static int *debugMode;
	static int *gridSize;
	if (!bitmapPointerSet) {
		bitmap = bitmapSetter;
		player = playerSetter;
		debugMode = debugModeSetter;
		gridSize = gridSizeSetter;
		bitmapPointerSet = 1;
		return;
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		moveInADirectionAndKickIfPossibleAndCollectAnUpgrade(north, *bitmap, player, *gridSize);
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		moveInADirectionAndKickIfPossibleAndCollectAnUpgrade(south, *bitmap, player, *gridSize);
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		moveInADirectionAndKickIfPossibleAndCollectAnUpgrade(east, *bitmap, player, *gridSize);
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		moveInADirectionAndKickIfPossibleAndCollectAnUpgrade(west, *bitmap, player, *gridSize);
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		if (!unPauseGame(NULL,NULL)) {
			placeBomb(*bitmap, player, *gridSize);
		}
	}
	else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		pauseGame(NULL,NULL);
	}
	else if (*debugMode) {
		if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) {
			placeBox(*bitmap, player, *gridSize);
		}
		else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
			increaseBombFireRange(player);
		}
		else if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_PRESS) {
			decreaseBombFireRange(player);
		}
		else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
			shieldSwitch(player);
		}
		else if (key == GLFW_KEY_K && action == GLFW_PRESS) {
			kickSwitch(player);
		}
		else if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS) {
			increaseBombsAvalible(player);
		}
		else if (key == GLFW_KEY_RIGHT_ALT && action == GLFW_PRESS) {
			decreaseBombsAvalible(player);
		}
		else if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
			openPortal(*bitmap, *gridSize);
		}
	}
}

/** Wypisuje do konsoli blad.
* @param error numer bledu
* @param description opis bledu
*/
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

/** Ustawia wartosci domyslne przekazanym zmiennym, jesli nie zostaly ustawione.
* @param[out] howManyEnemies Ile ma sie znajdowac przeciwnikow na mapie.
* @param[out] howManyBoxes Ile ma sie znajdowac pudelek na mapie.
* @param[out] howManyUpgrades Ile ma sie znajdowac ulepszen na mapie.
* @param[out] gridSize wielkosc mapy
* @param[out] gameTime czas gry
* @param[out] debugMode zmienna ustawiajaca debugMode gry
*/
void setDefaultsIfNecessary(int *howManyEnemies, int *howManyBoxes, int *howManyUpgrades, int *gridSize, int *gameTime, int *debugMode) {
	if (*gridSize == -1) {
		*gridSize = DEFAULT_GRID_SIZE;
	}
	else if (*gridSize > MAX_GRID_SIZE) {
		*gridSize = MAX_GRID_SIZE;
	}
	if (*gameTime == -1) {
		*gameTime = DEFAULT_GAME_TIME;
	}
	if (*debugMode == -1) {
		*debugMode = DEFAULT_DEBUG_MODE;
	}
	if (*howManyEnemies == -1) {
		if (gridSize != DEFAULT_GRID_SIZE) {
			*howManyEnemies = (0.42 * *gridSize* *gridSize)/5;
		}
		else {
			*howManyEnemies = DEFAULT_ENEMIES_COUNT;
		}
	}
	if (*howManyEnemies > MAX_ENEMIES_PER_MAP) {
		*howManyEnemies = MAX_ENEMIES_PER_MAP;
	}
	if (*howManyBoxes > 0.75 * *gridSize * *gridSize - *howManyEnemies || *howManyBoxes == -1) {
		*howManyBoxes = (0.6 * *gridSize * *gridSize) / 1.8;
	}
	if (*howManyUpgrades == -1) {
		*howManyUpgrades = *howManyBoxes / 5;
	}
}

/** Inicjalizuje gre oraz ustawia statyczne zmienne w konkretnych funkcjach
* @param enemy wskaznik na przeciwnika do przesuniecia
* @param bitmap wskaznik na wskaznik na mape gry
* @param pauseType Wskaznik na typ pauzy. Sluzy do ustawienia zmiennej statycznej wewnatrz funkcji.
* @param dTime Wskaznik na zmienna pamietajaca czas gry sprzed pauzy. Sluzy do ustawienia zmiennej statycznej wewnatrz funkcji.
* @param player wskaznik na gracza
* @param howManyEnemies Ile ma sie znajdowac przeciwnikow na mapie.
* @param howManyBoxes Ile ma sie znajdowac pudelek na mapie.
* @param howManyUpgrades Ile ma sie znajdowac ulepszen na mapie.
* @param gridSize wielkosc mapy
* @param gameTime czas gry
* @param debugMode zmienna ustawiajaca debugMode gry
* @param[out listArray Tablica przechowujaca indeksy glList.
*/
void init(Enemy enemyArray[MAX_ENEMIES_PER_MAP], tile**(*bitmap),
	PauseScreenType *pauseType, double *dTime, Player* player, int howManyEnemies,
	int howManyBoxes, int howManyUpgrades, int *gridSize, int gameTime, int *debugMode, int listArray[6]) {
	if (*bitmap == NULL) {
		allocateMap(bitmap, *gridSize);
	}
	glfwSetTime(0.0);
	key_callback(NULL, 0, 0, 0, 0, bitmap, player, debugMode, gridSize); //aby uniknac globalnych zmiennych, musze ustawic je statycznie w funkcji callback
	initGrid(*bitmap, *gridSize, howManyBoxes, howManyUpgrades);
	initPlayer(player, gameTime, *gridSize);
	initEnemies(enemyArray, *bitmap, howManyEnemies, *gridSize);
	pauseGame(pauseType, dTime);
	unPauseGame(pauseType, dTime);
	setGlLists(listArray, *gridSize);
}

/** Wywoluje funkcje resetujace wszystkie funkcje statyczne oraz resetuje czas
* @param[out] dTime wskaznik na aktualny czas gry
*/
void resetTimes(double *dTime) {
	glfwSetTime(0);
	resetEnemyStatics();
	resetDrawStatics();
	resetPlayerStatics();
	*dTime = 0;
}


int main(int argc, char** argv) {
	Enemy enemyArray[MAX_ENEMIES_PER_MAP]; /* tablica przechowujaca dane wszystkich przeciwnikow*/
	Player player;			/* struktura przechowujaca dane gracza*/
	tile** bitmap = NULL; /* wskaznik na dwuwymiarowa tablice, ktora reprezentowac bedzie plansze gry*/
	PauseScreenType pauseType = start;
	int listArray[6] = { 0 } /* Przechowuje indeksy glList. Jest ich dokladnie 6*/;

	//zmienne do glownej petli
	int score = 0;
	int portalOpened = 0;
	int highscore = 0;
	int width, height;
	double dTime; // po pauzie przywraca sie czas sprzed pauzy

	//zmienne do ustawienia parametrycznie
	int howManyEnemies = -1;
	int howManyBoxes = -1;
	int howManyUpgrades = -1;
	int gridSize = -1;
	int gameTime = -1;
	int debugMode = -1;
	int helpSwitch = 0;

	//wczytaj z parametrow
	char *errorZwrot = check_param(argc, argv, &howManyEnemies, &howManyBoxes, &howManyUpgrades, 
		&gridSize, &gameTime, &debugMode, &helpSwitch);
	
	//czy parametr -help / -h zostal uzyty
	if (helpSwitch) {
		printf("%s", errorZwrot);
		exit(0);
	}
	
	//ktoras zmienna nieustawiona parametrem
	setDefaultsIfNecessary(&howManyEnemies, &howManyBoxes, &howManyUpgrades, &gridSize, &gameTime, &debugMode);

	//wyswietl ewentualne bledy w parametrach
	if (errorZwrot[0] != 0) {
		error_callback(0, errorZwrot);
	}

	//wczytaj highscore z pliku jesli sie da
	FILE* file = fopen("high score.txt", "r");
	if (!file) {
		file = fopen("high score.txt", "w");
		highscore = -1;
	}
	if (highscore == -1) {
		highscore = 0;
	}
	else {
		highscore = getHighscore(file);
	}
	fclose(file);

	//inicjalizacja glfw i ustawienie odpowiednich funkcji / wartosci dla glfw
	if (!glfwInit())
	{
		error_callback(0, "glfw sie nie zainicjalizowalo :/");
		return 0;
		// Initialization failed
	}
	
	GLFWwindow* window = glfwCreateWindow(640, 480, "Boomber", NULL, NULL);
	if (!window) {
		glfwTerminate();
		error_callback(0, "GLFWwindow failed");
		return -1;
	}

	glfwSetErrorCallback(error_callback);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowAspectRatio(window, 3, 2);

	//inicjalizacja wszystkich funkcji ze zmiennymi statycznymi i stworzenie glLists
	init(enemyArray, &bitmap, &pauseType, &dTime, &player, howManyEnemies, howManyBoxes, howManyUpgrades, &gridSize, gameTime, &debugMode, listArray);

	//rozpoczecie glownej petli
	dTime = 0;
	glfwGetTime(dTime);
	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(window))
	{
		//forsowanie stosunku 3:2
		glfwGetFramebufferSize(window, &width, &height);
		if (width / 3 > height / 2) {
			glfwSetWindowSize(window, height / 2 * 3, height);
		}
		else if (width / 3 < height / 2) {
			glfwSetWindowSize(window, width, width / 3 * 2);
		}

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		//rysowanie pauzy
		if (pauseType != none) {
			glCallList(listArray[pauseType]);	//rysowanie tla i odpowiedniej wiadomosci
			if (pauseType != start) {
				writePauseMessageScore(score);	//dopisuje punkty do wiadomosci pauzy
			}
			glfwSwapBuffers(window);
			glfwPollEvents();		//aby wyjsc z pauzy nalezy wcisnac spacje
			continue;		//powrot do poczatku petli
		}
		//glfwSetTime(dTime); //set when unpause
		////////////////////////////////////////////////////////////////////////draw sequence

		glCallList(listArray[5]);	//szybsze jest narysowanie najpierw calej mapy jako same filary i sciezki za pomoca glCallList
		drawGrid(bitmap, gridSize); //a potem nadpisac niektore sciezki pudelkami
		
		glCallList(listArray[0]);									//rysuje pole na dane i ich tytuly
		writeDynamicData(highscore, player.score, player.timeLeft); //uzupelnia to pole potrzebnymi liczbami
		
		moveCheckExplodeAndCleanUpBombs(&player, bitmap, gridSize); //obsluz bomby

		if (manageEnemiesAndScore(enemyArray, &player, bitmap, howManyEnemies, gridSize, 0)) { //obsluz przeciwnikow
			if (!portalOpened) {	 //jesli wszyscy sa martwi, to sprobuj otworzyc portal
				openPortal(bitmap, gridSize);
			}
		}

		drawAllEnemies(enemyArray, gridSize, howManyEnemies); //narysuj przeciwnikow

		checkPlayer(bitmap, &player, gameTime, 0); //zaktualizuj dane gracza, moze przgral
		drawPlayer(&player, gridSize);	//narysuj gracza na mapie

		drawBombs(&player, gridSize); //ostatni rysunek, zeby bomby byly na wierzchu - dla widocznosci

		score = player.score;
		if (score > highscore) {
			highscore = score;
		}

		if (player.status == dead) {	//gracz przegral
			if (waitForGame_over(&player)) { //czy minelo dosc duzo czasu
				resetTimes(&dTime);
				initPlayer(&player, gameTime, gridSize);
				initGrid(bitmap, gridSize, howManyBoxes, howManyUpgrades);
				initEnemies(enemyArray, bitmap, howManyEnemies, gridSize);
				pauseType = gameOver;
			}
		}
		else if (player.status == winning) {	//gracz wygral
			if (waitForNextStageAndSumScore(&player)) { //czy minelo dosc duzo czasu
				resetTimes(&dTime);	
				reInitPlayer(&player, gameTime, gridSize);
				initGrid(bitmap, gridSize, howManyBoxes, howManyUpgrades);
				initEnemies(enemyArray, bitmap, howManyEnemies, gridSize);
				portalOpened = 0;
				pauseType = won;
			}
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	FILE* file2 = fopen("high score.txt", "w");
	if (!file2) {
		return 0;
	}
	setHighscore(highscore, file2);
	
	fclose(file2);
	dealocateMap(&bitmap, gridSize);
	unSetGlList(listArray);
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}