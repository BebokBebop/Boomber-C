/** @file */

#ifndef DRAW_H
#define DRAW_H

/** Inicjalizuje rzeczy wymagajace inicjalizacji z tego pliku
* @param bitmap wskaznik na mape gry
* @param gridSize wielkosc mapy (NxN)
* @param howManyBoxes ile na mapie znajduje sie pudel
* @param howManyUpgrades ile na mapie znajduje sie ulepszen
*/
void initGrid(tile** bitmap, int gridSize, int howManyBoxes, int howManyUpgrades);

/** Wywoluje funkcje zawierajace zmienne statyczne tak, by je zresetowac
*/
void resetDrawStatics();

/** Ustawia glListy dla optymalniejszego rysowania
* @param listArray Tablica przechowujaca indeksy glList.
* @param gridSize wielkosc mapy
*/
void setGlLists(int listArray[6], int gridSize);

/** Usuwa stworzone wczesniej glListy
* @param listArray Tablica przechowujaca indeksy glList.
*/
void unSetGlList(int listArray[6]);

/** Funkcja rysujaca podstawe mapy - tlo, sciezki, kolumny
* @param gridSize wielkosc mapy (NxN)
*/
void drawGridBase(int gridSize);

/** Funkcja rysujaca zmienna czesc mapy - pudelka, ulepszenia, ogien, zniszczone pudelka, oraz portal
* @param bitmap wskaznik na mape gry
* @param gridSize wielkosc mapy (NxN)
*/
void drawGrid(tile** bitmap, int gridSize);

/** Wywoluje rysowanie wszystkich bomb w okreslonych miejscach
* @param player wskaznik na gracza (gracz przechowuje bomby)
* @param gridSize wielkosc mapy (NxN)
*/
void drawBombs(Player *player, int gridSize);

/** Rysuje pojedyncza bombe o okreslonym okreslonym rozmiarze w okreslonym miejscu 
* @param x koordynat szerokosci wzgledem okna
* @param y koordynat wysokosci wzgledem okna
* @param sizeX szerokosc obiektu wzgledem okna
* @param sizeY wysokosc obiektu wzgledem okna
* @param bomb wskaznik na bombe do narysowania
*/
void drawBomb(double x, double y, double sizeX, double sizeY, Bomb* bomb);

/** Rysuje ulepszenie o okreslonym kolorze, okreslonym rozmiarze i w okreslonym miejscu
* @param R Skladowa koloru RGB
* @param G Skladowa koloru RGB
* @param B Skladowa koloru RGB
* @param x koordynat szerokosci wzgledem okna
* @param y koordynat wysokosci wzgledem okna
* @param sizeX szerokosc obiektu wzgledem okna
* @param sizeY wysokosc obiektu wzgledem okna
*/
void drawUpgrade(float R, float G, float B, double x, double y, double sizeX, double sizeY);

/** Rysuje kwadrat o okreslonym kolorze, okreslonym rozmiarze i w okreslonym miejscu
* @param R Skladowa koloru RGB
* @param G Skladowa koloru RGB
* @param B Skladowa koloru RGB
* @param x koordynat szerokosci wzgledem okna
* @param y koordynat wysokosci wzgledem okna
* @param sizeX szerokosc obiektu wzgledem okna
* @param sizeY wysokosc obiektu wzgledem okna
*/
void drawSquare(float R, float G, float B, double x, double y, double sizeX, double sizeY);

/** Rysuje portal o okreslonym rozmiarze i w okreslonym miejscu
* @param x koordynat szerokosci wzgledem okna
* @param y koordynat wysokosci wzgledem okna
* @param sizeX szerokosc obiektu wzgledem okna
* @param sizeY wysokosc obiektu wzgledem okna
*/
void drawPortal(double x, double y, double sizeX, double sizeY, int reset);

/** Rysuje gracza w okreslonym miejscu
* @param player wskaznik na gracza
* @param gridSize wielkosc mapy (NxN)
*/
void drawPlayer(Player *player, int gridSize);

/** Rysuje tlo panel obok mapy, na ktorym wypisane beda punkty gracza, najwyzsze dotychczasowe punkty oraz pozostaly czas gry
*/
void drawScoreboard();

/** Rysuje model przeciwnika typu 'blind' o okreslonym kolorze, okreslonym rozmiarze i w okreslonym miejscu
* @param R Skladowa koloru RGB
* @param G Skladowa koloru RGB
* @param B Skladowa koloru RGB
* @param x koordynat szerokosci wzgledem okna
* @param y koordynat wysokosci wzgledem okna
* @param sizeX szerokosc obiektu wzgledem okna
* @param sizeY wysokosc obiektu wzgledem okna
*/
void drawEnemyBlind(float R, float G, float B, double x, double y, double sizeX, double sizeY);

/** Rysuje model przeciwnika typu 'random' o okreslonym kolorze, okreslonym rozmiarze i w okreslonym miejscu
* @param R Skladowa koloru RGB
* @param G Skladowa koloru RGB
* @param B Skladowa koloru RGB
* @param x koordynat szerokosci wzgledem okna
* @param y koordynat wysokosci wzgledem okna
* @param sizeX szerokosc obiektu wzgledem okna
* @param sizeY wysokosc obiektu wzgledem okna
*/
void drawEnemyRandom(float R, float G, float B, double x, double y, double sizeX, double sizeY);

/** Rysuje model przeciwnika typu 'charger' w pierwszej jego fazie o okreslonym kolorze, okreslonym rozmiarze i w okreslonym miejscu
* @param R Skladowa koloru RGB
* @param G Skladowa koloru RGB
* @param B Skladowa koloru RGB
* @param x koordynat szerokosci wzgledem okna
* @param y koordynat wysokosci wzgledem okna
* @param sizeX szerokosc obiektu wzgledem okna
* @param sizeY wysokosc obiektu wzgledem okna
*/
void drawEnemychargerCalm(float R, float G, float B, double x, double y, double sizeX, double sizeY);

/** Rysuje model przeciwnika typu 'charger' w jego drugiej fazie o okreslonym kolorze, okreslonym rozmiarze i w okreslonym miejscu
* @param R Skladowa koloru RGB
* @param G Skladowa koloru RGB
* @param B Skladowa koloru RGB
* @param x koordynat szerokosci wzgledem okna
* @param y koordynat wysokosci wzgledem okna
* @param sizeX szerokosc obiektu wzgledem okna
* @param sizeY wysokosc obiektu wzgledem okna
*/
void drawEnemychargerUpset(float R, float G, float B, double x, double y, double sizeX, double sizeY);

/** Wywoluje funkcje rysowania przeciwnika wzgledem jego typu w okreslonym miejscu
* @param x Koordynat szerokosci wzgledem okna.
* @param y Kordynat wysokosci wzgledem okna.
* @param sizeX Szerokosc obiektu wzgledem okna.
* @param sizeY Wysokosc obiektu wzgledem okna.
* @param enemy Wskaznik na przeciwnika do narysowania.
*/
void drawEnemy(double x, double y, double sizeX, double sizeY, Enemy* enemy);

/** Rysuje panel obok mapy, na ktorym wypisuje punkty gracza, najwyzsze dotychczasowe punkty oraz pozostaly czas gry
* @param enemyArray tablica przechowujaca dane wszystkich przeciwnikow
* @param gridSize wielkosc mapy (NxN)
* @param howMany ile przeciwnikow jest do narysowania
*/
void drawAllEnemies(Enemy enemyArray[MAX_ENEMIES_PER_MAP], int gridSize, int howMany);

/** Rysuje tlo ekran pauzy
*/
void drawPauseScreen();

#endif 