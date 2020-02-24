/** @file */

#ifndef ENUMSSTRUCTSMACROS_H
#define ENUMSSTRUCTSMACROS_H

#define DEFAULT_GRID_SIZE 11// 11 - 15 - 19, tj 4n - 1 //najlepiej nieparzyste, bo pillary sa wtedy wysrodkowane
#define MAX_GRID_SIZE 100
#define MAX_ENEMIES_PER_MAP 20 //min 1
#define DEFAULT_ENEMIES_COUNT 4
#define DEFAULT_GAME_TIME 180.9999
#define DEFAULT_DEBUG_MODE 0


#define MAX_BOMBS 20 //przechowuje katywne bomby w tablicy, wiec musze miec stala wartosc
//#define UPGRADES_PER_MAP 10



#define INIT_BOMB_AVALIBLE 1
#define INIT_BOMB_KICK 0 //0-1
#define INIT_SHIELD 0 //0-1
#define INIT_FIRERANGE 2 //2 minimum

#define BOX_COLOR 0.5, 0.5, 0.5
#define PATH_COLOR 0.1, 0.1, 0.1
#define PILLAR_COLOR 1,1,1
#define FIRE_COLOR 0.9, 0.7, 0.1
#define FIRED_BOX_COLOR 0.4, 0.15, 0.0
#define PORTAL_COLOR 0.3, 0.3, 1
#define PORTAL_COLOR_2 0.7, 0.7, 1
#define PORTAL_COLOR_3 	0.9, 0.9, 1

/* alt colors
#define BOX_COLOR 0.4, 0.2, 0.0
#define PATH_COLOR 0.5,0.5,0.5//0.1, 0.1, 0.1
#define PILLAR_COLOR 0,0,0//1,1,1
#define FIRE_COLOR 0.9, 0.7, 0.1
#define FIRED_BOX_COLOR 0.4, 0.15, 0.0
#define PORTAL_COLOR 0.3, 0.3, 1
#define PORTAL_COLOR_2 0.7, 0.7, 1
#define PORTAL_COLOR_3 	0.9, 0.9, 1
*/

#define PLAYER_SIZE 0.91
#define PLAYER_COLOR 0.3, 0.55, 1.0
#define SHIELD_COLOR 0.6, 0.9, 1
#define DEAD_PLAYER_COLOR 0.5, 0.1, 0.1

#define UPGRADE_CRYSTAL_SIZE 0.9
#define UPG_FIRE_RANGE_COLOR FIRE_COLOR
#define UPG_SHIELD_COLOR SHIELD_COLOR
#define UPG_BOMB_KICK_COLOR 1, 0.7, 0.7
#define UPG_BOMBS_AVALIBLE 0.8, 0.1, 0.1

#define SCOREBOARD_BACKGROUND_COLOR PATH_COLOR
#define BACKGROUND_COLOR PILLAR_COLOR
#define FONT_COLOR 1,1,1
#define FONT_SIZE 0.01

#define PAUSE_SCREEN_COLOR 0.1,0.1,0.1

//polozenie mapy
#define GRID_L_X -0.965
#define GRID_D_Y -0.95

//polozenie scoreboardu
#define SCORE_BOARD_L_X 1.05/3.0
#define SCORE_BOARD_R_X 0.95
#define SCORE_BOARD_D_Y -0.95
#define SCORE_BOARD_U_Y 0.95

//time
#define PLAYER_APPEAR_TIME 1.5
#define BROKEN_SHIELD_TIME 1.5
#define FIRE_LINGERING_TIME 0.5
#define BOMB_EXPLODE_TIME 2.5
//speed
#define SCORE_DROP_FREQUENCY 1
#define TIME_COUNT_SPEED 0.07
#define PORTAL_SUCKING_SPEED 0.75

//enemies
#define ENEMY1_SPEED 0.8
#define ENEMY2_SPEED 0.5
#define ENEMY3_SPEED 0.2
#define RANDOM_TRIALS 2 //ile prob poruszenia sie ma podjac przeciwnik typu 'random'

#define ENEMY1_COLOR 0.9, 0.9, 0.0
#define ENEMY1_DEAD_COLOR DEAD_PLAYER_COLOR

#define ENEMY2_COLOR 0.0, 0.8, 0.8
#define ENEMY2_DEAD_COLOR DEAD_PLAYER_COLOR

#define ENEMY3_1ST_PHASE_COLOR 0.3, 0.0, 0.3
#define ENEMY3_2ND_PHASE_COLOR 0.9, 0.0, 0.9
#define ENEMY3_DEAD_COLOR DEAD_PLAYER_COLOR

