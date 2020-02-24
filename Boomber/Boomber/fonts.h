/** @file */

#ifndef FONTS_H
#define FONTS_H

/** Wskaznik na tablice reprezentujaca znak w postaci bitow - pixeli*/
typedef int(*sign)[8][5];

/** Zamienia wejsciowy ciag znakow, ta tablice wskaznikow na tablice reprezentujace znaki w postaci bitow - pixeli
* @param[out] signs wskaznik na wskaznik na tablice wskaznikow na tablice reprezentujace znaki w postaci bitow - pixeli
* @param word ciag znakow do przekonwertowania
*/
void translateWord(sign **signs, char *word);

/** Zapisuje w obszarze okna obok mapy tytuly informacji: aktualne punkty, najwieksza ilosc punktow oraz pozostaly czas gracza
*/
void writeStaticData();

/** Zapisuje w obszarze okna obok mapy aktualna ilosc punktow, dotychczasowa najwieksza ilosc punktow oraz pozostaly czas gracza pod odpowiednimi tytulami
* @param highscore najwyzsza dotychczasowa ilosc punktow
* @param score aktualna ilosc punktow
* @param timeLeft pozostaly czas gracza
*/
void writeDynamicData(int highscore, int score, int timeLeft);

/** Wypisuje na okno pauzy wiadomosc, zalezaca od typu pauzy
* @param pauseType typ pauzy
*/
void writePauseMessage(PauseScreenType pauseType);


/** Wypisuje na okno pauzy aktualna ilosc punktow
* @param score aktualna ilosc punktow
*/
void writePauseMessageScore(int score);

#endif // fonts
