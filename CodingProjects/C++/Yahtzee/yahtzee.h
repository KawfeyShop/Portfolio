#pragma once
#include <iostream>
#include <string> 
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>


#include <algorithm>
using namespace std;

class Dice {
    //all 5 dice roll, lock
public:
    static int Roll() {
        //srand(static_cast<unsigned int>(time(nullptr)));
        int dice_value = rand() % 6 + 1; // 1-6 random numbers 
        return dice_value;
    }
    static void ReRoll(vector<bool> torf, vector<int>& rolls) {
        for (int i = 0; i < 5; i++) {

            if (torf.at(i))
            {
                int tmp = Roll();
                rolls.at(i) = tmp;
            }
        }
    }

};

class ScoreCard {
private:
    int score = 0;
    vector<bool> available{ true, true, true, true, true, true, true, true, true, true, true, true, true };
    vector<int> points{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 };

public:
    //returns current score
    int getScore() {
        return score;
    }
    //stores the score and locks the category
    void storeScore(int rollScore, int choice) {
        if (available.at(choice) == true) {
            available.at(choice) = false;
            points.at(choice) = rollScore;
            score = score + rollScore;
        }
        else {
            cout << "error storing score" << endl;
        }
    }

    void getOptions(vector<int> dice, vector<int>& prospective) {
        vector<int> sortedDice = dice;
        sort(sortedDice.begin(), sortedDice.end());
        int sum = 0;

        for (int i = 0; i < 13; ++i) {
            if (!available.at(i)) {
                prospective.at(i) = -1;
            }
        }

        //1s
        if ((sortedDice.at(0) == 1) && available.at(0)) {
            sum = 0;
            for (int i = 0; i < 5; ++i) {
                if (dice.at(i) == 1) sum++;
            }
            prospective.at(0) = sum;
        }

        //2s
        if ((sortedDice.at(0) == 2 || sortedDice.at(1) == 2 || sortedDice.at(2) == 2 || sortedDice.at(3) == 2 || sortedDice.at(4) == 2) && available.at(1)) {
            sum = 0;
            for (int i = 0; i < 5; ++i) {
                if (dice.at(i) == 2) sum += 2;
            }
            prospective.at(1) = sum;
        }

        //3s
        if ((sortedDice.at(0) == 3 || sortedDice.at(1) == 3 || sortedDice.at(2) == 3 || sortedDice.at(3) == 3 || sortedDice.at(4) == 3) && available.at(2)) {
            sum = 0;
            for (int i = 0; i < 5; ++i) {
                if (dice.at(i) == 3) sum += 3;
            }
            prospective.at(2) = sum;
        }

        //4s
        if ((sortedDice.at(0) == 4 || sortedDice.at(1) == 4 || sortedDice.at(2) == 4 || sortedDice.at(3) == 4 || sortedDice.at(4) == 4) && available.at(3)) {
            sum = 0;
            for (int i = 0; i < 5; ++i) {
                if (dice.at(i) == 4) sum += 4;
            }
            prospective.at(3) = sum;
        }

        //5s
        if ((sortedDice.at(0) == 5 || sortedDice.at(1) == 5 || sortedDice.at(2) == 5 || sortedDice.at(3) == 5 || sortedDice.at(4) == 5) && available.at(4)) {
            sum = 0;
            for (int i = 0; i < 5; ++i) {
                if (dice.at(i) == 5) sum += 5;
            }
            prospective.at(4) = sum;
        }

        //6s
        if ((sortedDice.at(4) == 6) && available.at(5)) {
            sum = 0;
            for (int i = 0; i < 5; ++i) {
                if (dice.at(i) == 6) sum += 6;
            }
            prospective.at(5) = sum;
        }

        for (int i = 0; i <= 2; ++i) {
            if (sortedDice.at(i) == sortedDice.at(i + 2)) {
                //3 of a kind
                if ((sortedDice.at(i) == sortedDice.at(i + 1)) && available.at(6)) {
                    prospective.at(6) = dice.at(0) + dice.at(1) + dice.at(2) + dice.at(3) + dice.at(4);
                }

                //4 of a kind
                if (i != 2) {
                    if ((sortedDice.at(i) == sortedDice.at(i + 3)) && available.at(7)) {
                        prospective.at(7) = dice.at(0) + dice.at(1) + dice.at(2) + dice.at(3) + dice.at(4);
                    }
                }
            }
        }

        //full house
        if ((((sortedDice.at(0) == sortedDice.at(1) && sortedDice.at(2) == sortedDice.at(4))) || ((sortedDice.at(0) == sortedDice.at(2) && sortedDice.at(3) == sortedDice.at(4)))) && available.at(8)) {
            prospective.at(8) = 25;
        }

        //small straight
        if (((count(sortedDice.begin(), sortedDice.end(), 1) != 0 && count(sortedDice.begin(), sortedDice.end(), 2) != 0 && count(sortedDice.begin(), sortedDice.end(), 3) != 0 && count(sortedDice.begin(), sortedDice.end(), 4) != 0)
            || (count(sortedDice.begin(), sortedDice.end(), 2) != 0 && count(sortedDice.begin(), sortedDice.end(), 3) != 0 && count(sortedDice.begin(), sortedDice.end(), 4) != 0 && count(sortedDice.begin(), sortedDice.end(), 5) != 0)
            || (count(sortedDice.begin(), sortedDice.end(), 3) != 0 && count(sortedDice.begin(), sortedDice.end(), 4) != 0 && count(sortedDice.begin(), sortedDice.end(), 5) != 0 && count(sortedDice.begin(), sortedDice.end(), 6) != 0)
            ) && available.at(9)) {
            prospective.at(9) = 30;
        }

        //large straight
        if (((count(sortedDice.begin(), sortedDice.end(), 1) != 0 && count(sortedDice.begin(), sortedDice.end(), 2) != 0 && count(sortedDice.begin(), sortedDice.end(), 3) != 0 && count(sortedDice.begin(), sortedDice.end(), 4) != 0 && count(sortedDice.begin(), sortedDice.end(), 5) != 0)
            || (count(sortedDice.begin(), sortedDice.end(), 2) != 0 && count(sortedDice.begin(), sortedDice.end(), 3) != 0 && count(sortedDice.begin(), sortedDice.end(), 4) != 0 && count(sortedDice.begin(), sortedDice.end(), 5) != 0 && count(sortedDice.begin(), sortedDice.end(), 6) != 0)
            ) && available.at(10)) {
            prospective.at(10) = 40;
        }

        //yahtzee
        if ((sortedDice.at(0) == sortedDice.at(4)) && available.at(11)) {
            prospective.at(11) = 50;
        }
        else if ((sortedDice.at(0) == sortedDice.at(4)) && !available.at(11) && points.at(11) == 50) {
            score += 100;
            cout << "BONUS YAHTZEE: +100 bonus points" << endl;
            points.at(13) += 100;
        }

        //choice
        if (available.at(12)) {
            prospective.at(12) = dice.at(0) + dice.at(1) + dice.at(2) + dice.at(3) + dice.at(4);
        }
    }

