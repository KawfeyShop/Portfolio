#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <iostream>

#include "../yahtzee.h"

TEST_CASE("Class Dice can roll", "[Roll]") {
	//Roll function, make sure random number is in range, repeat to test range more accurately
	Dice diceCup;
	for (int i = 0; i < 100; ++i) {
		REQUIRE(diceCup.Roll() >= 1);
		REQUIRE(diceCup.Roll() <= 6);
	}
}
	
TEST_CASE("Class Dice can reroll", "[ReRoll]") {
	//ReRoll function
	Dice diceCup;

	//make sure none are rerolled if all false
	vector<bool> rerolls{ false, false, false, false, false };
	vector<int> rolls{0, 0, 0, 0, 0 };
	diceCup.ReRoll(rerolls,rolls);
	vector<int> test = { 0, 0, 0, 0, 0 };
	REQUIRE(rolls == test);

	//make sure all are rerolled if all true
	rerolls = { true, true, true, true, true };
	rolls = {0, 0, 0, 0, 0 };
	diceCup.ReRoll(rerolls, rolls);
	REQUIRE((rolls.at(0) != 0 && rolls.at(1) != 0 && rolls.at(2) != 0 && rolls.at(3) != 0 && rolls.at(4) != 0));

	//make sure only selected rolls are rerolled
	rerolls = { false, false, true, false, false };
	rolls = {0, 0, 0, 0, 0 };
	diceCup.ReRoll(rerolls, rolls);
	REQUIRE((rolls.at(2) != 0 && rolls.at(0) == 0 && rolls.at(1) == 0 && rolls.at(3) == 0 && rolls.at(4) == 0));
}

TEST_CASE("Class ScoreCard stores scores", "[storeScore]") {
	//make sure store score stores a score
	ScoreCard score;
	score.storeScore(15, 2);
	REQUIRE(score.getScore() == 15);
}

TEST_CASE("Class ScoreCard does not override taken scores", "[storeScore]"){
	//new score should not be added, the category should be locked
	ScoreCard score;
	score.storeScore(15, 2);
	REQUIRE(score.getScore() == 15);

	score.storeScore(25, 2);
	REQUIRE(score.getScore() == 15);
}

