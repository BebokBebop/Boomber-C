/** @file */

#include"enumsStructsMacros.h"
#include"TestArg.h"
#include<string.h>
#include<stdio.h>

char* check_param(int argc, char **argv, int *howManyEnemies, int *howManyBoxes, 
	int *howManyUpgrades, int *gridSize, int *gameTime, int *debugMode, int *helpSwitch) {
	char* badUse = "Zle uzycie.\nWpisz: \"[Nazwa_Programu] -h\"\nlub \"[Nazwa_Programu] help\",\nzeby otrzymac pomoc.\n";

	char* help = "Wpisz \"[Nazwa_Programu] -e [ilosc przeciwnikow (15 > x > 1)] \n-b [ilosc pudelek (< 3/4 * (wielkosc mapy)^2) - ilosc przeciwnikow]\n-u [ilosc ulepszen (< ilosc pudelek]\n-s [wielkosc mapy (>=7)]\n-t [czas gry w sekundach] \n-d [debug mode <0-1>]\"";

	char* errorZwrot[1000] = { 0 };

	char *przelaczniki = "hebustd";
	int zleWartosci[7] = { 0 };
	int ileRazyPrzelacznik[7] = { 0 };


	if (argc == 1) {
		strcat(errorZwrot, "Nie wykryto przelacznikow.\nUzyto wartosci domyslnych\n");
		return errorZwrot;
	}
	for (int i = 1; i < argc; ++i) {
		if (!strcmp(argv[i], "-e")) {
			ileRazyPrzelacznik[1]++;
			if (++i >= argc) {
				*helpSwitch = 1;
				return badUse;
			}
			else {
				if (!(*howManyEnemies = atoi(argv[i]))) {
					zleWartosci[1] = 1;
				}
				else if (*howManyEnemies < 1) {
					*howManyEnemies = 4;
					zleWartosci[1] = 2;
				}
			}
		}

		else if (!strcmp(argv[i], "-b")) {
			ileRazyPrzelacznik[2]++;
			if (++i >= argc) {
				*helpSwitch = 1;
				return badUse;
			}
			else {
				if (!(*howManyBoxes = atoi(argv[i]))) {
					zleWartosci[2] = 1;
				}
			}
		}

		else if (!strcmp(argv[i], "-u")) {
			ileRazyPrzelacznik[3]++;
			if (++i >= argc) {
				*helpSwitch = 1;
				return badUse;
			}
			else {
				if (!(*howManyUpgrades = atoi(argv[i]))) {
					zleWartosci[3] = 1;
				}
			}
		}

		else if (!strcmp(argv[i], "-s")) {
			ileRazyPrzelacznik[4]++;
			if (++i >= argc) {
				*helpSwitch = 1;
				return badUse;
			}
			else {
				if (!(*gridSize = atoi(argv[i]))) {
					zleWartosci[4] = 1;
				}
				if ((*gridSize + 1) % 4 != 0 && *gridSize < 7) {
					*gridSize = 11;
					zleWartosci[4] = 2;
				}
			}
		}
		else if (!strcmp(argv[i], "-t")) {
			ileRazyPrzelacznik[5]++;
			if (++i >= argc) {
				*helpSwitch = 1;
				return badUse;
			}
			else {
				if (!(*gameTime = atoi(argv[i]))) {
					zleWartosci[5] = 1;
				}
				if (*gameTime < 10) {
					*gameTime = 60.9999;
					zleWartosci[5] = 2;
				}
			}
		}
		else if (!strcmp(argv[i], "-d")) {
			ileRazyPrzelacznik[6]++;
			if (++i >= argc) {
				*helpSwitch = 1;
				return badUse;
			}
			else {
				*debugMode = atoi(argv[i]); //bedzie dzialac dla byle czego, ale nie zaszkodzi
				if (*debugMode != 1 && *debugMode != 0) {
					*debugMode = 0;
					zleWartosci[6] = 1;
				}
			}
		}
		else if (!strcmp(argv[i], "help") || !strcmp(argv[i], "-h")) {
			*helpSwitch = 1;
			return help;
		}
		else {
			*helpSwitch = 1;
			return badUse;
		}
	}
	
	if (*gridSize > MAX_GRID_SIZE) {
		*gridSize = -1;
		zleWartosci[4] = 2;
	}

	if (*gridSize != -1) {
		if (*howManyEnemies != -1) {
			if (*howManyEnemies > 0.75 * *gridSize* *gridSize || *howManyEnemies > MAX_ENEMIES_PER_MAP) {
				zleWartosci[1] = 2;
				*howManyEnemies = -1;
			}
		}
		if (*howManyBoxes != -1) {
			if (*howManyBoxes > 3.0 / 4.0 * *gridSize* *gridSize - *howManyEnemies) {
				zleWartosci[2] = 2;
				*howManyBoxes = -1;
			}
		}
	}
	if (*howManyBoxes != -1) {
		if (*howManyUpgrades != -1) {
			if (*howManyUpgrades > *howManyBoxes) {
				zleWartosci[3] = 2;
				*howManyUpgrades = -1;
			}
		}
	}


	for (int i = 0; i < 6; i++) {
		if (ileRazyPrzelacznik[i] > 1) {
			strcat(errorZwrot, ">Przelacznik [-");
			strncat(errorZwrot, &przelaczniki[i], 1);
			strcat(errorZwrot, "] zostal uzyty wiecej niz raz\n\tUzyto domyslnej wartosci\n");
		}
		//else if (!wymaganePrzelaczniki[i]) {
		//	strcat(errorZwrot, ">Przelacznik [-");
		//	strcat(errorZwrot, przelaczniki[i]);
		//	strcat(errorZwrot, "] nie zostal uzyty\n");
		//}
		else {
			if (zleWartosci[i] == 1) {
				strcat(errorZwrot, ">wartosc po \"-");
				strncat(errorZwrot, &przelaczniki[i], 1);
				strcat(errorZwrot, "\" nie jest poprawnie zapisana liczba\n\tUzyto domyslnej wartosci\n");
			}
			else if (zleWartosci[i] == 2) {
				strcat(errorZwrot, ">wartosc po \"-");
				strncat(errorZwrot, &przelaczniki[i], 1);
				strcat(errorZwrot, "\" jest poza zakresem\n\tUzyto wartosci domyslnej\n");
			}
		}
	}
	//plikWej = fopen(input);
	//plikWyjsciowy.open(output);

	//if (!plikWejsciowy)
	//{
	//	errorZwrot += ">Nie mozna otworzyc pliku wejsciowego\n";
	//}

	//if (!plikWyjsciowy)
	//{
	//	errorZwrot += ">Nie mozna otworzyc pliku wyjsciowego\n";
	//}

	return errorZwrot;
}