    void printScore() {
        //print all final scores
        cout << right;
        cout << setw(17) << "Aces: " << setw(3) << points.at(0) << endl;
        cout << setw(17) << "Twos: " << setw(3) << points.at(1) << endl;
        cout << setw(17) << "Threes: " << setw(3) << points.at(2) << endl;
        cout << setw(17) << "Fours: " << setw(3) << points.at(3) << endl;
        cout << setw(17) << "Fives: " << setw(3) << points.at(4) << endl;
        cout << setw(17) << "Sixes: " << setw(3) << points.at(5) << endl;
        cout << setw(17) << "3 of a Kind: " << setw(3) << points.at(6) << endl;
        cout << setw(17) << "4 of a Kind: " << setw(3) << points.at(7) << endl;
        cout << setw(17) << "Full House: " << setw(3) << points.at(8) << endl;
        cout << setw(17) << "Small Straight: " << setw(3) << points.at(9) << endl;
        cout << setw(17) << "Large Straight: " << setw(3) << points.at(10) << endl;
        cout << setw(17) << "Yahtzee: " << setw(3) << points.at(11) << endl;
        cout << setw(17) << "Chance: " << setw(3) << points.at(12) << endl;
        cout << setw(17) << "Bonus Yahtzee: " << setw(3) << points.at(13) << endl;
    }
};

