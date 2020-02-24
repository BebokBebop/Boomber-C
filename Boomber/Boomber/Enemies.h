/** @file */

#ifndef ENEMIES_H
#define ENEMIES_H
/** Inicjalizuje rzeczy wymagajace inicjalizacji z tego pliku.
* @param enemyArray Tablica przechowujaca dane wszystkich przeciwnikow.
* @param bitmap Wskaznik na mape gry.
* @param howMany Ile przeciwnikow jest do wygenerowania.
* @param gridSize Wielkosc mapy (NxN).
*/
void initEnemies(Enemy enemyArray[MAX_ENEMIES_PER_MAP], tile* bitmap, int howMany, int gridSize);

/** Wywoluje funkcje zawierajace zmienne statyczne tak, by je zresetowac.
*/
void resetEnemyStatics();

/** Dodaje nowego przeciwnika do tablicy i ustawia jego dane.
* @param enemyArray Tablica przechowujaca dane wszystkich przeciwnikow.
* @param ID Indeks nowego przeciwnika w tablicy przeciwnikow.
* @param type Typ przeciwnika.
* @param coords Koordynaty nowegp przeciwnika wzgledem mapy.
* @param dir Kiedunek poruszania sie nowego przeciwnika.
*/
void addEnemy(Enemy enemyArray[MAX_ENEMIES_PER_MAP], int ID, EnemyType type, XY coords, Direction dir);

/** Przesuwa przeciwnika typu 'blind' lub przeciwnika typu 'charger' w pierwszej jego fazie.
* @param enemy Wskaznik na przeciwnika do przesuniecia.
* @param bitmap Wskaznik na mape gry.
* @param gridSize Wielkosc mapy (NxN).
*/
void moveBlind(Enemy *enemy, tile** bitmap, int gridSize);

/** Przesuwa przeciwnika typu 'random'.
* @param enemy Wskaznik na przeciwnika do przesuniecia.
* @param bitmap Wskaznik na mape gry.
* @param gridSize Wielkosc mapy (NxN).
*/
void moveRandom(Enemy *enemy, tile** bitmap, int gridSize);

/** Sprawdza, czy gracz jest w polu widzenia przeciwnika, tj sa w tej samej kolumnie lub wierszu i nie sa zaslonieci kolumna i nakierowuje na niego przeciwnika.
* @param enemy Wskaznik na przeciwnika, ktorego sprawdzane jest pole widzenia.
* @param player Wskaznik na gracza.
* @return Liczba 0 jesli nie widac gracza i nie zmieniono kierunku przeciwnika, liczba 1 jesli go widac i nakierowano na niego przeciwnika.
*/
int pointTowardsPlayerIfPossible(Enemy* enemy, Player *player);

/** Przesuwa przeciwnika typu 'charger' w jego drugiej fazie.
* @param enemy Wskaznik na przeciwnika do przesuniecia.
* @param player Wskaznik na gracza.
* @param bitmap Wskaznik na mape gry.
* @param gridSize Wielkosc mapy (NxN).
*/
void moveCharger(Enemy *enemy, Player *player, tile** bitmap, int gridSize);

/** Probuje przesunac przeciwnika w jego kierunku o jeden kafelek.
* @param enemy Wskaznik na przeciwnika do przesuniecia.
* @param rush Przelacznik, czy przeciwnik ma sie przebijac przez pudelka.
* @param bitmap Wskaznik na mape gry.
* @param gridSize Wielkosc mapy (NxN).
* @return Liczba 0 jesli sie nie udalo przesunac przeciwnika, liczba 1 w przypadku kiedy sie udalo, 2 jesli kierunek w ktorym probowano sie poruszyc byl inny przeciwnik.
*/
int moveEnemy(Enemy* enemy, int rush, tile** bitmap, int gridSize);

/** Obsluguje przeciwnikow, tj. przesuwa ich, sprawdza czy nie zostali zabici przez gracza (stoja na ogniu),
* dodaje punkty graczowi, jesli przeciwnik umiera i sprawdza, czy ktorys z przeciwnikow jeszcze zyje.
* @param enemyArray tablica przechowujaca dane wszystkich przeciwnikow.
* @param player Wskaznik na gracza.
* @param bitmap Wskaznik na mape gry.
* @param howMany Ile jest przeciwnikow.
* @param gridSize Wielkosc mapy (NxN).
* @param reset Jesli 1 to nalezy zresetowac wartosci statycze w funkcji i z niej wyjsc, bez wykonywania reszty jej ciala.
* @return Liczba 0 kiedy zyje przynajmniej jeden przeciwnik, liczba 1 jesli wszyscy sa martwi.
*/
int manageEnemiesAndScore(Enemy enemyArray[MAX_ENEMIES_PER_MAP], Player* player, tile** bitmap, int howMany, int gridSize, int reset);

/** Stawia nowych przeciwnikow na planszy.
* @param enemyArray Tablica przechowujaca dane wszystkich przeciwnikow.
* @param bitmap Wskaznik na mape gry.
* @param howMany Ile przeciwnikow jest do wygenerowania.
* @param gridSize Wielkosc mapy (NxN).
*/
void dropEnemies(Enemy enemyArray[MAX_ENEMIES_PER_MAP], tile** bitmap, int howMany, int gridSize);

#endif