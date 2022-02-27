#include"prak3_1.cpp"

int main()
{
    initialisieren();
    counter();         //count the safe spot
    while(gameover == false) {
        cout << "Safe spot remains: " << countergedeckt << endl;
       darstellen();
       input();
       system("CLS");                   //function to clear terminal
    }
    endgame();
    darstellen();
}