class Game {
public:
    void play() {
        string temp;
        bool valid = false;
        int playTemp;
        player newPlayer;

        //get player count
        while (!valid) {
            cout << "Enter how many players (1-10): ";
            cin >> playTemp;
            if (playTemp >= 1 && playTemp <= 10) {
                valid = true;
            }
        }

        //get player names
        cin.ignore();
        for (int j = 0; j < playTemp; ++j) {
            cout << "Enter player " << j + 1 << "'s name: ";
            getline(cin, temp);
            newPlayer.name = temp;
            playerList.push_back(newPlayer);
        }

        //play 13 rounds for each player
        roundNum = 1;
        while (roundNum <= 13) {
            playerNum = 1;
            while (playerNum <= playerList.size()) {
                round();
                ++playerNum;
            }
            ++roundNum;
        }

        //game over, print all scores
        clrscr();
        cout << "---- GAME OVER ----" << endl;
        cout << endl;
        cout << "Final scores: " << endl;
        for (int l = 0; l < playTemp; ++l) {
            cout << setw(17) << left << playerList.at(l).name << setw(3) << right << playerList.at(l).score.getScore() << left << endl;
            playerList.at(l).score.printScore();
            cout << endl;
        }
    }

    void round() {
        vector<bool> rerolls{ true, true, true, true, true };
        vector<bool> done{ false, false, false, false, false };
        vector<int> rolls{ 0, 0, 0, 0, 0 };
        vector<int> pointOptions{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        int choice = -1;
        string temp;
        bool roundDone = false;
        bool valid = false;

        //get initial roll
        cupRoll.ReRoll(rerolls, rolls);

        for (int i = 0; i < 2; ++i) {
            //allow 2 rerolls
            rerolls = { false, false, false, false, false };

            choice = -1;
            //set round done to false
            if (i == 0) {
                roundDone = false;
            }

            while (choice != 0 && roundDone == false) {
                //print the roll screen, allow 
                clrscr();
                cout << "Round " << roundNum << ", " << playerList.at(playerNum - 1).name << "'s turn:" << endl;
                printRolls(rolls, rerolls, false);
                cout << "\nEnter which dice to reroll, enter 0 to end selecting: ";
                cin >> choice;

                //if roll is valid
                if (choice >= 1 && choice <= 5) {
                    rerolls.at(choice - 1) = !rerolls.at(choice - 1);
                }
            }

            //reroll
            cupRoll.ReRoll(rerolls, rolls);

            //if 0 is entered with no rerolls, skip all future rerolls
            if (rerolls == done) {
                roundDone = true;
            }
        }
        //print end screen
        clrscr();
        cout << "Round " << roundNum << ", " << playerList.at(playerNum - 1).name << "'s turn:" << endl;
        printRolls(rolls, rerolls, true);
        //get options
        playerList.at(playerNum - 1).score.getOptions(rolls, pointOptions);

        //print available scorecard options


        cout << left << "Select which category you would like to score in: " << endl;
        cout << setw(18) << "Category" << "Score" << endl;
        cout << setw(20) << "1. Aces: ";
        if (pointOptions.at(0) != -1) cout << right << setw(3) << pointOptions.at(0);
        else cout << "  X";
        cout << left << endl;
        cout << setw(20) << "2. Twos: ";
        if (pointOptions.at(1) != -1) cout << right << setw(3) << pointOptions.at(1);
        else cout << "  X";
        cout << left << endl;
        cout << setw(20) << "3. Threes: ";
        if (pointOptions.at(2) != -1) cout << right << setw(3) << pointOptions.at(2);
        else cout << "  X";
        cout << left << endl;
        cout << setw(20) << "4. Fours: ";
        if (pointOptions.at(3) != -1) cout << right << setw(3) << pointOptions.at(3);
        else cout << "  X";
        cout << left << endl;
        cout << setw(20) << "5. Fives: ";
        if (pointOptions.at(4) != -1) cout << right << setw(3) << pointOptions.at(4);
        else cout << "  X";
        cout << left << endl;
        cout << setw(20) << "6. Sixes: ";
        if (pointOptions.at(5) != -1) cout << right << setw(3) << pointOptions.at(5);
        else cout << "  X";
        cout << left << endl;
        cout << setw(20) << "7. 3 of a Kind: ";
        if (pointOptions.at(6) != -1) cout << right << setw(3) << pointOptions.at(6);
        else cout << "  X";
        cout << left << endl;
        cout << setw(20) << "8. 4 of a Kind: ";
        if (pointOptions.at(7) != -1) cout << right << setw(3) << pointOptions.at(7);
        else cout << "  X";
        cout << left << endl;
        cout << setw(20) << "9. Full House: ";
        if (pointOptions.at(8) != -1) cout << right << setw(3) << pointOptions.at(8);
        else cout << "  X";
        cout << left << endl;
        cout << setw(20) << "10. Small Straight: ";
        if (pointOptions.at(9) != -1) cout << right << setw(3) << pointOptions.at(9);
        else cout << "  X";
        cout << left << endl;
        cout << setw(20) << "11. Large Straight: ";
        if (pointOptions.at(10) != -1) cout << right << setw(3) << pointOptions.at(10);
        else cout << "  X";
        cout << left << endl;
        cout << setw(20) << "12. Yahtzee: ";
        if (pointOptions.at(11) != -1) cout << right << setw(3) << pointOptions.at(11);
        else cout << "  X";
        cout << left << endl;
        cout << setw(20) << "13. Choice: ";
        if (pointOptions.at(12) != -1) cout << right << setw(3) << pointOptions.at(12);
        else cout << "  X";
        cout << left << endl;

        //get a valid category to put into the scorecard
        choice = -1;
        cout << "Enter category: ";
        while (!valid) {
            cin >> choice;
            choice = choice - 1;
            if (choice >= 0 && choice <= 12) {
                if (pointOptions.at(choice) != -1) {
                    playerList.at(playerNum - 1).score.storeScore(pointOptions.at(choice), choice);
                    valid = true;
                }
                else {
                    cout << "Option is not available. enter which category to score in: ";
                }
            }
            else {
                cout << "Invalid option. Enter which category to score in: ";
            }
        }

        //print scores
        cout << "Round score: " << pointOptions.at(choice) << endl;
        cout << "Current total score: " << playerList.at(playerNum - 1).score.getScore() << endl;
        cout << "Press enter to continue" << endl;
        cin.ignore();
        getline(cin, temp);
    }

    void printRolls(vector<int> rolls, vector<bool> selected, bool end) {
        //print the dice
        cout << "    1.        2.        3.        4.        5." << endl;
        cout << " -------   -------   -------   -------   -------  " << endl;

        //print the dice rolls for each line for each dice
        for (int i = 0; i < 5; ++i) {
            if (rolls.at(i) == 2 || rolls.at(i) == 3) {
                cout << "|     o | ";
            }
            else if (rolls.at(i) == 4 || rolls.at(i) == 5 || rolls.at(i) == 6) {
                cout << "| o   o | ";
            }
            else {
                cout << "|       | ";
            }
        }
        cout << endl;

        for (int i = 0; i < 5; ++i) {
            if (rolls.at(i) == 1 || rolls.at(i) == 3 || rolls.at(i) == 5) {
                cout << "|   o   | ";
            }
            else if (rolls.at(i) == 6) {
                cout << "| o   o | ";
            }
            else {
                cout << "|       | ";
            }
        }
        cout << endl;

        for (int i = 0; i < 5; ++i) {
            if (rolls.at(i) == 2 || rolls.at(i) == 3) {
                cout << "| o     | ";
            }
            else if (rolls.at(i) == 4 || rolls.at(i) == 5 || rolls.at(i) == 6) {
                cout << "| o   o | ";
            }
            else {
                cout << "|       | ";
            }
        }
        cout << endl;

        //bottom dice
        cout << " -------   -------   -------   -------   -------  " << endl;

        //print selection arrows (updated every input)
        if (end == false) {
            for (int i = 0; i < 5; ++i) {
                if (selected.at(i) == true) {
                    cout << "    A     ";
                }
                else {
                    cout << "          ";
                }
            }
            cout << "Currently selected dice";
            cout << endl;
            for (int i = 0; i < 5; ++i) {
                if (selected.at(i) == true) {
                    cout << "    |     ";
                }
                else {
                    cout << "          ";
                }
            }
            cout << "<--";
            cout << endl;
        }
    }

private:
    struct player {
        ScoreCard score;
        string name;
    };

    int roundNum = 1;
    int playerNum = 0;
    vector<player> playerList;
    Dice cupRoll;
    void clrscr() {
#if defined _WIN32
        system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) ||defined(__linux__)
        system("clear");
#elif defined (__APPLE__)
        system("clear");
#endif
    }
};