TEST_CASE("ScoreCard class's getOptions calculates 1s", "[getOptions]") {
	//make sure 1 category is found
	ScoreCard score;
	vector<int> rolls{ 1, 1, 1, 1, 1 };
	vector<int> prospective{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	REQUIRE(prospective.at(0) == 5);
}

TEST_CASE("ScoreCard class's getOptions calculates 2s", "[getOptions]") {
	//make sure 2 category is found
	ScoreCard score;
	vector<int> rolls{ 2, 2, 2, 2, 2 };
	vector<int> prospective{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	REQUIRE(prospective.at(1) == 10);
}

TEST_CASE("ScoreCard class's getOptions calculates 3s", "[getOptions]") {
	//make sure 3 category is found
	ScoreCard score;
	vector<int> rolls{ 3, 3, 3, 3, 3 };
	vector<int> prospective{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	REQUIRE(prospective.at(2) == 15);
}

TEST_CASE("ScoreCard class's getOptions calculates 4s", "[getOptions]") {
	//make sure 4 category is found
	ScoreCard score;
	vector<int> rolls{ 4, 4, 4, 4, 4 };
	vector<int> prospective{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	REQUIRE(prospective.at(3) == 20);
}

TEST_CASE("ScoreCard class's getOptions calculates 5s", "[getOptions]") {
	//make sure 5 category is found
	ScoreCard score;
	vector<int> rolls{ 5, 5, 5, 5, 5 };
	vector<int> prospective{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	REQUIRE(prospective.at(4) == 25);
}

TEST_CASE("ScoreCard class's getOptions calculates 6s", "[getOptions]") {
	//make sure 6 category is found
	ScoreCard score;
	vector<int> rolls{ 6, 6, 6, 6, 6 };
	vector<int> prospective{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	REQUIRE(prospective.at(5) == 30);
}

TEST_CASE("ScoreCard class's getOptions calculates 3 of a kind", "[getOptions]") {
	//make sure 3 of a kind category is found
	ScoreCard score;
	vector<int> rolls{ 5, 5, 5, 3, 2 };
	vector<int> prospective{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	REQUIRE(prospective.at(6) == 20);
}

TEST_CASE("ScoreCard class's getOptions calculates 4 of a kind", "[getOptions]") {
	//make sure 4 of a kind category is found
	ScoreCard score;
	vector<int> rolls{ 5, 5, 5, 5, 6 };
	vector<int> prospective{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	REQUIRE(prospective.at(7) == 26);
}

TEST_CASE("ScoreCard class's getOptions calculates full house", "[getOptions]") {
	//make sure full category is found
	ScoreCard score;
	vector<int> rolls{ 3, 3, 3, 4, 4 };
	vector<int> prospective{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	REQUIRE(prospective.at(8) == 25);
}

TEST_CASE("ScoreCard class's getOptions calculates small straight", "[getOptions]") {
	//make sure small straight category is found
	ScoreCard score;
	vector<int> rolls{ 1, 2, 3, 4, 4 };
	vector<int> prospective{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	REQUIRE(prospective.at(9) == 30);
}

TEST_CASE("ScoreCard class's getOptions calculates large straight", "[getOptions]") {
	//make sure large straight category is found
	ScoreCard score;
	vector<int> rolls{ 1, 2, 3, 4, 5 };
	vector<int> prospective{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	REQUIRE(prospective.at(10) == 40);
}

TEST_CASE("ScoreCard class's getOptions calculates yahtzees and bonus yahtzee", "[getOptions]") {
	//make sure yahtzee score is found
	ScoreCard score;
	vector<int> rolls{ 4, 4, 4, 4, 4 };
	vector<int> prospective{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	//also make sure other categories are found correctly in conjunction
	vector<int> test = { 0, 0, 0, 20, 0, 0, 20, 20, 25, 0, 0, 50, 20 };
	REQUIRE(prospective == test);

	//make sure yahtzee is locked out and bonus yahtzee points is added
	score.storeScore(50, 11);
	REQUIRE(score.getScore() == 50);
	prospective = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	test = { 0, 0, 0, 20, 0, 0, 20, 20, 25, 0, 0, -1, 20 };
	REQUIRE(prospective == test);
	REQUIRE(score.getScore() == 150);

	//make sure yahtzee is now unavailable
	score.storeScore(20, 3);
	REQUIRE(score.getScore() == 170);
	rolls = { 1,2,3,4,5 };
	prospective ={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	test = { 1, 2, 3, -1, 5, 0, 0, 0, 0, 30, 40, -1, 15 };
	REQUIRE(prospective == test);
}

TEST_CASE("ScoreCard class's getOptions calculates Choice and locks", "[getOptions]") {
	//make sure choice option is placd
	ScoreCard score;
	vector<int> rolls{ 2, 5, 3, 1, 4 };
	vector<int> prospective{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	REQUIRE(prospective.at(12) == 15);

	score.storeScore(15, 12);

	//make sure choice is locked
	prospective = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	REQUIRE(prospective.at(12) == -1);
}

TEST_CASE("ScoreCard class's getOptions locks options over a normal game", "[getOptions]") {
	//make sure all options get locked except for 1 at the end of the game
	ScoreCard score;
	score.storeScore(0, 0);
	score.storeScore(0, 1);
	score.storeScore(0, 2);
	score.storeScore(0, 3);
	score.storeScore(0, 4);
	score.storeScore(0, 5);
	score.storeScore(0, 6);
	score.storeScore(0, 7);
	score.storeScore(0, 8);
	score.storeScore(0, 9);
	score.storeScore(0, 10);
	score.storeScore(0, 11);
	
	vector<int> rolls{ 2, 5, 3, 1, 4 };
	vector<int> prospective{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	vector<int> test = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15 };
	REQUIRE(prospective == test);
	
	//make sure all options are now locked
	score.storeScore(0, 12);
	prospective = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	score.getOptions(rolls, prospective);
	test = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	REQUIRE(prospective == test);
	REQUIRE(score.getScore() == 0);
}


TEST_CASE("ScoreCard class's printScore does not change any scores", "[printScore]") {
	//make sure no variables in print score is changed
	ScoreCard score;
	
	score.storeScore(5, 0);

	int prevScore = score.getScore();

	score.printScore();

	REQUIRE(score.getScore() == prevScore);
}

//All game class functions have a cin statement, or a clear screen statement which does not work with unit testing.
//Game class operates as our main function and is not well suited for unit tests and does not work with unit testing.