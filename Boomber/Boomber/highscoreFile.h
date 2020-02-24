/** @file */

#ifndef HIGHSCOREFILE_H
#define HIGHSCOREFILE_H

/** Pobiera z pliku wartosc dotychczasowej najwiekszej ilosci punktow
* @param in wskaznik na strukture pliku
* @param[out] pobrana z pliku wartosc dotychczasowej najwiekszej ilosci punktow 
*/
int getHighscore(FILE *in);

/** Zapisuje do pliku wartosc dotychczasowej najwiekszej ilosci punktow
* @param out wskaznik na strukture pliku
* @param score wartosc dotychczasowej najwiekszej ilosci punktow
*/
void setHighscore(int score, FILE*out);

#endif