/** @file */

#ifndef MANAGE_BOMBS_H
#define MANAGE_BOMBS_H

/** Znajduje ID w tablicy bomb gracza bomby o okreslonych koordynatach
* @param player wskaznik na gracza
* @param x koordynat szerokosci wzgledem mapy
* @param y koordynat wysokosci wzgledem mapy
* @return indeks, pod ktorym w tablicy bomb gracza znajduje sie bomba o podanych koordynatach
*/
int getBombID(Player *player, int x, int y);

/** Jesli moze, to przesuwa bombe o jeden kafelek 
* @param dir kierunek poruszania sie bomby
* @param currBomb wskaznik na aktualnie przesuwana bombe
* @param bitmap wskaznik na mape gry
* @param gridSize wielkosc mapy
*/
void moveTile(enum Direction dir, Bomb *currBomb, tile** bitmap, int gridSize);

/** Obsluguje bomby - przesuwa je, sprawdza, czy ktoras nie stoi na ogniu i nie musi wybuchnac, 
* czysci kafelki po bombach, ktore wybuchly i minelo dosc duzo czasu od ich wybuchu
* @param player wskaznik na gracza
* @param bitmap wskaznik na mape gry
* @param gridSize wielkosc mapy
*/
void moveCheckExplodeAndCleanUpBombs(Player *player, tile** bitmap, int gridSize);

/** Zmniejsza ilosc warstw ognia na kafelku i zamienia go na kafelek typu 'pathTile',
* jesli ilosc warstw ognia sie wyzeruje.
* @param currTile Kafelek do obsluzenia.
*/
void inline cleanTile(tile* currTile);

/** Przekazuje dane bomby A do bomby B.
* @param A bomba, ktorej dane sa przekazywane
* @param B bomba, do ktorej dane sa przekazywane
*/
void inline moveBombData(Bomb* A, Bomb* B);

/** Usuwa ogien pozostaly po eksplozji bomby, jesli minelo dosc duzo czasu od jej wybuchu
* @param currentBombID indeks w tablicy bomb gracza aktualnej bomby
* @param player wskaznik na gracza
* @param bitmap wskaznik na mape gry
*/
void cleanUp(int currentBombID, Player *player, tile** bitmap);

/** Probuje dany kafelek zamienic na 'fireTile' lub 'firedBox',
* jesli sie uda zamienic na 'fireTile', to zwraca *breaker = 0, czyli ogien moze isc dalej,
* jesli sie uda zamienic na 'firedBox', to zwraca *breaker = 1, czyli ogien nie isc dalej,
* jesli sie nie uda, to zwraca *breaker = 2, czyli ogien nie siegnal do tego kafelka i nie moze isc dalej
* @param currTile wskaznik na aktualny kafelek do sprawdzenia
* @param[out] breaker ustawia jego wartosc na 1 jesli dosiegnie pudelka
*/
void inline spreadFire(tile *currTile, int *breaker);

/** Zmienia status bomby na 'exploded', roznosi ogien po mapie zgodnie z zasiegiem danej bomby
* zwieksza ilosc wolnych bomb gracza
* @param bomb wskaznik na bombe, ktora nalezy eksplodowac
* @param player wskaznik na gracza
* @param bitmap wskaznik na mape gry
* @param gridSize wielkosc mapy
*/
void explodeBombAddPoints(Bomb* bomb, Player *player, tile** bitmap, int gridSize);

#endif