#include"prak3.h"
int Feld::getBombNumb() {
    return bombnumb;
}
void Feld::changeAufgedeckt() {
    if(stat == verdeckt) {
        countergedeckt--;        //number of safespot remains --
    }
    stat = aufgedeckt;
    checkwin();
    endgame();
}
int Feld::getStatus() {
    return stat;
}
void Feld::plantbomb() {
    stat = mine;      //stat veraendern von 'verdeckt' zu 'mine'
}
void Feld::statustodraw() {
    if(stat == verdeckt) {
        cout << "* ";
        //cout << bombnumb <<" ";
    }
    if(stat == mine) {
        if(gameover == false) {
            cout << "X ";                       //X is the bomb
        }
        else {
            cout << "* ";
        }
    }
    if(stat == aufgedeckt) {
        if(bombnumb == 0){
            cout << ". ";
        }
        else
        cout << bombnumb << " " ;
        //cout << "* ";
    }
}
void Feld::addBombNumb() {
    bombnumb++;
}
void counter(){                         //count the amount of remaining gedeckt coord
    for(int i= 0; i < maxrow; i++) {
        for(int z =0; z < maxcol; z++) {
            if(minefield[i][z].getStatus() == verdeckt) {
                countergedeckt++;
                //cout << i << " " << z << endl;
            }
        }
    }
    //log(countergedeckt);
}
void checkwin() {
    if(countergedeckt == 0) {
        win = true;
        gameover = true;

    }
}
bool aufgedeckterLeererNachbar(int cordx, int cordy) {
    if(minefield[cordx][cordy].getBombNumb() == 0) {
        return true;
    }
    else
        return false;
}
void nachbarnChecken(int row, int col) {            //function that will keep spreading until touch the bomb
    int i{}, j{};
    minefield[row][col].changeAufgedeckt();
    if(aufgedeckterLeererNachbar(row, col)) {        //aufgedecjterLeererNachbar();
        for (i = -1; i < 2; i++) {
            for(j = -1; j <2; j++) {
                if (i!=0 || j!=0) {
                    if (row + i >= 0 && row + i < maxrow && col + j >=0 && col + j < maxcol) {
                        if(minefield[row+i][col+j].getStatus() == verdeckt) nachbarnChecken(row+i, col+j);    //recursion
                    }
                }
            }
        }
    }
}
void inputstatus(int inputx, int inputy) {                   //function to check if the coordinate that player chose is a bomb or not, if not then continue
    if(minefield[inputx][inputy].getStatus() == mine) {
        gameover = true;
        endgame();    //this one to help me end the while loop and dont have to change inputstatus to int to use return 0;
    }
    if(minefield[inputx][inputy].getStatus() == verdeckt) {
        if(minefield[inputx][inputy].getBombNumb() > 0) {       //if bombnumb != 0
            minefield[inputx][inputy].changeAufgedeckt();
        }
        nachbarnChecken(inputx, inputy);            //if the bombnumb of chosen coordinate == 0 then check Nachbarn
    }
}
int endgame() {
    if(gameover == true && win == true ) {
        log("Congratulation!!!  You won");
    }
    if(gameover == true && win == false) {
        log("***BOOOOOMMM****\nGAME OVER");
        //darstellen();

    }
    return 0;
}
void initialisieren() {
    srand(time(NULL));
    for(int i = 0; i < numberofbomb; i++) {            //assign 10 random bombs
        coordx = rand()%12 + 0;    //random number from 0 - 11  //
        coordy = rand()%12 + 0;
        if(minefield[coordx][coordy].getStatus() == mine) {             //make sure no duplicated bomb
            i--;
        }
        else {
            minefield[coordx][coordy].plantbomb();
            //cout << "Bomb is planted at " << coordx << " " << coordy << endl;               //checking where the bomb is planted
            //log(minefield[coordx][coordy].getStatus());                                //checking if bomb is planted properly

            for( int i = -1; i <= 1; i++) {                                              //add number of bomb near a coordinate
                for ( int z = -1; z <= 1; z++) {
                    if(coordx + i >= 0 && coordx + i <= 11) {
                        if (coordy + z >= 0 && coordy <= 11) {
                            if(minefield[coordx+i][coordy+z].getStatus() == mine) continue;
                            else {
                                minefield[coordx+i][coordy+z].addBombNumb();
                            }
                        }
                    }
                }
            }
        }
    }
}
void darstellen(){          //function to draw the map , darstellen
    for (int i = 0;i <= 11; i++) {      //line
        if(i <10) {
            cout  << "0" << i << "|";
            for(int z= 0 ; z < 12; z ++) {    //column
                minefield[i][z].statustodraw();
            }
            cout << "\n";    //naeschte Linie
        }
        else {     //else if i > 10
            cout << i << "|";
            for(int z = 0; z < 12; z ++) {    //column
                minefield[i][z].statustodraw();
            }
            cout << "\n";
        }
    }
    for(int i = 0; i<=26; i++) {cout << "-";}
    cout << "\n";
    cout << "  |" ;
    for(int i=0; i<= 11; i++) {
        if(i < 10) cout << i<< " " ;
        else cout << i;
    }
    cout <<"\n";
}
void input() {                                  //Eingabe funktion
    int inputx{}, inputy{};
    cout << "Input x: ";
    cin >> inputx;
    cout <<"\nInput y: ";
    cin >> inputy;
    if(inputx < 0 || inputx > 11) {
        if(inputy < 0 || inputy > 11) {
            log("INVALID VALUE");
            input();
        }
    }
    else
    inputstatus(inputx, inputy);
}
