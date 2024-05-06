#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>

#include "./yahtzee.h"
using namespace std;

int main() {
    Game mainGame;
    string input;
    srand(time(0));

    //play game again if not Done
    while (input != "DONE") {
        mainGame.play();

        cout << endl;
        cout << "Enter \"DONE\" to end, press any key to play again: ";
        cin >> input;
    }
    cout << "Thanks for playing :)" << endl;
    return 0;
}