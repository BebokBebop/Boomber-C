/** @file  */

#ifndef TESTARG_H
#define TESTARG_H

/** Sprawdza poprawnosc podanych do funkcji main argumentow i zwraca komunikaty ewentualnych bledow.
* @param argc Ilosc argumentow przekazanych do funkcji main (tj. wraz z wywolaniem programu).
* @param argv Dwuwymiarowa tablica przechowujaca argumenty przekazane do funkcji main (tj. wraz z wywolaniem programu).
* @param[out] howManyEnemies Ile nalezy naniesc na plansze przeciwnikow.
* @param[out] howManyBoxes Ile nalezy naniesc na plansze pudelek.
* @param[out] howManyUpgrades Ile nalezy naniesc na plansze ulepszen.
* @param[out] gridSize Wielkosc mapy gry.
* @param[out] gameTime Czas w jakim nalezy wygrac plansze.
* @param[out] debugMode Czy nalezy wlaczyc gre w trybie debugu (dostepne dodatkowe opcje). 1 - tak, 0 - nie.
* @param[out] helpSwitch Czy nalezy wyswietlic pomoc. 1 - tak, 0 - nie.
* @return Ciag znakow zawierajacy wykryte w funkcji bledy w argumentach, pomoc lub ciag pusty, jesli zadnych bledow nie bylo.
*/
char* check_param(int argc, char **argv, int *howManyEnemies, int *howManyBoxes,
	int *howManyUpgrades, int *gridSize, int *gameTime, int *debugMode, int *helpSwitch);

#endif
