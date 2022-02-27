#ifndef PRAK3_H
#define PRAK3_H
#include<iostream>
#include<array>
#include<time.h>
#include<stdlib.h>

using namespace std;
#define log(x) std::cout << x << std::endl;
enum status {verdeckt, mine, aufgedeckt};
const int numberofbomb{10};
int countergedeckt{};
int coordx{};
int coordy{};
bool gameover = false, win = false;           //Aufgabe 3.3
int endgame();
void initialisieren();                 //aufgabe 3.2
void darstellen();
void inputstatus(int inputx, int inputy);
void nachbarnChecken(int cox, int coy);
bool aufgedeckterLeererNachbar(int cordx, int cordy);
void input();
void counter();         //count the number of field in the map
void checkwin();    //check if we win the game
const int maxrow{12}, maxcol{12};     //global value, number of row and column


struct Feld{
private:
    status stat;    //status
    int bombnumb;    //menge der Mine in der naehe
public:
    int getBombNumb();
    void plantbomb();
    int getStatus();
    void statustodraw();
    void addBombNumb();
    void changeAufgedeckt();
    Feld() {stat = verdeckt; bombnumb = 0;}  //default konstruktor
};
Feld minefield[maxrow][maxcol];
#endif // PRAK3_H