#define ENEMY_ROT_TIME 0.7 // jak dlugo zwloki przeciwnika sa widoczne

/** Mozliwe kierunki poruszania sie
*/
typedef enum { north = 1, east, south, west } Direction;

/** Typy ulepszen
*/
typedef enum {
	fireRange = 1, /**< Zasieg bomby.*/
	bombsAvalible, /**< Ile bomb na raz moze byc postawionych na mapie.*/
	bombKick, /**< Czy gracz moze "kopnac" bombe, tj sprawic, zeby bomba przesuwala sie w okreslonym kierunku.*/
	shield /**< Czy gracz ma tarcze. Jesli tak, to moze stanac na ogniu albo spotkac przeciwnika bez natychmiastowej smierci, ale wtedy tarcza w ciagu chwili zniknie.*/
} upgrades;

/** Typy kafelek mapy
*/
typedef enum {
	pathTile, /**< Kafelek sciezki - gracz, przeciwnik oraz przesuwajaca sie bomba moga sie po nim poruszac.*/
	boxTile, /**< Kafelek pudelka - wybuch bomby moze go zniszczyc, poruszajaca bomba sie przed nim zatrzyma, nic nie moze przez niego przejsc, poza przeciwnikiem typu 'charger' w jego drugiej fazie.*/
	pillarTile, /**< Kafelek kolumny - nic nie moze przez niego przejsc, nie mozna go w zaden sposob zniszczyc, przeciwnik typu 'charger' nie zobaczy przeciwnika, jesli na jego polu widzenia znajduje sie ten kafelek.*/
	bombTile, /**< Kafelek na ktorym znajduje sie bomba - nic przez niego nie moze przejsc, poza graczem, ktory ma ulepszenie 'bombKick', w takim wypadku gracz moze wejsc na ten kafelek, a bomba na nim sie znajdujaca zacznie sie przesuwac.*/
	fireTile, /**< Kafelek na ktorym znajduje sie ogien - wszystko moze na niego wejsc, przy czym przeciwnicy i gracz bez ulepszenia 'shield' znajdujacy sie na tym kafelku umieraja. Gracz posiadajacy ulepszenie shield straci je.*/
	firedBox, /**< Kafelek na ktorym znajduje sie pudelko, ktore dosiegnela eksplozja bomby - przeciwnicy nie moga przez niego przejsc poza przeciwnikiem typu 'charger' w jego drugiej fazie, ktory wchodzac na niego umrze. Dla gracza zachowuje sie jak kafelek 'fireTile'.*/
	portalTile, /**< Kafelek, ktory pojawia sie na srodku mapy w momencie, kiedy wszyscy przeciwnicy zostana pokonani. Kiedy gracz na niego wejdzie, to rozpocznie podsumowanie punktow i pauza typu zwyciestwo.*/
	enemyTile  /**< Kafelek na ktorym znajduje sie przeciwnik - inni przeciwnicy nie moga na niego wejsc, gracz wchodzac na nie otrzymuje obrazenia. Nie mozna na nim postawic bomby, a poruszajaca bomba sie przed nim zatrzyma.*/
} tileType;

/** Status bomby
*/
typedef enum {
	empty, /**< Bomba nie jest polozona.*/
	placed, /**< Bomba jest polozona i jeszcze nie wybuchla.*/
	exploding, /**< Bomba wlasnie wybuchnela.*/
	exploded, /**< Bomba jest po wybuchu.*/
	toBeCleaned /**< Bomba oczekuje na likwidacje wraz z jej ogniem.*/
} bombState;

/** Typy pauzy
*/
typedef enum {
	none, /**< Aktualnie nie ma pauzy.*/
	start, /**< Pauza w oczekiwaniu na rozpoczecie gry.*/
	stop, /**< Pauza w trakcie gry.*/
	gameOver, /**< Pauza po przegraniu planszy.*/
	won /**< Pauza po wygraniu planszy.*/
} PauseScreenType;

