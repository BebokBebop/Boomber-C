/** @file */

#ifndef PLAYER_H
#define PLAYER_H

/** Przesuwa gracza, jesli moze. Jesli na nowym kafelku bylo ulepszenie, to je zbiera, a jesli na nowym kafelku byla bomba, a gracz ma ulepszenie kopania bomb, to bomba ta zostanie kopnieta
* @param dir kierunek przesuniecia gracza
* @param bitmap wskaznik na mape gry
* @param player wskaznik na gracza
* @param gridSize wielkosc mapy
*/
void moveInADirectionAndKickIfPossibleAndCollectAnUpgrade(Direction dir, tile** bitmap, Player* player, int gridSize);

/** Inicjalizuje gracza, tj. ustawia mu wszystkie dane
* @param player wskaznik na gracza
* @param gameTime czas, w ktorym gracz ma skonczyc plansze
* @param gridSize wielkosc mapy
*/
void initPlayer(Player* player, int gameTime, int gridSize);

/** Wywoluje funkcje zawierajace zmienne statyczne tak, by je zresetowac
*/
void resetPlayerStatics();

/** Reinicjalizuje gracza, tj. czesc danych ustawia mu na nowo
* @param player wskaznik na gracza
* @param gameTime czas, w ktorym gracz ma skonczyc plansze
* @param gridSize wielkosc mapy
*/
void reInitPlayer(Player* player, int gameTime, int gridSize);

/** Otwiera portal, czyli zamienia srodkowy kafelek mapy na kafelek portalu
* @param bitmap wskaznik na mape gry
* @param gridSize wielkosc mapy
*/
void openPortal(tile** bitmap, int gridSize);

/** Stawia bombe na kafelku na ktorym stoi gracz
* @param bitmap wskaznik na mape gry
* @param player wskaznik na gracza
* @param gridSize wielkosc mapy
*/
void placeBomb(tile** bitmap, Player* player, int gridSize);

/** Stawia pudelko na kafelku na ktorym stoi gracz. Funkcja dostepna tylko w trybie debugu.
* @param bitmap wskaznik na mape gry
* @param player wskaznik na gracza
* @param gridSize wielkosc mapy
*/
void placeBox(tile** bitmap, Player* player, int gridSize);

/** Zabija gracza, jesli ten nie ma aktywnego ulepszenia tarczy. Jesli ma, to po chwili sie je wylacza.
* @param player wskaznik na gracza
*/
void damagePlayer(Player* player);

/** Stawia pudelko na kafelku na ktorym stoi gracz. Funkcja dostepna tylko w trybie debugu.
* @param bitmap wskaznik na mape gry
* @param player wskaznik na gracza
* @param gameTime czas, w ktorym gracz ma skonczyc plansze
* @param reset jesli 1 to nalezy zresetowac wartosci statycze w funkcji i z niej wyjsc, bez wykonywania reszty jej ciala
*/
void checkPlayer(tile** bitmap, Player* player, int gameTime, int reset);

/** Sprawdza, czy minelo dosc duzo czasu, zeby zakonczyc gre, po przegranej przeciwnika
* @return 1 kiedy minelo dosc duzo czasu, 0 kiedy nalezy jeszcze czekac
*/
int waitForGame_over();

/** Sprawdza, czy minelo dosc duzo czasu, zeby zakonczyc gre, po wygranej przeciwnika
* oraz przelewa pozostaly czas gracza*10 do jego punktow.
* @param player wskaznik na gracza
* @return 1 kiedy minelo dosc duzo czasu, 0 kiedy nalezy jeszcze czekac
*/
int waitForNextStageAndSumScore(Player* player);

/** Zwieksza zasieg bomb gracza. Dostepne tylko w trybie debugowania
* @param player wskaznik na gracza
*/
void increaseBombFireRange(Player* player);

/** Obniza zasieg bomb gracza. Dostepne tylko w trybie debugowania
* @param player wskaznik na gracza
*/
void decreaseBombFireRange(Player* player);

/** Zwieksza ilosc dostepnych bomb gracza. Dostepne tylko w trybie debugowania
* @param player wskaznik na gracza
*/

void increaseBombsAvalible(Player* player);

/** Zmniejsza ilosc dostepnych bomb gracza. Dostepne tylko w trybie debugowania
* @param player wskaznik na gracza
*/
void decreaseBombsAvalible(Player* player);

/** Wlacza lub wylacza ulepszenie tarczy gracza. Dostepne tylko w trybie debugowania
* @param player wskaznik na gracza
*/
void shieldSwitch(Player* player);

/** Wlacza lub wylacza ulepszenie kopania bomb gracza. Dostepne tylko w trybie debugowania
* @param player wskaznik na gracza
*/
void kickSwitch(Player* player);

#endif