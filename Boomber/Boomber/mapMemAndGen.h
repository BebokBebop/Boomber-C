/** @file */
#ifndef MAPMEMANDGEN_H
#define MAPMEMANDGEN_H

/** Dealokuje pamiec mapy o okreslonej wielkosci.
* @param bitmap wskaznik na wskaznik na mape gry
* @param gridSize wielkosc mapy
*/
void dealocateMap(tile **(*bitmap), int gridSize);

/** Alokuje pamiec dla mapy o okreslonej wielkosci.
* @param bitmap wskaznik na wskaznik na mape gry
* @param gridSize wielkosc mapy
*/
void allocateMap(tile **(*bitmap), int gridSize);

/** Generuje mape gry - stawia kolumny, pudelka i ulepszenia
* @param bitmap wskaznik na mape gry
* @param gridSize wielkosc mapy (NxN)
* @param howManyBoxes ile na mapie ma sie znajdowac sie pudel
* @param howManyUpgrades ile na mapie ma sie znajdowac ulepszen
*/
void generateMap(tile** bitmap, int gridSize, int howManyBoxes, int howManyUpgrades);

#endif