/** Typy przeciwnikow
*/
typedef enum {
	blind, /**< Porusza sie po prostej az do napotkania przeszkody (kafelek 'boxTile', 'pillarTile', 'firedBox', 'enemytile'),
		  * po czym probuje zmienic kierunek. Najpierw w lewo wzgledem pierwotnego kierunku, jesli nie da sie poruszyc w nowym kierunku,
		  * to probuje poruszyc sie w prawo wzgledem oryginalnego kierunku, jak i to sie nie uda, to zawraca wzgledem oryginalnego kierunku.
		  * Jesli nie moze sie poruszyc w zadnym z kierunkow, to sie nie porusza.*/
	random, /**< Porusza sie w przypadkowych kierunkach. Jesli nie moze sie poruszyc w danym kierunku, to probuje kolejny przypadkowy kierunek okreslona makrem RANDOM_TRIALS ilosc razy.*/
	charger /**< Porusza sie tak jak przeciwnik typu 'blind' az w jego polu widzenia znajdzie sie gracz,
		   * tj bedzie w tej samej kolumnie lub wierszu i jesli w linii prostej miedzy graczem i przeciwnikiem nie bedzie kafelka typu 'pillarTile',
		   * wtedy zmienia swoj tryb i porusza sie po linii prostej w kierunku w jakim ostatni raz 'widzial' gracza az do napotkania konca mapy lub innego przeciwnika,
		   * wtedy, jesli nie 'widzi' gracza, to wraca do trybu 'calm' i znow porusza sie jak przeciwnik typu 'blind'.*/
} EnemyType;

/** Mozliwy status gracza lub przeciwnika
*/
typedef enum {
	dead, /**< Status martwego gracza oraz przeciwnika, ktory umarl chwile temu i minelo dosc duzo czasu, zeby wylaczyc rysowanie jego korpusu.*/
	alive, /**< Status zywego gracza i przeciwnika.*/
	winning, /**< Status gracza jesli wejdzie do portalu.*/
	dying, /**< Status przeciwnika, ktory przed chwila umarl i jeszcze nie minelo dosc duzo czasu, zeby wylaczyc rysowanie jego korpusu.*/
	rushing, /**< Status przeciwnika typu 'charger', jesli 'zobaczyl' (sposob 'widzenia' opisany w komentarzu w do enumeratora EnrmyType) gracza.*/
	calm, /**< Status przeciwnika typu 'charger' jesli nie 'widzial' (sposob 'widzenia' opisany w komentarzu w do enumeratora EnrmyType) przez jakis czas gracza.*/
	appearing  /**< Status gracza pojawiajacego sie na mapie (pierwszy moment gry).*/
} Status;

/* Koordynaty kartezjanskie
*/
typedef struct {
	int x /** Koordynat x.*/;
	int y /** Koordynat y.*/;
}XY;

/* Pojedynczy kafelek na mapie
*/
typedef struct {
	tileType type; /**< Typ kafelka.*/
	int fireLayers; /**< Ile jest warstw ognia na kafelku.*/
	upgrades upgrade; /**< Jakie ulepszenie jest na kafelku.*/
}tile;

/** Bomba i jej dane
*/
typedef struct {
	int size; /**< Zasieg bomby.*/
	int fireCross[4]; /**< Gdzie po wycuchu siegnal ogien bomby w 4 kierunkach.*/
	XY coords; /**< Koordynaty bomby wzgledem mapy.*/
	double explosionTimer; /**< Czas do eksplozji lub czas po eksplozji.*/
	double kickTimer; /**< Kiedy ostatni raz bomba byla przesunieta.*/
	Direction kickDirection; /**< Kierunek przesuwania bomby.*/
	bombState statFlag; /**< Status bomby.*/
}Bomb;

/** Przeciwnik i jego dane
*/
typedef struct {
	Status status; /**< Status przeciwnika.*/
	XY coords; /**< Koordynaty przeciwnika wzgledem mapy.*/
	Direction direction; /**< Kierunek poruszania sie przeciwnika.*/
	EnemyType type; /**< Typ przeciwnika.*/
	float rottingTime; /**< Jak dlugo nalezy rysowac zwloki przeciwnika po jego smierci.*/
}Enemy;

/** Gracz i jego dane
*/
typedef struct {
	XY coords; /**< Koordynaty gracza wzgledem mapy.*/
	Status status; /**< Status gracza.*/
	int upgrades[5]; /**< Ulepszenia gracza.*/
	int score; /**< Punkty gracza.*/
	int timeLeft; /**< Czas, po ktorym gracz zacznie tracic punkty, az sie wyzeruja, po czym gracz umrze. Ten czas jest resetowany po przegraniu lub wygraniu planszy.*/
	double brokenShieldTimer; /**< Czas po zniszczeniu 'tarczy' przez jaki bedzie ona jeszcze aktywna .*/
	Bomb bombList[MAX_BOMBS]; /**< Tablica zawierajaca bomby postawione przez gracza.*/
	int newestBomb; /**< Indeks najpozniej polozonej i jeszcze aktywnej bomby w tablicy bomb.*/
	int oldestBomb; /**< Indeks najwczesniej polozonej i jeszcze aktywnej bomby w tablicy bomb.*/
}Player;

#endif 